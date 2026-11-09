#include "pso/map/CsnGroundQuery.h"
#include "types.h"
#include "pso/player/TObjChara.h"
#include "pso/misc/TLobby.h"
#include "pso/item/TItemData.h"
#include "pso/player/TObjPlayer.h"
#include "pso/map/FloorArea.h"
#include "pso/unk/text_8011A780.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/player/PlayerRequirementStats.h"
#include "pso/TItemMenuCtrl.h"

struct Blk_8010542C { u32 w[4]; };
struct Item_8010542C { u32 a; Blk_8010542C b; };
struct Entry_8010567C { u16 a; u16 b; };

struct Pkt_8010567C {
    u8 hdr[4];
    u8 f4;
    u8 f5;
    s16 f6;
    f32 x;
    f32 z;
    s16 f10;
    s16 f12;
    u8 f14;
    f32 f18;
    s32 f1c;
    s32 f20;
    s32 f24;
};

struct Obj_8010567C {
    u8 pad[0x28];
    s16 f28;
    u8 pad2a[2];
    s16 f2c;
    u8 pad2e[0x38 - 0x2E];
    f32 x;
    f32 y;
    f32 z;
    u8 pad44[0x70 - 0x44];
    f32 f70;
    u8 pad74[0x84 - 0x74];
    s32 f84;
    s32 f88;
    s32 f8c;
};


struct Rec_80105538 { s32 a; u16 b; u16 b2; s32 c; };

struct Pkt_80105538 {
    u8 hdr[4];
    s8 f4;
    s8 f5;
    s16 f6;
    f32 x;
    f32 z;
    s16 f10;
    u8 f12[2];
    s8 f14;
};

struct Vec_80105538 { f32 x, y, z; };

struct Obj_80105538 {
    u8 pad[0x28];
    s16 f28;
    u8 pad2a[2];
    s16 f2c;
    u8 pad2e[0x38 - 0x2E];
    f32 x;
    f32 y;
    f32 z;
    u8 pad44[0x370 - 0x44];
    s32 f370;
};

extern "C" {
int is_quest_active(void);
u8 get_technique_learn_limit(u8, u8);
typedef s32 (*Fn_8010542C)(void *);
extern Fn_8010542C item_create_fn_table[];
struct In_801054E0 { u8 pad0; u8 idx; };
typedef s32 (*Fn_801054E0)(In_801054E0 *);
struct E_801054E0 { Fn_801054E0 fn; };
extern E_801054E0 item_pro_create_fn_table[];
s32 TLobby__sub_801054E0(In_801054E0 *arg0);
void *get_player_by_client_id(s32);
s32 get_current_floor(void);
s32 TObjPlayer__sub_80104840(s32);
extern s32 TLobby__designated_client_id;
extern Entry_8010567C *quest_object_entries;
extern s32 local_client_id;
int check_class_equip_permission(TObjPlayer *player, s16 perm);
s32 is_valid_drop_floor();
}
void *build_6x06_send_guild_card(void *arg0);
extern Rec_80105538 *TLobby__data_805D6144;
extern const f32 lbl_805DAAB4;
extern "C" {
void send_6x60_standard_drop_item_request(Obj_80105538 *self);
int roll_weapon_special_channel15(void* p);
int roll_weapon_special_for_stars(void*);

// Slices of the ItemPMT record (lookup_item_pmt_record) this check loads.
// Weapon: class at +8, ATP/MST/ATA minimums at +0xE/+0x10/+0x12.
struct WeaponReqPmt {
    u8 pad0[8];
    u16 class_equip;
    u8 padA[4];
    u16 req_atp;
    u16 req_mst;
    u16 req_ata;
};
// Armor and barrier (type 1, subtype other than a unit): class at +0xE, level at +0x10.
struct ArmorReqPmt {
    u8 pad0[0xE];
    u16 class_equip;
    u8 level_req;
};
// Unit (type 1, subtype 3). restrict_index selects an android allow/deny case.
struct UnitReqPmt {
    u8 pad0[8];
    s16 restrict_index;
};
// Mag: class word at +0x14.
struct MagReqPmt {
    u8 pad0[0x14];
    u16 class_equip;
};

// Permission word whose human and newman bits are clear, so only an android passes.
#define ANDROID_EQUIP_PERM 0xD7
// Meseta above this (999999) is rejected.
#define MESETA_EQUIP_CAP 0xF423F

s32 check_equip_requirements(TObjPlayer *player, u8 *item, s32 *requirement) {
    s32 flags;
    PlayerRequirementStats stats;

    if (player == NULL || item == NULL) {
        if (requirement != NULL) {
            *requirement |= 0x20;
        }
        return 0;
    }
    if (player->obj_isState3_324() != 0 || player->is_script_controlled() != 0) {
        if (requirement != NULL) {
            *requirement = 0;
        }
        return 1;
    }
    if (is_quest_active() != 0) {
        u32 qflag;

        qflag = 0;
        switch (item[0]) {
        case 0:
            qflag = 1;
            break;
        case 1:
            switch (item[1]) {
            case 1:
                qflag = 2;
                break;
            case 2:
                qflag = 3;
                break;
            case 3:
                qflag = 4;
                break;
            }
            break;
        case 2:
            qflag = 5;
            break;
        }
        if (qflag != 0 && TItemMenuCtrl::query_flag(qflag) == 1) {
            return 0;
        }
    }
    flags = 0;
    switch (item[0]) {
    case 0: {
        WeaponReqPmt *rec;

        rec = (WeaponReqPmt *)lookup_item_pmt_record(item);
        if (rec != NULL) {
            if (check_class_equip_permission(player, rec->class_equip) == 0) {
                flags |= 1;
            }
            ((TWindowSubStatusDisp *)&stats)->clear_fields();
            build_player_equipment_requirement_stats(player, &stats);
            if (stats.values[0] < rec->req_atp) {
                flags |= 2;
            }
            if (stats.values[3] < rec->req_ata) {
                flags |= 4;
            }
            if (stats.values[2] < rec->req_mst) {
                flags |= 8;
            }
        } else {
            flags |= 0x20;
        }
        break;
    }
    case 1:
        if (item[1] != 3) {
            ArmorReqPmt *rec;

            rec = (ArmorReqPmt *)lookup_item_pmt_record(item);
            if (rec != NULL) {
                if (check_class_equip_permission(player, rec->class_equip) == 0) {
                    flags |= 1;
                }
                if (player->get_actor_level_index() < rec->level_req) {
                    flags |= 0x10;
                }
            } else {
                flags |= 0x20;
            }
        } else if (check_class_equip_permission(player, ANDROID_EQUIP_PERM) != 0) {
            UnitReqPmt *rec;

            rec = (UnitReqPmt *)lookup_item_pmt_record(item);
            if (rec != NULL) {
                switch (rec->restrict_index) {
                case 0:
                case 2:
                case 3:
                case 4:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                case 17:
                case 19:
                case 20:
                    break;
                case 1:
                case 5:
                case 16:
                case 18:
                case 21:
                    flags |= 1;
                    break;
                }
            } else {
                flags |= 0x20;
            }
        }
        break;
    case 2: {
        MagReqPmt *rec;

        rec = (MagReqPmt *)lookup_item_pmt_record(item);
        if (rec != NULL) {
            if (check_class_equip_permission(player, rec->class_equip) == 0) {
                flags |= 1;
            }
        } else {
            flags |= 0x20;
        }
        break;
    }
    case 3:
        switch (item[1]) {
        case 2: {
            u8 learn_limit;

            // Widened the same way as TItemData::calc_action_flags: the u8
            // parameter narrows it, and that argument is evaluated first.
            learn_limit = get_technique_learn_limit(player->m_88d, (s16)item[4]);
            if (learn_limit == 0xFF || learn_limit < item[2]) {
                flags |= 1;
            }
            break;
        }
        case 8:
            if (check_class_equip_permission(player, ANDROID_EQUIP_PERM) != 0) {
                flags |= 1;
            }
            break;
        }
        break;
    case 4: {
        // An enum local is rematerialized as the left operand of a signed compare.
        enum MesetaCap { meseta_cap = MESETA_EQUIP_CAP };
        MesetaCap cap = meseta_cap;

        if (cap < ((TItemData *)item)->data2.meseta) {
            flags |= 0x20;
        }
        break;
    }
    }
    if (requirement != NULL) {
        *requirement = flags;
    }
    if (flags == 0) {
        return 1;
    }
    return 0;
}

int check_class_equip_permission(TObjPlayer *player, s16 perm) {
    s32 t = player->class_flags;
    if (t & CLASS_FLAG_HUNTER) {
        if (!(perm & 1)) return 0;
    } else if (t & CLASS_FLAG_RANGER) {
        if (!(perm & 2)) return 0;
    } else if (!(perm & 4)) {
        return 0;
    }
    if (t & CLASS_FLAG_ANDROID) {
        if (!(perm & 0x10)) return 0;
    } else if (t & CLASS_FLAG_NEWMAN) {
        if (!(perm & 0x20)) return 0;
    } else if (t & CLASS_FLAG_HUMAN) {
        if (!(perm & 8)) return 0;
    }
    if (t & CLASS_FLAG_MALE) {
        if (!(perm & 0x40)) return 0;
    } else if (t & CLASS_FLAG_FEMALE) {
        if (!(perm & 0x80)) return 0;
    }
    return 1;
}

int roll_weapon_special_channel15(void* p) { return roll_weapon_special_for_stars(p); }
}

TItem *construct_item(TItemData *data) {
    Item_8010542C *src = (Item_8010542C *)data;
    Fn_8010542C fn;
    if (src != 0) {
        Item_8010542C item = *src;
        ((TItemData *)&item)->decode_from_network();
        if (((TItemData *)(&item))->isValidGroundDrop() != 0) {
            if (*(u8 *)src < 5) {
                fn = item_create_fn_table[*(u8 *)src];
                if (fn != 0) {
                    observe_item_id(item.b.w[2]);
                    return (TItem *)fn(&item);
                }
            }
        }
    }
    return 0;
}

extern "C" {

s32 TLobby__sub_801054E0(In_801054E0 *arg0) {
    if (arg0 != 0) {
        if (arg0->idx < 4) {
            if (item_pro_create_fn_table[arg0->idx].fn != 0) {
                return item_pro_create_fn_table[arg0->idx].fn(arg0);
            }
        }
    }
    return 0;
}

void send_6x60_standard_drop_item_request(Obj_80105538 *self) {
    void *p1;
    void *p2;
    if (self != 0) {
        p1 = get_player_by_client_id(TLobby__designated_client_id);
        p2 = get_player_by_client_id(local_client_id);
        if (p1 != 0 && p2 != 0) {
            get_current_floor();
            if (is_valid_drop_floor() != 0 &&
                (((TObjPlayer *)p1)->get_floor() != ((TObjPlayer *)p2)->get_floor() ||
                 TLobby__designated_client_id == local_client_id)) {
                if (self->f2c != -1) {
                    Rec_80105538 e = TLobby__data_805D6144[self->f2c];
                    if (e.b != 0xFFFF) {
                        Pkt_80105538 pkt;
                        build_6x06_send_guild_card(&pkt);
                        pkt.f4 = get_current_floor();
                        pkt.f5 = self->f370;
                        pkt.f6 = self->f2c;
                        pkt.x = self->x;
                        pkt.z = self->z;
                        pkt.f10 = self->f28;
                        pkt.f14 = get_current_floor_area();
                        Vec_80105538 v;
                        v.x = pkt.x;
                        v.y = lbl_805DAAB4;
                        v.z = pkt.z;
                        if (csnVecterUnder((const Vec *)&v, 1) != 0) {
                            ((TLobby *)(&pkt))->dispatch_packet_wrapper();
                        }
                    }
                }
            }
        }
    }
}

void TObjChara::request_box_item_drop(void *unused, s16 arg2) {
    Obj_8010567C *self = (Obj_8010567C *)this;
    void *p1;
    void *p2;
    if (self != 0) {
        p1 = get_player_by_client_id(TLobby__designated_client_id);
        p2 = get_player_by_client_id(local_client_id);
        if (p1 != 0 && p2 != 0 && TObjPlayer__sub_80104840(get_current_floor_area()) != AREA_PIONEER2_EP1 &&
            (((TObjPlayer *)p1)->get_floor() != ((TObjPlayer *)p2)->get_floor() ||
             TLobby__designated_client_id == local_client_id)) {
            if (self->f2c != -1) {
                Entry_8010567C e = quest_object_entries[self->f2c];
                if (e.b != 0xFFFF) {
                    Pkt_8010567C pkt;
                    ((TLobby *)(&pkt))->build_6x06_guild_card_packet();
                    pkt.f4 = get_current_floor();
                    pkt.f5 = 0x30;
                    pkt.x = self->x;
                    pkt.z = self->z;
                    pkt.f10 = self->f28;
                    pkt.f12 = arg2;
                    pkt.f6 = self->f2c;
                    pkt.f14 = get_current_floor_area();
                    pkt.f18 = self->f70;
                    pkt.f1c = this->set_params[0];
                    pkt.f20 = self->f88;
                    pkt.f24 = this->set_params[2];
                    ((TLobby *)(&pkt))->process_and_dispatch_packet();
                }
            }
        }
    }
}
}
