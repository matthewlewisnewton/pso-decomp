#include "types.h"
#include "pso/misc/TLoadCtrl_80227390.h"
#include "pso/object/TObjBgmColCtrl_8017E8E4.h"
#include "pso/object/TObjBgmCol.h"
#include "pso/object/TObjBgmColCtrl.h"

struct Zone_8017E748 { u8 pad[0x9C]; s32 category; };

extern "C" {
extern s32 area_music_filename_table[];
extern s32 bgm_zone_category;
extern s32 lbl_805D5B04;
s32 is_within_distance__10TObjBgmColFf(f32);

s32 TObjBgmCol::check() {
    f32 temp_f0;

    temp_f0 = this->m_98;
    if (is_within_distance__10TObjBgmColFf(temp_f0 * temp_f0) != 0) {
        if ((s32) this->m_90 != 0) {
            this->m_90 = 0;
            return 1;
        }
        return 0;
    }
    if ((s32) this->m_90 != 0) {
        return 2;
    }
    this->m_90 = 1;
    return 3;
}
void TObjBgmCol::run_task() {
    Zone_8017E748 *zone = (Zone_8017E748 *)this;
    if (get_quest_bgm_issued_flag() == 0) {
        switch (check()) {
        case 1:
            if (bgm_zone_category != zone->category) {
                if (zone->category == 4) {
                    TObjBgmColCtrl::play_lobby_theme_music();
                } else {
                    play_area_music((char *)area_music_filename_table[zone->category]);
                }
                bgm_zone_category = zone->category;
            }
            lbl_805D5B04 = 1;
            return;
        case 0:
            lbl_805D5B04 = 1;
            break;
        case 2:
            break;
        }
    }
}

}
