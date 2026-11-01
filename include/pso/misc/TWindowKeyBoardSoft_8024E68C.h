#ifndef PSO_MISC_TWINDOWKEYBOARDSOFT_8024E68C_H
#define PSO_MISC_TWINDOWKEYBOARDSOFT_8024E68C_H

#include "types.h"
#include "pso/misc/TWindowDrawContext.h"


extern "C" {
void apply_window_closing_stretch__FPUci(TWindowDrawContext *, int);
void set_open_tick__19TWindowKeyBoardSoftFl(TWindowDrawContext *, s32);
void set_bounds__19TWindowKeyBoardSoftFffff(TWindowDrawContext *, f32, f32, f32, f32);
void shrink_clip_right__19TWindowKeyBoardSoftFv(TWindowDrawContext *);
void animate_scale__19TWindowKeyBoardSoftFv(TWindowDrawContext *);
s32 is_point_in_bounds__19TWindowKeyBoardSoftFPv(TWindowDrawContext *, void *);
TWindowDrawContext *open_singleton__19TWindowKeyBoardSoftFiiii(f32 *pos, f32 *size, f32 *scale, u32 flags, f32 depth);
TWindowDrawContext *get_or_create_instance__19TWindowKeyBoardSoftFv();
TWindowDrawContext *free_singleton__19TWindowKeyBoardSoftFUls(TWindowDrawContext *, s16);
TWindowDrawContext *init_layout__19TWindowKeyBoardSoftFv(TWindowDrawContext *);
void adjust_pos_for_split_screen__19TWindowKeyBoardSoftFl(f32 *point, s32 view);
s32 try_open__19TWindowKeyBoardSoftFii(s32 arg0, s32 arg1);
}

#endif
