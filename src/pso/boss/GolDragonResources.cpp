#include "pso/boss/EffectGeometryParameters.h"
#include "pso/system/vector.h"

extern "C" {
extern const Vec TBoss8Dragon__data_804744A8 = {0.0f, 0.0f, 0.0f};
extern const EffectGeometryParameters lbl_804744B4 = {0, 0.0f, 30.0f, 7.0f, 1};
extern const EffectGeometryParameters TBoss8Dragon__body_effect_parameters = {0, 0.0f, 35.0f, 50.0f, 1};
extern const EffectGeometryParameters boss8_dragon_init_state_params = {0, 10.0f, 25.0f, 7.5f, 1};
extern const Vec lbl_804744F0 = {-35.0f, 0.0f, 10.0f};
extern const Vec lbl_804744FC = {-60.0f, 0.0f, -20.0f};
extern const s32 boss8_dragon_mode_params[10] = {
    0x41, 0x4c, 0x223, -1, 0xf0, 0x220, -1, 0x221, 0x222,
    0xc5,
};
extern const s32 dragon_mode_params_a[10] = {
    0x200, 0x211, 0x212, 0x212, 0x94, 0x21d, -1, 0x21c, 0x21b,
    0x219,
};
extern const s32 dragon_mode_params_b[10] = {
    0x41, 0x4c, 0x208, 0x203, 0xf0, 0x207, 0x200, 0x201, 0x202,
    0x205,
};
extern const s32 dragon_camera_script_frame_table[35] = {
    0, 8, 0xa, 0x28, 0x29, 0x32, 0x33, 0x36, 0x37,
    0x38, 0x39, 0x3a, 0x43, 0x46, 0x47, 0x48, 0x4a, 0x4c,
    0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x58, 0x59,
    0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x64, 0x66, 0x3e7,
};
extern const s32 dragon_next_action_table[11] = {
    3, 0x27, 0x28, 0x29, 0x2a, 3, 5, 6, 0x23,
    8, 0x21,
};
extern const s32 boss8_dragon_state_transition_table[8] = {
    0, 0, 2, 3, 3, 3, 0, 0,
};
extern const s32 boss8_dragon_action_pick_table[29] = {
    5, 6, 0xf, 0x2b, 0x13, 8, 0x27, 0x28, 3,
    5, 6, 0x23, 8, 3, 2, 0x29, 0x2a, 0x27,
    0x28, 3, 5, 6, 0x23, 8, 0x27, 0x28, 3,
    2, 0x22,
};
extern const s32 boss8_dragon_action_pick_table_b[28] = {
    0x13, 8, 0x27, 0x28, 3, 0x27, 0x28, 3, 2,
    3, 0x27, 0x28, 5, 6, 0x23, 8, 3, 5,
    6, 0x23, 8, 2, 3, 5, 6, 0xf, 0x16,
    0x21,
};

extern __declspec(section ".rodata") const char lbl_8047473C[] ATTRIBUTE_ALIGN(4) = "boss1_s_nb_dragon.nj";
extern __declspec(section ".rodata") const char lbl_80474754[] ATTRIBUTE_ALIGN(4) = "lo_boss1_s_nb_dragon.nj";
extern __declspec(section ".rodata") const char lbl_8047476C[] ATTRIBUTE_ALIGN(4) = "boss1_s_sd_dragon.nj";
extern __declspec(section ".rodata") const char lbl_80474784[] ATTRIBUTE_ALIGN(4) = "dead_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_804747A0[] ATTRIBUTE_ALIGN(4) = "bossopgc_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_804747C0[] ATTRIBUTE_ALIGN(4) = "down_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_804747DC[] ATTRIBUTE_ALIGN(4) = "frin_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_804747F8[] ATTRIBUTE_ALIGN(4) = "frloop_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_80474818[] ATTRIBUTE_ALIGN(4) = "frout_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_80474834[] ATTRIBUTE_ALIGN(4) = "land_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_80474850[] ATTRIBUTE_ALIGN(4) = "lift_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_8047486C[] ATTRIBUTE_ALIGN(4) = "nkdown_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_8047488C[] ATTRIBUTE_ALIGN(4) = "nkup_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_804748A8[] ATTRIBUTE_ALIGN(4) = "nobi_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_804748C4[] ATTRIBUTE_ALIGN(4) = "stand_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_804748E0[] ATTRIBUTE_ALIGN(4) = "tatk_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_804748FC[] ATTRIBUTE_ALIGN(4) = "walk_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_80474918[] ATTRIBUTE_ALIGN(4) = "wngclose_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_80474938[] ATTRIBUTE_ALIGN(4) = "wngopn_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_80474958[] ATTRIBUTE_ALIGN(4) = "daml_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_80474974[] ATTRIBUTE_ALIGN(4) = "dams_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_80474990[] ATTRIBUTE_ALIGN(4) = "fire_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_804749AC[] ATTRIBUTE_ALIGN(4) = "fly_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_804749C8[] ATTRIBUTE_ALIGN(4) = "flyshot_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_804749E8[] ATTRIBUTE_ALIGN(4) = "kiri_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_80474A04[] ATTRIBUTE_ALIGN(4) = "tobidasi_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_80474A24[] ATTRIBUTE_ALIGN(4) = "tukomi_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_80474A44[] ATTRIBUTE_ALIGN(4) = "wgwalk_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_80474A64[] ATTRIBUTE_ALIGN(4) = "wing_boss1_s_nb_dragon.njm";
extern __declspec(section ".rodata") const char lbl_80474A80[] ATTRIBUTE_ALIGN(4) = "bm_boss8_dragon.bml";
extern __declspec(section ".rodata") const char lbl_80474A94[] ATTRIBUTE_ALIGN(4) = "TBoss8Dragon";

extern const EffectGeometryParameters boss8_dragon_breath_eff_params = {0, 10.0f, 15.0f, 8.0f, 1};
extern const EffectGeometryParameters TBoss8Dragon__breath_params = {1, 2.0f, 10.0f, 10.0f, 1};
extern const EffectGeometryParameters lbl_80474ACC = {1, 10.0f, 30.0f, 10.0f, 1};
extern const EffectGeometryParameters lbl_80474AE0 = {0, 10.0f, 0.0f, 10.0f, 1};
extern const s32 boss8_dragon_point_index_table[4] = {
    3, 4, 5, 6,
};

const char *boss8_dragon_class_name = lbl_80474A94;
f32 lbl_805D6980;
f32 lbl_805D6984;
}
