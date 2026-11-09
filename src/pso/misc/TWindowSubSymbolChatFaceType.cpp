#include "pso/misc/WindowLayoutDescriptor.h"
#include "pso/misc/TWindowSubSymbolChatFaceType.h"
#include "pso/misc/TWindowSubStatusDisp.h"

extern "C" {
extern u8 lbl_804D2C18[];
WindowLayoutDescriptor symbol_chat_face_type_window_layout = {
    {178.0f, 188.0f}, 50050.0f, lbl_804D2C18, 0x43
};
}

TWindowSubSymbolChatFaceType::~TWindowSubSymbolChatFaceType() {
    TWindowSubStatusDisp::destroy_status_display((s32)m_68, 1);
}
