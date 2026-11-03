#ifndef PSO_RENDER_SPRITEDESCRIPTOR_H
#define PSO_RENDER_SPRITEDESCRIPTOR_H

#include "types.h"
#include <stddef.h>

struct SpriteFrame {
    s16 width, height, center_x, center_y;
    s16 u0, v0, u1, v1;
    s16 unknown10, unknown12;
};

struct SpriteDescriptor {
    f32 x, y, unknown08, scale_x, scale_y;
    s32 rotation;
    void *unknown18;
    SpriteFrame *frames;
};

typedef char SpriteFrameSize[(sizeof(SpriteFrame) == 0x14) ? 1 : -1];
typedef char SpriteDescriptorSize[(sizeof(SpriteDescriptor) == 0x20) ? 1 : -1];
typedef char SpriteDescriptorRotation[(offsetof(SpriteDescriptor, rotation) == 0x14) ? 1 : -1];
typedef char SpriteDescriptorPointer[(offsetof(SpriteDescriptor, unknown18) == 0x18) ? 1 : -1];
typedef char SpriteDescriptorFrames[(offsetof(SpriteDescriptor, frames) == 0x1c) ? 1 : -1];

// The descriptor and its frame array are borrowed for the duration of the call.
// The caller must supply a valid frame index.
extern "C" void draw_compass_sprite__10TObjPlayerFlllf(SpriteDescriptor *sprite, s32 index, s32 color, s32 flags, f32 depth);

#endif
