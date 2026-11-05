#include "pso/audio/SoundBankTables.h"

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
