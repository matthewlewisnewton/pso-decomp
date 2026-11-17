#include "types.h"
#include "pso/misc/TLanguage_801E4874.h"
#include "pso/unk/text_800F9B84.h"
#include "pso/unk/text_8014B8A4.h"
#include "pso/npc/TObjNpcNFM01.h"
#include "pso/npc/TUnk_804A9F50.h"
#include "pso/npc/TObjNpcNFW00.h"
#include "pso/misc/TLobby.h"
#include "pso/npc/TObjNpcBase.h"
#include "pso/npc/TObjNpcLappy.h"
#include "pso/player/TObjPlayer.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct RecoveredGlobal_8014CBA8___vt__12TObjNpcNFM01 {
    s32 value;
    u8 remaining[0x174];
};

extern "C" {
extern const char lbl_8043FD48[] = "TObjNpcNFM01";
extern const char *TObjNpcNFM01__name;
extern const char lbl_8043FD58[] = "npc_h01_data.rel";
extern const char lbl_8043FD6C[] = "n_h01_e_body.gvm";
extern s32 __vt__12TObjNpcNFM01[];
void release_texture_list(void*);
void *__ct__11TObjControlFP7TObject(void *, void *);
void __dl__7TObjectFPv(void *);
void *__nw__7TObjectFUl(int);

void TObjNpcNFM01::free_resources() {
    if ((u32) TObjNpcNFM01__texture_handle != 0U) {
        release_texture_list((void*)TObjNpcNFM01__texture_handle);
        TAdSinglePlyChrSelectGC::safe_free((void *)TObjNpcNFM01__texture_handle);
        TObjNpcNFM01__texture_handle = 0U;
    }
    if ((u32) TObjNpcNFM01__model_object != 0U) {
        TLobby::free_nodes_with_id((u32)((void*)TObjNpcNFM01__model_object));
        TObjNpcNFM01__model_object = 0U;
    }
}
void TObjNpcNFM01::load_resources() {
    TObjNpcNFM01__model_object = (s32 *)create_named_object((s32)lbl_8043FD58);
    TObjNpcNFM01__texture_handle = load_gvm_texture_file(lbl_8043FD6C);
}

void *__dt__12TObjNpcNFM01Fv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__12TObjNpcNFM01;
        ((TUnk_804A9F50 *)arg0)->destroy_npc_lappy_base(0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

extern void *tl_04;

typedef char RecoveredGlobal_8014CBA8___vt__12TObjNpcNFM01_size[sizeof(RecoveredGlobal_8014CBA8___vt__12TObjNpcNFM01) == 0x178 ? 1 : -1];
u8 *TObjNpcNFM01__ct(u8 *player, s32 arg1, s32 arg2) {
    construct_male_npc_base((player));
    *(s32 **)((s8 *)player + 0x18) = &(*(RecoveredGlobal_8014CBA8___vt__12TObjNpcNFM01 *)&__vt__12TObjNpcNFM01).value;
    *(s32 *)((s8 *)player + 0) = (s32) TObjNpcNFM01__name;
    ((TObjNpcNFM01 *)(player))->apply_set_data((void *)arg2);
    ((TObjChara *)player)->initialize_position_copies();
    *(s32 *)((s8 *)player + 0x34) = (s32) *TObjNpcNFM01__model_object;
    ((TObjNpcNFM01 *)player)->texlist = (s32) TObjNpcNFM01__texture_handle;
    ((TObjNpcBase *)player)->setup_common();
    return player;
}

void * TObjNpcNFW00__create(void *arg0) {
    void *o;
    void *o2;
    o = __nw__7TObjectFUl(0x20);
    if (o != NULL) {
        o = __ct__11TObjControlFP7TObject(o, tl_04);
    }
    o2 = __nw__7TObjectFUl(0x3B8);
    if (o2 != NULL) {
        o2 = TObjNpcNFW00__ct((u8 *)o2, (s32)o, (s32)arg0);
    }
    return o2;
}

}
