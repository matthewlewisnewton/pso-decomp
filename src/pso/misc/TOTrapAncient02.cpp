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

extern "C" {
u16 find_nearest_visible_player(void *, int, f32);
s32 get_current_floor(void);
f32 atan2_float(f32 y, f32 x);

f32 get_collision_body_radius(void *, s32);
void submit_cursor_candidate(void *, s32);
void *get_player_by_client_id(s32 i);

void rotate_vector_by_matrix(int, void *, void *);
s32 rotate_matrix_y(int, int);
void subtract_vector(void *, void *);
s32 push_matrix_from(void *src);
s32 pop_matrix();
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
struct Obj_8017A8B0 {
    u8 pad[0x38];
    f32 pos[3];
    u8 pad44[0x2A8 - 0x44];
    u8 *target;
    u8 pad2ac[0x326 - 0x2AC];
    s16 state;
    u8 pad328[0x334 - 0x328];
    f32 range;
    u8 pad338[0x33C - 0x338];
    u16 idx;
    u8 pad33e[0x364 - 0x33E];
    s32 switchId;
};

struct Vec_8017A988 { f32 x, y, z; };

struct VBase_8017A988 { u8 pad[0x18]; };

struct Obj_8017A988 : VBase_8017A988 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4(s16 *, s32);
    u16 id;
    u8 pad1e[0x38 - 0x1E];
    Vec_8017A988 pos;
    u8 pad44[0x80 - 0x44];
    u32 x80;
    u8 pad84[0x326 - 0x84];
    s16 state;
    u8 pad328[0x344 - 0x328];
    f32 x344;
    f32 x348;
    u8 pad34c[0x368 - 0x34C];
    s32 timer;
};

struct Base_B_8017AC98 { char pad[0x18]; };

struct V_B_8017AC98 : Base_B_8017AC98 {
    virtual void pv15();
    virtual void pv16();
    virtual void pv17();
    virtual void pv18();
    virtual void pv19();
    virtual void pv20();
    virtual void pv21();
    virtual void pv22();
    virtual s32 m8(f32, f32);
};

struct Base_8017B84C_8017AC98 { char pad[0x18]; };

struct VObj_8017B84C_8017AC98 : Base_8017B84C_8017AC98 {
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
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61();
    virtual void m62();
    virtual void m63();
    virtual void m64();
    virtual void m65();
    virtual void m66();
    virtual void m67();
    virtual void m68();
    virtual void m69();
    virtual void m70();
    virtual void m71();
    virtual void m72();
    virtual void m73();
    virtual void m74();
    virtual void m75();
    virtual void m76();
    virtual void m77();
};

struct Obj_8017ACA0 {
    u8 pad[0x326];
    s16 state;
    u8 pad328[0x34C - 0x328];
    s32 angle;
};

struct Trap_8017ADC4 {
    u8 pad0[0x2A8];
    void *target;
    u8 pad2AC[0x326 - 0x2AC];
    s16 mode;
    s16 state;
    u8 pad32A[0x33C - 0x32A];
    u16 player;
    u8 pad33E[0x344 - 0x33E];
    f32 h344;
    f32 h348;
    u8 pad34C[0x350 - 0x34C];
    s32 reset;
    s32 timer;
};

u16 get_entity_id(void *);
void obj_setFlags30(void *, u32);
s32 is_split_screen();
void * get_bml_model(void *, int);
s32 check_player_flag1__6TLobbyFv();
s32 free_collision_body_parts(void *);
void init_collision_body_parts(void *, void *, s32);
void *__dt__6TOTrapFv(void *arg0, s16 arg1);
void * TOTrap__ct(void *, void *, void *);
void *TOTrapAncient02R__ct(TOTrapAncient02R *arg0, void *arg1, void *arg2);
void * __dt__15TOTrapAncient02Fv(void *arg0, s16 arg1);
void * TOTrapAncient02__ct(TOTrapAncient02 *self, void *parent, void *creator);

u8 is_current_floor_switch_set(u16);
void __dl__7TObjectFPv(void *);
void scroll_ginja_mesh_uvs(u32, s32, s32, u16, s32);
s32 dispatch_input_to_instance__18TAdEnterPasswordGCFi(void *);
void translate_matrix(u32 arg0, f32 x, f32 y, f32 z);
s32 push_matrix();
s32 post_translate_matrix(void *);
void draw_ginja_model(s32 model);

extern BmlResource *TOTrapAncient02__shared_resource;
extern s32 __vt__15TOTrapAncient02[];
extern const char *lbl_805D31B4;
extern s32 lbl_805D31B8;
extern s32 actor_frame_tick;
extern s32 game_difficulty_selection;
extern s32 lbl_805D5ADC;
extern u32 lbl_805D5AE0;
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
struct TrapAncient02CollisionBody {
    f32 local_center[3];
    f32 radius;
    f32 field_10;
    s32 field_14;
    u32 flags;
    f32 world_center[3];
    f32 field_28;
};
typedef char TrapAncient02ResourceDescriptor_size[(sizeof(TrapAncient02ResourceDescriptor) == 0x10) ? 1 : -1];
typedef char TrapAncient02ResourceRecord_size[(sizeof(TrapAncient02ResourceRecord) == 0x18) ? 1 : -1];
typedef char TrapAncient02CollisionBody_size[(sizeof(TrapAncient02CollisionBody) == 0x2C) ? 1 : -1];
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
TrapAncient02CollisionBody trap_ancient02_collision_body = {
    { 0.0f, 8.5f, 0.0f }, 2.0f, 0.0f, 0, 0x38003, { 0.0f, 0.0f, 0.0f }, 0.0f
};
extern s32 __vt__16TOTrapAncient02R[];











}
void setup_particle_tev(s32 arg0);

// Reverse definitions with deferred generation reproduce this unit's original
// function order.

void TOTrapAncient02R::submit_cursor_and_notify() {
    struct VObj_8017B84C_8017AC98 *o = (struct VObj_8017B84C_8017AC98 *)this;
    o->m77();
}

#pragma push
#pragma fp_contract on
void *TOTrapAncient02__ct(TOTrapAncient02 *self, void *parent, void *creator) {
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
    init_collision_body_parts(self, (void *)&trap_ancient02_collision_body, 1);
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
        free_collision_body_parts(trap);
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
        lbl_805D5AE0 = (u32)find_object_node((NJS_OBJECT *)get_bml_model(obj, 0), 2)->model;
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
        lbl_805D5AE0 = (u32)find_object_node((NJS_OBJECT *)get_bml_model(obj, 0), 2)->model;
        lbl_805D5AE4 = 1;
        lbl_805D5ADC = 0;
        break;
    default:
        obj = new BmlResource(1, (BmlResourceDescriptor *)(base + 8), 0, 0, (void *)(0));
        TOTrapAncient02__shared_resource = obj;
        lbl_805D5AE0 = (u32)((NJS_OBJECT *)obj->models->model)->child->child->model;
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
        o = (TOTrapAncient02 *)TOTrapAncient02__ct(o, tl_05, arg0);
    }
    return o;
}

void TOTrapAncient02::render() {
    if (TMainTask::get_render_pass() != 1) {
        this->m_340 = ((V_B_8017AC98 *) this)->m8(lbl_805DBAA4, lbl_805DBA94);
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
    post_translate_matrix(&this->position);
    rotate_matrix_y(0, this->rotation.yaw);
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
    rotate_matrix_y(0, this->m_34c);
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
    post_translate_matrix(&this->position);
    rotate_matrix_y(0, this->rotation.yaw);
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
    rotate_matrix_y(0, this->m_34c);
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
    TOTrapAncient02 *self = this;
    void *p;
    f32 d;
    submit_cursor_candidate(self, -1);
    switch (self->phase) {
    case 0:
        if (self->h344 < lbl_805DBA84) {
            self->h344 += lbl_805DBA78;
        } else {
            self->phase = 1;
            self->h344 = lbl_805DBA84;
        }
        break;
    case 1:
        self->h348 += lbl_805DBA78;
        if (lbl_805DBA88 <= self->h348) {
            self->phase = 2;
            self->h348 = lbl_805DBA88;
        }
        break;
    case 2:
        self->player = find_nearest_visible_player(self, 0, self->range);
        if (self->player != 0xFFFF) {
            p = (void *)get_player_by_client_id((self->player));
            self->target = (u8 *)p;
            if (self->target != NULL) {
                d = horizontal_distance_squared((const Vec *)((u8 *)self->target + 0x38), (const Vec *)&self->position);
                self->dist = self->range - TObjPlayer__sub_8017A1A4(p, 0);
                if (d < self->dist * self->dist) {
                    if (self->player == local_client_id) {
                        send_6x2C_impose_hold(p, &self->position, self->timer, 0, self->dist);
                    }
                    self->mode = 3;
                    self->phase = 2;
                } else {
                    self->player = 0xFFFF;
                    self->target = NULL;
                }
            }
        } else {
            self->target = NULL;
        }
        if (self->target == NULL) {
            self->phase = 3;
        }
        break;
    case 3:
        if (lbl_805DBA80 < self->h348) {
            self->h348 -= lbl_805DBA78;
        } else {
            self->phase = 4;
            self->h348 = lbl_805DBA80;
        }
        break;
    case 4:
        if (lbl_805DBA80 < self->h344) {
            self->h344 -= lbl_805DBA78;
        } else {
            self->mode = 0;
            self->phase = 0;
            self->h344 = lbl_805DBA80;
            self->player = 0xFFFF;
            self->target = NULL;
        }
        break;
    }
}

void TOTrapAncient02::vfunc_82() {
    Trap_8017ADC4 *self = (Trap_8017ADC4 *)this;
    s32 p;
    submit_cursor_candidate(self, -1);
    switch (self->state) {
    case 0:
    case 1:
        self->state = 2;
    case 2:
        if (self->target != NULL) {
            obj_setFlags30(self->target, 0x200);
            ((TObjEnemy *)(self->target))->sub_8002AE64();
            ((TObjEnemy *)(self->target))->sub_800A7798(lbl_805DBA78);
            self->timer--;
            if (self->timer < 0) {
                self->state = 3;
                self->timer = self->reset;
                if (self->target != NULL && local_client_id == get_entity_id(self->target)) {
                    p = (s32)get_player_by_client_id(local_client_id);
                    if (p != 0 && check_player_flag1__6TLobbyFv() != 0) {
                        TObjPlayer::send_code_45_1(p);
                    }
                }
            }
        } else {
            self->state = 3;
            self->timer = self->reset;
        }
        break;
    case 3:
        if (lbl_805DBA80 < self->h348) {
            self->h348 -= lbl_805DBA78;
        } else {
            self->state = 4;
            self->h348 = lbl_805DBA80;
        }
        break;
    case 4:
        if (lbl_805DBA80 < self->h344) {
            self->h344 -= lbl_805DBA78;
        } else {
            self->mode = 0;
            self->state = 0;
            self->h344 = lbl_805DBA80;
            self->player = 0xFFFF;
            self->target = NULL;
        }
        break;
    }
}

void TOTrapAncient02::vfunc_84() {
    Obj_8017ACA0 *self = (Obj_8017ACA0 *)this;
    if (lbl_805D5ADC != actor_frame_tick && lbl_805D5AE0 != 0) {
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
            play_persistent_sound((s32)(0x4461B), (const void *)(self), (const Vec *)((u32)((u8 *)self + 0x38)), 0, 0);
            return;
        case AREA_MINE1:
        case AREA_MINE2:
            play_persistent_sound((s32)(0x4004C612), (const void *)(self), (const Vec *)((u32)((u8 *)self + 0x38)), 0, 0);
            return;
        case AREA_RUINS1:
        case AREA_RUINS2:
        case AREA_RUINS3:
            play_persistent_sound((s32)(0x4004C618), (const void *)(self), (const Vec *)((u32)((u8 *)self + 0x38)), 0, 0);
            return;
        case AREA_VR_SPACESHIP_ALPHA:
        case AREA_VR_SPACESHIP_BETA:
            play_persistent_sound((s32)(0x4004C610), (const void *)(self), (const Vec *)((u32)((u8 *)self + 0x38)), 0, 0);
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
void *TOTrapAncient02R__ct(TOTrapAncient02R *trap_ancient02_r, void *arg1, void *arg2) {
    ((s32 (*)(void *, void *))TOTrapAncient02__ct)(trap_ancient02_r, arg1);
    *(s32 **)((s8 *)trap_ancient02_r + 0x18) = __vt__16TOTrapAncient02R;
    *(s32 *)((s8 *)trap_ancient02_r + 0) = (s32) lbl_805D31B8;
    trap_ancient02_r->apply_object_set_data(arg2);
    ((TObjChara *)trap_ancient02_r)->initialize_position_copies();
    ((TObjChara *)trap_ancient02_r)->calc_attach_pos();
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
    *(s32 *)((s8 *)trap_ancient02_r + 0x2A8) = 0;
    trap_ancient02_r->h348 = lbl_805DBA80;
    trap_ancient02_r->h344 = lbl_805DBA80;
    *(s32 *)&trap_ancient02_r->m_34c = 0;
    if (trap_ancient02_r->rotation.roll > 0) {
        *(s32 *)&trap_ancient02_r->m_358 = 1;
    } else {
        *(s32 *)&trap_ancient02_r->m_358 = 0;
    }
    return trap_ancient02_r;
}
#pragma pop

TOTrapAncient02R::~TOTrapAncient02R() {
}

#pragma push
#pragma fp_contract on
void *TOTrapAncient02R::create(void *arg0) {
    void *o = TObject::operator new(0x36C);
    if (o != NULL) {
        o = TOTrapAncient02R__ct((TOTrapAncient02R *)o, tl_05, arg0);
    }
    return o;
}
#pragma pop

#pragma push
#pragma fp_contract on
f32 TOTrapAncient02R::receive_physical_attack(void *, f32) {
    Obj_8017A988 *self = (Obj_8017A988 *)this;
    s16 msg;
    if (self->id >= 0x4000 && self->x80 != 0) {
        Vec_8017A988 v = self->pos;
        v.y += self->x344 + self->x348;
        spawn_particle_effect((const Vec *)(&v), 0x1D0);
        spawn_particle_effect((const Vec *)(&v), 1);
        if (--self->timer <= 0) {
            self->timer = 0;
            if (((TObjCollidable *)self)->access_object_saved_state(&msg, 1) != 0) {
                self->state = 4;
                msg = self->state;
                ((TObjCollidable *)self)->send_object_state_update(&msg);
                ((TObjCollidable *)self)->access_object_saved_state(&msg, 0);
                self->m4(&msg, 1);
            }
        }
    }
    return lbl_805DBA80;
}
#pragma pop

#pragma push
#pragma fp_contract on
void TOTrapAncient02R::find_target_player() {
    Obj_8017A8B0 *self = (Obj_8017A8B0 *)this;
    ((TObjCollidable *)self)->clear_player_status_flag(0, 1);
    ((TObjChara *)self)->calc_attach_pos();
    if (*(s32 *)&this->m_364 == -1 || is_current_floor_switch_set(*(s32 *)&this->m_364) == 1) {
        this->player = find_nearest_visible_player(self, 0, this->range);
        if (this->player != 0xFFFF) {
            this->target = (u8 *)get_player_by_client_id(this->player);
            if (this->target != NULL) {
                if (horizontal_distance_squared((const Vec *)(this->target + 0x38), (const Vec *)self->pos) < this->range * this->range) {
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
                dist = range + get_collision_body_radius(target, 0);
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
                        rotate_matrix_y(0, rotation.yaw);
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
