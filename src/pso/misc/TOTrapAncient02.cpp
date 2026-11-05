#include "pso/math/VectorNormalize.h"
#include "pso/misc/ParticleFactory.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/SoundEffect.h"
#include "pso/misc/PersistentSound.h"
#include "pso/math/ScratchVectorStorage.h"
#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/system/NinjaUtil.h"
#include "pso/TMainTask.h"
#include "pso/render/render_util.h"
#include "pso/TObject.h"
#include "pso/misc/TOTrap.h"
#include "pso/misc/TOTrap_801791EC.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjChara.h"
#include "pso/object/TObjMotion.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/misc/TOTrapAncient02.h"
#include "pso/misc/TOTrapAncient02R.h"
#include "pso/map/FloorArea.h"
#include "pso/player/TObjPlayer_80083594.h"

#include "pso/system/vector.h"

#include "pso/misc/TTecZonde.h"
#include "pso/TParticleCtrl.h"
#include "pso/boss/TObjBoss2Tunnel.h"

#include "pso/misc/TTecFoie.h"
#include "pso/misc/TTecGiBarta.h"
#include "pso/misc/TTecGiFoie.h"
#include "pso/misc/TTecMegid.h"
#include "pso/object/TObjFish.h"
#include "pso/object/TObjSeabedSuisoBrakable.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/math/MatrixVector.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/system/MatrixStack.h"
#include "pso/system/MatrixOps.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/system/BmlResource.h"
#include "pso/misc/TSwitch.h"
#include "pso/misc/TLobby.h"
#include "pso/ui/TAdEnterPasswordGC.h"
#include "pso/misc/TOTrapAncient01.h"
#include "pso/player/TObjPlayer_801AF2F0.h"
#include "pso/system/GinjaUvScroll.h"
#include "pso/system/GinjaMaterial.h"

extern "C" {


extern s32 local_client_id;


extern BmlResource *TOTrapAncient02__shared_resource;
extern const char *lbl_805D31B4;
extern const char *lbl_805D31B8;
extern s32 actor_frame_tick;
extern s32 game_difficulty_selection;
extern s32 lbl_805D5ADC;
extern void *lbl_805D5AE0;
extern s32 lbl_805D5AE4;

extern char lbl_80442E70[];
extern char lbl_80442E88[];
extern char lbl_80442EA4[];
extern char lbl_80442EC0[];
extern char lbl_80442ED8[];
extern char lbl_80442EF0[];
extern const char *lbl_805D31A8[];
extern const char *lbl_805D31AC[];
extern const char *lbl_805D31B0[];
// The model list and BML descriptor of each pillar: the torabasami default,
// the VR temple pillar and the jungle/seabed pillar.
struct TrapAncient02ResourceRecord {
    const char *model_filenames[2];
    BmlResourceDescriptor descriptor;
};
typedef char TrapAncient02ResourceRecord_size[(sizeof(TrapAncient02ResourceRecord) == 0x18) ? 1 : -1];
TrapAncient02ResourceRecord trap_ancient02_resources[3] = {
    { { lbl_80442E70, 0 }, { lbl_80442E88, trap_ancient02_resources[0].model_filenames, lbl_805D31A8, 1, 0 } },
    { { lbl_80442EA4, 0 }, { lbl_80442EC0, trap_ancient02_resources[1].model_filenames, lbl_805D31AC, 1, 0 } },
    { { lbl_80442ED8, 0 }, { lbl_80442EF0, trap_ancient02_resources[2].model_filenames, lbl_805D31B0, 1, 0 } },
};
CollisionBody trap_ancient02_collision_body = {
    { 0.0f, 8.5f, 0.0f }, 2.0f, 0.0f, 0, 0x38003, { 0.0f, 0.0f, 0.0f }, 0.0f
};











}

// Reverse definitions with deferred generation reproduce this unit's original
// function order.

void TOTrapAncient02R::init_trap_object_id() {
    s32 temp_r0;
    this->m_364 = (s32) this->set_params[1];
    temp_r0 = this->m_364;
    if ((temp_r0 < 0) || (temp_r0 >= 0x100)) {
        this->m_364 = -1;
    }
}

void TOTrapAncient02R::clamp_trap_level_param() {
    s32 temp_r0;
    this->m_35c = (s32) this->set_params[2];
    temp_r0 = this->m_35c;
    if (temp_r0 < 0) {
        this->m_35c = 0;
        return;
    }
    if (temp_r0 >= 5) {
        this->m_35c = 4;
    }
}

void TOTrapAncient02R::init_trap_param_clamped() {
    s32 temp_r0;
    this->m_368 = (s32) this->scale.y;
    temp_r0 = this->m_368;
    if (temp_r0 < 1) {
        this->m_368 = 1;
        return;
    }
    if (temp_r0 > 0x100) {
        this->m_368 = 0x100;
    }
}

f32 TOTrapAncient02R::receive_weapon_special_attack(void *, void *) {
    return receive_physical_attack(NULL, 1.0f);
}

f32 TOTrapAncient02R::receive_direct_attack(void *, DirectAttackPayload, void *, s32, s32) {
    return receive_physical_attack(NULL, 1.0f);
}

int TOTrapAncient02R::calc_distance_accuracy_penalty(void *, void *, void *, float) { return 1; }
s32 TOTrapAncient02R::select_melee_contact_body(void *, f32) { return 1; }
s32 TOTrapAncient02R::roll_physical_accuracy(void *, s32, f32) { return 1; }
s32 TOTrapAncient02R::try_start_action(s32, s32) { return 1; }
s32 TOTrapAncient02R::is_any_player_matching_stat() { return 0; }

void TOTrapAncient02R::submit_cursor_and_notify() {
    find_target_player();
}

TOTrapAncient02::TOTrapAncient02(TObject *parent, void *creator) : TOTrap(parent, creator) {
    this->m_name = lbl_805D31B4;
    this->apply_object_set_data(creator);
    this->initialize_position_copies();
    this->calc_attach_pos();
    this->model = (void *)TOTrapAncient02__shared_resource->models->model;
    this->texlist = TOTrapAncient02__shared_resource->models->m_c;
    this->mode = 0;
    this->phase = 0;
    this->range = 0.5f * this->scale.x + 30.0f;
    this->dist = this->range;
    this->reset = 30.0f + (f32)this->set_params[0];
    if (this->reset < 0) {
        this->reset = 0;
    }
    this->timer = this->reset;
    this->player = 0xFFFF;
    init_collision_body_parts(this, &trap_ancient02_collision_body, 1);
    this->refresh_collision_body_centers();
    this->actorFlags |= 0x60000000;
    this->register_object_by_id();
    this->h348 = 0.0f;
    this->h344 = 0.0f;
    this->m_34c = 0;
    if (this->rotation.roll > 0) {
        this->m_358 = 1;
    } else {
        this->m_358 = 0;
    }
}

TOTrapAncient02::~TOTrapAncient02() {
    unregister_object_by_id();
    free_collision_body_parts(this);
}

void TOTrapAncient02::load_resources() {
    TrapAncient02ResourceRecord *records = trap_ancient02_resources;
    BmlResource *obj;
    switch (get_current_floor_area()) {
    case AREA_VR_TEMPLE_ALPHA:
    case AREA_VR_TEMPLE_BETA:
        obj = new BmlResource(1, &records[1].descriptor, 0, 0, NULL);
        TOTrapAncient02__shared_resource = obj;
        lbl_805D5AE0 = find_object_node((NJS_OBJECT *)get_bml_model(obj, 0), 2)->model;
        lbl_805D5AE4 = 2;
        lbl_805D5ADC = 0;
        break;
    case AREA_CENTRAL_CONTROL_AREA:
    case AREA_JUNGLE_NORTH:
    case AREA_JUNGLE_EAST:
    case AREA_MOUNTAIN:
    case AREA_SEASIDE:
    case AREA_SEABED_UPPER:
    case AREA_SEABED_LOWER:
    case AREA_SEASIDE_NIGHT:
    case AREA_TOWER:
        obj = new BmlResource(1, &records[2].descriptor, 0, 0, NULL);
        TOTrapAncient02__shared_resource = obj;
        lbl_805D5AE0 = find_object_node((NJS_OBJECT *)get_bml_model(obj, 0), 2)->model;
        lbl_805D5AE4 = 1;
        lbl_805D5ADC = 0;
        break;
    default:
        obj = new BmlResource(1, &records[0].descriptor, 0, 0, NULL);
        TOTrapAncient02__shared_resource = obj;
        lbl_805D5AE0 = ((NJS_OBJECT *)obj->models->model)->child->child->model;
        lbl_805D5AE4 = 1;
        lbl_805D5ADC = 0;
        break;
    }
}

void TOTrapAncient02::destroy_instance() {
    if (TOTrapAncient02__shared_resource != NULL) {
        delete TOTrapAncient02__shared_resource;
        TOTrapAncient02__shared_resource = NULL;
    }
}

void *TOTrapAncient02::create(void *arg0) {
    return new TOTrapAncient02(tl_05, arg0);
}

void TOTrapAncient02::render() {
    if (TMainTask::get_render_pass() != 1) {
        this->m_340 = update_object_view_visibility(400.0f, 20.0f);
        if (((s32) this->m_340 == 1) && (((s32) this->m_358 == 0) || (is_split_screen() != 0) || (TAdEnterPasswordGC::dispatch_input_to_instance(this) == 0))) {
            set_draw_list_mask(3);
            if ((s32) this->m_358 != 0) {
                this->render_particle_chain();
            } else {
                this->draw_effect_chain();
            }
            restore_draw_list_mask();
        }
    }
}

void TOTrapAncient02::draw_effect_chain() {
    NJS_OBJECT *base;
    NJS_OBJECT *upper;
    NJS_OBJECT *head;
    NJS_OBJECT *side;

    push_matrix();
    set_current_texture_list((GinjaTextureList *)(this->texlist));
    post_translate_matrix(&this->position.x);
    rotate_matrix_y(NULL, this->rotation.yaw);
    base = (NJS_OBJECT *)this->model;
    translate_matrix(0, base->pos[0], base->pos[1] + this->h344, base->pos[2]);
    draw_ginja_model((s32)base->model);
    push_matrix();
    upper = base->child;
    translate_matrix(0, upper->pos[0], upper->pos[1] + this->h348, upper->pos[2]);
    draw_ginja_model((s32)upper->model);
    TParticleCtrl::begin_effect_render();
    push_matrix();
    head = upper->child;
    post_translate_matrix(head->pos);
    draw_ginja_model((s32)head->model);
    pop_matrix();
    push_matrix();
    side = head->sibling;
    post_translate_matrix(side->pos);
    rotate_matrix_y(NULL, this->m_34c);
    draw_ginja_model((s32)side->model);
    pop_matrix();
    TParticleCtrl::end_effect_render();
    pop_matrix();
    pop_matrix();
}

void TOTrapAncient02::render_particle_chain() {
    NJS_OBJECT *base;
    NJS_OBJECT *upper;
    NJS_OBJECT *head;
    NJS_OBJECT *side;

    push_matrix();
    post_translate_matrix(&this->position.x);
    rotate_matrix_y(NULL, this->rotation.yaw);
    base = (NJS_OBJECT *)this->model;
    translate_matrix(0, base->pos[0], base->pos[1] + this->h344, base->pos[2]);
    setup_particle_tev(0);
    set_current_texture_list((GinjaTextureList *)(this->texlist));
    load_projection_tex_matrix(0x38E);
    draw_ginja_model((s32)base->model);
    reset_particle_tev();
    push_matrix();
    upper = base->child;
    translate_matrix(0, upper->pos[0], upper->pos[1] + this->h348, upper->pos[2]);
    setup_particle_tev(0);
    set_current_texture_list((GinjaTextureList *)(this->texlist));
    load_projection_tex_matrix(0x38E);
    draw_ginja_model((s32)upper->model);
    reset_particle_tev();
    TParticleCtrl::begin_effect_render();
    push_matrix();
    head = upper->child;
    post_translate_matrix(head->pos);
    setup_particle_tev(1);
    set_current_texture_list((GinjaTextureList *)(this->texlist));
    load_projection_tex_matrix(0x38E);
    draw_ginja_model((s32)head->model);
    reset_particle_tev();
    pop_matrix();
    push_matrix();
    side = head->sibling;
    post_translate_matrix(side->pos);
    rotate_matrix_y(NULL, this->m_34c);
    setup_particle_tev(0);
    set_current_texture_list((GinjaTextureList *)(this->texlist));
    load_projection_tex_matrix(0x38E);
    draw_ginja_model((s32)side->model);
    reset_particle_tev();
    pop_matrix();
    TParticleCtrl::end_effect_render();
    pop_matrix();
    pop_matrix();
}

void TOTrapAncient02::vfunc_81() {
    TObjPlayer *p;
    f32 d;
    submit_cursor_candidate(this, -1);
    switch (this->phase) {
    case 0:
        if (this->h344 < 7.0f) {
            this->h344 += 1.0f;
        } else {
            this->phase = 1;
            this->h344 = 7.0f;
        }
        break;
    case 1:
        this->h348 += 1.0f;
        if (10.15f <= this->h348) {
            this->phase = 2;
            this->h348 = 10.15f;
        }
        break;
    case 2:
        this->player = find_nearest_visible_player(this, 0, this->range);
        if (this->player != 0xFFFF) {
            p = get_player_by_client_id(this->player);
            this->target = p;
            if (this->target != NULL) {
                d = horizontal_distance_squared(&this->target->position, &this->position);
                this->dist = this->range - TObjPlayer__sub_8017A1A4(p, 0);
                if (d < this->dist * this->dist) {
                    if (this->player == local_client_id) {
                        send_6x2C_impose_hold(this->dist, p, &this->position, this->timer, 0);
                    }
                    this->mode = 3;
                    this->phase = 2;
                } else {
                    this->player = 0xFFFF;
                    this->target = NULL;
                }
            }
        } else {
            this->target = NULL;
        }
        if (this->target == NULL) {
            this->phase = 3;
        }
        break;
    case 3:
        if (0.0f < this->h348) {
            this->h348 -= 1.0f;
        } else {
            this->phase = 4;
            this->h348 = 0.0f;
        }
        break;
    case 4:
        if (0.0f < this->h344) {
            this->h344 -= 1.0f;
        } else {
            this->mode = 0;
            this->phase = 0;
            this->h344 = 0.0f;
            this->player = 0xFFFF;
            this->target = NULL;
        }
        break;
    }
}

void TOTrapAncient02::vfunc_82() {
    TObjPlayer *p;
    submit_cursor_candidate(this, -1);
    switch (this->phase) {
    case 0:
    case 1:
        this->phase = 2;
    case 2:
        if (this->target != NULL) {
            obj_setFlags30(this->target, 0x200);
            this->target->sub_8002AE64();
            this->target->sub_800A7798(1.0f);
            this->timer--;
            if (this->timer < 0) {
                this->phase = 3;
                this->timer = this->reset;
                if (this->target != NULL && local_client_id == get_entity_id(this->target)) {
                    p = get_player_by_client_id(local_client_id);
                    if (p != 0 && p->check_player_flag1() != 0) {
                        TObjPlayer::send_code_45_1((s32)p);
                    }
                }
            }
        } else {
            this->phase = 3;
            this->timer = this->reset;
        }
        break;
    case 3:
        if (0.0f < this->h348) {
            this->h348 -= 1.0f;
        } else {
            this->phase = 4;
            this->h348 = 0.0f;
        }
        break;
    case 4:
        if (0.0f < this->h344) {
            this->h344 -= 1.0f;
        } else {
            this->mode = 0;
            this->phase = 0;
            this->h344 = 0.0f;
            this->player = 0xFFFF;
            this->target = NULL;
        }
        break;
    }
}

void TOTrapAncient02::vfunc_84() {
    if (lbl_805D5ADC != actor_frame_tick && lbl_805D5AE0 != NULL) {
        lbl_805D5ADC = actor_frame_tick;
        scroll_ginja_mesh_uvs(lbl_805D5AE0, 0, 0xE, lbl_805D5AE4, 1);
    }
    this->m_34c += 0x888;
    switch (this->mode) {
    case 1:
    case 2:
    case 3:
        switch (get_current_floor_area()) {
        case AREA_CAVE1:
        case AREA_CAVE2:
        case AREA_CAVE3:
            play_persistent_sound(0x4461B, this, &position, 0, 0);
            return;
        case AREA_MINE1:
        case AREA_MINE2:
            play_persistent_sound(0x4004C612, this, &position, 0, 0);
            return;
        case AREA_RUINS1:
        case AREA_RUINS2:
        case AREA_RUINS3:
            play_persistent_sound(0x4004C618, this, &position, 0, 0);
            return;
        case AREA_VR_SPACESHIP_ALPHA:
        case AREA_VR_SPACESHIP_BETA:
            play_persistent_sound(0x4004C610, this, &position, 0, 0);
        case AREA_PIONEER2_EP1:
            return;
        case AREA_FOREST1:
            return;
        case AREA_FOREST2:
            return;
        case AREA_DRAGON:
            return;
        case AREA_DE_ROL_LE:
            return;
        case AREA_VOL_OPT:
            return;
        case AREA_DARK_FALZ:
            return;
        case AREA_LOBBY:
            return;
        case AREA_BATTLE1:
            return;
        case AREA_BATTLE2:
            return;
        case AREA_PIONEER2_EP2:
            return;
        case AREA_VR_TEMPLE_ALPHA:
            return;
        case AREA_VR_TEMPLE_BETA:
            return;
        }
        break;
    }
}

void TOTrapAncient02::vfunc_88() {  }

void TOTrapAncient02::vfunc_86() {  }

TOTrapAncient02R::TOTrapAncient02R(TObject *parent, void *creator) : TOTrapAncient02(parent, creator) {
    this->m_name = lbl_805D31B8;
    this->apply_object_set_data(creator);
    this->initialize_position_copies();
    this->calc_attach_pos();
    this->model = (void *)TOTrapAncient02__shared_resource->models->model;
    this->texlist = TOTrapAncient02__shared_resource->models->m_c;
    this->mode = 0;
    this->phase = 0;
    this->range = 0.5f * this->scale.x + 30.0f;
    this->dist = this->range;
    this->reset = (s32) (30.0f + (f32) this->set_params[0]);
    if (this->reset < 0) {
        this->reset = 0;
    }
    this->timer = this->reset;
    this->init_trap_object_id();
    this->clamp_trap_level_param();
    this->calc_trap_count();
    this->init_trap_param_clamped();
    this->player = 0xFFFF;
    this->target = NULL;
    this->h348 = 0.0f;
    this->h344 = 0.0f;
    this->m_34c = 0;
    if (this->rotation.roll > 0) {
        this->m_358 = 1;
    } else {
        this->m_358 = 0;
    }
}

TOTrapAncient02R::~TOTrapAncient02R() {
}

void *TOTrapAncient02R::create(void *arg0) {
    return new TOTrapAncient02R(tl_05, arg0);
}

f32 TOTrapAncient02R::receive_physical_attack(void *, f32) {
    s16 msg;
    if (entity_id >= 0x4000 && set_entry != NULL) {
        Vec v = position;
        v.y += h344 + h348;
        spawn_particle_effect(&v, 0x1D0);
        spawn_particle_effect(&v, 1);
        if (--m_368 <= 0) {
            m_368 = 0;
            if (access_object_saved_state(&msg, 1) != 0) {
                mode = 4;
                msg = mode;
                send_object_state_update(&msg);
                access_object_saved_state(&msg, 0);
                vfunc_6(&msg, 1);
            }
        }
    }
    return 0.0f;
}

void TOTrapAncient02R::find_target_player() {
    clear_player_status_flag(0, 1);
    calc_attach_pos();
    if (this->m_364 == -1 || is_current_floor_switch_set((u16)this->m_364) == 1) {
        this->player = find_nearest_visible_player(this, 0, this->range);
        if (this->player != 0xFFFF) {
            this->target = get_player_by_client_id(this->player);
            if (this->target != NULL) {
                if (horizontal_distance_squared(&this->target->position, &position) < this->range * this->range) {
                    this->mode = 2;
                }
            } else {
                this->player = 0xFFFF;
                this->target = NULL;
            }
        } else {
            this->target = NULL;
        }
    }
}

void TOTrapAncient02R::vfunc_81() {
    f32 d;
    s32 ang;
    set_indexed_flags(0, 1);
    submit_cursor_candidate(this, -1);
    switch (phase) {
    case 0:
        if (h344 < 7.0f) {
            h344 += 1.0f;
        } else {
            phase = 1;
            h344 = 7.0f;
        }
        break;
    case 1:
        h348 += 1.0f;
        if (10.15f <= h348) {
            phase = 2;
            h348 = 10.15f;
        }
        break;
    case 2:
        player = find_nearest_visible_player(this, 0, range);
        if (player != 0xFFFF) {
            TObjPlayer *p = get_player_by_client_id(player);
            target = p;
            if (target != NULL && p->get_floor() == get_current_floor() &&
                (target->alt_room == alt_room || target->room == room || target->room == alt_room)) {
                d = horizontal_distance_squared(&target->position, &position);
                dist = range + get_collision_body_radius(target, 0);
                if (d < dist * dist) {
                    mode = 3;
                    phase = 2;
                    VecCopy(&scratch_vec.vector, &position);
                    scratch_vec.vector.y += h344 + h348;
                    VecCopy(&lbl_8050BF00.vector, &target->body_center_position);
                    subtract_vector((&lbl_8050BF00.vector), (&scratch_vec.vector));
                    if (normalize_vector_checked(&lbl_8050BF00.vector) < 0.00001f) {
                        lbl_8050BF00.vector.x = lbl_8050BF00.vector.y = 0.0f;
                        lbl_8050BF00.vector.z = 1.0f;
                        push_matrix_from(&identity_matrix);
                        rotate_matrix_y(NULL, rotation.yaw);
                        rotate_vector_by_matrix(0, (&lbl_8050BF00.vector), (&lbl_8050BF00.vector));
                        pop_matrix();
                    }
                    ang = 10430.38043493439 * atan2_float(lbl_8050BF00.vector.x, lbl_8050BF00.vector.z);
                    switch (m_35c) {
                    case 1: {
                        DirectAttackPayload dmg;
                        dmg.kind = 3;
                        dmg.power = vfunc_87(20.0f * (f32)m_360 + 240.0f);
                        target->receive_direct_attack(this, dmg, NULL, -1, -1);
                        spawn_particle_effect(&scratch_vec.vector, 0xB9);
                        spawn_particle_effect(&scratch_vec.vector, 0xBA);
                        {
                            void *t = TObject::operator new(0x260);
                            if (t != NULL) {
                                ((TTecZonde *)t)->construct_bolt_effect((u8 *)tl_07, (u8 *)(&scratch_vec.vector), (u8 *)(&lbl_8050BF00.vector), 0x14000000, 0x14, range, 1.8f);
                            }
                        }
                        play_sound_effect(0x4002A408, &scratch_vec.vector, 0, 0);
                        break;
                    }
                    case 0:
                        TTecFoie::create_ex(this, &scratch_vec.vector, &target->body_center_position, (void *)m_360);
                        break;
                    case 2:
                        ((TTecGiBarta *)this)->create_ex((void *)(&scratch_vec.vector), (void *)ang, (void *)m_360);
                        break;
                    case 3:
                        TTecMegid::create((s32)this, (s32)(&scratch_vec.vector), (s32)&target->body_center_position, m_360);
                        break;
                    case 4:
                        TTecGiFoie::create(this, &scratch_vec.vector, (void *)m_360);
                        break;
                    }
                } else {
                    player = 0xFFFF;
                    target = NULL;
                }
            } else {
                player = 0xFFFF;
                target = NULL;
            }
        } else {
            target = NULL;
        }
        if (target == NULL) {
            phase = 3;
        }
        break;
    case 3:
        if (0.0f < h348) {
            h348 -= 1.0f;
        } else {
            phase = 4;
            h348 = 0.0f;
        }
        break;
    case 4:
        if (0.0f < h344) {
            h344 -= 1.0f;
        } else {
            mode = 0;
            phase = 0;
            h344 = 0.0f;
            player = 0xFFFF;
            target = NULL;
        }
        break;
    }
}

void TOTrapAncient02R::vfunc_82() {
    f32 temp_f1;
    f32 temp_f1_2;
    set_indexed_flags(0, 1);
    submit_cursor_candidate(this, -1);
    switch (this->phase) {
    case 0:
    case 1:
        this->phase = 2;
    case 2:
        this->timer = (this->timer - 1);
        if ((s32) this->timer < 0) {
            this->phase = 3;
            this->timer = (s32) this->reset;
        }
        break;
    case 3:
        if (0.0f < this->h348) {
            this->h348 -= 1.0f;
            return;
        }
        this->phase = 4;
        this->h348 = 0.0f;
        return;
    case 4:
        if (0.0f < this->h344) {
            this->h344 -= 1.0f;
            return;
        }
        this->mode = 0;
        this->phase = 0;
        this->h344 = 0.0f;
        this->player = 0xFFFF;
        this->target = 0;
        break;
    }
}

void TOTrapAncient02R::calc_trap_count() {
    s32 temp_r4;

    this->m_360 = (s32) (this->scale.z + ((2.0f * (f32) game_difficulty_selection) + 1.0f));
    temp_r4 = this->m_360;
    if (temp_r4 < 0) {
        this->m_360 = 0;
        return;
    }
    if ((s32) game_difficulty_selection == 3) {
        if (temp_r4 > 0x1D) {
            this->m_360 = 0x1D;
        }
    } else if (temp_r4 > 0xE) {
        this->m_360 = 0xE;
    }
}
