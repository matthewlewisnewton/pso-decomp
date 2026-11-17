#ifndef PSO_TOBJEZBONEROTBASE_H
#define PSO_TOBJEZBONEROTBASE_H

#include "pso/TObject.h"
#include "pso/system/NinjaTypes.h"
#include <stddef.h>

struct EZBoneRotKey {
    s32 bone;
    f32 axis[3];
};

struct EZBoneRotDesc {
    s32 amplitude;
    s32 phase_step;
    s32 child_phase_step;
    f32 child_amplitude_scale;
    EZBoneRotKey *keys;  // Negative bone index terminates the sequence.
};

struct EZBoneRotAngles {
    s32 x, y, z;
};

class TObjEZBoneRotBase : public TObject {
public:
    TObjEZBoneRotBase(TObject *parent, NJS_OBJECT *root, EZBoneRotDesc *desc);
    virtual ~TObjEZBoneRotBase();
    void capture_base_angles();
    void capture_base_angles_recursive(NJS_OBJECT *node);

    NJS_OBJECT *m_root;
    EZBoneRotDesc *m_desc;
    EZBoneRotAngles m_base_angles[8];
    s32 m_phase;
    s32 m_bone_index;
    EZBoneRotKey *m_key;
    EZBoneRotAngles *m_angles;
    f32 m_scale;
};

typedef char EZBoneRotKeySize[sizeof(EZBoneRotKey) == 0x10 ? 1 : -1];
typedef char EZBoneRotDescSize[sizeof(EZBoneRotDesc) == 0x14 ? 1 : -1];
typedef char EZBoneRotBaseSize[sizeof(TObjEZBoneRotBase) == 0x98 ? 1 : -1];
typedef char EZBoneRotBaseAnglesOffset[offsetof(TObjEZBoneRotBase, m_base_angles) == 0x24 ? 1 : -1];
typedef char EZBoneRotBasePhaseOffset[offsetof(TObjEZBoneRotBase, m_phase) == 0x84 ? 1 : -1];

#endif
