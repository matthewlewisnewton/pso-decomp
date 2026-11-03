#include "pso/audio/SoundBankTables.h"

// --- data head (folded from pso/audio/SoundBankTables.cpp) ---

extern "C" {
extern const char sound_bank_filename_player_proj[] = "player.proj";
extern const char sound_bank_filename_player_pool[] = "player.pool";
extern const char sound_bank_filename_player_sdir[] = "player.sdir";
extern const char sound_bank_filename_player_samp[] = "player.samp";
extern const char sound_bank_filename_weapon_proj[] = "weapon.proj";
extern const char sound_bank_filename_weapon_pool[] = "weapon.pool";
extern const char sound_bank_filename_weapon_sdir[] = "weapon.sdir";
extern const char sound_bank_filename_weapon_samp[] = "weapon.samp";
extern const char sound_bank_filename_technic_proj[] = "technic.proj";
extern const char sound_bank_filename_technic_pool[] = "technic.pool";
extern const char sound_bank_filename_technic_sdir[] = "technic.sdir";
extern const char sound_bank_filename_technic_samp[] = "technic.samp";
extern const char sound_bank_filename_system_proj[] = "system.proj";
extern const char sound_bank_filename_system_pool[] = "system.pool";
extern const char sound_bank_filename_system_sdir[] = "system.sdir";
extern const char sound_bank_filename_system_samp[] = "system.samp";
extern const char sound_bank_filename_a_enemy_proj[] = "a_enemy.proj";
extern const char sound_bank_filename_a_enemy_pool[] = "a_enemy.pool";
extern const char sound_bank_filename_a_enemy_sdir[] = "a_enemy.sdir";
extern const char sound_bank_filename_a_enemy_samp[] = "a_enemy.samp";
extern const char sound_bank_filename_a_env_proj[] = "a_env.proj";
extern const char sound_bank_filename_a_env_pool[] = "a_env.pool";
extern const char sound_bank_filename_a_env_sdir[] = "a_env.sdir";
extern const char sound_bank_filename_a_env_samp[] = "a_env.samp";
extern const char sound_bank_filename_b1_enemy_proj[] = "b1_enemy.proj";
extern const char sound_bank_filename_b1_enemy_pool[] = "b1_enemy.pool";
extern const char sound_bank_filename_b1_enemy_sdir[] = "b1_enemy.sdir";
extern const char sound_bank_filename_b1_enemy_samp[] = "b1_enemy.samp";
extern const char sound_bank_filename_b2_enemy_proj[] = "b2_enemy.proj";
extern const char sound_bank_filename_b2_enemy_pool[] = "b2_enemy.pool";
extern const char sound_bank_filename_b2_enemy_sdir[] = "b2_enemy.sdir";
extern const char sound_bank_filename_b2_enemy_samp[] = "b2_enemy.samp";
extern const char sound_bank_filename_b3_enemy_proj[] = "b3_enemy.proj";
extern const char sound_bank_filename_b3_enemy_pool[] = "b3_enemy.pool";
extern const char sound_bank_filename_b3_enemy_sdir[] = "b3_enemy.sdir";
extern const char sound_bank_filename_b3_enemy_samp[] = "b3_enemy.samp";
extern const char sound_bank_filename_b4_enemy_proj[] = "b4_enemy.proj";
extern const char sound_bank_filename_b4_enemy_pool[] = "b4_enemy.pool";
extern const char sound_bank_filename_b4_enemy_sdir[] = "b4_enemy.sdir";
extern const char sound_bank_filename_b4_enemy_samp[] = "b4_enemy.samp";
extern const char sound_bank_filename_b5_enemy_proj[] = "b5_enemy.proj";
extern const char sound_bank_filename_b5_enemy_pool[] = "b5_enemy.pool";
extern const char sound_bank_filename_b5_enemy_sdir[] = "b5_enemy.sdir";
extern const char sound_bank_filename_b5_enemy_samp[] = "b5_enemy.samp";
extern const char sound_bank_filename_b6_enemy_proj[] = "b6_enemy.proj";
extern const char sound_bank_filename_b6_enemy_pool[] = "b6_enemy.pool";
extern const char sound_bank_filename_b6_enemy_sdir[] = "b6_enemy.sdir";
extern const char sound_bank_filename_b6_enemy_samp[] = "b6_enemy.samp";
extern const char sound_bank_filename_b7_enemy_proj[] = "b7_enemy.proj";
extern const char sound_bank_filename_b7_enemy_pool[] = "b7_enemy.pool";
extern const char sound_bank_filename_b7_enemy_sdir[] = "b7_enemy.sdir";
extern const char sound_bank_filename_b7_enemy_samp[] = "b7_enemy.samp";
extern const char sound_bank_filename_b81_enemy_proj[] = "b81_enemy.proj";
extern const char sound_bank_filename_b81_enemy_pool[] = "b81_enemy.pool";
extern const char sound_bank_filename_b81_enemy_sdir[] = "b81_enemy.sdir";
extern const char sound_bank_filename_b81_enemy_samp[] = "b81_enemy.samp";
extern const char sound_bank_filename_b82_enemy_proj[] = "b82_enemy.proj";
extern const char sound_bank_filename_b82_enemy_pool[] = "b82_enemy.pool";
extern const char sound_bank_filename_b82_enemy_sdir[] = "b82_enemy.sdir";
extern const char sound_bank_filename_b82_enemy_samp[] = "b82_enemy.samp";
extern const char sound_bank_filename_c_enemy_proj[] = "c_enemy.proj";
extern const char sound_bank_filename_c_enemy_pool[] = "c_enemy.pool";
extern const char sound_bank_filename_c_enemy_sdir[] = "c_enemy.sdir";
extern const char sound_bank_filename_c_enemy_samp[] = "c_enemy.samp";
extern const char sound_bank_filename_c_env_proj[] = "c_env.proj";
extern const char sound_bank_filename_c_env_pool[] = "c_env.pool";
extern const char sound_bank_filename_c_env_sdir[] = "c_env.sdir";
extern const char sound_bank_filename_c_env_samp[] = "c_env.samp";
extern const char sound_bank_filename_city_proj[] = "city.proj";
extern const char sound_bank_filename_city_pool[] = "city.pool";
extern const char sound_bank_filename_city_sdir[] = "city.sdir";
extern const char sound_bank_filename_city_samp[] = "city.samp";
extern const char sound_bank_filename_d1_enemy_proj[] = "d1_enemy.proj";
extern const char sound_bank_filename_d1_enemy_pool[] = "d1_enemy.pool";
extern const char sound_bank_filename_d1_enemy_sdir[] = "d1_enemy.sdir";
extern const char sound_bank_filename_d1_enemy_samp[] = "d1_enemy.samp";
extern const char sound_bank_filename_d1_env_proj[] = "d1_env.proj";
extern const char sound_bank_filename_d1_env_pool[] = "d1_env.pool";
extern const char sound_bank_filename_d1_env_sdir[] = "d1_env.sdir";
extern const char sound_bank_filename_d1_env_samp[] = "d1_env.samp";
extern const char sound_bank_filename_d2_enemy_proj[] = "d2_enemy.proj";
extern const char sound_bank_filename_d2_enemy_pool[] = "d2_enemy.pool";
extern const char sound_bank_filename_d2_enemy_sdir[] = "d2_enemy.sdir";
extern const char sound_bank_filename_d2_enemy_samp[] = "d2_enemy.samp";
extern const char sound_bank_filename_d2_env_proj[] = "d2_env.proj";
extern const char sound_bank_filename_d2_env_pool[] = "d2_env.pool";
extern const char sound_bank_filename_d2_env_sdir[] = "d2_env.sdir";
extern const char sound_bank_filename_d2_env_samp[] = "d2_env.samp";
extern const char sound_bank_filename_f_enemy_proj[] = "f_enemy.proj";
extern const char sound_bank_filename_f_enemy_pool[] = "f_enemy.pool";
extern const char sound_bank_filename_f_enemy_sdir[] = "f_enemy.sdir";
extern const char sound_bank_filename_f_enemy_samp[] = "f_enemy.samp";
extern const char sound_bank_filename_f_env_proj[] = "f_env.proj";
extern const char sound_bank_filename_f_env_pool[] = "f_env.pool";
extern const char sound_bank_filename_f_env_sdir[] = "f_env.sdir";
extern const char sound_bank_filename_f_env_samp[] = "f_env.samp";
extern const char sound_bank_filename_j_enemy_proj[] = "j_enemy.proj";
extern const char sound_bank_filename_j_enemy_pool[] = "j_enemy.pool";
extern const char sound_bank_filename_j_enemy_sdir[] = "j_enemy.sdir";
extern const char sound_bank_filename_j_enemy_samp[] = "j_enemy.samp";
extern const char sound_bank_filename_j_env_proj[] = "j_env.proj";
extern const char sound_bank_filename_j_env_pool[] = "j_env.pool";
extern const char sound_bank_filename_j_env_sdir[] = "j_env.sdir";
extern const char sound_bank_filename_j_env_samp[] = "j_env.samp";
extern const char sound_bank_filename_m_enemy_proj[] = "m_enemy.proj";
extern const char sound_bank_filename_m_enemy_pool[] = "m_enemy.pool";
extern const char sound_bank_filename_m_enemy_sdir[] = "m_enemy.sdir";
extern const char sound_bank_filename_m_enemy_samp[] = "m_enemy.samp";
extern const char sound_bank_filename_m_env_proj[] = "m_env.proj";
extern const char sound_bank_filename_m_env_pool[] = "m_env.pool";
extern const char sound_bank_filename_m_env_sdir[] = "m_env.sdir";
extern const char sound_bank_filename_m_env_samp[] = "m_env.samp";
extern const char sound_bank_filename_nb_enemy_proj[] = "nb_enemy.proj";
extern const char sound_bank_filename_nb_enemy_pool[] = "nb_enemy.pool";
extern const char sound_bank_filename_nb_enemy_sdir[] = "nb_enemy.sdir";
extern const char sound_bank_filename_nb_enemy_samp[] = "nb_enemy.samp";
extern const char sound_bank_filename_nb_env_proj[] = "nb_env.proj";
extern const char sound_bank_filename_nb_env_pool[] = "nb_env.pool";
extern const char sound_bank_filename_nb_env_sdir[] = "nb_env.sdir";
extern const char sound_bank_filename_nb_env_samp[] = "nb_env.samp";
extern const char sound_bank_filename_t_enemy_proj[] = "t_enemy.proj";
extern const char sound_bank_filename_t_enemy_pool[] = "t_enemy.pool";
extern const char sound_bank_filename_t_enemy_sdir[] = "t_enemy.sdir";
extern const char sound_bank_filename_t_enemy_samp[] = "t_enemy.samp";
extern const char sound_bank_filename_t_env_proj[] = "t_env.proj";
extern const char sound_bank_filename_t_env_pool[] = "t_env.pool";
extern const char sound_bank_filename_t_env_sdir[] = "t_env.sdir";
extern const char sound_bank_filename_t_env_samp[] = "t_env.samp";
extern const char sound_bank_filename_v1_enemy_proj[] = "v1_enemy.proj";
extern const char sound_bank_filename_v1_enemy_pool[] = "v1_enemy.pool";
extern const char sound_bank_filename_v1_enemy_sdir[] = "v1_enemy.sdir";
extern const char sound_bank_filename_v1_enemy_samp[] = "v1_enemy.samp";
extern const char sound_bank_filename_v1_env_proj[] = "v1_env.proj";
extern const char sound_bank_filename_v1_env_pool[] = "v1_env.pool";
extern const char sound_bank_filename_v1_env_sdir[] = "v1_env.sdir";
extern const char sound_bank_filename_v1_env_samp[] = "v1_env.samp";
extern const char sound_bank_filename_v2_enemy_proj[] = "v2_enemy.proj";
extern const char sound_bank_filename_v2_enemy_pool[] = "v2_enemy.pool";
extern const char sound_bank_filename_v2_enemy_sdir[] = "v2_enemy.sdir";
extern const char sound_bank_filename_v2_enemy_samp[] = "v2_enemy.samp";
extern const char sound_bank_filename_v2_env_proj[] = "v2_env.proj";
extern const char sound_bank_filename_v2_env_pool[] = "v2_env.pool";
extern const char sound_bank_filename_v2_env_sdir[] = "v2_env.sdir";
extern const char sound_bank_filename_v2_env_samp[] = "v2_env.samp";
extern const char sound_bank_filename_w_enemy_proj[] = "w_enemy.proj";
extern const char sound_bank_filename_w_enemy_pool[] = "w_enemy.pool";
extern const char sound_bank_filename_w_enemy_sdir[] = "w_enemy.sdir";
extern const char sound_bank_filename_w_enemy_samp[] = "w_enemy.samp";
extern const char sound_bank_filename_w_env_proj[] = "w_env.proj";
extern const char sound_bank_filename_w_env_pool[] = "w_env.pool";
extern const char sound_bank_filename_w_env_sdir[] = "w_env.sdir";
extern const char sound_bank_filename_w_env_samp[] = "w_env.samp";
extern const char sound_bank_filename_noname[] = "noname";

s16 sound_bank_load_list_city[] = { 17, -1 };
s16 sound_bank_load_list_b1_enemy[] = { 6, -1 };
s16 sound_bank_load_list_b2_enemy[] = { 7, -1 };
s16 sound_bank_load_list_b3_enemy[] = { 8, -1 };
s16 sound_bank_load_list_b4_enemy[] = { 9, -1 };
s16 sound_bank_load_list_b5_enemy[] = { 10, -1 };
s16 sound_bank_load_list_b7_enemy[] = { 12, -1 };
s16 sound_bank_load_list_b6_enemy[] = { 11, -1 };

u32 sound_bank_file_sizes[153] = {
    0x200, 0x684, 0x994, 0x7B040,
    0x3A4, 0xFB8, 0x1294, 0x12A180,
    0x2A8, 0xCF8, 0xC1C, 0x130198,
    0x1F0, 0x6A8, 0x904, 0xB65B0,
    0x2E0, 0xA40, 0xCF4, 0x163750,
    0x1A4, 0x5B8, 0x70C, 0xB3D90,
    0x148, 0x3E8, 0x55C, 0xF5D50,
    0x108, 0x418, 0x55C, 0x89DB8,
    0x1A4, 0x758, 0x9DC, 0xD7898,
    0x2D0, 0xAE8, 0xE5C, 0x251150,
    0x168, 0x468, 0x5EC, 0xD16F8,
    0x174, 0x498, 0x634, 0x114320,
    0x1B0, 0x598, 0x754, 0x140A58,
    0x2A8, 0xAB8, 0xE5C, 0x244C10,
    0x2A8, 0x9B8, 0xD84, 0x242498,
    0x278, 0xA98, 0xDCC, 0x190948,
    0x1C4, 0x5F8, 0x754, 0xCFBE0,
    0xC8, 0x248, 0x244, 0x41758,
    0x354, 0xD18, 0x100C, 0x19F4E0,
    0x128, 0x378, 0x4CC, 0x4E990,
    0x354, 0xD18, 0x100C, 0x19F4E0,
    0x128, 0x348, 0x484, 0x81BD0,
    0x2E4, 0x948, 0xAFC, 0xDFC60,
    0x1A0, 0x5A8, 0x70C, 0xD01E0,
    0x414, 0xD18, 0x1294, 0x151E38,
    0x22C, 0x7E8, 0xA24, 0x149FE0,
    0x194, 0x688, 0x8BC, 0xFECE0,
    0x178, 0x558, 0x6C4, 0x8BCA0,
    0x2BC, 0x8D8, 0xC64, 0xBA3D8,
    0x22C, 0x7E8, 0xA24, 0x149FE0,
    0x518, 0x1148, 0x1834, 0x216A30,
    0x22C, 0x7E8, 0xA24, 0x149FE0,
    0x38C, 0xDE0, 0x109C, 0x168EC8,
    0x174, 0x4B8, 0x634, 0xAF4D0,
    0x300, 0xB68, 0xF34, 0x1EE3B0,
    0x178, 0x4E8, 0x67C, 0x7C290,
    0x31C, 0x978, 0xD84, 0xFFDB8,
    0x228, 0x7D8, 0xA24, 0x184320,
    0x0,
};

const char* sound_bank_filenames[153] = {
    sound_bank_filename_player_proj, sound_bank_filename_player_pool, sound_bank_filename_player_sdir, sound_bank_filename_player_samp,
    sound_bank_filename_weapon_proj, sound_bank_filename_weapon_pool, sound_bank_filename_weapon_sdir, sound_bank_filename_weapon_samp,
    sound_bank_filename_technic_proj, sound_bank_filename_technic_pool, sound_bank_filename_technic_sdir, sound_bank_filename_technic_samp,
    sound_bank_filename_system_proj, sound_bank_filename_system_pool, sound_bank_filename_system_sdir, sound_bank_filename_system_samp,
    sound_bank_filename_a_enemy_proj, sound_bank_filename_a_enemy_pool, sound_bank_filename_a_enemy_sdir, sound_bank_filename_a_enemy_samp,
    sound_bank_filename_a_env_proj, sound_bank_filename_a_env_pool, sound_bank_filename_a_env_sdir, sound_bank_filename_a_env_samp,
    sound_bank_filename_b1_enemy_proj, sound_bank_filename_b1_enemy_pool, sound_bank_filename_b1_enemy_sdir, sound_bank_filename_b1_enemy_samp,
    sound_bank_filename_b2_enemy_proj, sound_bank_filename_b2_enemy_pool, sound_bank_filename_b2_enemy_sdir, sound_bank_filename_b2_enemy_samp,
    sound_bank_filename_b3_enemy_proj, sound_bank_filename_b3_enemy_pool, sound_bank_filename_b3_enemy_sdir, sound_bank_filename_b3_enemy_samp,
    sound_bank_filename_b4_enemy_proj, sound_bank_filename_b4_enemy_pool, sound_bank_filename_b4_enemy_sdir, sound_bank_filename_b4_enemy_samp,
    sound_bank_filename_b5_enemy_proj, sound_bank_filename_b5_enemy_pool, sound_bank_filename_b5_enemy_sdir, sound_bank_filename_b5_enemy_samp,
    sound_bank_filename_b6_enemy_proj, sound_bank_filename_b6_enemy_pool, sound_bank_filename_b6_enemy_sdir, sound_bank_filename_b6_enemy_samp,
    sound_bank_filename_b7_enemy_proj, sound_bank_filename_b7_enemy_pool, sound_bank_filename_b7_enemy_sdir, sound_bank_filename_b7_enemy_samp,
    sound_bank_filename_b81_enemy_proj, sound_bank_filename_b81_enemy_pool, sound_bank_filename_b81_enemy_sdir, sound_bank_filename_b81_enemy_samp,
    sound_bank_filename_b82_enemy_proj, sound_bank_filename_b82_enemy_pool, sound_bank_filename_b82_enemy_sdir, sound_bank_filename_b82_enemy_samp,
    sound_bank_filename_c_enemy_proj, sound_bank_filename_c_enemy_pool, sound_bank_filename_c_enemy_sdir, sound_bank_filename_c_enemy_samp,
    sound_bank_filename_c_env_proj, sound_bank_filename_c_env_pool, sound_bank_filename_c_env_sdir, sound_bank_filename_c_env_samp,
    sound_bank_filename_city_proj, sound_bank_filename_city_pool, sound_bank_filename_city_sdir, sound_bank_filename_city_samp,
    sound_bank_filename_d1_enemy_proj, sound_bank_filename_d1_enemy_pool, sound_bank_filename_d1_enemy_sdir, sound_bank_filename_d1_enemy_samp,
    sound_bank_filename_d1_env_proj, sound_bank_filename_d1_env_pool, sound_bank_filename_d1_env_sdir, sound_bank_filename_d1_env_samp,
    sound_bank_filename_d2_enemy_proj, sound_bank_filename_d2_enemy_pool, sound_bank_filename_d2_enemy_sdir, sound_bank_filename_d2_enemy_samp,
    sound_bank_filename_d2_env_proj, sound_bank_filename_d2_env_pool, sound_bank_filename_d2_env_sdir, sound_bank_filename_d2_env_samp,
    sound_bank_filename_f_enemy_proj, sound_bank_filename_f_enemy_pool, sound_bank_filename_f_enemy_sdir, sound_bank_filename_f_enemy_samp,
    sound_bank_filename_f_env_proj, sound_bank_filename_f_env_pool, sound_bank_filename_f_env_sdir, sound_bank_filename_f_env_samp,
    sound_bank_filename_j_enemy_proj, sound_bank_filename_j_enemy_pool, sound_bank_filename_j_enemy_sdir, sound_bank_filename_j_enemy_samp,
    sound_bank_filename_j_env_proj, sound_bank_filename_j_env_pool, sound_bank_filename_j_env_sdir, sound_bank_filename_j_env_samp,
    sound_bank_filename_m_enemy_proj, sound_bank_filename_m_enemy_pool, sound_bank_filename_m_enemy_sdir, sound_bank_filename_m_enemy_samp,
    sound_bank_filename_m_env_proj, sound_bank_filename_m_env_pool, sound_bank_filename_m_env_sdir, sound_bank_filename_m_env_samp,
    sound_bank_filename_nb_enemy_proj, sound_bank_filename_nb_enemy_pool, sound_bank_filename_nb_enemy_sdir, sound_bank_filename_nb_enemy_samp,
    sound_bank_filename_nb_env_proj, sound_bank_filename_nb_env_pool, sound_bank_filename_nb_env_sdir, sound_bank_filename_nb_env_samp,
    sound_bank_filename_t_enemy_proj, sound_bank_filename_t_enemy_pool, sound_bank_filename_t_enemy_sdir, sound_bank_filename_t_enemy_samp,
    sound_bank_filename_t_env_proj, sound_bank_filename_t_env_pool, sound_bank_filename_t_env_sdir, sound_bank_filename_t_env_samp,
    sound_bank_filename_v1_enemy_proj, sound_bank_filename_v1_enemy_pool, sound_bank_filename_v1_enemy_sdir, sound_bank_filename_v1_enemy_samp,
    sound_bank_filename_v1_env_proj, sound_bank_filename_v1_env_pool, sound_bank_filename_v1_env_sdir, sound_bank_filename_v1_env_samp,
    sound_bank_filename_v2_enemy_proj, sound_bank_filename_v2_enemy_pool, sound_bank_filename_v2_enemy_sdir, sound_bank_filename_v2_enemy_samp,
    sound_bank_filename_v2_env_proj, sound_bank_filename_v2_env_pool, sound_bank_filename_v2_env_sdir, sound_bank_filename_v2_env_samp,
    sound_bank_filename_w_enemy_proj, sound_bank_filename_w_enemy_pool, sound_bank_filename_w_enemy_sdir, sound_bank_filename_w_enemy_samp,
    sound_bank_filename_w_env_proj, sound_bank_filename_w_env_pool, sound_bank_filename_w_env_sdir, sound_bank_filename_w_env_samp,
    sound_bank_filename_noname,
};

u16 sound_bank_file_crc16[152] = {
    0x526D, 0x59A2, 0x2B29, 0x7BED, 0x9EF6, 0x66C5, 0x7BCE, 0x28F2,
    0x4E6B, 0xDB7E, 0xDD99, 0xF77B, 0x06AB, 0x7A22, 0xBA6D, 0x5540,
    0xBC16, 0x4DF0, 0xA5E2, 0x36B1, 0xFFB4, 0x163B, 0x6AB5, 0xF364,
    0x75B2, 0x378E, 0xD0F1, 0x5145, 0x172F, 0xAAB0, 0x925C, 0x88DD,
    0x59A8, 0xB848, 0x6BEA, 0x3233, 0xC491, 0xFC36, 0x71C2, 0xCFC9,
    0xD7C8, 0xE901, 0xE3CB, 0xD0A2, 0x7D81, 0xA391, 0xE7CF, 0x2B13,
    0xF6CB, 0xE590, 0xD07A, 0xF8CB, 0xBEA5, 0xEB4F, 0x1E5E, 0x7A24,
    0x859E, 0x4962, 0xC3C2, 0x93C4, 0x3957, 0xBCB9, 0x5D3C, 0x53E7,
    0xDA66, 0x3A61, 0x84A8, 0xD12C, 0x2DF9, 0xDE89, 0x0965, 0x6920,
    0x8F31, 0x66C5, 0xA890, 0xBF6D, 0xD73A, 0x0B8F, 0x990C, 0x67F2,
    0xC4FA, 0x66C5, 0xA890, 0xBF6D, 0xFB0C, 0xB7BC, 0x372B, 0xCCF1,
    0x0475, 0x6B4E, 0x60D9, 0xCD22, 0x9D4F, 0xBE45, 0x01BB, 0xE70F,
    0x38E0, 0x471C, 0xC6B9, 0xCE1F, 0x6025, 0xD873, 0x0F39, 0x868B,
    0x70D0, 0xF40A, 0x4E4B, 0x7C47, 0xA0E4, 0xE2C4, 0xE8A3, 0x3409,
    0x0169, 0xD025, 0xA0CD, 0xAB1B, 0xDA1A, 0xD873, 0x0F39, 0x868B,
    0x7160, 0x6829, 0xEBC0, 0xB4B5, 0xC60B, 0xD873, 0x0F39, 0x868B,
    0xB9BF, 0x176F, 0xDC0F, 0x9ADB, 0xE23D, 0x16FA, 0xD8A0, 0xF046,
    0x9BEC, 0x3215, 0xF801, 0xE139, 0x3FB9, 0x5819, 0xD53F, 0x6407,
    0x35D4, 0xF385, 0xBE91, 0x6616, 0xF128, 0xE8D4, 0x044A, 0xDC83,
};

__declspec(section ".data") SoundEffectRange sound_effect_range_player = { 0x0, 0x21 };
__declspec(section ".data") SoundEffectRange sound_effect_range_weapon = { 0x22, 0x66 };
__declspec(section ".data") SoundEffectRange sound_effect_range_technic = { 0x67, 0x98 };
__declspec(section ".data") SoundEffectRange sound_effect_range_system = { 0xE7, 0x107 };
__declspec(section ".data") SoundEffectRange sound_effect_range_a_enemy = { 0x20E, 0x24F };
__declspec(section ".data") SoundEffectRange sound_effect_range_a_env = { 0x250, 0x26C };
__declspec(section ".data") SoundEffectRange sound_effect_range_b1_enemy = { 0x108, 0x11A };
__declspec(section ".data") SoundEffectRange sound_effect_range_b2_enemy = { 0x195, 0x1A7 };
__declspec(section ".data") SoundEffectRange sound_effect_range_b3_enemy = { 0x1EB, 0x20D };
__declspec(section ".data") SoundEffectRange sound_effect_range_b4_enemy = { 0x26D, 0x2A9 };
__declspec(section ".data") SoundEffectRange sound_effect_range_b7_enemy = { 0x39C, 0x3B5 };
__declspec(section ".data") SoundEffectRange sound_effect_range_c_enemy = { 0x13F, 0x176 };
__declspec(section ".data") SoundEffectRange sound_effect_range_c_env = { 0x177, 0x194 };
__declspec(section ".data") SoundEffectRange sound_effect_range_city = { 0x1A8, 0x1B1 };
__declspec(section ".data") SoundEffectRange sound_effect_range_d1_enemy = { 0x2AA, 0x2ED };
__declspec(section ".data") SoundEffectRange sound_effect_range_d1_env = { 0x2EE, 0x2FE };
__declspec(section ".data") SoundEffectRange sound_effect_range_d2_enemy = { 0x310, 0x353 };
__declspec(section ".data") SoundEffectRange sound_effect_range_d2_env = { 0x2FF, 0x30F };
__declspec(section ".data") SoundEffectRange sound_effect_range_f_enemy = { 0x99, 0xCC };
__declspec(section ".data") SoundEffectRange sound_effect_range_f_env = { 0xCD, 0xE6 };
__declspec(section ".data") SoundEffectRange sound_effect_range_j_enemy = { 0x354, 0x39B };
__declspec(section ".data") SoundEffectRange sound_effect_range_j_env = { 0x11B, 0x13E };
__declspec(section ".data") SoundEffectRange sound_effect_range_m_enemy = { 0x1B2, 0x1D2 };
__declspec(section ".data") SoundEffectRange sound_effect_range_m_env = { 0x1D3, 0x1EA };
__declspec(section ".data") SoundEffectRange sound_effect_range_v1_enemy = { 0x3B6, 0x3FA };
__declspec(section ".data") SoundEffectRange sound_effect_range_v1_env = { 0x3FB, 0x411 };
__declspec(section ".data") SoundEffectRange sound_effect_range_v2_enemy = { 0x412, 0x451 };
__declspec(section ".data") SoundEffectRange sound_effect_range_v2_env = { 0x452, 0x468 };
__declspec(section ".data") SoundEffectRange sound_effect_range_w_enemy = { 0x469, 0x49E };
__declspec(section ".data") SoundEffectRange sound_effect_range_w_env = { 0x49F, 0x4C3 };
__declspec(section ".data") SoundEffectRange sound_effect_range_b81_enemy = { 0x5C0, 0x5F2 };
__declspec(section ".data") SoundEffectRange sound_effect_range_b82_enemy = { 0x5F3, 0x622 };
__declspec(section ".data") SoundEffectRange sound_effect_range_b5_enemy = { 0x4C4, 0x4D8 };
__declspec(section ".data") SoundEffectRange sound_effect_range_b6_enemy = { 0x558, 0x56D };
__declspec(section ".data") SoundEffectRange sound_effect_range_nb_enemy = { 0x592, 0x5BF };
__declspec(section ".data") SoundEffectRange sound_effect_range_nb_env = { 0x56E, 0x591 };
__declspec(section ".data") SoundEffectRange sound_effect_range_t_enemy = { 0x4FD, 0x557 };
__declspec(section ".data") SoundEffectRange sound_effect_range_t_env = { 0x4D9, 0x4FC };

SoundEffectBankRoutes sound_effect_bank_range_routes = {
    {
        &sound_effect_range_player,
        &sound_effect_range_weapon,
        &sound_effect_range_technic,
        0,
        0,
        &sound_effect_range_system,
        0,
    },
    {
        0,
        0,
        &sound_effect_range_f_enemy,
        &sound_effect_range_b1_enemy,
        &sound_effect_range_c_enemy,
        &sound_effect_range_b2_enemy,
        &sound_effect_range_m_enemy,
        &sound_effect_range_b3_enemy,
        &sound_effect_range_a_enemy,
        &sound_effect_range_b4_enemy,
        &sound_effect_range_d1_enemy,
        &sound_effect_range_d2_enemy,
        &sound_effect_range_j_enemy,
        &sound_effect_range_b7_enemy,
        &sound_effect_range_v1_enemy,
        &sound_effect_range_v2_enemy,
        &sound_effect_range_w_enemy,
        &sound_effect_range_b81_enemy,
        &sound_effect_range_b5_enemy,
        &sound_effect_range_nb_enemy,
        &sound_effect_range_t_enemy,
        &sound_effect_range_b6_enemy,
    },
    {
        0,
        &sound_effect_range_city,
        &sound_effect_range_f_env,
        0,
        &sound_effect_range_c_env,
        0,
        &sound_effect_range_m_env,
        0,
        &sound_effect_range_a_env,
        0,
        &sound_effect_range_d1_env,
        &sound_effect_range_d2_env,
        &sound_effect_range_j_env,
        0,
        &sound_effect_range_v1_env,
        &sound_effect_range_v2_env,
        &sound_effect_range_w_env,
        0,
        0,
        &sound_effect_range_nb_env,
        &sound_effect_range_t_env,
        0,
    },
    {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        &sound_effect_range_b82_enemy,
        0,
        0,
        0,
        0,
    },
};

u16 sound_bank_file_indices[38][4] = {
    { 0, 1, 2, 3 },
    { 4, 5, 6, 7 },
    { 8, 9, 10, 11 },
    { 12, 13, 14, 15 },
    { 16, 17, 18, 19 },
    { 20, 21, 22, 23 },
    { 24, 25, 26, 27 },
    { 28, 29, 30, 31 },
    { 32, 33, 34, 35 },
    { 36, 37, 38, 39 },
    { 40, 41, 42, 43 },
    { 44, 45, 46, 47 },
    { 48, 49, 50, 51 },
    { 52, 53, 54, 55 },
    { 56, 57, 58, 59 },
    { 60, 61, 62, 63 },
    { 64, 65, 66, 67 },
    { 68, 69, 70, 71 },
    { 72, 73, 74, 75 },
    { 76, 77, 78, 79 },
    { 80, 81, 82, 83 },
    { 84, 85, 86, 87 },
    { 88, 89, 90, 91 },
    { 92, 93, 94, 95 },
    { 96, 97, 98, 99 },
    { 100, 101, 102, 103 },
    { 104, 105, 106, 107 },
    { 108, 109, 110, 111 },
    { 112, 113, 114, 115 },
    { 116, 117, 118, 119 },
    { 120, 121, 122, 123 },
    { 124, 125, 126, 127 },
    { 128, 129, 130, 131 },
    { 132, 133, 134, 135 },
    { 136, 137, 138, 139 },
    { 140, 141, 142, 143 },
    { 144, 145, 146, 147 },
    { 148, 149, 150, 151 },
};

__declspec(section ".data") s16 sound_bank_load_list_common[] = { 0, 1, 2, 3, -1 };
__declspec(section ".data") s16 sound_bank_load_list_f_enemy_f_env[] = { 22, 23, -1 };
__declspec(section ".data") s16 sound_bank_load_list_c_enemy_c_env[] = { 15, 16, -1 };
__declspec(section ".data") s16 sound_bank_load_list_m_enemy_m_env[] = { 26, 27, -1 };
__declspec(section ".data") s16 sound_bank_load_list_a_enemy_a_env[] = { 4, 5, -1 };
__declspec(section ".data") s16 sound_bank_load_list_d1_enemy_d1_env[] = { 18, 19, -1 };
__declspec(section ".data") s16 sound_bank_load_list_d2_enemy_d2_env[] = { 20, 21, -1 };
__declspec(section ".data") s16 sound_bank_load_list_j_enemy_j_env[] = { 24, 25, -1 };
__declspec(section ".data") s16 sound_bank_load_list_v1_enemy_v1_env[] = { 32, 33, -1 };
__declspec(section ".data") s16 sound_bank_load_list_v2_enemy_v2_env[] = { 34, 35, -1 };
__declspec(section ".data") s16 sound_bank_load_list_w_enemy_w_env[] = { 36, 37, -1 };
__declspec(section ".data") s16 sound_bank_load_list_b81_enemy_b82_enemy[] = { 13, 14, -1 };
__declspec(section ".data") s16 sound_bank_load_list_nb_enemy_nb_env[] = { 28, 29, -1 };
__declspec(section ".data") s16 sound_bank_load_list_t_enemy_t_env[] = { 30, 31, -1 };

s16* sound_bank_load_routes[22] = {
    sound_bank_load_list_common,
    sound_bank_load_list_city,
    sound_bank_load_list_f_enemy_f_env,
    sound_bank_load_list_b1_enemy,
    sound_bank_load_list_c_enemy_c_env,
    sound_bank_load_list_b2_enemy,
    sound_bank_load_list_m_enemy_m_env,
    sound_bank_load_list_b3_enemy,
    sound_bank_load_list_a_enemy_a_env,
    sound_bank_load_list_b4_enemy,
    sound_bank_load_list_d1_enemy_d1_env,
    sound_bank_load_list_d2_enemy_d2_env,
    sound_bank_load_list_j_enemy_j_env,
    sound_bank_load_list_b7_enemy,
    sound_bank_load_list_v1_enemy_v1_env,
    sound_bank_load_list_v2_enemy_v2_env,
    sound_bank_load_list_w_enemy_w_env,
    sound_bank_load_list_b81_enemy_b82_enemy,
    sound_bank_load_list_b5_enemy,
    sound_bank_load_list_nb_enemy_nb_env,
    sound_bank_load_list_t_enemy_t_env,
    sound_bank_load_list_b6_enemy,
};

u16 sound_bank_group_ids[38] = {
    0, 1, 2, 5, 15, 16, 6, 10,
    14, 17, 30, 33, 23, 36, 37, 8,
    9, 11, 18, 19, 21, 20, 3, 4,
    22, 7, 12, 13, 35, 34, 32, 31,
    24, 25, 26, 27, 28, 29,
};
}
#include "pso/misc/TLobby_8023F734.h"
#include "pso/system/memory.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/audio/SoundRequestVoice.h"
#include "pso/misc/TLobby_80242910.h"
#include "pso/misc/TLobby_803382E4.h"
#include "pso/system/main_loop.h"
#include <string.h>
#pragma readonly_strings on
struct Voice_80241FD8;
#pragma push

#include "types.h"

typedef struct Range_8023FBBC {
    s32 start;
    s32 end;
} Range_8023FBBC;

typedef struct Owner_8023FBBC {
    u8 pad[0x288];
    s32 kind;
} Owner_8023FBBC;

SoundRequestVoice lbl_805162EC[0x28];
u8 lbl_80517BEC[0x258];   // contents of SOUND.BIN (read by init_sound_aux_effects)
void *lbl_80517E44[0x27];  // MusyX sdir buffers per sound bank (inferred)
u16 calculate_crc16_ccitt(const u8* bytes, s32 count);
extern "C" {
s32 sndOutputMode(s32);

s32 advance_rng__6TLobbyFPv(void *arg0) {
    *(s32 *)((s8 *)arg0 + 0x2AC) = (s32) ((*(s32 *)((s8 *)arg0 + 0x2AC) * 0x10DCD) + 1);
    return *(s32 *)((s8 *)arg0 + 0x2AC);
}

void TLobby__sub_8023F754(s32 arg0, s32 arg1) {
    if (arg0 < 0 || arg0 >= 0x20) {
        return;
    }
    s32 *p = (s32 *)&lbl_805162EC;
    p[arg0 * 40 + 34] = arg1;
}

void set_sound_slot_special_scale(s32 slot, f32 scale) {
    if (slot < 0 || slot >= 32) return;
    clamp_field9c__6TLobbyFPvf(&lbl_805162EC[slot], scale);
}

f32 get_field_2a4__6TLobbyFPv(void* p) { return *(f32*)((char*)p + 0x2a4); }
s32 get_field_0x280__6TLobbyFPv(void* p) { return *(s32*)((char*)p + 0x280); }
void set_menu_index__6TLobbyFPvi(void* p, s32 v) { *(s32*)((char*)p + 0x280) = v; }
void set_mode__6TLobbyFPvi(void *arg0, s32 arg1) {
    switch (arg1) {
    case 0:
        sndOutputMode(0);
        *(s32 *)((s8 *)arg0 + 0x2A0) = arg1;
        return;
    case 1:
        sndOutputMode(1);
        *(s32 *)((s8 *)arg0 + 0x2A0) = arg1;
        return;
    case 2:
        sndOutputMode(2);
        *(s32 *)((s8 *)arg0 + 0x2A0) = arg1;
        return;
    }
}


void set_clamped_field27c__6TLobbyFPvf(void *arg0, f32 farg0) {
    f32 var_f1;

    var_f1 = farg0;
    if (var_f1 < 0.0f) {
        var_f1 = 0.0f;
    }
    if (var_f1 > 1.0f) {
        var_f1 = 1.0f;
    }
    *(f32 *)((s8 *)arg0 + 0x27C) = var_f1;
}
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma opt_dead_assignments off
s32 TLobby__sub_8023F880(s32 arg0) {
  u8 *new_var;
  s8 *new_var2;
  if ((arg0 >= 0) && (arg0 < 0x28))
  {
    new_var = (u8 *)lbl_805162EC;
    new_var2 = (s8 *) (new_var + (arg0 * 0xA0));
    return *((s32 *)(new_var2 + 4));
  }
  return -9;
}
void fade_out_sound_slot(s32 slot, s32 step) {
    if (slot < 0 || slot >= 32) return;
    ((void (*)(void*, s32))start_voice_fade)(&lbl_805162EC[slot], step);
}
void set_sound_slot_pitch(s32 slot, s32 pitch, s32 duration) {
    if (slot < 0 || slot >= 0x20) {
        return;
    }
    set_voice_pitch_slide((u8 *)&lbl_805162EC[slot], (s32)((u32)pitch << 13) / 3072, duration);
}
#pragma push
#pragma opt_common_subs on
#pragma opt_propagation on
#pragma opt_dead_assignments on
s32 alloc_looping_sound_slot(u32 id, s32 actor, const void *position, s32 base, s32 flags) {
    s32 i;
    for (i = 0; i < 32; i++) {
        if ((lbl_805162EC[i].state == -1 || lbl_805162EC[i].state == 1) &&
            lbl_805162EC[i].kind == 0 && (s32)(id >> 16) == lbl_805162EC[i].bank &&
            (s32)(id & 0xFFFF) == lbl_805162EC[i].index && actor == (s32)lbl_805162EC[i].actor &&
            (lbl_805162EC[i].flags & 1)) {
            TLobby__sub_802409E4(&lbl_805162EC[i]);
            lbl_805162EC[i].position = position;
            lbl_805162EC[i].base = base;
            return i;
        }
    }
    for (i = 0; i < 32; i++) {
        if (lbl_805162EC[i].state == 0) {
            goto found;
        }
    }
    return -6;
found:
    init_sound_voice__6TLobbyFPviiii(&lbl_805162EC[i], 0, id >> 16, id & 0xFFFF, flags | 1);
    lbl_805162EC[i].base = base;
    lbl_805162EC[i].extra = 0;
    lbl_805162EC[i].spatial = 0;
    lbl_805162EC[i].position = position;
    lbl_805162EC[i].actor = (void *)actor;
    lbl_805162EC[i].refresh = 5;
    return i;
}

s32 alloc_one_shot_sound_slot(u32 id, const void *position, s32 base, s32 flags) {
    s32 i;
    for (i = 0; i < 32; i++) {
        if ((lbl_805162EC[i].state == -1 || lbl_805162EC[i].state == 1) &&
            lbl_805162EC[i].kind == 0 && (s32)(id >> 16) == lbl_805162EC[i].bank &&
            (s32)(id & 0xFFFF) == lbl_805162EC[i].index && lbl_805162EC[i].age <= 2) {
            if (lbl_805162EC[i].base < base) {
                lbl_805162EC[i].base = base;
            }
            return i;
        }
    }
    for (i = 0; i < 32; i++) {
        if (lbl_805162EC[i].state == 0) {
            goto found;
        }
    }
    return -6;
found:
    init_sound_voice__6TLobbyFPviiii(&lbl_805162EC[i], 0, id >> 16, id & 0xFFFF, flags);
    lbl_805162EC[i].base = base;
    lbl_805162EC[i].extra = 0;
    lbl_805162EC[i].spatial = 0;
    lbl_805162EC[i].position = position;
    lbl_805162EC[i].actor = 0;
    return i;
}
#pragma pop

#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma opt_dead_assignments off
s32 resolve_sound_effect_bank(Owner_8023FBBC *owner, s32 kind, s32 bank, s32 index) {
    u8 *t = (u8 *)&sound_bank_file_sizes;
    s32 result = -1;
    Range_8023FBBC *r = NULL;
    switch (kind) {
    case 0:
        switch (bank) {
        case 0:
        case 1:
        case 2:
        case 5:
            { s32 off = bank * 4; u8 *a = t + 0x728; r = *(Range_8023FBBC **)(a + off); }
            break;
        case 3:
            if (owner->kind >= 0 && owner->kind < 22) {
                { s32 off = owner->kind * 4; u8 *a = t + 0x744; r = *(Range_8023FBBC **)(a + off); }
            }
            break;
        case 4:
            if (owner->kind >= 0 && owner->kind < 22) {
                { s32 off = owner->kind * 4; u8 *a = t + 0x79C; r = *(Range_8023FBBC **)(a + off); }
            }
            break;
        case 6:
            if (owner->kind >= 0 && owner->kind < 22) {
                { s32 off = owner->kind * 4; u8 *a = t + 0x7F4; r = *(Range_8023FBBC **)(a + off); }
            }
            break;
        }
        break;
    }
    if (r != NULL && index >= 0 && index <= r->end - r->start) {
        result = index + r->start;
    }
    return result;
}
}
#pragma pop

#pragma pop


struct Ent_8023FCC0 {
    u32 h[4];
    s32 k[4];
    s32 pad20;
};

// The sound control object (sound_control_state, set up by init_sound_aux_effects).
struct Obj_8023FCC0 {
    u8 reverb[0x1C4];             // MusyX SND_AUX_REVERBHI work area
    u8 reverb_temp_disable;       // SND_AUX_REVERBHI.tempDisable
    f32 reverb_coloration;
    f32 reverb_mix;
    f32 reverb_time;
    f32 reverb_damping;
    f32 reverb_pre_delay;
    f32 reverb_crosstalk;
    u8 chorus[0x90];              // MusyX SND_AUX_CHORUS work area
    u32 chorus_base_delay;        // SND_AUX_CHORUS.baseDelay
    u32 chorus_variation;
    u32 chorus_period;
    f32 reverb_level;             // SoundRequestOwner::reverb: voices send it (send_sound_request_reverb)
    s32 f280;
    s32 age;
    s32 group_state;
    u8 pad_28C[0x298 - 0x28C];
    s32 load_state;
    s32 next_group_state;
    u8 pad_2A0[0x2B0 - 0x2A0];
    s32 route_pos;
    s16 *route;
    s32 depth;
    s32 f2BC;
    s32 stack[16];
    s32 tick;
    u32 elapsed;
    u32 ms;
    u8 pad_30C[4];
    Ent_8023FCC0 ents[(0xC14 - 0x310) / 0x24];
    u8 padC10[4];
    void *bank_file_handles[4];
    s32 bank_file_sizes[4];
};

extern "C" {
void *adxf_open_afs__6TLobbyFii(int, int);

s32 TLobby__sub_8023FFB8(Obj_8023FCC0 *self, int id);
s32 TLobby__sub_803CC4C0(void *handle);
u32 sndPushGroup(void *prj_data, u16 gid, void *samples, void *sdir, void *pool);

u8 is_ready__6TLobbyFPv(void *arg0) {
    return (u8) (*(s32 *)((s8 *)arg0 + 0x298) == 1);
}
void TLobby__sub_8023FCC0(Obj_8023FCC0 *self) {
    s32 i;
    s32 j;
    s32 pos;
    s32 active;
    s32 done;
    s32 errors;
    s32 id;
    s32 file;
    u16 crc;
    if (self->route == NULL) {
        return;
    }
    self->load_state = 2;
    pos = self->route_pos;
    if (pos >= 0 && self->route[pos] == -1) {
        return;
    }
    if (pos == -1) {
        self->route_pos = 0;
        TLobby__sub_8023FFB8(self, self->route[self->route_pos]);
        return;
    }
    errors = 0;
    done = 0;
    active = 0;
    if (pos >= 0) {
        for (i = 0; i < 4; i++) {
            if (self->bank_file_handles[i] != NULL) {
                active++;
                switch (TLobby__sub_803CC4C0(self->bank_file_handles[i])) {
                case 2:
                case 1:
                    break;
                case 3:
                    done++;
                    break;
                case 4:
                default:
                    TLobby::flush_checked_reads();
                    errors++;
                    break;
                }
            }
        }
    }
    if (errors == 0 && active != 0 && active == done) {
    for (j = 0; j < 4; j++) {
        if (self->bank_file_handles[j] != NULL) {
            ((TLobby *)self->bank_file_handles[j])->close_adxf_handle();
            self->bank_file_handles[j] = NULL;
        }
    }
    TLobby::clear_player_slot_tables(-1);
    id = self->route[self->route_pos];
    for (i = 0; i < 4; i++) {
        file = self->ents[id].k[i];
        crc = calculate_crc16_ccitt((const u8 *)self->ents[id].h[i], sound_bank_file_sizes[file]);
        if (crc != sound_bank_file_crc16[file]) {
            return;
        }
    }
    sndPushGroup((void *)self->ents[id].h[0], sound_bank_group_ids[id], (void *)self->ents[id].h[3],
                 lbl_80517E44[self->ents[id].k[2] / 4], (void *)self->ents[id].h[1]);
    self->stack[self->depth] = id;
    self->depth++;
    if (self->ents[id].h[3] != 0) {
        xfree((void *)self->ents[id].h[3]);
        self->ents[id].h[3] = 0;
    }
    self->route_pos++;
    if (self->route[self->route_pos] >= 0) {
        TLobby__sub_8023FFB8(self, self->route[self->route_pos]);
        return;
    }
    self->group_state = self->next_group_state;
    self->route = NULL;
    self->route_pos = -1;
    self->load_state = 1;
    }
}

void reset_sound_group_fade__6TLobbyFv(void) {
    s32 i;
    for (i = 0; i < 0x20; i++) {
        lbl_805162EC[i].extra = -0x100;
    }
}
void fade_voice_channels__6TLobbyFi(s32 arg0) {
    s32 i;
    for (i = 0; i < 0x20; i++) {
        ((void (*)(void*, s32))start_voice_fade)(&lbl_805162EC[i], arg0);
    }
}
s32 TLobby__sub_8023FFB8(Obj_8023FCC0 *self, int id) {
    s32 i;
    s32 ret;
    if (self->ents[id].h[3] != 0) {
        xfree((void *)self->ents[id].h[3]);
        self->ents[id].h[3] = 0;
    }
    if (self->ents[id].h[2] != 0) {
        xfree((void *)self->ents[id].h[2]);
        self->ents[id].h[2] = 0;
    }
    if (self->ents[id].h[1] != 0) {
        xfree((void *)self->ents[id].h[1]);
        self->ents[id].h[1] = 0;
    }
    if (self->ents[id].h[0] != 0) {
        xfree((void *)self->ents[id].h[0]);
        self->ents[id].h[0] = 0;
    }
    for (i = 0; i < 4; i++) {
        self->bank_file_sizes[i] = sound_bank_file_sizes[sound_bank_file_indices[id][i]];
        self->bank_file_sizes[i] = (self->bank_file_sizes[i] + 0x7FF) & ~0x7FF;
        self->ents[id].h[i] = (u32)xmalloc(self->bank_file_sizes[i]);
        if (self->ents[id].h[i] == 0) {
            ret = 3;
            goto fail;
        }
        self->ents[id].k[i] = sound_bank_file_indices[id][i];
        self->bank_file_handles[i] = adxf_open_afs__6TLobbyFii(0, sound_bank_file_indices[id][i]);
        if (self->bank_file_handles[i] == NULL) {
            ret = 2;
            goto fail;
        }
    }
    for (i = 0; i < 4; i++) {
        TLobby::read_checked_align((s32)self->bank_file_handles[i], (s32)(self->bank_file_sizes[i] / 2048), (s32)self->ents[id].h[i]);
        ((TLobby *)(&self->bank_file_handles[i]))->set_entry_params(i, self->bank_file_sizes[i] / 2048, self->ents[id].h[i]);
    }
    return 0;
fail:
    if (self->ents[id].h[3] != 0) {
        xfree((void *)self->ents[id].h[3]);
        self->ents[id].h[3] = 0;
    }
    if (self->ents[id].h[2] != 0) {
        xfree((void *)self->ents[id].h[2]);
        self->ents[id].h[2] = 0;
    }
    if (self->ents[id].h[1] != 0) {
        xfree((void *)self->ents[id].h[1]);
        self->ents[id].h[1] = 0;
    }
    if (self->ents[id].h[0] != 0) {
        xfree((void *)self->ents[id].h[0]);
        self->ents[id].h[0] = 0;
    }
    return ret;
}

}


struct Slot_802405B0 { void *buf[4]; u8 pad[0x24 - 0x10]; };

struct Mgr_802405B0 {
    u8 pad0[0x288];
    s32 state;
    u8 pad28c[0x2B8 - 0x28C];
    s32 depth;
    s32 stack[(0x310 - 0x2BC) / 4];
    Slot_802405B0 slots[8];
};

extern "C" {
s32 sndPopGroup();
s32 OSGetTick();
}
extern "C" {
s32 update_sound_frame(Obj_8023FCC0 *self);

int TLobby__sub_802401C8(void) { return 0; }

s32 update_sound_frame(Obj_8023FCC0 *self) {
    s32 t;
    s32 i;
    s32 j;
    s32 n;
    t = OSGetTick();
    self->elapsed = t - self->tick;
    self->tick = t;
    self->ms = self->elapsed / ((*(u32 *)0x800000F8 >> 2) / 1000);
    TLobby__sub_8023FCC0(self);
    advance_rng__6TLobbyFPv(self);
    for (i = 0; i < 40; i++) {
        tick_sound_voice(&lbl_805162EC[i]);
    }
    n = 0;
    for (i = 0; i < 40; i++) {
        if (lbl_805162EC[i].state != 3 && lbl_805162EC[i].index == 6 && lbl_805162EC[i].index == 0x19) {
            n++;
        }
    }
    for (i = 0; i < 40; i++) {
        if (lbl_805162EC[i].state != 3 && !(lbl_805162EC[i].index == 6 && lbl_805162EC[i].index == 0x19)) {
            for (j = 0; j < n; j++) {
            }
        }
    }
    self->age++;
    return 0;
}

s32 reset_sound_state__6TLobbyFPv(u8 *arg0) {
    pop_sound_groups__6TLobbyFPvi(arg0, 1);
    *(s32 *)((s8 *)arg0 + 0x298) = 4;
    return 0;
}
extern "C" {
void sndAuxCallbackReverbHI(u8 reason, void *info, void *user);
void sndAuxCallbackPrepareReverbHI(void *rev);
void sndAuxCallbackChorus(u8 reason, void *info, void *user);
u32 sndAuxCallbackPrepareChorus(void *ch);
void sndSetAuxProcessingCallbacks(u8 studio, void *auxA, void *userA, u8 midiA, u32 seqIDA, void *auxB, void *userB,
                                  u8 midiB, u32 seqIDB);
s32 TLobby__sub_801E3E9C(s32 id, const char *name, void *buf, s32 size);
}

s32 init_sound_aux_effects(Obj_8023FCC0 *self) {
    s32 i;
    s32 result;
    u32 size;

    for (i = 0; i < 40; i++) {
        set_field0__6TLobbyFPvi(&lbl_805162EC[i], self);
    }
    self->tick = OSGetTick();
    self->elapsed = 0;
    self->f280 = 0;
    self->route_pos = -1;
    self->route = NULL;
    self->group_state = -1;
    self->f2BC = 0;
    self->depth = 0;
    set_mode__6TLobbyFPvi(self, 1);
    memset(lbl_80517BEC, 0, sizeof(lbl_80517BEC));
    result = TLobby__sub_801E3E9C(0, "SOUND.BIN", lbl_80517BEC, 0xA0);
    if (result != 0) {
        return 1;
    }
    self->reverb_level = 0.0f;
    self->reverb_temp_disable = 0;
    self->reverb_time = 2.0f;
    self->reverb_pre_delay = 0.1f;
    self->reverb_damping = 0.6f;
    self->reverb_coloration = 0.9f;
    self->reverb_crosstalk = 0.0f;
    self->reverb_mix = 1.0f;
    self->chorus_base_delay = 15;
    self->chorus_variation = 0;
    self->chorus_period = 500;
    sndAuxCallbackPrepareReverbHI(self);
    sndAuxCallbackPrepareChorus(self->chorus);
    sndSetAuxProcessingCallbacks(0, sndAuxCallbackReverbHI, self, 0xFF, 0, sndAuxCallbackChorus, self->chorus, 0xFF,
                                 0);
    memset(lbl_80517E44, 0, 38 * sizeof(void *));
    for (i = 0; i < 38; i++) {
        size = (sound_bank_file_sizes[sound_bank_file_indices[i][2]] + 0x7FF) & ~0x7FF;
        lbl_80517E44[i] = xmalloc(size);
        if (lbl_80517E44[i] == NULL) {
            return 3;
        }
        memset(lbl_80517E44[i], 0, size);
        void *handle = adxf_open_afs__6TLobbyFii(0, sound_bank_file_indices[i][2]);
        if (handle != NULL) {
            TLobby::read_checked_align((s32)handle, (s32)size / 2048, (s32)lbl_80517E44[i]);
            TLobby::set_read_params(&handle, (s32)size / 2048, (int)lbl_80517E44[i]);
            do {
                TLobby__sub_803382E4();
                TLobby::run_disk_error_check();
                render_tick();
            } while (TLobby__sub_803CC4C0(handle) != 3);
            TLobby::reset_read_state();
            ((TLobby *)handle)->close_adxf_handle();
        } else {
            return 2;
        }
    }
    self->load_state = 1;
    return result;
}

#define M ((Mgr_802405B0 *)p)
s32 pop_sound_groups__6TLobbyFPvi(void *p, s32 arg1) {
    s32 idx;
    s32 n;
    ((s32 (*)(int))fade_voice_channels__6TLobbyFi)(0);
    ((s32 (*)(void))reset_sound_group_fade__6TLobbyFv)();
    if (M->state == -1) {
        return 8;
    }
    if (arg1 == 0) {
        while ((n = M->depth) > 0) {
            idx = M->stack[n];
            if (idx < 4) {
                break;
            }
            sndPopGroup();
            if (M->slots[idx].buf[3] != NULL) {
                xfree(M->slots[idx].buf[3]);
                M->slots[idx].buf[3] = NULL;
            }
            if (M->slots[idx].buf[2] != NULL) {
                xfree(M->slots[idx].buf[2]);
                M->slots[idx].buf[2] = NULL;
            }
            if (M->slots[idx].buf[1] != NULL) {
                xfree(M->slots[idx].buf[1]);
                M->slots[idx].buf[1] = NULL;
            }
            if (M->slots[idx].buf[0] != NULL) {
                xfree(M->slots[idx].buf[0]);
                M->slots[idx].buf[0] = NULL;
            }
            M->depth--;
        }
        M->state = 0;
    } else {
        while ((n = M->depth) > 0) {
            idx = M->stack[n];
            sndPopGroup();
            if (M->slots[idx].buf[3] != NULL) {
                xfree(M->slots[idx].buf[3]);
                M->slots[idx].buf[3] = NULL;
            }
            if (M->slots[idx].buf[2] != NULL) {
                xfree(M->slots[idx].buf[2]);
                M->slots[idx].buf[2] = NULL;
            }
            if (M->slots[idx].buf[1] != NULL) {
                xfree(M->slots[idx].buf[1]);
                M->slots[idx].buf[1] = NULL;
            }
            if (M->slots[idx].buf[0] != NULL) {
                xfree(M->slots[idx].buf[0]);
                M->slots[idx].buf[0] = NULL;
            }
            M->depth--;
        }
        M->state = -1;
    }
    return 0;
}
#undef M

#pragma push

#pragma fp_contract on
s32 sndVolume(s32, s32, s32);

s32 validate_and_set_selection__6TLobbyFPvi(void *arg0, s32 arg1) {
    if ((arg1 < 0) || (arg1 >= 0x16)) {
        return 4;
    }
    if ((arg1 != 0) && ((s32) *(s32 *)((s8 *)arg0 + 0x288) == -1)) {
        return 8;
    }
    if ((s32) *(s32 *)((s8 *)arg0 + 0x288) > 0) {
        pop_sound_groups__6TLobbyFPvi(arg0, 0);
    }
    sndVolume(0x7F, 0, 0xFF);
    if ((s32) *(s32 *)((s8 *)arg0 + 0x298) != 1) {
        return 9;
    }
    *(s32 *)((s8 *)arg0 + 0x2B0) = -1;
    *(s32 *)((s8 *)arg0 + 0x2B4) = (s32) sound_bank_load_routes[arg1];
    *(s32 *)((s8 *)arg0 + 0x29C) = arg1;
    return 0;
}

#pragma pop


void *TLobby__sub_80240808(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 *)((s8 *)arg0 + 0x294) = 0;
        *(s32 *)((s8 *)arg0 + 0x290) = 0;
        *(s32 *)((s8 *)arg0 + 0x288) = -1;
        if (arg1 > 0) {
            ::operator delete(arg0);
        }
    }
    return arg0;
}

void reset_sound_owner_state(u8 *arg0) {
    *(s32 *)((s8 *)arg0 + 0x2BC) = 0;
    *(s32 *)((s8 *)arg0 + 0x2B8) = 0;
    *(s32 *)((s8 *)arg0 + 0x294) = 0;
    *(s32 *)((s8 *)arg0 + 0x290) = 0;
    *(s32 *)((s8 *)arg0 + 0x284) = 0;
    *(s32 *)((s8 *)arg0 + 0x288) = -1;
    *(s32 *)((s8 *)arg0 + 0x298) = 0;
    *(s32 *)((s8 *)arg0 + 0x2B0) = -1;
    *(s32 *)((s8 *)arg0 + 0x2B4) = 0;
    *(s32 *)((s8 *)arg0 + 0x2A8) = 0;
    *(f32 *)((s8 *)arg0 + 0x2A4) = 4.0f;
    *(s32 *)((s8 *)arg0 + 0x2AC) = 0x1E240;
}
}

u16 calculate_crc16_ccitt(const u8* bytes, s32 count) {
    u16 crc = 0;
    while (count-- > 0) {
        crc = update_crc16_ccitt__6TLobbyFUsUc(crc, *bytes);
        ++bytes;
    }
    return crc;
}

u16 update_crc16_ccitt__6TLobbyFUsUc(u16 crc, u8 c) {
    s32 i;
    u32 r = crc;
    r ^= c << 8;
    for (i = 0; i < 8; i++) {
        r <<= 1;
        if (r & 0x10000) {
            r ^= 0x1021;
        }
    }
    return r;
}

void construct_global_array_a0__6TLobbyFv(void) {
    __construct_array(lbl_805162EC, (void *)TLobby__sub_8024218C, (void *)TLobby__sub_80242148, 0xA0, 0x28);
    __register_global_object(0, (void *)TLobby__sub_80240974, lbl_805162E0);
}

void TLobby__sub_80240974(void) {
    __destroy_arr(lbl_805162EC, (void *)TLobby__sub_80242148, 0xa0, 0x28);
}

void set_field0__6TLobbyFPvi(void* p, s32 v) { *(s32*)((char*)p + 0x0) = v; }

extern const f32 TLobby__data_805DC9E0;
extern const f32 lbl_805DC9E4;
extern f32 lbl_805DC9E8;

void clamp_field9c__6TLobbyFPvf(void *arg0, f32 farg0) {
    f32 var_f1;

    var_f1 = farg0;
    if (var_f1 < TLobby__data_805DC9E0) {
        *(f32 *)((s8 *)arg0 + 0x9C) = (f32) lbl_805DC9E4;
        return;
    }
    if (var_f1 > lbl_805DC9E8) {
        var_f1 = lbl_805DC9E8;
    }
    *(f32 *)((s8 *)arg0 + 0x9C) = var_f1;
}

void TLobby__sub_802409E4(void* p) { *(s16*)((char*)p + 0x92) = 5; }

extern "C" s32 sndFXCtrl14(u32 vid, u8 ctrl, u16 value);

void TLobby__sub_802409F0(SoundRequestVoice *v) {
    switch (v->kind) {
    case 0:
        if (v->previousPitch != v->pitch) {
            sndFXCtrl14(v->token, 0x80, v->pitch);
            v->previousPitch = v->pitch;
        }
        break;
    }
}

void update__6TLobbyFPv(void *arg0) {
    s32 temp_r0;
    s32 temp_r4;

    if ((u32) (*(s32 *)((s8 *)arg0 + 0x80) + 0x77780000) == 0x8888U) {
        *(s32 *)((s8 *)arg0 + 0x84) = 0;
        *(s32 *)((s8 *)arg0 + 0x80) = 0;
        *(s32 *)((s8 *)arg0 + 0x78) = (s32) *(s32 *)((s8 *)arg0 + 0x7C);
    }
    temp_r4 = *(s32 *)((s8 *)arg0 + 0x80);
    if (temp_r4 > 0) {
        temp_r0 = *(s32 *)((s8 *)arg0 + 0x84);
        if (temp_r0 <= 0) {
            *(s32 *)((s8 *)arg0 + 0x84) = 0;
            *(s32 *)((s8 *)arg0 + 0x80) = 0;
            *(s32 *)((s8 *)arg0 + 0x78) = (s32) *(s32 *)((s8 *)arg0 + 0x7C);
        } else {
            *(s32 *)((s8 *)arg0 + 0x78) = (s32) ((s32) (*(s32 *)((s8 *)arg0 + 0x7C) * (temp_r4 - temp_r0)) / temp_r4);
            *(s32 *)((s8 *)arg0 + 0x84) = (s32) (*(s32 *)((s8 *)arg0 + 0x84) - ((s32 (*)(s32))get_field_308__6TLobbyFPv)(*(s32 *)((s8 *)arg0 + 0)));
        }
    }
    *(s32 *)((s8 *)arg0 + 0x64) = (s32) (*(s32 *)((s8 *)arg0 + 0x6C) + *(s32 *)((s8 *)arg0 + 0x70) + *(s32 *)((s8 *)arg0 + 0x78));
    *(s32 *)((s8 *)arg0 + 0x64) = (s32) (*(s32 *)((s8 *)arg0 + 0x64) + 0x2000);
    if ((s32) *(s32 *)((s8 *)arg0 + 0x64) < 0) {
        *(s32 *)((s8 *)arg0 + 0x64) = 0;
    }
    if ((s32) *(s32 *)((s8 *)arg0 + 0x64) > 0x3FFF) {
        *(s32 *)((s8 *)arg0 + 0x64) = 0x3FFF;
    }
}

#undef lbl_805162EC
#pragma push


struct Voice_80241FD8 {
    u32 pad0; s32 state; u32 pad1; s32 kind; u8 pad2[0x20 - 0x10]; s32 token;
    u8 pad3[0x48 - 0x24]; s32 fade; s32 fadeStep;
};

struct Ctl_80240B64 {
    u8 type;
    s16 value;
};

struct Params_80240B64 {
    u8 count;
    Ctl_80240B64 *ctl;
};

struct Owner_80241798 { u8 pad[0x288]; u32 field_288; };

struct Sound_80241798 {
    Owner_80241798 *owner;
    u8 pad4[0x4];
    s32 flags;
    u8 padC[0x4];
    s32 group;
    s32 id;
    u8 pad18[0x58];
    s32 pitch;
    s32 velocity;
    u8 pad78[0x14];
    s16 field_8C;
};

extern "C" {
s32 sndFXCtrl(int, int, int);
s32 sndFXKeyOff(int);
s32 OSDisableInterrupts(void);
s32 OSRestoreInterrupts(s32);
void TLobby__sub_80240F3C(SoundRequestVoice *);
void calc_sound_spatial_params(SoundRequestVoice *);
u32 sndFXStartParaInfo(u16, u8, u8, u8, Params_80240B64 *);
u32 sndFXCheck(u32);
extern s8 TLobby__data_805434A8[];
extern s32 TLobby__lobby_state_flags;
void TLobby__sub_80241798(Sound_80241798 *arg0);
}
void send_voice_controller_updates(u8 *arg0);

s32 set_voice_pitch_slide(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_r5;
    var_r5 = arg2;
    if (var_r5 <= 0) {
        var_r5 = 0x88888888;
    }
    *(s32 *)((s8 *)arg0 + 0x7C) = arg1;
    *(s32 *)((s8 *)arg0 + 0x80) = var_r5;
    *(s32 *)((s8 *)arg0 + 0x84) = var_r5;
    return 0;
}

s32 tick_sound_voice(SoundRequestVoice *v) {
    Params_80240B64 params;
    Ctl_80240B64 ctl[6];
    s32 level;
    s32 fade;
    s32 step;
    switch (v->kind) {
    case 0:
    switch (v->state) {
    case -1:
        v->age++;
        v->effect = ((s32 (*)(SoundRequestOwner*, s32, s32, s32))resolve_sound_effect_bank)(v->owner, v->kind, v->bank, v->index);
        if (v->effect < 0) {
            v->state = 0;
            return 0;
        }
        if (v->delay != 0) {
            v->delay--;
            break;
        }
        ((void (*)(SoundRequestVoice *))TLobby__sub_80241A0C)(v);
        TLobby__sub_80241798((Sound_80241798 *)(v));
    start:
        ((void (*)(SoundRequestVoice *))TLobby__sub_80240F38)(v);
        TLobby__sub_80240F3C(v);
        calc_sound_spatial_params(v);
        clamp_params__6TLobbyFPv(v);
        update__6TLobbyFPv(v);
        params.count = 1;
        params.ctl = ctl;
        ctl[0].type = 0x80;
        ctl[0].value = v->pitch;
        if (!(TLobby__lobby_state_flags & 2) && TLobby__data_805434A8[7] == 0) {
            level = OSDisableInterrupts();
        }
        v->token = sndFXStartParaInfo(v->effect, 0x7F, v->pan, v->studio, &params);
        send_voice_controller_updates((u8 *)v);
        if (!(TLobby__lobby_state_flags & 2) && TLobby__data_805434A8[7] == 0) {
            OSRestoreInterrupts(level);
        }
        send_sound_request_reverb((SoundRequestVoice *)(v));
        v->state = 1;
        break;
    case 0:
        break;
    case 1:
        if (v->flags & 0x80) {
            v->pitchMoving += v->pitchVelocity;
            if (v->pitchVelocity > 0) {
                if (v->pitchMoving > v->pitchLimit) {
                    v->pitchVelocity = -v->pitchVelocity;
                }
            } else if (v->pitchMoving < -v->pitchLimit) {
                v->pitchVelocity = -v->pitchVelocity;
            }
        }
        v->age++;
        fade = v->fade;
        if (fade <= -0x7F) {
            sndFXKeyOff(v->token);
            v->state = 0;
            break;
        }
        step = v->fadeStep;
        if (step != 0) {
            v->fade = fade - step;
        }
        if (v->flags & 1) {
            if (v->refresh >= 5) {
                calc_sound_spatial_params(v);
            }
        } else {
            calc_sound_spatial_params(v);
        }
        v->refresh--;
        send_sound_request_reverb((SoundRequestVoice *)(v));
        clamp_params__6TLobbyFPv(v);
        update__6TLobbyFPv(v);
        if (sndFXCheck(v->token) == 0xFFFFFFFF) {
            if ((v->flags & 1) && v->refresh >= 0) {
                sndFXKeyOff(v->token);
                v->previousPan = v->previousSurround = v->previousVolume = 0x88888888;
                goto start;
            }
            v->state = 0;
        } else {
            send_voice_controller_updates((u8 *)v);
            TLobby__sub_802409F0(v);
            if ((v->flags & 1) && v->refresh < 0) {
                sndFXKeyOff(v->token);
                v->state = 0;
            }
        }
        break;
    }
        break;
    }
    return 0;
}

void update_random_flip_flag__6TLobbyFPv(u8 *arg0) {
    switch (*(s32 *)((s8 *)arg0 + 0x10)) {
    case 0:
        switch (*(s32 *)((s8 *)arg0 + 0x14)) {
        case 0: case 1: case 2: case 3: case 4:
        case 7: case 8: case 9:
        case 21:
        case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31:
            *(s32 *)((s8 *)arg0 + 8) |= 0x100;
            break;
        }
        break;
    }
    if (*(s32 *)((s8 *)arg0 + 8) & 0x100) {
        *(s16 *)((s8 *)arg0 + 0x90) = (s16)(((u32 (*)(void*))advance_rng__6TLobbyFPv)(*(void **)((s8 *)arg0 + 0)) & 1);
    }
}

void TLobby__sub_80240F38(void) {  }

void TLobby__sub_80240F3C(SoundRequestVoice *v) {
    s32 num = 1;
    s32 den = 1;
    s32 extra = 0;
    switch (v->bank) {
    case 0:
        switch (v->index) {
        case 0: case 1: case 2: case 3: case 4:
        case 7: case 9:
        case 18: case 21:
        case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31:
            v->flags |= 0x40;
            break;
        }
        break;
    case 3:
        switch (((Owner_80241798 *)v->owner)->field_288) {
        case 2:
            switch (v->index) {
            case 12:
                den = 1;
                v->flags |= 0x40;
                break;
            case 1: case 24:
                den = 4;
                v->flags |= 0x40;
                break;
            }
            break;
        case 8:
            switch (v->index) {
            case 31:
                v->flags |= 0x40;
                break;
            }
            break;
        case 12:
            switch (v->index) {
            case 33: case 43: case 64: case 65:
                v->flags |= 0x40;
                break;
            }
            break;
        case 16:
            switch (v->index) {
            case 17: case 51: case 52:
                v->flags |= 0x40;
                break;
            }
            break;
        }
        switch (((Owner_80241798 *)v->owner)->field_288) {
        case 2:
            switch (v->index) {
            case 13:
                v->flags |= 0x40;
                break;
            case 36:
                den = 2;
                v->flags |= 0x40;
                break;
            case 47:
                den = 6;
                extra = 0x1C00;
                v->flags |= 0x40;
                break;
            }
            break;
        case 10:
            switch (v->index) {
            case 1:
                den = 4;
                v->flags |= 0x40;
                break;
            case 13:
                den = 2;
                v->flags |= 0x40;
                break;
            case 32:
                den = 3;
                v->flags |= 0x40;
                break;
            case 34:
                v->flags |= 0x40;
                break;
            case 41:
                num = 2;
                v->flags |= 0x40;
                break;
            }
            break;
        case 11:
            switch (v->index) {
            case 1:
                den = 4;
                v->flags |= 0x40;
                break;
            case 13:
                den = 2;
                v->flags |= 0x40;
                break;
            case 32:
                den = 3;
                v->flags |= 0x40;
                break;
            case 34:
                v->flags |= 0x40;
                break;
            case 41:
                num = 2;
                v->flags |= 0x40;
                break;
            }
            break;
        case 14:
            switch (v->index) {
            case 1:
                den = 1;
                v->flags |= 0x40;
                break;
            case 2:
                v->flags |= 0x40;
                break;
            case 10:
                den = 4;
                v->flags |= 0x40;
                break;
            case 22:
                v->flags |= 0x40;
                break;
            case 36:
                den = 3;
                v->flags |= 0x40;
                break;
            case 42:
                den = 2;
                v->flags |= 0x40;
                break;
            case 54:
                den = 6;
                v->flags |= 0x40;
                break;
            case 57:
                v->flags |= 0x40;
                break;
            case 64:
                num = 2;
                v->flags |= 0x40;
                break;
            }
            break;
        case 15:
            switch (v->index) {
            case 3: case 15:
                num = 2;
                v->flags |= 0x40;
                break;
            case 17:
                den = 4;
                v->flags |= 0x40;
                break;
            case 37: case 38:
                v->flags |= 0x40;
                break;
            case 16:
                break;
            }
            break;
        case 19:
            switch (v->index) {
            case 2: case 8: case 22:
                num = 2;
                v->flags |= 0x40;
                break;
            case 15:
                v->flags |= 0x40;
                break;
            case 27: case 28:
                num = 2;
                v->flags |= 0x40;
                break;
            }
            break;
        case 4:
            switch (v->index) {
            case 11: case 19:
                den = 3;
                v->flags |= 0x40;
                break;
            case 13: case 51: case 52:
                v->flags |= 0x40;
                break;
            case 12:
                break;
            }
            break;
        case 5:
            switch (v->index) {
            case 1: case 6:
                num = 2;
                v->flags |= 0x40;
                break;
            }
            break;
        case 6:
            switch (v->index) {
            case 3: case 15: case 24:
                num = 2;
                v->flags |= 0x40;
                break;
            }
            break;
        case 7:
            switch (v->index) {
            case 31:
                num = 2;
                v->flags |= 0x40;
                break;
            }
            break;
        case 8:
            switch (v->index) {
            case 38: case 45: case 50: case 51:
                num = 2;
                v->flags |= 0x40;
                break;
            case 63:
                den = 12;
                v->flags |= 0x40;
                break;
            }
            break;
        case 9:
            switch (v->index) {
            case 34:
                num = 2;
                v->flags |= 0x40;
                break;
            }
            break;
        case 18:
            switch (v->index) {
            case 13: case 14:
                v->flags |= 0x40;
                break;
            }
            break;
        case 12:
            switch (v->index) {
            case 2: case 12: case 19: case 21: case 40: case 48: case 57:
                num = 2;
                v->flags |= 0x40;
                break;
            }
            break;
        case 16:
            switch (v->index) {
            case 2: case 3: case 37: case 39: case 45:
                num = 2;
                v->flags |= 0x40;
                break;
            case 38:
                break;
            }
            break;
        case 20:
            switch (v->index) {
            case 5: case 28: case 62:
                num = 2;
                v->flags |= 0x40;
                break;
            }
            break;
        }
        break;
    case 6:
        switch (((Owner_80241798 *)v->owner)->field_288) {
        case 17:
            switch (v->index) {
            case 22: case 30: case 31:
                num = 2;
                v->flags |= 0x40;
                break;
            }
            break;
        }
        break;
    }
    if (v->flags & 0x40) {
        v->pitchMoving = num * ((s32)((advance_rng__6TLobbyFPv(v->owner) >> 16) & 0x3F00) - 0x2000 + extra) / den;
    }
}

void TLobby__sub_80241798(Sound_80241798 *arg0) {
    s32 num = 1;
    s32 den = 1;
    s32 mask = 0;
    s32 min = 0;
    switch (arg0->owner->field_288) {
    case 16:
        switch (arg0->group) {
        case 4:
            switch (arg0->id) {
            case 5: case 6: case 7: case 8: case 9:
                mask = 0x3F;
                min = 0x40;
                arg0->flags |= 0x80;
                break;
            }
            break;
        }
        break;
    case 2:
        switch (arg0->group) {
        case 4:
            switch (arg0->id) {
            case 6:
                mask = 0x3F;
                min = 0x20;
                arg0->flags |= 0x80;
                break;
            }
            break;
        }
        break;
    case 9:
        switch (arg0->group) {
        case 3:
            switch (arg0->id) {
            case 0: case 1:
                mask = 0x3F;
                min = 0x80;
                arg0->flags |= 0x80;
                break;
            }
            break;
        }
        break;
    case 12:
        switch (arg0->group) {
        case 4:
            switch (arg0->id) {
            case 11:
                mask = 0x3F;
                min = 0x20;
                arg0->flags |= 0x80;
                break;
            case 12: case 13:
                mask = 0x3F;
                min = 0x60;
                arg0->flags |= 0x80;
                break;
            }
            break;
        case 3:
            switch (arg0->id) {
            case 20:
                den = 6;
                mask = 0x3F;
                min = 0x20;
                arg0->flags |= 0x80;
                arg0->field_8C = 0x1000;
                break;
            }
            break;
        }
        break;
    case 13:
        switch (arg0->group) {
        case 3:
            switch (arg0->id) {
            case 5:
                num = 2;
                mask = 0x3F;
                min = 0xC0;
                arg0->flags |= 0x80;
                break;
            case 21: case 22:
                mask = 0x3F;
                min = 0x40;
                arg0->flags |= 0x80;
                break;
            }
            break;
        }
        break;
    }
    if (arg0->flags & 0x80) {
        arg0->pitch = num * ((s32)((((u32 (*)(void*))advance_rng__6TLobbyFPv)(arg0->owner) >> 16) & 0x3FFF) - 0x2000) / den;
        arg0->velocity = min + (mask & ((u32 (*)(void*))advance_rng__6TLobbyFPv)(arg0->owner));
        if ((s32)(((u32 (*)(void*))advance_rng__6TLobbyFPv)(arg0->owner) & 0x3F) < 0x20) {
            arg0->velocity = -arg0->velocity;
        }
    }
}

void TLobby__sub_80241A0C(void) {  }

extern const f32 lbl_805DC9EC;

void send_sound_request_reverb(SoundRequestVoice *voice) {
    f32 request = voice->reverb;
    s32 amount;
    if (request < TLobby__data_805DC9E0) {
        if (voice->bank == 5 || (voice->flags & 0x10)) amount = 0;
        else amount = s32(lbl_805DC9EC * voice->owner->reverb);
    } else amount = s32(lbl_805DC9EC * request);
    if (voice->bank == 6) {
        switch (voice->index) {
        case 12:
        case 25:
            return;
        default:
            break;
        }
    }
    if (voice->previousReverb != u8(amount))
        sndFXCtrl(voice->token, 91, amount);
}

void send_voice_controller_updates(u8 *arg0) {
    switch ((s32) *(s32 *)((s8 *)arg0 + 0xC)) {
    case 0:
    if ((*(s32 *)((s8 *)arg0 + 0x24)) != (s32) *(s32 *)((s8 *)arg0 + 0x28)) {
        *(s32 *)((s8 *)arg0 + 0x24) = *(s32 *)((s8 *)arg0 + 0x28);
        sndFXCtrl((int) (*(s32 *)((s8 *)arg0 + 0x20)), 7, (int) ((u8) *(s32 *)((s8 *)arg0 + 0x28)));
    }
    if ((*(s32 *)((s8 *)arg0 + 0x2C)) != (s32) *(s32 *)((s8 *)arg0 + 0x30)) {
        *(s32 *)((s8 *)arg0 + 0x2C) = *(s32 *)((s8 *)arg0 + 0x30);
        sndFXCtrl((int) (*(s32 *)((s8 *)arg0 + 0x20)), 0xA, (int) ((u8) *(s32 *)((s8 *)arg0 + 0x30)));
    }
    if ((s32) *(s32 *)((s8 *)arg0 + 0x10) == 5) {
        sndFXCtrl((int) (*(s32 *)((s8 *)arg0 + 0x20)), 0x83, (int) (0U));
        return;
    }
    if ((*(s32 *)((s8 *)arg0 + 0x34)) != (s32) *(s32 *)((s8 *)arg0 + 0x38)) {
        *(s32 *)((s8 *)arg0 + 0x34) = *(s32 *)((s8 *)arg0 + 0x38);
        sndFXCtrl((int) (*(s32 *)((s8 *)arg0 + 0x20)), 0x83, (int) ((u8) *(s32 *)((s8 *)arg0 + 0x38)));
    }
        break;
    }
}

void clamp_params__6TLobbyFPv(void *arg0) {
    *(s32 *)((s8 *)arg0 + 0x28) = (((*(s32 *)((s8 *)arg0 + 0x48) + *(s32 *)((s8 *)arg0 + 0x40)) + *(s32 *)((s8 *)arg0 + 0x3C)) + *(s32 *)((s8 *)arg0 + 0x44)) + 0x7F;
    *(s32 *)((s8 *)arg0 + 0x30) = (s32) (0x40 - (*(s32 *)((s8 *)arg0 + 0x50) + *(s32 *)((s8 *)arg0 + 0x54)));
    *(s32 *)((s8 *)arg0 + 0x38) = (s32) ((*(s32 *)((s8 *)arg0 + 0x58) + *(s32 *)((s8 *)arg0 + 0x60)) + 0x40);
    *(s32 *)((s8 *)arg0 + 0x28) = (s32) (*(s32 *)((s8 *)arg0 + 0x28) + *(s32 *)((s8 *)(*(void **)((s8 *)arg0 + 0)) + 0x280));
    if ((s32) *(s32 *)((s8 *)arg0 + 0x28) < 0) {
        *(s32 *)((s8 *)arg0 + 0x28) = 0;
    }
    if ((s32) *(s32 *)((s8 *)arg0 + 0x28) > 0x7F) {
        *(s32 *)((s8 *)arg0 + 0x28) = 0x7F;
    }
    if ((s32) *(s32 *)((s8 *)arg0 + 0x30) < 0) {
        *(s32 *)((s8 *)arg0 + 0x30) = 0;
    }
    if ((s32) *(s32 *)((s8 *)arg0 + 0x30) > 0x7F) {
        *(s32 *)((s8 *)arg0 + 0x30) = 0x7F;
    }
    if ((s32) *(s32 *)((s8 *)arg0 + 0x38) < 0) {
        *(s32 *)((s8 *)arg0 + 0x38) = 0;
    }
    if ((s32) *(s32 *)((s8 *)arg0 + 0x38) > 0x7F) {
        *(s32 *)((s8 *)arg0 + 0x38) = 0x7F;
    }
}

s32 start_voice_fade(struct Voice_80241FD8 *v, s32 step) {
    switch (v->kind) {
    case 0:
        if (v->fadeStep == 0) {
            if (step != 0) {
                v->fadeStep = step;
                v->fade = -step;
            } else {
                if (step == 0 && v->state == 1) {
                    sndFXKeyOff(v->token);
                }
                v->state = 0;
            }
        }
        break;
    }
    return 0;
}

#pragma push
#pragma fp_contract on
s32 init_sound_voice__6TLobbyFPviiii(void *lobby, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    *(s32 *)((s8 *)lobby + 4) = 0;
    *(s32 *)((s8 *)lobby + 8) = arg4;
    *(s32 *)((s8 *)lobby + 0xC) = arg1;
    *(s32 *)((s8 *)lobby + 0x10) = arg2;
    *(s32 *)((s8 *)lobby + 0x14) = arg3;
    *(s32 *)((s8 *)lobby + 0x1C) = 0;
    *(s32 *)((s8 *)lobby + 0x20) = 0;
    *(s32 *)((s8 *)lobby + 0x28) = 0x7F;
    *(s32 *)((s8 *)lobby + 0x24) = 0x88888888;
    *(s32 *)((s8 *)lobby + 0x30) = 0x40;
    *(s32 *)((s8 *)lobby + 0x2C) = 0x88888888;
    *(s32 *)((s8 *)lobby + 0x38) = 0;
    *(s32 *)((s8 *)lobby + 0x34) = 0x88888888;
    *(s32 *)((s8 *)lobby + 0x3C) = 0;
    *(s32 *)((s8 *)lobby + 0x40) = 0;
    *(s32 *)((s8 *)lobby + 0x44) = 0;
    *(s32 *)((s8 *)lobby + 0x48) = 0;
    *(s32 *)((s8 *)lobby + 0x4C) = 0;
    *(s32 *)((s8 *)lobby + 0x50) = 0;
    *(s32 *)((s8 *)lobby + 0x54) = 0;
    *(s32 *)((s8 *)lobby + 0x58) = 0;
    *(s32 *)((s8 *)lobby + 0x60) = 0;
    *(s32 *)((s8 *)lobby + 0x64) = 0;
    *(s32 *)((s8 *)lobby + 0x68) = 0x88888888;
    *(s32 *)((s8 *)lobby + 0x6C) = 0;
    *(s32 *)((s8 *)lobby + 0x70) = 0;
    *(s32 *)((s8 *)lobby + 0x74) = 0;
    *(s32 *)((s8 *)lobby + 0x78) = 0;
    *(s32 *)((s8 *)lobby + 0x7C) = 0;
    *(s32 *)((s8 *)lobby + 0x80) = 0;
    *(s32 *)((s8 *)lobby + 0x84) = 0;
    *(s16 *)((s8 *)lobby + 0x8C) = 0x3F00;
    *(s32 *)((s8 *)lobby + 0x98) = 0;
    *(s16 *)((s8 *)lobby + 0x90) = 0;
    *(s16 *)((s8 *)lobby + 0x92) = 0;
    *(s32 *)((s8 *)lobby + 0x94) = 0;
    *(f32 *)((s8 *)lobby + 0x9C) = (f32) lbl_805DC9E4;
    *(s32 *)((s8 *)lobby + 0x88) = 0;
    switch (*(s32 *)((s8 *)lobby + 0xC)) {
    case 0:
        *(s32 *)((s8 *)lobby + 4) = -1;
        update_random_flip_flag__6TLobbyFPv((u8 *)lobby);
        break;
    }
    return 0;
}
#pragma pop

#pragma pop

#pragma push

struct RecoveredGlobal_8024259C_TLobby__data_8050AAAC {
    s32 value;
    u8 remaining[0x24];
};

typedef struct Tag_802421C4 { s32 a; s32 b; } Tag_802421C4;

#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
struct Pair_80242380 {
    u8 c[8];
};

struct Ext_80242380 {
    u8 bytes[0x64];
};

typedef struct Entry_80242380 {
    s32 id;
    s32 f4;
    char name[0x11];
    char s19[0x11];
    char s2A[0x11];
    char s3B[0x11];
    Pair_80242380 f4C;
    s32 f54;
    Ext_80242380 ext;
} Entry_80242380;

extern "C" {
s32 seq_jump__9TProtocolFPUcR21TPlyMeetUserExtension(int, void *, void *);
extern RecoveredGlobal_8024259C_TLobby__data_8050AAAC TLobby__data_8050AAAC;
extern u32 TLobby__protocol_instance;
char *get_shared_text_buffer();
void text_builder_append(char *);
}
void text_builder_reset();
extern "C" {
s32 send_find_user__9TProtocolFR16TPlyGuildCardTagUl(void *, Tag_802421C4 *, s32);
extern unsigned char lbl_80517F9C[];
void __copy(void *, void *, int);
Entry_80242380 *copy_com_card_entry__6TLobbyFPvPv(Entry_80242380 *dst, Entry_80242380 *src);
int TLobby__sub_8024273C(void*);

void *TLobby__sub_80242148(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 *)((s8 *)arg0 + 4) = 0;
        if (arg1 > 0) {
            ::operator delete(arg0);
        }
    }
    return arg0;
}
void TLobby__sub_8024218C(void* p) { *(s32*)((char*)p + 0x0) = 0; *(s32*)((char*)p + 0x4) = 0; }
s32 get_field_308__6TLobbyFPv(void* p) { return *(s32*)((char*)p + 0x308); }
int forward_8024273C__6TLobbyFPv(void* p) { return TLobby__sub_8024273C(p); }

void send_find_user_self_tag__6TLobbyFi(s32 arg0) {
    if ((u32) TLobby__protocol_instance != 0U) {
        Tag_802421C4 tag = *(Tag_802421C4 *)((u8 *)TLobby__protocol_instance + 0x1900);
        send_find_user__9TProtocolFR16TPlyGuildCardTagUl((void *)TLobby__protocol_instance, &tag, arg0);
    }
}

typedef struct Entry_8024220C Entry_8024220C;
typedef struct Src_8024220C Src_8024220C;
void load_selected_guild_card_record(Src_8024220C *arg0) {
  char *new_var;
  void *p;
  (*(Entry_8024220C *)&selected_guild_card_record).id = arg0->id;
  (*(Entry_8024220C *)&selected_guild_card_record).f4 = 0;
  memset((*(Entry_8024220C *)&selected_guild_card_record).name, 0, 0x11);
  strncpy((*(Entry_8024220C *)&selected_guild_card_record).name, arg0->name, 0x10);
  (*(Entry_8024220C *)&selected_guild_card_record).name[0x10] = 0;
  new_var = arg0->list;
  new_var = build_text_from_comma_list__6TLobbyFPv(new_var);
  p = new_var;
  p = ((void *)parse_csv_token__6TLobbyFPvPv((char *)(p), (char *)((*(Entry_8024220C *)&selected_guild_card_record).s19)));
  p = ((void *)parse_csv_token__6TLobbyFPvPv((char *)(p), (char *)((*(Entry_8024220C *)&selected_guild_card_record).s2A)));
  p = ((void *)parse_csv_token__6TLobbyFPvPv((char *)(p), (char *)((*(Entry_8024220C *)&selected_guild_card_record).s2A)));
  parse_csv_token__6TLobbyFPvPv((char *)(p), (char *)((*(Entry_8024220C *)&selected_guild_card_record).s3B));
  TLobby__sub_802422EC((*(Entry_8024220C *)&selected_guild_card_record).f4C, arg0->f64);
  __as__21TPlyMeetUserExtensionFRC21TPlyMeetUserExtension((*(Entry_8024220C *)&selected_guild_card_record).ext, arg0->ext);
}

void TLobby__sub_802422EC(void *arg0, void *arg1) {
    *(s32 *)((s8 *)arg0 + 0) = (s32) *(s32 *)((s8 *)arg1 + 0);
    *(s32 *)((s8 *)arg0 + 4) = (s32) *(s32 *)((s8 *)arg1 + 4);
    *(s16 *)((s8 *)arg0 + 8) = (s16) *(s16 *)((s8 *)arg1 + 8);
}

void find_and_load_com_card__6TLobbyFUi(u32 arg0) {
    s32 n;
    s32 i;
    n = ((s32 (*)(void))get_com_card_data__6TLobbyFv)();
    for (i = 0; i < n; i++) {
        get_com_card_entry__6TLobbyFi(i);
        if (arg0 == ((u32 (*)(void))TLobby__sub_802428F8)()) break;
    }
    if (i < n) {
        copy_com_card_entry__6TLobbyFPvPv((Entry_80242380 *)(selected_guild_card_record), (Entry_80242380 *)(get_com_card_entry__6TLobbyFi(i)));
    }
}

Entry_80242380 *copy_com_card_entry__6TLobbyFPvPv(Entry_80242380 *dst, Entry_80242380 *src) {
    dst->id = src->id;
    dst->f4 = src->f4;
    __copy(dst->name, src->name, 0x11);
    __copy(dst->s19, src->s19, 0x11);
    __copy(dst->s2A, src->s2A, 0x11);
    __copy(dst->s3B, src->s3B, 0x11);
    dst->f4C = src->f4C;
    dst->f54 = src->f54;
    dst->ext = src->ext;
    return dst;
}

void* get_com_card_entry__6TLobbyFi(int a0) {  return (char*)lbl_80517F9C + a0 * 188; }
typedef char RecoveredGlobal_8024259C_TLobby__data_8050AAAC_size[sizeof(RecoveredGlobal_8024259C_TLobby__data_8050AAAC) == 0x28 ? 1 : -1];

char *parse_csv_token__6TLobbyFPvPv(char *src, char *dst) {
    s32 i;
    for (i = 0x10; i != 0; i--) {
        char c = *src;
        if (c == 0) break;
        src++;
        if (c == ',') break;
        *dst = c;
        dst++;
    }
    if (*src == ',') {
        src++;
    }
    *dst = 0;
    return src;
}

char *skip_to_comma_field__6TLobbyFPvii(char *s, s32 a, s32 b) {
    s32 i;
    for (i = a + 1; i < b;) {
        if (*s == '\0') return s;
        if (*s++ == ',') i++;
    }
    return s;
}

char *build_text_from_comma_list__6TLobbyFPv(char *list) {
    char buf[0x11];
    char *s;
    char *d;
    s32 i;
    s32 count;
    text_builder_reset();
    s = list;
    count = 1;
    while (*s != '\0') {
        if (*s++ == ',') {
            count++;
        }
    }
    for (i = 0; i < count; i++) {
        TWindowSubStatusDisp::append_comma();
        s = skip_to_comma_field__6TLobbyFPvii(list, i, count);
        d = buf;
        while (*s != '\0' && *s != ',') {
            *d++ = *s++;
        }
        *d = '\0';
        text_builder_append(buf);
    }
    return get_shared_text_buffer();
}

void TLobby__sub_8024259C(s32 arg0) {
    if ((u32) TLobby__protocol_instance != 0U) {
        memset((void *)&TLobby__data_8050AAAC.value, 0, 0x11);
        strncpy((void *)&TLobby__data_8050AAAC.value, (void *)(arg0 + 0x19), 0x10);
        *(s8 *)((s8 *)&TLobby__data_8050AAAC.value + 0x10) = 0;
        seq_jump__9TProtocolFPUcR21TPlyMeetUserExtension(TLobby__protocol_instance, (void *)(arg0 + 0x4C), (void *)(arg0 + 0x58));
    }
}
}

#pragma pop

struct RecoveredGlobal_802426E8_lbl_80517F9C {
    s32 value;
    u8 remaining[0x5E0];
};

struct RecoveredGlobal_8024287C_lbl_80517EE0 {
    s32 value;
    u8 remaining[0xB8];
};

struct RecoveredGlobal_8024287C_lbl_80517F9C {
    s32 value;
    u8 remaining[0x5E0];
};

extern "C" {
#define lbl_80517F9C (*(RecoveredGlobal_802426E8_lbl_80517F9C *)lbl_80517F9C)
extern int com_card_entry_count;
#define selected_guild_card_record (*(RecoveredGlobal_8024287C_lbl_80517EE0 *)selected_guild_card_record)
#define lbl_80517F9C (*(RecoveredGlobal_802426E8_lbl_80517F9C *)lbl_80517F9C)
u32 find_card_by_id__17TWindowSubComCardFUl();
int fn_80077AA4(void*);
s32 get_com_card_list__6TLobbyFPv();

extern s32 lbl_805D63D8;

void init_player_entry__6TLobbyFPvPv(u8 *arg0, u8 *arg1) {
    s32 temp_r5;
    void *p;

    *(s32 *)((s8 *)arg0 + 0) = (s32) *(s32 *)((s8 *)arg1 + 0xC);
    temp_r5 = lbl_805D63D8;
    lbl_805D63D8 = temp_r5 + 1;
    *(s32 *)((s8 *)arg0 + 4) = temp_r5;
    ((s32 (*)(void*, void*, int))TLobby__sub_802422EC)(arg0 + 0x4C, arg1 + 0x10, temp_r5);
    __as__21TPlyMeetUserExtensionFRC21TPlyMeetUserExtension(arg0 + 0x58, arg1 + 0x60);
    ((TLobby *)arg0)->get_id();
    if (find_card_by_id__17TWindowSubComCardFUl() == 0U) {
        strncpy(arg0 + 8, (void *) (((TWindowSubStatusDisp *)arg0)->get_sub_disp_ptr()), 0x10);
    } else {
        strncpy(arg0 + 8, (void *) (get_com_card_list__6TLobbyFPv()), 0x10);
    }
    *(s8 *)((s8 *)arg0 + 0x18) = 0;
    p = ((void* (*)(void*))build_text_from_comma_list__6TLobbyFPv)(arg1 + 0x1C);
    p = ((void* (*)(void*, void*))parse_csv_token__6TLobbyFPvPv)(p, arg0 + 0x19);
    p = ((void* (*)(void*, void*))parse_csv_token__6TLobbyFPvPv)(p, arg0 + 0x2A);
    p = ((void* (*)(void*, void*))parse_csv_token__6TLobbyFPvPv)(p, arg0 + 0x2A);
    ((void* (*)(void*, void*))parse_csv_token__6TLobbyFPvPv)(p, arg0 + 0x3B);
}

typedef char RecoveredGlobal_802426E8_lbl_80517F9C_size[sizeof(RecoveredGlobal_802426E8_lbl_80517F9C) == 0x5E4 ? 1 : -1];
void remove_com_card_entry__6TLobbyFi(s32 arg0) {
    u8 *lobby;
    if (arg0 < 7) {
        lobby = (u8 *)&lbl_80517F9C.value + (arg0 * 0xBC);
        ((TLobby *)lobby)->move_words((u32 *)(lobby + 0xBC), (s32)((void *) ((u32) ((7 - arg0) * 0xBC) >> 2U)));
    }
    (*(s32 *)&com_card_entry_count) -= 1;
}

int TLobby__sub_8024273C(void *p) {
    u8 *entry;
    s32 slot = remove_com_card_by_id__6TLobbyFUi(*(u32 *)((u8 *)p + 0xC));
    entry = (u8 *)&lbl_80517F9C.value;
    entry += slot * 0xBC;
    init_player_entry__6TLobbyFPvPv(entry, (u8 *)p);
    com_card_entry_count++;
    TLobby__sub_80242918();
}

s32 remove_com_card_by_id__6TLobbyFUi(u32 arg0) {
    s32 i;
    s32 n;
    n = ((s32)get_com_card_data__6TLobbyFv());
    for (i = 0; i < n; i++) {
        if (arg0 == ((u32)((TLobby *)(((void* (*)(s32))get_com_card_entry__6TLobbyFi)(i)))->get_id())) {
            remove_com_card_entry__6TLobbyFi(i);
            n -= 1;
        }
    }
    if (n < 8) {
        return n;
    }
    remove_com_card_entry__6TLobbyFi(0);
    return 7;
}

void reset_state_805D63DC__6TLobbyFv(void*) { com_card_entry_count = 0; TLobby::clear_flag_bit2(); }

void reset_state__6TLobbyFPv(void* p) { reset_state_805D63DC__6TLobbyFv(p); }
void TLobby__sub_8024285C(void* p) { reset_state_805D63DC__6TLobbyFv(p); }

typedef char RecoveredGlobal_8024287C_lbl_80517EE0_size[sizeof(RecoveredGlobal_8024287C_lbl_80517EE0) == 0xBC ? 1 : -1];
typedef char RecoveredGlobal_8024287C_lbl_80517F9C_size[sizeof(RecoveredGlobal_8024287C_lbl_80517F9C) == 0x5E4 ? 1 : -1];
void construct_entry_arrays__6TLobbyFv(void) {
    TLobby__sub_802428C4((void*)((void *) &selected_guild_card_record.value));
    ((s32 (*)(s32 *, void *(*)(void *), s32, s32, s32))__construct_array)(&(*(RecoveredGlobal_8024287C_lbl_80517F9C *)&lbl_80517F9C).value, TLobby__sub_802428C4, 0, 0xBC, 8);
}

void* TLobby__sub_802428C4(void* p) { fn_80077AA4((char*)p + 0x58); return p; }
s32 TLobby__sub_802428F8(void* p) { return *(s32*)((char*)p + 0x4); }

int get_com_card_data__6TLobbyFv(void) {  return com_card_entry_count; }

}
#undef lbl_80517F9C
#undef selected_guild_card_record
