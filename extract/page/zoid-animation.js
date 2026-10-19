(function (scope) {
  "use strict";
  const BODY_PARTS = {
    26:[[0,128,80,0x1298]],
    64:[[0,173,49,0x1298],[0,125,52,0x10d8]],
    65:[[0,144,89,0x1298],[0,124,89,0x10d8]],
    73:[[0,192,64,0x1288]],
    90:[[0,200,96,0x1288]],
    116:[[0,128,128,0x1298],[1,128,128,0x10d8]]
  };
  const SHAPES = new Map([
    ["8,8",[0,0]],["16,16",[0,1]],["32,32",[0,2]],["64,64",[0,3]],
    ["16,8",[1,0]],["32,8",[1,1]],["32,16",[1,2]],["64,32",[1,3]],
    ["8,16",[2,0]],["8,32",[2,1]],["16,32",[2,2]],["32,64",[2,3]]
  ]);
  const signed16 = value => value<<16>>16;
  const requireInteger = (value,low,high,name) => {
    if(!Number.isInteger(value)||value<low||value>high)throw Error(`Invalid Zoid animation ${name}.`);
  };

  class Player {
    constructor(archive,{model,slot,side=0,variant=0,equipment=[0,0,0]}={}) {
      requireInteger(model,1,152,"model");requireInteger(slot,0,13,"slot");
      requireInteger(side,0,1,"side");requireInteger(variant,0,7,"palette");
      if(!Array.isArray(equipment)||equipment.length!==3)throw Error("Zoid animation requires three mount slots.");
      equipment.forEach(item=>requireInteger(item,0,100,"mounted item"));
      equipment.forEach((item,slot)=>{
        if(!item)return;
        const selector=item*2+(slot?1:0),graphics=0x7abc6c+selector*8,definition=0x7ac2bc+selector*8;
        if(![graphics,graphics+4,definition,definition+4].every(at=>archive.u32(at)))throw Error("This mounted item has no stored graphics and sprite definition.");
      });
      this.archive=archive;this.model=model;this.slot=slot;this.side=side;this.variant=variant;this.equipment=equipment.slice();
      this.vram=new Uint8Array(0x18000);this.palette=new Uint8Array(1024);this.oam=new Uint8Array(1024);this.registers=new Uint8Array(0x60);
      this.oamView=new DataView(this.oam.buffer);this.registerView=new DataView(this.registers.buffer);
      this.registerView.setUint16(0,0x1140,true);this.registerView.setUint16(8,0x4086,true);
      this.sprites=[];this.mounts=[];this.bodySprites=[];this.group=null;this.sources=[];this.sourceKeys=new Set();
      this.tick=0;this.state=0;this.ready=1;this.index=0;this.elapsed=0;this.songs=[];
      for(const [address,role]of [[0xcb340,"battle body and mount loader"],[0x9a1f8,"body graphics loader"],
        [0x9a1bc,"palette loader"],[0x9aa64,"mounted graphics loader"],[0xd04a0,"equipment animation start"],
        [0xd0644,"equipment animation update"],[0x94330,"sprite pool initialization"],[0x94374,"sprite table constructor"],
        [0x94564,"sprite animation selection"],[0x94578,"sprite ordering"],[0x946a0,"sprite OAM and timing"],
        [0x95098,"sprite group creation"],[0x95154,"sprite group callbacks"],[0xd22b4,"mirrored sprite coordinates"],
        [0x95208,"transfer queue"],[0x95254,"tilemap transfer queue"],[0x952ac,"queued transfers"],
        [0x922a4,"OAM upload"]])this._code(address,role);
      this._loadBody();this._loadMounts();this._initializeBody();this._draw();this._start();
    }

    _source(start,end,role,transform="identity") {
      const key=`${start}:${end}:${role}`;
      if(!this.sourceKeys.has(key)){this.sourceKeys.add(key);this.sources.push(this.archive.sourceSpan(start,end,role,transform));}
    }

    _pointer(at,role) {this._source(at,at+4,role);return this.archive.pointer(at);}

    _code(address,role) {
      const asset=this.archive.assets.find(item=>item.kind==="code"&&item.start<=address&&item.end>address);
      if(!asset)throw Error("A combined animation routine has no source owner.");
      this._source(asset.start,asset.end,role,"interpreted-native-routine");
    }

    _load(at,target,offset,role) {
      const start=this._pointer(at,`${role} selector`),data=this.archive.lz(start);
      const asset=this.archive.assets.find(item=>item.start===start&&item.details.encoding==="gba-lz77");
      if(!asset)throw Error("A combined animation resource has no source owner.");
      this._source(start,asset.end,role,"gba-lz77");target.set(data,offset);return data;
    }

    _record(at) {
      this._source(at,at+8,"sprite definition selector");
      const record=this.archive.sprite({record:at});
      this._source(record.frame_table,record.frame_table+record.frames.length*4,"sprite frame selectors");
      this._source(record.animation_table,record.animation_table+record.animations.length*4,"sprite animation selectors");
      for(const [table,count]of [[record.frame_table,record.frames.length],[record.animation_table,record.animations.length]])
        this._source(table+count*4,table+(count+1)*4,"parser termination lookahead; not a native sprite operand");
      for(const row of [...record.frames,...record.animations]){
        const asset=this.archive.byID.get(row.asset);this._source(asset.start,asset.end,"sprite frame or animation");
      }
      return record;
    }

    _create(record,animation,x,y,tile_offset,palette_bank,flags) {
      const sprite={record,animation,x:signed16(this.side?256-x:x),y:signed16(y),tile_offset,palette_bank,
        flags:flags|1|(this.side?0x8000:0),address:127-this.sprites.length,step:0,age:0};
      this.sprites.push(sprite);return sprite;
    }

    _loadBody() {
      const table=0x7a5cf0+this.model*12;
      this._load(table,this.vram,0x4000,"body tiles");
      this._load(0x7a641c+this.model*32+this.variant*4,this.palette,0,"body palette");
      // LoadCompressedPalette preserves the existing background color at index zero.
      this.palette[0]=0;this.palette[1]=0;
      this._load(table+4,this.vram,0,"body tilemap");
      if(this.side){
        const source=this.vram.slice(0,1024),view=new DataView(source.buffer),target=new DataView(this.vram.buffer);
        for(let y=0;y<16;y++)for(let x=0;x<32;x++)target.setUint16((y*32+x)*2,view.getUint16((y*32+31-x)*2,true)^0x400,true);
      }
      this.vram.fill(0,0x400,0x1000);
      this._source(table+8,table+12,"body attachment selector");
      if(this.archive.u32(table+8)){
        this._load(table+8,this.vram,0x10000,"body attachment tiles");
        this._load(0x7a8f24+this.model*32+this.variant*4,this.palette,0x200,"body attachment palette");
        if(!BODY_PARTS[this.model])throw Error("An original body callback is unsupported.");
        this._source(0x7a3164+this.model*8,0x7a3164+this.model*8+8,"body callback selectors");
        for(let index=0;index<2;index++){
          const value=this.archive.u32(0x7a3164+this.model*8+index*4);
          if(value)this._code((value-0x08000000)&~1,index?"body update callback":"body initialization callback");
        }
        this.group={phase:[73,90].includes(this.model)?255:0,selector:0};
      }
    }

    _mountX(slot,item) {
      const at=0x7ec38c+this.model*32+slot*4;
      this._source(at,at+2,"selected mount x coordinate");
      let x=this.archive.i16(at);
      if(slot===2){this._source(0x7ac90c+item*2,0x7ac90c+item*2+2,"rear mount correction");x=signed16(x-this.archive.i16(0x7ac90c+item*2));}
      return x;
    }

    _loadMounts() {
      for(let slot=0;slot<3;slot++){
        const item=this.equipment[slot];if(!item){this.mounts.push(null);continue;}
        const id=item*2+(slot?1:0),table=0x7abc6c+id*8;
        this._load(table,this.vram,0x10000+slot*0x1000,"mounted tiles");
        this._load(table+4,this.palette,0x200+slot*32,"mounted palette");
        this._source(0x7ec38c+this.model*32+slot*4,0x7ec38c+this.model*32+slot*4+4,"mount coordinates");
        this._source(0x7ed68c+this.model*3+slot,0x7ed68c+this.model*3+slot+1,"mount priority");
        this.mounts.push(this._create(this._record(0x7ac2bc+id*8),0,this._mountX(slot,item),
          this.archive.i16(0x7ec38c+this.model*32+slot*4+2),slot*128,slot,0x1218|(this.archive.u8(0x7ed68c+this.model*3+slot)<<6)));
      }
    }

    _initializeBody() {
      if(!this.group)return;
      const record=this._record(0x7aa244+this.model*8);
      for(const [animation,x,y,flags]of BODY_PARTS[this.model])this.bodySprites.push(this._create(record,animation,x,y,0,0,flags));
    }

    _setAnimation(sprite,animation) {sprite.animation=animation;sprite.step=0;sprite.age=0;sprite.flags&=~4;}

    _start() {
      if(this.slot<=3){
        if(this.slot<3&&this.mounts[this.slot]){this.mounts[this.slot].flags&=~8;this.state=2;this.ready=0;}
        return;
      }
      this._source(0x7a773c+this.model*40+(this.slot-4)*4,0x7a773c+this.model*40+(this.slot-4)*4+4,"built-in animation selector");
      this.tilePlayer=this.archive.equipmentPlayback(this.model,this.slot,{side:this.side});
      if(this.tilePlayer){
        const asset=this.tilePlayer.asset;this._source(asset.start,asset.end,"built-in tilemap script","gba-lz77");
        this.state=1;this.ready=0;
        if(this.model===64&&this.slot===5){this.group.phase=1;this.group.selector=0;}
        if(this.model===116&&this.slot===6){this.group.phase=1;this.group.selector=1;}
      }else if(this.model===26&&this.slot===5||this.model===64&&[4,6].includes(this.slot)||this.model===65&&this.slot===4){
        this.group.phase=1;this.state=2;this.ready=0;
        if(this.model===64)this.group.selector=this.slot===4?2:1;
      }
    }

    _updateBody() {
      if(!this.group)return;
      if(this.group.phase===1){
        for(let index=0;index<this.bodySprites.length;index++){
          const sprite=this.bodySprites[index];sprite.flags&=~8;
          if(this.model===64)this._setAnimation(sprite,this.group.selector&65535);
          if(this.model===116&&this.group.selector)this._setAnimation(sprite,index+2);
        }
        this.group.phase=2;
      }else if(this.group.phase===2&&this.bodySprites.every(sprite=>sprite.flags&4))this.group.phase=255;
    }

    _moveMounts() {
      const forward=([75,78,120].includes(this.model)&&this.slot===6||[109,110,111].includes(this.model)&&this.slot===5)&&this.index===2;
      const backward=([75,78,120].includes(this.model)&&this.slot===11||[109,110,111].includes(this.model)&&this.slot===10)&&this.index===4;
      if(!forward&&!backward)return;
      const center=[75,78].includes(this.model)?192:this.model===120?168:176;
      for(let slot=0;slot<3;slot++){
        const sprite=this.mounts[slot];if(!sprite)continue;
        const target=forward&&slot?slot^3:slot;
        let x=this._mountX(target,this.equipment[slot]);if(forward)x=signed16(center*2-x);
        sprite.x=signed16(this.side?256-x:x);
        const address=0x7ed68c+this.model*3+target;this._source(address,address+1,"turned mount priority");
        sprite.flags=((sprite.flags^0x8000)&~0xc0)|(this.archive.u8(address)<<6);
      }
    }

    _draw() {
      const active=[];
      for(const sprite of this.sprites.slice().sort((a,b)=>a.address-b.address)){
        if(!(sprite.flags&1)){sprite.flags&=~2;continue;}
        let position=active.length;
        while(position){const previous=active[position-1],flags=sprite.flags,old=previous.flags;let shift;
          if((flags&0xc0)!==(old&0xc0))shift=(flags&0xc0)<(old&0xc0);
          else if((flags&0x300)<(old&0x300))shift=true;
          else shift=Boolean(flags&0x40000)&&(!(old&0x40000)||sprite.y>previous.y);
          if(!shift)break;position--;
        }active.splice(position,0,sprite);
      }
      let index=0;
      for(const sprite of active){
        const animation=sprite.record.animations[sprite.animation],step=animation.steps[sprite.step],pieces=sprite.record.frames[step.frame].pieces;
        const objects=this.archive.objects(pieces,sprite);
        if(objects.length<pieces.length)sprite.flags|=0x800000;else sprite.flags&=~0x800000;
        for(const object of objects){
          if(index>=128)break;
          const [shape,size]=SHAPES.get(`${object.width},${object.height}`);
          let attr0=(object.y&255)|(sprite.flags&0xc00)|(object.piece.tail&0xff00)|(shape<<14);
          let attr1=(object.x&511)|(size<<14);
          if(object.matrix)throw Error("An affine combined-animation piece requires a separate native check.");
          attr1|=object.flips<<12;
          this.oamView.setUint16(index*8,attr0,true);this.oamView.setUint16(index*8+2,attr1,true);
          this.oamView.setUint16(index*8+4,object.tile|(object.palette_bank<<12)|(object.priority<<10),true);index++;
        }
        if(!(sprite.flags&8)){
          sprite.age=(sprite.age+1)&65535;
          if(sprite.age===step.duration_updates){
            if(sprite.step+1<animation.steps.length)sprite.step++;
            else {sprite.flags|=4;const mode=sprite.flags&0x30;
              if(!mode){sprite.flags&=~1;continue;}
              if(mode===0x20)sprite.step=0;
              else if(mode===0x30){this._setAnimation(sprite,0);continue;}
            }sprite.age=0;
          }
        }
      }
      for(;index<128;index++)this.oamView.setUint32(index*8,0x200,true);
    }

    update() {
      this.tick++;this.songs=[];
      if(this.state){
        if(this.slot<3){if(this.mounts[this.slot]?.flags&4){this.state=0;this.ready=1;}}
        else if(this.state===1){
          const before=this.tilePlayer.elapsed,command=this.tilePlayer.script.commands[this.tilePlayer.index];
          const result=this.tilePlayer.update();this.songs=result.songs;
          for(const key of ["state","ready","index","elapsed"])this[key]=this.tilePlayer[key];
          this.vram.set(this.tilePlayer.tilemap);
          if(before===command.duration_or_song&&this.state)this._moveMounts();
        }else if(this.state===2&&(!this.group||this.group.phase===255)){this.state=0;this.ready=1;}
      }
      this._updateBody();this._draw();return this.frame();
    }

    stateRecord() {return {model:this.model,slot:this.slot,state:this.state,ready:this.ready,index:this.index,elapsed:this.elapsed};}
    spriteRecords() {return this.sprites.filter(sprite=>sprite.flags&3).sort((a,b)=>a.address-b.address).map(sprite=>Object.fromEntries(Object.entries(sprite).filter(([key])=>key!=="record")));}
    frame() {return {vram:this.vram,palette:this.palette,oam:this.oam,registers:this.registers};}
    get done() {return !this.state&&(!this.group||[0,255].includes(this.group.phase));}
    image() {
      if(!scope.ZoidsDisplay)throw Error("Combined Zoid playback requires the display renderer.");
      const colors=scope.ZoidsDisplay.render(this.frame()),pixels=new Uint32Array(colors.length);
      for(let i=0;i<colors.length;i++){const value=colors[i],r=value&31,g=value>>>5&31,b=value>>>10&31;
        pixels[i]=((r<<3)|(r>>>2))|(((g<<3)|(g>>>2))<<8)|(((b<<3)|(b>>>2))<<16)|0xff000000;
      }return {width:240,height:160,pixels};
    }
    sourceTrace() {return {status:"traced",operation:"zoid-combined-animation",parameters:{model:this.model,slot:this.slot,side:this.side,variant:this.variant,equipment:this.equipment},sources:this.sources,identification_credit:0,proof_status:"unverified",scope:"Isolated original update order with body callbacks, mounted sprites, and tilemap changes. Full battle scheduling, camera effects, and audio are excluded."};}
  }

  function bindings(archive,model,equipment=[0,0,0]) {
    requireInteger(model,1,152,"model");
    const rows=archive.equipmentBindings(model).map(row=>({...row,kind:"tilemap"}));
    for(const slot of ({26:[5],64:[4,6],65:[4]}[model]||[]))rows.push({model,slot,kind:"body-callback",asset:null,
      selector:0x7a773c+model*40+(slot-4)*4,label:`Body parts · slot ${slot}`});
    if(!Array.isArray(equipment)||equipment.length!==3)throw Error("Zoid animation requires three mount slots.");
    equipment.forEach((item,slot)=>{requireInteger(item,0,100,"mounted item");if(item)rows.push({model,slot,kind:"mounted",item,asset:null,label:`${archive.name(0x7ee170,item)} · mount ${slot+1}`});});
    return rows.sort((a,b)=>a.slot-b.slot);
  }

  // Rack rules: RunPlayerEquipmentMenu's per-rack descriptor, AppendPlayerEquipmentSelectionRows' checks in order, EquipPlayerZoid's kind check.
  const ZOID_RECORDS=0x7afcc4,EQUIPMENT_RECORDS=0x7b2524,COMPATIBLE_MODELS=0x7a1e2f,GROUP_NAMES=0x7f2dec,RACK_MODES=[4,12,8,0];
  function rackDescriptor(archive,model,rack) {
    const record=ZOID_RECORDS+model*56,slotFlags=archive.u16(record+0x18+rack*4);
    let flags=(slotFlags&1)|(slotFlags&2)|RACK_MODES[rack];
    flags|=[0,0x10,0x20,0x30,0x40][archive.u8(record+2)]??0;
    if(archive.u8(record)&0x40)flags|=0x80;
    return flags;
  }
  const rackAcceptsWeapons=(archive,model,rack)=>Boolean(rackDescriptor(archive,model,rack)&1);
  const itemMountMode=(archive,item)=>archive.u8(EQUIPMENT_RECORDS+item*24+0x14)&3;
  function rackStatus(archive,model,rack,item) {
    const record=EQUIPMENT_RECORDS+item*24,descriptor=rackDescriptor(archive,model,rack),group=archive.u8(record+0x15);
    if(group){
      const row=COMPATIBLE_MODELS+group*8;let index=0;
      if(archive.u8(row)!==model){
        if(archive.u8(row))while(++index<=7){const entry=archive.u8(row+index);if(!entry||entry===model)break;}
        if(archive.u8(row+index)!==model)return "model";
      }
    }
    const constraints=archive.u8(record+0x14),size=constraints&0x1c,mode=constraints&3,rackMode=descriptor&12,code=descriptor&0x70;
    if(size&&!(size===4&&code>0x0f||size===8&&code>0x1f||size===12&&code>0x2f||size===16&&code>0x3f))return "size";
    if(mode&&!(mode===1&&rackMode===4||mode===2&&(rackMode===8||rackMode===12)||mode===3&&rackMode===12))return "mount";
    if(!(descriptor&(archive.u16(record+2)&1?2:1)))return "kind";
    if(archive.u8(record)===0x1a&&descriptor&0x80)return "smoke";
    return "accepted";
  }
  const groupName=(archive,item)=>archive.name(GROUP_NAMES,archive.u8(EQUIPMENT_RECORDS+item*24+0x15));
  const hasMountedGraphics=(archive,id,slot)=>{
    const selector=id*2+(slot?1:0),graphics=0x7abc6c+selector*8,definition=0x7ac2bc+selector*8;
    return [graphics,graphics+4,definition,definition+4].every(at=>archive.u32(at));
  };

  // Mounted sprites exist only for items 1-100 (LoadBattleSceneZoidGraphics skips item - 1 > 0x63); later items are command parts.
  function equipmentOptions(archive,slot=0,model=null) {
    requireInteger(slot,0,2,"mount slot");
    const result=[{id:0,label:"None",visible:true,status:"accepted"}];
    for(let id=1;id<=199;id++){
      const label=archive.name(0x7ee170,id),visible=id<=100&&hasMountedGraphics(archive,id,slot);
      if(label==="N/A"||id<=100&&!visible||model==null&&!visible)continue;
      result.push({id,label,visible,status:model==null?"accepted":rackStatus(archive,model,slot,id),mode:itemMountMode(archive,id)});
    }return result;
  }

  function timeline(archive,options) {
    const player=new Player(archive,options),frames=[],states=[],events=[],frameIDs=new Map(),seen=new Map();
    const base={vram:player.vram.slice(),palette:player.palette.slice(),registers:player.registers.slice()};
    for(let update=0;update<=131072;update++){
      const tilemap=player.vram.slice(0,2048),oam=player.oam.slice(),data=new Uint8Array(tilemap.length+oam.length);
      data.set(tilemap);data.set(oam,tilemap.length);const digest=scope.ZoidsObjects.key(data);
      if(!frameIDs.has(digest)){frameIDs.set(digest,frames.length);frames.push({tilemap,oam});}
      const frame=frameIDs.get(digest),state={...player.stateRecord(),frame,group:player.group?{...player.group}:null,sprites:player.spriteRecords()};
      const key=JSON.stringify(state);
      if(seen.has(key))return {format:"zoid-combined-timeline-v1",parameters:{model:player.model,slot:player.slot,side:player.side,variant:player.variant,equipment:player.equipment},...base,frames,states,events,terminal:"loop",loop_start_update:seen.get(key),source:player.sourceTrace()};
      seen.set(key,update);states.push(state);
      if(player.done)return {format:"zoid-combined-timeline-v1",parameters:{model:player.model,slot:player.slot,side:player.side,variant:player.variant,equipment:player.equipment},...base,frames,states,events,terminal:"end",loop_start_update:null,source:player.sourceTrace()};
      player.update();for(const song of player.songs)events.push({update:update+1,song});
    }
    throw Error("Combined Zoid playback exceeds its update limit.");
  }

  function image(record,update) {
    requireInteger(update,0,record.states.length-1,"timeline update");
    const frame=record.frames[record.states[update].frame],vram=record.vram.slice();vram.set(frame.tilemap);
    const colors=scope.ZoidsDisplay.render({vram,palette:record.palette,oam:frame.oam,registers:record.registers}),pixels=new Uint32Array(colors.length);
    for(let i=0;i<colors.length;i++){const value=colors[i],r=value&31,g=value>>>5&31,b=value>>>10&31;
      pixels[i]=((r<<3)|(r>>>2))|(((g<<3)|(g>>>2))<<8)|(((b<<3)|(b>>>2))<<16)|0xff000000;
    }return {width:240,height:160,pixels};
  }

  const api={Player,bindings,equipmentOptions,rackAcceptsWeapons,rackStatus,itemMountMode,groupName,timeline,image};scope.ZoidsZoidAnimation=api;
  if(typeof module==="object"&&module.exports)module.exports=api;
})(globalThis);
