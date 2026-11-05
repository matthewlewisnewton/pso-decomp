#include "pso/math/VectorNormalize.h"
#include "pso/misc/ParticleFactory.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/SoundEffect.h"
#include "pso/misc/PersistentSound.h"
#include "pso/math/ScratchVectorStorage.h"
#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/system/NinjaUtil.h"
#include "pso/TMainTask.h"
#include "pso/render/render_util.h"
#include "pso/TObject.h"
#include "pso/misc/TOTrap.h"
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
#include "pso/unk/text_803D8F74.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/system/BmlResource.h"
#include "pso/misc/TSwitch.h"
#include "pso/system/GinjaUvScroll.h"
#include "pso/system/GinjaMaterial.h"

extern "C" {

void submit_cursor_candidate(void *, s32);
void *get_player_by_client_id(s32 i);

extern const f64 lbl_80442F38;
extern u8 identity_matrix[];
extern const f32 lbl_805DBA78;
extern const f32 lbl_805DBA80;
extern const f32 lbl_805DBA84;
extern const f32 lbl_805DBA88;
extern const f32 lbl_805DBA8C;
extern const f32 lbl_805DBA90;
extern const f32 lbl_805DBA94;
extern const f32 lbl_805DBA98;
f32 TObjPlayer__sub_8017A1A4(void *, s32);
void send_6x2C_impose_hold(void *, void *, s32, s32, f32);
extern s32 local_client_id;
s32 check_player_flag1__6TLobbyFv();
void *__dt__6TOTrapFv(void *arg0, s16 arg1);
void * TOTrap__ct(void *, void *, void *);
TOTrapAncient02R *TOTrapAncient02R__ct(TOTrapAncient02R *arg0, void *arg1, void *arg2);
void * __dt__15TOTrapAncient02Fv(void *arg0, s16 arg1);
TOTrapAncient02 *TOTrapAncient02__ct(TOTrapAncient02 *self, void *parent, void *creator);

void __dl__7TObjectFPv(void *);
s32 dispatch_input_to_instance__18TAdEnterPasswordGCFi(void *);

extern BmlResource *TOTrapAncient02__shared_resource;
extern s32 __vt__15TOTrapAncient02[];
extern const char *lbl_805D31B4;
extern const char *lbl_805D31B8;
extern s32 actor_frame_tick;
extern s32 game_difficulty_selection;
extern s32 lbl_805D5ADC;
extern void *lbl_805D5AE0;
extern s32 lbl_805D5AE4;
extern const f32 lbl_805DBA7C;
extern const f32 lbl_805DBA9C;
extern const f32 lbl_805DBAA0;
extern const f32 lbl_805DBAA4;

extern char lbl_80442E70[];
extern char lbl_80442E88[];
extern char lbl_80442EA4[];
extern char lbl_80442EC0[];
extern char lbl_80442ED8[];
extern char lbl_80442EF0[];
extern const char *lbl_805D31A8[];
extern const char *lbl_805D31AC[];
extern const char *lbl_805D31B0[];
struct TrapAncient02ResourceDescriptor {
    const char *bml_filename;
    const char *const *model_filenames;
    const char *const *motion_filenames;
    s16 model_count;
    s16 motion_count;
};
struct TrapAncient02ResourceRecord {
    const char *model_filenames[2];
    TrapAncient02ResourceDescriptor descriptor;
};
typedef char TrapAncient02ResourceDescriptor_size[(sizeof(TrapAncient02ResourceDescriptor) == 0x10) ? 1 : -1];
typedef char TrapAncient02ResourceRecord_size[(sizeof(TrapAncient02ResourceRecord) == 0x18) ? 1 : -1];
TrapAncient02ResourceRecord trap_ancient02_torabasami_resources = {
    { lbl_80442E70, 0 },
    { lbl_80442E88, trap_ancient02_torabasami_resources.model_filenames, lbl_805D31A8, 1, 0 }
};
TrapAncient02ResourceRecord trap_ancient02_ruins_pillar_resources = {
    { lbl_80442EA4, 0 },
    { lbl_80442EC0, trap_ancient02_ruins_pillar_resources.model_filenames, lbl_805D31AC, 1, 0 }
};
TrapAncient02ResourceRecord trap_ancient02_seabed_pillar_resources = {
    { lbl_80442ED8, 0 },
    { lbl_80442EF0, trap_ancient02_seabed_pillar_resources.model_filenames, lbl_805D31B0, 1, 0 }
};
CollisionBody trap_ancient02_collision_body = {
    { 0.0f, 8.5f, 0.0f }, 2.0f, 0.0f, 0, 0x38003, { 0.0f, 0.0f, 0.0f }, 0.0f
};
extern s32 __vt__16TOTrapAncient02R[];











}
void setup_particle_tev(s32 arg0);

// Reverse definitions with deferred generation reproduce this unit's original
// function order.

void TOTrapAncient02R::submit_cursor_and_notify() {
    find_target_player();
}

#pragma push
#pragma fp_contract on
TOTrapAncient02 *TOTrapAncient02__ct(TOTrapAncient02 *self, void *parent, void *creator) {
    TOTrap__ct(self, parent, creator);
    *(s32 **)((s8 *)self + 0x18) = __vt__15TOTrapAncient02;
    self->m_name = lbl_805D31B4;
    self->apply_object_set_data(creator);
    self->initialize_position_copies();
    self->calc_attach_pos();
    self->model = (void *)TOTrapAncient02__shared_resource->models->model;
    self->texlist = TOTrapAncient02__shared_resource->models->m_c;
    self->mode = 0;
    self->phase = 0;
    self->range = lbl_805DBAA0 * self->scale.x + lbl_805DBA9C;
    self->dist = self->range;
    self->reset = lbl_805DBA9C + (f32)self->set_params[0];
    if (self->reset < 0) {
        self->reset = 0;
    }
    self->timer = self->reset;
    self->player = 0xFFFF;
    init_collision_body_parts(self, &trap_ancient02_collision_body, 1);
    self->refresh_collision_body_centers();
    self->actorFlags |= 0x60000000;
    self->register_object_by_id();
    self->h348 = lbl_805DBA80;
    self->h344 = lbl_805DBA80;
    self->m_34c = 0;
    if (self->rotation.roll > 0) {
        self->m_358 = 1;
    } else {
        self->m_358 = 0;
    }
    return self;
}
#pragma pop

void *__dt__15TOTrapAncient02Fv(void *trap, s16 arg1) {
    if (trap != NULL) {
        *(s32 **)((s8 *)trap + 0x18) = __vt__15TOTrapAncient02;
        ((TObjCollidable *)trap)->unregister_object_by_id();
        free_collision_body_parts((TObjCollidable *)trap);
        __dt__6TOTrapFv(trap, 0);
        if (arg1 > 0) {
            ((s32 (*)(void *))__dl__7TObjectFPv)(trap);
        }
    }
    return trap;
}

void TOTrapAncient02::load_resources() {
    char *base = (char *)&trap_ancient02_torabasami_resources;
    BmlResource *obj;
    switch (get_current_floor_area()) {
    case AREA_VR_TEMPLE_ALPHA:
    case AREA_VR_TEMPLE_BETA:
        obj = new BmlResource(1, (BmlResourceDescriptor *)(base + 0x20), 0, 0, (void *)(0));
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
        obj = new BmlResource(1, (BmlResourceDescriptor *)(base + 0x38), 0, 0, (void *)(0));
        TOTrapAncient02__shared_resource = obj;
        lbl_805D5AE0 = find_object_node((NJS_OBJECT *)get_bml_model(obj, 0), 2)->model;
        lbl_805D5AE4 = 1;
        lbl_805D5ADC = 0;
        break;
    default:
        obj = new BmlResource(1, (BmlResourceDescriptor *)(base + 8), 0, 0, (void *)(0));
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
    TOTrapAncient02 *o = (TOTrapAncient02 *)TObject::operator new(sizeof(TOTrapAncient02));
    if (o != NULL) {
        o = TOTrapAncient02__ct(o, tl_05, arg0);
    }
    return o;
}

void TOTrapAncient02::render() {
    if (TMainTask::get_render_pass() != 1) {
        this->m_340 = update_object_view_visibility(lbl_805DBAA4, lbl_805DBA94);
        if (((s32) this->m_340 == 1) && (((s32) this->m_358 == 0) || (is_split_screen() != 0) || (dispatch_input_to_instance__18TAdEnterPasswordGCFi(this) == 0))) {
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
    void *p;
    f32 d;
    submit_cursor_candidate(this, -1);
    switch (this->phase) {
    case 0:
        if (this->h344 < lbl_805DBA84) {
            this->h344 += lbl_805DBA78;
        } else {
            this->phase = 1;
            this->h344 = lbl_805DBA84;
        }
        break;
    case 1:
        this->h348 += lbl_805DBA78;
        if (lbl_805DBA88 <= this->h348) {
            this->phase = 2;
            this->h348 = lbl_805DBA88;
        }
        break;
    case 2:
        this->player = find_nearest_visible_player(this, 0, this->range);
        if (this->player != 0xFFFF) {
            p = (void *)get_player_by_client_id((this->player));
            this->target = (u8 *)p;
            if (this->target != NULL) {
                d = horizontal_distance_squared((const Vec *)((u8 *)this->target + 0x38), (const Vec *)&this->position);
                this->dist = this->range - TObjPlayer__sub_8017A1A4(p, 0);
                if (d < this->dist * this->dist) {
                    if (this->player == local_client_id) {
                        send_6x2C_impose_hold(p, &this->position, this->timer, 0, this->dist);
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
        if (lbl_805DBA80 < this->h348) {
            this->h348 -= lbl_805DBA78;
        } else {
            this->phase = 4;
            this->h348 = lbl_805DBA80;
        }
        break;
    case 4:
        if (lbl_805DBA80 < this->h344) {
            this->h344 -= lbl_805DBA78;
        } else {
            this->mode = 0;
            this->phase = 0;
            this->h344 = lbl_805DBA80;
            this->player = 0xFFFF;
            this->target = NULL;
        }
        break;
    }
}

void TOTrapAncient02::vfunc_82() {
    s32 p;
    submit_cursor_candidate(this, -1);
    switch (this->phase) {
    case 0:
    case 1:
        this->phase = 2;
    case 2:
        if (this->target != NULL) {
            obj_setFlags30(this->target, 0x200);
            ((TObjEnemy *)(this->target))->sub_8002AE64();
            ((TObjEnemy *)(this->target))->sub_800A7798(lbl_805DBA78);
            this->timer--;
            if (this->timer < 0) {
                this->phase = 3;
                this->timer = this->reset;
                if (this->target != NULL && local_client_id == get_entity_id((TObjChara *)this->target)) {
                    p = (s32)get_player_by_client_id(local_client_id);
                    if (p != 0 && check_player_flag1__6TLobbyFv() != 0) {
                        TObjPlayer::send_code_45_1(p);
                    }
                }
            }
        } else {
            this->phase = 3;
            this->timer = this->reset;
        }
        break;
    case 3:
        if (lbl_805DBA80 < this->h348) {
            this->h348 -= lbl_805DBA78;
        } else {
            this->phase = 4;
            this->h348 = lbl_805DBA80;
        }
        break;
    case 4:
        if (lbl_805DBA80 < this->h344) {
            this->h344 -= lbl_805DBA78;
        } else {
            this->mode = 0;
            this->phase = 0;
            this->h344 = lbl_805DBA80;
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

#pragma push
#pragma fp_contract on
TOTrapAncient02R *TOTrapAncient02R__ct(TOTrapAncient02R *trap_ancient02_r, void *arg1, void *arg2) {
    TOTrapAncient02__ct(trap_ancient02_r, arg1, arg2);
    *(s32 **)((s8 *)trap_ancient02_r + 0x18) = __vt__16TOTrapAncient02R;
    trap_ancient02_r->m_name = lbl_805D31B8;
    trap_ancient02_r->apply_object_set_data(arg2);
    trap_ancient02_r->initialize_position_copies();
    trap_ancient02_r->calc_attach_pos();
    trap_ancient02_r->model = (void *)TOTrapAncient02__shared_resource->models->model;
    trap_ancient02_r->texlist = TOTrapAncient02__shared_resource->models->m_c;
    trap_ancient02_r->mode = 0;
    trap_ancient02_r->phase = 0;
    trap_ancient02_r->range = lbl_805DBAA0 * trap_ancient02_r->scale.x + lbl_805DBA9C;
    trap_ancient02_r->dist = trap_ancient02_r->range;
    trap_ancient02_r->reset = (s32) (lbl_805DBA9C + (f32) trap_ancient02_r->set_params[0]);
    if (trap_ancient02_r->reset < 0) {
        trap_ancient02_r->reset = 0;
    }
    trap_ancient02_r->timer = trap_ancient02_r->reset;
    trap_ancient02_r->init_trap_object_id();
    trap_ancient02_r->clamp_trap_level_param();
    trap_ancient02_r->calc_trap_count();
    trap_ancient02_r->init_trap_param_clamped();
    trap_ancient02_r->player = 0xFFFF;
    trap_ancient02_r->target = NULL;
    trap_ancient02_r->h348 = lbl_805DBA80;
    trap_ancient02_r->h344 = lbl_805DBA80;
    trap_ancient02_r->m_34c = 0;
    if (trap_ancient02_r->rotation.roll > 0) {
        trap_ancient02_r->m_358 = 1;
    } else {
        trap_ancient02_r->m_358 = 0;
    }
    return trap_ancient02_r;
}
#pragma pop

TOTrapAncient02R::~TOTrapAncient02R() {
}

#pragma push
#pragma fp_contract on
void *TOTrapAncient02R::create(void *arg0) {
    TOTrapAncient02R *o = (TOTrapAncient02R *)TObject::operator new(sizeof(TOTrapAncient02R));
    if (o != NULL) {
        o = TOTrapAncient02R__ct(o, tl_05, arg0);
    }
    return o;
}
#pragma pop

#pragma push
#pragma fp_contract on
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
    return lbl_805DBA80;
}
#pragma pop

#pragma push
#pragma fp_contract on
void TOTrapAncient02R::find_target_player() {
    clear_player_status_flag(0, 1);
    calc_attach_pos();
    if (this->m_364 == -1 || is_current_floor_switch_set((u16)this->m_364) == 1) {
        this->player = find_nearest_visible_player(this, 0, this->range);
        if (this->player != 0xFFFF) {
            this->target = (u8 *)get_player_by_client_id(this->player);
            if (this->target != NULL) {
                if (horizontal_distance_squared(&((TObjChara *)this->target)->position, &position) < this->range * this->range) {
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
#pragma pop

#pragma push
#pragma fp_contract on
void TOTrapAncient02R::vfunc_81() {
    f32 d;
    s32 ang;
    set_indexed_flags(0, 1);
    submit_cursor_candidate(this, -1);
    switch (phase) {
    case 0:
        if (h344 < lbl_805DBA84) {
            h344 += lbl_805DBA78;
        } else {
            phase = 1;
            h344 = lbl_805DBA84;
        }
        break;
    case 1:
        h348 += lbl_805DBA78;
        if (lbl_805DBA88 <= h348) {
            phase = 2;
            h348 = lbl_805DBA88;
        }
        break;
    case 2:
        player = find_nearest_visible_player(this, 0, range);
        if (player != 0xFFFF) {
            TObjPlayer *p = (TObjPlayer *)get_player_by_client_id(player);
            target = (u8 *)p;
            if (target != NULL && p->get_floor() == get_current_floor() &&
                (((TObjChara *)target)->alt_room == alt_room || ((TObjChara *)target)->room == room || ((TObjChara *)target)->room == alt_room)) {
                d = horizontal_distance_squared(&((TObjChara *)target)->position, &position);
                dist = range + get_collision_body_radius((TObjChara *)target, 0);
                if (d < dist * dist) {
                    mode = 3;
                    phase = 2;
                    VecCopy(&scratch_vec.vector, &position);
                    scratch_vec.vector.y += h344 + h348;
                    VecCopy(&lbl_8050BF00.vector, &((TObjChara *)target)->body_center_position);
                    subtract_vector((&lbl_8050BF00.vector), (&scratch_vec.vector));
                    if (normalize_vector_checked(&lbl_8050BF00.vector) < lbl_805DBA8C) {
                        lbl_8050BF00.vector.x = lbl_8050BF00.vector.y = lbl_805DBA80;
                        lbl_8050BF00.vector.z = lbl_805DBA78;
                        push_matrix_from(identity_matrix);
                        rotate_matrix_y(NULL, rotation.yaw);
                        rotate_vector_by_matrix(0, (&lbl_8050BF00.vector), (&lbl_8050BF00.vector));
                        pop_matrix();
                    }
                    ang = lbl_80442F38 * atan2_float(lbl_8050BF00.vector.x, lbl_8050BF00.vector.z);
                    switch (m_35c) {
                    case 1: {
                        DirectAttackPayload dmg;
                        dmg.kind = 3;
                        dmg.power = vfunc_87(lbl_805DBA94 * (f32)m_360 + lbl_805DBA90);
                        ((TObjChara *)target)->receive_direct_attack(this, dmg, NULL, -1, -1);
                        spawn_particle_effect((const Vec *)((&scratch_vec.vector)), 0xB9);
                        spawn_particle_effect((const Vec *)((&scratch_vec.vector)), 0xBA);
                        {
                            void *t = TObject::operator new(0x260);
                            if (t != NULL) {
                                ((TTecZonde *)t)->construct_bolt_effect((u8 *)tl_07, (u8 *)(&scratch_vec.vector), (u8 *)(&lbl_8050BF00.vector), 0x14000000, 0x14, range, (f32)lbl_805DBA98);
                            }
                        }
                        play_sound_effect(0x4002A408, (const Vec *)((&scratch_vec.vector)), 0, 0);
                        break;
                    }
                    case 0:
                        TTecFoie::create_ex(this, &scratch_vec.vector, &((TObjChara *)target)->body_center_position, (void *)m_360);
                        break;
                    case 2:
                        ((TTecGiBarta *)this)->create_ex((void *)(&scratch_vec.vector), (void *)ang, (void *)m_360);
                        break;
                    case 3:
                        TTecMegid::create((s32)this, (s32)(&scratch_vec.vector), (s32)&((TObjChara *)target)->body_center_position, m_360);
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
        if (lbl_805DBA80 < h348) {
            h348 -= lbl_805DBA78;
        } else {
            phase = 4;
            h348 = lbl_805DBA80;
        }
        break;
    case 4:
        if (lbl_805DBA80 < h344) {
            h344 -= lbl_805DBA78;
        } else {
            mode = 0;
            phase = 0;
            h344 = lbl_805DBA80;
            player = 0xFFFF;
            target = NULL;
        }
        break;
    }
}
#pragma pop

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
        if (lbl_805DBA80 < this->h348) {
            this->h348 -= lbl_805DBA78;
            return;
        }
        this->phase = 4;
        this->h348 = (f32) lbl_805DBA80;
        return;
    case 4:
        if (lbl_805DBA80 < this->h344) {
            this->h344 -= lbl_805DBA78;
            return;
        }
        this->mode = 0;
        this->phase = 0;
        this->h344 = (f32) lbl_805DBA80;
        this->player = 0xFFFF;
        this->target = 0;
        break;
    }
}

#pragma push
#pragma fp_contract on
void TOTrapAncient02R::calc_trap_count() {
    s32 temp_r4;

    this->m_360 = (s32) (this->scale.z + ((lbl_805DBA7C * (f32) game_difficulty_selection) + lbl_805DBA78));
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
#pragma pop
