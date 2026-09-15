#include "m2c_prelude.h"
void func_0809AA64(void *, s32, s32, s32);
void func_080ECD34(void *, s32);
extern u8 D_087AD1B8, D_087AD1C0, D_087AD1C8, D_087AC9E8;
extern u8 D_081076AC, D_08107970, D_08107A68, D_08107D24;
extern u8 D_08108024, D_08108040, D_0810805C, D_08108078, D_08108094, D_081080B0, D_081080CC, D_081080F4;
extern u8 D_06010000, D_06013000, D_06010400, D_06013400, D_06010700, D_06013700, D_06010B00, D_06013B00;
extern u8 D_05000200, D_05000220, D_05000240, D_05000260, D_05000280, D_050002A0, D_05000380, D_050003A0;
extern u8 D_050002C0, D_050002E0, D_05000300, D_05000320, D_05000340, D_05000360;

void sub_080C9F00(u8 arg0, u8 arg1) {
    s32 a, b;
    switch (arg1) {
    case 0:
    {
        void *p0 = &D_087AD1B8;
        a = 0; if (arg0 == 0) a = 0x180;
        b = 0; if (arg0 == 0) b = 6;
        func_0809AA64(p0, 0, a, b);
        goto done;
    }
    case 1:
    {
        void *p1 = &D_087AD1C0;
        a = 0; if (arg0 == 0) a = 0x180;
        b = 0; if (arg0 == 0) b = 6;
        func_0809AA64(p1, 0, a, b);
        return;
    }
    case 2:
        func_080ECD34(&D_081076AC, arg0 == 0 ? (s32)&D_06013000 : (s32)&D_06010000);
        func_080ECD34(&D_08107970, arg0 == 0 ? (s32)&D_06013400 : (s32)&D_06010400);
        func_080ECD34(&D_08107A68, arg0 == 0 ? (s32)&D_06013700 : (s32)&D_06010700);
        func_080ECD34(&D_08107D24, arg0 == 0 ? (s32)&D_06013B00 : (s32)&D_06010B00);
        func_080ECD34(&D_08108024, arg0 == 0 ? (s32)&D_05000200 + 0xC0 : (s32)&D_05000200);
        func_080ECD34(&D_08108040, arg0 == 0 ? (s32)&D_05000220 + 0xC0 : (s32)&D_05000220);
        func_080ECD34(&D_0810805C, arg0 == 0 ? (s32)&D_05000240 + 0xC0 : (s32)&D_05000240);
        func_080ECD34(&D_08108078, arg0 == 0 ? (s32)&D_05000260 + 0xC0 : (s32)&D_05000260);
        func_080ECD34(&D_08108094, arg0 == 0 ? (s32)&D_05000280 + 0xC0 : (s32)&D_05000280);
        func_080ECD34(&D_081080B0, arg0 == 0 ? (s32)&D_050002A0 + 0xC0 : (s32)&D_050002A0);
        func_080ECD34(&D_081080CC, (s32)&D_05000380);
        func_080ECD34(&D_081080F4, (s32)&D_050003A0);
done:
        func_0809AA64(&D_087AC9E8, 0, 0x3B4, 0xD);
        return;
    case 3:
    {
        void *p3 = &D_087AD1C8;
        a = 0; if (arg0 == 0) a = 0x180;
        b = 0; if (arg0 == 0) b = 6;
        func_0809AA64(p3, 0, a, b);
        return;
    }
    }
}
