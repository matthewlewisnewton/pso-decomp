#ifndef PSO_MISC_TWINDOWSUBSYMBOLCHATFACETYPE_H
#define PSO_MISC_TWINDOWSUBSYMBOLCHATFACETYPE_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowSubSymbolChatFaceType : public TWindowBase {
    TWindowSubSymbolChatFaceType(void *position, s8 *selection);
    virtual ~TWindowSubSymbolChatFaceType();
    void update_parts_entries();
    void handle_input();
    s32 is_open();
    virtual void render();
    virtual void run_task();
    u8 m_60;
    u8 m_61;
    u8 m_62;
    u8 _pad63[0x1];
    s8 *m_64; // Borrowed selection byte.
    void *m_68; // Owned opaque heading storage; legacy child lifetime protocol.
    void close_when_chat_closed();
    void confirm_selection();
};

typedef char TWindowSubSymbolChatFaceType_size[sizeof(TWindowSubSymbolChatFaceType) == 0x6C ? 1 : -1];

typedef char FaceType_selection[offsetof(TWindowSubSymbolChatFaceType, m_64) == 0x64 ? 1 : -1];
typedef char FaceType_heading[offsetof(TWindowSubSymbolChatFaceType, m_68) == 0x68 ? 1 : -1];

#endif
