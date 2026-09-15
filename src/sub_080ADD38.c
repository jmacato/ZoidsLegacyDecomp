#include "m2c_prelude.h"
extern u8 D_02032473[];
extern u8 D_0203247D[];
extern u8 D_087B7958[];
extern u8 D_087B2524[];
extern u8 D_020218E4[];
extern u8 D_020218E8[];
extern u8 D_02027378[];
extern u8 D_02032273[];
extern s32 D_087EDD54[];
extern s32 D_087B77C8[];
extern u8 D_0200A880;
extern u8 D_0200A881;
extern u8 D_0200A882;
extern u16 D_0200A884;
struct S087B2524
{
  u8 _p0[2];
  u16 f2;
  s32 f4;
  u8 _p8[16];
};
struct S70
{
  u8 _a[4];
  u8 f4;
  u8 _b[107];
};
M2C_UNK func_08092E84();
volatile int *func_08094484();
M2C_UNK func_08094554();
M2C_UNK func_08096F3C();
s32 *func_0809716C();
M2C_UNK func_080971AC();
M2C_UNK func_080972C8();
void func_080981F0();
long long func_08098248();
volatile char func_0809844C();
M2C_UNK func_080986B4();
M2C_UNK func_08098834();
M2C_UNK func_080988C8();
u8 func_08098B58();
unsigned short func_08098BB4();
M2C_UNK func_0809A52C();
M2C_UNK func_0809A9C8();
volatile long func_080AC214();
M2C_UNK func_080AC3B8();
M2C_UNK func_080ACA8C();
M2C_UNK func_080ACB5C();
short func_080ACBA0();
M2C_UNK func_080ACBDC();
volatile char func_080ACCC4();
M2C_UNK func_080ACDA8();
M2C_UNK func_080B61C8();
M2C_UNK func_080B63C4();
M2C_UNK func_080B67B8();
unsigned char func_080B6810();
M2C_UNK func_080E59BC();
s32 func_080E669C();
M2C_UNK func_080E66B8();
M2C_UNK func_080E7664();
M2C_UNK func_080E77A4();
s32 func_080E7B64();
s32 func_080ECD98();
M2C_UNK func_080ED17C();
static inline static s32 *inline_fn(s32 *arg0)
{
  return arg0;
}

static inline static int inline_fn2(s8 *arg0)
{
  return (*((u8 *) arg0)) * 4;
}

static inline static u8 *inline_fn23(void *arg0, int arg1)
{
  return (u8 *) (arg0 + arg1);
}

static inline static s16 inline_fn234(s8 *arg0)
{
  return (s16) (*((u16 *) arg0));
}

static inline static s8 *inline_fn2345(void *arg0)
{
  return (s8 *) arg0;
}

static inline static s8 *inline_fn23456(void *arg0)
{
  return (s8 *) arg0;
}

static inline static s8 *inline_fn234567(void *arg0)
{
  return ((s8 *) arg0) + 0x32;
}

static inline static s32 *inline_fn2345678(int arg0)
{
  return (s32 *) (((s8 *) arg0) + 0x087A1DD0);
}

static inline static s16 *inline_fn23456789(s32 *arg0)
{
  return (s16 *) (((s8 *) arg0) + 6);
}

static inline static s16 *inline_fn2345678910(s8 *arg0)
{
  return (s16 *) (arg0 + 6);
}

static inline static s8 *inline_fn234567891011(s32 *arg0)
{
  return ((s8 *) arg0) + 0x12;
}

static inline static s32 *inline_fn23456789101112(s8 *arg0)
{
  return (s32 *) arg0;
}

static inline static s8 *inline_fn2345678910111213(void *arg0)
{
  return (s8 *) arg0;
}

static inline static s8 *inline_fn234567891011121314(s32 *arg0)
{
  return inline_fn234567891011(arg0);
}

static inline static int inline_fn23456789101112131415(int arg0)
{
  return (arg0 ^ 0) & 0xFFFFFFFF;
}

static inline static u8 inline_fn2345678910111213141516(u8 arg0)
{
  return arg0;
}

static inline static int inline_fn234567891011121314151617(int arg0)
{
  return arg0;
}

static inline s8 *inline_fn23456789101112131415161718(s8 *arg0)
{
  return 0 + arg0;
}

void sub_080ADD38(void)
{
  s8 *new_var363;
  char *new_var460;
  void *new_var383;
  int new_var241;
  u8 *new_var470;
  void *sp1C;
  void *new_var451;
  s8 *new_var155;
  s32 *new_var51;
  s32 new_var377;
  void *new_var408;
  unsigned char pad7;
  s32 *new_var299;
  int new_var404;
  u8 sp14[6];
  s32 new_var94;
  s8 *new_var209;
  int new_var170;
  int new_var467;
  s32 temp_r0_9;
  s8 *new_var339;
  char new_var137;
  s32 *new_var114;
  void *sp20;
  void *sp24;
  unsigned int new_var335;
  s32 sp28;
  s32 *sp2C;
  int new_var251;
  u8 new_var185;
  u8 *new_var124;
  s32 new_var297;
  s32 *sp30;
  s8 *new_var148;
  unsigned int new_var86;
  s8 *new_var430;
  s8 *new_var418;
  s8 *new_var74;
  s32 *sp34;
  int new_var105;
  u8 *new_var196;
  s32 *sp38;
  void *new_var392;
  int new_var245;
  char pad3;
  void *new_var316;
  int new_var283;
  void *new_var79;
  int new_var303;
  int new_var25;
  int new_var199;
  int new_var444;
  u8 (*new_var214)[6];
  int new_var26;
  unsigned int new_var210;
  s32 new_var152;
  struct S087B2524 *new_var122;
  unsigned int new_var200;
  s32 *sp3C;
  s8 *new_var3;
  int new_var281;
  s32 *sp40;
  s8 *new_var49;
  unsigned char new_var121;
  register unsigned long var_sl;
  u32 slx8v;
  s8 *new_var463;
  unsigned int new_var141;
  s8 **new_var374;
  unsigned long new_var296;
  void *sp44;
  s16 *new_var191;
  char sp48;
  u16 new_var62;
  void *sp4C;
  int sp50;
  u8 (*new_var360)[6];
  int new_var161;
  int new_var510;
  int new_var511;
  int new_var512;
  int new_var513;
  int new_var514;
  s32 *p716;
  int new_var515;
  int new_var516;
  u8 *new_var517;
  u8 *new_var518;
  u8 *new_var519;
  u8 *new_var520;
  s8 *new_var96;
  s8 *new_var247;
  int new_var154;
  int new_var8;
  s32 f4C;
  s8 *tbl410;
  s32 n13;
  u32 new_var109;
  u8 *new_var87;
  int new_var188;
  int new_var457;
  s8 *new_var108;
  u8 new_var272;
  u8 new_var354;
  short new_var472;
  s16 *new_var326;
  char new_var353;
  int new_var262;
  void *new_var139;
  int new_var240;
  int new_var250;
  s8 *new_var48;
  int new_var73;
  u16 *new_var301;
  int new_var394;
  int new_var102;
  s8 *new_var120;
  s8 *new_var379;
  void *new_var147;
  s16 new_var449;
  u16 *new_var292;
  void *new_var116;
  int new_var187;
  u32 sp54;
  s32 *sp58;
  u8 new_var159;
  unsigned int new_var393;
  s8 *new_var58;
  s32 new_var459;
  int new_var309;
  s8 *new_var224;
  float new_var351;
  s8 **new_var264;
  char *new_var193;
  s8 *new_var28;
  int new_var18;
  u16 *new_var13;
  u8 *new_var288;
  u8 *new_var252;
  int new_var11;
  int new_var135;
  s8 *new_var397;
  s32 sp5C;
  int new_var388;
  void *new_var5;
  u8 *new_var85;
  int new_var50;
  s32 sp60;
  unsigned int new_var204;
  u8 *new_var31;
  s8 *new_var277;
  short new_var52;
  u8 *new_var153;
  s32 *new_var24;
  s32 sp64;
  s16 temp_r4;
  s8 *new_var266;
  void *new_var64;
  int new_var117;
  int new_var222;
  s8 *new_var362;
  u8 *new_var181;
  s8 *new_var305;
  u8 (*new_var327)[6];
  unsigned int new_var256;
  int new_var179;
  int new_var90;
  register s32 temp_r5;
  unsigned char pad5;
  s32 *new_var435;
  u8 *new_var140;
  unsigned int new_var380;
  s8 *new_var171;
  volatile int *new_var215;
  int new_var358;
  void *new_var125;
  unsigned int pad4;
  int new_var468;
  long new_var462;
  int *new_var450;
  int new_var330;
  void *new_var447;
  void *new_var389;
  s8 *new_var415;
  u8 new_var63;
  u8 new_var443;
  int new_var307;
  register short temp_r6;
  int new_var370;
  int new_var32;
  u16 *new_var98;
  s16 *new_var33;
  short new_var433;
  int new_var103;
  u8 *new_var16;
  s32 *temp_r0_15;
  register s32 var_r4_3;
  u8 *new_var36;
  s16 *new_var308;
  int new_var434;
  s32 var_r4;
  s8 *tblA;
  s32 *temp_r0_12;
  s32 *temp_r0_13;
  int new_var323;
  s8 *new_var230;
  s8 *new_var368;
  int new_var261;
  unsigned int new_var151;
  volatile int *new_var311;
  s32 new_var165;
  int new_var414;
  void *new_var417;
  u8 *new_var168;
  int new_var413;
  u8 *new_var315;
  int new_var41;
  s32 *new_var77;
  s8 *new_var269;
  s16 *new_var333;
  u8 *new_var30;
  s8 *new_var229;
  s32 *new_var286;
  u8 *new_var366;
  unsigned int new_var306;
  u8 *new_var458;
  u8 *new_var156;
  s8 *new_var314;
  s32 *temp_r0_14;
  unsigned char new_var344;
  int new_var38;
  char new_var469;
  int new_var280;
  int new_var45;
  int new_var274;
  s16 *new_var2;
  int new_var221;
  s8 *new_var163;
  s32 *new_var391;
  s8 *new_var332;
  int new_var44;
  int new_var440;
  unsigned short new_var183;
  s32 k152v;
  s32 k8v2;
  s32 k8c;
  s8 *new_var324;
  s32 *temp_r0_16;
  int new_var239;
  int new_var304;
  int new_var293;
  s16 new_var235;
  int new_var61;
  void *new_var372;
  u8 temp_r0_18;
  s8 *new_var387;
  s8 *new_var429;
  u32 new_var356;
  unsigned int new_var207;
  u8 *new_var42;
  s32 *temp_r0_7;
  void *new_var461;
  int new_var34;
  int new_var110;
  u8 (*new_var352)[];
  int new_var298;
  s8 *new_var164;
  u8 *new_var246;
  int new_var111;
  u8 *new_var82;
  int new_var89;
  s16 new_var349;
  s8 *new_var465;
  int new_var313;
  u16 *new_var270;
  s8 *new_var405;
  s32 *new_var75;
  int new_var211;
  s32 *temp_r0_8;
  s8 *new_var84;
  u8 new_var40;
  u8 *new_var381;
  s8 *new_var396;
  register unsigned int var_r4_5;
  s32 temp_r0;
  s32 new_var378;
  int new_var452;
  s8 *new_var91;
  u8 (*new_var55)[6];
  void *new_var56;
  unsigned int pad9;
  u32 new_var233;
  s32 *new_var70;
  int new_var17;
  s8 *new_var115;
  u8 *new_var376;
  s8 *new_var177;
  unsigned int pad8;
  s8 *new_var454;
  unsigned long long new_var285;
  int new_var129;
  int new_var100;
  u8 (*new_var373)[6];
  void *new_var338;
  int new_var329;
  s8 *new_var202;
  int new_var88;
  int new_var112;
  s8 *new_var59;
  s32 *new_var6;
  s32 var_r0;
  int new_var395;
  s32 *new_var160;
  s32 *new_var371;
  s32 var_r0_2;
  s32 var_r0_2b;
  int new_var190;
  s32 *new_var216;
  unsigned char new_var132;
  int new_var201;
  s8 *new_var423;
  u8 *new_var300;
  short new_var227;
  int new_var107;
  s8 *new_var7;
  int new_var455;
  s8 *new_var302;
  u16 *new_var46;
  int new_var242;
  s8 *new_var206;
  s32 var_r0_3;
  u16 *new_var20;
  s32 *new_var419;
  long var_r0_4;
  volatile int *new_var275;
  unsigned short new_var310;
  int new_var291;
  int new_var255;
  s8 *new_var436;
  s8 *new_var99;
  s32 *new_var267;
  int new_var359;
  s32 var_r2;
  s32 new_var502;
  register s32 var_r6_2;
  int new_var437;
  struct S70 *new_var175;
  s8 *new_var60;
  short new_var466;
  int new_var259;
  s16 *new_var144;
  int *new_var320;
  s16 *new_var9;
  void *new_var416;
  s16 *new_var19;
  u8 *new_var325;
  unsigned char new_var328;
  int new_var420;
  int new_var219;
  s32 *new_var182;
  u8 new_var166;
  unsigned char new_var167;
  s32 *new_var213;
  unsigned int temp_r0_3;
  s16 *new_var208;
  u16 *new_var226;
  char new_var334;
  int new_var265;
  s32 *new_var232;
  s32 var_r7;
  int new_var225;
  s32 **new_var243;
  s32 *new_var133;
  int new_var238;
  int var_r7_2;
  int new_var290;
  s8 **new_var146;
  u8 *new_var258;
  int new_var361;
  char new_var276;
  double new_var422;
  u8 *new_var138;
  int new_var149;
  int new_var83;
  unsigned int new_var180;
  unsigned int pad6;
  int new_var104;
  register u16 *var_r6;
  register u16 *new_var505;
  volatile int *new_var223;
  int new_var43;
  int new_var438;
  int new_var431;
  void *new_var273;
  s32 *new_var113;
  s8 *new_var71;
  u16 temp_r0_5;
  s8 *new_var192;
  s32 *new_var53;
  long new_var127;
  s8 *new_var406;
  s8 *new_var421;
  int new_var347;
  int new_var331;
  s32 *new_var81;
  short new_var186;
  short new_var428;
  int new_var150;
  register u32 var_r5_3;
  s8 *new_var80;
  u8 *new_var399;
  s32 temp_r2;
  int new_var312;
  u16 temp_r1;
  s32 *new_var184;
  s8 *new_var220;
  s8 *new_var446;
  s8 *new_var69;
  void *new_var101;
  unsigned int new_var384;
  s16 new_var248;
  int new_var162;
  u16 temp_r1_5;
  s8 *new_var92;
  u8 *new_var131;
  s8 *new_var134;
  u16 *new_var54;
  void *new_var260;
  int new_var432;
  unsigned int pad;
  unsigned int new_var445;
  unsigned int new_var402;
  int *new_var282;
  u16 temp_r1_8;
  register u32 var_r5;
  s8 **new_var471;
  u8 *new_var237;
  u8 *new_var278;
  int new_var294;
  short new_var173;
  s32 *new_var142;
  u8 *new_var158;
  s8 *ta3010;
  u8 tv3010;
  s8 *new_var158b;
  void *new_var398;
  u16 new_var295;
  int new_var;
  s8 *new_var364;
  u8 *new_var76;
  register u32 var_r5_6;
  s8 *new_var195;
  u8 (*new_var400)[6];
  s16 *new_var249;
  int new_var403;
  int temp_r0_11;
  s16 *new_var412;
  register u32 var_r5_5;
  int new_var284;
  u8 *var_r4_2;
  u8 *new_var365;
  void *new_var336;
  s8 *new_var4;
  s16 *new_var271;
  s8 *new_var287;
  int new_var203;
  s16 new_var448;
  int new_var253;
  int new_var385;
  u8 *new_var357;
  s32 *new_var319;
  s8 *new_var145;
  s32 new_var369;
  int new_var57;
  s16 *new_var254;
  u16 *new_var345;
  int new_var427;
  int new_var453;
  struct S087B2524 *new_var68;
  unsigned short new_var317;
  u16 *new_var375;
  unsigned char new_var97;
  int new_var401;
  u8 temp_r0_17;
  s8 *new_var169;
  s32 new_var95;
  u8 temp_r0_2;
  s8 *new_var390;
  s8 *new_var126;
  int new_var93;
  int new_var143;
  unsigned long new_var441;
  u8 new_var473;
  s8 *new_var29;
  u8 temp_r0_6;
  s8 *new_var321;
  int new_var382;
  int new_var409;
  u16 *new_var228;
  u16 *new_var10;
  u16 *new_var194;
  int new_var367;
  int new_var342;
  int new_var176;
  u8 temp_r0_4;
  int new_var39;
  void *new_var47;
  void *new_var67;
  int new_var136;
  int new_var442;
  unsigned int new_var279;
  u16 *new_var66;
  long new_var407;
  int new_var268;
  long new_var343;
  u8 *new_var198;
  u8 temp_r1_2;
  volatile int *new_var172;
  unsigned int new_var346;
  u8 (*new_var197)[6];
  short new_var234;
  short temp_r1_6;
  short t16c;
  short t16d;
  short t16e;
  s32 temp_r1_3;
  u8 temp_r3;
  u8 temp_r5_2;
  u8 t52b;
  s32 new_var27;
  u8 new_var424;
  short new_var386;
  u8 new_var217;
  s32 *new_var337;
  s8 *new_var37;
  int new_var78;
  u8 *new_var411;
  u8 new_var14;
  int new_var322;
  u8 *new_var348;
  u8 var_r2_3;
  s32 *new_var350;
  unsigned int new_var456;
  s8 *new_var218;
  unsigned long pad2;
  s8 *new_var119;
  register s32 var_r4_4;
  s32 *new_var231;
  void *temp_r0_10;
  int new_var263;
  void *temp_r1_4;
  void *temp_r1_7;
  s8 *new_var289;
  s8 *new_var21;
  register s32 var_r5_2;
  register s32 var_r5_4;
  void *new_var355;
  unsigned short new_var212;
  int new_var65;
  u8 *new_var341;
  s8 *new_var244;
  unsigned char new_var123;
  int new_var118;
  int new_var236;
  void *temp_r0_19;
  int new_var22;
  u8 *new_var439;
  s32 var_cmp;
  s32 var_done_flag;
  s8 *new_var157;
  void *new_var410;
  int new_var15;
  u8 new_var257;
  unsigned int new_var106;
  u16 *p3006;
  s8 *new_var12;
  u8 *p30;
  char *p30b;
  s8 *new_var174;
  register void *p20;
  unsigned int new_var318;
  u16 *new_var425;
  register u8 *ptr2060;
  s32 *new_var72;
  int new_var426;
  int new_var340;
  s8 *new_var128;
  unsigned long new_var35;
  u8 new_var178;
  int new_var205;
  u32 new_var189;
  int new_var464;
  s8 **new_var130;
  s8 *p4C;
  s32 kFFFF;
  s32 ten10;
  s32 k8v;
  u8 *tblC;
  u8 *tblD;
  s32 k6;
  s32 k5;
  s32 k11;
  new_var141 = (new_var50 = 0x08106364);
  new_var297 = (sp64 = 0xB);
  sp28 = func_080E669C();
  new_var351 = (float) 0;
  new_var239 = 1;
  new_var452 = (0, 0x30);
  var_r7 = (0, 0);
  new_var31 = (u8 *) 0x02032487;
  new_var355 = (new_var260 = new_var47);
  new_var18 = new_var351;
  var_done_flag = 0;
  new_var110 = 0xE;
loop_1:
  switch (var_r7)
  {
    int new_var23;
  case 0x0:


    func_08098BB4(0x08000F56);
    func_08098BB4(0x08000F0D);
    func_080B61C8(0 ^ 0, 0, 0);
    func_080AC214(3, 0);
    func_080B63C4();
    func_080AC3B8(5, 0, 0x32 * (0x08001BC5 * 0));
    func_080ACA8C(8, 1, 3);
    sp2C = func_08094484(0x08105A20, 0x08105A2C, 0, 0xD8, 0x98, 0x343, 0xF, 8, var_r7);
    sp30 = (new_var275 = func_08094484(0x08105664, 0x08105690, 0, 0, 4, var_r5_6 = 0x2E2, 0xF, 0x20, var_r7));
    sp50 = 0;
    sp48 = 0;

    if (((1 != 0) != 0U) != 0)

    sp44 = (sp4C = 0);

    var_r7 = 0x1000;
    goto block_306;
    ;

  case 0x1000:
    temp_r0_18 = 0xB8;
    sp40 = func_08094484(0x0821024C, 0x08210258, (1 * 0) * 0, temp_r0_18, 0x58, 0, 0, 8, 0);
    var_r7 = 0x1010;
    goto block_306;
    new_var93 = (((((((((1 & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu;


    new_var149 = 0x02030564;
    if (new_var8 != 0)

    new_var266 = new_var7;

  case 0x1010:

    new_var201 += var_r0 * 0;

    new_var417 = ((0, 0x020321A4)) + sp44;






    new_var157 = ((s8 *) sp1C) - (-new_var8);


    new_var405 = new_var266;
    if (!new_var8)
    {
    }
    if (sp50)
    {
    }
    new_var471 = &new_var379;
    new_var94 = new_var94;
    new_var334 = 1 != 0;
    if (*new_var471)
    {
    }
    new_var418 = new_var405;
    if (!new_var418)
    {


    }
    new_var197 = &sp14;
    new_var373 = (0, &sp14);
    if (var_sl)
    {
    }

    goto dummy_label_982533;
  dummy_label_982533:
    ;

    if (((!D_020218E8) && (!D_020218E8)) != 0U)
    {
    }


    sp2C = sp2C;
  dummy_label_118870:
    ;

    new_var14 = 0;
    if (new_var308 == (0 ^ 0))
    {
    }
    if ((sp2C && sp2C) && sp2C)
    {
    }
    if (new_var334)
    {
    }
    do
    {
    }
    while (0);
  dummy_label_496715:
    ;


    var_r6_2 = var_r2;
    new_var184 += 0;
    ;


    ;
  dummy_label_292366:
    ;

    new_var381 = (new_var411 = (u8 *) 0);

    new_var462 = 0xFFFFu;
    new_var100 = 1;
    {
      u8 *pA;
      pA = (u8 *) 0x020321A4;
      asm volatile("" : "+r"(pA));
      sp1C = (void *) (((((8 & 0xFFu) * (((*((u8 *) (sp44 + ((s32) pA)))) * ((0, 2))) * 7)) + ((s32) D_020218E8)) ^ 0) ^ 0);
    }
    new_var187 = 0xFFFFFFFFFFFFFFFFu;
    ;
    new_var465 = ((0, (s8 *) new_var355)) - (-0x40);
    new_var323 = (*((u8 *) (0x020321A4 + sp44))) * 7;
    new_var473 = *((u8 *) sp1C);
    ;
    new_var443 = *inline_fn23(sp1C, new_var100);
    func_0809A52C(new_var473, new_var443, 0, 0, 0x02002880);
    new_var373 = (0, &sp14);
    temp_r0_16 = (new_var71 = ((s8 *) sp1C) - (-6));
    if ((float) (((!sp20) && (!sp20)) && (!sp20)))
    {

    }
    temp_r6 = (new_var27 = (((((((((((unsigned int) (*((0, (s16 *) temp_r0_16)))) & new_var187))) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu)));
    asm volatile("" :: "r"(new_var27));
    asm volatile("" :: "r"(new_var27));
    new_var218 = ((s8 *) sp1C) + 0x3E;
    ;
    new_var201 = 0xA;
    new_var502 = 0;
    new_var369 = func_080ECD98(*((s16 *) (((s8 *) sp1C) + 0x3A)), 0xA);
    if (((s32) (*inline_fn23456789(sp1C))) < ((s32) (new_var268 = (new_var472 = (s16) new_var369))))
    {
      if (!sp1C)
      {
        goto dummy_label_573985;
      dummy_label_573985:
        ;

        temp_r3 = temp_r3 + ((0, 0));
      }
      new_var502 = 1;
    }
    ;
    ;
    asm volatile("" :: "r"(new_var502));
    asm volatile("" :: "r"(new_var502));
    func_0809844C(new_var27, 4, new_var502, 0xA, 4, (0, 3), 8 & 0xFFFFFFFFu);
    new_var8 = 0xA;
    new_var322 = *((s16 *) new_var465);
    new_var322 = new_var322 & 0xFFFFu;
    func_0809844C(*((s16 *) (((s8 *) sp1C) + 0x3A)), 4, 0, 0xA, 4, (1 * 0, 8), 8);
    func_0809844C(*((s16 *) new_var218), 4, new_var14, new_var201, (0, 4), 8, 9);
    new_var36 = inline_fn23((s8 *) sp1C, 0x38);
    new_var329 = new_var343;
    new_var407 = 1;
    ;
    if (new_var137)
    {


    }
    if (((u32) var_r5_4) * 0, new_var407)
    {
      new_var343 = (0, new_var137 = 1);
      if (new_var329 != 0)

      if (!new_var165)
      {
      }
    }
    if (!var_r5_6)
    {
    }
    new_var106 = 0x5A94;
    if (1 != (new_var329 * 0))

    new_var424 = *new_var36;
    switch (*new_var36)
    {
    case 0:
      var_r0 = 0x08106360;
      if (!var_r4)
      {
      }
      goto block_67;
      new_var119 = (s8 *) new_var373;

    case 1:
      var_r0 = new_var50;
      goto block_67;

    case 2:
      new_var137 = new_var137 + 0;
      var_r0 = 0x08106368;
      do
      {

        goto block_67;

        if (!(new_var317 = var_sl))
        {
        }
      }
      while ((0 ^ 0) & (0xFF ^ 0));



    case 3:

      if (0 != new_var35)
      {
      }
      var_r0 = 0x0810636C;



      new_var341 = ((u8 *) sp24) - (-2);
      ;
    block_67:
      { register s32 a11 asm("r1"); a11 = 0xB; asm volatile("" : "+r"(a11)); func_080981F0(var_r0, ((((new_var322 & 0xFFu) & 0xFFFFu) & 0xFFFFu) & 0xFFFFu) * 0, 4, 5, a11); }

      break;

    case 4:
      ;
      func_080981F0(0x08106370, 0 & 0xFFFFu, 4, 5, 0xB);
      break;

    }

    new_var54 = (new_var91 = (s8 *) ((0, sp1C)));
    func_080986B4(7);
    new_var165 = (s32) D_020218E4;
    func_080981F0(func_080E7B64(*inline_fn23(((((((*inline_fn23((s8 *) sp1C, 2)) << 1) << 2) << (1 & 0xFFFFFFFFu)) << 1) << 1) + new_var165, new_var106)), 0, (0, 7), (0, 0, 0), 0);
  dummy_label_859184:
    ;

    new_var46 = new_var46;
    func_080ACBDC(8, sp48);
    var_sl += 0;
    func_08098BB4(0x08000F9E);
    new_var225 = new_var225 + new_var94;
    ;
    sp44 = D_0200A880;
    sp48 = ((s32) (new_var185 = D_0200A881 ^ 0)) ^ 0;
    switch (D_0200A882)
    {
    case 0:
      ;

      if (0x100 & (D_0200A884 ^ 0))
      {
        new_var371 = sp40;
        func_08094554(new_var371);
        func_08092E84(0x41);
        var_r7 = 0x2000;
      }

      new_var91 += 4;
      if (var_r5_3 && var_r5_3)
      {
      }

    default:
      goto block_306;
      new_var91 = new_var54;
    dummy_label_207587:
      ;


    case 1:
      new_var9 = new_var9;
      new_var = (*((u16 *) (new_var91 - (-4)))) & 0xFFFE;
      *((u16 *) (new_var91 - (-4))) = (u16) new_var;
      func_08098BB4((new_var444 = 0x08000FA6) & 0xFFFFFFFFu);
      *sp2C = *sp2C;
      *sp2C = (*sp2C) | 0x20000;
      *sp30 = *sp30;
      *sp30 = (*((0, sp30))) | 0x20000;
      var_r7 = 0x1020;
      goto block_306;
      new_var57 = (float) new_var57;

    case 2:
      func_08094554(new_var24 = sp40);
      func_08094554(sp2C);
      ;
      func_08094554(sp30);
      func_080ACBA0(8);
      func_08098BB4(new_var444);
      var_done_flag = 1;
      goto block_306;

    }

    break;
    new_var111 = (temp_r0_3 = (!p20) ^ 0);


  case 0x1020:

    if (!new_var454)
    {
    }
    temp_r0_9 = (temp_r0_9 <<= 3);
    new_var468 = new_var358 && new_var358;
    new_var450 = &new_var;
    ;
    if (!new_var143)
    {
    }
    do
    {
      ;
    }
    while (((0xFF & ((((0, new_var102)) & 0xFF) & 0xFF)) & 0xFF) * 0);


    if (sp20)
    {
    }

    *sp2C = *sp2C;



    func_08098BB4(0x08000FB3);
    if (!sp54)
    {
    }





    goto dummy_label_102421;
  dummy_label_102421:
    ;

    ;


    if ((temp_r0_11 && temp_r0_11) && temp_r0_11)
    {
    }
    if (new_var468 && new_var358)
    {
    }
    do
    {
    }
    while (0, 0 != 0);
  dummy_label_900856:
    ;

    ;
    new_var414 = (unsigned int) (*new_var450);
    new_var395 += 0 ^ 0;
    if (temp_r0_10)
    {
    }
    func_080981F0(D_087EDD54[*inline_fn23((s8 *) sp1C, (0 * 0) ^ 0)], 0, 1, 0, 0);
    ;
    new_var236 = 0xFF;
    temp_r5 = *inline_fn23456789(sp1C);
    asm volatile("" :: "r"(temp_r5));
    new_var188 = (var_r7_2 = 0);
    new_var254 = (s16 *) (((s8 *) sp1C) + 0x3A);
    new_var29 = new_var29;
    new_var513 = *((s16 *) (((s8 *) sp1C) + (0x3A ^ 0)));
    {
      register s32 tenlo asm("r2");
      tenlo = 0xA;
      asm volatile("" : "+r"(tenlo));
      ten10 = tenlo;
    }
    {
      s32 c5r; s32 c5t;
      c5r = func_080ECD98(new_var513, 0xA ^ 0);
      c5t = (s32) temp_r5;
      asm volatile("" : "+r"(c5t));
      if (((s32) c5t) < ((s32) (s16) c5r))
      {
        var_r7_2 = 1 & 0xFFFFFFFFu;
      }
    }
    pad3 = 0 ^ 0;
    func_0809844C(temp_r5, 4, var_r7_2, new_var431, pad3, 4, 0);
    new_var431 = 0xA;
    new_var47 = sp1C;
    {
      register s8 *b2 asm("r1");
      b2 = (s8 *) sp1C;
      asm volatile("" : "+r"(b2));
      new_var513 = *((s16 *) (b2 + 0x3A));
    }
    func_0809844C(new_var513, 4, new_var464, (0 * 0, 0xA), 0 ^ 0, 9, 0);
    func_0809844C(*((s16 *) (((s8 *) sp1C) + 0x3E)), 4, 0, 0xA, sp50 * 0, 9, 1);
    new_var423 = ((s8 *) ((0, sp1C))) - (-0x40);
    func_0809844C(*((s16 *) new_var423), 4, 0, 0xA, 0, 4, 2);
    new_var208 = (s16 *) (((s8 *) sp1C) + 0x3A);
    new_var464 = 0 & (0xFFFF ^ 0);
    new_var102 = (new_var23 = 0);
    new_var102 = 0xFF & (0xFF & ((((new_var431 & (0xFF ^ (new_var102 ^ ((0, 0))))) & 0xFFFFFFFF) & 0xFF) & 0xFF));
    new_var340 = new_var431;
    if (!temp_r1_6)
    {
    }
    func_0809844C(*((s16 *) (((s8 *) sp1C) + 0x42)), 4, 0, new_var340, 8 * 0, 4, 4);
    new_var144 = (s16 *) (((s8 *) sp1C) + 0x44);
    new_var380 = new_var188;
    new_var448 = *new_var144;
    new_var393 = 0;
    new_var162 = 0xFF;
    new_var162 = (0xFF & (0xFF & ((((0, new_var102)) & 0xFF) & (0xFF ^ 0)))) & new_var162;
    func_0809844C(new_var448, 4, new_var380, new_var162 ^ 0, 0, 4, 5);
    new_var379 = ((s8 *) sp1C) + new_var8;
    new_var157 = ((s8 *) sp1C) - (-new_var8);
    new_var96 = (new_var29 = (s8 *) sp1C);
    new_var204 = (0, 0xFFFFFFFFFFFFFFFFu);
    func_0809844C(*((s16 *) (((s8 *) sp1C) + 0xA)), 4, 0, new_var340, (0, new_var23), 4, 6);
    new_var449 = *((s16 *) (((s8 *) sp1C) - (-0x46)));
    new_var264 = &new_var12;
    func_0809844C(new_var449 ^ 0, 4, 0, new_var431, 0, 4 ^ 0, 8);
    if (sp1C)

    new_var90 = new_var444;
    new_var138 = (u8 *) 0x087A1DB8;
    new_var333 = (0, (s16 *) (((s8 *) sp1C) + 0x48));
    new_var90 = 0;
    new_var90 = (((new_var90 ^ 0) * (new_var90 ^ 0)) & new_var204) & new_var236;
    func_0809844C(*new_var333, 4, new_var90 ^ (((0, 0)) ^ 0), new_var8, new_var90, 4, 9);
    new_var12 = temp_r0_10;
    new_var206 = (s8 *) sp1C;
    new_var206 = ((0, new_var206)) + 0x10;
    new_var347 = 0xFFFFFFFFFFFFFFFFu;
    new_var374 = new_var264;
    new_var12 = (*new_var374) - (-((0x3C & new_var347) ^ ((0, new_var90))));
    new_var177 = (s8 *) sp1C;
    new_var191 = (s16 *) new_var206;
    func_0809844C(*((s16 *) (((s8 *) sp1C) + 0x3C)), 4, new_var90, new_var8, new_var90, 4, ten10);
    new_var395 = 0xE;
    new_var210 = (new_var11 = (((((0xFFFFFFFFu & new_var90) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu);
    new_var412 = (s16 *) (0x4A + ((0, (s32) sp1C)));
    func_0809844C(((((((((0xFFFFFFFFu & (*new_var412)) & ((0, 0xFFFFFFFFu))) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu, 4, new_var90, ((0, 0xA & 0xFFFFFFFFu)) ^ 0, new_var11, 4, 0xC);
    new_var183 = 4;
    func_0809844C((s16) (*inline_fn23((s8 *) (new_var237 = sp1C), 0x39)), 4 & 0xFFu, ((double) new_var210, new_var210 ^ 0), new_var431 ^ new_var210, new_var90, new_var183, new_var395);
    new_var120 = (s8 *) sp1C;
    {
      register s8 *b3 asm("r1");
      b3 = (s8 *) sp1C;
      asm volatile("" : "+r"(b3));
      new_var449 = *((s16 *) (b3 + 0x10));
    }
    func_0809844C(new_var449, new_var183, new_var90, new_var431, new_var393, new_var183, 0xF);
    new_var401 = (((char) ((new_var416 = sp1C) && new_var416)) & 0xFF) && new_var416;
    if (new_var401)
    {
    }
    new_var514 = *((s16 *) (((s8 *) sp1C) - (-(new_var217 = new_var395))));
    f4C = 0;
    p4C = ((s8 *) sp1C) + 0x4C;
    if ((((s32) (*((0, (s16 *) (((s8 *) sp1C) - (-new_var395)))))) ^ (0 ^ 0)) > ((s32) (*((s16 *) p4C))))
    {
      f4C = 1;
    }
    func_0809844C(new_var514, new_var183, f4C, new_var340, 0, new_var183, (0x10 & 0xFFFF) & 0xFFFFu);
    func_0809844C(*((s16 *) p4C), (0, 4), new_var347 * 0, new_var340, 0, (char) 9, 0x10);
    ;
    new_var132 = 0;
    new_var203 = (0, *inline_fn23((s8 *) sp1C, 0x38));
    switch (new_var203)
    {
    case 0:
      var_r0_2 = 0x08106360;
      goto block_88;

    case 1:


      var_r0_2 = new_var50;
      goto block_88;

    case 2:
      var_r0_2 = 0x08106368;
      goto block_88;

    case 3:
      var_r0_2 = 0x0810636C;
      if ((new_var43 && new_var43) && new_var43)
      {
      }
      new_var12 = temp_r0_10;
    block_88:
      func_080981F0(new_var180 = var_r0_2, 0, 0, 6, 0x11);

      break;

    case 4:
      func_080981F0(0x08106370, ((0, new_var102)) * 0, 0, 6, 0x11);
      break;
      if (!sp28)
      {
      }

    }

    if (((new_var330 && new_var330) && new_var330) != 0)
    {
    }
    var_sl = 0;
    goto dummy_label_460633;
  dummy_label_460633:
    ;

    sp54 = 1;
    new_var75 = (sp58 = func_08094484(0x080ED830, 0x080ED864, (0, new_var132), (0 & 0xFFFF) ^ 0, (new_var349 = (s32) (*new_var138)) ^ 0, 0x3EE, 0xF, 0x20, 0));
    if (var_r0_4)

    goto dummy_label_260802;
  dummy_label_260802:
    ;

    sp38 = (new_var181 = func_08094484(0x08105A20 & 0xFFFFFFFFu, 0x08105A2C, 0, (0, 0xD8 ^ 0), (new_var25 = 0x98), 0x343, 0xF, (k8c = 8), 1 * 0));
    asm volatile("" :: "r"(k8c));
    sp3C = func_08094484(0x08105A70, ((((((((0x08105A7C & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu, 0 * (((0 ^ 0) ^ 0) ^ 0), 0xA8, 0x98, 0x346, 0xF, k8c, 0);
    func_080ACB5C(8);
    var_r7 = 0x1030;
    goto block_306;
    ;
    ;
    if (!sp20)



  case 0x1030:
    func_08096F3C();
    do
    {
      new_var296 = 1;
      new_var240 = ((!var_sl) && (!var_sl)) && (!var_sl);
      if (!sp20)
      {
      }
      if (var_sl != sp54)
      {

        {
          u8 *tblB;
          tblB = (u8 *) 0x087A1D80;
          asm volatile("" : "+r"(tblB));
          func_08098BB4(*((s32 *) ((var_sl * 4) + ((s32) tblB))));
        }
        func_080972C8();
        new_var58 = (s8 *) var_sl;
        new_var58 = new_var58 - (-0x087A1DB8);
        new_var128 = (s8 *) sp58;
        if (new_var240 != 0)
        {


        }
        new_var198 = (u8 *) new_var58;
        *((s16 *) (new_var128 + 6)) = (s16) (*new_var198);
        sp54 = var_sl;
      }
      func_080ED17C(new_var296);
      if ((((*((u16 *) 0x03006034)) & 0x40) && (0 != var_sl)) != 0U)
      {
        var_sl = (u32) ((u8) (var_sl - 1));
        func_08092E84(0x40);
      }
      if (((0x80 & (*((u16 *) 0x03006034))) && (var_sl < (0xCU + 1))) != 0)
      {

        var_sl = (u32) ((u8) (var_sl + 1));

        func_08092E84(0x40);
        goto dummy_label_309891;
      dummy_label_309891:
        ;

      }
    }
    while (!(3 & (*((u16 *) 0x0300000E))));











    if (1 != 0)

    if (sp30)


    if (1 != 0)
    {
    dummy_label_205865:
      ;

    }
    goto dummy_label_349352;
  dummy_label_349352:
    ;

    func_08094554(sp58);
    sp28 = sp28;
    sp28 = sp28 + 0;
    func_08094554(sp38);
    func_08094554(sp3C);
    if (1 & (*((u16 *) 0x0300000E)))
    {
      func_08092E84(0x3E);
      var_r7 = 0x1040;
    }
    else
    {
      func_08098BB4(0x080014D0);
      func_08092E84(0x3F);
      var_r7 = 0x1100;
    }
    ;
    goto block_306;
    if (!new_var147)

    ;

  case 0x1040:
    func_08098BB4(0x08001420);
    var_r5 = 0;
    tblA = (s8 *) 0x087EE170;
    var_r6 = (u16 *) (((s8 *) sp1C) + 0x52);
    do
    {
      var_r4 = var_r5 * 2 + 1;
      if (var_r5 > 3U)
      {
        var_r4 += 1;
      }
      func_080981F0(*((s32 *) ((*var_r6 << 2) + (s32) tblA)), 0, 0, 3, (var_r4 = (s16) var_r4));
      new_var515 = *var_r6;
      if (new_var515 != 0)
      {
        new_var122 = (struct S087B2524 *) D_087B2524;
        new_var295 = new_var515;
        asm volatile("" : "+&r"(new_var295) : "r"(new_var515));
        if ((new_var122[new_var295].f2 & 1) == 0)
        {
          if ((*((s32 *) ((((u8 *) D_087B2524) + (new_var295 * 0x18)) + 4)) & 0x10) == 0)
          {
            func_080981F0(0x08106374, 0, 0, 1, var_r4);
          }
          else
          {
            func_080981F0(0x08106378, 0, 0, 1, var_r4);
          }
        }
        else
        {
          func_080981F0(0x0810637C, 0, 0, 1, var_r4);
        }
      }
      var_r6 += 2;
      var_r5 += 1;
      asm volatile("" :: "r"(var_r5));
      asm volatile("" :: "r"(var_r5));
      asm volatile("" :: "r"(var_r5));
      asm volatile("" :: "r"(var_r5));
    }
    while (var_r5 <= 7U);
    asm volatile("" :: "r"(tblA));
    var_r5 = 8;
    var_sl = 0;
    sp54 = 1;
    sp58 = func_08094484(0x080ED8F8, 0x080ED92C, 0, 0, *(u8 *) 0x087A1DC6, 0x3F4, 0xF, 0x20, var_sl);
    sp38 = func_08094484(0x08105AC0, 0x08105ACC, 0, 0xD0, 0x98, 0x34C, 0xF, var_r5, var_sl);
    var_r7 = 0x1050;
    goto block_306;

  case 0x1050:
    new_var282 = &new_var150;
    func_08096F3C();
    do
    {
      new_var197 = &sp14;
      if (var_sl != sp54)
      {
        if ((new_var395 && new_var395) && new_var395)
        {
        }
        new_var263 = 0 ^ 0;
        new_var152 = *((u8 *) (((s8 *) sp1C) + 2));
        temp_r0_6 = new_var152;
        if (1 != 0)
        {
          new_var190 = 1;
          if (temp_r0_6)
          {
            ;
            new_var94 = temp_r0_6;

            new_var102 = (new_var94 << 1) << 1;

            {
              u8 *pA;
              s32 v65;
              v65 = (((new_var102 << 1) << 1) << new_var190) << 1;
              asm volatile("" : "+r"(v65));
              pA = (u8 *) 0x02027378;
              asm volatile("" : "+r"(pA));
              sp20 = (void *) (v65 + (s32) pA);
            }
          }
          else
          {
            sp20 = 0xFFFFFFFFFFFFFFFFu * 0;
            var_done_flag = 0;
          }
          if (*((u16 *) ((sp1C - (-(var_sl * 4))) + 0x52)))
          {
            func_080E59BC(sp1C, sp20, 0, var_sl, sp28);
            func_080ACDA8(sp28 + 0, 2, 0);
          }
          else
          {
            new_var112 = (new_var263, 0);
            do
            {
            }
            while (new_var112);

            if (1 != 0U)

            func_08098BB4(0x080014CB);



            if (new_var17 && new_var17)
            {
            }




          }
          if ((!sp2C) && (!sp2C))
          {
          }
          func_080972C8();
        }
        new_var248 = (*(new_var19 = inline_fn23456789(sp58)) = (s16) ((int) (*((u8 *) (((0x087A1DC6 ^ 0)) + ((s8 *) var_sl))))));
        sp54 = var_sl;
      }
      func_080ED17C(1);
      if ((0x40 & (*((u16 *) 0x03006034))) && (var_sl != 0))
      {
        if (var_r0 != 0)

        temp_r5_2 = temp_r5_2;
        var_sl = (u32) (((u8) (var_sl - 1)) ^ 0);
        new_var122 = (struct S087B2524 *) D_087B2524;
        temp_r5_2 += 0;
        func_08092E84(0x40);
      }
      if ((0x80 & (*((u16 *) 0x03006034))) && (var_sl <= ((6U - (-1)) - 1)))
      {
        var_sl = (u32) ((u8) (1 + var_sl));
        func_08092E84(0x40);
      }
      if (new_var388 = 0)

      sp60 = sp60 + 0;
    }
    while (!(3 & (*((u16 *) 0x0300000E))));
    func_08092E84(0x3F);
    temp_r0_3 = temp_r0_3;
    func_08094554(sp58);
    func_08094554(sp38);
    new_var150 = (new_var102 = (!new_var114));
    if ((*new_var282) && (!new_var114))
    {
      if (var_r0_4)
      {
      }
    }
    func_08098BB4(0x080014D0);
    var_r7 = 0x1100;
    temp_r1_2 = sp28;
    if (((!temp_r1_2) && (!sp28)) != 0)

    if ((var_r5_6 && var_r5_6) && var_r5_6)
    {
    }
    goto block_306;
    new_var242 = 0;
    new_var361 = 0x087AF5F8;

  case 0x1100:
    func_08098BB4(0x08000F56);
    func_08098BB4(0x08000F0D);
    func_080AC214(3, 0);
    new_var44 = 7;
    func_080AC3B8(5, 0 ^ 0, 0);
    p716 = func_0809716C(3);
    *((u8 *) (((s8 *) p716) + 0x14)) = (u8) sp48;
    *((u8 *) (((s8 *) p716) + 0x16)) = (u8) sp44;
    p716 = func_0809716C(5);
    *((u8 *) (((s8 *) p716) + 0x14)) = (u8) sp50;
    *((u8 *) (((s8 *) p716) + 0x16)) = (u8) sp4C;
    *sp2C = (*sp2C) & 0xFFFDFFFF;
    *sp30 &= 0xFFFDFFFF;
    var_r7 = 0x1010;
    goto block_306;

  case 0x2000:
    if (sp38 != 0U)
    {


    }
    sp40 = func_08094484(0x08359850, 0x0835985C ^ 0, 0, 0x9C, 0x20, 0 * var_r2, 0, 8, 0);
    var_r7 = 0x2010;
    goto block_306;
    if ((new_var266 && new_var266) && new_var266)

    new_var229 = new_var7;

  case 0x2010:

    temp_r0_9 = D_02032273[(s32) sp4C] << 6;
    sp20 = (void *) (temp_r0_9 + ((s32) (new_var505 = (u16 *) D_02027378)));
    func_0809A9C8(*((u8 *) sp20), 0, 0, 0, 0, 0x02002880);
    p30 = ((u8 *) sp20) + new_var452;
    func_0809844C(*p30, 2, 0, 0xA, (k6 = 6), (k11 = 0xB), 8);
    func_0809844C(*((s32 *) (((u8 *) sp20) + 4)), 8, 0, 0xA, k6, (k5 = 5), 0xA);
    func_0809844C(D_087B77C8[*p30], 8, 0, 0xA, k6, k5, k11);
    func_080986B4(8);
    func_080981F0(D_087EDD54[((struct S70 *) (new_var505 = (u16 *) (((u8 *) new_var505) - 0x5A94)))[*(((u8 *) sp20) + 1)].f4], 0, 8, 0, 0);
    func_080ACCC4(8, sp50);
    func_08098BB4(0x08000FA2);
    sp4C = (void *) D_0200A880;
    sp50 = (s32) D_0200A881;
    switch (D_0200A882)
    {
    case 0:
      if (0x200 & D_0200A884)
      {
        func_08094554(sp40);
        func_080971AC(4);
        func_08092E84(0x41);
        var_r7 = 0x1000;
      }
      new_var100 = (temp_r5 = var_sl);
      goto block_306;

    case 1:
      new_var = (*((u16 *) (((u8 *) sp20) + 2))) & 0xFFFE;
      *((u16 *) (((u8 *) sp20) + 2)) = (u16) new_var;
      func_08098BB4(0x08000FA6);
      *sp2C |= 0x20000;
      *sp30 |= 0x20000;
      var_r7 = 0x2020;
      goto block_306;

    case 2:
      func_08094554(sp40);
      func_08094554(sp2C);
      func_08094554(sp30);
      func_080ACBA0(8);
      func_08098BB4(new_var444);
      var_done_flag = 1;
      goto block_306;

    }

    break;


  case 0x2020:
    func_08098BB4(0x08001558);
    new_var4 = (s8 *) sp20;
    new_var177 = (s8 *) sp1C;
    new_var52 = 4;
    new_var64 = sp20;
    new_var299 = (s32 *) (((s8 *) sp20) + 4);
    new_var4 = new_var4;
    new_var325 = (u8 *) (((s8 *) new_var64) - (-0));
    new_var174 = (s8 *) sp20;
    new_var176 = -new_var361;
    new_var4 += 0x34;
    func_080981F0(func_080E7B64(*new_var325), 0, 1 ^ 0, 0 & 0xFFFFFFFF, 0);
  dummy_label_491263:
    ;

    new_var326 = (s16 *) (0x36 + new_var174);
    new_var271 = &(*(new_var33 = new_var326));
    new_var129 = (float) new_var176;
    func_0809844C(*((s16 *) new_var4), 3, 0, new_var395, 0, 8, 1);
    func_0809844C(*new_var271, 3, 0, new_var395, 0, 8, 2);
    new_var101 = sp20;
    if (0 != 0)

    new_var333 = (s16 *) (((s8 *) sp1C) + 0x48);
    new_var298 = 0x30;
    new_var302 = (s8 *) sp20;
    new_var302 = new_var302;
    new_var302 = new_var302 + 0x3C;
    func_0809844C(*((s16 *) new_var302), 3, ((0 & 0xFFFFFFFF) & 0xFFFFFFFF) & 0xFFFFFFFF, new_var395, 0, 8, 3);
    new_var108 = (s8 *) sp20;
    new_var108 -= -(0x38 & 0xFF);
    func_0809844C(*((s16 *) new_var108), 3, 0, new_var110, 0, 8, 4);
    func_0809844C(*((s16 *) (new_var101 + 0x3A)), 3, temp_r1_2 * (0 * 0), new_var395, 0, 8, 5);
    new_var244 = (s8 *) sp20;
    new_var244 = new_var244 + 0x30;
    new_var246 = (u8 *) (((s8 *) sp20) + new_var298);
    func_0809844C((s16) (*((u8 *) new_var244)), 2, 0, (0, new_var8), (unsigned long) 0, 0xB, 7);
    func_0809844C(*new_var299, 8, 0, new_var8, 0, 5 ^ 0, 8);
    new_var241 = new_var8;
    {
      u8 *tblL;
      tblL = (u8 *) 0x087B77C8;
      asm volatile("" : "+r"(tblL));
      func_0809844C(*((s32 *) (((0, (s8 *) ((2 * (new_var166 = *new_var246)) * (2 & 0xFFFF)))) + ((s32) tblL))), 8, 0, new_var241, 0, 5, 9);
    }
    new_var65 = 0x31;
    new_var78 = 0xFF;
    new_var455 = 0x087EE158;
    new_var284 = 0;
    new_var154 = new_var455;
    func_080981F0(*((s32 *) (((s8 *) (2 * ((*((u8 *) (((s8 *) sp20) + new_var65))) * 2))) + new_var154)), 0, 0, 0xD - func_08098B58(*((s32 *) (((0, new_var455)) + ((s8 *) ((*((u8 *) (sp20 + 0x31))) * (4 & new_var78)))))), 0xB);
    new_var118 = 0x087A1F30;
    {
      u8 r129; s32 k13f;
      r129 = func_08098B58(*((s32 *) (((s8 *) ((0, (2 * (*((u8 *) (((s8 *) sp20) + 0x32)))) * 2))) + 0x087A1F30)));
      k13f = 0xD;
      asm volatile("" : "+r"(k13f));
      n13 = k13f - r129;
    }
    func_080981F0(*((s32 *) (((s8 *) (2 * (((0, *((u8 *) (((s8 *) sp20) + 0x32)))) * 2))) + new_var118)), 0, 0, n13, ({ register s32 a13 asm("r1"); a13 = 0xD; asm volatile("" : "+r"(a13)); a13; }));
  dummy_label_323292:
    ;

    var_sl = 0;
    var_r5_6 = 1;
    sp54 = 1;
    func_080ACB5C(8);
    var_r7 = 0x2025;
    goto block_306;
    goto block_235;
    if (temp_r1_6)


    new_var259 = sp50 && sp50;
    ;

  case 0x2025:
    sp58 = func_08094484(0x080ED830, 0x080ED864, 0, 0, (s32) (*((u8 *) (new_var363 = 0x087A1DF0 + ((s8 *) var_sl)))), 0x3EE, 0xF & 0xFFFFFFFF, 0x20, 0);
    sp34 = func_08094484(0x08106140, 0x0810614C, 0, 0, 0x88, 0x3B7, 0xF, (k8v2 = 8), 0);
    asm volatile("" :: "r"(k8v2));
    asm volatile("" :: "r"(k8v2));
    new_var283 = 0xD;
    new_var304 = 0x08105A20;
    if (!new_var206)
    {
    }
    {
      u32 a1v;
      a1v = ({ register u32 a1p asm("r1"); a1p = 0x08105A2C; asm volatile("" : "+r"(a1p)); a1p; });
      sp38 = func_08094484(new_var304, a1v, new_var283 * (1 * 0), 0xD8, (k152v = 0x98), (new_var262 = 0x343), 0xF, k8v2, 0 * (sp5C == 0));
    }
    asm volatile("" :: "r"(k8v2));
    asm volatile("" :: "r"(k8v2));
    asm volatile("" :: "r"(k152v));
    sp3C = func_08094484(0x08105A70, 0x08105A7C, 0, 0xA8, k152v, ({ register s32 a6b asm("r2"); a6b = 0x346; asm volatile("" : "+r"(a6b)); a6b; }), 0xF, k8v2, 0);
    var_r7 = 0x2030;
    new_var21 = new_var21;
    new_var21 = new_var21 - (-0);
    if (!var_r4_4)
    {
    }
    goto block_306;

  case 0x2030:
    func_08096F3C();
    do
    {
      temp_r0_11 = 0xFFFFFFFF;
      if (var_sl != ((long long) sp54))
      {
        u8 *tblG;
        tblG = (u8 *) 0x087A1DD0;
        asm volatile("" : "+r"(tblG));
        func_08098BB4(*((s32 *) (((2 * var_sl) * 2) + ((s32) tblG))));
        func_080972C8();
        var_r7 = 0x1000;
        new_var181 = &(*((u8 *) (((s8 *) var_sl) + 0x087A1DF0)));
        *inline_fn23456789(sp58) = (s16) (*new_var181);
        sp54 = var_sl;
      }
      func_080ED17C(1);
      if (((0, ((0x40 & 0xFFFF) ^ (((((0 & temp_r0_11) & temp_r0_11) & temp_r0_11) & temp_r0_11) & temp_r0_11)) & (*((u16 *) 0x03006034)))) && (0 != var_sl))
      {
        var_sl = (u32) ((u8) (var_sl - 1));
        func_08092E84(0x40);
      }
      var_r5 = 0;
      if ((0x80 & (*((u16 *) 0x03006034))) && (var_sl <= 6U))
      {
        var_sl = (u8) (var_sl + 1);

        var_sl = var_sl & 0xFFFFu;



        func_08092E84(new_var121 = 0x40);
      }
    }
    while (!(0xB & (*((u16 *) 0x0300000E))));
    func_08094554(sp58);
    if (!sp50)
    {
    }
    func_08094554(sp34);
    func_08094554(sp38);
    new_var320 = &new_var111;
    func_08094554(sp3C);
    ;
    if ((1 & (*((u16 *) 0x0300000E))) != 0)
    {
      func_08092E84(0x3E);
      var_r7 = 0x2040;
    }
    else
    {
      if (D_087B2524)
      {
      }
      if ((2 ^ 0) & ((long) (*((u16 *) 0x0300000E))))
      {
        goto block_234;
      }
      else
      {
        if (1 != 0)

        func_08092E84(0x3E);
        var_r7 = 0x3000;
      }






    }
    goto block_306;
    sp64 = (*new_var320) & 0xFF;
    new_var280 = 7;

  case 0x2040:
    p716 = func_0809716C(0);
    *((s32 *) (((s8 *) p716) + 0)) |= 0x80;
    func_08098834(0);
    *((s8 *) (((s8 *) p716) + 0x16)) = 0;
    *((s8 *) (((s8 *) p716) + 0x14)) = 0;
    *((s8 *) (((s8 *) p716) + 0x15)) = 0;
    new_var129 = 0x17;
    *((u8 *) (((s8 *) p716) + new_var129)) = 0xFF;
    func_08098BB4(0x08001848);
    func_080B67B8(sp20);
    new_var31 = &(*((u8 *) 0x02032487));
    asm volatile("" : "+r"(new_var31));
    temp_r1_2 = *new_var31;
    if ((temp_r1_2 == 0) ^ 0)
    {
      func_080981F0(0x08106380, 0, 0, 0, (s32) temp_r1_2);
      func_080986B4(2);
      new_var253 = !var_sl;
      if (new_var253)
      {
      }
      func_080972C8();
      var_r4_2 = sp20 + ((unsigned int) 0x31);
    }
    else
    {
      ;
      var_r4_2 = sp20;
      new_var182 = 0;
      {
        register u32 k189 asm("r5");
        k189 = 0;
        var_r4_2 += 0x31;
        if (sp5C)
        {
        }
        if (k189 < ((u32) (*((volatile u8 *) new_var31))))
        {
          do
          {
            var_r6_2 = var_r2;
            new_var243 = &new_var182;
            if (1 != 0)
            {
              new_var394 = 0x02030564;
              func_080E7664(D_02032473[k189], D_0203247D[k189], new_var394);
              if (*new_var243)
              {
              }
              func_080988C8(0, new_var394);
            }
            k189 += 1;
          }
          while (k189 < (((u32) (*((u8 *) 0x02032487)))));
        }
        asm volatile("" :: "r"(var_r4_2));

        ;
      }
      var_sl = 0;
      temp_r0_19 += (unsigned char) 0;
    }
    temp_r3 = *var_r4_2;
    new_var87 = &(*var_r4_2);
    if ((*new_var87) != 0)
    {
      new_var36 = new_var36;

      new_var167 = 0xD8;
      sp38 = func_08094484(0x08105A20, 0x08105A2C, 0, new_var167, 0x98 ^ 0, 0x343, 0xF, 8, 0);
      sp3C = func_08094484(0x08105A70, 0x08105A7C, 0, 0xA8, 0x98, 0x346, 0xF, 8, 0);

    }
    else
    {
      sp38 = (new_var172 = func_08094484(0x08105AC0, 0x08105ACC, 0, 0xD0, 0x98, 0x34C, 0xF, 8, (s32) temp_r3));
    }
    new_var41 = (new_var143 = !sp20);
    if (((!new_var281) && (!new_var281)) && (!new_var281))
    {
    }
    var_r7 = 0x2050;
    goto block_306;
    if ((double) 0, ((!1) && (!1)) && (!1))

    new_var286 = (new_var60 = new_var169);

  case 0x2050:
    new_var217 = *((u8 *) 0x02032487);
    new_var365 = &(*((u8 *) (((s8 *) sp20) - (-0x31))));
    if (new_var217 != 0)
    {
      kFFFF = 0x02030564;
      asm volatile("" : "+r"(kFFFF));
      do
      {
        func_080986B4(2);
        new_var272 = D_02032473[var_sl];
        func_080E77A4(new_var272, D_0203247D[var_sl], kFFFF);
        func_080981F0(kFFFF, 0, 2, 0, 0);
        func_080972C8();
        new_var32 = ((((var_sl * 2) + 1) * 2) * 2) * 2;
        *inline_fn23456789(sp58) = (s16) new_var32;
        func_08098BB4(0x08001856);
        var_sl = (u32) D_0200A880;
        temp_r1_3 = D_0200A882;
        if (temp_r1_3 == 0)
        {
          continue;
        }
        if ((temp_r1_3 != 1) || ((*new_var365) == 0))
        {
          if ((temp_r1_3 == 2) || ((*new_var365) == 0))
          {
            func_08098BB4(0x08001B09);
            func_08094554(sp38);
            if ((*new_var365) != 0)
            {
              new_var231 = sp3C;
              func_08094554(new_var231);
            }
            goto block_235;
          }
          continue;
        }
        goto exit_2050;
      }
      while (1);
    }
    else
    {
      do
      {
        func_080ED17C(1);
      }
      while ((3 & (*((u16 *) 0x0300000E))) == 0U);
      if ((1 & (*((u16 *) 0x0300000E))) && ((*new_var365) != 0))
      {
        func_08094554(sp38);
        func_08094554(sp3C);
        func_08092E84(0x3E);
        var_r7 = 0x2060;
      }
      else
      {
        func_08098BB4(0x08001B09);
        func_08094554(sp38);
        if ((*new_var365) != 0)
        {
          func_08094554(sp3C);
        }
        func_08092E84(0x3F);
        var_r7 = 0x2100;
      }
    }
    goto block_306;

  case 0x2060:

    if (!new_var203)
    {
    }
    new_var457 = !D_0200A884;
    if (new_var457)
    {
    }
    if (new_var450)
    {
    }
    goto dummy_label_342081;
  dummy_label_342081:
    ;

    var_r5_3 += 0;
    goto dummy_label_518998;
  dummy_label_518998:
    ;

    if (!new_var384)
    {
    }




    ;
    if (!new_var112)
    {
    }
    if (1 ^ 0)
    {
      ;

      do
      {
      }
      while ((0 != 0) ^ 0);
      p716 = func_0809716C(0);

      ;

      ;

      var_r7 = 0x3005;







      new_var457 = !D_0200A884;


    }
    new_var148 = new_var286;
    if (!new_var9)
    {
    }
    new_var268 = new_var472;
    if (temp_r5 != 0)
    {
    }
    ;
  dummy_label_890384:
    ;

    *p716 = (*p716) & (~0x80);
    new_var281 = !new_var7;
    new_var403 = 0x2E & 0xFF;
    new_var403 = (new_var403 & ((0, 0xFF))) & 0xFF;
    var_r2 = (var_r5_3 = 1);
    new_var79 = sp20;
    new_var358 = ((new_var403 & 0xFF) & 0xFF) & 0xFF;
    func_08098BB4(0x0800185A);
    new_var155 = inline_fn2345678910111213(new_var79) + 0x31;
    new_var131 = (new_var42 = (u8 *) 0x087A1E24);
    new_var470 = (u8 *) new_var155;
    new_var453 = ((0, (({ register s32 m453 asm("r1"); m453 = (4 * (*new_var470)) * 13; asm volatile("" : "+r"(m453)); m453 += (({ register s32 pb453 asm("r0"); pb453 = 0x020280B8; asm volatile("" : "+r"(pb453)); pb453; })); asm volatile("" : "+r"(m453)); m453; }))));
    new_var446 = (new_var174 = ((s8 *) sp24) + 0);
    sp24 = (new_var139 = new_var453);
    {
      u8 *tblI;
      tblI = (u8 *) 0x087EE158;
      asm volatile("" : "+r"(tblI));
      asm volatile("" ::: "memory");
      func_080981F0(*((s32 *) (((*((u8 *) sp24)) * 4) + ((s32) tblI))), 0, 1 ^ 0, 0, 0);
    }
    ;
    new_var432 = 0xFF;
    func_0809844C(*((s16 *) (0x2A + ((s8 *) sp24))), 3, new_var284, new_var395, 0, (unsigned long) 8, ({ register s32 a239 asm("r1"); a239 = new_var239; asm volatile("" : "+r"(a239)); a239; }));
    new_var406 = ((s8 *) new_var139) - (-0x2C);
    goto dummy_label_514035;
  dummy_label_514035:
    ;

    if ((new_var281 && (!new_var266)) && (!new_var229))
    {
    }
    func_0809844C(*((0, (s16 *) new_var406)), 3, 0, (unsigned long) new_var395, 0, 8, 2);
    ;
    new_var227 = 0;
    temp_r0_13 = new_var266;
    new_var142 = new_var160;
    new_var48 = new_var48;
    new_var48 = (s8 *) sp24;
    new_var413 = 0x080018AD ^ ((0, 0));
    new_var48 = (0, new_var48 + 0);
    new_var372 = sp24;
    ;
    new_var253 = new_var8;
    new_var437 = 0xA8;
    func_0809844C(*((s16 *) (((s8 *) new_var372) + new_var358)), (0, 3), 0, new_var395, new_var227, 8, 3);
    var_r4_3 = var_r4_3 + ((2 * ((0 ^ 0) * 2)) * 0);
    func_0809844C(*((s16 *) (((s8 *) sp24) + 0x30)), 3, 0, new_var395, 0, 8, 4);
    new_var17 = (temp_r0_11 = -0x087AF5F8);
    new_var176 = (0, new_var17);
    func_0809844C(*((s16 *) ((0x32 ^ 0) + ((s8 *) sp24))), 3, 0, new_var395, 0, 8, 5);
    new_var339 = (new_var85 = ((s8 *) sp24) + 0x28);
    pad5 = .0 != (new_var253 && new_var253);
    new_var112 = !new_var142;
    new_var330 = 0x346;
    func_0809844C((s16) (*((0, new_var85))), 2, 1 * 0, new_var162, 0, 0xB, 7);
    new_var241 = new_var8 * 0;
    new_var252 = (u8 *) sp24;
    new_var287 = new_var48;
    if (pad5)
    {
    }
    var_r7_2 = (var_r5 * 2) - (-1);
    new_var399 = (u8 *) sp24;
    if ((*new_var399) == 1)
    {
      func_08098BB4(0x080018AD);
      var_r5_3 = 0;
      ptr2060 = new_var399 + 2;
      do
      {
        var_r6_2 = 1;
        if (var_r5_3 != (*((u8 *) (((s8 *) sp24) + 1))))
        {
          var_r6_2 = 0;
        }
        switch (var_r5_3)
        {
        case 0:
          var_r4_3 = var_r5_3 + 10;
          func_080981F0(0x0810638C, var_r6_2, 0, 0, (s16) var_r4_3);
          break;

        case 1:
          func_080981F0(0x08106394, var_r6_2, 0, 0, 0xB);
          var_r4_3 = 0xB;
          break;

        case 2:
          func_080981F0(0x0810639C, var_r6_2, 0, 0, 0xC);
          var_r4_3 = 0xC;
          break;

        case 3:
          func_080981F0(0x081063A4, var_r6_2, 0, 0, 0xD);
          var_r4_3 = 0xD;
          break;

        default:
          var_r4_3 = var_r5_3 + 10;
          break;

        }

        new_var16 = &ptr2060[var_r5_3];
        func_0809844C(((s16) (*new_var16)) ^ 0, 2, var_r6_2, new_var8, new_var263, 0xB, (s16) var_r4_3);
      }
      while ((unsigned short) ((var_r5_3 += 1) <= 3U));
    }
    var_r2 = var_r7_2;
    { register s32 zsl asm("r1"); zsl = 0; asm volatile("" : "+r"(zsl)); var_sl = zsl; }
    { register s32 one2 asm("r2"); one2 = 1; asm volatile("" : "+r"(one2)); sp54 = one2; }
    new_var234 = *new_var131;
    new_var467 = ((0 & 0xFFFFFFFF) != 1) != 0U;
    new_var215 = func_08094484(0x080ED830, 0x080ED864, 0 ^ 0, (0, 0), (s32) (new_var159 = new_var234), 0x3EE, (new_var318 = 0xF), 0x20, ({ register s32 a8s asm("r3"); a8s = var_sl; asm volatile("" : "+r"(a8s)); a8s; }));
    new_var220 = ((s8 *) sp24) - (-0);
    new_var159 = 1;
    if (new_var467)
    {
      sp58 = (new_var311 = new_var215);
      new_var415 = (new_var69 = new_var266);
      sp38 = func_08094484(0x08105A20, 0x08105A2C, (0, 3 * 0), 0xD8, 0x98, ((0, 0x343)) & 0xFFFFFFFFu, new_var318, (k8v = ({ register s32 a8 asm("r4"); a8 = 8; asm volatile("" : "+r"(a8)); a8; })), var_sl);
      if (sp1C)
      {
      }
      new_var222 = 0;
      sp3C = func_08094484(0x08105A70, 0x08105A7C, ((((((new_var340 & 0xFF) & 0xFF) & new_var432) * new_var222) & 0xFFFFu) * 2) * 2, new_var437, 0x98, new_var330, new_var318, k8v, var_sl);
      new_var230 = new_var415;
      if (new_var194)

      ;

      new_var28 = (s8 *) sp24;
      new_var28 = new_var28;
      new_var28 = new_var28;
      new_var28 = 1 + new_var28;
      ;
    }
    tblC = (u8 *) 0x087AF5F8;
    asm volatile("" : "+r"(tblC));
    new_var43 = *((u8 *) new_var220);
    new_var43 = new_var43 * 2;
    new_var186 = new_var43;
    new_var129 = new_var176;
    new_var366 = (u8 *) new_var28;
    temp_r1_5 = (*((u16 *) (new_var43 + ((s32) tblC))));
    var_r4 = var_r2;
    var_r2_3 = 0 ^ 0;
    if (((*((u16 *) (new_var43 + ((s32) tblC)))) == 0x4B) != (0x081063CC * 0))
    {
      var_r7 = 0x2100;
      var_r2_3 = *new_var366;
      ;
      if (((new_var69 && new_var230) & 0xFF) && temp_r0_13)
      {
      }

    }
    func_0809A9C8(temp_r1_5, 0, (short) var_r2_3, 0, var_sl, 0x02002880);
    var_r7 = 0x2070;
    goto block_306;
    new_var451 = sp20;


  case 0x2070:
    ;
    func_08096F3C();
    do
    {
      if (var_sl != sp54)
      {
        tblD = ({ register u8 *td asm("r1"); td = (u8 *) 0x087A1DF8; asm volatile("" : "+r"(td)); td; });
        new_var152 = var_sl;
        new_var152 = new_var152 * 4;
        new_var152 += (s32) tblD;
        new_var314 = (s8 *) new_var152;
        new_var192 = new_var314;

        new_var7 = new_var192;
        new_var249 = (s16 *) (((s8 *) sp1C) + new_var395);
        new_var319 = (s32 *) new_var7;
        func_08098BB4(*new_var319);
        do
        {
          if (1 != 0)
          {


          }
        }
        while ((*new_var249) * (4 * 0));

        if (new_var8 != 0)
        {
        }
        func_080972C8();
        new_var145 = new_var145;
        *inline_fn23456789(sp58) = (s16) (*((u8 *) (((s8 *) var_sl) + 0x087A1E24)));
        sp54 = var_sl;
      }
      func_080ED17C(1);

      new_var126 = (s8 *) sp24;
      new_var126 = new_var126 + 0;
      ;
      new_var251 = 1;
      new_var124 = (u8 *) new_var126;
      var_r2 = 0x03006034;
      if ((0x40 & (*((u16 *) var_r2))) && (var_sl != 0))
      {
        var_sl = (u32) ((u8) (var_sl - new_var251));
        func_08092E84(0x40);
      }
      new_var62 = *(new_var301 = (u16 *) 0x03006034);
      new_var26 = 0xFFFFFFFFFFFFFFFF & 0x80;
      if (!var_r6_2)

      new_var274 = new_var123;
      new_var26 = new_var26 & new_var62;
      new_var104 = 9;
      if (new_var26 != 0)
      {
        if ((*((u8 *) sp24)) == 1)
        {
          var_r5 = 0;
          if (((s32) var_sl) > new_var104)
          {

            new_var180 = new_var18;
            if (1 != new_var180)
            {
            }

          }
          else
          {


            goto block_229;
          }
        }
        else
        if ((long long) (((s32) var_sl) <= ((4 + 1) - 1)))
        {
        block_229:
          var_sl = (u32) ((u8) (var_sl + 1));

          func_08092E84(0x40);

          if (new_var274 != new_var242)
          {
            if (temp_r0_19)



            if (1 != 0U)
            {
            }


          }
        }
      }
    }
    while ((3 & (*((u16 *) 0x0300000E))) == ((7 * 0) ^ 0));
    func_08094554(sp58);
    func_08094554(sp38);
    func_08094554(sp3C);
    if ((1 & (*((u16 *) 0x0300000E))) != 0)
    {
      new_var212 = 0x3E;

      func_08092E84(new_var212);

      var_r7 = 0x2080;
    }
    else
    {
      new_var140 = &(*((u8 *) 0x02032492));
    block_234:
      func_08098BB4(0x08001B09);
    dummy_label_157951:
      ;

    block_235:
      func_08092E84(0x3F);
      var_r7 = 0x2100;
    }
    goto dummy_label_784397;
  dummy_label_784397:
    ;

    if (!new_var416)
    {
    }
    goto block_306;
    new_var169 = ((s8 *) (&sp14)) + 3;
    new_var307 = !new_var416;

  case 0x2080:
    p716 = func_0809716C(0);
    *((s32 *) (((s8 *) p716) + 0)) |= 0x80;
    func_08098834(0);
    new_var38 = (new_var307 && (!new_var416)) ^ 0;
    *((s8 *) (((s8 *) p716) + 0x15)) = (*((s8 *) (((s8 *) p716) + 0x14)) = (*((s8 *) (((s8 *) p716) + 0x16)) = 0));
    new_var392 = new_var416;
    new_var135 = (new_var38 ^ 0) && (!new_var392);
    new_var267 = p716;
    *((u8 *) (((s8 *) p716) + 0x17)) = 0xFF;
    *((s8 *) (((s8 *) p716) + 0x12)) = 0;
    func_08098BB4(0x08001848);
    func_080B6810(sp24);
    t16c = *((u8 *) 0x02032492);
    if (((long long) t16c) == 0)
    {
      func_080981F0(0x08106380, 0, 0, 0, (s32) t16c);
      func_080986B4(2);
      func_080972C8();
    }
    else
    {
      var_r5_3 = 0;
      if (((u32) var_r5_3) < ((u32) (*((volatile u8 *) 0x02032492))))
      {
        tbl410 = (s8 *) 0x087EF410;
        do
        {
          { register u8 *pT asm("r0"); pT = (u8 *) 0x02032488; asm volatile("" : "+r"(pT));
            new_var6 = (s32 *) ((2 * ((*((u8 *)(var_r5_3 + ((s32) pT)))) * 2)) + ((s32) tbl410)); }
          func_080988C8(0, *new_var6);
          var_r5_3 += 1;
        }
        while (((u32) var_r5_3) < ((u32) (*((volatile u8 *) 0x02032492))));
      }

      var_sl = new_var263;
      var_sl = var_sl;
    }
    sp38 = (s32 *) func_08094484(0x08105AC0, 0x08105ACC, 0, (0, 0xD0), 0x98, 0x34C, 0xF, 8, 0);
    ;
    var_r7 = 0x2090;
    goto block_306;

  case 0x2090:
    if ((long long) ((*((u8 *) 0x02032492)) != (new_var88 = 0)))
    {
      tbl410 = (s8 *) 0x087EF478;

      do
      {
        func_080986B4(2);
        new_var39 = inline_fn2(((s8 *) var_sl) - (-0x02032488));
        func_080981F0(*((s32 *) (((s8 *) new_var39) + ((s32) tbl410))), 0, 2, 0, 0);
        func_080972C8();
      dummy_label_412773:
        ;

        *((s16 *) (((s8 *) sp58) + 6)) = (temp_r1_3 = ((var_sl * 2) + 1) * 8);
        if (new_var8 && new_var8)
        {
        }
        func_08098BB4(0x08001856);
        var_sl = (u32) D_0200A880;

        if (var_sl == 0U)
        {
        }
      }
      while (!D_0200A882);

    }
    else
    {
      do
      {
        new_var43 = new_var43;
        func_080ED17C(1);
      dummy_label_180400:
        ;

      }
      while (!(3 & (*((u16 *) 0x0300000E))));
    }
    func_08092E84(0x3F);
    if (((!new_var143) && (!new_var143)) && (!new_var143))
    {
    }
    func_08098BB4(0x08001B09);
    func_08094554(sp38);
    var_r7 = 0x2100;
    goto block_306;

  case 0x2100:
    func_08098BB4(0x08000F0D);
    func_08098BB4(0x08000F56);
    func_080AC214(3, 0);
    func_080AC3B8(5, 0, 0);
    p716 = func_0809716C(3);
    *((u8 *) (((s8 *) p716) + 0x14)) = (u8) sp48;
    *((u8 *) (((s8 *) p716) + 0x16)) = (u8) sp44;
    p716 = func_0809716C(5);
    *((u8 *) (((s8 *) p716) + 0x14)) = (u8) sp50;
    *((u8 *) (((s8 *) p716) + 0x16)) = (u8) sp4C;
    *sp2C &= 0xFFFDFFFF;
    *sp30 &= 0xFFFDFFFF;
    var_r7 = 0x2010;
    goto block_306;

  case 0x3000:
    if (temp_r0_17)
    {


    }
    goto dummy_label_677221;
    func_08094554(sp38);
  dummy_label_677221:
    ;

    func_08098BB4(0x08001B10);
    func_080981F0(func_080E7B64(*((u8 *) (((s8 *) sp20) + (0 * 0)))), 0, 3, 0, 0);
    *((s16 *) ((4 & 0xFFFFFFFF) + ((s8 *) sp40))) = 8;
    *inline_fn23456789(sp40) = 0x20;
  block_305:
    var_r7 = 0x3005;

    if (1 != 0U)
    {
      goto block_306;
      ;
    }
    ;
    new_var38 = 3;
    ;

  case 0x3005:
    sp34 = func_08094484(0x08105A20, 0x08105A2C, 0, new_var167, 0x98, 0x343, 0xF, 8, 0);
    new_var221 = 0x3010;
    t16d = 0xFFFF;
    t16d = (((5U & 0xFFFF) & t16d) & 0xFFFF) & 0xFFFF;
  block_257:
    var_r7 = new_var221;

    goto block_306;
    new_var274 = (((t16d & 0xFFFF) & 0xFFFF) & 0xFFFF) & 0xFFFF;
    new_var89 = (new_var274 + (-1)) - (-1);



  case 0x3010:
    ta3010 = ((s8 *) sp20) + 0x32;
    tv3010 = *((u8 *) ta3010);
    new_var158 = (u8 *) ta3010;
    asm volatile("" :: "r"(ta3010));
    if (((u32) tv3010) <= ((4U + 1) - 1))
    {
      var_r0 = inline_fn23456789101112131415(2);
      var_r0 = var_r0;
      func_0809844C(inline_fn234(((s8 *) sp20) + 0x26), var_r0 & 0xFFFFFFFF, 0, new_var395, 3, 0xB, 3);
      new_var390 = (s8 *) sp20;
      func_0809844C((s16) (*((u16 *) (new_var390 + 0x28))), 2, 0, new_var395, 3, 0xB, 4);
      func_0809844C((s16) (*((u16 *) (((s8 *) sp20) + 0x2E))), 2, 0, new_var395, 3, (t16e = 0xB) ^ 0, 5);
      new_var154 = 0;
      new_var171 = (s8 *) sp20;
      if (sp2C)
      {
      }
      new_var171 = new_var171 + 0x2A;
      new_var364 = (s8 *) sp20;
      func_0809844C(inline_fn234(new_var171), 2, 0, new_var395, 3, 0xB, 6 ^ ((2 * 0) & 0xFF));




      new_var98 = (u16 *) (new_var364 - (-0x2C));
      func_0809844C((s16) (*new_var98), 2, new_var154, new_var395, 3, 0xB, 7);
    }
    else
    {
      func_080981F0(0x081063AC, 32 * ((0 * 2) * 2), 3, 0xB, 3);
      func_080981F0(0x081063AC, 0 * 0, 3, 0xB, 4);
      func_080981F0(0x081063AC, 0, 3, new_var297, 5);

      func_080981F0(0x081063AC, 0, (3 & ((new_var250, 0xFF))) ^ 0, 0xB, 6);
      func_080981F0(0x081063AC, 0, 3, 0xB, 7);

    }
    {
      u8 *tblJ;
      tblJ = (u8 *) 0x087A1F30;
      asm volatile("" : "+r"(tblJ));
      t52b = func_08098B58(*((s32 *) (((*new_var158) * 4) + ((s32) tblJ))));
    }
    new_var94 += 0;
    func_080981F0(0x081061C4, 0, 3, 5, 0xC);
    var_r7 = 0x3000;
    ;
    var_r4_4 = t52b;
    if (((u32) var_r4_4) < (7U + 1))
    {
      do
      {


        func_08098248(0x081061C4, 0, 3);
        var_r4_4 = var_r4_4 + 1;
      }
      while (((u32) var_r4_4) <= 7U);
    }
    asm volatile("" :: "r"(t52b));
    {
      u8 *tblK;
      tblK = (u8 *) 0x087A1F30;
      asm volatile("" : "+r"(tblK));
      new_var195 = (s8 *) (2 * (2 * (*((volatile u8 *) new_var158))));
      func_08098248(*((s32 *) (new_var195 + ((s32) tblK))), 0, 3);
    }
    ;
    func_08098BB4(0x08001BCC);
    var_r7 = 0x3020;
    sp1C = sp1C + 0;
    goto block_306;

  case 0x3020:
    func_08098BB4(0x08001BC1);
    if ((D_0200A882 == 1) ^ 0)
    {
      ;
      temp_r0_17 = new_var143;
      new_var183 = 4;
      if (temp_r0_17)
      {
        if (p20)
        {
        }
      }
      if ((((((new_var265 = ((1)) & ((0, 0xFFFFFFFFFFFFFFFF))))))))
      {
        if (((u32) D_0200A880) <= 3U)
        {
          if (new_var170)
          {
          }
          p20 = sp20;
          new_var41 = 0x2A;
          goto dummy_label_857382;
        dummy_label_857382:
          ;

          new_var59 = (s8 *) p20;
          new_var228 = (u16 *) (p20 + 0x26);
          new_var59 = new_var59 + 0x28;
          *((u8 *) (((s8 *) sp20) + 0x32)) = D_0200A880;
          new_var300 = D_087B7958;
          ;
          new_var136 = (*((u8 *) (0x32 + (new_var224 = (s8 *) sp20)))) ^ 0;
          new_var158b = (s8 *) sp20;
          ;
          *new_var228 = *((u16 *) (new_var300 + (((new_var136 * (6 & 0xFFu)) * 2))));
          new_var194 = (var_r6 = (u16 *) new_var59);
          *new_var194 = *((u16 *) ((D_087B7958 + ((*((u8 *) (((s8 *) sp20) + 0x32))) * 0xC)) + 2));
          *((u16 *) (((s8 *) p20) + new_var41)) = *((u16 *) ((D_087B7958 + (3 * (4 * (*((u8 *) (((s8 *) sp20) + 0x32)))))) + 4));
          *((u16 *) (((s8 *) p20) - (-0x2C))) = *(new_var33 = (D_087B7958 + (2 * ((2 * (*((u8 *) (((s8 *) sp20) + 0x32)))) * 3))) + 6);
          ;
          if (var_r4 && var_r4)
          {
          }
          new_var292 = ((s8 *) p20) + 0x2E;
          ;
          new_var14 = *((u8 *) (new_var158b + 0x32));
          *new_var292 = *((u16 *) ((D_087B7958 + (6 * (2 * new_var14))) + (-((0, -8)))));
          goto block_257;
        }
      }
      if ((D_0200A880 ^ 0) == 4)
      {

        func_08094554(sp34);

        var_r7 = 0x3030;
      }
      else
      {
        *((u8 *) (((s8 *) sp20) + 0x32)) = D_0200A880;
        goto block_257;
      }
    }
    else
    {
      func_08098BB4(0x08001BC5);
      func_080981F0(0x081063B0, 0, 0, 5, 0xD);
      new_var261 = 0 != (0x20 * 0);
      new_var309 = 0x32;
      new_var313 = 0x087A1F30;
      new_var163 = (new_var163 = (s8 *) sp20);
      new_var163 += new_var309;
      new_var308 = (s16 *) (((s8 *) sp40) + 4);
      {
        u8 r256; s32 n13b;
        r256 = func_08098B58(*((s32 *) (((s8 *) (((new_var95 = (new_var255 = (temp_r0 = *((u8 *) (((s8 *) sp20) + 0x32))))) * 4) & 0xFFFFu)) + new_var313)));
        n13b = ({ register s32 k13h asm("r3"); k13h = 0xD; asm volatile("" : "+r"(k13h)); k13h; }) - r256;
        func_080981F0(*((s32 *) (((s8 *) ((2 * (*((u8 *) new_var163))) * 2)) - (-0x087A1F30))), 0, 0, n13b, 0xD);
      }
    dummy_label_700030:
      ;

      func_080972C8();
      temp_r1_2 = (*new_var308 = 0xFF & 0xFFFF);
      *((s16 *) (((s8 *) sp40) + 4)) = *new_var308;
      *((s16 *) (((s8 *) sp40) + 4)) = 0x9C & (*((s16 *) (((s8 *) sp40) + 4)));
      new_var255 = 0x2025;
      *inline_fn23456789(sp40) = 0x20;
      if (new_var263 != 0U)
      {
      }

      func_08094554(sp34);
      var_r7 = new_var255;
      if (new_var261)

      if (0 != 0)
      {
      }
    }
    goto block_306;

  case 0x3030:
    new_var512 = 0;
    var_sl = new_var512;
    var_r5_3 = 0;
    new_var510 = 0x080ED830;
    new_var511 = 0x080ED864;
    do
    {
      sp14[var_r5_3] = new_var512;
      var_r5_3 = var_r5_3 + 1;
      new_var145 = new_var277;
    dummy_label_710136:
      ;

    }
    while (var_r5_3 <= 5U);
    { register s32 t10 asm("r4"); t10 = 10; asm volatile("" : "+r"(t10)); sp5C = t10; }
    { register s32 t1 asm("r0"); t1 = 1; asm volatile("" : "+r"(t1)); sp60 = t1; }
    new_var35 = var_sl;
    new_var35 = new_var35;
    new_var35 = new_var35 << (2 ^ 0);
    do
    {
      new_var35 = new_var35;
      new_var35 = new_var35;
      new_var179 = 0x38;
      if (((!new_var392) && (!new_var416)) && (!new_var392))
      {
      }
      new_var35 <<= 1;
      sp58 = func_08094484(new_var510, new_var511, 0, new_var179, (s16) (new_var35 + ((short) 0x20)), 0x3EE, 0xF, 0x20, 0);
      ;
      sp34 = func_08094484(0x08105AFC, 0x08105B08, 0, 0x58, 0x78, 0x350, 0xF, 8, 0x20000 * 0);
      func_08098BB4(0x08001C02);
    }
    while (0 != 0);
    pad6 = 0x3040;
    var_r7 = (long) pad6;
    goto block_306;
    D_0200A884 += 0;
    new_var146 = &new_var99;

  case 0x3040:

    if (((!new_var183) && (!new_var183)) && (!new_var183))
    {
    }


    new_var454 = new_var145;
    if (!new_var214)
    {
    }

    ;
    new_var285 = new_var285;

    new_var132 = 0;
    new_var410 = sp24;
    new_var376 = &(*((u8 *) (new_var174 = ((s8 *) new_var410) + 0)));


    ;
    goto dummy_label_594221;
  dummy_label_594221:
    ;



    new_var396 = (new_var69 = new_var266);
    if (sp24)
    {
    }
    goto dummy_label_185612;
  dummy_label_185612:
    ;



    new_var358 = ((0, 0xFF)) & ((new_var403 & 0xFF) & 0xFF);


    new_var425 = (u16 *) 0x03006034;
    p3006 = new_var425;
    if (p3006)

    var_r4_3 = 0 * 0;
    var_r4_3 = var_r5_3 ^ ((sp60 != var_r4_3) * 0);


    do
    {
    }
    while (((0, *p3006)) * 0);
    new_var230 = new_var396;
    new_var277 += 0;
    var_r4 = 1;
    if ((!new_var112) && (!new_var112))
    {
    }




    new_var102 = 1 ^ 0;
    temp_r0_11 = temp_r0_11;
    ;


    if (!(new_var132 & 0xFFFFFFFFu))
    {
    }
    if (sp2C)
    {
    }






    goto dummy_label_633581;
  dummy_label_633581:
    ;

    new_var236 += 0;
    if (!new_var454)
    {
    }


    if ((var_r5 && var_r5) && var_r5)
    {
      new_var29 = new_var29;
    }
    new_var384 = 0xFFFFu;
    new_var238 = 0x081063C4;
    new_var419 = new_var286;
    func_08096F3C();
    p3006 = (u16 *) 0x03006034;
  loop_278:
    slx8v = var_sl << 3;
    asm volatile("" :: "r"(slx8v));
    if (sp60 != 0)
    {
      var_r5_6 = (var_r5_3 = (!p20) * 0);
      var_r4_5 = 0x30000;
      do
      {
        ;
        new_var197 = (0, &sp14);
        new_var356 = var_r5_3;
        func_0809844C((s16) (*new_var197)[new_var356], 2, 0, new_var395, 3, 0xB, ((s32) var_r4_5) >> 16);
        var_r4_5 = var_r4_5 + 0x10000;
      }
      while ((var_r5_3 += 1) < (4U + 1));
      new_var290 = sp54;
      func_080981F0(new_var238, (0, 2 * 0), 3, 0, new_var8);
      new_var285 = 0xC;
      func_0809844C(sp5C, 2, 0, new_var343 = new_var8, 3, new_var105, new_var8);
      new_var105 = new_var285;
      new_var19 = inline_fn23456789(sp58);
      if ((new_var290 ^ 0) != 0)
      {
      }
      func_080972C8();
      sp60 = 0;
    }

    *inline_fn2345678910((s8 *) inline_fn(sp58)) = (s16) (slx8v + 0x20);
    if (sp30)
    {
    }
    new_var402 = new_var279;
    func_080ED17C(1);
    new_var245 = (new_var245 = 0);
    new_var245 = (!new_var43) ^ new_var245;
    new_var41 = new_var41;
    new_var344 = (new_var347 = new_var143) & 0xFF;
    if (new_var245)
    {
    }
    new_var97 = (0xFFFFFFFF & (((1 & 0xFFFFFFFF) & 0xFFFFFFFF) & 0xFFFFFFFF)) & 0xFFFFFFFF;
    if ((0x40 & (*p3006)) && ((0 != var_sl) ^ 0))
    {
      var_sl = (u32) ((u8) ((var_sl - 1) & 0xFFu));

      func_08092E84(0x40);

    }
    if (((0x80 & 0xFFu) & (*p3006)) && (var_sl < ((3U & 0xFFFF) + 1)))
    {
      new_var35 <<= 1;
      if (new_var451)

      new_var192 += 0 & 0xFFFFFFFF;
    dummy_label_190839:
      ;

      if (((!(((u8) (((unsigned long) (var_sl - 1)) & (0xFFu ^ 0))) ^ (new_var8 * 0))) && (!((u32) ((u8) ((var_sl + (-1)) & 0xFFu))))) && (!(((u32) ((u8) ((var_sl - 1) & 0xFFu))) ^ (0 * (((0 * 17) * 15) * 72340172838076673)))))
      {
      }
      new_var347 = new_var347;
      var_sl = (u32) ((u8) (var_sl + 1));
      temp_r5 = *inline_fn23456789(new_var392);
      if (new_var178)
      {
      }
      func_08092E84(0x40);
    }
    new_var268 = new_var402;
    new_var386 = new_var384;
    new_var306 = (unsigned int) (new_var344 && new_var347);
    new_var459 = (s32) D_020218E4;
    if (((long long) (0x20 & ((unsigned short) ((*p3006) ^ 0)))) != ((0 != var_sl) * 0))
    {
      new_var385 = (((((((0, 0xFFFFFFFFFFFFFFFF)) & var_sl)))));
      temp_r1_7 = &sp14[0xFFFFFFFFFFFFFFFF & (((new_var385)))];
      temp_r0_18 = *((u8 *) temp_r1_7);
      if (((*((u8 *) temp_r1_7)) & 0xFFFFu) != 0)
      {
        new_var440 = (1 ^ 0) ^ 0;
        *(new_var315 = (u8 *) temp_r1_7) = ((u8) (temp_r0_18 - (new_var102 = new_var440))) ^ (2 * 0);
        sp5C = (s32) ((unsigned long) ((0, (u8) (sp5C + 1))));


        sp60 = 1;
        func_08092E84(0x40);
      }
    }
    new_var335 = 1;
    new_var214 += 0;
    if (((0x10 & (*(new_var20 = p3006))) && (sp5C != (0 & 0xFF))) != 0)
    {
      var_r4 = var_r4;
      var_r4 = ((long long) (var_r5 * 2)) + var_r4;
      ;
      *((u8 *) temp_r0_19) = (u8) ((*((u8 *) (temp_r0_19 = &sp14[var_sl]))) + new_var97);
      if (new_var4)


      if ((((float) new_var306) && (!sp20)) != 0U)
      {
      }
      sp5C = (s32) ((u8) (sp5C - new_var335));
      sp60 = (float) 1;
      func_08092E84(0x40);
    }
    new_var27 = 0xFFFFu;
    ;
    new_var165 = new_var459;
    new_var298 = (var_sl - 1) & (0xFFu);

    do
    {
    }
    while (new_var298 * 0);

    new_var159 = new_var27;
    new_var272 = (((((0xFFFFu & (0 & new_var384)) & new_var384) & new_var384) & new_var386) & new_var386) & 0xFFFFu;
    new_var433 = 3 & (*((u16 *) (((short) (((((0 & 0xFFFFu) & new_var159) & new_var159) & 0xFFFFu) & (new_var159 ^ 0)), 0x0300000E))));
    new_var37 = (new_var193 = (s8 *) sp20);
    if (!new_var433)
    {
      goto loop_278;
    }
    ;
    new_var149 = new_var272;
    var_r4_4 = 0x0300000E;
    if (((char) (*((u16 *) (((new_var149, var_r4_4)) & (new_var173 = 0xFFFFFFFFu))))) & 1)
    {
      ;
      new_var46 = new_var46;
      new_var408 = sp20;
      new_var148 = new_var419;

      new_var277 = inline_fn2345(new_var408);
      new_var99 = new_var148;
      if ((sp5C == 0) ^ 0)
      {
        new_var353 = 0;
        new_var185 = new_var353;
        new_var145 = new_var277;
        new_var202 = 0x2E + new_var145;
        new_var360 = &sp14;
        new_var232 = (new_var435 = (new_var337 = sp58));
        new_var10 = (u16 *) new_var202;
        new_var214 = (new_var185, new_var360);
        new_var460 = new_var193;
        new_var66 = (u16 *) (new_var460 + 0x28);
        new_var429 = new_var37;
        if (!new_var8)

      dummy_label_96746:
        ;

        new_var119 = (s8 *) new_var214;
        new_var84 = new_var460;
        *((u8 *) inline_fn234567(sp20)) = 4U;
        new_var209 = inline_fn23456789101112131415161718((s8 *) (new_var400 = &sp14));
        new_var149 += (8 * 0) * 8;
        new_var270 = (u16 *) (new_var84 - (-0x26));
        new_var151 = (*new_var270 = (*((u8 *) new_var209)) & 0xFFFFu);
        new_var375 = (u16 *) (new_var429 + 0x2C);
        new_var49 = new_var119;
        *new_var66 = (new_var283 = (new_var40 = *((u8 *) ((0, 1 + new_var49)))));
        *new_var10 = (u16) (*((u8 *) (((s8 *) (&sp14)) + (2 ^ (0 & 0xFFFFu)))));
        temp_r0_12 = (new_var156 = (u8 *) (*new_var146));
        sp20 = (0, sp20);
        *((u16 *) (new_var84 + 0x2A)) = (u16) (*((u8 *) (((s8 *) (&sp14)) + 3)));
        *new_var375 = (u16) (*((u8 *) (((s8 *) (new_var327 = (new_var55 = &sp14))) - (-4))));
        new_var354 = *new_var156;
        new_var430 = new_var84 + 0x2A;
        new_var442 = 0;




        func_080981F0(0x081063CC, 0, 3, 0, 0xA);
        func_08094554(new_var232);
        func_08094554(sp34);
        var_r0_4 = new_var212;
        goto block_304;
        *((u16 *) new_var430) = (u16) (new_var63 = new_var354);
      }

      ;
      func_08092E84(0x58);
      func_08098BB4(0x08001C22);
      func_080972C8();
      goto block_306;
    exit_2050:
      func_08094554(sp38);
      func_08094554(sp3C);
      var_r7 = (new_var61 = 0x2060);
      goto block_306;
    }
    else
    {
      func_080981F0(0x081063CC, 0, 3 ^ 0, 0, 0xA);
      new_var83 = new_var268;
      func_08094554(sp58);
      if (!new_var267)
      {
        new_var199 = !(new_var469 = new_var356);
        ;
        if ((((0, (0, new_var199 && new_var199))) && new_var199) != new_var83)

        {
        dummy_label_736825:
          ;

        }
      }
      asm volatile("" :: "rm"(sp1C));
      new_var136 = 0;
      func_08094554(sp34);
      new_var279 = 0U;
      if (new_var136)
      {
      }
      var_r0_4 = 0x3F;
    block_304:
      func_08092E84(var_r0_4);

      var_r7 = 0x3005;
      goto block_306;
    }
    goto block_306;

  }


  if ((new_var7 && new_var7) && new_var7)
  {
    new_var126 = (s8 *) sp24;

  }
  new_var205 = !D_0200A880;
  new_var39 = new_var39;
block_306:
  if (var_done_flag != 0)
  {
    goto done;
  dummy_label_261346:
    ;

    ;
  }


  if (0 != ((((float) (var_sl ^ 0)) && var_sl) && var_sl))




  if (!new_var50)
  {
  }


  goto loop_1;

done:
  func_080E66B8();

  if ((var_sl == 0) != new_var136)
  {
    if (new_var205)
    {


    }
  }
}
