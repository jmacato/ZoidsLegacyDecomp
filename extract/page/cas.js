(function (scope) {
  "use strict";

  const FAMILIES = [[25,26,27,28,29,30],[64,65,66,67]];
  const BODY_PARTS = {
    26:[[128,80,0x1298]],
    64:[[173,49,0x1298],[125,52,0x10d8]],
    65:[[144,89,0x1298],[124,89,0x10d8]]
  };
  const SHAPES = new Map([
    ["8,8",[0,0]],["16,16",[0,1]],["32,32",[0,2]],["64,64",[0,3]],
    ["16,8",[1,0]],["32,8",[1,1]],["32,16",[1,2]],["64,32",[1,3]],
    ["8,16",[2,0]],["8,32",[2,1]],["16,32",[2,2]],["32,64",[2,3]]
  ]);
  const signed16 = value => value<<16>>16;

  class CasScene {
    constructor(archive,{source,target,side=0,variant=0,slot=0,skipFrame=null}={}) {
      const family=FAMILIES.find(models=>models.includes(source));
      if(!family||!family.includes(target)||source===target)throw Error("Invalid CAS form transition.");
      if(![0,1].includes(side))throw Error("Invalid CAS scene side.");
      if(!Number.isInteger(variant)||variant<0||variant>7)throw Error("Invalid CAS palette variant.");
      if(!Number.isInteger(slot)||slot<0||slot>5)throw Error("Invalid CAS battle slot.");
      if(skipFrame!==null&&(!Number.isInteger(skipFrame)||skipFrame<0||skipFrame>689))throw Error("Invalid CAS skip frame.");
      if(archive.rom.length!==8388608||!archive.verified){
        throw Error("CAS display timing requires the original USA ROM.");
      }
      this.archive=archive;
      this.source=source;this.target=target;this.side=side;this.variant=variant;this.slot=slot;
      this.skipFrame=skipFrame;this.skipStartedTick=null;
      this.heldKeys=0;this.eventActive=0;this.inputEvents=[];
      this.vram=new Uint8Array(0x18000);
      this.palette=new Uint8Array(1024);
      this.oam=new Uint8Array(1024);
      this.registers=new Uint8Array(0x60);
      this.staging=new Uint8Array(0x4000);
      this.registerView=new DataView(this.registers.buffer);
      this.oamView=new DataView(this.oam.buffer);
      this.tick=-1;this.displayIndex=-1;this.stage=0;this.done=false;this.exit=false;
      this.sources=[];this.sourceKeys=new Set();this.sprites=[];this.bodySprites=[];
      this.songs=[];this.events=[];
      this.scroll=[side?0xa800:-0x9800,0,0,-0x3000];
      this.windowState=1;this.windowTimer=0;
      this.paletteFrame=0;this.paletteDelay=0;this.paletteDescending=false;
      for(const [address,role]of [
        [0xcfee4,"CAS scene schedule"],[0xcfd98,"CAS palette and window task"],
        [0x9a35c,"body graphics loader"],[0x9a1bc,"palette loader"],
        [0x94330,"sprite pool initialization"],[0x94374,"sprite table lookup"],
        [0x94484,"sprite creation"],[0x94578,"sprite ordering"],
        [0x946a0,"sprite coordinates, OAM, and animation updates"],
        [0x95098,"sprite group creation"],[0x95114,"sprite group destruction"],
        [0x95154,"sprite group callback updates"],[0xd22b4,"mirrored body coordinates"],
        [0x9538c,"fixed window configuration"],[0x9544c,"window bounds"],
        [0x96080,"window register updates"],[0x921d4,"scheduler and drawing order"],
        [0x92410,"VBlank display register transfer"],[0x922a4,"VBlank OAM transfer"],
        [0x92604,"held key input sampling"]
      ])this._code(address,role);
      this._writeRegister(0,0x7340);
      this._writeRegister(8,0x4086);
      this._writeRegister(10,0x020b);
      this._writeRegister(0x40,240);this._writeRegister(0x42,240);
      this._writeRegister(0x44,80);this._writeRegister(0x46,0x50a0);
      this._writeRegister(0x48,0);this._writeRegister(0x4a,0x3f);
      this._writeRegister(0x54,16);
      this.carrier=this._createSprite(this._sprite(null,0x3c713c,0x3c71dc),side?-570:810,80,0x180,3,side?0x8018:0x18);
      this._load(0x3c422c,this.vram,0x13000,"carrier tiles");
      this._loadPalette(0x3c5338,0x260,"carrier palette");
      this._load(0x3c71e0,this.vram,0x8000,"scenery tiles");
      this._load(0x3c77fc,this.vram,0x1000,"scenery tilemap");
      const maps=new DataView(this.vram.buffer);
      for(let at=0x1000;at<0x1800;at+=2)maps.setUint16(at,maps.getUint16(at,true)|0x4000,true);
      this._source(0x3c773c,0x3c77fc,"scenery palette frames");
      this._loadBody(source);
      this._traceBody(source);
      this._traceBody(target);
      this.sceneTask=this._sceneTask();
      this._updateRegisters();
      for(let index=0;index<128;index++)this.oamView.setUint32(index*8,0x200,true);
    }

    _source(start,end,role,transform="identity") {
      const key=`${start}:${end}:${role}`;
      if(this.sourceKeys.has(key))return;
      this.sourceKeys.add(key);
      this.sources.push(this.archive.sourceSpan(start,end,role,transform));
    }

    _pointer(at,role) {
      this._source(at,at+4,role);
      return this.archive.pointer(at);
    }

    _code(address,role) {
      const asset=this.archive.assets.find(item=>item.kind==="code"&&item.start<=address&&item.end>address);
      if(!asset)throw Error("A CAS routine has no extracted source span.");
      this._source(asset.start,asset.end,role,"interpreted-native-routine");
    }

    _decoded(start,role) {
      const data=this.archive.lz(start);
      const asset=this.archive.assets.find(item=>item.start===start&&item.details.encoding==="gba-lz77");
      if(!asset)throw Error("A CAS resource has no extracted source span.");
      this._source(start,asset.end,role,"gba-lz77");
      return data;
    }

    _load(start,destination,offset,role) {
      const data=this._decoded(start,role);
      if(offset+data.length>destination.length)throw Error("A CAS resource leaves its destination.");
      destination.set(data,offset);
      if(data.length&1)destination[offset+data.length]=0;
      return data;
    }

    _loadPalette(start,offset,role) {
      const data=this._decoded(start,role);
      this.staging.set(data);
      if(offset===0)this.staging.set(this.palette.subarray(0,2));
      const count=(data.length+31)&~31;
      this.palette.set(this.staging.subarray(0,count),offset);
    }

    _sprite(record,frame_table,animation_table) {
      const sprite=this.archive.sprite({record,frame_table,animation_table});
      if(record!==null)this._source(record,record+8,"body sprite selector");
      this._source(sprite.frame_table,sprite.frame_table+sprite.frames.length*4+4,"sprite frame pointers and boundary");
      this._source(sprite.animation_table,sprite.animation_table+sprite.animations.length*4+4,"sprite animation pointers and boundary");
      for(const item of [...sprite.frames,...sprite.animations]){
        const asset=this.archive.byID.get(item.asset);
        this._source(asset.start,asset.end,"sprite frame or animation");
      }
      return sprite;
    }

    _createSprite(record,x,y,tile_offset,palette_bank,flags) {
      let address=127;
      while(this.sprites.some(sprite=>sprite.address===address&&(sprite.flags&3)))address--;
      if(address<0)throw Error("The CAS sprite pool is full.");
      const sprite={record,x:signed16(x),y:signed16(y),tile_offset,palette_bank,flags:flags|1,address,animation:0,step:0,age:0};
      this.sprites.push(sprite);
      return sprite;
    }

    _loadBody(model) {
      this.model=model;
      const table=0x7a5cf0+model*12;
      this._load(this._pointer(table,"body tile selector"),this.staging,0,"body tiles");
      this.vram.set(this.staging,0x4000);
      this._loadPalette(this._pointer(0x7a641c+model*32+this.variant*4,"body palette selector"),0,"body palette");
      const mapStart=this._pointer(table+4,"body tilemap selector");
      if(this.side){
        this._load(mapStart,this.staging,0,"body tilemap");
        const source=new DataView(this.staging.buffer),destination=new DataView(this.vram.buffer);
        for(let row=0;row<16;row++)for(let x=0;x<32;x++)destination.setUint16((row*32+x)*2,source.getUint16((row*32+31-x)*2,true)^0x400,true);
      }else this._load(mapStart,this.vram,0,"body tilemap");
      this.vram.fill(0,0x800,0x1000);
      this._source(table+8,table+12,"body object tile selector");
      if(this.archive.u32(table+8)){
        this._load(this.archive.pointer(table+8),this.vram,0x10000,"body object tiles");
        this._loadPalette(this._pointer(0x7a8f24+model*32+this.variant*4,"body object palette selector"),0x200,"body object palette");
        if(!BODY_PARTS[model])throw Error("The CAS body callback is unsupported.");
        this._source(0x7a3164+model*8,0x7a3164+model*8+8,"body callback selectors");
        for(let index=0;index<2;index++)this._code(this.archive.pointer(0x7a3164+model*8+index*4)&~1,"body callback positions, flags, and updates");
      }
      this.pendingBody=model;
    }

    _traceBody(model) {
      const table=0x7a5cf0+model*12;
      this._decoded(this._pointer(table,"body tile selector"),"body tiles");
      this._decoded(this._pointer(table+4,"body tilemap selector"),"body tilemap");
      this._decoded(this._pointer(0x7a641c+model*32+this.variant*4,"body palette selector"),"body palette");
      this._source(table+8,table+12,"body object tile selector");
      if(this.archive.u32(table+8)){
        this._decoded(this.archive.pointer(table+8),"body object tiles");
        this._decoded(this._pointer(0x7a8f24+model*32+this.variant*4,"body object palette selector"),"body object palette");
        this._source(0x7a3164+model*8,0x7a3164+model*8+8,"body callback selectors");
        for(let index=0;index<2;index++)this._code(this.archive.pointer(0x7a3164+model*8+index*4)&~1,"body callback positions, flags, and updates");
        this._sprite(0x7aa244+model*8);
      }
    }

    _initializeBody() {
      if(this.pendingBody===null)return;
      const model=this.pendingBody;
      this.pendingBody=null;
      if(!BODY_PARTS[model])return;
      const record=this._sprite(0x7aa244+model*8);
      for(const [x,y,flags]of BODY_PARTS[model])this.bodySprites.push(this._createSprite(record,this.side?256-x:x,y,0,0,flags|(this.side?0x8000:0)));
    }

    _song(id) {
      this.songs.push(id);
      this.events.push({tick:this.tick,song:id});
    }

    *_sceneTask() {
      const direction=this.side?-1:1,c=this.carrier;
      this._song(22);
      for(let i=0;i<192;i++){
        this.scroll[0]+=direction*256;
        this.scroll[2]+=direction*512;
        c.x=signed16(c.x-direction*3);
        yield;
      }
      c.flags&=~8;
      this.stage=0x10;
      while(c.step<=11){
        if(c.step===0)c.y=signed16(c.y+2);
        else if(c.step>=6&&c.step<=8)c.x=signed16(c.x-direction);
        if(c.age===0&&(c.step===1||c.step===9))this._song(89);
        yield;
      }
      this.stage=0x20;
      for(const sprite of this.bodySprites)sprite.flags=(sprite.flags&~1)|2;
      this.bodySprites=[];
      this._loadBody(this.target);
      this.events.push({tick:this.tick,body:this.target});
      this.stage=0x30;
      while(!(c.flags&4)){
        if(c.step<=14)c.x=signed16(c.x+direction);
        if(c.age===0&&c.step===15)this._song(89);
        yield;
      }
      this.stage=0x40;
      this._song(104);
      let acceleration=0,drift=0,carrierSpeed=0,carrierPosition=this.side?0x600:0xea00;
      do{
        if(acceleration<=0xfff)acceleration+=0x20;
        if(drift>-0x800){drift-=0x40;carrierSpeed+=0x60;}
        this.scroll[0]+=direction*(acceleration+drift);
        this.scroll[2]+=direction*drift;
        carrierPosition+=direction*carrierSpeed;
        c.x=signed16(Math.trunc(carrierPosition/256));
        yield;
      }while(this.side?this.scroll[0]>-0xf000:this.scroll[0]<=0xffff);
      this.windowState=2;this.windowTimer=0;this.stage=0x50;
      while(!this.exit){
        this.scroll[0]+=direction*(0x800+drift);
        this.scroll[2]+=direction*drift;
        yield;
      }
      this.done=true;this.stage=0x60;
    }

    _paletteTask(heldKeys,eventActive) {
      if(eventActive!==1&&!this.exit&&this.windowState===0&&(heldKeys&2)){
        this.windowState=2;this.windowTimer=0;
        if(this.skipStartedTick===null){this.skipStartedTick=this.tick;this.events.push({tick:this.tick,skip:true});}
      }
      if(this.windowState){
        this.windowTimer++;
        const timer=this.windowTimer;
        if(this.windowState===1){
          this._writeRegister(0x44,80-timer);
          this._writeRegister(0x46,((80+timer)<<8)|160);
          if(timer===32)this.windowState=0;
        }else{
          this._writeRegister(0x44,48+timer);
          this._writeRegister(0x46,((112-timer)<<8)|160);
          if(timer===32){this.windowState=0;this.exit=true;this._writeRegister(0x50,0xff);this._writeRegister(0x54,16);}
        }
      }
      if(this.paletteDelay===0){
        const at=0x3c773c+this.paletteFrame*32;
        this.palette.set(this.archive.rom.subarray(at,at+32),0x80);
        if(this.paletteDescending){if(this.paletteFrame===0)this.paletteDescending=false;else this.paletteFrame--;}
        else if(this.paletteFrame===5)this.paletteDescending=true;
        else this.paletteFrame++;
        this.paletteDelay=4;
      }
      this.paletteDelay--;
    }

    _writeRegister(at,value) {
      this.registerView.setUint16(at,value&65535,true);
    }

    _updateRegisters() {
      for(let index=0;index<4;index++)this._writeRegister(0x10+index*2,this.scroll[index]>>8);
    }

    _drawSprites() {
      const active=[];
      for(const sprite of this.sprites.slice().sort((a,b)=>a.address-b.address)){
        if(!(sprite.flags&1)){sprite.flags&=~2;continue;}
        let position=active.length;
        while(position){
          const previous=active[position-1],flags=sprite.flags,old=previous.flags;
          let shift;
          if((flags&0xc0)!==(old&0xc0))shift=(flags&0xc0)<(old&0xc0);
          else if((flags&0x300)<(old&0x300))shift=true;
          else shift=Boolean(flags&0x40000)&&(!(old&0x40000)||sprite.y>previous.y);
          if(!shift)break;
          position--;
        }
        active.splice(position,0,sprite);
      }
      let index=0;
      for(const sprite of active){
        const animation=sprite.record.animations[sprite.animation],frame=animation.steps[sprite.step].frame,pieces=sprite.record.frames[frame].pieces;
        const camera=sprite.flags&0x1000;
        const objects=this.archive.objects(pieces,{...sprite,x:signed16(sprite.x-(camera?this.scroll[0]>>8:0)),y:signed16(sprite.y-(camera?this.scroll[1]>>8:0))});
        if(objects.length<pieces.length)sprite.flags|=0x800000;else sprite.flags&=~0x800000;
        for(const object of objects){
          if(index>=128)break;
          if(object.matrix)throw Error("An affine CAS object requires a separate native check.");
          const [shape,size]=SHAPES.get(`${object.width},${object.height}`);
          this.oamView.setUint16(index*8,(object.y&255)|(sprite.flags&0xc00)|(object.piece.tail&0xff00)|(shape<<14),true);
          this.oamView.setUint16(index*8+2,(object.x&511)|(object.flips<<12)|(size<<14),true);
          this.oamView.setUint16(index*8+4,object.tile|(object.palette_bank<<12)|(object.priority<<10),true);
          index++;
        }
        if(!(sprite.flags&8)){
          sprite.age=(sprite.age+1)&65535;
          if(sprite.age===animation.steps[sprite.step].duration_updates){
            if(sprite.step+1<animation.steps.length)sprite.step++;
            else{
              sprite.flags|=4;
              const mode=sprite.flags&0x30;
              if(!mode){sprite.flags&=~1;continue;}
              if(mode===0x20)sprite.step=0;
              else if(mode===0x30){sprite.animation=0;sprite.step=0;sprite.flags&=~4;}
            }
            sprite.age=0;
          }
        }
      }
      for(;index<128;index++)this.oamView.setUint32(index*8,0x200,true);
    }

    update({heldKeys=0,eventActive=0}={}) {
      if(this.done)return this.frame;
      if(!Number.isInteger(heldKeys)||heldKeys<0||heldKeys>0x3ff||!Number.isInteger(eventActive)||eventActive<0||eventActive>255)throw Error("Invalid CAS scheduler input.");
      this.tick++;
      if(heldKeys!==this.heldKeys||eventActive!==this.eventActive)this.inputEvents.push({tick:this.tick,heldKeys,eventActive});
      this.heldKeys=heldKeys;this.eventActive=eventActive;
      this.songs=[];
      if(this.exit){this.done=true;this.stage=0x60;}
      else this.sceneTask.next();
      if(!this.done)this._paletteTask(heldKeys,eventActive);
      this._initializeBody();
      this._drawSprites();
      this._updateRegisters();
      return this.frame;
    }

    nextFrame() {
      if(this.displayFrame?.done)return this.displayFrame;
      const previousTick=this.displayIndex<3?-1:this.displayIndex-(this.displayIndex<389?3:4);
      if(this.tick!==previousTick)throw Error("CAS display playback cannot mix with manual scheduler updates.");
      this.displayIndex++;
      if(this.displayIndex>=this.frameCount)throw Error("CAS display playback exceeded its native schedule.");
      if(this.displayIndex>=3&&this.displayIndex!==389){
        // ReadKeys precedes the target upload; scheduler tick 386 spans two display frames.
        const tick=this.tick+1,sampledFrame=tick===0?0:tick+(tick<=386?2:3);
        this.update({heldKeys:this.skipFrame!==null&&this.skipFrame<=sampledFrame?2:0});
      }
      const frame=this.frame;
      if(this.displayIndex<3){
        frame.registers=frame.registers.slice();
        frame.registers.fill(0,0,2);
        frame.registers[0x50]=0xbf;
      }
      this.displayFrame={...frame,display_frame:this.displayIndex,scheduler_done:frame.done,done:this.displayIndex===this.frameCount-1};
      return this.displayFrame;
    }

    requestSkip() {
      if(this.displayFrame?.done)return false;
      if(this.skipFrame===null)this.skipFrame=this.displayIndex+1;
      return true;
    }

    get frameCount() {
      if(this.skipFrame===null)return 690;
      const inputTick=this.skipFrame<=388?this.skipFrame-2:Math.max(387,this.skipFrame-3);
      const closingTick=Math.max(32,inputTick);
      // The natural exit resets an unfinished close at scheduler tick 655.
      if(closingTick>=624)return 690;
      return closingTick+34+(closingTick>=355?1:0);
    }

    get frame() {
      return {vram:this.vram,palette:this.palette,oam:this.oam,registers:this.registers,
        tick:this.tick,updates:this.tick+1,stage:this.stage,done:this.done,model:this.model,
        scroll:this.scroll.slice(),window:[this.windowState,this.windowTimer],exit:Number(this.exit),
        carrier:{x:this.carrier.x,y:this.carrier.y,flags:this.carrier.flags,step:this.carrier.step,age:this.carrier.age},songs:this.songs.slice()};
    }

    sourceTrace() {
      const unitAddress=0x02034b4c+this.side*0x1380+this.slot*0x270;
      return {status:"traced",operation:"CAS scene",parameters:{source:this.source,target:this.target,side:this.side,variant:this.variant,slot:this.slot,skipFrame:this.skipFrame},
        inputs:[{address:0x020372f0,bytes:[this.side],role:"battle side"},
          {address:0x020372f1,bytes:[this.slot],role:"battle slot"},
          {address:unitAddress,bytes:[this.source,this.variant],role:"source model and shared palette variant"},
          {address:0x0203725a,bytes:[this.target],role:"target model"},
          {address:0x02030664,bytes:[0],role:"initial event state before scheduler inputs"}],
        scheduler_inputs:{held_keys_address:0x0300000c,button_mask:0x03ff,event_state_address:0x02030664,changes:this.inputEvents.slice()},
        hardware_input:{register:0x04000130,held_buttons:this.skipFrame===null?0:2,first_frame:this.skipFrame,
          phase:"first instruction boundary at boot_frame + skip_frame; held through return"},
        sources:this.sources.slice(),dependencies:[],identification_credit:0,proof_status:"unverified",
        display_timing:{method:"native-observed",rom_sha256:"0379d0e57d77783ed1d18f28c78b9dd1a964e842aac023e6803377f2e86ddc7d",
          fixture:{palette:this.variant,slot:this.slot,skip:this.skipFrame!==null,initial_scene:"isolated CAS after full ROM boot"},
          display_frames:this.frameCount,hidden_loading_frames:[0,1,2],held_display_frame:this.frameCount>389?389:null,
          initial_registers:{DISPCNT:0,BLDCNT:0xbf,BLDY:16},
          scheduler_ticks:{first:0,last:this.frameCount-(this.frameCount>389?5:4)},memory_scope:"Partial upload scanline states are not simulated."},
        scope:"ROM-derived body sprites, carrier, backgrounds, windows, and palettes. Display loading delays use the stated native fixture."};
    }
  }

  function image(frame) {
    const pixels=Uint32Array.from(scope.ZoidsDisplay.render(frame),value=>{
      const r=value&31,g=(value>>>5)&31,b=(value>>>10)&31;
      return (r<<3|r>>>2)|((g<<3|g>>>2)<<8)|((b<<3|b>>>2)<<16)|0xff000000;
    });
    return {width:240,height:160,pixels};
  }

  async function bundle(archive,parameters,progress=()=>{}) {
    const scene=new CasScene(archive,parameters),files=new scope.ZoidsROM.Files(),frames=[],outputs=[],images=new Map();
    const count=scene.frameCount;
    for(let index=0;index<count;index++){
      const frame=scene.nextFrame(),rendered=image(frame),digest=scope.ZoidsROM.sha256(new Uint8Array(rendered.pixels.buffer));
      if(frame.display_frame!==index||frame.done!==(index===count-1))throw Error("CAS export timing differs from its scene.");
      let path=images.get(digest);
      if(!path){
        path=`frames/${String(index).padStart(3,"0")}.png`;
        const bytes=await scope.ZoidsROM.png(rendered);
        files.add(path,bytes);images.set(digest,path);
        outputs.push({path,size:bytes.length,sha256:scope.ZoidsROM.sha256(bytes)});
      }
      frames.push({frame:index,path,tick:frame.tick,stage:frame.stage,model:frame.model,songs:frame.songs});
      if(index%10===0){progress(index+1,count);await new Promise(resolve=>setTimeout(resolve,0));}
    }
    files.json("animation.json",{parameters,width:240,height:160,frame_hz:16777216/280896,frames,events:scene.events});
    const timeline=await files.get("animation.json");
    outputs.push({path:"animation.json",size:timeline.length,sha256:scope.ZoidsROM.sha256(timeline)});
    files.json("sources.json",{rom:{size:archive.rom.length,sha256:scope.ZoidsROM.sha256(archive.rom)},outputs,provenance:scene.sourceTrace()});
    progress(count,count);
    return files.zip();
  }

  const api={CasScene,FAMILIES,image,bundle};
  scope.ZoidsCAS=api;
  if(typeof module!=="undefined"&&module.exports)module.exports=api;
})(typeof globalThis!=="undefined"?globalThis:this);
