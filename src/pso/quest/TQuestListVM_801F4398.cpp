#include "types.h"
#include "pso/quest/TQuestListVMData.h"
#include "pso/misc/TQuestListOnline.h"
#include "pso/quest/TQuestListVM.h"
int TQuestListVM::get_data() {  return (s32)TQuestListVM__quest_data_output_cursor; }

    extern int online_quest_dat_buffer;
int TQuestListOnline::get_quest_list_flag() {  return online_quest_dat_buffer; }
