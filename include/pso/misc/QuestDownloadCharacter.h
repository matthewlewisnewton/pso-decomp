#ifndef PSO_MISC_QUESTDOWNLOADCHARACTER_H
#define PSO_MISC_QUESTDOWNLOADCHARACTER_H

#include "types.h"

// Native character codes are halfwords; the single-byte conversion returns a byte.
extern "C" {
s32 TQuestVmDownLoadServer__sub_803E6F98(u16 code);
s32 TQuestVmDownLoadServer__sub_803E7018(u16 code);
// The output must have room for two bytes, even when the caller expects one.
s32 TQuestVmDownLoadServer__sub_803E7098(u8 *output, u16 code);
u16 TQuestVmDownLoadServer__sub_803EC69C(u16 code);
u8 TQuestVmDownLoadServer__sub_803EC8D8(u16 code);
s32 TQuestVmDownLoadServer__sub_803ECC7C(u16 code);
}

#endif
