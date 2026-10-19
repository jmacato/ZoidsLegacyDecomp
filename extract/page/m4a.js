/* M4A command, voice, envelope, and PCM rules follow src/audio in this repository. */
(function(scope) {
  "use strict";
  function engineModule() {
    const BASE=0x08000000, FRAME_RATE=16777216/280896, ON=0xc7;
    const s8=value=>(value<<24)>>24;
    const highMultiply=(a,b)=>{
      a>>>=0;b>>>=0;
      const lo=(a&65535)*b,hi=(a>>>16)*b;
      return (Math.floor(hi/65536)+Math.floor(((hi%65536)*65536+lo)/4294967296))>>>0;
    };
    // Track and channel bytes retain native offsets for routine comparisons.
    class State {
      constructor(size=64){this.b=new Uint8Array(size);this.view=new DataView(this.b.buffer);this.owner=null;this.channels=[];}
      u32(at){return this.view.getUint32(at,true);}
      put(at,value){this.view.setUint32(at,value>>>0,true);}
    }
    class Engine {
      constructor(rom,id,{loop=true,repeat=true,mode=5,channels=8}={}){
        if(!(rom instanceof Uint8Array))rom=new Uint8Array(rom);
        this.rom=rom;this.view=new DataView(rom.buffer,rom.byteOffset,rom.byteLength);
        if(!Number.isInteger(mode)||mode<1||mode>12||!Number.isInteger(channels)||channels<1||channels>12)throw Error("Invalid M4A sound mode.");
        this.mode=mode;this.maxChannels=channels;this.loop=loop;this.repeat=repeat;this.muted=new Set();
        this.frameSamples=this.u16(0x6a32e4+(mode-1)*2);
        this.frequency=Math.floor((0x91d1b*this.frameSamples+5000)/10000);
        this.sampleStep=(Math.floor(0x1000000/this.frequency)+1)>>>1;
        this.sampleRate=this.frameSamples*FRAME_RATE;this.period=Math.floor(0x630/this.frameSamples);
        this.load(id);
      }
      check(at,size=1){if(!Number.isSafeInteger(at)||at<0||at+size>this.rom.length)throw Error(`M4A ROM read outside its bounds at ${at.toString(16)}.`);}
      u8(at){this.check(at);return this.rom[at];}
      u16(at){this.check(at,2);return this.view.getUint16(at,true);}
      u32(at){this.check(at,4);return this.view.getUint32(at,true);}
      pointer(at){const value=this.u32(at)-BASE;this.check(value);return value;}
      load(id){
        if(!Number.isInteger(id)||id<0||id>=134)throw Error("Choose a song from 0 through 133.");
        const selector=0x6a46c4+id*8;
        this.id=id;this.header=this.pointer(selector);this.priority=this.u8(this.header+2);this.reverb=this.u8(this.header+3)&127;
        this.playerIndex=this.u16(selector+4);if(this.playerIndex>=4)throw Error("Invalid M4A player selector.");
        this.trackCapacity=Math.min(16,this.u8(0x6a4694+this.playerIndex*12+8));
        this.declaredTrackCount=this.u8(this.header);if(this.declaredTrackCount>16)throw Error("An M4A song has too many tracks.");
        const count=Math.min(this.declaredTrackCount,this.trackCapacity);
        this.bank=count?this.pointer(this.header+4):null;
        this.tracks=Array.from({length:count},(_,index)=>{
          const t=new State(80);t.index=index;t.b[0]=0xc0;t.pc=this.pointer(this.header+8+index*4);t.stack=[];t.loops=0;t.voice=null;return t;
        });
        this.loopTargets=this.tracks.map(()=>1);
        this.pcm=Array.from({length:this.maxChannels},()=>new State());
        this.psg=Array.from({length:4},(_,i)=>{const c=new State();c.b[1]=i+1;c.b[28]=0x11<<i;c.phase=0;c.lfsr=0x7fff;c.lengthLeft=0;return c;});
        this.memory=new Uint8Array(256);this.registers=new Uint8Array(256);
        this.registers[0x20]=0x77;this.registers[0x24]=0x8f;this.registers[0x29]=0x40;
        for(const at of [3,9,25])this.registers[at]=8;
        for(const at of [5,13,29])this.registers[at]=0x80;
        this.tempo=150;this.tempoScale=256;this.tempoInterval=150;this.tempoCounter=0;
        this.clock=0;this.status=0;this.frames=0;this.psgEnvelopeFrame=0;
        this.ring=new Uint8Array(0x630);this.bufferIndex=0;this.finished=false;this.tailFrames=0;this.onceStopped=false;
      }
      pcmFrequency(wave,key,fine){
        key&=255;fine&=255;if(key>178){key=178;fine=255;}
        const a=this.u8(0x6a3200+key),b=this.u8(0x6a3201+key);
        const first=this.u32(0x6a32b4+(a&15)*4)>>>(a>>>4),next=this.u32(0x6a32b4+(b&15)*4)>>>(b>>>4);
        const ratio=(first+Math.floor(((next-first)>>>0)*fine/256))>>>0;
        return highMultiply(this.u32(wave+4),ratio);
      }
      psgFrequency(channel,key,fine){
        key&=255;fine&=255;
        if(channel===4)return this.u8(0x6a3398+Math.max(0,Math.min(59,key-21)));
        let index=key-36;if(index<0){index=0;fine=0;}else if(index>130){index=130;fine=255;}
        const a=this.u8(0x6a32fc+index),b=this.u8(0x6a32fd+index);
        const curve=code=>(this.u16(0x6a3380+(code&15)*2)<<16)>>(16+(code>>>4));
        const first=curve(a),next=curve(b);
        return (2048+first+((next-first)*fine>>8))>>>0;
      }
      resetModulation(t){t.b[22]=0;t.b[26]=0;t.b[0]|=t.b[24]===0?12:3;}
      setLoop(value){
        value=!!value;
        if(this.loop&&!value)this.loopTargets=this.tracks.map(track=>track.loops+1);
        this.loop=value;
      }
      refresh(t){
        const b=t.b;
        if(b[0]&1){
          let volume=b[19]*b[18]>>>5;
          if(b[24]===1)volume=(s8(b[22])+128)*volume>>>7;
          let pan=s8(b[20])*2+s8(b[21]);if(b[24]===2)pan+=s8(b[22]);pan=Math.max(-128,Math.min(127,pan));
          b[16]=(pan+128)*volume>>>8;b[17]=(127-pan)*volume>>>8;
        }
        if(b[0]&4){
          let pitch=((s8(b[14])*b[15]+s8(b[12]))<<2)+(s8(b[10])<<8)+(s8(b[11])<<8)+b[13];
          if(b[24]===0)pitch+=s8(b[22])<<4;
          b[8]=pitch>>8;b[9]=pitch;
        }
        b[0]&=0xfa;
      }
      channelVolume(c,t){
        const b=c.b,pan=s8(b[20]),velocity=b[18];
        b[2]=Math.min(255,((128+pan)*velocity*t.b[16])>>14);
        b[3]=Math.min(255,((127-pan)*velocity*t.b[17])>>14);
      }
      channelPitch(c,t){
        const key=Math.max(0,c.b[8]+s8(t.b[8])),channel=c.b[1]&7;
        c.put(32,channel?this.psgFrequency(channel,key,t.b[9]):this.pcmFrequency(c.u32(36)-BASE,key,t.b[9]));
      }
      unlink(c){if(c.owner){const list=c.owner.channels,index=list.indexOf(c);if(index>=0)list.splice(index,1);}c.owner=null;}
      endTrack(t){for(const c of [...t.channels]){if(c.b[0]&ON)c.b[0]|=0x40;this.unlink(c);}t.b[0]=0;}
      note(t,index){
        const b=t.b;b[4]=this.u8(0x6a33e4+index);
        if(this.u8(t.pc)<128){b[5]=this.u8(t.pc++);if(this.u8(t.pc)<128){b[6]=this.u8(t.pc++);if(this.u8(t.pc)<128)b[4]+=this.u8(t.pc++);}}
        let tone=b.subarray(36,48),key=b[5],rhythmPan=0;
        const outer=tone[0];
        if(outer&0xc0){
          const v=new DataView(tone.buffer,tone.byteOffset,12),mapped=outer&0x40?this.u8(v.getUint32(8,true)-BASE+key):key;
          const at=v.getUint32(4,true)-BASE+mapped*12;this.check(at,12);tone=this.rom.subarray(at,at+12);
          if(tone[0]&0xc0)return;
          if(outer&0x80){if(tone[3]&0x80)rhythmPan=(tone[3]-192)*2;key=tone[1];}
        }
        const type=tone[0]&7,priority=Math.min(255,this.priority+b[29]);let c=null;
        if(type){
          c=this.psg[type-1];if(!c)throw Error("Unsupported M4A PSG channel.");
          if((c.b[0]&ON)&&!(c.b[0]&0x40)&&(c.b[19]>priority||(c.b[19]===priority&&(c.owner?.index??-1)<t.index)))return;
        }else{
          let best=null,bestPriority=priority,bestTrack=t.index,stopping=false;
          for(const candidate of this.pcm){
            const cb=candidate.b;if(!(cb[0]&ON)){c=candidate;break;}
            if(cb[0]&0x40){if(!stopping){stopping=true;bestPriority=cb[19];bestTrack=candidate.owner?.index??-1;best=candidate;continue;}}
            else if(stopping)continue;
            const owner=candidate.owner?.index??-1;
            if(cb[19]<bestPriority){bestPriority=cb[19];bestTrack=owner;}
            else if(cb[19]>bestPriority)continue;
            else if(owner>bestTrack)bestTrack=owner;else if(owner<bestTrack)continue;
            best=candidate;
          }
          c ||= best;if(!c)return;
        }
        this.unlink(c);c.owner=t;c.trackIndex=t.index;t.channels.unshift(c);
        b[28]=b[27];if(b[27])this.resetModulation(t);this.refresh(t);
        c.b.set(b.subarray(4,8),16);c.b[19]=priority;c.b[8]=key;c.b[20]=rhythmPan;c.b[1]=tone[0];
        c.b.set(tone.subarray(8,12),4);c.b.set(b.subarray(30,32),12);
        c.put(36,new DataView(tone.buffer,tone.byteOffset,12).getUint32(4,true));
        this.channelVolume(c,t);this.channelPitch(c,t);
        if(type){c.b[30]=tone[2];c.b[31]=(tone[3]&0x80)||!(tone[3]&0x70)?8:tone[3];}
        c.b[0]=0x80;b[0]&=0xf0;
      }
      command(t,opcode,at){
        const b=t.b,take=()=>this.u8(t.pc++),branch=()=>{const target=this.pointer(t.pc);t.pc+=4;return target;};
        if(opcode<=0xb0){if(opcode<0x80)throw Error("Invalid M4A running status.");b[1]=this.u8(0x6a33e4+opcode-0x80);return;}
        if(opcode>=0xcf){this.note(t,opcode-0xcf);return;}
        if([0xb1,0xb6,0xb7,0xb8,0xc6,0xc7,0xc9,0xca,0xcb].includes(opcode)){this.endTrack(t);return;}
        switch(opcode){
          case 0xb2:{const target=branch();if(target<=at&&!t.stack.length)t.loops++;t.pc=target;break;}
          case 0xb3:if(t.stack.length>=3){this.endTrack(t);break;}else{const target=branch();t.stack.push(t.pc);b[2]=t.stack.length;t.pc=target;break;}
          case 0xb4:if(t.stack.length){t.pc=t.stack.pop();b[2]=t.stack.length;}break;
          case 0xb5:{const limit=take(),target=branch();if(limit===0)t.pc=target;else{const next=b[3]+1;if(next<limit){b[3]=next;t.pc=target;}else b[3]=0;}break;}
          case 0xb9:{
            const op=take(),index=take(),operand=take(),current=this.memory[index],other=op>=12?this.memory[operand]:operand;
            if(op===0)this.memory[index]=operand;else if(op===1)this.memory[index]+=operand;else if(op===2)this.memory[index]-=operand;
            else if(op===3)this.memory[index]=this.memory[operand];else if(op===4)this.memory[index]+=this.memory[operand];else if(op===5)this.memory[index]-=this.memory[operand];
            else if(op<=17){const target=branch(),conditions=[current===other,current!==other,current>other,current>=other,current<=other,current<other];if(conditions[(op-6)%6])t.pc=target;}
            break;
          }
          case 0xba:b[29]=take();break;
          case 0xbb:this.tempo=take()*2;this.tempoInterval=this.tempo*this.tempoScale>>>8;break;
          case 0xbc:b[10]=take();b[0]|=12;break;
          case 0xbd:{const voice=take(),offset=this.bank+voice*12;this.check(offset,12);b.set(this.rom.subarray(offset,offset+12),36);t.voice=voice;break;}
          case 0xbe:b[18]=take();b[0]|=3;break;
          case 0xbf:b[20]=take()-64;b[0]|=3;break;
          case 0xc0:b[14]=take()-64;b[0]|=12;break;
          case 0xc1:b[15]=take();b[0]|=12;break;
          case 0xc2:b[25]=take();if(!b[25])this.resetModulation(t);break;
          case 0xc3:b[27]=take();break;
          case 0xc4:b[23]=take();if(!b[23])this.resetModulation(t);break;
          case 0xc5:{const type=take();if(type!==b[24]){b[24]=type;b[0]|=15;}break;}
          case 0xc8:b[12]=take()-64;b[0]|=12;break;
          case 0xcc:{const register=take();this.registers[register]=take();break;}
          case 0xcd:{const selector=take(),offsets={2:36,4:44,5:45,6:46,7:47,8:30,9:31,10:38,11:39};
            if(selector===0||selector===3)this.endTrack(t);
            else if(selector===1){const wave=this.u32(t.pc);t.pc+=4;new DataView(b.buffer).setUint32(40,wave,true);}
            else if(selector in offsets)b[offsets[selector]]=take();else throw Error("Unsupported extended M4A command.");break;}
          case 0xce:{if(this.u8(t.pc)<128)b[5]=take();for(const c of t.channels)if((c.b[0]&0x83)&&!(c.b[0]&0x40)&&c.b[17]===b[5]){c.b[0]|=0x40;break;}break;}
          default:throw Error(`Unsupported M4A command 0x${opcode.toString(16)}.`);
        }
      }
      sequenceFrame(){
        if(this.status&0x80000000)return;
        let counter=this.tempoCounter+this.tempoInterval;
        for(let ticks=0;(this.tempoCounter=counter&65535)>=150;counter=this.tempoCounter-150){
          if(++ticks>4096)throw Error("M4A tempo exceeds its tick limit.");
          let active=0;
          for(const t of this.tracks){
            const b=t.b;if(!(b[0]&128))continue;active|=1<<t.index;
            for(const c of [...t.channels]){
              if(!(c.b[0]&ON)){this.unlink(c);continue;}
              if(c.b[16]&&!--c.b[16])c.b[0]|=0x40;
            }
            if(b[0]&64){b.fill(0,0,64);b[0]=128;b[15]=2;b[19]=64;b[25]=22;b[36]=1;}
            let commands=0;
            while(b[1]===0&&b[0]){
              if(++commands>100000)throw Error("An M4A track loops without a wait.");
              const at=t.pc;let opcode=this.u8(t.pc);
              if(opcode>=128){t.pc++;if(opcode>=0xbd)b[7]=opcode;}else opcode=b[7];
              this.command(t,opcode,at);
            }
            if(!b[0])continue;
            b[1]--;
            if(b[25]&&b[23]){
              if(b[28])b[28]--;
              else{
                const phase=b[26]+b[25];b[26]=phase;
                const wave=s8(phase-64)<0?s8(phase):128-phase,modulation=b[23]*wave>>6;
                if(((b[22]^modulation)&255)!==0){b[22]=modulation;b[0]|=b[24]===0?12:3;}
              }
            }
          }
          this.clock++;
          if(!active){this.status=0x80000000;return;}
          this.status=active;
          if(!this.loop&&!this.onceStopped&&this.tracks.every(t=>!(t.b[0]&128)||t.loops>=this.loopTargets[t.index])){
            this.onceStopped=true;for(const t of this.tracks)this.endTrack(t);
          }
        }
        for(const t of this.tracks){
          const b=t.b;if(!(b[0]&128)||!(b[0]&15))continue;this.refresh(t);
          for(const c of [...t.channels]){
            if(!(c.b[0]&ON)){this.unlink(c);continue;}
            if(b[0]&3){this.channelVolume(c,t);if(c.b[1]&7)c.b[29]|=1;}
            if(b[0]&12){this.channelPitch(c,t);if(c.b[1]&7)c.b[29]|=2;}
          }
          b[0]&=0xf0;
        }
      }
      pcmEnvelope(c){
        const b=c.b;let flags=b[0],volume=b[9];if(!(flags&ON))return false;
        if(flags&128){
          if(flags&64){b[0]=0;return false;}
          flags=3;c.put(40,c.u32(36)+16);c.put(24,this.u32(c.u32(36)-BASE+12));c.put(28,0);volume=0;
          if(this.u8(c.u32(36)-BASE+3)&0xc0)flags|=16;
          volume+=b[4];if(volume>=255){volume=255;flags--;}
        }else if(flags&4){if(b[13]--<=1){b[0]=0;return false;}}
        else if(flags&64){
          volume=volume*b[7]>>>8;
          if(volume<=b[12]){volume=b[12];if(!volume){b[0]=0;return false;}flags|=4;}
        }else if((flags&3)===2){
          volume=volume*b[5]>>>8;if(volume<=b[6]){volume=b[6];if(!volume){volume=b[12];if(!volume){b[0]=0;return false;}flags|=4;}else flags--;}
        }else if((flags&3)===3){volume+=b[4];if(volume>=255){volume=255;flags--;}}
        b[0]=flags;b[9]=volume;b[10]=((volume*16>>>4)*(b[2]+b[3]))>>>9;return true;
      }
      mixPCM(){
        const n=this.frameSamples,start=this.bufferIndex*n,next=(this.bufferIndex+1)%this.period*n,out=new Uint8Array(n);
        if(this.reverb)for(let i=0;i<n;i++){let value=(s8(this.ring[start+i])+s8(this.ring[next+i]))*this.reverb>>8;if(value&128)value++;out[i]=value;}
        const words=new DataView(out.buffer);
        for(const c of this.pcm){
          if(!this.pcmEnvelope(c))continue;
          const b=c.b,wave=c.u32(36)-BASE,count=this.u32(wave+12),loop=this.u32(wave+8),loopLength=count-loop;
          let source=c.u32(40)-BASE,remaining=c.u32(24),phase=c.u32(28),ended=false;
          const increment=Math.imul(this.sampleStep,c.u32(32))>>>0,fixed=!!(b[1]&8),gain=this.muted.has(c.trackIndex)?0:b[10];
          // The native mixer accumulates four signed samples in one rotating word.
          for(let group=0;group<n&&!ended;group+=4){
            let word=words.getUint32(group,true),used=0;
            for(let j=0;j<4&&group+j<n;j++){
              let sample=s8(this.u8(source));
              if(!fixed)sample+=(phase*(s8(this.u8(source+1))-sample))>>23;
              const product=Math.imul(gain<<16,sample);
              word=(((word>>>8)|(word<<24))+(product&~0xff0000))>>>0;used++;
              let advance=1;
              if(!fixed){phase=(phase+increment)>>>0;advance=phase>>>23;phase&=~0x3f800000;}
              source+=advance;remaining-=advance;
              if(remaining<=0){
                if(!(b[0]&16)){ended=true;b[0]=0;break;}
                if(loopLength<=0)throw Error("An M4A sample has an empty loop.");
                const overshoot=(-remaining)%loopLength;source=wave+16+loop+overshoot;remaining=loopLength-overshoot;
              }
            }
            if(used<4){const rotate=(4-used)*8;word=(word>>>rotate)|(word<<(32-rotate));}
            words.setUint32(group,word>>>0,true);
          }
          if(!ended){c.put(40,source+BASE);c.put(24,remaining);c.put(28,phase);}
        }
        this.ring.set(out,start);this.bufferIndex=(this.bufferIndex+1)%this.period;return out;
      }
      psgVolume(c){
        const b=c.b,right=b[2],left=b[3];let route;
        if(right>=left&&(right>>>1)>=left)route=15;else if(left>right&&(left>>>1)>=right)route=240;else route=255;
        let amplitude=(right+left)>>>4;if(route!==255)amplitude=Math.min(15,amplitude);
        b[10]=amplitude;b[25]=(b[6]*amplitude+15)>>>4;b[27]=route&b[28];
      }
      psgFrame(){
        this.psgEnvelopeFrame=this.psgEnvelopeFrame?this.psgEnvelopeFrame-1:14;
        for(const c of this.psg){
          const b=c.b;if(!(b[0]&ON))continue;
          const channel=b[1]&7;let frame=this.psgEnvelopeFrame,complete=false;
          const echo=()=>{b[9]=(b[10]*b[12]+255)>>>8;if(b[9]){b[0]|=4;b[29]|=1;}else b[0]=0;complete=true;};
          const sustain=()=>{if(!b[6]){b[0]&=~3;echo();}else{b[0]--;b[29]|=1;b[9]=b[25];b[11]=7;}};
          const decay=()=>{b[0]--;b[11]=b[5];if(b[11]){b[29]|=1;b[9]=b[10];}else sustain();};
          if(b[0]&128){
            if(b[0]&64){b[0]=0;b[29]=0;continue;}
            b[0]=3;b[29]=3;this.psgVolume(c);c.phase=0;c.lfsr=0x7fff;
            c.lengthLeft=b[30]?(channel===3?256:64)-b[30]:Infinity;
            if(channel===3){c.put(40,c.u32(36));b[26]=b[30]?0xc0:0x80;}else b[26]=b[30]?0x40:0;
            b[11]=b[4];if(s8(b[4]))b[9]=0;else decay();
          }else if(b[0]&4){b[13]--;if(s8(b[13])<=0)b[0]=0;complete=true;}
          else if((b[0]&64)&&(b[0]&3)){b[0]&=~3;b[11]=b[7];if(s8(b[7]))b[29]|=1;else echo();}
          else {
            if(!b[11]){
              if(channel===3)b[29]|=1;this.psgVolume(c);
              const stage=b[0]&3;
              if(stage===0){b[9]--;if(s8(b[9])<=0)echo();else b[11]=b[7];}
              else if(stage===1){b[9]=b[25];b[11]=7;}
              else if(stage===2){b[9]--;if(s8(b[9])<=s8(b[25]))sustain();else b[11]=b[5];}
              else{b[9]++;if(b[9]>=b[10])decay();else b[11]=b[4];}
            }
          }
          if(!complete){
            b[11]--;
            if(frame===0){
              frame=-1;
              if(!b[11]){
                if(channel===3)b[29]|=1;this.psgVolume(c);
                const stage=b[0]&3;
                if(stage===0){b[9]--;if(s8(b[9])<=0)echo();else b[11]=b[7];}
                else if(stage===1){b[9]=b[25];b[11]=7;}
                else if(stage===2){b[9]--;if(s8(b[9])<=s8(b[25]))sustain();else b[11]=b[5];}
                else{b[9]++;if(b[9]>=b[10])decay();else b[11]=b[4];}
              }
              if(!complete)b[11]--;
            }
          }
          if(!b[0]){b[29]=0;continue;}
          if((b[29]&2)&&channel<4&&(b[1]&8))c.put(32,(c.u32(32)+1)&0x7fe);
          if(b[29]&2)b[26]=(b[26]&0xc0)+(c.u32(32)>>>8);
          if(channel===3&&(b[29]&1)&&(b[26]&128))b[26]&=127;
          b[29]=0;
        }
      }
      psgSample(c){
        const b=c.b;if(!(b[0]&ON))return 0;
        const channel=b[1]&7,frequency=c.u32(32),wave=c.u32(36);let value=0;
        if(channel===4){
          const ratio=frequency&7,shift=frequency>>>4,step=524288/(ratio||0.5)/(2**(shift+1))/this.sampleRate;
          c.phase+=step;while(c.phase>=1){const bit=(c.lfsr^(c.lfsr>>>1))&1;c.lfsr=(c.lfsr>>>1)|(bit<<14);if(wave&1)c.lfsr=(c.lfsr&~64)|(bit<<6);c.phase--;}
          value=c.lfsr&1?-1:1;
        }else{
          const hz=(channel===3?65536:131072)/Math.max(1,2048-(frequency&2047));
          c.phase=(c.phase+hz/this.sampleRate)%1;
          if(channel===3){const index=Math.floor(c.phase*32),packed=this.u8(wave-BASE+(index>>>1));value=(((packed>>((1-(index&1))*4))&15)-7.5)/7.5;}
          else{const duty=[0.125,0.25,0.5,0.75][wave&3];value=c.phase<duty?1:-1;}
        }
        if(c.lengthLeft!==Infinity){c.lengthLeft-=256/this.sampleRate;if(c.lengthLeft<=0)return 0;}
        if(channel===3){
          const setting=this.u8(0x6a33d4+b[9]),gain=setting&128?0.75:[0,1,0.5,0.25][(setting>>>5)&3];
          return value*gain;
        }
        return value*b[9]/15;
      }
      frame(){
        if(this.finished)return {left:new Float32Array(this.frameSamples),right:new Float32Array(this.frameSamples),pcm:new Uint8Array(this.frameSamples)};
        this.sequenceFrame();this.psgFrame();const pcm=this.mixPCM(),left=new Float32Array(pcm.length),right=new Float32Array(pcm.length);
        for(let i=0;i<pcm.length;i++){
          let l=s8(pcm[i])/128,r=l;
          for(const c of this.psg){const sample=this.psgSample(c)*0.25;if(this.muted.has(c.trackIndex))continue;if(c.b[27]&0xf0)l+=sample;if(c.b[27]&15)r+=sample;}
          left[i]=Math.max(-1,Math.min(1,l));right[i]=Math.max(-1,Math.min(1,r));
        }
        this.frames++;
        if(this.status&0x80000000){
          this.tailFrames++;const active=[...this.pcm,...this.psg].some(c=>c.b[0]&ON),echo=this.ring.some(value=>value!==0);
          if((!active&&!echo)||this.tailFrames>Math.ceil(FRAME_RATE*3)){
            if(this.loop&&this.repeat&&this.tracks.length){const muted=this.muted;this.load(this.id);this.muted=muted;}else this.finished=true;
          }
        }
        return {left,right,pcm};
      }
      render(frames=8){
        if(!Number.isInteger(frames)||frames<1||frames>120)throw Error("Invalid M4A render block.");
        const left=new Float32Array(frames*this.frameSamples),right=new Float32Array(left.length);let count=0;
        for(let i=0;i<frames&&!this.finished;i++){const block=this.frame();left.set(block.left,count);right.set(block.right,count);count+=block.left.length;}
        return {left:left.subarray(0,count),right:right.subarray(0,count),sampleRate:this.sampleRate,finished:this.finished,state:this.info()};
      }
      info(){return {song:this.id,player:this.playerIndex,track_capacity:this.trackCapacity,stored_tracks:this.declaredTrackCount,clock:this.clock,tempo:this.tempo,frames:this.frames,finished:this.finished,tracks:this.tracks.map(t=>({id:t.index,voice:t.voice,key:t.b[5],volume:t.b[18],pan:s8(t.b[20]),active:!!(t.b[0]&128),muted:this.muted.has(t.index),channels:t.channels.filter(c=>c.b[0]&ON).length,offset:t.pc}))};}
    }
    return {Engine,FRAME_RATE,highMultiply};
  }
  const api=engineModule();
  async function renderWav(rom,id,{maxSeconds=600,onprogress=()=>{}}={}){
    if(!Number.isFinite(maxSeconds)||maxSeconds<=0||maxSeconds>3600)throw Error("Invalid audio export duration limit.");
    class ExportEngine extends api.Engine{
      check(at,size=1){super.check(at,size);this.romReads??=new Uint8Array(this.rom.length);this.romReads.fill(1,at,at+size);}
    }
    const engine=new ExportEngine(rom,id,{loop:false,repeat:false}),chunks=[];
    const limit=Math.ceil(maxSeconds*api.FRAME_RATE);let length=0;
    while(!engine.finished){
      const block=engine.render(16),bytes=new Uint8Array(block.left.length*4),view=new DataView(bytes.buffer);
      for(let index=0;index<block.left.length;index++){
        for(let channel=0;channel<2;channel++){
          const value=Math.max(-1,Math.min(1,(channel?block.right:block.left)[index]));
          view.setInt16(index*4+channel*2,Math.round(value*(value<0?32768:32767)),true);
        }
      }
      chunks.push(bytes);length+=bytes.length;onprogress(engine.frames/api.FRAME_RATE);
      if(!engine.finished&&engine.frames>=limit)throw Error("The song exceeds the audio export duration limit.");
      await new Promise(resolve=>setTimeout(resolve,0));
    }
    const bytes=new Uint8Array(44+length),view=new DataView(bytes.buffer),rate=Math.round(engine.sampleRate);
    for(const [at,text]of [[0,"RIFF"],[8,"WAVE"],[12,"fmt "],[36,"data"]])
      for(let index=0;index<text.length;index++)bytes[at+index]=text.charCodeAt(index);
    view.setUint32(4,36+length,true);view.setUint32(16,16,true);view.setUint16(20,1,true);
    view.setUint16(22,2,true);view.setUint32(24,rate,true);view.setUint32(28,rate*4,true);
    view.setUint16(32,4,true);view.setUint16(34,16,true);view.setUint32(40,length,true);
    let offset=44;for(const chunk of chunks){bytes.set(chunk,offset);offset+=chunk.length;}
    const sources=[];let first=null;
    for(let at=0;at<=engine.romReads.length;at++){
      if(engine.romReads[at]){if(first===null)first=at;}
      else if(first!==null){sources.push([first,at]);first=null;}
    }
    return {bytes,sources,sample_rate:rate,source_sample_rate:engine.sampleRate,frames:engine.frames,
      scope:"One sequence pass and its release tail, rendered by the JavaScript player. PSG synthesis, output filters, and hardware timing remain unverified."};
  }
  function workerMain(){
    let engine=null;
    self.onmessage=event=>{
      try{
        const message=event.data;
        if(message.type==="init"){engine=new self.ZoidsM4A.Engine(new Uint8Array(message.rom),message.song,message.options);self.postMessage({type:"ready",sampleRate:engine.sampleRate,state:engine.info()});}
        else if(message.type==="render"){
          if(!engine)throw Error("No M4A song loaded.");const block=engine.render(message.frames);self.postMessage({type:"audio",...block},[block.left.buffer,block.right.buffer]);
        }else if(message.type==="mute")engine.muted=new Set(message.tracks);
        else if(message.type==="loop")engine.setLoop(message.value);
      }catch(error){self.postMessage({type:"error",message:error.message});}
    };
  }
  const workerSource=`self.ZoidsM4A=(${engineModule.toString()})();(${workerMain.toString()})();`;
  class Player {
    constructor({onchange=()=>{},onerror=()=>{}}={}){this.onchange=onchange;this.onerror=onerror;this.context=null;this.worker=null;this.sources=new Set();this.volume=0.65;this.loop=true;this.status="stopped";this.generation=0;this.muted=new Set();this.state=null;}
    elapsed(){return this.context&&this.hasAudio&&this.status!=="stopped"?Math.max(0,this.context.currentTime-this.startedAt):0;}
    notify(){this.onchange({status:this.status,elapsed:this.elapsed(),state:this.state,volume:this.volume,loop:this.loop});}
    async play(rom,song,{loop=this.loop}={}){
      this.stop();const generation=this.generation;
      const AudioContext=scope.AudioContext||scope.webkitAudioContext;if(!AudioContext)throw Error("This browser does not support Web Audio.");
      if(!scope.Worker)throw Error("This browser does not support audio workers.");
      if(!this.context){this.context=new AudioContext();this.gain=this.context.createGain();this.gain.connect(this.context.destination);}
      this.gain.gain.value=this.volume;await this.context.resume();if(generation!==this.generation)return;
      this.status="loading";this.state=null;this.hasAudio=false;if(this.song!==song){this.muted.clear();this.song=song;}this.notify();
      const url=URL.createObjectURL(new Blob([workerSource],{type:"text/javascript"}));
      this.workerURL=url;
      try{this.worker=new scope.Worker(url);}catch(error){URL.revokeObjectURL(url);this.workerURL=null;throw error;}
      this.queuedUntil=this.context.currentTime+0.06;this.startedAt=this.queuedUntil;this.pending=false;this.ended=false;
      this.worker.onmessage=event=>{
        if(generation!==this.generation)return;
        const message=event.data;
        if(message.type==="error"){this.fail(Error(message.message));return;}
        if(message.type==="ready"){URL.revokeObjectURL(this.workerURL);this.workerURL=null;this.status="playing";this.state=message.state;this.worker.postMessage({type:"mute",tracks:[...this.muted]});this.pump();this.timer=setInterval(()=>{this.pump();this.notify();},50);}
        else if(message.type==="audio"){
          this.pending=false;this.state=message.state;this.ended=message.finished;
          if(message.left.length){
            const buffer=this.context.createBuffer(2,message.left.length,message.sampleRate);buffer.copyToChannel(message.left,0);buffer.copyToChannel(message.right,1);
            const source=this.context.createBufferSource();source.buffer=buffer;source.connect(this.gain);
            const start=Math.max(this.queuedUntil,this.context.currentTime+0.02);this.queuedUntil=start+buffer.duration;
            if(!this.hasAudio){this.startedAt=start;this.hasAudio=true;}
            this.sources.add(source);source.onended=()=>{source.disconnect();this.sources.delete(source);};source.start(start);
          }
          this.pump();
        }
        this.notify();
      };
      this.worker.onerror=event=>{if(generation===this.generation)this.fail(Error(event.message||"The M4A audio worker failed."));};
      const bytes=new Uint8Array(rom);this.worker.postMessage({type:"init",rom:bytes.buffer,song,options:{loop}},[bytes.buffer]);
    }
    pump(){
      if(this.status!=="playing")return;
      if(this.ended){if(this.context.currentTime>=this.queuedUntil){this.stop();this.notify();}return;}
      if(!this.pending&&this.queuedUntil<this.context.currentTime+0.5){this.pending=true;this.worker.postMessage({type:"render",frames:8});}
    }
    async pause(){if(this.status!=="playing")return;const generation=this.generation;await this.context.suspend();if(generation!==this.generation)return;this.status="paused";this.notify();}
    async resume(){if(this.status!=="paused")return;const generation=this.generation;await this.context.resume();if(generation!==this.generation)return;this.status="playing";this.pump();this.notify();}
    setVolume(value){this.volume=Math.max(0,Math.min(1,Number(value)||0));if(this.gain)this.gain.gain.value=this.volume;this.notify();}
    setLoop(value){this.loop=!!value;this.worker?.postMessage({type:"loop",value:this.loop});this.notify();}
    mute(track,value){if(value)this.muted.add(track);else this.muted.delete(track);this.worker?.postMessage({type:"mute",tracks:[...this.muted]});this.notify();}
    stop(){
      this.generation++;clearInterval(this.timer);this.timer=null;this.worker?.terminate();this.worker=null;
      if(this.workerURL){URL.revokeObjectURL(this.workerURL);this.workerURL=null;}
      for(const source of this.sources){source.onended=null;try{source.stop();}catch{/* never started */}source.disconnect();}this.sources.clear();
      this.status="stopped";this.state=null;this.pending=false;this.notify();
    }
    fail(error){this.stop();this.onerror(error);}
    dispose(){this.stop();this.context?.close();this.context=null;}
  }
  api.Player=Player;api.workerSource=workerSource;api.renderWav=renderWav;
  if(typeof module!=="undefined"&&module.exports)module.exports=api;else scope.ZoidsM4A=api;
})(typeof globalThis!=="undefined"?globalThis:this);
