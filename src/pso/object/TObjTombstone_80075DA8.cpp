#include "types.h"
#include "pso/item/TItemData.h"
#include "pso/object/TObjTombstone.h"
#include "pso/object/TObjTombstone_80075DA8.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/system/vector.h"
#include "pso/object/TObjMotion.h"
#include "pso/object/TObjTombstone.h"
#include "pso/player/TObjPlayer.h"

struct Vec_80076098 {
    f32 x;
    f32 y;
    f32 z;
};

struct Tomb_80076098 {
    u8 pad0[0x38];
    Vec_80076098 pos;
    u8 pad44[0x234 - 0x44];
    s32 done;
};

extern "C" {
s32 is_other_tombstone_closer__13TObjTombstoneFv();
extern const f32 TObjTombstone__data_805D9174;
extern const f32 TObjTombstone__data_805D9178;
extern const f32 TObjTombstone__data_805D917C;
extern const f32 lbl_805D91B4;
extern const f32 lbl_805D91B8;
void subtract_vector(void *, void *);
f32 vector_length(void *);
s32 check_all_players_active__13TObjTombstoneFv(void *);
void *get_player_by_client_id(s32 i);
extern s32 local_client_id;
extern s32 TLobby__designated_client_id;
extern const f32 TObjTombstone__data_805D9184;
f32 get_distance_to_local_player_xz__13TObjTombstoneFPv(void *);
void TObjTombstone__sub_80075DFC(TObjTombstone *);
void __dl__7TObjectFPv(void *);
s32 check_owner__13TObjTombstoneFv();

void TObjTombstone::init_parts() { format_player_name(); format_label(); build_name_text(); format_enemy_text(); format_quoted_name(); format_date_text(); }

extern s32 tombstone_first_run_flag;
}
extern f32 TObjTombstone__base_matrix[];
extern const f32 lbl_805D91AC;
extern const f32 lbl_805D91B0;
extern TItemData lbl_8048D278[];
extern "C" s32 rand();
extern "C" f32 cos_table_lookup(s32);
extern "C" f32 sin_table_lookup(s32);
extern "C" s32 project_actor_to_ground(TObjCollidable *, Vec *, Vec *);
void drop_stacked_item(TItemData *, u16, f32 *);

#pragma push
#pragma fp_contract on
#pragma opt_propagation off
// Keep the original selection temporary live across both weighted draws.
// The generated conversion/zero pools still need shared ownership recovery.
void TObjTombstone__sub_80075DFC(TObjTombstone *self) {
    self->m_234 = 1;
    s32 count = 0;
    f32 pick = lbl_805D91AC * rand();
    f32 *weight = TObjTombstone__base_matrix;
    f32 sum = *weight;
    for (s32 i = 1; i <= 4; ++i) {
        if (0.0f != sum && pick <= sum) {
            count = i;
            break;
        }
        sum += *++weight;
    }
    if (count != 0) {
        s32 choice = 0;
        for (s32 i = 0; i < 4; ++i) {
            if (get_player_by_client_id(i) != NULL) ++choice;
        }
        if (count > choice) count = choice;
        choice = -1;
        pick = lbl_805D91AC * rand();
        weight = TObjTombstone__base_matrix + 4;
        sum = *weight;
        for (s32 i = 0; i < 6; ++i) {
            if (0.0f != sum && pick <= sum) {
                choice = i;
                break;
            }
            sum += *++weight;
        }
        if (choice != -1) {
            s32 angle = self->rotation_y - ((count - 1) * 0x2000) / 2;
            TItemData item = lbl_8048D278[choice];
            s32 dropped = 0;
            for (s32 offset = 0; offset < 0x10000; offset += 0x2000) {
                Vec position = self->position;
                position.x += lbl_805D91B0 * cos_table_lookup(angle);
                position.z += lbl_805D91B0 * sin_table_lookup(angle);
                position.y += TObjTombstone__data_805D9184;
                if (project_actor_to_ground(self, &position, 0) != 0) {
                    position.y += TObjTombstone__data_805D9184;
                    item.id = -1;
                    drop_stacked_item(&item, local_client_id, &position.x);
                    if (++dropped >= count) break;
                }
                angle += 0x2000;
            }
        }
    }
}
#pragma pop

extern "C" {

s32 TObjTombstone::is_player_nearby() {
    Tomb_80076098 *self = (Tomb_80076098 *)this;
    Vec_80076098 d;
    f32 best;
    f32 len;
    s32 i;
    u8 *player;
    if (self->done != 0) {
        return 0;
    } else if (local_client_id != TLobby__designated_client_id) {
        self->done = 1;
        return 0;
    }
    if (check_all_players_active__13TObjTombstoneFv(this) == 0) {
        return 0;
    }
    best = TObjTombstone__data_805D9184;
    for (i = 0; i < 4; i++) {
        player = (u8 *)get_player_by_client_id(i);
        if (player != NULL) {
            VecCopy((Vec *)&d, (const Vec *)(player + 0x38));
            subtract_vector(&d, &self->pos);
            d.y = TObjTombstone__data_805D9174;
            len = vector_length(&d);
            if (best > len) {
                best = len;
            }
        }
    }
    return best < TObjTombstone__data_805D9184;
}

#pragma push
#pragma opt_common_subs off
void TObjTombstone::update_rise() {
    f32 temp_f1;
    f32 temp_f1_2;
    if ((is_other_tombstone_closer__13TObjTombstoneFv() == 0) && (this->m_b0 < TObjTombstone__data_805D917C)) {
        temp_f1 = *(f32 *)&this->unk_B4 + lbl_805D91B4;
        *(f32 *)&this->unk_B4 = temp_f1;
        if (temp_f1 > TObjTombstone__data_805D9178) {
            *(f32 *)&this->unk_B4 = (f32) TObjTombstone__data_805D9178;
        }
    } else {
        temp_f1_2 = *(f32 *)&this->unk_B4 + lbl_805D91B8;
        *(f32 *)&this->unk_B4 = temp_f1_2;
        if (temp_f1_2 < TObjTombstone__data_805D9174) {
            *(f32 *)&this->unk_B4 = (f32) TObjTombstone__data_805D9174;
        }
    }
}
#pragma pop

void TObjTombstone::run_task() {
    if (check_owner__13TObjTombstoneFv() != 0) {
        queue_destruction__7TObjectFv(this);
        return;
    }
    this->m_b0 = get_distance_to_local_player_xz__13TObjTombstoneFPv(this);
    update_rise();
    if (is_player_nearby() != 0) {
        TObjTombstone__sub_80075DFC(this);
    }
    this->m_230 = (this->m_230 + 1);
    tombstone_first_run_flag = 0;
}

extern s32 __vt__13TObjTombstone[];

}
TObjTombstone::~TObjTombstone() {

}
extern "C" {

}
