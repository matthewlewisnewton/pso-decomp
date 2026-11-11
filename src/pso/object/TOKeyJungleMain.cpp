#include "pso/system/BmlResource.h"
#include "pso/system/CurrentTextureList.h"
#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/TMainTask.h"
#include "pso/TObject.h"
#include "pso/math/MatrixVector.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/render/render_util.h"
#include "pso/unk/text_803D96A8.h"

#include "pso/system/vector.h"
#include "pso/TLevelSelect.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/TOKey.h"
#include "pso/misc/TQuestVmDownLoadServer.h"
#include "pso/npc/TObjNpcEnemy.h"
#include "pso/object/TObjMotion.h"
#include "pso/player/TObjPlayer.h"
#include "pso/object/TObjFish.h"
#include "pso/misc/TOKeyJungleMain.h"
#include "pso/map/FloorArea.h"
#include "pso/misc/TLobbyEventTheme.h"

struct Base_8029D3A4_8029CF68;
struct Base_8029CF68;
struct VBase_18_076902;
struct RecoveredGlobal_8029D238_TOKeyJungleMain__data_804653C8;
struct RecoveredGlobal_8029CFEC_lbl_804DC590;
struct RecoveredGlobal_8029D200_TOKeyJungleMain__data_804653C8;
struct VBase_18_1a504b;
struct RecoveredGlobal_8029D438_lbl_804DC5A0;
struct RecoveredGlobal_8029D438___vt__15TOKeyJungleMain;
struct VBase_18_26a62c;
struct SVec_8029D5C8;
struct Fish_8029D5C8;
struct Vec_8029E170;
struct Ent_8029E170;
extern "C" {
void * __nw__7TObjectFUl(int);
void render__8TObjFishFv(u8 *arg0);
s32 init_fish_school__8TObjFishFPvll(u8 *arg0, Vec_8029E170 *arg1, s32 arg2, s32 arg3);
extern s32 TObjFish__area_bml_resource;
extern void* __vt__8TObjFish[];
extern void* fish_resource_name_table[];
}

struct Base_8029D3A4_8029CF68 { char pad[0x18]; };

struct VObj_8029D3A4_8029CF68 : Base_8029D3A4_8029CF68 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
};

struct Base_8029CF68 { char pad[0x18]; };

struct VObj_8029CF68 : Base_8029CF68 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual s32 m8(f32, f32);
};

struct VBase_18_076902 { char pad[0x18]; };

struct RecoveredGlobal_8029D238_TOKeyJungleMain__data_804653C8 { s32 value; u8 remaining[0x8]; };
typedef char RecoveredGlobal_8029D238_TOKeyJungleMain__data_804653C8_size[sizeof(RecoveredGlobal_8029D238_TOKeyJungleMain__data_804653C8) == 0xC ? 1 : -1];

struct RecoveredGlobal_8029CFEC_lbl_804DC590 { s32 value; u8 remaining[0xC]; };
typedef char RecoveredGlobal_8029CFEC_lbl_804DC590_size[sizeof(RecoveredGlobal_8029CFEC_lbl_804DC590) == 0x10 ? 1 : -1];

struct RecoveredGlobal_8029D200_TOKeyJungleMain__data_804653C8 {
    s32 value;
    u8 remaining[0x8];
};

struct VBase_18_1a504b { char pad[0x18]; };

struct RecoveredGlobal_8029D438_lbl_804DC5A0 {
    s32 value;
    u8 remaining[0x28];
};

struct RecoveredGlobal_8029D438___vt__15TOKeyJungleMain {
    s32 value;
    u8 remaining[0x70];
};

extern "C" {
s32 post_translate_matrix(void *);
s32 draw_ginja_object();
s32 draw_ginja_model_with_motion(s32, s32, f32);
s32 get_bml_motion(s32, s32);
s32 TObjFish__sub_8001EDB0(s32, s32);
s32 rotate_matrix_y(s32, s32);
s32 push_matrix();

extern u32 TOKeyJungleMain__static_model_resource;
void render__15TOKeyJungleMainFv(TOKeyJungleMain *arg0);
void free_collision_body_parts(void *);
void __dl__7TObjectFPv(void *);
void *__dt__5TOKeyFv(void *arg0, s16 arg1);
extern s32 __vt__15TOKeyJungleMain[];
void *__dt__15TOKeyJungleMainFv(void *arg0, s16 arg1);
extern s32 TObjFish__area_event_stage;
u8 update_state__8TObjFishFv(void *arg0);
extern const f32 lbl_805DDD38;
extern const f32 lbl_805DDD3C;
extern RecoveredGlobal_8029D238_TOKeyJungleMain__data_804653C8 TOKeyJungleMain__data_804653C8;
extern s32 game_difficulty_selection;
extern RecoveredGlobal_8029CFEC_lbl_804DC590 bm_obj_jungle_mkey_resource_descriptor;
s32 dispatch_by_phase__15TOKeyJungleMainFlUs(void *, int);
s32 init_collision_body_parts(void *, void *, int);
void *__ct__5TOKeyFP7TObject(TOKey *arg0);
extern RecoveredGlobal_8029D438_lbl_804DC5A0 TOKeyJungleMain_collision_body_parts;
extern s32 lbl_805D3D50;
u8 *TOKeyJungleMain__ct(TOKeyJungleMain *arg0, s32 arg1, s32 arg2);
void debug_printf_at(s32, const char *, ...);
extern char lbl_80465A2C[];
void *TOKeyJungleMain::create(void *arg0) {
    void *o = __nw__7TObjectFUl(0xF0);
    if (o != NULL) {
        o = TOKeyJungleMain__ct((TOKeyJungleMain *)((u8 *)o), (s32)tl_05, (s32)arg0);
    }
    return o;
}

void TOKeyJungleMain::release_static_resource() {
    if ((u32) TOKeyJungleMain__static_model_resource != 0U) {
        delete (BmlResource *)((void*)TOKeyJungleMain__static_model_resource);
        TOKeyJungleMain__static_model_resource = 0U;
    }
}

void TOKeyJungleMain::load_static_resource() {
    s32 temp_r3;
    s32 var_r0;
    temp_r3 = (int)new BmlResource(5, (BmlResourceDescriptor *)(&bm_obj_jungle_mkey_resource_descriptor.value), 0, 0, (void *)(0));
    var_r0 = temp_r3;
    (*(s32 *)&TOKeyJungleMain__static_model_resource) = var_r0;
}

void TOKeyJungleMain::debug_draw_key_id() {
    *(s32 *)&this->switch_id = this->set_params[0];
    if (*(s32 *)&this->switch_id < 0) {
        *(s32 *)&this->switch_id = 0;
    }
    if (*(s32 *)&this->switch_id > 2) {
        *(s32 *)&this->switch_id = 2;
    }
    TObjNpcEnemy::set_global_count(0xFF00FF);
    debug_printf_at(0x130020, lbl_80465A2C, ((s32 *)&TOKeyJungleMain__data_804653C8)[*(s32 *)&this->switch_id]);
    TObjNpcEnemy::set_global_count(0xF0F0F0FF);
}

void render__15TOKeyJungleMainFv(TOKeyJungleMain *key_jungle_main) {
    if (((VObj_8029CF68 *)key_jungle_main)->m8(key_jungle_main->view_range, *(f32 *)((s8 *)key_jungle_main + 0xC4)) == 1) {
        switch (key_jungle_main->is_on) {
        case 0:
            set_current_texture_list((GinjaTextureList *)(TObjFish__sub_8001EDB0((*(s32 *)&TOKeyJungleMain__static_model_resource), 1)));
            push_matrix();
            post_translate_matrix((u8 *)key_jungle_main + 0x38);
            rotate_matrix_y(0, key_jungle_main->rotation.yaw);
            (s32)get_bml_model((BmlResource *)(*(s32 *)&TOKeyJungleMain__static_model_resource), 1);
            draw_ginja_object();
            pop_matrix();
            return;
        case 1:
            set_current_texture_list((GinjaTextureList *)(TObjFish__sub_8001EDB0((*(s32 *)&TOKeyJungleMain__static_model_resource), 1)));
            push_matrix();
            post_translate_matrix((u8 *)key_jungle_main + 0x38);
            rotate_matrix_y(0, key_jungle_main->rotation.yaw);
            draw_ginja_model_with_motion((s32)get_bml_model((BmlResource *)(*(s32 *)&TOKeyJungleMain__static_model_resource), 1), get_bml_motion((*(s32 *)&TOKeyJungleMain__static_model_resource), 1), key_jungle_main->m_e8);
            TParticleCtrl::begin_effect_render();
            draw_ginja_model_with_motion((s32)get_bml_model((BmlResource *)(*(s32 *)&TOKeyJungleMain__static_model_resource), 0), get_bml_motion((*(s32 *)&TOKeyJungleMain__static_model_resource), 0), *(f32 *)((s8 *)key_jungle_main + 0xEC));
            TParticleCtrl::end_effect_render();
            pop_matrix();
            break;
        }
    }
}

typedef char RecoveredGlobal_8029D200_TOKeyJungleMain__data_804653C8_size[sizeof(RecoveredGlobal_8029D200_TOKeyJungleMain__data_804653C8) == 0xC ? 1 : -1];
void TOKeyJungleMain::send_switch_on() {
    dispatch_by_phase__15TOKeyJungleMainFlUs((void *)game_difficulty_selection, (int) (*(s32 *)((s8 *)(&(*(RecoveredGlobal_8029D200_TOKeyJungleMain__data_804653C8 *)&TOKeyJungleMain__data_804653C8).value) + (this->switch_id * 4))));
}

void TOKeyJungleMain::update_lock_state() {
    s32 temp_r31;
    if ((s32) this->mode != 2) {
        temp_r31 = this->is_on;
        if (TLevelSelect::get_difficulty_flag_bit(game_difficulty_selection, *(s32 *)((s8 *)&TOKeyJungleMain__data_804653C8.value + (this->switch_id * 4))) != 0) {
            this->is_on = 1;
        } else {
            this->is_on = 0;
        }
        if (temp_r31 != (s32) this->is_on) {
            this->play_activate_sound();
        }
    }
}

void TOKeyJungleMain::update_switch_on() {
    u8 *arg0 = (u8 *)this;
  unsigned int new_var;
  s32 bml_motion;
  s32 temp_r3_3;
  u32 temp_r3_2;
  new_var = 0;
  bml_motion = get_bml_motion((s32)((*(u8 * *)&TOKeyJungleMain__static_model_resource)), 1);
  this->m_e8 = (f32) ((this->m_e8) + lbl_805DDD38);
  temp_r3_2 = (*((s32 *) (((s8 *) bml_motion) + 4))) - 1;
  if ((this->m_e8) > ((f32) temp_r3_2))
  {
    this->m_e8 = (f32) temp_r3_2;
  }
  temp_r3_3 = get_bml_motion((s32)((*(u8 * *)&TOKeyJungleMain__static_model_resource)), new_var);
  *((f32 *) (((s8 *) arg0) + 0xEC)) = (f32) ((*((f32 *) (((s8 *) arg0) + 0xEC))) + lbl_805DDD38);
  temp_r3_2 = (*((s32 *) (((s8 *) temp_r3_3) + 4))) - 1;
  if ((*((f32 *) (((s8 *) arg0) + 0xEC))) > ((f32) temp_r3_2))
  {
    *((f32 *) (((s8 *) arg0) + 0xEC)) = (f32) lbl_805DDD3C;
  }
}

void TOKeyJungleMain::update_switch_off() {
    struct VObj_8029D3A4_8029CF68 *o = (struct VObj_8029D3A4_8029CF68 *)this;
    o->m18();
}
void *__dt__15TOKeyJungleMainFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__15TOKeyJungleMain;
        ((TObjCollidable *)arg0)->unregister_object_by_id();
        free_collision_body_parts(arg0);
        __dt__5TOKeyFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

typedef char RecoveredGlobal_8029D438_lbl_804DC5A0_size[sizeof(RecoveredGlobal_8029D438_lbl_804DC5A0) == 0x2C ? 1 : -1];
typedef char RecoveredGlobal_8029D438___vt__15TOKeyJungleMain_size[sizeof(RecoveredGlobal_8029D438___vt__15TOKeyJungleMain) == 0x74 ? 1 : -1];
u8 *TOKeyJungleMain__ct(TOKeyJungleMain *key_jungle_main, s32 arg1, s32 arg2) {
    __ct__5TOKeyFP7TObject((key_jungle_main));
    *(s32 **)((s8 *)key_jungle_main + 0x18) = &(*(RecoveredGlobal_8029D438___vt__15TOKeyJungleMain *)&__vt__15TOKeyJungleMain).value;
    *(s32 *)((s8 *)key_jungle_main + 0) = (s32) lbl_805D3D50;
    ((TOKeyJungleMain *)(key_jungle_main))->apply_object_set_data((void *)arg2);
    ((TOKey *)key_jungle_main)->init_switch_id();
    init_collision_body_parts(key_jungle_main, &TOKeyJungleMain_collision_body_parts.value, 1);
    ((TObjCollidable *)key_jungle_main)->refresh_collision_body_centers();
    ((TObjPlayer *)key_jungle_main)->register_object_by_id();
    key_jungle_main->mode = 0;
    key_jungle_main->switch_id = (s32) key_jungle_main->set_params[0];
    if ((s32) key_jungle_main->switch_id < 0) {
        key_jungle_main->switch_id = 0;
    }
    if ((s32) key_jungle_main->switch_id > 2) {
        key_jungle_main->switch_id = 2;
    }
    key_jungle_main->m_e8 = (f32) lbl_805DDD3C;
    *(f32 *)((s8 *)key_jungle_main + 0xEC) = (f32) lbl_805DDD3C;
    return (u8 *)key_jungle_main;
}
}
