#ifndef PSO_UI_ITEMLISTROW_H
#define PSO_UI_ITEMLISTROW_H

#include "types.h"

struct TWindowDrawContext;

struct ItemListRow
{
  u16 flags;
  u8 pad2[6];
  f32 x;
  f32 y;
  u8 pad10[4];
  f32 height;
  s32 item;
  u8 status_icon;
  u8 category_icon;
  u8 pad1e[2];
  s32 label;
  s32 suffix;
  s32 status_style;
  s32 category_style;
  s32 style;
  s32 suffix_style;
};

struct ItemListWindowView
{
  u8 pad0[0x10];
  f32 x;
  f32 y;
  f32 width;
  u8 pad1c[0x14];
  s32 visible;
  u8 pad34[4];
  f32 depth;
  u8 pad3c[4];
  f32 clip_top;
  f32 text_clip;
  f32 clip_bottom;
};

struct ItemListPosition
{
  f32 x;
  f32 y;
};

#include <stddef.h>
typedef char ItemListRow_size[sizeof(ItemListRow) == 0x38 ? 1 : -1];
typedef char ItemListRow_icons_offset[offsetof(ItemListRow, status_icon) == 0x1C ? 1 : -1];
typedef char ItemListRow_label_offset[offsetof(ItemListRow, label) == 0x20 ? 1 : -1];
typedef char ItemListWindow_clip_offset[offsetof(ItemListWindowView, clip_top) == 0x40 ? 1 : -1];

void draw_item_list_row(ItemListRow* row, TWindowDrawContext* window);

#endif
