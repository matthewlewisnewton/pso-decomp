#include "pso/system/ArrayAllocation.h"
#include "types.h"
#include "pso/TSetManager.h"
#include "pso/THeap.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TScene.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/map/FloorArea.h"
#include "pso/misc/TLobby_800F9DA0.h"

struct Dst_8020DEE4 { u16 id; s16 v; u8 pad[4]; };

struct SrcA_8020DEE4 { u8 pad0[2]; s16 v; u8 pad4[4]; u16 id; u8 padA[0x44 - 0xA]; };

struct SrcB_8020DEE4 { u8 pad0[2]; s16 v; u8 pad4[6]; u16 id; u8 padC[0x48 - 0xC]; };

struct Area_8020DEE4 { s32 countA; s32 countB; u8 pad8[8]; Dst_8020DEE4 *a; Dst_8020DEE4 *b; };

struct Vec3_8020DB44 { s32 a, b, c; };

struct A_8020DBCC { s16 a; s16 b; };

struct B_8020DBCC { s16 a; s16 b; s16 c; s16 d; s16 e; s16 f; };

struct Room_8020D9A0 { u8 pad0[8]; s32 name; };

struct Grp_8020D9A0 { Room_8020D9A0 *room; s32 count; };

struct Map_8020D9A0 { Grp_8020D9A0 *grp; s32 count; };

struct Rec_8020D9A0 { u8 pad0[2]; s16 f2; s16 f4; u8 pad6[2]; u16 f8; u8 padA[0x3A]; };

// Row of a floor object/enemy set as stored in the full set data buffers
// TLobby__data_805D6138 / TLobby__data_805D613C. The type field doubles as the
// empty-slot marker: a set row is unused while its type is -1.
struct FloorObjectSetRow { s16 type; u8 pad02[0x44 - 2]; };

struct FloorEnemySetRow { s16 type; u8 pad02[0x48 - 2]; };

// Per-floor row table for one floor: the loaded object/enemy set row counts
// (both are -1 for a floor with no set), the placement flags recording which
// sets were applied, and the heap-allocated processed row lists.
struct LobbyFloorRows {
    s32 objects;
    s32 enemies;
    u32 objectPlacement;
    u32 enemyPlacement;
    void *objectRows;
    void *enemyRows;
};

// Per-floor archive pool entry pair holding the raw object/enemy set data
// (TLobby__data_80513A40, the first two words per floor).
struct LobbyPoolEntry { void *objects; void *enemies; };

// The lobby population tables are one contiguous block: a pool entry pair per
// floor, the per-floor row tables, then the per-floor set row counts. The
// original translation unit defined every table together and reaches the later
// tables as offsets from TLobby__data_80513A40, so this overlay declares the
// shared layout: pool_entries is TLobby__data_80513A40, floors is
// TLobby__floor_enemy_group_table, object_row_counts is TLobby__data_80513C80,
// enemy_row_counts is TLobby__data_80513CC8 and data_80513D10 is
// TLobby__data_80513D10.
struct LobbyPopulationTables {
    LobbyPoolEntry pool_entries[18];
    LobbyFloorRows floors[18];
    s32 object_row_counts[18];
    s32 enemy_row_counts[18];
    u8 data_80513D10[0x24];
};

typedef char LobbyPoolEntry_size[sizeof(LobbyPoolEntry) == 8 ? 1 : -1];
typedef char LobbyPopulationTables_floors_offset[(offsetof(LobbyPopulationTables, floors) == 0x90) ? 1 : -1];
typedef char LobbyPopulationTables_object_row_counts_offset[(offsetof(LobbyPopulationTables, object_row_counts) == 0x240) ? 1 : -1];
typedef char LobbyPopulationTables_enemy_row_counts_offset[(offsetof(LobbyPopulationTables, enemy_row_counts) == 0x288) ? 1 : -1];
typedef char LobbyPopulationTables_data_80513D10_offset[(offsetof(LobbyPopulationTables, data_80513D10) == 0x2D0) ? 1 : -1];

extern "C" {
void TLobby__sub_8020D94C(void);
extern s16 TLobby__data_805D6134;
s32 get_current_floor(void);
extern Area_8020DEE4 TLobby__floor_enemy_group_table[];
extern SrcA_8020DEE4 *TLobby__data_805D610C;
extern SrcB_8020DEE4 *TLobby__data_805D6114;
void depart_floor_population(int unused);
s32 lookup_scene_object__6TLobbyFPv(s32, void *);
void *memset(void *, int, unsigned long);
extern A_8020DBCC *quest_object_entries;
extern B_8020DBCC *TLobby__data_805D6144;
s32 replace_file_extension__6TLobbyFPvPvPv(char *arg0, char *arg1, char *arg2);
}
void arrive_floor_population(void);
extern s32 lbl_805D60F8;
extern s32 TLobby__data_805D60FC;
extern u32 TLobby__data_805D611C;
extern s32 TLobby__data_805D6120;
extern u32 TLobby__data_805D6124;
extern s32 TLobby__data_805D6128;
void swap_object_row_endian(void *);
extern char lbl_8044BC24[];
extern char lbl_8044BC2C[];
extern Map_8020D9A0 *TLobby__data_805D6068;
s32 load_map_decoration_rows(s32 map, s32 grp, s32 room);
extern "C" {
void* TSetManager__ct(void*, s32);
void* __nw__7TObjectFUl(u32);

extern s32 tl_02;
extern u32 TLobby__data_805D6104;
extern THeap *TLobby__data_805D6108;
extern FloorObjectSetRow *TLobby__data_805D6138;
extern FloorEnemySetRow *TLobby__data_805D613C;
extern s32 TLobby__data_805D6148;
extern s32 TLobby__data_805D614C;
extern s32 lbl_805D6100;
extern LobbyPopulationTables TLobby__data_80513A40;
void archive_pool_free(u32, void *);
void TLobby__sub_8020DC78(void);


void TSetManager::create() {
    void* obj = __nw__7TObjectFUl(0x20);
    if (obj != 0) {
        TSetManager__ct(obj, tl_02);
    }
}

void TLobby__sub_8020D94C(void) {
    if ((u32) TLobby__data_805D611C != 0U) {
        ::operator delete[]((void*)TLobby__data_805D611C);
        TLobby__data_805D611C = 0U;
        TLobby__data_805D6120 = 0;
    }
    if ((u32) TLobby__data_805D6124 != 0U) {
        ::operator delete[]((void*)TLobby__data_805D6124);
        TLobby__data_805D6124 = 0U;
        TLobby__data_805D6128 = 0;
    }
}
}

s32 load_map_decoration_rows(s32 map, s32 grp, s32 room) {
    Room_8020D9A0 *r;
    s32 i;
    s32 size;
    char path[0x20];
    if (TLobby__data_805D6068[map].grp == NULL || TLobby__data_805D6068[map].count - 1 < grp) {
        return 0;
    }
    r = TLobby__data_805D6068[map].grp[grp].room;
    if (r == NULL || TLobby__data_805D6068[map].grp[grp].count - 1 < room) {
        return 0;
    }
    if (TLobby::is_online_ready() != 0) {
        replace_file_extension__6TLobbyFPvPvPv((char *)path, (char *)r->name, (char *)lbl_8044BC24);
    } else {
        replace_file_extension__6TLobbyFPvPvPv((char *)path, (char *)r->name, (char *)lbl_8044BC2C);
    }
    size = ((TScene *)path)->update_lobby_scene();
    if (size < 0) {
        return 0;
    }
    TLobby__data_805D6120 = (u32)size / 0x44;
    if ((TLobby__data_805D611C = (u32)::operator new[](TLobby__data_805D6120 * 0x44)) == 0) {
        return 0;
    }
    read_disc_file(path, (void *)TLobby__data_805D611C);
    for (i = 0; i < TLobby__data_805D6120; i++) {
        swap_object_row_endian(&((Rec_8020D9A0 *)TLobby__data_805D611C)[i]);
        ((Rec_8020D9A0 *)TLobby__data_805D611C)[i].f2 = 0;
        ((Rec_8020D9A0 *)TLobby__data_805D611C)[i].f8 = 0xFFFF;
        ((Rec_8020D9A0 *)TLobby__data_805D611C)[i].f4 = -1;
    }
    return 1;
}

#pragma push
#pragma scheduling off

void TLobby::clear_floor_flags_and_depart() {
    s32 unused;
    TLobby__sub_8020D94C();
    unused = TLobby__data_805D6134 & ~8;
    TLobby__data_805D6134 = unused;
    TLobby__data_805D6134 &= ~16;
    depart_floor_population(unused);
}
#pragma pop

void TLobby::setup_floor_decorations() {
    Vec3_8020DB44 v;
    s32 t;
    s32 r;
    arrive_floor_population();
    (*(s32 *)&TLobby__data_805D611C) = 0;
    TLobby__data_805D6134 &= ~8;
    (*(s32 *)&TLobby__data_805D6124) = 0;
    TLobby__data_805D6120 = 0;
    TLobby__data_805D6128 = 0;
    TLobby__data_805D6134 &= ~16;
    lbl_805D60F8 = get_current_floor_area();
    r = get_current_floor();
    TLobby__data_805D60FC = r;
    if (lookup_scene_object__6TLobbyFPv(r, &v) != 0) {
        load_map_decoration_rows(v.a, v.b, v.c);
        return;
    }
    lbl_805D60F8 = -1;
}

void TLobby::reset_id_tables() {
    s32 i;
    s32 n = 0;
    if (quest_object_entries != 0) {
        memset(quest_object_entries, 0, 0x2E80);
        for (i = 0; i < 0xBA0; i++) {
            s16 t = n + 0x100;
            n++;
            quest_object_entries[i].b = t;
        }
    }
    if (TLobby__data_805D6144 != 0) {
        memset(TLobby__data_805D6144, 0, 0x87C0);
        for (i = 0; i < 0xB50; i++) {
            s16 t = n + 0x100;
            n++;
            TLobby__data_805D6144[i].c = t;
        }
    }
}

void TLobby__sub_8020DC78(void) {
    LobbyPopulationTables *base = &TLobby__data_80513A40;
    LobbyPoolEntry (LobbyPopulationTables::*enemy_member)[18];
    LobbyPoolEntry (LobbyPopulationTables::*object_member)[18];
    s32 i;
    s32 j;
    s32 n;
    TLobby__data_805D6134 = 0;
    if (TLobby__data_805D6138 != NULL) {
        memset(TLobby__data_805D6138, 0, 0x31680);
        for (i = 0; i < 0xBA0; i++) {
            TLobby__data_805D6138[i].type = -1;
        }
    }
    if (TLobby__data_805D613C != NULL) {
        memset(TLobby__data_805D613C, 0, 0x19740);
        for (i = 0; i < 0x5A8; i++) {
            TLobby__data_805D613C[i].type = -1;
        }
    }
    memset(base->object_row_counts, 0, 0x48);
    memset(base->enemy_row_counts, 0, 0x48);
    memset(base->data_80513D10, 0, 0x24);
    n = 0;
    if (quest_object_entries != 0) {
        memset(quest_object_entries, 0, 0x2E80);
        for (i = 0; i < 0xBA0; i++) {
            s16 t = n + 0x100;
            n++;
            quest_object_entries[i].b = t;
        }
    }
    if (TLobby__data_805D6144 != 0) {
        memset(TLobby__data_805D6144, 0, 0x87C0);
        for (i = 0; i < 0xB50; i++) {
            s16 t = n + 0x100;
            n++;
            TLobby__data_805D6144[i].c = t;
        }
    }
    TLobby__data_805D6148 = 0;
    TLobby__data_805D614C = 0;
    TLobby__data_805D611C = 0;
    TLobby__data_805D6124 = 0;
    TLobby__data_805D6120 = 0;
    TLobby__data_805D6128 = 0;
    lbl_805D6100 = 0;
    // pool_entries is at offset 0, so `base->pool_entries` is the anchor
    // register itself. Applying a pointer-to-member is the address calculation
    // MWCC keeps as `addi rX, rBase, 0`.
    enemy_member = &LobbyPopulationTables::pool_entries;
    {
        LobbyPoolEntry *enemy_pool = base->*enemy_member;
        for (j = 17; j >= 0; j--) {
            if (enemy_pool[j].enemies != NULL) {
                archive_pool_free(TLobby__data_805D6104, enemy_pool[j].enemies);
                enemy_pool[j].enemies = NULL;
            }
        }
    }
    object_member = &LobbyPopulationTables::pool_entries;
    {
        LobbyPoolEntry *object_pool = base->*object_member;
        for (j = 17; j >= 0; j--) {
            if (object_pool[j].objects != NULL) {
                archive_pool_free(TLobby__data_805D6104, object_pool[j].objects);
                object_pool[j].objects = NULL;
            }
        }
    }
    {
        LobbyFloorRows *rows = base->floors;
        for (j = 17; j >= 0; j--) {
            if (rows[j].enemyRows != NULL) {
                TLobby__data_805D6108->heap_free(rows[j].enemyRows);
                rows[j].enemyRows = NULL;
            }
        }
    }
    {
        LobbyFloorRows *rows = base->floors;
        for (j = 17; j >= 0; j--) {
            if (rows[j].objectRows != NULL) {
                TLobby__data_805D6108->heap_free(rows[j].objectRows);
                rows[j].objectRows = NULL;
            }
        }
    }
    memset(base->floors, 0, 0x1B0);
}

void depart_floor_population(int unused) {
    Area_8020DEE4 *area = &TLobby__floor_enemy_group_table[get_current_floor()];
    if (TLobby__data_805D610C != 0) {
        SrcA_8020DEE4 *s = TLobby__data_805D610C;
        Dst_8020DEE4 *d = area->a;
        s32 i;
        for (i = 0; i < area->countA; i++, s++, d++) {
            if (s->id == d->id) {
                d->v = s->v;
            }
        }
    }
    if (TLobby__data_805D6114 != 0) {
        SrcB_8020DEE4 *s = TLobby__data_805D6114;
        Dst_8020DEE4 *d = area->b;
        s32 i;
        for (i = 0; i < area->countB; i++, s++, d++) {
            if (s->id == d->id) {
                d->v = s->v;
            }
        }
    }
    if (TLobby__data_805D6114 != 0) {
        TAdSinglePlyChrSelectGC::safe_free((u32)TLobby__data_805D6114);
        TLobby__data_805D6114 = 0;
    }
    if (TLobby__data_805D610C != 0) {
        TAdSinglePlyChrSelectGC::safe_free((u32)TLobby__data_805D610C);
        TLobby__data_805D610C = 0;
    }
}
