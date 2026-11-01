#include "pso/system/SoundEffect.h"
#include "pso/math/AngleLookup.h"
#include "pso/system/MatrixStack.h"
#include "pso/TParticleCtrl.h"
#include "types.h"
#include "pso/misc/TTecGiFoie.h"
extern "C" void *__dt__13TUnk_804CC148Fv(void *, s16);
void direction_to_rotation_xz(u8 *, s32 *, s32 *);
#include "pso/system/vector.h"
#include "pso/effect/TUnk_804CC148.h"

#include "pso/misc/TTecAnti.h"
#include "pso/misc/TTecLuker.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

struct RecoveredGlobal_80230D9C_lbl_804CC510
{
  s32 value;
  u8 remaining[0x48];
};

struct RecoveredGlobal_80230D9C_lbl_804CC55C
{
  s32 value;
  u8 remaining[0x94];
};

struct RecoveredFields_80230D9C_arg0
{
  u8 unknown_0[0x78];
  s16 field_78;
  u8 unknown_7A[0xE];
  f32 field_88;
  u8 unknown_8C[0x20];
  s16 field_AC;
};

typedef struct RecoveredFields_80230D9C_arg0 RecoveredFields_80230D9C_arg0;

typedef struct RecoveredGlobal_80230D9C_lbl_804CC510 RecoveredGlobal_80230D9C_lbl_804CC510;

typedef struct RecoveredGlobal_80230D9C_lbl_804CC55C RecoveredGlobal_80230D9C_lbl_804CC55C;

typedef char RecoveredGlobal_80230D9C_lbl_804CC510_size[((sizeof(RecoveredGlobal_80230D9C_lbl_804CC510)) == 0x4C) ? (1) : (-1)];

typedef char RecoveredGlobal_80230D9C_lbl_804CC55C_size[((sizeof(RecoveredGlobal_80230D9C_lbl_804CC55C)) == 0x98) ? (1) : (-1)];

struct TUnk_804CC800;
typedef TUnk_804CC800 GiFoieOrbitTask;

struct RecoveredGlobal_80231638___vt__10TTecGiFoie
{
  s32 value;
  u8 remaining[0x24];
};

struct HitInfo_8023154C { s32 type; f32 power; };

struct VBase_8023154C { char pad[0x18]; };

struct VObj_8023154C : VBase_8023154C {
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
    virtual void m21(void *, HitInfo_8023154C *, void *, s32, s32);
};

struct Obj_8023154C {
    u8 pad0[0x1C];
    void *source;
    u8 pad20[0x88 - 0x20];
    f32 power;
    u8 padP[0xB8 - 0x88 - 4];
    void *contact;
    u8 padC[0xF8 - 0xB8 - 4];
    u16 ids[32];
    s32 cursor;
};

typedef Vec Vec_802312E4;

struct Rot_802312E4 { s32 x, y, z; };

struct Part_802312E4 { s32 id; u32 flags; u8 pad8[4]; };

struct Profile_802312E4 { Part_802312E4 *parts; u32 count; };

// The 0x4C allocation and native TObject base fix this private task layout.
struct TUnk_804CC800 : public TObject {
    TParticleCtrl **emitters;
    Vec_802312E4 origin;
    Vec_802312E4 position;
    f32 radius;
    s32 phase;
    s32 ticks;
    u8 band;
    s8 level;
    u8 orbit_mode;
    u8 single;
    s32 axis_yaw;
    virtual void run_task();
    virtual ~TUnk_804CC800();
    TUnk_804CC800(Vec_802312E4 *, s32, s32, s32, TObject *, u8);
};

typedef char OrbitTask_size[sizeof(GiFoieOrbitTask) == 0x4C ? 1 : -1];

typedef struct RecoveredGlobal_80231638___vt__10TTecGiFoie RecoveredGlobal_80231638___vt__10TTecGiFoie;

typedef char RecoveredGlobal_80231638___vt__10TTecGiFoie_size[((sizeof(RecoveredGlobal_80231638___vt__10TTecGiFoie)) == 0x28) ? (1) : (-1)];

typedef Vec Vec_8023179C;

struct GiFoie_8023179C {
    u32 x0;
    u8 pad4[0x18 - 0x4];
    void *vt;
    void *source;
    Vec_8023179C pos;
    u8 pad2c[0x78 - 0x2C];
    s16 level;
    s16 band;
    u8 pad7c[0x90 - 0x7C];
    f32 radius;
    u8 pad94[0xB4 - 0x94];
    u16 fb4;
    u8 padb6[0xE8 - 0xB6];
    u8 *effect;
    GiFoieOrbitTask *tasks[3];
    u16 ids[32];
    s32 cursor;
};

u16 get_entity_id(void *);
f32 newton_sqrtf(f32);
void queue_destruction__7TObjectFv(void *arg0);
void *spawn_particle_effect_with_rotation(void *pos, void *dir, s32 id, int e);
void *spawn_continuous_particle_with_direction(void *pos, void *dir, s32 id);
f32 horizontal_distance_squared(void *, void *);
void mem_free(void *);
void *mem_alloc(u32 size);
void * find_entity_by_id(u16);
s32 is_technique_ready__8TTecCtrlFv();
s32 update_technique_slot__10TTecRaFoieFl(s32, s32, s32);

void __dl__7TObjectFPv(void *);
void * __nw__7TObjectFUl(int);
void __dt__7TObjectFv(void *, int);
void __ct__7TObjectFP7TObject(void *, void *);
void construct_area_technique_base(void *, void *, void *, void *, void *);
s32 calc_technique_parameters(int, int, int);
u8 * __dt__10TTecGiFoieFv(u8 *arg0, s16 arg1);
void run_task__10TTecGiFoieFv(u8 *self);
void * TTecGiFoie__ct(void *self_, void *source, void *origin, void *level);
void matrix_mult_vec(void *, void *, void *);
void rotate_matrix_y(void *, s32);
s32 push_matrix_from(void *src);
s32 pop_matrices(s32 arg0);

extern const f32 TTecGiFoie__data_805DC81C;
extern RecoveredGlobal_80231638___vt__10TTecGiFoie __vt__10TTecGiFoie;
extern const Profile_802312E4 TTecGiFoie__emitter_profile_table[];
extern u8 lbl_8044D324[];
extern Vec_8023179C lbl_8044D32C;
extern RecoveredGlobal_80230D9C_lbl_804CC510 tech_high_level_linear_power_table;
extern RecoveredGlobal_80230D9C_lbl_804CC55C lbl_804CC55C;
extern u8 identity_matrix[];
extern u32 TTecGiFoie__name;
extern const f32 lbl_8044D338[3];
extern const Vec_802312E4 lbl_8044D344;
extern const f64 lbl_8044D358;
extern const f64 lbl_8044D360[];
extern const f32 lbl_805DC814;
f32 atan2_float(f32, f32);
void rotate_matrix_x(void *, s32);
void rotate_vector_by_matrix(void *, const void *, void *);

extern const f32 lbl_805DC810;
extern const f32 lbl_805DC818;
extern const f32 lbl_805DC820;
extern const f32 lbl_805DC824;
extern TObject *tl_07;

void TTecGiFoie::calc_params() {
    u8 *arg0 = (u8 *)this;
  int new_var;
 new_var = (int) calc_technique_parameters(1, (int) ((RecoveredFields_80230D9C_arg0 *) arg0)->field_78, 0xFFFF); do { ((TTecAnti *)(arg0 + ((0, 0x88))))->copy_params((u8 *)new_var); if ((((s16) ((RecoveredFields_80230D9C_arg0 *) arg0)->field_78) >= 0xF) && (is_technique_ready__8TTecCtrlFv() == 0)) { ((RecoveredFields_80230D9C_arg0 *) arg0)->field_88 = (f32) ((*((s16 *) (((s8 *)&tech_high_level_linear_power_table.value) + 4))) + ((*((s16 *) (((s8 *)&tech_high_level_linear_power_table.value) + 6))) * ((RecoveredFields_80230D9C_arg0 *) arg0)->field_78)); return; } } while (0);
  ((RecoveredFields_80230D9C_arg0 *) arg0)->field_88 = (f32) (((RecoveredFields_80230D9C_arg0 *) arg0)->field_88 + ((f32) (((RecoveredFields_80230D9C_arg0 *) arg0)->field_AC * ((RecoveredFields_80230D9C_arg0 *) arg0)->field_78)));
  if (is_technique_ready__8TTecCtrlFv())
  {
    ((RecoveredFields_80230D9C_arg0 *) arg0)->field_88 = (f32) (((RecoveredFields_80230D9C_arg0 *) arg0)->field_88 * (*((f32 *) (((s8 *)&lbl_804CC55C.value) + 8))));
  }
}

// Orbit state is allocated by construct_orbit (0x802312E4), not TTecGiFoie.
// Keep the two motion paths' float/double operations and callback order intact.
#pragma push
#pragma fp_contract on
#pragma opt_propagation off
void TUnk_804CC800::run_task() {
    Rot_802312E4 direction;
    s32 index;
    switch (this->band) {
    case 0: index = 0; break;
    case 1: index = 1; break;
    case 2: index = 2; break;
    case 3: index = 0; break;
    case 4: index = 1; break;
    case 5: index = 2; break;
    default: index = 0; break;
    }
    this->ticks++;
    if (this->orbit_mode != 0) {
        Vec_802312E4 offset;
        this->radius = this->radius + lbl_8044D358;
        this->phase += 0x1C71;
        offset.x = this->radius * cos_table_lookup(this->phase);
        offset.z = this->radius * sin_table_lookup(this->phase);
        offset.y = lbl_805DC810;
        push_matrix_from(identity_matrix);
        rotate_matrix_y(0, this->axis_yaw);
        rotate_matrix_x(0, 0x4000);
        rotate_vector_by_matrix(0, &offset, &offset);
        pop_matrix();
        this->position.x = this->origin.x + offset.x;
        this->position.y = this->origin.y + offset.y;
        this->position.z = this->origin.z + offset.z;
    } else {
        this->radius += lbl_805DC814;
        this->phase += (s32)(lbl_805DC818 * (f32)(this->band + 9));
        this->position.y = this->origin.y + lbl_8044D338[index] * sin_table_lookup((s32)(lbl_805DC818 * (f32)(this->ticks * 15)));
        this->position.x = this->origin.x + this->radius * cos_table_lookup(this->phase);
        this->position.z = this->origin.z + this->radius * sin_table_lookup(this->phase);
    }
    if (this->single != 0) {
        Vec_802312E4 offset = lbl_8044D344;
        push_matrix_from(identity_matrix);
        rotate_matrix_y(0, this->axis_yaw);
        rotate_vector_by_matrix(0, &offset, &offset);
        pop_matrix();
        direction.x = 0;
        direction.y = 0;
        direction.z = 0;
        direction_to_rotation_xz((u8 *)&offset, &direction.x, &direction.z);
        this->emitters[0]->set_position(&this->position);
        this->emitters[0]->set_direction(&direction);
    } else {
        direction.y = (s32)(lbl_8044D360[0] * atan2_float(this->position.x - this->origin.x, this->position.z - this->origin.z));
        direction.z = 0x4000;
        direction.x = direction.y - 0x8000;
        // GC/2.6 needs a named zero and a fresh counter, with propagation off,
        // to keep this field reset separate from the loop's two initializers.
        s32 direction_y = 0;
        direction.y = direction_y;
        for (s32 emitter_index = 0; emitter_index < TTecGiFoie__emitter_profile_table[this->band].count; emitter_index++) {
            this->emitters[emitter_index]->set_position(&this->position);
            this->emitters[emitter_index]->set_direction(&direction);
        }
    }
}

#pragma pop

TUnk_804CC800::~TUnk_804CC800() {
    u32 i;
    if (single != 0) {
        queue_destruction__7TObjectFv(emitters[0]);
    } else {
        for (i = 0; i < TTecGiFoie__emitter_profile_table[band].count; i++) {
            queue_destruction__7TObjectFv(emitters[i]);
        }
    }
    mem_free(emitters);
}

TUnk_804CC800::TUnk_804CC800(Vec_802312E4 *pos, s32 arg2, s32 band, s32 arg4, TObject *parent, u8 single) : TObject(parent) {
    GiFoieOrbitTask *self = this;
    self->orbit_mode = 0;
    self->origin.x = pos->x;
    self->origin.y = pos->y;
    self->origin.z = pos->z;
    self->band = band;
    self->level = arg4;
    VecCopy(&self->position, &self->origin);
    self->phase = arg2;
    self->radius = lbl_805DC810;
    self->ticks = 0;
    self->single = single;
    if (self->single != 0) {
        Rot_802312E4 r;
        self->emitters = (TParticleCtrl **)mem_alloc(4);
        r.x = 0;
        r.y = 0;
        r.z = 0x4000;
        self->emitters[0] = (TParticleCtrl *)spawn_continuous_particle_with_direction(&self->origin, &r, 0x19D);
        self->radius = TTecGiFoie__data_805DC81C;
    } else {
        s32 i;
        self->emitters = (TParticleCtrl **)mem_alloc(TTecGiFoie__emitter_profile_table[self->band].count * 4);
        for (i = 0; i < TTecGiFoie__emitter_profile_table[self->band].count; i++) {
            Rot_802312E4 r;
            Part_802312E4 *p;
            r.x = 0;
            r.y = 0;
            r.z = 0x4000;
            p = &TTecGiFoie__emitter_profile_table[self->band].parts[i];
            self->emitters[i] = (TParticleCtrl *)spawn_particle_effect_with_rotation(&self->origin, &r, p->id, (p->flags & 0x1000) ? 0x2000 : 0);
            if (self->band == 2) {
                if (arg4 >= 0xF && arg4 < 0x19) {
                    if (i <= 1 && self->emitters[i] != 0) {
                        self->emitters[i]->set_scale(lbl_805DC820, lbl_805DC820);
                    }
                } else if (arg4 >= 0x19 && arg4 < 0x1E) {
                    if (i <= 1 && self->emitters[i] != 0) {
                        self->emitters[i]->set_scale(lbl_805DC820, lbl_805DC824);
                    }
                }
            }
        }
    }
}

void TTecGiFoie::create(void *arg0, void *origin, void *level) {
    void *o;
    o = __nw__7TObjectFUl(0x13C);
    if (o != NULL) {
        TTecGiFoie__ct(o, arg0, origin, level);
    }
}

#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma opt_dead_assignments off
void TTecGiFoie::vfunc_6(void *target) {
    Obj_8023154C *self = (Obj_8023154C *)this;
    s32 found = 0;
    s32 i;
    for (i = 0; i < 32; i++) {
        if (self->ids[i] == get_entity_id(((VObj_8023154C *)target))) {
            found = 1;
        }
    }
    if (found == 0) {
        self->ids[*(s32 *)&this->m_138] = get_entity_id(((VObj_8023154C *)target));
        *(s32 *)&this->m_138 += 1;
        if (*(s32 *)&this->m_138 >= 32) {
            *(s32 *)&this->m_138 = 31;
        }
        HitInfo_8023154C tmp;
        tmp.type = 1;
        tmp.power = this->m_88;
        HitInfo_8023154C info = tmp;
        ((VObj_8023154C *)target)->m21(self->source, &info, self->contact, 1, -1);
    }
}
#pragma pop

#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma opt_dead_assignments off
u8 *__dt__10TTecGiFoieFv(u8 *arg0, s16 arg1) {
  s32 temp_r30;
  s32 var_r29;
  s32 var_r31;
  if (arg0 != 0)
  {
    var_r31 = 0;
    var_r29 = var_r31;
    var_r31 = 0;
    *((s32 **) (((s8 *) arg0) + 0x18)) = &__vt__10TTecGiFoie.value;
    do
    {
      temp_r30 = var_r31 + 0xEC;
      if (TTecLuker::is_parents_unqueued(*((s32 *) (((s8 *) arg0) + temp_r30))) != 0)
      {
        queue_destruction__7TObjectFv((void *)(*((s32 *) (((s8 *) arg0) + temp_r30))));
      }
      var_r29 += 1;
      var_r31 += 4;
    }
    while (var_r29 < 3);
    __dt__13TUnk_804CC148Fv((void *)((TUnk_804CC148 *)arg0), 0);
    if (arg1 > 0)
    {
      ((s32 (*)(void *))__dl__7TObjectFPv)((void *) arg0);
    }
  }
  return arg0;
}
#pragma pop

#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma opt_dead_assignments off
void run_task__10TTecGiFoieFv(u8 *self) {
    f32 distance;
    if (*(void **)((s8 *)self + 0xE8) == NULL) {
        queue_destruction__7TObjectFv(self);
        return;
    }
    *(void **)((s8 *)self + 0x1C) = find_entity_by_id(((TTecGiFoie *)self)->m_b4);
    if (*(void **)((s8 *)self + 0x1C) == NULL) {
        queue_destruction__7TObjectFv(self);
        return;
    }
    if (TTecLuker::is_parents_unqueued(((TTecGiFoie *)self)->m_ec) != 0) {
        distance = newton_sqrtf(horizontal_distance_squared(*(u8 **)((s8 *)self + 0xEC) + 0x2C, self + 0x20));
        if (*(u8 **)((s8 *)self + 0xE8) != NULL) {
            *(f32 *)((s8 *)(*(u8 **)((s8 *)(*(u8 **)((s8 *)self + 0xE8)) + 0xA4)) + 0xC) = TTecGiFoie__data_805DC81C + distance;
        }
        ((TUnk_804CC148 *)self)->apply_technique_to_area_targets();
        if (distance >= ((TTecGiFoie *)self)->m_90) {
            queue_destruction__7TObjectFv(self);
        }
    }
}
#pragma pop

void *TTecGiFoie__ct(void *self_, void *source, void *origin, void *level) {
#define self ((GiFoie_8023179C *)self_)
    s32 i;
    s32 j;
    s32 k;
    s32 r;
    construct_area_technique_base(self_, source, origin, origin, level);
    self->vt = &__vt__10TTecGiFoie.value;
    self->x0 = TTecGiFoie__name;
    ((TTecGiFoie *)self_)->calc_params();
    if (self->effect != NULL) {
        *(f32 *)((s8 *)(*(u8 **)((s8 *)self->effect + 0xA4)) + 0xC) = TTecGiFoie__data_805DC81C + self->radius;
    }
    for (i = 0; i < 32; i++) {
        self->ids[i] = 0xFFFF;
    }
    for (j = 0; j < 3; j++) {
        self->tasks[j] = 0;
    }
    self->cursor = 0;
    for (k = 0; k < lbl_8044D324[self->band]; k++) {
        Vec_8023179C v = lbl_8044D32C;
        Vec_8023179C p;
        s32 angle;
        s32 step;
        GiFoieOrbitTask *o;
        step = (s32)(lbl_805DC818 * (f32)(360 / lbl_8044D324[self->band]));
        angle = step * k + 0x4000;
        push_matrix_from(identity_matrix);
        rotate_matrix_y(0, angle);
        matrix_mult_vec(0, &v, &v);
        pop_matrices(1);
        p.x = self->pos.x + v.x;
        p.y = self->pos.y + v.y;
        p.z = self->pos.z + v.z;
        o = new TUnk_804CC800(&p, angle, self->band, self->level, tl_07, 0);
        self->tasks[k] = o;
    }
    switch (self->band) {
    case 0:
        r = play_sound_effect(0x4002A801, (const Vec *)((u8 *)self_ + 0x20), 0, 0);
        if (r >= 0) {
            update_technique_slot__10TTecRaFoieFl(r, 0x100, 0);
        }
        break;
    case 1:
        play_sound_effect(0x4002A801, (const Vec *)((u8 *)self_ + 0x20), 0, 0);
        break;
    case 2:
    case 3:
        r = play_sound_effect(0x4002A801, (const Vec *)((u8 *)self_ + 0x20), 0, 0);
        if (r >= 0) {
            update_technique_slot__10TTecRaFoieFl(r, -0x180, 0);
        }
        break;
    case 4:
        r = play_sound_effect(0x4002A801, (const Vec *)((u8 *)self_ + 0x20), 0, 0);
        if (r >= 0) {
            update_technique_slot__10TTecRaFoieFl(r, -0x250, 0);
        }
        break;
    case 5:
        r = play_sound_effect(0x4002A801, (const Vec *)((u8 *)self_ + 0x20), 0, 0);
        if (r >= 0) {
            update_technique_slot__10TTecRaFoieFl(r, -0x100, 0);
        }
        break;
    default:
        play_sound_effect(0x4002A801, (const Vec *)((u8 *)self_ + 0x20), 0, 0);
        break;
    }
    if (self->source != NULL) {
        self->fb4 = get_entity_id(self->source);
    }
    return self_;
#undef self
}

void TTecGiFoie::render() {  }

}
