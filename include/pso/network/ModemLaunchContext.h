#ifndef PSO_NETWORK_MODEMLAUNCHCONTEXT_H
#define PSO_NETWORK_MODEMLAUNCHCONTEXT_H

#include "types.h"
#include <stddef.h>

// Views of the reserved launch record at 0x80003100. Unknown spans stay opaque.
struct ModemLaunchOptions {
    u8 unknown_000[4];
    char text[0xF0];
    s32 field_0f4;
    u8 unknown_0f8[0x44];
    s8 field_13c;
    s8 field_13d;
    u8 unknown_13e[0x82];
    s16 field_1c0;
    s16 field_1c2;
    u8 unknown_1c4[0x78];
    s8 field_23c;
    s8 field_23d;
    s16 field_23e;
    u8 unknown_240[0x120];
    s8 field_360;
    u8 unknown_361[0x49F];
};

struct ModemLaunchParameters {
    s8 field_00;
    u8 unknown_01[0x8B];
    char name[5][0x100];
};

struct ModemLaunchData {
    u32 signature;
    u32 flags;
    u8 unknown_08[0xC];
    u32 argument_size;
    u32 field_18;
    u32 options_size;
    u8 unknown_20[0x6000];
    u8 arguments[0x800];
    u8 region_6820[0x800];
    ModemLaunchOptions options;
    ModemLaunchParameters parameters;
    u8 unknown_7dac[0x254];
};

struct ModemLaunchContext {
    char path[0x100];
    s32 field_100;
    s32 field_104;
    u32 payload_size;
    u8 unknown_10c[4];
    u8 data[0x8000];
};

typedef char ModemLaunchOptionsFields[
    offsetof(ModemLaunchOptions, field_0f4) == 0xF4 &&
    offsetof(ModemLaunchOptions, field_13c) == 0x13C &&
    offsetof(ModemLaunchOptions, field_13d) == 0x13D &&
    offsetof(ModemLaunchOptions, field_1c0) == 0x1C0 &&
    offsetof(ModemLaunchOptions, field_1c2) == 0x1C2 &&
    offsetof(ModemLaunchOptions, field_23c) == 0x23C &&
    offsetof(ModemLaunchOptions, field_23d) == 0x23D &&
    offsetof(ModemLaunchOptions, field_23e) == 0x23E &&
    offsetof(ModemLaunchOptions, field_360) == 0x360 ? 1 : -1];
typedef char ModemLaunchOptionsSize[sizeof(ModemLaunchOptions) == 0x800 ? 1 : -1];
typedef char ModemLaunchParametersNames[offsetof(ModemLaunchParameters, name) == 0x8C ? 1 : -1];
typedef char ModemLaunchDataSize[sizeof(ModemLaunchData) == 0x8000 ? 1 : -1];
typedef char ModemLaunchArguments[offsetof(ModemLaunchData, arguments) == 0x6020 ? 1 : -1];
typedef char ModemLaunchOptionsOffset[offsetof(ModemLaunchData, options) == 0x7020 ? 1 : -1];
typedef char ModemLaunchParametersOffset[offsetof(ModemLaunchData, parameters) == 0x7820 ? 1 : -1];
typedef char ModemLaunchContextData[offsetof(ModemLaunchContext, data) == 0x110 ? 1 : -1];

extern "C" {
extern s32 lbl_805D7CA8;
// Preserve the observed store/read-back and repeated slot loads.
// This qualifies the slot, not the context storage.
extern ModemLaunchContext *volatile lbl_805D7CB0;
extern u32 lbl_805D7CB4;
extern ModemLaunchParameters *lbl_805D7CB8;
extern u8 *lbl_805D7CBC;
extern ModemLaunchData *lbl_805D7CC0;
extern ModemLaunchOptions *lbl_805D7CC4;
}

#endif
