#include "types.h"
#include "pso/system/Adxf.h"
#include "pso/unk/TLobby_800FA2A0.h"
#include "pso/unk/text_803CC294.h"
#include "pso/unk/TLobby.h"

extern "C" {

s32 ADXF_Open(void *, int);
s32 ADXF_GetFsizeByte(void *);
u8 *alloc_from_heap__6TLobbyFPv(s32);
u8 *link_into_list__6TLobbyFv();
s32 strncpy(void *, void *, int);

s32 create_named_entry__6TLobbyFiiUiiPv(s32 name, s32 arg1, u32 arg2, void *src, void **arg4) {
    u8 *var_r31;
    s32 temp_r3;

    if (arg4 != NULL) {
        *arg4 = NULL;
    }
    temp_r3 = ADXF_Open((void *)name, 0);
    if (temp_r3 == 0) {
        return -2;
    }
    var_r31 = alloc_from_heap__6TLobbyFPv(0x68);
    if (var_r31 != NULL) {
        var_r31 = link_into_list__6TLobbyFv();
    }
    strncpy(var_r31 + 8, (void *)name, 0x20);
    *(s32 *)((s8 *)var_r31 + 0) = 1;
    *(s32 *)((s8 *)var_r31 + 0x28) = arg1;
    *(s32 *)((s8 *)var_r31 + 0x2C) = ADXF_GetFsizeByte((void *)temp_r3);
    *(s32 *)((s8 *)var_r31 + 0x30) = ADXF_GetFsizeSct((u8 *)temp_r3);
    ADXF_Close((AdxfHandle *)temp_r3);
    *(s32 *)((s8 *)var_r31 + 0x34) = 0;
    *(u32 *)((s8 *)var_r31 + 0x40) = arg2;
    if (arg2 != 0U) {
        move_words((void *)(var_r31 + 0x44), (const void *)(u32 *)src, 8);
    }
    if (arg4 != NULL) {
        *arg4 = var_r31;
    }
    return *(s32 *)((s8 *)var_r31 + 0x2C);
}

}
