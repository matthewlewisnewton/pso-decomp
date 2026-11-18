#include "types.h"
#include "pso/unk/text_803DA798.h"
#include "pso/player/TObjPlayer_803DF7A8.h"
#include "pso/player/TObjPlayer.h"

typedef struct TexObj_803E1D90 { u32 dummy[8]; } TexObj_803E1D90;

typedef struct TexHdr_803E1D90 {
    u32 f0;
    s32 format;
    u32 f8;
    u32 fC;
    u32 width;
    u32 height;
    u32 f18;
    u32 flags;
    void *image;
} TexHdr_803E1D90;

typedef struct TexInfo_803E1D90 { u32 f0; u32 f4; u32 tlut; TexHdr_803E1D90 *hdr; } TexInfo_803E1D90;

typedef struct TexEnt_803E1D90 { u32 f0; u32 f4; TexInfo_803E1D90 *info; } TexEnt_803E1D90;

typedef struct TexList_803E1D90 { TexEnt_803E1D90 *ents; } TexList_803E1D90;

typedef struct Ctx_803E1D90 { u8 pad[0x20]; TexList_803E1D90 *list; } Ctx_803E1D90;

extern "C" {
s32 GXLoadPosMtxImm(void *, int);
extern s32 current_matrix;
extern s32 tex_matrix_id_table[];
void GXLoadTexMtxImm(void *mtx, u32 id, s32 type);
void Dolphin_GXInitTexObj(TexObj_803E1D90 *, void *, u16, u16, s32, s32, s32, u8);
void GXInitTexObjCI(TexObj_803E1D90 *, void *, u16, u16, s32, s32, s32, u8, u32);
void GXLoadTexObj(TexObj_803E1D90 *, s32);
extern s32 list_texture_map_table[];
extern TexObj_803E1D90 list_texture_tex_obj;
extern Ctx_803E1D90 *current_render_context;
extern s32 gx_pos_mtx_index_table[10];
}

#pragma push
#pragma scheduling off
void load_current_pos_matrix(s32 arg0) {
    GXLoadPosMtxImm((void *)current_matrix, gx_pos_mtx_index_table[arg0]);
}
#pragma pop


#pragma push
#pragma scheduling off
void load_current_tex_matrix(s32 i) {
    GXLoadTexMtxImm((void *)current_matrix, tex_matrix_id_table[i], 0);
}
#pragma pop


void load_list_texture(s32 idx, s32 wrapS, s32 wrapT, s32 map) {
    TexInfo_803E1D90 *info = current_render_context->list->ents[idx].info;
    TexHdr_803E1D90 *hdr = info->hdr;
    u32 flags = hdr->flags;
    u8 mip;
    if (flags & 0x80000000) {
        mip = 1;
    } else {
        mip = 0;
    }
    if (flags & 0x8000) {
        GXInitTexObjCI(&list_texture_tex_obj, hdr->image, hdr->width, hdr->height, hdr->format, wrapS, wrapT, mip, info->tlut);
    } else {
        Dolphin_GXInitTexObj(&list_texture_tex_obj, hdr->image, hdr->width, hdr->height, hdr->format, wrapS, wrapT, mip);
    }
    GXLoadTexObj(&list_texture_tex_obj, list_texture_map_table[map]);
}

extern "C" {
s32 gx_pos_mtx_index_table[10] = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27};
s32 tex_matrix_id_table[10] = {30, 33, 36, 39, 42, 45, 48, 51, 54, 57};
s32 list_texture_map_table[10] = {0, 1, 2, 3, 4, 5, 6, 7, 0xFF};
TexObj_803E1D90 list_texture_tex_obj;
}
