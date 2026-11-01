// Scoped data-only extraction from zeroz41/pso-decomp ddca6f412205abd69aaf86d1378f95d23152d6f4.
// Original upstream author: zeroz. This logical file is not an original-TU filename claim.
// Initial import only: fork symbol/type/consumer and split integration follows separately.
#include "types.h"

class TQuestListVM;

// A window's width and height.
struct WindowSize {
    f32 width;
    f32 height;
};

extern const char quest_file_prefix[] = "PSO______0";
extern const char quest_file_99_name[] = "PSO______099";
extern const s32 quest_file_first_index = 4;
extern const s32 quest_file_index_limit = 0x5F;

static const char download_list_title_jp[] = "\x83\x5F\x83\x45\x83\x93\x83\x8D\x81\x5B\x83\x68"; // ダウンロード
static const char download_list_title[] = "Down Load";
static const char tmp_buf_owner_name[] = "quest_vm_load";
const char *TQuestListVM_class_name = "TQuestListVM";
static const WindowSize description_window_size = {228.0f, 184.0f};
static const WindowSize detail_window_size = {332.0f, 210.0f};
static const char quest_file_name_format[] = "%s%02d";

u8 *decrypted_quest_buffer;
u32 decompression_capacity;
u8 *quest_data_output_cursor;
u32 quest_decrypt_result_size;
TQuestListVM *quest_list_vm_instance;

