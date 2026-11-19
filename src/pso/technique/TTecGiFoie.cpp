#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/system/SoundEffect.h"
#include "pso/audio/SoundSlotPitch.h"
#include "pso/effect/particle/TParticleCtrl.h"
#include "pso/system/ArrayAllocation.h"
#include "types.h"
#include "pso/technique/TTecGiFoie.h"
#include "pso/system/task/TObject.h"
#include "pso/technique/TTecCtrl.h"
#include "pso/boss/darkfalz/TOBoss4Rock.h"
#include "pso/system/MatrixStack.h"
extern "C" void *__dt__13TUnk_804CC148Fv(void *, s16);
#include "pso/system/vector.h"
#include "pso/effect/TUnk_804CC148.h"

#include "pso/technique/TTecAnti.h"
#include "pso/technique/TTecLuker.h"
#include "pso/player/TObjPlayer.h"
#include "pso/math/AngleLookup.h"
#include "pso/math/MatrixVector.h"
#include "pso/system/MatrixOps.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/render/render_util.h"
#include "pso/player/TObjPlayer_80011014.h"

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

struct Rot_802312E4 { s32 x, y, z; };

// Same layout as TTecGiBarta's Row_802304A0 {entry, flags, scale}.
struct Part_802312E4 { s32 id; u32 flags; f32 scale; };

struct Profile_802312E4 { const Part_802312E4 *parts; u32 count; };

typedef struct RecoveredGlobal_80231638___vt__10TTecGiFoie RecoveredGlobal_80231638___vt__10TTecGiFoie;

typedef char RecoveredGlobal_80231638___vt__10TTecGiFoie_size[((sizeof(RecoveredGlobal_80231638___vt__10TTecGiFoie)) == 0x28) ? (1) : (-1)];


struct GiFoie_8023179C {
    const char *m_name;
    u8 pad4[0x18 - 0x4];
    void *vt;
    void *source;
    Vec pos;
    u8 pad2c[0x78 - 0x2C];
    s16 level;
    s16 band;
    u8 pad7c[0x90 - 0x7C];
    f32 radius;
    u8 pad94[0xB4 - 0x94];
    u16 fb4;
    u8 padb6[0xE8 - 0xB6];
    u8 *effect;
    TUnk_804CC800 *tasks[3];
    u16 ids[32];
    s32 cursor;
};


void *spawn_particle_effect_with_rotation(void *pos, void *dir, s32 id, int e);
void *spawn_continuous_particle_with_direction(void *pos, void *dir, s32 id);
void * find_entity_by_id(u16);
void __dl__7TObjectFPv(void *);
void construct_area_technique_base(void *, void *, void *, void *, void *);
s32 calc_technique_parameters(int, int, int);
u8 * __dt__10TTecGiFoieFv(u8 *arg0, s16 arg1);
void run_task__10TTecGiFoieFv(u8 *self);
void * TTecGiFoie__ct(void *self_, void *source, void *origin, void *level);
void matrix_mult_vec(void *, void *, void *);

extern RecoveredGlobal_80231638___vt__10TTecGiFoie __vt__10TTecGiFoie;
extern RecoveredGlobal_80230D9C_lbl_804CC510 tech_high_level_linear_power_table;
extern RecoveredGlobal_80230D9C_lbl_804CC55C lbl_804CC55C;

const char *TTecGiFoie__name = "TTecGiFoie";

// emitter_parts_N: the N particle parts an entry of TTecGiFoie__emitter_profile_table spawns.
static const Part_802312E4 emitter_parts_1[1] = {{34, 2, 0.0f}};
static const Part_802312E4 emitter_parts_2[2] = {{34, 2, 0.0f}, {172, 1, 0.0f}};
static const Part_802312E4 emitter_parts_3[3] = {{34, 2, 0.0f}, {172, 1, 0.0f}, {414, 0x1000, 1.0f}};

const Profile_802312E4 TTecGiFoie__emitter_profile_table[6] = {
    {emitter_parts_1, 1}, {emitter_parts_1, 1}, {emitter_parts_1, 1},
    {emitter_parts_2, 2}, {emitter_parts_2, 2}, {emitter_parts_3, 3},
};

// orbit_counts: per band, how many orbits TTecGiFoie__ct spaces evenly (360 / count degrees) around the caster.
static const u8 orbit_counts[6] = {1, 1, 1, 2, 2, 3};
extern TObject *tl_07;

// defer_codegen emits these in reverse source order: the last function in the file comes first in .text.
#pragma defer_codegen on

void TTecGiFoie::render() {  }

void *TTecGiFoie__ct(void *self_, void *source, void *origin, void *level) {
#define self ((GiFoie_8023179C *)self_)
    s32 i;
    s32 j;
    s32 k;
    s32 r;
    construct_area_technique_base(self_, source, origin, origin, level);
    self->vt = &__vt__10TTecGiFoie.value;
    self->m_name = TTecGiFoie__name;
    ((TTecGiFoie *)self_)->calc_params();
    if (self->effect != NULL) {
        *(f32 *)((s8 *)(*(u8 **)((s8 *)self->effect + 0xA4)) + 0xC) = 5.0f + self->radius;
    }
    for (i = 0; i < 32; i++) {
        self->ids[i] = 0xFFFF;
    }
    for (j = 0; j < 3; j++) {
        self->tasks[j] = 0;
    }
    self->cursor = 0;
    for (k = 0; k < orbit_counts[self->band]; k++) {
        Vec v = {0.0f, 0.0f, -10.0f};
        Vec p;
        s32 angle;
        s32 step;
        step = (s32)(182.04445f * (f32)(360 / orbit_counts[self->band]));
        angle = step * k + 0x4000;
        push_matrix_from(identity_matrix);
        rotate_matrix_y(0, angle);
        matrix_mult_vec(0, &v, &v);
        pop_matrices(1);
        p.x = self->pos.x + v.x;
        p.y = self->pos.y + v.y;
        p.z = self->pos.z + v.z;
        self->tasks[k] = new TUnk_804CC800(&p, angle, self->band, self->level, tl_07, 0);
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
        self->fb4 = get_entity_id((TObjBase *)self->source);
    }
    return self_;
#undef self
}

#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma opt_dead_assignments off
void run_task__10TTecGiFoieFv(u8 *self) {
    f32 distance;
    if (*(void **)((s8 *)self + 0xE8) == NULL) {
        ((TObject *)self)->queue_destruction();
        return;
    }
    *(void **)((s8 *)self + 0x1C) = find_entity_by_id(((TTecGiFoie *)self)->m_b4);
    if (*(void **)((s8 *)self + 0x1C) == NULL) {
        ((TObject *)self)->queue_destruction();
        return;
    }
    if (TTecLuker::is_parents_unqueued(((TTecGiFoie *)self)->m_ec) != 0) {
        distance = newton_sqrtf(horizontal_distance_squared((Vec *)(*(u8 **)((s8 *)self + 0xEC) + 0x2C), (Vec *)(self + 0x20)));
        if (*(u8 **)((s8 *)self + 0xE8) != NULL) {
            *(f32 *)((s8 *)(*(u8 **)((s8 *)(*(u8 **)((s8 *)self + 0xE8)) + 0xA4)) + 0xC) = 5.0f + distance;
        }
        ((TUnk_804CC148 *)self)->apply_technique_to_area_targets();
        if (distance >= ((TTecGiFoie *)self)->m_90) {
            ((TObject *)self)->queue_destruction();
        }
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
        ((TObject *)((void *)(*((s32 *) (((s8 *) arg0) + temp_r30)))))->queue_destruction();
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
void TTecGiFoie::vfunc_6(void *target) {
    Obj_8023154C *self = (Obj_8023154C *)this;
    s32 found = 0;
    s32 i;
    for (i = 0; i < 32; i++) {
        if (self->ids[i] == get_entity_id((TObjBase *)target)) {
            found = 1;
        }
    }
    if (found == 0) {
        self->ids[*(s32 *)&this->m_138] = get_entity_id((TObjBase *)target);
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

void TTecGiFoie::create(void *arg0, void *origin, void *level) {
    void *o;
    o = TObject::operator new(0x13C);
    if (o != NULL) {
        TTecGiFoie__ct(o, arg0, origin, level);
    }
}

TUnk_804CC800::TUnk_804CC800(Vec *pos, s32 angle, s32 level_band, s32 tech_level, TObject *parent, u8 single_particle)
    : TObject(parent) {
    orbit_mode = 0;
    origin.x = pos->x;
    origin.y = pos->y;
    origin.z = pos->z;
    band = level_band;
    level = tech_level;
    VecCopy(&position, &origin);
    phase = angle;
    radius = 0.0f;
    ticks = 0;
    single = single_particle;
    if (single != 0) {
        Rot_802312E4 r;
        emitters = (TParticleCtrl **)::operator new[](sizeof(*emitters));
        r.x = 0;
        r.y = 0;
        r.z = 0x4000;
        emitters[0] = (TParticleCtrl *)spawn_continuous_particle_with_direction(&origin, &r, 0x19D);
        radius = 5.0f;
    } else {
        s32 i;
        emitters = (TParticleCtrl **)::operator new[](TTecGiFoie__emitter_profile_table[band].count * sizeof(*emitters));
        for (i = 0; i < TTecGiFoie__emitter_profile_table[band].count; i++) {
            Rot_802312E4 r;
            const Part_802312E4 *p;
            r.x = 0;
            r.y = 0;
            r.z = 0x4000;
            p = &TTecGiFoie__emitter_profile_table[band].parts[i];
            emitters[i] = (TParticleCtrl *)spawn_particle_effect_with_rotation(&origin, &r, p->id, (p->flags & 0x1000) ? 0x2000 : 0);
            if (band == 2) {
                if (tech_level >= 0xF && tech_level < 0x19) {
                    if (i <= 1 && emitters[i] != 0) {
                        emitters[i]->set_scale(1.3f, 1.3f);
                    }
                } else if (tech_level >= 0x19 && tech_level < 0x1E) {
                    if (i <= 1 && emitters[i] != 0) {
                        emitters[i]->set_scale(1.3f, 1.8f);
                    }
                }
            }
        }
    }
}

TUnk_804CC800::~TUnk_804CC800() {
    if (single != 0) {
        emitters[0]->queue_destruction();
    } else {
        for (u32 i = 0; i < TTecGiFoie__emitter_profile_table[band].count; i++) {
            emitters[i]->queue_destruction();
        }
    }
    ::operator delete[](emitters);
}

void TUnk_804CC800::run_task() {
    static const f32 lbl_8044D338[3] = {0.0f, 3.5f, 7.0f};
    s32 rot[3];
    s32 bob;
    switch (band) {
    case 0:
        bob = 0;
        break;
    case 1:
        bob = 1;
        break;
    case 2:
        bob = 2;
        break;
    case 3:
        bob = 0;
        break;
    case 4:
        bob = 1;
        break;
    case 5:
        bob = 2;
        break;
    default:
        bob = 0;
        break;
    }
    ticks++;
    if (orbit_mode) {
        Vec offset;
        radius += 0.015;
        phase += 0x1C71;
        offset.x = radius * cos_table_lookup(phase);
        offset.z = radius * sin_table_lookup(phase);
        offset.y = 0.0f;
        push_matrix_from(identity_matrix);
        rotate_matrix_y(0, axis_yaw);
        rotate_matrix_x(0, 0x4000);
        rotate_vector_by_matrix(0, &offset, &offset);
        pop_matrix();
        position.x = origin.x + offset.x;
        position.y = origin.y + offset.y;
        position.z = origin.z + offset.z;
    } else {
        radius += 0.55f;
        phase += (s32)(182.04445f * (band + 9));
        position.y = lbl_8044D338[bob] * sin_table_lookup((s32)(182.04445f * (f32)(ticks * 15))) + origin.y;
        position.x = radius * cos_table_lookup(phase) + origin.x;
        position.z = radius * sin_table_lookup(phase) + origin.z;
    }
    if (single) {
        Vec dir = {0.0f, 0.0f, 1.0f};
        push_matrix_from(identity_matrix);
        rotate_matrix_y(0, axis_yaw);
        rotate_vector_by_matrix(0, &dir, &dir);
        pop_matrix();
        rot[0] = 0;
        rot[1] = 0;
        rot[2] = 0;
        direction_to_rotation_xz((u8 *)&dir, &rot[0], &rot[2]);
        emitters[0]->set_position(&position);
        emitters[0]->set_direction(rot);
    } else {
        u32 i;
        s16 roll;
        rot[1] = (s32)(10430.38043493439 * atan2_float(position.x - origin.x, position.z - origin.z));
        roll = i = 0;
        rot[0] = rot[1] - 0x8000;
        rot[1] = roll;
        rot[2] = 0x4000;
        for (; i < TTecGiFoie__emitter_profile_table[band].count; i++) {
            emitters[i]->set_position(&position);
            emitters[i]->set_direction(rot);
        }
    }
}

void TTecGiFoie::calc_params() {
    u8 *arg0 = (u8 *)this;
  int new_var;
 new_var = (int) calc_technique_parameters(1, (int) ((RecoveredFields_80230D9C_arg0 *) arg0)->field_78, 0xFFFF); do { ((TTecAnti *)(arg0 + ((0, 0x88))))->copy_params((u8 *)new_var); if ((((s16) ((RecoveredFields_80230D9C_arg0 *) arg0)->field_78) >= 0xF) && (TTecCtrl::is_technique_ready() == 0)) { ((RecoveredFields_80230D9C_arg0 *) arg0)->field_88 = (f32) ((*((s16 *) (((s8 *)&tech_high_level_linear_power_table.value) + 4))) + ((*((s16 *) (((s8 *)&tech_high_level_linear_power_table.value) + 6))) * ((RecoveredFields_80230D9C_arg0 *) arg0)->field_78)); return; } } while (0);
  ((RecoveredFields_80230D9C_arg0 *) arg0)->field_88 = (f32) (((RecoveredFields_80230D9C_arg0 *) arg0)->field_88 + ((f32) (((RecoveredFields_80230D9C_arg0 *) arg0)->field_AC * ((RecoveredFields_80230D9C_arg0 *) arg0)->field_78)));
  if (TTecCtrl::is_technique_ready())
  {
    ((RecoveredFields_80230D9C_arg0 *) arg0)->field_88 = (f32) (((RecoveredFields_80230D9C_arg0 *) arg0)->field_88 * (*((f32 *) (((s8 *)&lbl_804CC55C.value) + 8))));
  }
}

#pragma defer_codegen off


}
