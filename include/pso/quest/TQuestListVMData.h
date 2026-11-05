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
extern const char quest_file_prefix[11];
extern const char quest_file_99_name[13];
extern const char download_list_title_jp[13];
extern const char download_list_title[10];
extern const char tmp_buf_owner_name[14];
extern const char TQuestListVM__class_name_string[13];
extern const QuestListWindowSize description_window_size;
extern const QuestListWindowSize detail_window_size;
extern const char quest_file_name_format[7];
extern const char *TQuestListVM_class_name;
extern u8 *decrypted_quest_buffer;
extern u32 decompression_capacity;
extern u8 *quest_data_output_cursor;
extern u32 quest_decrypt_result_size;
extern TQuestListVM *quest_list_vm_instance;
extern const s32 quest_file_first_index;
extern const s32 quest_file_index_limit;
}
#endif
