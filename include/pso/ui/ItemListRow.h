#ifndef PSO_UI_ITEMLISTROW_H
#define PSO_UI_ITEMLISTROW_H

#include "types.h"
#include "pso/misc/TWindowDrawContext.h"

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

// The item-list window is the draw context. Its x/y/width sit on inner_x/inner_y/inner_w,
// visible is open_tick, and text_clip/clip_bottom are the two clip edges.
struct ItemListWindowView : TWindowDrawContext
{
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
