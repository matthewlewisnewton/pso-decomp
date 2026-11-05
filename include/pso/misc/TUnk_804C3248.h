#ifndef PSO_MISC_TUNK_804C3248_H
#define PSO_MISC_TUNK_804C3248_H
#include "types.h"
#include "pso/object/TObjMotion.h"

class TParticleCtrl;
struct PhotonAttachment {
    TParticleCtrl *particle;
    Vec position;
    s32 joint_index;
    s32 rotation[3];
};

typedef char PhotonAttachment_size[sizeof(PhotonAttachment) == 0x20 ? 1 : -1];
typedef char PhotonAttachment_position_offset[offsetof(PhotonAttachment, position) == 0x4 ? 1 : -1];
typedef char PhotonAttachment_joint_offset[offsetof(PhotonAttachment, joint_index) == 0x10 ? 1 : -1];
typedef char PhotonAttachment_rotation_offset[offsetof(PhotonAttachment, rotation) == 0x14 ? 1 : -1];

class TUnk_804C3248 : public TObjMotion {
public:
    virtual ~TUnk_804C3248();
    virtual void enter_scene();
    virtual void update_if_active();
    void setup_photon_blast_camera();
    void update_state();
    void free_photon();
    void update_photon_blast_attachments();
    void set_photon_blast_joint_callback();
    void begin_photon_summon_camera(s8);
    u8 unk_FC[0x4];
    u32 m_100;
    Vec camera_target;
    Vec camera_position;
    Vec camera_destination_target;
    Vec camera_destination_position;
    s32 m_134;
    u8 unk_138[0x4];
    f32 m_13c;
    u8 unk_140[0x4];
    f32 m_144;
    PhotonAttachment *m_148;
    u8 unk_14C[0x4];
    f32 m_150;
    u8 unk_154[0x4];
};

typedef char PhotonSummon_size[sizeof(TUnk_804C3248) == 0x158 ? 1 : -1];
typedef char PhotonSummon_count_offset[offsetof(TUnk_804C3248, m_100) == 0x100 ? 1 : -1];
typedef char PhotonSummon_attachments_offset[offsetof(TUnk_804C3248, m_148) == 0x148 ? 1 : -1];

#endif
