#include "pso/TObjEZBoneRotPlayer.h"
#include "pso/player/TObjPlayer.h"

extern "C" {
f32 sin_table_lookup(s32);
extern const char *TObjEZBoneRotPlayer__name;
extern const char *lbl_805D2B48;
}

void TObjEZBoneRotPlayer::run_task() {
    TObjPlayer *player = m_player;
    s32 flags = player->action_mask & 0xDF7FF;
    if (flags & 0x99003) {
        m_scale += -0.016666668f;
    } else if ((flags & 0x1E0) || m_previous_yaw != player->rotation.yaw) {
        m_scale += 0.13333334f;
    } else if (flags & 0x4661C) {
        m_scale += 0.016666668f;
    } else {
        m_scale += -0.016666668f;
    }
    f32 scale = m_scale;
    if (scale < 0.0f) {
        m_scale = 0.0f;
    } else if (scale > 1.0f) {
        m_scale = 1.0f;
    }
    advance_bone_rotation();
    m_previous_yaw = m_player->rotation.yaw;
}

TObjEZBoneRotPlayer::TObjEZBoneRotPlayer(TObjPlayer *player, NJS_OBJECT *root, EZBoneRotDesc *desc)
    : TObjEZBoneRotBase(player, root, desc) {
    m_name = TObjEZBoneRotPlayer__name;
    m_player = player;
    m_previous_yaw = m_player->rotation.yaw;
}

TObjEZBoneRotPlayer *TObjEZBoneRotPlayer::create(TObjPlayer *player, NJS_OBJECT *root, EZBoneRotDesc *desc) {
    return new TObjEZBoneRotPlayer(player, root, desc);
}

void TObjEZBoneRotPlayer::advance_bone_rotation() {
    start_bone_rotation_sequence(m_phase);
    if (m_scale > 0.0f) {
        m_phase += m_desc->phase_step;
    }
}

void TObjEZBoneRotPlayer::calc_bone_offsets_recursive(NJS_OBJECT *node, s32 phase, s32 amplitude) {
    do {
        s32 bone = m_key->bone;
        if (bone < 0) {
            return;
        }
        if (bone == m_bone_index) {
            f32 offset = (f32)amplitude * sin_table_lookup(phase);
            node->ang[0] = m_angles->x + (s32)(m_key->axis[0] * offset);
            node->ang[1] = m_angles->y + (s32)(m_key->axis[1] * offset);
            node->ang[2] = m_angles->z + (s32)(m_key->axis[2] * offset);
            m_angles++;
            m_key++;
            if (m_key->bone < 0) {
                return;
            }
        }
        m_bone_index++;
        if (node->child != NULL) {
            calc_bone_offsets_recursive(node->child, phase + m_desc->child_phase_step,
                (s32)(m_desc->child_amplitude_scale * (f32)amplitude));
        }
        node = node->sibling;
    } while (node != NULL);
}

void TObjEZBoneRotPlayer::start_bone_rotation_sequence(s32 phase) {
    m_bone_index = 0;
    m_key = m_desc->keys;
    m_angles = m_base_angles;
    calc_bone_offsets_recursive(m_root, phase, (s32)((f32)m_desc->amplitude * m_scale));
}

void TObjEZBoneRotBase::capture_base_angles_recursive(NJS_OBJECT *node) {
    do {
        s32 bone = m_key->bone;
        if (bone < 0) {
            return;
        }
        if (bone == m_bone_index) {
            node->evalflags &= ~NJD_EVAL_UNIT_ANG;
            m_angles->x = node->ang[0];
            m_angles->y = node->ang[1];
            m_angles->z = node->ang[2];
            m_angles++;
            m_key++;
            if (m_key->bone < 0) {
                return;
            }
        }
        m_bone_index++;
        if (node->child != NULL) {
            capture_base_angles_recursive(node->child);
        }
        node = node->sibling;
    } while (node != NULL);
}

void TObjEZBoneRotBase::capture_base_angles() {
    m_bone_index = 0;
    m_key = m_desc->keys;
    m_angles = m_base_angles;
    capture_base_angles_recursive(m_root);
}

TObjEZBoneRotBase::~TObjEZBoneRotBase() {}

TObjEZBoneRotBase::TObjEZBoneRotBase(TObject *parent, NJS_OBJECT *root, EZBoneRotDesc *desc)
    : TObject(parent) {
    m_name = lbl_805D2B48;
    m_root = root;
    m_desc = desc;
    EZBoneRotKey *key = m_desc->keys;
    while (key->bone >= 0) {
        key++;
    }
    capture_base_angles();
    m_phase = 0;
    m_scale = 0.0f;
}
