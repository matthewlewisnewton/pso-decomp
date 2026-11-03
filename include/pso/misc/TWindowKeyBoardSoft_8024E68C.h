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
void apply_context_transform_to_rect(TWindowDrawContext *, f32 *quad);
TWindowDrawContext *get_or_create_instance__19TWindowKeyBoardSoftFv();
TWindowDrawContext *free_singleton__19TWindowKeyBoardSoftFUls(TWindowDrawContext *, s16);
TWindowDrawContext *init_layout__19TWindowKeyBoardSoftFv(TWindowDrawContext *);
void adjust_pos_for_split_screen__19TWindowKeyBoardSoftFl(f32 *point, s32 view);
}

#endif
