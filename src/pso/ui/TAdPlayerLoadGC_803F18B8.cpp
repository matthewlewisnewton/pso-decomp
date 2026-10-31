#include "types.h"
#include "pso/ui/TAdPlayerLoadGC_803F18B8.h"
#include "pso/TAdPlayerLoadGC.h"
#include "dolphin/os.h"
#include "dolphin/card.h"

struct S_803F3328 {
    u8 pad0[4];
    s32 state;
    CARDFileInfo card;
    CARDStat stat;
};
typedef struct Slot_803F3478 {
    s32 f0;
    char name[0x20];
    char name2[0x20];
    s32 f44;
    s32 f48;
    s32 f4C;
    s32 f50;
    s32 f54;
    s32 f58;
    s32 f5C;
    s32 f60;
    u8 f64;
    u8 pad65[3];
} Slot_803F3478;
typedef Slot_803F3478 Slot_803F1CC4, Slot_803F1E90, Slot_803F2058;

extern "C" {
extern s32 lbl_805D7940;
s32 memset(void *, int, int);
void *CARDGetDiskID(s32);
s32 CARDSetDiskID(s32, void *);
void *memcpy(void *, const void *, u32);
extern void *lbl_805D7950;
extern u8 lbl_805E10EC[4];
extern u8 lbl_805E10F4[2];
u8 lbl_805A28C0[0x20];
Slot_803F3478 TAdPlayerLoadGC__load_request_slots[2];
S_803F3328 lbl_805A29B0[100];
u8 lbl_805A5ED0[0x30];
struct CardInfo_803F31D8 { s32 state; s32 f4; u32 sector_size; };
extern void *lbl_805D7960;

extern s32 player_load_channel_flags;

s32 TAdPlayerLoadGC::get_or_set_channel_flag(s32 arg0, s32 arg1) {
    if (((arg0 != 0) && (arg0 != 1)) || (arg1 < 0) || (arg1 > 2)) {
        return 0;
    }
    if (arg1 != 2) {
        (&player_load_channel_flags)[arg0] = arg1;
    }
    return (&player_load_channel_flags)[arg0];
}

s32 TAdPlayerLoadGC::get_load_state() {
    return lbl_805D7940;
}

int sprintf(char *, const char *, ...);
int strcmp(const char *, const char *);
int memcmp(const void *, const void *, u32);
extern char lbl_8047FD08[];

#pragma push
#pragma opt_propagation off
void TAdPlayerLoadGC__sub_803F1908(s32 card_channel) {
    s32 *st;
    CARDStat stat;
    char company[2];
    char game[4];
    OSCalendarTime calendar;
    char date[0x20];
    // These loop invariants retain the native saved-register lifetimes.
    u32 ticks_per_second;
    void *disk_id;
    char *slot_name;
    u8 *game_name;
    u8 *company_name;
    s32 i;
    s32 found;

    st = (s32 *)(lbl_805A28C0 + card_channel * 0x68);
    st += 0x1A;

    switch (*st) {
    case 1:
        TAdPlayerLoadGC__load_request_slots[card_channel].f5C = CARDMountAsync(card_channel, lbl_805D7960, 0, 0);
        if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C < 0) {
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -0xC8;
            *st = 0x18;
            return;
        }
        *st = 2;
    case 2:
        TAdPlayerLoadGC__load_request_slots[card_channel].f5C = CARDGetResultCode(card_channel);
        if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C == 0 || TAdPlayerLoadGC__load_request_slots[card_channel].f5C == -6) {
            *st = 3;
        } else {
            if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C != -1) {
                TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -0xC8;
                *st = 0x18;
            }
            return;
        }
    case 3:
        TAdPlayerLoadGC__load_request_slots[card_channel].f5C = CARDCheckAsync(card_channel, 0);
        if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C < 0) {
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -0xC9;
            *st = 0x18;
            return;
        }
        *st = 4;
    case 4:
        TAdPlayerLoadGC__load_request_slots[card_channel].f5C = CARDGetResultCode(card_channel);
        if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C == 0) {
            *st = 5;
        } else {
            if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C != -1) {
                TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -0xC9;
                *st = 0x18;
                CARDUnmount(card_channel);
            }
            return;
        }
    case 5:
        TAdPlayerLoadGC__load_request_slots[card_channel].f5C = CARDGetSectorSize(card_channel, &((CardInfo_803F31D8 *)lbl_805A5ED0)[card_channel].sector_size);
        if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C < 0) {
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -0xCA;
            *st = 0x18;
            goto unmount;
        }
        if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1) {
            lbl_805D7950 = CARDGetDiskID(card_channel);
            memcpy(lbl_805A28C0, lbl_805D7950, 0x20);
            memcpy(lbl_805A28C0, lbl_805E10EC, 4);
            memcpy(lbl_805A28C0 + 4, lbl_805E10F4, 2);
            CARDSetDiskID(card_channel, lbl_805A28C0);
        }
        if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) != 1) {
            disk_id = CARDGetDiskID(card_channel);
            memcpy(game, disk_id, 4);
            memcpy(company, (u8 *)disk_id + 4, 2);
        } else {
            memcpy(game, lbl_805E10EC, 4);
            memcpy(company, lbl_805E10F4, 2);
        }
        found = 0;
        i = 0;
        slot_name = TAdPlayerLoadGC__load_request_slots[card_channel].name;
        game_name = stat.gameName;
        company_name = stat.company;
        ticks_per_second = *(u32 *)0x800000F8 >> 2;
        for (; i < 0x7F; i++) {
            if (CARDGetStatus(card_channel, i, &stat) >= 0) {
                OSTicksToCalendarTime((u64)(stat.time * ticks_per_second), &calendar);
                sprintf(date, lbl_8047FD08, calendar.year, calendar.mon + 1, calendar.mday, calendar.hour, calendar.min, calendar.sec);
                if (strcmp(stat.fileName, slot_name) == 0 &&
                    memcmp(game_name, game, 4) == 0 && memcmp(company_name, company, 2) == 0) {
                    found = 1;
                    break;
                }
            }
        }
        if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
            CARDSetDiskID(card_channel, lbl_805D7950);
        }
        if (found == 0) {
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -0x66;
        } else {
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = 0;
        }
        *st = 0x16;
    unmount:
        CARDUnmount(card_channel);
        return;
    case 0: case 6: case 7: case 8: case 9: case 0xA: case 0xB: case 0xC:
    case 0xD: case 0xE: case 0xF: case 0x10: case 0x11: case 0x12: case 0x13:
    case 0x14: case 0x15: case 0x16: case 0x17: case 0x18:
        return;
    }
}
#pragma pop

#pragma push
#pragma opt_propagation off
void TAdPlayerLoadGC::step_set_attributes(s32 card_channel) {
    s32 *st;
    st = (s32 *)(lbl_805A28C0 + card_channel * 0x68);
    st += 0x1A;

    switch (*st) {

    case 0x11:
        if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1) {
            lbl_805D7950 = CARDGetDiskID(card_channel);
            memcpy(lbl_805A28C0, lbl_805D7950, 0x20);
            memcpy(lbl_805A28C0, lbl_805E10EC, 4);
            memcpy(lbl_805A28C0 + 4, lbl_805E10F4, 2);
            CARDSetDiskID(card_channel, lbl_805A28C0);
        }
        TAdPlayerLoadGC__load_request_slots[card_channel].f5C = CARDSetAttributesAsync(card_channel, TAdPlayerLoadGC__load_request_slots[card_channel].f60, TAdPlayerLoadGC__load_request_slots[card_channel].f64, 0);
        if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C < 0) {
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -0xD4;
            *st = 0x18;
            break;
        }
        *st = 0x12;
    case 0x12:
        TAdPlayerLoadGC__load_request_slots[card_channel].f5C = CARDGetResultCode(card_channel);
        if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C == 0) {
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = 0;
            *st = 0x16;
        } else if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C != -1) {
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -0xD4;
            *st = 0x18;
        }
        break;
    case 0x13: case 0x14: case 0x15: case 0x16: case 0x17: case 0x18:
        return;
    }
}
#pragma pop
#pragma push
#pragma opt_propagation off
void TAdPlayerLoadGC::update_card_delete(s32 card_channel) {
    s32 *st;
    Slot_803F1E90 *s;
    st = (s32 *)(lbl_805A28C0 + card_channel * 0x68);
    st += 0x1A;

    switch (*st) {
    case 0xF:
        if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1) {
            lbl_805D7950 = CARDGetDiskID(card_channel);
            memcpy(lbl_805A28C0, lbl_805D7950, 0x20);
            memcpy(lbl_805A28C0, lbl_805E10EC, 4);
            memcpy(lbl_805A28C0 + 4, lbl_805E10F4, 2);
            CARDSetDiskID(card_channel, lbl_805A28C0);
        }
        TAdPlayerLoadGC__load_request_slots[card_channel].f5C = CARDDeleteAsync(card_channel, TAdPlayerLoadGC__load_request_slots[card_channel].name, 0);
        if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C < 0) {
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -0xD3;
            *st = 0x18;
            break;
        }
        *st = 0x10;
    case 0x10:
        TAdPlayerLoadGC__load_request_slots[card_channel].f5C = CARDGetResultCode(card_channel);
        if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C == 0) {
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = 0;
            *st = 0x16;
        } else if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C != -1) {
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -0xD3;
            *st = 0x18;
        }
        break;
    case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x17: case 0x18:
        return;
    }
}
#pragma pop
#pragma push
#pragma opt_propagation off
void TAdPlayerLoadGC::update_card_rename(s32 card_channel) {
    s32 *st;
    s32 off;
    off = card_channel * 0x68;
    st = (s32 *)(lbl_805A28C0 + off);
    st += 0x1A;

    switch (*st) {
    case 0xd:
        if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1) {
            lbl_805D7950 = CARDGetDiskID(card_channel);
            memcpy(lbl_805A28C0, lbl_805D7950, 0x20);
            memcpy(lbl_805A28C0, lbl_805E10EC, 4);
            memcpy(lbl_805A28C0 + 4, lbl_805E10F4, 2);
            CARDSetDiskID(card_channel, lbl_805A28C0);
        }
        TAdPlayerLoadGC__load_request_slots[card_channel].f5C = CARDRenameAsync(card_channel, TAdPlayerLoadGC__load_request_slots[card_channel].name, TAdPlayerLoadGC__load_request_slots[card_channel].name2, 0);
        if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C < 0) {
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -210;
            *st = 0x18;
            break;
        }
        *st = 0xe;
    case 0xe:
        TAdPlayerLoadGC__load_request_slots[card_channel].f5C = CARDGetResultCode(card_channel);
        if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C == 0) {
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = 0;
            *st = 0x16;
        } else if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C != -1) {
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -210;
            *st = 0x18;
        }
        break;
    case 0xf: case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x17: case 0x18:
        return;
    }
}
#pragma pop

#pragma push
#pragma opt_propagation off
#pragma opt_lifetimes off
void TAdPlayerLoadGC__sub_803F2240(s32 arg0) {
    Slot_803F3478 *result_slot;
    s32 result;
    s32 request_index;
    u32 request_offset;
    u32 record_offset = arg0 * sizeof(S_803F3328);
    s32 card_channel = lbl_805A29B0[arg0].state;

    switch (TAdPlayerLoadGC__load_request_slots[card_channel].f48) {
    case 0xB:
        if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1) {
            lbl_805D7950 = CARDGetDiskID(card_channel);
            memcpy(lbl_805A28C0, lbl_805D7950, 0x20);
            memcpy(lbl_805A28C0, lbl_805E10EC, 4);
            memcpy(lbl_805A28C0 + 4, lbl_805E10F4, 2);
            CARDSetDiskID(card_channel, lbl_805A28C0);
        }
        result = CARDWriteAsync(&((S_803F3328 *)((u8 *)lbl_805A29B0 + record_offset))->card, (void *)TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f0, TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f50, TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f4C, 0);
        request_index = lbl_805A29B0[arg0].state;
        request_offset = request_index * sizeof(Slot_803F3478);
        result_slot = (Slot_803F3478 *)((u8 *)TAdPlayerLoadGC__load_request_slots + request_offset);
        result_slot->f5C = result;
        if (result_slot->f5C < 0) {
            card_channel = lbl_805A29B0[arg0].state;
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f58 = -0xCE;
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x18;
            break;
        }
        TAdPlayerLoadGC__load_request_slots[request_index].f48 = 0xC;
    case 0xC:
        result = CARDGetResultCode(lbl_805A29B0[arg0].state);
        result_slot = &TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state];
        result_slot->f5C = result;
        if (result_slot->f5C == 0) {
            card_channel = lbl_805A29B0[arg0].state;
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x14;
        } else {
            if (result_slot->f5C == -1) {
                break;
            }
            card_channel = lbl_805A29B0[arg0].state;
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f58 = -0xCE;
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x18;
            break;
        }
    case 0x14:
        card_channel = lbl_805A29B0[arg0].state;
        if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1) {
            lbl_805D7950 = CARDGetDiskID(card_channel);
            memcpy(lbl_805A28C0, lbl_805D7950, 0x20);
            memcpy(lbl_805A28C0, lbl_805E10EC, 4);
            memcpy(lbl_805A28C0 + 4, lbl_805E10F4, 2);
            CARDSetDiskID(card_channel, lbl_805A28C0);
        }
        result = CARDSetStatusAsync(lbl_805A29B0[arg0].state, lbl_805A29B0[arg0].card.fileNo, &((S_803F3328 *)((u8 *)lbl_805A29B0 + record_offset))->stat, 0);
        request_index = lbl_805A29B0[arg0].state;
        request_offset = request_index * sizeof(Slot_803F3478);
        result_slot = (Slot_803F3478 *)((u8 *)TAdPlayerLoadGC__load_request_slots + request_offset);
        result_slot->f5C = result;
        if (result_slot->f5C < 0) {
            card_channel = lbl_805A29B0[arg0].state;
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f58 = -0xD0;
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x18;
            break;
        }
        TAdPlayerLoadGC__load_request_slots[request_index].f48 = 0x15;
    case 0x15:
        result = CARDGetResultCode(lbl_805A29B0[arg0].state);
        result_slot = &TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state];
        result_slot->f5C = result;
        if (result_slot->f5C == 0) {
            card_channel = lbl_805A29B0[arg0].state;
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f58 = 0;
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x16;
        } else if (result_slot->f5C != -1) {
            card_channel = lbl_805A29B0[arg0].state;
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f58 = -0xD0;
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x18;
        }
        break;
    case 0x16: case 0x17: case 0x18:
        return;
    default:
        return;
    }
}
#pragma pop

#pragma push
#pragma opt_propagation off
void TAdPlayerLoadGC__sub_803F2610(s32 arg0) {
    Slot_803F3478 *result_slot;
    s32 request_index;
    u32 request_offset;
    s32 result;
    s32 card_channel;
    s32 offset = arg0 * sizeof(S_803F3328);
    card_channel = lbl_805A29B0[arg0].state;

    switch (TAdPlayerLoadGC__load_request_slots[card_channel].f48) {
    case 9:
        if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1) {
            lbl_805D7950 = CARDGetDiskID(card_channel);
            memcpy(lbl_805A28C0, lbl_805D7950, 0x20);
            memcpy(lbl_805A28C0, lbl_805E10EC, 4);
            memcpy(lbl_805A28C0 + 4, lbl_805E10F4, 2);
            CARDSetDiskID(card_channel, lbl_805A28C0);
        }
        result = CARDReadAsync(&((S_803F3328 *)((u8 *)lbl_805A29B0 + offset))->card, (void *)TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f0, TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f50, TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f4C, 0);
        request_index = lbl_805A29B0[arg0].state;
        request_offset = request_index * sizeof(Slot_803F3478);
        result_slot = (Slot_803F3478 *)((u8 *)TAdPlayerLoadGC__load_request_slots + request_offset);
        result_slot->f5C = result;
        if (result_slot->f5C < 0) {
            card_channel = lbl_805A29B0[arg0].state;
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f58 = -0xCD;
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x18;
            break;
        }
        TAdPlayerLoadGC__load_request_slots[request_index].f48 = 0xA;
    case 0xA:
        result = CARDGetResultCode(lbl_805A29B0[arg0].state);
        result_slot = &TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state];
        result_slot->f5C = result;
        if (result_slot->f5C == 0) {
            card_channel = lbl_805A29B0[arg0].state;
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f58 = 0;
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x16;
        } else if (result_slot->f5C != -1) {
            card_channel = lbl_805A29B0[arg0].state;
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f58 = -0xCD;
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x18;
        }
        break;
    case 0xB: case 0xC: case 0xD: case 0xE: case 0xF:
    case 0x10: case 0x11: case 0x12: case 0x13: case 0x14:
    case 0x15: case 0x16: case 0x17: case 0x18:
        return;
    }
}
#pragma pop

#pragma push
#pragma opt_propagation off
void TRKSuppAccessFile(s32 arg0) {
    Slot_803F3478 *result_slot;
    s32 result;
    s32 request_index;
    u32 request_offset;
    u32 record_offset = arg0 * sizeof(S_803F3328);
    s32 card_channel = lbl_805A29B0[arg0].state;

    switch (TAdPlayerLoadGC__load_request_slots[card_channel].f48) {
    case 8:
        if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1) {
            lbl_805D7950 = CARDGetDiskID(card_channel);
            memcpy(lbl_805A28C0, lbl_805D7950, 0x20);
            memcpy(lbl_805A28C0, lbl_805E10EC, 4);
            memcpy(lbl_805A28C0 + 4, lbl_805E10F4, 2);
            CARDSetDiskID(card_channel, lbl_805A28C0);
        }
        result = CARDOpen(lbl_805A29B0[arg0].state, TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].name, &((S_803F3328 *)((u8 *)lbl_805A29B0 + record_offset))->card);
        request_index = lbl_805A29B0[arg0].state;
        request_offset = request_index * sizeof(Slot_803F3478);
        result_slot = (Slot_803F3478 *)((u8 *)TAdPlayerLoadGC__load_request_slots + request_offset);
        result_slot->f5C = result;
        if (result_slot->f5C < 0) {
            card_channel = lbl_805A29B0[arg0].state;
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f58 = -0xCC;
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x18;
            break;
        }
        TAdPlayerLoadGC__load_request_slots[request_index].f48 = 0x13;
    case 0x13:
        result = CARDGetStatus(lbl_805A29B0[arg0].state, lbl_805A29B0[arg0].card.fileNo, &((S_803F3328 *)((u8 *)lbl_805A29B0 + record_offset))->stat);
        request_index = lbl_805A29B0[arg0].state;
        request_offset = request_index * sizeof(Slot_803F3478);
        result_slot = (Slot_803F3478 *)((u8 *)TAdPlayerLoadGC__load_request_slots + request_offset);
        result_slot->f5C = result;
        if (result_slot->f5C < 0) {
            card_channel = lbl_805A29B0[arg0].state;
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f58 = -0xCF;
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x18;
            CARDClose(&((S_803F3328 *)((u8 *)lbl_805A29B0 + record_offset))->card);
        } else {
            card_channel = lbl_805A29B0[arg0].state;
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f58 = 0;
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x16;
        }
        break;
    case 0x14: case 0x15: case 0x16: case 0x17: case 0x18:
        return;
    }
}
#pragma pop

#pragma push
#pragma opt_propagation off
void TAdPlayerLoadGC__sub_803F2A4C(s32 arg0) {
    Slot_803F3478 *result_slot;
    s32 result;
    s32 request_index;
    s32 card_channel = lbl_805A29B0[arg0].state;

    switch (TAdPlayerLoadGC__load_request_slots[card_channel].f48) {
    case 6:
        if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1) {
            lbl_805D7950 = CARDGetDiskID(card_channel);
            memcpy(lbl_805A28C0, lbl_805D7950, 0x20);
            memcpy(lbl_805A28C0, lbl_805E10EC, 4);
            memcpy(lbl_805A28C0 + 4, lbl_805E10F4, 2);
            CARDSetDiskID(card_channel, lbl_805A28C0);
        }
        result = CARDCreateAsync(lbl_805A29B0[arg0].state, TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].name, TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f50, &lbl_805A29B0[arg0].card, 0);
        request_index = lbl_805A29B0[arg0].state;
        result_slot = &TAdPlayerLoadGC__load_request_slots[request_index];
        result_slot->f5C = result;
        if (result_slot->f5C < 0) {
            card_channel = lbl_805A29B0[arg0].state;
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f58 = -0xCB;
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x18;
            break;
        }
        TAdPlayerLoadGC__load_request_slots[request_index].f48 = 7;
    case 7:
        result = CARDGetResultCode(lbl_805A29B0[arg0].state);
        request_index = lbl_805A29B0[arg0].state;
        result_slot = &TAdPlayerLoadGC__load_request_slots[request_index];
        result_slot->f5C = result;
        if (result_slot->f5C == 0) {
            card_channel = lbl_805A29B0[arg0].state;
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x13;
        } else {
            if (result_slot->f5C == -1) {
                break;
            }
            card_channel = lbl_805A29B0[arg0].state;
            if (TAdPlayerLoadGC::get_or_set_channel_flag(card_channel, 2) == 1 && lbl_805D7950 != NULL) {
                CARDSetDiskID(card_channel, lbl_805D7950);
            }
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f58 = -0xCB;
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x18;
            break;
        }
    case 0x13:
        TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f5C = CARDGetStatus(lbl_805A29B0[arg0].state, lbl_805A29B0[arg0].card.fileNo, &lbl_805A29B0[arg0].stat);
        if (TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f5C < 0) {
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f58 = -0xCF;
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x18;
            CARDClose(&lbl_805A29B0[arg0].card);
        } else {
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f58 = 0;
            TAdPlayerLoadGC__load_request_slots[lbl_805A29B0[arg0].state].f48 = 0x16;
        }
        break;
    case 8: case 9: case 0xA: case 0xB: case 0xC: case 0xD: case 0xE: case 0xF:
    case 0x10: case 0x11: case 0x12: case 0x14: case 0x15: case 0x16: case 0x17: case 0x18:
        return;
    }
}
#pragma pop

void TAdPlayerLoadGC__sub_803F2CD0(s32 card_channel, s32 result) {
    TAdPlayerLoadGC__load_request_slots[card_channel].f5C = result;
    switch (result) {
    default:
        TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -201;
        TAdPlayerLoadGC__load_request_slots[card_channel].f48 = 0x18;
        break;
    case 0:
    case -6:
        TAdPlayerLoadGC__load_request_slots[card_channel].f48 = 5;
        break;
    }
}

#pragma push
#pragma opt_propagation off
void TAdPlayerLoadGC__sub_803F2D20(s32 card_channel) {
    s32 *st;
    st = (s32 *)(lbl_805A28C0 + card_channel * 0x68);
    st += 0x1A;

    switch (*st) {
    case 1:
        TAdPlayerLoadGC__load_request_slots[card_channel].f5C = CARDMountAsync(card_channel, lbl_805D7960, 0, 0);
        if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C < 0) {
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -200;
            *st = 0x18;
            break;
        }
        *st = 2;
    case 2:
        TAdPlayerLoadGC__load_request_slots[card_channel].f5C = CARDGetResultCode(card_channel);
        if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C == 0 || TAdPlayerLoadGC__load_request_slots[card_channel].f5C == -6) {
            *st = 3;
        } else {
            if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C != -1) {
                TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -200;
                *st = 0x18;
            }
            break;
        }
    case 3:
        TAdPlayerLoadGC__load_request_slots[card_channel].f5C = CARDCheckAsync(card_channel, TAdPlayerLoadGC__sub_803F2CD0);
        if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C < 0) {
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -201;
            *st = 0x18;
            break;
        }
        *st = 4;
    case 4:
        TAdPlayerLoadGC__load_request_slots[card_channel].f5C = CARDGetResultCode(card_channel);
        if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C == 0) {
            *st = 5;
        } else {
            if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C != -1) {
                TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -201;
                *st = 0x18;
                CARDUnmount(card_channel);
            }
            break;
        }
    case 5:
        TAdPlayerLoadGC__load_request_slots[card_channel].f5C = CARDGetSectorSize(card_channel, &((CardInfo_803F31D8 *)lbl_805A5ED0)[card_channel].sector_size);
        if (TAdPlayerLoadGC__load_request_slots[card_channel].f5C < 0) {
            TAdPlayerLoadGC__load_request_slots[card_channel].f58 = -202;
            *st = 0x18;
            CARDUnmount(card_channel);
            break;
        }
        TAdPlayerLoadGC__load_request_slots[card_channel].f58 = 0;
        *st = 0x16;
        break;
    case 0: case 6: case 7: case 8: case 9: case 0xA: case 0xB: case 0xC:
    case 0xD: case 0xE: case 0xF: case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x17: case 0x18:
        return;
    }
}
#pragma pop

extern u8 lbl_805D7944;
extern void (*lbl_805D7948)(s32, s32, u32);
extern void (*lbl_805D794C)(s32, s32, u32);
extern s32 lbl_805D7954;
extern s32 lbl_805E10E8;

// Keep native array-index induction variables; pointer walking changes both the
// stack/register allocation and the generated command-table branch targets.
#pragma push
#pragma opt_strength_reduction off
#pragma opt_propagation on
s32 TAdPlayerLoadGC__sub_803F2F1C(void) {
    s32 channel;
    s32 result;
    s32 mem_size;
    u32 sector_size;
    s32 request_channel;
    u32 level;
    CardInfo_803F31D8 *info;

    if (lbl_805D7940 < 1) {
        return -1;
    }
    if (lbl_805D7944 != 0) {
        return 0;
    }
    lbl_805D7944++;

    for (channel = 0; channel < 2; channel++) {
        result = CARDProbeEx(channel, &mem_size, (s32 *)&sector_size);
        switch (result) {
        case -128:
        default:
            info = &((CardInfo_803F31D8 *)lbl_805A5ED0)[channel];
            if (result != info->state) {
                info->state = result;
                info->f4 = 0;
                info->sector_size = 0;
            }
            break;
        case -3:
            info = &((CardInfo_803F31D8 *)lbl_805A5ED0)[channel];
            if (result != info->state) {
                if (info->state == 0) {
                    mem_size = info->f4;
                    sector_size = info->sector_size;
                    info->state = result;
                    info->f4 = 0;
                    info->sector_size = 0;
                    if (lbl_805D794C != NULL) {
                        level = OSDisableInterrupts();
                        lbl_805D794C(channel, mem_size, sector_size);
                        OSRestoreInterrupts(level);
                    }
                }
                info->state = result;
                info->f4 = 0;
                info->sector_size = 0;
            }
            break;
        case -2:
            info = &((CardInfo_803F31D8 *)lbl_805A5ED0)[channel];
            if (result != info->state) {
                info->state = result;
                info->f4 = 0;
                info->sector_size = 0;
            }
            break;
        case 0:
            info = &((CardInfo_803F31D8 *)lbl_805A5ED0)[channel];
            if (result != info->state) {
                info->state = result;
                ((CardInfo_803F31D8 *)lbl_805A5ED0)[channel].f4 = mem_size;
                ((CardInfo_803F31D8 *)lbl_805A5ED0)[channel].sector_size = sector_size;
                if (lbl_805D7948 != NULL) {
                    level = OSDisableInterrupts();
                    lbl_805D7948(channel, ((CardInfo_803F31D8 *)lbl_805A5ED0)[channel].f4, ((CardInfo_803F31D8 *)lbl_805A5ED0)[channel].sector_size);
                    OSRestoreInterrupts(level);
                }
            }
            break;
        case -1:
            break;
        }
    }

    for (request_channel = 0; request_channel < 2; request_channel++) {
        switch (TAdPlayerLoadGC__load_request_slots[request_channel].f44) {
        case 1:
            TAdPlayerLoadGC__sub_803F2D20(request_channel);
            break;
        case 2:
            TAdPlayerLoadGC__sub_803F2A4C(TAdPlayerLoadGC__load_request_slots[request_channel].f54);
            break;
        case 3:
            TRKSuppAccessFile(TAdPlayerLoadGC__load_request_slots[request_channel].f54);
            break;
        case 5:
            TAdPlayerLoadGC__sub_803F2240(TAdPlayerLoadGC__load_request_slots[request_channel].f54);
            break;
        case 4:
            TAdPlayerLoadGC__sub_803F2610(TAdPlayerLoadGC__load_request_slots[request_channel].f54);
            break;
        case 6:
            TAdPlayerLoadGC::update_card_rename(request_channel);
            break;
        case 7:
            TAdPlayerLoadGC::update_card_delete(request_channel);
            break;
        case 8:
            TAdPlayerLoadGC::step_set_attributes(request_channel);
            break;
        case 9:
            TAdPlayerLoadGC__sub_803F1908(request_channel);
            break;
        case 0:
        default:
            break;
        }
    }
    lbl_805D7944--;
    return 0;
}
#pragma pop

s32 TAdPlayerLoadGC__sub_803F31BC(void) {
    if (lbl_805D7940 == 0) {
        return -1;
    }
    return 0;
}

#pragma push
// Native initialization keeps an array-index induction variable instead of a
// walking pointer; this also preserves the separate zero-valued field registers.
#pragma opt_strength_reduction off
s32 TAdPlayerLoadGC__sub_803F31D8(void *arg0) {
    s32 i;

    lbl_805D7954 = lbl_805E10E8;
    if (lbl_805D7940 > 0) {
        return -1;
    }
    if (arg0 == NULL) {
        return -2;
    }
    CARDInit();
    for (i = 0; i < 2; i++) {
        ((CardInfo_803F31D8 *)lbl_805A5ED0)[i].state = -3;
        ((CardInfo_803F31D8 *)lbl_805A5ED0)[i].f4 = 0;
        ((CardInfo_803F31D8 *)lbl_805A5ED0)[i].sector_size = 0;
        TAdPlayerLoadGC::reset_slot_entry(i);
    }
    lbl_805D7960 = arg0;
    lbl_805D7948 = NULL;
    lbl_805D794C = NULL;
    lbl_805D7940 = 1;
    memset(lbl_805A29B0, 0, 0x3520);
    return 0;
}

#pragma pop
void TAdPlayerLoadGC::reset_slot_entry(s32 arg0) {
    u8 *temp_r30;
    temp_r30 = (u8 *)TAdPlayerLoadGC__load_request_slots + (arg0 * 0x68);
    *(s32 *)((s8 *)temp_r30 + 0) = 0;
    memset(temp_r30 + 4, 0, 0x20);
    memset(temp_r30 + 0x24, 0, 0x20);
    *(s32 *)((s8 *)temp_r30 + 0x44) = 0;
    *(s32 *)((s8 *)temp_r30 + 0x48) = 0;
    *(s32 *)((s8 *)temp_r30 + 0x4C) = 0;
    *(s32 *)((s8 *)temp_r30 + 0x50) = 0;
    *(s32 *)((s8 *)temp_r30 + 0x54) = -1;
    *(s32 *)((s8 *)temp_r30 + 0x58) = 0;
    *(s32 *)((s8 *)temp_r30 + 0x5C) = 0;
}

s32 TAdPlayerLoadGC::close_card_slot(s32 arg0) {
    S_803F3328 *s;
    s32 ret;
    if (arg0 >= 0 && arg0 < 0x64) {
        s = &lbl_805A29B0[arg0];
        ret = CARDClose(&s->card);
        memset(s, 0, 0x88);
        s->state = 2;
    }
    return ret;
}

}
