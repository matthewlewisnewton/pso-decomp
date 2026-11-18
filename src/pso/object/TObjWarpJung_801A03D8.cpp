#include "pso/system/BmlResource.h"
#include "types.h"
#include "pso/object/TObjWarpJung_801A03D8.h"
#include "pso/object/TObjWarpJung.h"

extern "C" {
void free_children__12TObjDoorJungFPv(void *, u16);
extern void *warp_jung_beam_models[];
extern s32 warp_jung_beam_entry_index;
extern s32 lbl_805D5CC0;
s32 scroll_ginja_mesh_uvs(s32, s32, s32, u16, s32);
int draw_ginja_object(void);

    extern int TObjWarpJung__beam_bml_resource;
void TObjWarpJung::render_warp(void* a0) { (int)get_bml_model((BmlResource *)TObjWarpJung__beam_bml_resource, (s32)a0); draw_ginja_object(); }

extern s32 actor_frame_tick;
extern s32 lbl_805D5CB4;
extern s32 warp_jung_beam_mesh_node;
extern s32 lbl_805D5CC4;

s32 TObjWarpJung__sub_801A0404(s32 arg0) {
    s32 i;
    switch (arg0) {
    case 0:
        if (warp_jung_beam_entry_index >= 0) {
            for (i = 0; i < 6; i++) {
                free_children__12TObjDoorJungFPv(warp_jung_beam_models[i], warp_jung_beam_entry_index);
            }
        }
        break;
    case 1:
        if (lbl_805D5CC0 >= 0) {
            for (i = 0; i < 6; i++) {
                free_children__12TObjDoorJungFPv(warp_jung_beam_models[i], lbl_805D5CC0);
            }
        }
        break;
    }
    return 1;
}

s32 TObjWarpJung::update_warp_display() {
    if ((s32) actor_frame_tick != (s32) lbl_805D5CB4) {
        lbl_805D5CB4 = actor_frame_tick;
        if ((s32) lbl_805D5CC4 >= 0) {
            scroll_ginja_mesh_uvs(warp_jung_beam_mesh_node, 0, 5, (u16) lbl_805D5CC4, 1);
            return 1;
        }
    }
    return 0;
}

}
