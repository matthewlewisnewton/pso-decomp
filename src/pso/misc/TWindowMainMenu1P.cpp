#include "types.h"
#include "pso/misc/TCameraCtrl_800687BC.h"
#include "pso/misc/TWindowMainMenu.h"
#include "pso/misc/TWindowMainMenu1P.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TWindowCtrlMain.h"
#include "pso/misc/TWindowOptionCtrl_8026CBA4.h"

const WindowLayoutPosition window_layout_rect_table[210] = {
    {13.0f, 256.0f}, {13.0f, 317.0f}, {324.0f, 256.0f}, {13.0f, 256.0f},
    {324.0f, 256.0f}, {324.0f, 318.0f}, {324.0f, 318.0f}, {13.0f, 256.0f},
    {221.0f, 256.0f}, {395.0f, 256.0f}, {221.0f, 256.0f}, {409.0f, 256.0f},
    {16.0f, 172.0f}, {13.0f, 317.0f}, {320.0f, 340.0f}, {13.0f, 256.0f},
    {227.0f, 256.0f}, {433.0f, 256.0f}, {13.0f, 256.0f}, {200.0f, 256.0f},
    {385.0f, 256.0f}, {13.0f, 256.0f}, {210.0f, 256.0f}, {85.0f, 256.0f},
    {13.0f, 256.0f}, {299.0f, 256.0f}, {28.0f, 85.0f}, {17.0f, 312.0f},
    {28.0f, 37.0f}, {226.0f, 37.0f}, {30.0f, 444.0f}, {471.0f, 337.0f},
    {373.0f, 203.0f}, {373.0f, 123.0f}, {254.0f, 37.0f}, {17.0f, 306.0f},
    {132.0f, 202.0f}, {463.0f, 37.0f}, {12.0f, 50.0f}, {400.0f, 50.0f},
    {12.0f, 418.0f}, {12.0f, 389.0f}, {12.0f, 389.0f}, {266.0f, 270.0f},
    {294.0f, 365.0f}, {400.0f, 50.0f}, {12.0f, 50.0f}, {98.0f, 364.0f},
    {124.0f, 98.0f}, {215.0f, 177.0f}, {176.0f, 130.0f}, {227.0f, 130.0f},
    {17.0f, 224.0f}, {228.0f, 224.0f}, {244.0f, 224.0f}, {106.0f, 120.0f},
    {260.0f, 62.0f}, {260.0f, 62.0f}, {275.0f, 175.0f}, {388.0f, 177.0f},
    {400.0f, 340.0f}, {270.0f, 215.0f}, {20.0f, 120.0f}, {87.0f, 356.0f},
    {87.0f, 356.0f}, {12.0f, 189.0f}, {12.0f, 50.0f}, {320.0f, 140.0f},
    {140.0f, 300.0f}, {500.0f, 300.0f}, {320.0f, 240.0f}, {292.0f, 144.0f},
    {320.0f, 140.0f}, {140.0f, 300.0f}, {500.0f, 300.0f}, {320.0f, 240.0f},
    {292.0f, 144.0f}, {320.0f, 140.0f}, {140.0f, 300.0f}, {500.0f, 300.0f},
    {320.0f, 240.0f}, {292.0f, 144.0f}, {151.0f, 166.0f}, {17.0f, 287.0f},
    {104.0f, 357.0f}, {288.0f, 212.0f}, {99.0f, 120.0f}, {359.0f, 282.0f},
    {12.0f, 305.0f}, {13.0f, 256.0f}, {13.0f, 256.0f}, {239.0f, 256.0f},
    {341.0f, 256.0f}, {341.0f, 318.0f}, {341.0f, 318.0f}, {341.0f, 256.0f},
    {13.0f, 256.0f}, {13.0f, 357.0f}, {13.0f, 142.0f}, {13.0f, 243.0f},
    {13.0f, 340.0f}, {341.0f, 256.0f}, {341.0f, 128.0f}, {341.0f, 190.0f},
    {341.0f, 190.0f}, {341.0f, 128.0f}, {13.0f, 128.0f}, {13.0f, 155.0f},
    {13.0f, 128.0f}, {13.0f, 155.0f}, {13.0f, 182.0f}, {341.0f, 102.0f},
    {13.0f, 256.0f}, {39.0f, 340.0f}, {13.0f, 256.0f}, {13.0f, 256.0f},
    {420.0f, 256.0f}, {420.0f, 256.0f}, {420.0f, 314.0f}, {13.0f, 256.0f},
    {13.0f, 256.0f}, {13.0f, 316.0f}, {208.0f, 256.0f}, {388.0f, 256.0f},
    {388.0f, 366.0f}, {208.0f, 256.0f}, {388.0f, 335.0f}, {13.0f, 256.0f},
    {435.0f, 256.0f}, {194.0f, 256.0f}, {402.0f, 256.0f}, {402.0f, 315.0f},
    {402.0f, 304.0f}, {194.0f, 256.0f}, {419.0f, 256.0f}, {419.0f, 256.0f},
    {419.0f, 314.0f}, {194.0f, 256.0f}, {194.0f, 256.0f}, {439.0f, 256.0f},
    {194.0f, 256.0f}, {194.0f, 314.0f}, {194.0f, 256.0f}, {419.0f, 256.0f},
    {194.0f, 256.0f}, {194.0f, 256.0f}, {419.0f, 256.0f}, {429.0f, 256.0f},
    {194.0f, 256.0f}, {194.0f, 256.0f}, {419.0f, 256.0f}, {419.0f, 256.0f},
    {419.0f, 256.0f}, {419.0f, 256.0f}, {8.0f, 256.0f}, {188.0f, 256.0f},
    {408.0f, 256.0f}, {408.0f, 256.0f}, {408.0f, 256.0f}, {408.0f, 314.0f},
    {397.0f, 256.0f}, {188.0f, 256.0f}, {397.0f, 315.0f}, {327.0f, 256.0f},
    {13.0f, 256.0f}, {435.0f, 256.0f}, {194.0f, 256.0f}, {419.0f, 256.0f},
    {366.0f, 37.0f}, {270.0f, 75.0f}, {254.0f, 37.0f}, {30.0f, 116.0f},
    {117.0f, 7.0f}, {88.0f, 120.0f}, {181.0f, 50.0f}, {622.0f, 37.0f},
    {18.0f, 53.0f}, {17.0f, 287.0f}, {17.0f, 277.0f}, {395.0f, 256.0f},
    {68.0f, 251.0f}, {82.0f, 292.0f}, {96.0f, 333.0f}, {26.0f, 359.0f},
    {325.0f, 359.0f}, {30.0f, 346.0f}, {17.0f, 285.0f}, {352.0f, 266.0f},
    {12.0f, 266.0f}, {12.0f, 345.0f}, {294.0f, 365.0f}, {167.0f, 153.0f},
    {18.0f, 308.0f}, {294.0f, 305.0f}, {41.0f, 128.0f}, {99.0f, 128.0f},
    {109.0f, 164.0f}, {10000.0f, 10000.0f}, {399.0f, 256.0f}, {18.0f, 265.0f},
    {41.0f, 128.0f}, {43.0f, 54.0f}, {18.0f, 300.0f}, {351.0f, 66.0f},
    {351.0f, 86.0f}, {176.0f, 253.0f}, {85.0f, 119.0f}, {99.0f, 160.0f},
    {113.0f, 201.0f}, {127.0f, 242.0f},
};

const WindowLayoutPosition window_layout_position_table[92] = {
    {2.0f, 14.0f}, {2.0f, 74.0f}, {72.0f, 14.0f}, {2.0f, 14.0f},
    {86.0f, 14.0f}, {86.0f, 75.0f}, {86.0f, 75.0f}, {2.0f, 14.0f},
    {139.0f, 14.0f}, {83.0f, 14.0f}, {125.0f, 14.0f}, {97.0f, 14.0f},
    {1000.0f, 172.0f}, {2.0f, 74.0f}, {156.0f, 100.0f}, {2.0f, 13.0f},
    {103.0f, 13.0f}, {120.0f, 13.0f}, {2.0f, 14.0f}, {131.0f, 14.0f},
    {68.0f, 14.0f}, {2.0f, 14.0f}, {10.0f, 14.0f}, {0.0f, 8.0f},
    {1.0f, 0.0f}, {25.0f, 66.0f}, {0.0f, 0.0f}, {106.0f, 34.0f},
    {0.0f, 0.0f}, {155.0f, -1.0f}, {0.0f, 200.0f}, {234.0f, 144.0f},
    {53.0f, -10.0f}, {53.0f, -10.0f}, {268.0f, 217.0f}, {47.0f, 58.0f},
    {0.0f, 34.0f}, {381.0f, 304.0f}, {1.0f, 10.0f}, {140.0f, 0.0f},
    {10.0f, 115.0f}, {10.0f, 91.0f}, {10.0f, 91.0f}, {227.0f, 21.0f},
    {30.0f, 139.0f}, {140.0f, 0.0f}, {0.0f, 0.0f}, {98.0f, 364.0f},
    {82.0f, 36.0f}, {8.0f, 47.0f}, {16.0f, 39.0f}, {2.0f, 52.0f},
    {17.0f, 224.0f}, {228.0f, 224.0f}, {244.0f, 224.0f}, {100.0f, 108.0f},
    {16.0f, 52.0f}, {1000.0f, 1000.0f}, {89.0f, 57.0f}, {132.0f, 0.0f},
    {96.0f, 94.0f}, {118.0f, 80.0f}, {20.0f, 120.0f}, {2.0f, 5.0f},
    {1.0f, 73.0f}, {12.0f, 50.0f}, {43.0f, 1.0f}, {164.0f, 80.0f},
    {140.0f, 300.0f}, {500.0f, 300.0f}, {320.0f, 240.0f}, {164.0f, 80.0f},
    {164.0f, 80.0f}, {140.0f, 300.0f}, {500.0f, 300.0f}, {320.0f, 240.0f},
    {164.0f, 80.0f}, {164.0f, 80.0f}, {140.0f, 300.0f}, {500.0f, 300.0f},
    {320.0f, 240.0f}, {164.0f, 80.0f}, {151.0f, 166.0f}, {63.0f, 98.0f},
    {150.0f, 168.0f}, {154.0f, 212.0f}, {8.0f, 128.0f}, {359.0f, 282.0f},
    {43.0f, 1.0f}, {186.0f, 91.0f}, {20.0f, 240.0f}, {145.0f, 180.0f},
};

extern "C" {
extern const char TWindowMainMenu1P__class_name_string[] = "TWindowMainMenu1P";
const char *TWindowMainMenu1P__name = TWindowMainMenu1P__class_name_string;
}

struct RecoveredGlobal_80288838___vt__17TWindowMainMenu1P { s32 value; u8 remaining[0x24]; };
typedef char RecoveredGlobal_80288838___vt__17TWindowMainMenu1P_size[sizeof(RecoveredGlobal_80288838___vt__17TWindowMainMenu1P) == 0x28 ? 1 : -1];

extern "C" {
void __dl__7TObjectFPv(s32);
extern s32 __vt__17TWindowMainMenu1P[];
extern const f32 lbl_805DD8A0;
extern const f32 lbl_805DD8A4;
extern const f32 lbl_805DD8A8;
extern const f32 lbl_805DD8AC;
extern const f32 lbl_805DD8B0;
extern const f32 lbl_805DD8B4;
extern const f32 lbl_805DD8B8;
extern const f32 lbl_805DD8BC;
extern const f32 lbl_805DD8C0;
extern const f32 lbl_805DD8C4;
extern const f32 lbl_805DD8C8;
void TWindowMainMenu__ct(void *);

#pragma fp_contract on
void TWindowMainMenu1P::update_backdrop_transition() {
    u8 *arg0 = (u8 *)this;
  f32 temp_f1;
  s32 temp_r3;
  s32 temp_r3_2;
  temp_r3 = *((s32 *) (((s8 *) arg0) + 0x4C));
  if (!(temp_r3 & 1))
  {
    *((u8 *) (((s8 *) arg0) + 0x60)) = (u8) ((*((u8 *) (((s8 *) arg0) + 0x60))) - 1);
    *((u8 *) (((s8 *) arg0) + 0x61)) = (u8) ((*((u8 *) (((s8 *) arg0) + 0x61))) + -1);
    if (((s8) (*((u8 *) (((s8 *) arg0) + 0x60)))) < 0)
    {
      *((u8 *) (((s8 *) arg0) + 0x60)) = 0U;
    }
    if (((s8) (*((u8 *) (((s8 *) arg0) + 0x61)))) < 0)
    {
      *((u8 *) (((s8 *) arg0) + 0x61)) = 0U;
    }
    if ((((s8) (*((u8 *) (((s8 *) arg0) + 0x60)))) == 0) && (((s8) (*((u8 *) (((s8 *) arg0) + 0x61)))) == 0))
    {
      temp_r3_2 = *((s32 *) (((s8 *) arg0) + 0x4C));
      if (temp_r3_2 & 2)
      {
        *((s32 *) (((s8 *) arg0) + 0x4C)) = (s32) (temp_r3_2 & 0xFFFFFFFD);
        end_view_override();
      }
    }
  }
  else
    if (temp_r3 & 8)
  {
    *((u8 *) (((s8 *) arg0) + 0x60)) = (u8) ((*((u8 *) (((s8 *) arg0) + 0x60))) + 1);
    *((u8 *) (((s8 *) arg0) + 0x61)) = (u8) ((*((u8 *) (((s8 *) arg0) + 0x61))) - 1);
    if (((f32) ((s8) (*((u8 *) (((s8 *) arg0) + 0x60))))) > lbl_805DD8A0)
    {
      *((u8 *) (((s8 *) arg0) + 0x60)) = 6U;
    }
    if (((s8) (*((u8 *) (((s8 *) arg0) + 0x61)))) < 0)
    {
      *((u8 *) (((s8 *) arg0) + 0x61)) = 0U;
    }
  }
  else
  {
    *((u8 *) (((s8 *) arg0) + 0x60)) = (u8) ((*((u8 *) (((s8 *) arg0) + 0x60))) + 1);
    *((u8 *) (((s8 *) arg0) + 0x61)) = (u8) ((*((u8 *) (((s8 *) arg0) + 0x61))) + 1);
    if (((f32) ((s8) (*((u8 *) (((s8 *) arg0) + 0x60))))) > lbl_805DD8A4)
    {
      *((u8 *) (((s8 *) arg0) + 0x60)) = 3U;
    }
    if (((f32) ((s8) (*((u8 *) (((s8 *) arg0) + 0x61))))) > lbl_805DD8A4)
    {
      *((u8 *) (((s8 *) arg0) + 0x61)) = 3U;
    }
  }
  this->m_6c = (f32) ((lbl_805DD8AC * ((f32) ((s8) (*((u8 *) (((s8 *) arg0) + 0x60)))))) + lbl_805DD8A8);
  *((f32 *) (((s8 *) arg0) + 0x70)) = (f32) (-((lbl_805DD8B4 * ((f32) ((s8) (*((u8 *) (((s8 *) arg0) + 0x61)))))) - lbl_805DD8B0));
  TWindowCtrlMain::set_depth(lbl_805DD8B8 * ((f32) ((s8) (*((u8 *) (((s8 *) arg0) + 0x60))))), *((s32 *) (((s8 *) arg0) + 0x54)));
  TWindowCtrlMain::set_field18(-((lbl_805DD8C0 * ((f32) ((s8) (*((u8 *) (((s8 *) arg0) + 0x61)))))) - lbl_805DD8BC), *((s32 *) (((s8 *) arg0) + 0x54)));
  this->m_a4 = (f32) ((lbl_805DD8C4 - (this->m_6c)) / lbl_805DD8A8);
  *((f32 *) (((s8 *) arg0) + 0xA8)) = (f32) ((*((f32 *) (((s8 *) arg0) + 0x70))) / lbl_805DD8B0);
  temp_f1 = *((f32 *) (((s8 *) arg0) + 0xA8));
  if ((this->m_a4) < (*((f32 *) (((s8 *) arg0) + 0xA8))))
  {
    this->m_a4 = *((f32 *) (((s8 *) arg0) + 0xA8));
  }
  *((f32 *) (((s8 *) arg0) + 0xA8)) = (f32) (lbl_805DD8C8 * (this->m_a4));
  if ((*((s32 *) (((s8 *) arg0) + 0x4C))) & 2)
  {
    ((CameraViewParams *)(((u8 *) arg0) + 0x64))->apply_if_overridden();
  }
}

void TWindowMainMenu1P::render() {  }
void TWindowMainMenu1P::run_task() { handle_menu_selection(); sub_80263FE0(); update_backdrop_transition(); }

extern const f32 lbl_805DD8CC;
extern const f32 lbl_805DD8D0;
extern const f32 lbl_805DD8D4;
extern const f32 lbl_805DD8D8;

u8 *__dt__17TWindowMainMenu1PFv(u8 *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = &(*(RecoveredGlobal_80288838___vt__17TWindowMainMenu1P *)&__vt__17TWindowMainMenu1P).value;
        if (*(s32 *)((s8 *)arg0 + 0x4C) & 2) {
            end_view_override();
        }
        __dt__15TWindowMainMenuFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv((s32) arg0);
        }
    }
    return arg0;
}

void *TWindowMainMenu1P__ct(TWindowMainMenu1P *window_main_menu1_p) {
    TWindowMainMenu__ct(window_main_menu1_p);
    *(s32 **)((s8 *)window_main_menu1_p + 0x18) = __vt__17TWindowMainMenu1P;
    window_main_menu1_p->m_name = TWindowMainMenu1P__name;
    *(u8 *)((s8 *)window_main_menu1_p + 0x60) = 0;
    *(u8 *)((s8 *)window_main_menu1_p + 0x61) = 0;
    window_main_menu1_p->m_6c = lbl_805DD8A8;
    *(f32 *)((s8 *)window_main_menu1_p + 0x70) = lbl_805DD8B0;
    window_main_menu1_p->m_8c = lbl_805DD8C4;
    *(f32 *)((s8 *)window_main_menu1_p + 0x90) = lbl_805DD8BC;
    window_main_menu1_p->m_94 = lbl_805DD8CC;
    *(f32 *)((s8 *)window_main_menu1_p + 0x98) = lbl_805DD8CC;
    window_main_menu1_p->m_9c = lbl_805DD8D0;
    *(f32 *)((s8 *)window_main_menu1_p + 0xA0) = lbl_805DD8D4;
    window_main_menu1_p->m_a4 = lbl_805DD8D8;
    *(f32 *)((s8 *)window_main_menu1_p + 0xA8) = lbl_805DD8C8;
    return window_main_menu1_p;
}

}
