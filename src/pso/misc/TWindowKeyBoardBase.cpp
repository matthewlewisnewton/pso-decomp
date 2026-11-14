#include "pso/misc/WindowLayoutDescriptor.h"
#include "pso/misc/TWindowKeyBoardBase_8008102C.h"
#include "pso/system/ArrayAllocation.h"
#include "types.h"
#include "pso/misc/TQuestVmDownLoadServer_803E6970.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TWindowKeyBoardBase.h"
#include "pso/misc/TWindowDD.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/ui/Language.h"

extern "C" {
u8 * get_window_layout_position(s32);
}
void init_keyboard_text_buffer(u8 *arg0, u32 arg1, u32 arg2);
extern "C" {
extern WindowLayoutDescriptor TWindowKeyBoardBase__window_descriptor;
extern const char *keyboard_base_type_name_pointer;
s32 set_stream_and_load_file__6TLobbyFPCv(const char *);
s32 Dolphin_ARAlloc(s32);
s32 TQuestVmDownLoadServer__sub_803F0C04(s32, s32, s32, s32, s32);
extern const char lbl_8044F098[] = "Ask_n.dic";
u32 *destroy__19TWindowKeyBoardBaseFPvs(u32 *arg0, s16 arg1);
int initialize_subwindow__9TWindowDDFv(void*);

void TWindowKeyBoardBase::render() {
    s32 temp_r31;

    if ((sub_8025EB68() == 0) && ((sub_8025CB10() != 0) || (this->m_62 & 2))) {
        temp_r31 = TWindowDD::draw_default_entry((s32)this);
        if (this->m_62 & 2) {
            draw_window_frame((void *)temp_r31);
        }
        sub_8025E6DC((u8 *)temp_r31);
    }
}

void TWindowKeyBoardBase::run_task() { initialize_subwindow__9TWindowDDFv(this); update_fade(); }

TWindowKeyBoardBase::~TWindowKeyBoardBase() {
    ::operator delete[]((void *)m_9c);
    destroy__19TWindowKeyBoardBaseFPvs((u32 *)&m_84, -1);
    destroy__19TWindowKeyBoardBaseFPvs((u32 *)&m_6c, -1);
}

TWindowKeyBoardBase::TWindowKeyBoardBase()
    : TWindowBase((u8 *)&TWindowKeyBoardBase__window_descriptor, 4, get_window_layout_position(0xB7)) {
    init_text_buffer_holder__19TWindowKeyBoardBaseFv(&m_6c);
    init_text_buffer_holder__19TWindowKeyBoardBaseFv(&m_84);
    m_name = keyboard_base_type_name_pointer;
    s32 language = current_language;
    init_keyboard_text_field(0, 0);
    init_keyboard_text_buffer((u8 *)&m_84, 0, 0);
    m_68 = (u32)&m_6c;
    m_b4 = 0;
    m_62 = 0;
    m_65 = -1;
    m_9c = 0;
    m_a0 = 0;
    m_a4 = 0;
    m_a8 = 0;
    m_ac = 0;
    if (language == LANGUAGE_JAPANESE) {
        init_keyboard_text_buffer((u8 *)&m_84, 0x24, 0);
        m_9c = (u32)::operator new[](0x194);
        m_b0 = 0x94;
    }
}

void TLobby::load_ask_dictionary() {
    s32 data;
    s32 size;
    s32 aligned;
    s32 aram;
    size = TLobby::get_resource_file_size(lbl_8044F098);
    aligned = (size + 0x1F) & ~0x1F;
    aram = Dolphin_ARAlloc(aligned);
    data = set_stream_and_load_file__6TLobbyFPCv(lbl_8044F098);
    TLobby::aram_transfer_sync(3, data, aram, aligned);
    TAdSinglePlyChrSelectGC::safe_free((void *)data);
    TQuestVmDownLoadServer__sub_803F0C04(aram, size, 3, 1, 0x2710);
    TQuestVmDownLoadServer__sub_803F09A4();
}
}
