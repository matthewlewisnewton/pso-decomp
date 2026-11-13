#include "pso/system/NinjaTypes.h"
#include "pso/protocol/protocol_types.h"
#include "types.h"
#include "pso/boss/TBoss8Dragon_802FDDD4.h"
#include "pso/misc/TLobby_801E43E4.h"
#include "pso/system/byteswap.h"
#include "pso/boss/TBoss8Dragon.h"

extern "C" {

void copy_model_node(u8 *, u8 *);
NJS_OBJECT *clone_node_tree__12TBoss8DragonFPvPvi(NJS_OBJECT *src, NJS_OBJECT *dst, void *model);
extern f32 lbl_805D6980;
extern f32 lbl_805D6984;
extern f32 lbl_805D69C0;
extern f32 lbl_805D9E80;
extern f32 TBoss8Dragon__data_805DEDC8;
extern f32 lbl_805DEE40;

NJS_OBJECT *clone_node_tree__12TBoss8DragonFPvPvi(NJS_OBJECT *src, NJS_OBJECT *dst, void *model) {
    NJS_OBJECT *cur = dst;
    dst = dst + 1;
    copy_model_node((u8 *)cur, (u8 *)src);
    cur->model = model;
    if (src->child != NULL) {
        cur->child = dst;
        dst = clone_node_tree__12TBoss8DragonFPvPvi(src->child, dst, model);
    }
    if (src->sibling != NULL) {
        cur->sibling = dst;
        dst = clone_node_tree__12TBoss8DragonFPvPvi(src->sibling, dst, model);
    }
    return dst;
}

void TBoss8Dragon::apply_poison_status() {  }
void TBoss8Dragon::apply_paralysis() {  }
void TBoss8Dragon::apply_slow_status() {  }
void TBoss8Dragon::apply_confusion_status() {  }
void TBoss8Dragon::apply_movement_ailment(s32) {  }
void TBoss8Dragon::apply_shock_status() {  }
void TBoss8Dragon::clear_harmful_statuses() {  }
void TBoss8Dragon::send_swapped_packet() { bswap_packet(); send_subcommand((u8 *)this); }
void TBoss8Dragon::bswap_packet() { ((G_ClientIDHeader *)this)->bswap(); bswap_16((u16 *)((char*)this + 0x4)); bswap_16((u16 *)((char*)this + 0x6)); bswap_32((u32 *)((char*)this + 0x8)); }
}

void build_6xA8_gol_dragon_boss_actions(void* p) { *(u8*)((char*)p + 0x0) = 168; *(u8*)((char*)p + 0x1) = 6; }

void TBoss8Dragon__sub_802FDF10(void) {
    f32 temp_f1;

    temp_f1 = TBoss8Dragon__data_805DEDC8 * lbl_805D9E80;
    lbl_805D6980 = temp_f1;
    lbl_805D6984 = lbl_805DEE40 * lbl_805D9E80;
    lbl_805D69C0 = temp_f1;
}

__declspec(section ".ctors") static void *const __sinit_TBoss8Dragon_802FDDD4_cpp_ref = (void *)TBoss8Dragon__sub_802FDF10;
