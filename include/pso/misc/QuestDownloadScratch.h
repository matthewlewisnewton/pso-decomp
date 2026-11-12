#ifndef PSO_QUEST_DOWNLOAD_SCRATCH_H
#define PSO_QUEST_DOWNLOAD_SCRATCH_H

#include "types.h"

struct QuestDownloadDisplayPrefix { char text[12]; };
extern "C" QuestDownloadDisplayPrefix lbl_80596258;

// These bytes provide storage for synchronous conversion and ID-list phases.
// Start the corresponding complete object before its producer writes elements;
// representation-only users may continue to access the enclosing byte array.
extern "C" {
extern u8 quest_download_text_buffer[0x404] ATTRIBUTE_ALIGN(4);
extern u8 lbl_8058DC48[0x50];
extern u8 lbl_8058DC98[0x50];
extern u8 lbl_8058DCE8[0x50];
extern u8 lbl_8058DD38[0x50];
s32 TQuestVmDownLoadServer__sub_803EDF64(const u16 *, s32, u16 *, s32 *);
}
struct QuestDownloadScratchWords { s16 values[0x202]; };
struct QuestDownloadScratchIds { s32 values[0x101]; };
typedef char QuestScratchWords_extent[sizeof(QuestDownloadScratchWords) == 0x404 ? 1 : -1];
typedef char QuestScratchIds_extent[sizeof(QuestDownloadScratchIds) == 0x404 ? 1 : -1];

enum QuestDownloadScratchPlacement { quest_download_scratch_storage };
#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline void *operator new(size_t, void *storage, QuestDownloadScratchPlacement) { return storage; }
#pragma pop

#endif
