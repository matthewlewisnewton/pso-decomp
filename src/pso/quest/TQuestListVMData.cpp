// Scoped storage extraction from zeroz41/pso-decomp ddca6f412205abd69aaf86d1378f95d23152d6f4.
// The task-10 attributed import is 0556e1669 (scoped checkpoint ee0c46d61636f6dc313ebdb512484de3b79beccf).
// This logical data unit is a later organization, not an original-TU filename claim.
#include "pso/quest/TQuestListVMData.h"

extern "C" {
extern const char lbl_8044BEE8[11] = "PSO______0";
extern const char lbl_8044BEF4[13] = "PSO______099";
extern const char lbl_8044BF04[13] = "\x83\x5F\x83\x45\x83\x93\x83\x8D\x81\x5B\x83\x68"; // ダウンロード
extern const char lbl_8044BF14[10] = "Down Load";
extern const char TQuestListVM__data_8044BF20[14] = "quest_vm_load";
extern const char TQuestListVM__class_name_string[13] = "TQuestListVM";
extern const QuestListWindowSize lbl_8044BF40 = {228.0f, 184.0f};
extern const QuestListWindowSize lbl_8044BF48 = {332.0f, 210.0f};
extern const char lbl_8044BF50[7] = "%s%02d";

const char *TQuestListVM__class_name = TQuestListVM__class_name_string;
u8 *TQuestListVM__decrypted_quest_buffer;
u32 TQuestListVM__decompression_capacity;
u8 *TQuestListVM__quest_data_output_cursor;
u32 TQuestListVM__quest_decrypt_result_size;
TQuestListVM *quest_list_vm_instance;
extern const s32 lbl_805DC6B0 = 4;
extern const s32 lbl_805DC6B4 = 0x5F;
}
