#ifndef PSO_QUEST_TQUESTLISTVMDATA_H
#define PSO_QUEST_TQUESTLISTVMDATA_H

#include "types.h"

class TQuestListVM;
struct QuestListWindowSize {
    f32 width;
    f32 height;
};

// Existing exported names are retained across source and original-object users.
// These are shared storage declarations, not a Quest class/layout migration.
extern "C" {
extern const char lbl_8044BEE8[11];
extern const char lbl_8044BEF4[13];
extern const char lbl_8044BF04[13];
extern const char lbl_8044BF14[10];
extern const char TQuestListVM__data_8044BF20[14];
extern const char TQuestListVM__class_name_string[13];
extern const QuestListWindowSize lbl_8044BF40;
extern const QuestListWindowSize lbl_8044BF48;
extern const char lbl_8044BF50[7];
extern const char *TQuestListVM__class_name;
extern u8 *TQuestListVM__decrypted_quest_buffer;
extern u32 TQuestListVM__decompression_capacity;
extern u8 *TQuestListVM__quest_data_output_cursor;
extern u32 TQuestListVM__quest_decrypt_result_size;
extern TQuestListVM *quest_list_vm_instance;
extern const s32 lbl_805DC6B0;
extern const s32 lbl_805DC6B4;
}
#endif
