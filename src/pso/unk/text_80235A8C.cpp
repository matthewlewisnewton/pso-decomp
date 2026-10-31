#include "pso/system/SoundEffect.h"
#include "types.h"
#include "pso/unk/text_80235A8C.h"
#include "pso/unk/TUnk_804CCA78.h"

struct RecoveredGlobal_80235A8C_lbl_804CCA78 { s32 value; u8 remaining[0x14]; };
typedef char RecoveredGlobal_80235A8C_lbl_804CCA78_size[sizeof(RecoveredGlobal_80235A8C_lbl_804CCA78) == 0x18 ? 1 : -1];

extern "C" {
s32 update_technique_slot__10TTecRaFoieFl(int, void *, int);

s32 __ct__7TObjectFP7TObject(void *, void *);
}
extern RecoveredGlobal_80235A8C_lbl_804CCA78 lbl_804CCA78;
u8 *construct_timed_sound_voice(u8 *arg0, s32 arg1, s16 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 handle;
    __ct__7TObjectFP7TObject((void *)arg0, (void *)arg5);
    *(s32 **)((s8 *)arg0 + 0x18) = &lbl_804CCA78.value;
    *(s16 *)((s8 *)arg0 + 0x1C) = arg2;
    ((TUnk_804CCA78 *)arg0)->m_1e = 0;
    *(s32 *)((s8 *)arg0 + 0x20) = arg3;
    ((TUnk_804CCA78 *)arg0)->m_24 = play_sound_effect((s32)((int) (*(s32 *)((s8 *)arg0 + 0x20))), (const Vec *)((void *)arg1), 0, 0);
    handle = ((TUnk_804CCA78 *)arg0)->m_24;
    if ((handle >= 0) && (arg4 != 0)) {
        update_technique_slot__10TTecRaFoieFl((int)handle, (void *)arg4, 0);
    }
    return arg0;
}
