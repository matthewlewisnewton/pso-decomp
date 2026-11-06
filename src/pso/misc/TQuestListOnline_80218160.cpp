#include "types.h"
#include "pso/TShopWindowBase.h"
#include "pso/misc/TQuestListOnline.h"
#include "pso/TProtocol.h"

struct Obj_802181B0 { u8 pad[0x20]; u32 state; };

    extern int TLobby__protocol_instance;
    extern int online_quest_bin_data;
    extern int online_quest_dat_buffer;
    extern int quest_bin_decompressed_size;
    extern int online_quest_list_decompressed_size;
void TQuestListOnline::request_menu() { ((TProtocol *)TLobby__protocol_instance)->send_quest_menu_request(); online_quest_bin_data = 0; quest_bin_decompressed_size = 0; online_quest_dat_buffer = 0; online_quest_list_decompressed_size = 0; set_field_20((s32)((void*)12)); }

void TQuestListOnline::vfunc_11() {
    Obj_802181B0 *arg0 = (Obj_802181B0 *)this;
    switch (this->state) {
    case 0: ((TQuestListOnline*)arg0)->request_menu(); break;
    case 1: ((TQuestListOnline*)arg0)->build_list_window(); break;
    case 2: ((TQuestListOnline*)arg0)->show_info_window(); break;
    case 3: ((TQuestListOnline*)arg0)->handle_list_selection(); break;
    case 8: ((TQuestListOnline*)arg0)->handle_quest_confirm(); break;
    case 4: ((TQuestListOnline*)arg0)->begin_buffer_request(); break;
    case 5: ((TQuestListOnline*)arg0)->request_download_buffer(); break;
    case 6: ((TQuestListOnline*)arg0)->decompress_quest_list_buffers(); break;
    case 9: ((TQuestListOnline*)arg0)->invoke_callback_28_and_queue_destruction(); break;
    case 10: ((TQuestListOnline*)arg0)->invoke_callback_2c_and_queue_destruction(); break;
    case 7: ((TQuestListOnline*)arg0)->invoke_callback_30_and_queue_destruction(); break;
    case 11: ((TQuestListOnline*)arg0)->invoke_callback_34_and_queue_destruction(); break;
    case 12: return;
    }
}
