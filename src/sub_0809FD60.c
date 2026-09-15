#include "m2c_prelude.h"

extern void func_080ED17C(s32);

extern s8 D_02031749;
extern s32 D_0203174C[];
extern u8 D_02031754;
extern s32 D_02032E88[];
extern u16 D_020324A4[];
extern s32 D_03000054[];

void sub_0809FD60(void) {
  u8 direction[4];
  volatile s32 x_step;
  volatile s32 y_step;
  register s32 x_accum asm("r4");
  register s32 y_accum asm("r5");
  register u32 count asm("r9");
  register s32 *camera asm("r6");
  register u8 *step asm("sl");
  register s32 *state asm("r8");
  u8 done;

  {
    register s32 *target asm("r3") = D_0203174C;
    register s32 *initial_camera asm("r6") = D_03000054;
    register s32 x_delta asm("r1");
    register s32 first_x asm("r2");
    register s32 y_delta asm("r0");
    register s32 target_x asm("r1");
    register s32 camera_x asm("r0");

    target_x = target[0];
    camera_x = initial_camera[0];
    x_delta = target_x - camera_x;
    if (x_delta < 0) {
      x_delta += 0xFF;
    }
    first_x = x_delta >> 8;
    x_step = first_x;

    y_delta = target[1] - initial_camera[1];
    if (y_delta < 0) {
      y_delta += 0xFF;
    }
    y_step = y_delta >> 8;

    if (first_x >= 0) {
      direction[0] = 0;
    } else {
      x_step = -x_step;
      direction[0] = 1;
    }
  }

  {
    register s32 y_sign asm("r1") = y_step;

    if (y_sign >= 0) {
      direction[1] = 0;
    } else {
      register s32 negative_y asm("r2") = y_step;

      negative_y = -negative_y;
      y_step = negative_y;
      direction[1] = 1;
    }
  }

  y_accum = 0;
  x_accum = 0;
  count = x_accum;
  camera = D_03000054;
  {
    register u8 *initial_step asm("r3") = &D_02031754;

    asm volatile("" : : "r"(initial_step));
    step = initial_step;
  }
  {
    register s32 *initial_state asm("r7") = D_02032E88;

    state = initial_state;
  }

loop: {
  register s32 x_delta asm("r0") = x_step;

  x_accum = x_delta + x_accum;
}
  {
    register s32 y_delta asm("r1") = y_step;

    y_accum = y_delta + y_accum;
  }

  if (x_accum >= D_02031754) {
    register s32 current_step asm("r0");

    do {
      register s32 amount asm("r3");
      register s32 value asm("r0");
      register u8 *current_step_ptr asm("r7");

      if (direction[0] == 0) {
        value = D_03000054[0];
        amount = 0x100;
        value += amount;
        D_03000054[0] = value;
        if (D_02032E88[1] != 0) {
          value = camera[2];
          goto store_shadow_x;
        }
      } else {
        register s32 negative asm("r7");

        value = D_03000054[0];
        negative = -0x100;
        value += negative;
        D_03000054[0] = value;
        if (D_02032E88[1] != 0) {
          value = camera[2];
          amount = negative;
        store_shadow_x:
          value += amount;
          camera[2] = value;
        }
      }

      current_step_ptr = step;
      asm volatile("ldrb %0, [%1]"
                   : "=r"(current_step)
                   : "r"(current_step_ptr));
      x_accum -= current_step;
    } while (x_accum >= current_step);
  }

  if (y_accum >= *step) {
    register s32 current_step asm("r0");

    do {
      register s32 amount asm("r3");
      register s32 value asm("r0");
      register u8 *current_step_ptr asm("r7");

      if (direction[1] == 0) {
        value = D_03000054[1];
        amount = 0x100;
        value += amount;
        D_03000054[1] = value;
        if (D_02032E88[1] != 0) {
          value = camera[3];
          goto store_shadow_y;
        }
      } else {
        register s32 negative asm("r7");

        value = D_03000054[1];
        negative = -0x100;
        value += negative;
        D_03000054[1] = value;
        if (D_02032E88[1] != 0) {
          value = camera[3];
          amount = negative;
        store_shadow_y:
          value += amount;
          camera[3] = value;
        }
      }

      current_step_ptr = step;
      asm volatile("ldrb %0, [%1]"
                   : "=r"(current_step)
                   : "r"(current_step_ptr));
      y_accum -= current_step;
    } while (y_accum >= current_step);
  }

  {
    register s32 x asm("r1") = camera[0];

    if (x < 0) {
      camera[0] = 0;
      {
        register s32 *x_state asm("r2") = state;
        if (x_state[1] != 0) {
          camera[2] = 0;
        }
      }
      goto x_clamped;
    }
    {
      register u16 *dims asm("r2") = D_020324A4;
      register s32 limit asm("r0") = (dims[0] << 11) - 0xF000;
      if (x > limit) {
        camera[0] = limit;
        {
          register s32 *x_state asm("r7") = state;
          if (x_state[1] != 0) {
            camera[2] = (dims[0] << 11) - 0xF000;
          }
        }
      x_clamped:
        done = 1;
      } else {
        done = 0;
      }
    }
  }

  {
    register s32 *y_camera asm("r2") = camera;
    register s32 y asm("r1") = y_camera[1];

    if (y < 0) {
      y_camera[1] = 0;
      {
        register s32 *y_state asm("r0") = state;
        if (y_state[1] != 0) {
          y_camera[3] = 0;
        }
      }
      goto y_clamped;
    }
    {
      register u16 *dims asm("r2") = D_020324A4;
      register s32 limit asm("r0") = (dims[1] << 11) - 0xA000;
      if (y > limit) {
        camera[1] = limit;
        {
          register s32 *y_state asm("r1") = state;
          if (y_state[1] != 0) {
            register s32 shadow_limit asm("r0") = dims[1] << 11;
            register s32 addend asm("r2");

            asm volatile("" : "=r"(addend) : "0"(-0xA000));
            camera[3] = shadow_limit + addend;
          }
        }
      y_clamped: {
        register u32 next_done asm("r0") = done;

        next_done++;
        done = (u8)next_done;
      }
      }
    }
  }

  if (done != 2) {
    register u8 *count_step asm("r3");

    count = (u8)(count + 1);
    count_step = step;
    if (count != *count_step) {
      func_080ED17C(1);
      goto loop;
    }
  }

  D_02031749 = 0;
}
