//! Constant propagation over matched Thumb code. A value is known only when every path to it agrees; anything the
//! decoder cannot follow becomes unknown, never guessed. A load from a fixed RAM address stays symbolic (the value at
//! that address, with the arithmetic applied after it) so a caller can evaluate it against the stores made before.

use std::collections::{BTreeMap, BTreeSet, HashMap, VecDeque};
use std::rc::Rc;

use crate::rom::{le16, le32, Rom, R};
use crate::{repo_root, verify_c, BASE, ROM_SIZE};

/// r0-r3 and the first eight stack words at the call.
pub const ARGS: usize = 12;
const STACK_ARGS: usize = ARGS - 4;
const MAX_OPS: usize = 8;

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, PartialOrd, Ord)]
pub enum Op {
    Add(u32),
    Mul(u32),
    Lsl(u32),
    Lsr(u32),
    Asr(u32),
    And(u32),
    Orr(u32),
    Xor(u32),
    Not,
}

impl Op {
    fn apply(self, value: u32) -> u32 {
        match self {
            Op::Add(k) => value.wrapping_add(k),
            Op::Mul(k) => value.wrapping_mul(k),
            Op::Lsl(k) => if k >= 32 { 0 } else { value << k },
            Op::Lsr(k) => if k >= 32 { 0 } else { value >> k },
            Op::Asr(k) => ((value as i32) >> k.min(31)) as u32,
            Op::And(k) => value & k,
            Op::Orr(k) => value | k,
            Op::Xor(k) => value ^ k,
            Op::Not => !value,
        }
    }
}

/// The value at a fixed RAM address (`size` bytes, sign-extended when `signed`), then `ops` in order.
#[derive(Clone, Debug, PartialEq, Eq, Hash, PartialOrd, Ord)]
pub struct Sym {
    pub address: u32,
    pub size: u8,
    pub signed: bool,
    pub ops: Vec<Op>,
}

#[derive(Clone, Debug, PartialEq, Eq, Hash, PartialOrd, Ord, Default)]
pub enum V {
    #[default]
    Top,
    C(u32),
    G(Rc<Sym>),
}

impl V {
    pub fn c(&self) -> Option<u32> {
        match self {
            V::C(value) => Some(*value),
            _ => None,
        }
    }

    fn op(&self, op: Op) -> V {
        match self {
            V::C(value) => V::C(op.apply(*value)),
            V::G(sym) if sym.ops.len() < MAX_OPS => {
                let mut sym = (**sym).clone();
                sym.ops.push(op);
                V::G(Rc::new(sym))
            }
            _ => V::Top,
        }
    }

    /// `self <op> other` where the result can be expressed: both constant, or one side constant.
    fn bin(&self, other: &V, op: fn(u32) -> Op, commutative: bool) -> V {
        match (self, other) {
            (V::C(a), V::C(b)) => V::C(op(*b).apply(*a)),
            (V::G(_), V::C(b)) => self.op(op(*b)),
            (V::C(a), V::G(_)) if commutative => other.op(op(*a)),
            _ => V::Top,
        }
    }

    fn add(&self, other: &V) -> V {
        self.bin(other, Op::Add, true)
    }

    fn sub(&self, other: &V) -> V {
        match other {
            V::C(b) => self.op(Op::Add(b.wrapping_neg())),
            _ => V::Top,
        }
    }

    /// The value, given the bytes known at fixed RAM addresses.
    pub fn eval(&self, read: &dyn Fn(u32, u8) -> Option<u32>) -> Option<u32> {
        match self {
            V::Top => None,
            V::C(value) => Some(*value),
            V::G(sym) => {
                let raw = read(sym.address, sym.size)?;
                let mut value = match (sym.size, sym.signed) {
                    (1, true) => raw as u8 as i8 as i32 as u32,
                    (2, true) => raw as u16 as i16 as i32 as u32,
                    _ => raw,
                };
                for op in &sym.ops {
                    value = op.apply(value);
                }
                Some(value)
            }
        }
    }
}

#[derive(Clone, Copy, Debug)]
pub struct Function {
    pub entry: u32,
    pub hi: u32,
}

/// Thumb functions of cfg/functions.json that lie wholly in matched code.
pub fn functions(rom: &Rom) -> R<Vec<Function>> {
    let text = std::fs::read_to_string(repo_root().join("cfg/functions.json")).map_err(|error| error.to_string())?;
    let owners: Vec<serde_json::Value> = serde_json::from_str(&text).map_err(|error| error.to_string())?;
    let mut out = Vec::new();
    for owner in &owners {
        if owner["mode"] != "thumb" {
            continue;
        }
        let lo = verify_c::parse_hex(owner["lo"].as_str().unwrap_or(""))?;
        let hi = verify_c::parse_hex(owner["hi"].as_str().unwrap_or(""))?;
        if rom.code_bytes(lo, hi - lo).is_ok() {
            out.push(Function { entry: lo, hi });
        }
    }
    out.sort_by_key(|function| function.entry);
    Ok(out)
}

#[derive(Clone, Debug, PartialEq, Eq)]
struct State {
    r: [V; 15],
    sp: Option<i32>,
    stack: BTreeMap<i32, V>,
    escaped: bool,
    /// N, Z, C, V.
    flags: [Option<bool>; 4],
}

impl State {
    fn entry(args: &[V; ARGS]) -> State {
        let mut r: [V; 15] = Default::default();
        r[..4].clone_from_slice(&args[..4]);
        let stack = (0..STACK_ARGS).filter(|index| args[4 + index] != V::Top).map(|index| (index as i32 * 4, args[4 + index].clone())).collect();
        State { r, sp: Some(0), stack, escaped: false, flags: [None; 4] }
    }

    fn join(&mut self, other: &State) -> bool {
        let before = self.clone();
        for (mine, theirs) in self.r.iter_mut().zip(other.r.iter()) {
            if mine != theirs {
                *mine = V::Top;
            }
        }
        if self.sp != other.sp {
            self.sp = None;
            self.stack.clear();
        }
        self.stack.retain(|key, value| other.stack.get(key) == Some(value) && *value != V::Top);
        self.escaped |= other.escaped;
        for (mine, theirs) in self.flags.iter_mut().zip(other.flags.iter()) {
            if mine != theirs {
                *mine = None;
            }
        }
        *self != before
    }

    fn slot(&self, offset: u32) -> V {
        let Some(sp) = self.sp else { return V::Top };
        self.stack.get(&(sp + offset as i32)).cloned().unwrap_or_default()
    }

    fn store_slot(&mut self, offset: u32, value: V) {
        if let Some(sp) = self.sp {
            self.stack.insert(sp + offset as i32, value);
        }
    }

    fn nz(&mut self, value: &V) {
        let value = value.c();
        self.flags[0] = value.map(|value| value >> 31 != 0);
        self.flags[1] = value.map(|value| value == 0);
    }

    fn flags_sub(&mut self, a: &V, b: &V) {
        match (a.c(), b.c()) {
            (Some(a), Some(b)) => {
                let result = a.wrapping_sub(b);
                self.flags = [Some(result >> 31 != 0), Some(result == 0), Some(a >= b), Some(((a ^ b) & (a ^ result)) >> 31 != 0)];
            }
            _ => self.flags = [None; 4],
        }
    }

    fn flags_add(&mut self, a: &V, b: &V) {
        match (a.c(), b.c()) {
            (Some(a), Some(b)) => {
                let result = a.wrapping_add(b);
                self.flags = [Some(result >> 31 != 0), Some(result == 0), Some(result < a), Some((!(a ^ b) & (a ^ result)) >> 31 != 0)];
            }
            _ => self.flags = [None; 4],
        }
    }

    /// Whether condition `code` holds, when the flags it reads are known.
    fn condition(&self, code: u16) -> Option<bool> {
        let [n, z, c, v] = self.flags;
        let holds = match code >> 1 {
            0 => z?,
            1 => c?,
            2 => n?,
            3 => v?,
            4 => c? && !z?,
            5 => n? == v?,
            _ => !z? && n? == v?,
        };
        Some(if code & 1 == 1 { !holds } else { holds })
    }

    fn memory_store(&mut self) {
        if self.escaped {
            self.stack.clear();
        }
    }
}

#[derive(Clone, Debug)]
pub struct Call {
    pub site: u32,
    pub target: u32,
    pub args: [V; ARGS],
}

/// A store to a fixed RAM address.
#[derive(Clone, Debug)]
pub struct Store {
    pub site: u32,
    pub address: u32,
    pub size: u8,
    pub value: V,
}

#[derive(Default, Debug)]
pub struct Analysis {
    /// Calls in address order of their sites.
    pub calls: Vec<Call>,
    /// Calls through a register the analysis could not resolve.
    pub unknown_calls: Vec<u32>,
    /// Every word loaded pc-relative, by load site.
    pub literals: BTreeMap<u32, u32>,
    /// Stores to fixed RAM addresses, in address order of their sites.
    pub stores: Vec<Store>,
    /// Jumps through a register with no table found.
    pub unknown_jumps: Vec<u32>,
    /// Halfwords inside the function never reached and not pool, table or padding.
    pub unreached: u32,
}

enum Flow {
    Next,
    Stop,
    Jump(u32),
    Branch(u32),
    Table(Vec<u32>),
}

pub struct Code<'a> {
    rom: &'a Rom,
    /// `bx rN` stubs (agbcc _call_via_rN): entry -> N.
    via: HashMap<u32, usize>,
    pub functions: Vec<Function>,
}

fn is_rom(address: u32) -> bool {
    (BASE..BASE + ROM_SIZE).contains(&address)
}

fn is_ram(address: u32) -> bool {
    matches!(address >> 24, 0x02 | 0x03)
}

impl<'a> Code<'a> {
    pub fn new(rom: &'a Rom) -> R<Code<'a>> {
        let functions = functions(rom)?;
        let mut via = HashMap::new();
        for function in &functions {
            let half = le16(rom.code_bytes(function.entry, 2)?, 0);
            if half & 0xFF87 == 0x4700 && function.hi - function.entry <= 4 {
                via.insert(function.entry, usize::from((half >> 3) & 15));
            }
        }
        Ok(Code { rom, via, functions })
    }

    pub fn function_at(&self, entry: u32) -> Option<Function> {
        self.functions.binary_search_by_key(&entry, |function| function.entry).ok().map(|index| self.functions[index])
    }

    fn enqueue(states: &mut BTreeMap<u32, State>, queue: &mut VecDeque<u32>, next: u32, next_state: State) {
        match states.get_mut(&next) {
            Some(existing) => {
                if existing.join(&next_state) {
                    queue.push_back(next);
                }
            }
            None => {
                states.insert(next, next_state);
                queue.push_back(next);
            }
        }
    }

    fn half(&self, at: u32) -> R<u16> {
        Ok(le16(self.rom.code_bytes(at, 2)?, 0))
    }

    /// A load of `size` bytes: ROM contents when the address is a constant ROM address, the symbolic value for a fixed
    /// RAM address, else unknown.
    fn load(&self, address: &V, size: u32, signed: bool) -> V {
        let Some(address) = address.c() else { return V::Top };
        if is_rom(address) && address % size == 0 && address - BASE + size <= ROM_SIZE {
            let Some(word) = self.rom.scan_word(address & !3) else { return V::Top };
            let shift = (address & 3) * 8;
            let value = match size {
                4 => word,
                2 => (word >> shift) & 0xFFFF,
                _ => (word >> shift) & 0xFF,
            };
            return V::C(match (size, signed) {
                (1, true) => value as u8 as i8 as i32 as u32,
                (2, true) => value as u16 as i16 as i32 as u32,
                _ => value,
            });
        }
        if is_ram(address) {
            return V::G(Rc::new(Sym { address, size: size as u8, signed, ops: Vec::new() }));
        }
        V::Top
    }

    pub fn analyze(&self, function: Function, args: &[V; ARGS]) -> R<Analysis> {
        let mut analysis = Analysis::default();
        let mut states: BTreeMap<u32, State> = BTreeMap::new();
        let mut data: BTreeSet<u32> = BTreeSet::new();
        let mut queue = VecDeque::new();
        states.insert(function.entry, State::entry(args));
        queue.push_back(function.entry);
        let mut calls: BTreeMap<u32, Call> = BTreeMap::new();
        let mut stores: BTreeMap<u32, Option<Store>> = BTreeMap::new();
        let mut unknown_calls = BTreeSet::new();
        let mut unknown_jumps = BTreeSet::new();
        let inside = |at: u32| at >= function.entry && at < function.hi;
        while let Some(at) = queue.pop_front() {
            let mut state = states[&at].clone();
            let instruction = self.half(at)?;
            let mut successors = Vec::new();
            if instruction & 0xF800 == 0xF000 {
                let low = self.half(at + 2)?;
                if low & 0xF800 != 0xF800 {
                    return Err(format!("0x{at:08X}: BL prefix without suffix"));
                }
                let offset = ((i32::from(instruction & 0x7FF) << 21) >> 9) + (i32::from(low & 0x7FF) << 1);
                let target = (at as i32 + 4 + offset) as u32;
                if inside(target) && target != function.entry {
                    Self::enqueue(&mut states, &mut queue, target, state);
                    continue;
                }
                let mut call_args: [V; ARGS] = Default::default();
                call_args[..4].clone_from_slice(&state.r[..4]);
                for index in 0..STACK_ARGS {
                    call_args[4 + index] = state.slot(index as u32 * 4);
                }
                match self.via.get(&target) {
                    Some(&register) => match state.r[register].c() {
                        Some(pointer) if self.function_at(pointer & !1).is_some() => {
                            calls.insert(at, Call { site: at, target: pointer & !1, args: call_args });
                        }
                        _ => {
                            unknown_calls.insert(at);
                        }
                    },
                    None => {
                        calls.insert(at, Call { site: at, target, args: call_args });
                    }
                }
                for register in [0, 1, 2, 3, 12, 14] {
                    state.r[register] = V::Top;
                }
                state.flags = [None; 4];
                for index in 0..STACK_ARGS as u32 {
                    state.store_slot(index * 4, V::Top);
                }
                if state.escaped {
                    state.stack.clear();
                }
                successors.push((at + 4, state));
            } else {
                match self.step(at, instruction, &mut state, &mut analysis.literals, &mut stores, &mut data, function)? {
                    Flow::Next => successors.push((at + 2, state)),
                    Flow::Stop => {}
                    Flow::Jump(target) => successors.push((target, state)),
                    Flow::Branch(target) => {
                        successors.push((target, state.clone()));
                        successors.push((at + 2, state));
                    }
                    Flow::Table(targets) => {
                        if targets.is_empty() {
                            unknown_jumps.insert(at);
                        }
                        for target in targets {
                            successors.push((target, state.clone()));
                        }
                    }
                }
            }
            for (next, next_state) in successors {
                if !inside(next) {
                    if next != at + 2 && next != at + 4 {
                        continue;
                    }
                    return Err(format!("0x{at:08X}: falls off the end of function 0x{:08X}", function.entry));
                }
                Self::enqueue(&mut states, &mut queue, next, next_state);
            }
        }
        let mut at = function.entry;
        while at < function.hi {
            if states.contains_key(&at) {
                let half = self.half(at)?;
                at += if half & 0xF800 == 0xF000 { 4 } else { 2 };
                continue;
            }
            if data.contains(&(at & !3)) {
                at += 2;
                continue;
            }
            let half = self.half(at)?;
            if half != 0 && half != 0x46C0 {
                analysis.unreached += 1;
            }
            at += 2;
        }
        analysis.calls = calls.into_values().collect();
        analysis.stores = stores.into_values().flatten().collect();
        analysis.unknown_calls = unknown_calls.into_iter().collect();
        analysis.unknown_jumps = unknown_jumps.into_iter().collect();
        Ok(analysis)
    }

    /// A store through `address`: recorded when the address is a fixed RAM address.
    fn store(&self, at: u32, address: &V, size: u8, value: V, s: &mut State, stores: &mut BTreeMap<u32, Option<Store>>) {
        s.memory_store();
        stores.insert(at, address.c().filter(|address| is_ram(*address)).map(|address| Store { site: at, address, size, value }));
    }

    #[allow(clippy::too_many_arguments)]
    fn step(&self, at: u32, ins: u16, s: &mut State, literals: &mut BTreeMap<u32, u32>, stores: &mut BTreeMap<u32, Option<Store>>, data: &mut BTreeSet<u32>, function: Function) -> R<Flow> {
        let rd = usize::from(ins & 7);
        let rs = usize::from((ins >> 3) & 7);
        match ins >> 13 {
            0b000 => {
                let op = (ins >> 11) & 3;
                let a = s.r[rs].clone();
                if op == 3 {
                    let operand = if ins & 0x400 != 0 { V::C(u32::from((ins >> 6) & 7)) } else { s.r[usize::from((ins >> 6) & 7)].clone() };
                    if ins & 0x200 == 0 {
                        s.flags_add(&a, &operand);
                        s.r[rd] = a.add(&operand);
                    } else {
                        s.flags_sub(&a, &operand);
                        s.r[rd] = a.sub(&operand);
                    }
                } else {
                    let amount = u32::from((ins >> 6) & 31);
                    s.r[rd] = match op {
                        0 => a.op(Op::Lsl(amount)),
                        1 => a.op(Op::Lsr(if amount == 0 { 32 } else { amount })),
                        _ => a.op(Op::Asr(if amount == 0 { 31 } else { amount })),
                    };
                    let value = s.r[rd].clone();
                    s.nz(&value);
                    if !(op == 0 && amount == 0) {
                        s.flags[2] = None;
                    }
                }
                Ok(Flow::Next)
            }
            0b001 => {
                let register = usize::from((ins >> 8) & 7);
                let immediate = V::C(u32::from(ins & 0xFF));
                let current = s.r[register].clone();
                match (ins >> 11) & 3 {
                    0 => {
                        s.nz(&immediate);
                        s.r[register] = immediate;
                    }
                    1 => s.flags_sub(&current, &immediate),
                    2 => {
                        s.flags_add(&current, &immediate);
                        s.r[register] = current.add(&immediate);
                    }
                    _ => {
                        s.flags_sub(&current, &immediate);
                        s.r[register] = current.sub(&immediate);
                    }
                }
                Ok(Flow::Next)
            }
            _ if ins & 0xFC00 == 0x4000 => {
                let (a, b) = (s.r[rd].clone(), s.r[rs].clone());
                let alu = (ins >> 6) & 15;
                match alu {
                    0x8 => {
                        s.nz(&a.bin(&b, Op::And, true));
                        return Ok(Flow::Next);
                    }
                    0xA => {
                        s.flags_sub(&a, &b);
                        return Ok(Flow::Next);
                    }
                    0xB => {
                        s.flags_add(&a, &b);
                        return Ok(Flow::Next);
                    }
                    0x9 => s.flags_sub(&V::C(0), &b),
                    0x5 | 0x6 => s.flags = [None; 4],
                    _ => {}
                }
                let by = |f: fn(u32) -> Op| match b.c() {
                    Some(amount) => a.op(f(amount & 0xFF)),
                    None => V::Top,
                };
                let value = match alu {
                    0x0 => a.bin(&b, Op::And, true),
                    0x1 => a.bin(&b, Op::Xor, true),
                    0x2 => by(Op::Lsl),
                    0x3 => by(Op::Lsr),
                    0x4 => by(Op::Asr),
                    0x7 => match (a.c(), b.c()) {
                        (Some(a), Some(b)) => V::C(a.rotate_right(b & 31)),
                        _ => V::Top,
                    },
                    0x9 => match b.c() {
                        Some(b) => V::C(b.wrapping_neg()),
                        None => V::Top,
                    },
                    0xC => a.bin(&b, Op::Orr, true),
                    0xD => a.bin(&b, Op::Mul, true),
                    0xE => match b.c() {
                        Some(b) => a.op(Op::And(!b)),
                        None => V::Top,
                    },
                    0xF => b.op(Op::Not),
                    _ => V::Top,
                };
                match alu {
                    0x9 | 0x5 | 0x6 => {}
                    0x2 | 0x3 | 0x4 | 0x7 | 0xD => {
                        s.nz(&value);
                        s.flags[2] = None;
                    }
                    _ => s.nz(&value),
                }
                s.r[rd] = value;
                Ok(Flow::Next)
            }
            _ if ins & 0xFC00 == 0x4400 => {
                let op = (ins >> 8) & 3;
                let hd = rd | if ins & 0x80 != 0 { 8 } else { 0 };
                let hs = rs | if ins & 0x40 != 0 { 8 } else { 0 };
                let source = match hs {
                    13 => V::Top,
                    15 => V::C(at + 4),
                    _ => s.r[hs].clone(),
                };
                match op {
                    0 => {
                        if hd == 15 {
                            return Ok(self.jump(at, &source, literals, data, function));
                        }
                        if hd == 13 {
                            s.sp = None;
                            s.stack.clear();
                        } else {
                            s.r[hd] = s.r[hd].add(&source);
                        }
                    }
                    1 => {
                        let a = match hd {
                            15 => V::C(at + 4),
                            13 => V::Top,
                            _ => s.r[hd].clone(),
                        };
                        s.flags_sub(&a, &source);
                    }
                    2 => {
                        if hd == 15 {
                            return Ok(self.jump(at, &source, literals, data, function));
                        }
                        if hs == 13 {
                            s.escaped = true;
                        }
                        if hd == 13 {
                            s.sp = None;
                            s.stack.clear();
                        } else {
                            s.r[hd] = source;
                        }
                    }
                    _ => {
                        return Ok(match source.c() {
                            Some(target) if hs != 14 && target & 1 == 1 && target & !1 >= function.entry && target & !1 < function.hi => Flow::Jump(target & !1),
                            _ => Flow::Stop,
                        });
                    }
                }
                Ok(Flow::Next)
            }
            _ if ins & 0xF800 == 0x4800 => {
                let address = ((at + 4) & !3) + u32::from(ins & 0xFF) * 4;
                let value = self.rom.scan_word(address).ok_or_else(|| format!("0x{at:08X}: literal outside the ROM"))?;
                literals.insert(at, value);
                data.insert(address);
                s.r[usize::from((ins >> 8) & 7)] = V::C(value);
                Ok(Flow::Next)
            }
            _ if ins & 0xF000 == 0x5000 => {
                let address = s.r[rs].add(&s.r[usize::from((ins >> 6) & 7)]);
                match (ins >> 9) & 7 {
                    0 => self.store(at, &address, 4, s.r[rd].clone(), s, stores),
                    1 => self.store(at, &address, 2, s.r[rd].op(Op::And(0xFFFF)), s, stores),
                    2 => self.store(at, &address, 1, s.r[rd].op(Op::And(0xFF)), s, stores),
                    3 => s.r[rd] = self.load(&address, 1, true),
                    4 => s.r[rd] = self.load(&address, 4, false),
                    5 => s.r[rd] = self.load(&address, 2, false),
                    6 => s.r[rd] = self.load(&address, 1, false),
                    _ => s.r[rd] = self.load(&address, 2, true),
                }
                Ok(Flow::Next)
            }
            0b011 | 0b100 if ins & 0xF000 != 0x9000 => {
                let offset = u32::from((ins >> 6) & 31);
                let size: u32 = match ins >> 12 {
                    0x6 => 4,
                    0x7 => 1,
                    _ => 2,
                };
                let address = s.r[rs].add(&V::C(offset * size));
                if ins & 0x800 != 0 {
                    s.r[rd] = self.load(&address, size, false);
                } else {
                    let value = match size {
                        4 => s.r[rd].clone(),
                        2 => s.r[rd].op(Op::And(0xFFFF)),
                        _ => s.r[rd].op(Op::And(0xFF)),
                    };
                    self.store(at, &address, size as u8, value, s, stores);
                }
                Ok(Flow::Next)
            }
            _ if ins & 0xF000 == 0x9000 => {
                let register = usize::from((ins >> 8) & 7);
                let offset = u32::from(ins & 0xFF) * 4;
                if ins & 0x800 != 0 {
                    s.r[register] = s.slot(offset);
                } else {
                    let value = s.r[register].clone();
                    s.store_slot(offset, value);
                }
                Ok(Flow::Next)
            }
            _ if ins & 0xF000 == 0xA000 => {
                let register = usize::from((ins >> 8) & 7);
                let offset = u32::from(ins & 0xFF) * 4;
                if ins & 0x800 == 0 {
                    s.r[register] = V::C(((at + 4) & !3) + offset);
                } else {
                    s.r[register] = V::Top;
                    s.escaped = true;
                }
                Ok(Flow::Next)
            }
            _ if ins & 0xFF00 == 0xB000 => {
                let offset = i32::from(ins & 0x7F) * 4;
                s.sp = s.sp.map(|sp| if ins & 0x80 != 0 { sp - offset } else { sp + offset });
                Ok(Flow::Next)
            }
            _ if ins & 0xF600 == 0xB400 => {
                let list: Vec<usize> = (0..8).filter(|bit| ins & (1 << bit) != 0).collect();
                let extra = ins & 0x100 != 0;
                let count = list.len() as i32 + i32::from(extra);
                if ins & 0x800 == 0 {
                    s.sp = s.sp.map(|sp| sp - count * 4);
                    let mut values: Vec<V> = list.iter().map(|&register| s.r[register].clone()).collect();
                    if extra {
                        values.push(V::Top);
                    }
                    for (index, value) in values.into_iter().enumerate() {
                        s.store_slot(index as u32 * 4, value);
                    }
                    Ok(Flow::Next)
                } else {
                    for (index, &register) in list.iter().enumerate() {
                        s.r[register] = s.slot(index as u32 * 4);
                    }
                    s.sp = s.sp.map(|sp| sp + count * 4);
                    Ok(if extra { Flow::Stop } else { Flow::Next })
                }
            }
            _ if ins & 0xF000 == 0xC000 => {
                let base = usize::from((ins >> 8) & 7);
                let list: Vec<usize> = (0..8).filter(|bit| ins & (1 << bit) != 0).collect();
                if ins & 0x800 != 0 {
                    for &register in &list {
                        s.r[register] = V::Top;
                    }
                } else {
                    s.memory_store();
                    stores.insert(at, None);
                }
                if !(ins & 0x800 != 0 && list.contains(&base)) {
                    s.r[base] = s.r[base].add(&V::C(list.len() as u32 * 4));
                }
                Ok(Flow::Next)
            }
            _ if ins & 0xFF00 == 0xDF00 => {
                for register in [0, 1, 2, 3] {
                    s.r[register] = V::Top;
                }
                s.flags = [None; 4];
                s.memory_store();
                Ok(Flow::Next)
            }
            _ if ins & 0xF000 == 0xD000 && ins & 0x0F00 != 0x0E00 => {
                let target = (at as i32 + 4 + i32::from(ins as u8 as i8) * 2) as u32;
                Ok(match s.condition((ins >> 8) & 15) {
                    Some(true) => Flow::Jump(target),
                    Some(false) => Flow::Next,
                    None => Flow::Branch(target),
                })
            }
            _ if ins & 0xF800 == 0xE000 => Ok(Flow::Jump((at as i32 + 4 + ((i32::from(ins & 0x7FF) << 21) >> 20)) as u32)),
            _ => Err(format!("0x{at:08X}: Thumb instruction 0x{ins:04X} is not decoded")),
        }
    }

    /// `mov pc, rN` / `add pc, rN`: a known target, or the switch table agbcc places after the jump.
    fn jump(&self, at: u32, target: &V, literals: &BTreeMap<u32, u32>, data: &mut BTreeSet<u32>, function: Function) -> Flow {
        if let Some(target) = target.c() {
            return Flow::Jump(target & !1);
        }
        let Some(mut table) = literals.values().copied().filter(|value| *value > at && *value < function.hi && value % 4 == 0).min() else {
            return Flow::Table(Vec::new());
        };
        let mut first_label = function.hi;
        let mut targets = Vec::new();
        while table < first_label && table + 4 <= function.hi {
            let Ok(bytes) = self.rom.code_bytes(table, 4) else { break };
            let label = le32(bytes, 0);
            if label < function.entry || label >= function.hi || label & 1 != 0 {
                break;
            }
            data.insert(table);
            first_label = first_label.min(label);
            targets.push(label);
            table += 4;
        }
        targets.sort();
        targets.dedup();
        Flow::Table(targets)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn symbolic_ram_value_evaluates_after_its_arithmetic() {
        let loaded = V::G(Rc::new(Sym { address: 0x0202_166A, size: 2, signed: false, ops: Vec::new() }));
        let tile = loaded.add(&V::C(2)).op(Op::Lsl(16)).op(Op::Lsr(16));
        assert_eq!(tile.eval(&|address, size| (address == 0x0202_166A && size == 2).then_some(0x3E6)), Some(0x3E8));
        assert_eq!(tile.eval(&|_, _| None), None);
        assert_eq!(V::C(5).sub(&V::C(7)), V::C(5u32.wrapping_sub(7)));
        assert_eq!(V::Top.add(&V::C(1)), V::Top);
    }

    #[test]
    fn join_keeps_only_agreeing_values() {
        let mut a = State::entry(&[V::C(1), V::C(2), V::Top, V::Top, V::C(9), V::Top, V::Top, V::Top, V::Top, V::Top, V::Top, V::Top]);
        let b = State::entry(&[V::C(1), V::C(3), V::Top, V::Top, V::C(9), V::Top, V::Top, V::Top, V::Top, V::Top, V::Top, V::Top]);
        assert!(a.join(&b));
        assert_eq!(a.r[0], V::C(1));
        assert_eq!(a.r[1], V::Top);
        assert_eq!(a.slot(0), V::C(9));
    }

    #[test]
    fn conditions_follow_the_flags() {
        let mut state = State::entry(&Default::default());
        state.flags_sub(&V::C(75), &V::C(75));
        assert_eq!(state.condition(0x0), Some(true));
        assert_eq!(state.condition(0x1), Some(false));
        state.flags_sub(&V::C(3), &V::C(22));
        assert_eq!(state.condition(0x8), Some(false));
        assert_eq!(state.condition(0x9), Some(true));
        state.flags_sub(&V::Top, &V::C(1));
        assert_eq!(state.condition(0x0), None);
    }
}
