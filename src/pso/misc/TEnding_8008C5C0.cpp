#include "pso/misc/TEnding.h"
#include "pso/misc/TCameraCtrl_803D6538.h"
#include "pso/misc/TEnding_8008C5C0.h"
#include "pso/misc/TKeyBoardControl_8000F764.h"
#include "pso/misc/TLoadCtrl_80227390.h"
#include "pso/object/TObjLight_80133568.h"
#include "pso/player/TObjPlayer_801A5AEC.h"
#include "pso/unk/text_800F9B84.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/system/main_loop.h"
#include "pso/system/vector.h"

#include "types.h"
#include "pso/TParticleCtrl.h"

extern "C" {
void set_active_camera_pose(u8 *arg0, u8 *arg1);
u8 *TCameraCtrl__ct(u8 *arg0, void *parent);
void __ct__7TEndingFv(void *);
void run_load_callback_table(void *, int);
void set_copy_clear_color_argb(int, int, int);
void *__nw__7TObjectFUl(int);
extern const char TEnding__class_name_string[] = "TEnding";
extern u8 ending_scene_callbacks[];
extern u8 default_scene_light_config[];
extern void *tl_camera;
static const f32 lbl_805D9570 = 1.0f;
static const f32 lbl_805D9574 = 0.85f;
extern s32 ending_scene_active;

void TEnding::set_flag_and_advance() {
    ending_scene_active = 1;
    TEnding::start_ending_scene();
}

#ifdef __MWERKS__
#pragma push
#pragma pool_data off
#endif
void TEnding::start_ending_scene() {
    void *p;
    set_screen_size(lbl_805D9570, lbl_805D9574);
    set_copy_clear_color_argb(0, 0, 0);
    reset_controller_input_state();
    init_map_lights(default_scene_light_config);
    p = __nw__7TObjectFUl(0x1D4);
    if (p != 0) {
        TCameraCtrl__ct((u8 *)p, tl_camera);
    }
    Vec position = {0.0f, 0.0f, 0.0f};
    Vec target = {0.0f, 0.0f, -100.0f};
    TCameraCtrl::select_active_controller(9);
    set_active_camera_pose((u8 *)&position, (u8 *)&target);
    clear_resource_load_tasks();
    run_load_callback_table(ending_scene_callbacks, 0x68);
    TKeyBoardControl__sub_8000F90C(2);
    TKeyBoardControl__sub_8000F91C(2);
    static const char music_filename[] = "ending.adx";
    play_area_music((char *)music_filename);
    TParticleCtrl::create_quad_sprites();
    p = __nw__7TObjectFUl(0x710);
    if (p != 0) {
        __ct__7TEndingFv(p);
    }
    render_tick();
}

#ifdef __MWERKS__
#pragma pop
#endif

void TEnding__sub_8008C6E8() {}
void TEnding__sub_8008C6EC() {}
}

void TEnding::render() {}
