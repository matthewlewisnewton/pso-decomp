#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/misc/ParticleFactory.h"
#include "pso/system/CurrentTextureList.h"
#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/system/NinjaUtil.h"
#include "pso/TMainTask.h"
#include "pso/render/render_util.h"
#include "pso/TObject.h"
#include "pso/misc/TOTrap.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjChara.h"
#include "pso/misc/TOTrapSeabed01.h"
#include "pso/object/TObjMotion.h"
#include "pso/player/TObjPlayer_80083594.h"

#include "pso/system/vector.h"

#include "pso/object/TObjDoorJung.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/TOTrapAncient02.h"
#include "pso/misc/TRaderMapCore.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer_801AF2F0.h"
#include "pso/system/BmlResource.h"
#include "pso/object/TObjFish_8001ED90.h"
#include "pso/system/ModelDrawContext.h"
#include "pso/system/MatrixStack.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/misc/TOTrapAncient01.h"
#include "pso/player/TUnk_804B6C24.h"
#include "pso/ui/TAdEnterPasswordGC.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/system/GinjaMaterial.h"
#include "pso/misc/TLobby_80226070.h"
#include <dolphin/base/PPCArch.h>
#include "pso/TObjSuisoChip.h"
#include "pso/math/MatrixVector.h"
#include "pso/unk/text_803D853C.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/system/GinjaUvScroll.h"
#include "pso/system/GinjaTexture.h"
#include "pso/misc/TLanguage_801E4874.h"





struct SeabedTrapFragmentSpawn {
    s32 id;
    Vec pos;
    s32 arg;
};

extern "C" {
extern s32 local_client_id;

extern TObjChipParams TOTrapSeabed01__transform_params;
extern SeabedTrapFragmentSpawn seabed_trap_fragment_spawns[];
extern BmlResource *TOTrapSeabed01__bml_resource;
extern GinjaTextureList *TOTrapSeabed01__texture_file;
extern const char *lbl_805D3530;


extern NJS_OBJECT *TOTrapSeabed01__ginja_model;







}



extern "C" {


extern s32 actor_frame_tick;
extern s32 lbl_805D681C;
extern s32 seabed01_ginja_mesh_index;



}



#include "pso/object/TObjSeabedSuisoBrakable.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"



extern "C" {
extern CollisionBody seabed_trap_collision_body;
extern const char *TOTrapSeabed01_class_name;
extern char lbl_804720E8[];
extern char lbl_80472100[];
extern BmlResourceDescriptor seabed_trap_resource_descriptor;

extern s32 trap_seabed01_param_index_table[];




inline f32 clampf_802CA5F4(f32 lo, f32 hi, f32 v) {
    f32 r;
    if (lo > v) {
        r = lo;
    } else if (hi < v) {
        r = hi;
    } else {
        r = v;
    }
    return r;
}
inline s32 CLAMPI(s32 v, s32 lo, s32 hi) {
    s32 r;
    if (v < lo) {
        r = lo;
    } else {
        r = hi;
        if (v <= hi) {
            r = v;
        }
    }
    return r;
}
inline s32 clampi_802CA5F4(s32 lo, s32 hi, s32 v) {
    if (v < lo) {
        return lo;
    }
    if (v > hi) {
        return hi;
    }
    return v;
}







extern const char lbl_80471FB8[];
extern const char lbl_80471FD0[];
extern const char lbl_80471FF0[];
extern const char lbl_80472010[];
extern const char lbl_80472028[];
const char *seabed_trap_model_filenames[4] = { lbl_80471FB8, lbl_80471FD0, lbl_80471FF0, 0 };
__declspec(section ".data") const char *seabed_trap_motion_filenames[2] = { lbl_80472010, 0 };
BmlResourceDescriptor seabed_trap_resource_descriptor = { lbl_80472028, seabed_trap_model_filenames, seabed_trap_motion_filenames, 3, 1 };
CollisionBody seabed_trap_collision_body = { { 0.0f, 20.0f, 0.0f }, 14.0f, 0.0f, 0, 0x08011F04, { 0.0f, 0.0f, 0.0f }, 0.0f };
SeabedTrapFragmentSpawn seabed_trap_fragment_spawns[6] = {
    { 2, { 9.0f, 21.0f, 9.0f }, -24576 },
    { 2, { 9.0f, 21.0f, -9.0f }, -8192 },
    { 2, { -9.0f, 21.0f, 9.0f }, 24576 },
    { 2, { -9.0f, 21.0f, -9.0f }, 8192 },
    { 1, { -4.0f, 0.0f, -4.0f }, 0 },
    { 1, { 4.0f, 0.0f, 4.0f }, 32768 },
};

}

// Reverse definitions with deferred generation reproduce this unit's original
// function order and generate the inline TOTrap slots first.

TOTrapSeabed01::TOTrapSeabed01(TObject *parent, void *creator) : TOTrap(parent, creator) {
    m_name = TOTrapSeabed01_class_name;
    apply_object_set_data(creator);
    model = get_bml_model(TOTrapSeabed01__bml_resource, 0);
    current_motion = (NJS_MOTION *)get_bml_motion(TOTrapSeabed01__bml_resource, 0);
    play_speed = 1.0f;
    frame = 0.0f;
    clamp_params_and_init();
    init_collision_body_parts(this, &seabed_trap_collision_body, 1);
    refresh_collision_body_centers();
    register_object_by_id();
    actorFlags |= 0x60040000;
    m_344 = 0;
    m_358 = -1;
}

TOTrapSeabed01::~TOTrapSeabed01() {
    unregister_object_by_id();
    free_collision_body_parts(this);
}

void TOTrapSeabed01::vfunc_6(s16 *arg1, s32 arg2) {
    if ((s16) *arg1 == 4) {
        if (arg2 == 1) {
            play_sounds();
        }
        s32 tmp = this->m_358;
        if (tmp >= 0) {
            stop_sound_request(tmp);
            tmp = -1;
            this->m_358 = tmp;
        }
        sub_802C9D38();
        set_flag8();
        queue_destruction();
    }
}

void TOTrapSeabed01::load_resources() {
    TOTrapSeabed01__bml_resource = new BmlResource(5, &seabed_trap_resource_descriptor, 0, 0, NULL);
    TOTrapSeabed01__texture_file = load_gvm_texture_file(lbl_804720E8);
    NJS_OBJECT *n = find_object_node(get_bml_model(TOTrapSeabed01__bml_resource, 0), 5);
    GinjaTextureList *t = TOTrapSeabed01__texture_file;
    TOTrapSeabed01__ginja_model = n;
    lbl_805D681C = 0;
    seabed01_ginja_mesh_index = -1;
    if (t != NULL) {
        seabed01_ginja_mesh_index = t->find_entry_by_name(lbl_80472100);
    }
}

void TOTrapSeabed01::free_static_resources() {
    if (TOTrapSeabed01__texture_file != NULL) {
        release_texture_list(TOTrapSeabed01__texture_file);
        TAdSinglePlyChrSelectGC::safe_free((void *)TOTrapSeabed01__texture_file);
        TOTrapSeabed01__texture_file = NULL;
    }
    if (TOTrapSeabed01__bml_resource != NULL) {
        delete TOTrapSeabed01__bml_resource;
        TOTrapSeabed01__bml_resource = NULL;
    }
}

void *TOTrapSeabed01::create(void *arg0) {
    return new TOTrapSeabed01(tl_05, arg0);
}

void TOTrapSeabed01::clamp_params_and_init() {
    this->scale.x = clampf_802CA5F4(0.1f, 10.0f, this->scale.x);
    this->set_params[0] = CLAMPI(this->set_params[0], 1, 0x3C);
    this->set_params[1] = CLAMPI(this->set_params[1], 0, 1);
    this->mode = 0;
    this->range = 15.0f;
    this->dist = 15.0f;
    this->m_348 = (s32) (30.0f * (f32) this->set_params[0]);
    if (this->set_params[1] != 0) {
        this->m_34c = 1;
    } else {
        this->m_34c = 0;
    }
    this->play_speed = this->scale.x;
    if (this->scale.y < 0.0f) {
        this->scale.y = 0.0f;
    }
    this->attack.power = this->vfunc_87(this->scale.y);
    this->set_params[2] = CLAMPI(this->set_params[2], 0, 5);
    this->attack.kind = trap_seabed01_param_index_table[this->set_params[2]];
}

void TOTrapSeabed01::vfunc_84() {  }

void TOTrapSeabed01::render() {
    if (TMainTask::get_render_pass() != 1 && (m_34c == 0 || is_split_screen() != 0 || TAdEnterPasswordGC::dispatch_input_to_instance(this) == 0) && m_340 == 1) {
        switch (mode) {
        case 0:
        case 1:
            draw();
            break;
        case 2:
        case 3:
            render_effect_layers();
            break;
        }
    }
}

void TOTrapSeabed01::draw() {
    if ((TRaderMapCore::is_not_split_screen() != 1) || (m_34c == 0)) {
        set_depth_buffer_settings_3();
        set_draw_list_mask(1);
        TParticleCtrl::begin_effect_render();
        set_current_texture_list(TOTrapSeabed01__texture_file);
        push_matrix();
        post_translate_matrix(&position.x);
        rotate_matrix_y(NULL, rotation.yaw);
        draw_object_tree((NJS_OBJECT *)model);
        pop_matrix();
        TParticleCtrl::end_effect_render();
        restore_draw_list_mask();
        restore_saved_depth_alpha_state();
    }
}

void TOTrapSeabed01::draw_object_tree(NJS_OBJECT *object) {
    u32 flags;
    NJS_OBJECT *child;
    do {
        flags = object->evalflags;
        push_matrix();
        if (!(flags & 1)) {
            post_translate_matrix(object->pos);
        }
        if (!(flags & 2)) {
            rotate_matrix_by_node_angles(object->ang, flags & 0x20);
        }
        if (!(flags & 4)) {
            scale_current_matrix(object->scl);
        }
        if (!(flags & 8)) {
            if (this->m_34c != 0) {
                setup_particle_tev(0);
                set_current_texture_list(TOTrapSeabed01__texture_file);
                load_projection_tex_matrix(0x38E);
                draw_ginja_model(object->model);
                reset_particle_tev();
            } else {
                draw_ginja_model(object->model);
            }
        }
        if (!(flags & 0x10)) {
            child = object->child;
            if (child != NULL) {
                draw_object_tree(child);
            }
        }
        pop_matrix();
        object = object->sibling;
    } while (object != NULL);
}

void TOTrapSeabed01::render_effect_layers() {
    set_current_texture_list(TOTrapSeabed01__texture_file);
    if ((s32) actor_frame_tick != (s32) lbl_805D681C) {
        if (TOTrapSeabed01__ginja_model != NULL && seabed01_ginja_mesh_index != -1) {
            scroll_ginja_mesh_uvs(TOTrapSeabed01__ginja_model->model, 0, -0x14, seabed01_ginja_mesh_index, 1);
            PPCSync();
        }
        lbl_805D681C = actor_frame_tick;
    }
    set_model_node_callback((s32)TOTrapSeabed01::trigger_by_id);
    push_matrix();
    post_translate_matrix(&position.x);
    rotate_matrix_y(NULL, rotation.yaw);
    set_depth_buffer_settings_3();
    set_draw_list_mask(1);
    draw_ginja_model_with_motion(model, current_motion, frame);
    restore_draw_list_mask();
    restore_saved_depth_alpha_state();
    TParticleCtrl::begin_effect_render();
    set_depth_buffer_settings_1();
    set_draw_list_mask(2);
    draw_ginja_model_with_motion(model, current_motion, frame);
    restore_draw_list_mask();
    restore_saved_depth_alpha_state();
    TParticleCtrl::end_effect_render();
    pop_matrix();
    set_model_node_callback((NULL));
}

void TOTrapSeabed01::trigger_by_id(u32 arg0) {
    if (arg0 == (u32) TOTrapSeabed01__ginja_model) {
        TParticleCtrl::begin_effect_render();
        return;
    }
    TParticleCtrl::end_effect_render();
}

void TOTrapSeabed01::vfunc_81() {
    u32 temp_r0;
    frame = frame + play_speed;
    temp_r0 = current_motion->nbFrame - 1;
    if (frame > (f32) temp_r0) {
        frame = (f32) temp_r0;
        mode = 3;
        calc_attach_pos();
        clear_player_status_flag(0, 0x08001F04U);
        set_indexed_flags(0, 0x8003);
        obj_clearFlags30(0x40000U);
        check_hold_player();
    }
}

void TOTrapSeabed01::vfunc_82() {
    s32 temp_r0;
    temp_r0 = this->m_348 - 1;
    this->m_348 = temp_r0;
    if (temp_r0 < 0) {
        bodies->radius = 15.0f;
        set_indexed_flags(0, 0x100);
        TObjPlayer::init_all_slots();
        check_object_collisions();
        vfunc_67(1.0f);
        receive_physical_attack(target, 1.0f);
    }
    submit_cursor_candidate(this, -1);
}

void TOTrapSeabed01::check_hold_player() {
    f32 temp_f0;
    f32 temp_f31;
    TObjPlayer *p;
    u32 id;
    target = NULL;
    player = find_nearest_visible_player(this, 0, range);
    id = player;
    if ((id != 0xFFFF) && (p = get_player_by_client_id(id), target = p, target != NULL)) {
        temp_f31 = horizontal_distance_squared(&target->position, &position);
        dist = dist - TObjPlayer__sub_8017A1A4(p, 0);
        temp_f0 = dist;
        if (temp_f31 < (temp_f0 * temp_f0)) {
            if (TRaderMapCore::is_not_split_screen() == 1) {
                send_6x2C_impose_hold(dist, p, &position, -1, 0);
            } else if (player == local_client_id) {
                send_6x2C_impose_hold(dist, p, &position, -1, 0);
            }
            sub_802C9C18(0);
            return;
        }
        player = 0xFFFF;
        target = NULL;
    }
}

int TOTrapSeabed01::vfunc_67(f32) {
    s32 i;
    TObjChara *p;
    for (i = 0; i < 0x10; i++) {
        p = (TObjChara *)TObjPlayer::get_battle_param(i);
        if (TObjPlayer::is_valid_and_active((u32)p) != 0 && p->check_value_equals(lbl_805D3530) != 0) {
            p->receive_direct_attack(this, attack, NULL, -1, -1);
            if (attack.kind < 5) {
                p->apply_knockback_from_attacker((u8 *)this, 0.0f);
            }
        }
    }
    return 1;
}

void TOTrapSeabed01::play_sounds() {
    Mtx34 m;
    TObjChipSpawnParams p;
    SeabedTrapFragmentSpawn *e;
    s32 i;
    f32 y;
    TObjChip::copy_transform(&p, &TOTrapSeabed01__transform_params);
    y = 0.0f;
    p.textures = (s32)TOTrapSeabed01__texture_file;
    for (i = 0; i < 6; i++) {
        e = &seabed_trap_fragment_spawns[i];
        VecCopy(&p.pos, &e->pos);
        p.model = (s32)get_bml_model(TOTrapSeabed01__bml_resource, e->id);
        p.arg = e->arg;
        new TObjSuisoChip(this, &p);
        Vec v = p.pos;
        v.y = y;
        set_matrix_identity((u8 *)m);
        translate_matrix_vec3((u8 *)m, (u8 *)&position);
        rotate_matrix_y(m, rotation.yaw);
        matrix_mult_vec(m, &v, &v);
        {
            TParticleCtrl *particle = spawn_particle_effect(&v, 0x8B);
            if (particle != NULL) {
                particle->set_scale(0.5f, 0.5f);
            }
        }
    }
    sub_802C9C18(1);
}

f32 TOTrapSeabed01::receive_physical_attack(void *source, f32 power) {
    sub_802C9D38();
    return TOTrap::receive_physical_attack(source, power);
}
