#include "pso/unk/text_802841FC.h"
#include "pso/misc/WindowLayoutDescriptor.h"
#include "pso/misc/TWindowSubStatusDisp.h"

extern "C" {
extern WindowLayoutDescriptor symbol_chat_face_type_window_layout;
extern const char *TWindowSubSymbolChatFaceType__name;
// Existing opaque heading initializer; complete child class ownership is unresolved.
u8 *construct_type1_heading__20TWindowSubStatusDispFll(void *storage, s32 text, s32 client);
}

TWindowSubSymbolChatFaceType::TWindowSubSymbolChatFaceType(void *position, s8 *selection)
    : TWindowBase((u8 *)&symbol_chat_face_type_window_layout, 4, (u8 *)position) {
    void *heading;
    m_name = TWindowSubSymbolChatFaceType__name;
    m_60 = 0;
    m_61 = 0;
    m_62 = 0;
    m_64 = selection;
    heading = ::operator new(0x24);
    if (heading != NULL) {
        heading = construct_type1_heading__20TWindowSubStatusDispFll(heading, (s32)TWindowSubStatusDisp::get_message_10(0x33), m_20);
    }
    m_68 = heading;
}
