#include "types.h"
#include "pso/TObject.h"
#include "pso/system/vector.h"
#include "pso/unk/text_80087278.h"

// TBoss5GryphonLightning object layout. The class name pointer and vtable
// placement mirror the TObject family in this game (vtable slot at +0x18).
struct GryphonLightning_80324F4C {
    const char *m_name; // +0x00
    u8 _pad04[0x14]; // +0x04 flags/id, prev/next/up/down
    void *vt; // +0x18
    f32 m_1c; // +0x1C
    Vec m_pos_a; // +0x20
    Vec m_pos_b; // +0x2C
    void *m_38;
    void *m_3c;
    void *m_40;
    void *m_44;
    struct {
        Vec pos; // +0x00
        f32 m_c; // +0x0C
    } m_pts[4]; // +0x48
    f32 m_88;
    f32 m_8c;
    s32 m_90;
    s32 m_94;
};

extern "C" {
extern const char *lbl_805D4180;
extern const f32 lbl_805DF5E0;
extern u8 __vt__22TBoss5GryphonLightning[];
TObject *__ct__7TObjectFP7TObject(TObject *, TObject *);

s32 TBoss5GryphonLightning__ct(s32 arg0, s32 parent, f32 arg2, s32 arg3) {
    GryphonLightning_80324F4C *self = (GryphonLightning_80324F4C *)arg0;
    __ct__7TObjectFP7TObject((TObject *)arg0, (TObject *)parent);
    self->vt = __vt__22TBoss5GryphonLightning;
    self->m_name = lbl_805D4180;
    VecCopy(&self->m_pos_a, (const Vec *)arg3);
    VecCopy(&self->m_pos_b, &self->m_pos_a);
    self->m_1c = arg2;
    self->m_94 = 0;
    self->m_38 = spawn_continuous_particle_effect_with_flags(&self->m_pos_a, 0x20c, 0x40);
    self->m_3c = spawn_continuous_particle_effect_with_flags(&self->m_pos_a, 0x20e, 0x40);
    self->m_40 = spawn_continuous_particle_effect_with_flags(&self->m_pos_b, 0x20f, 0x40);
    self->m_44 = spawn_continuous_particle_effect_with_flags(&self->m_pos_b, 0x216, 0x40);
    for (s32 i = 0; i < 4; i++) {
        VecCopy(&self->m_pts[i].pos, &self->m_pos_a);
        self->m_pts[i].m_c = lbl_805DF5E0;
    }
    self->m_88 = lbl_805DF5E0;
    self->m_8c = lbl_805DF5E0;
    self->m_90 = 1;
    return arg0;
}
}
