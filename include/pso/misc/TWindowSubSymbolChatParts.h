#ifndef PSO_MISC_TWINDOWSUBSYMBOLCHATPARTS_H
#define PSO_MISC_TWINDOWSUBSYMBOLCHATPARTS_H

#include "types.h"
#include "pso/misc/TWindowAddition.h"

struct Scroll_8026D790;

struct TWindowSubSymbolChatParts : public TWindowAddition {
    TWindowSubSymbolChatParts(void *position, s32 *value7c, s32 *value80);
    virtual ~TWindowSubSymbolChatParts();
    void sub_80285274(u8 *);
    void sub_80285054();
    s32 calc_symbol_index();
    s32 sub_80283974();
    virtual void render();
    virtual void run_task();
    u8 m_70;
    u8 m_71;
    u8 m_72;
    u8 m_73;
    u8 _pad74[0x2];
    s16 m_76;
    u8 _pad78[0x4];
    s32 *m_7c; // Borrowed word.
    s32 *m_80; // Borrowed word.
    u8 _pad84[0x4];
    void *m_88; // Owned opaque heading; legacy release protocol.
    Scroll_8026D790 *m_8c; // Known producer; shared release remains erased.
    void handle_cancel();
    void add_part();
    void handle_add();
};

typedef char TWindowSubSymbolChatParts_size[sizeof(TWindowSubSymbolChatParts) == 0x90 ? 1 : -1];

extern "C" {
void select_index_and_scroll__20TWindowSubSymbolChatFl(TWindowSubSymbolChatParts *, s32);
void update_height__20TWindowSubSymbolChatFv(TWindowSubSymbolChatParts *);
void open__20TWindowSubSymbolChatFl(TWindowSubSymbolChatParts *, s32);
void fn_80284C04(u8 *arg0);
void select_symbol_chat_slot(TWindowSubSymbolChatParts *parts);
}

// --- C functions defined in TWindowSubSymbolChatParts.cpp ---
extern "C" {
void fn_80284C04(u8 *arg0);
void fn_80284FB8(void *arg0);
void select_symbol_chat_slot(TWindowSubSymbolChatParts *parts);
}
// --- end of C functions

typedef char SymbolParts_values[offsetof(TWindowSubSymbolChatParts, m_7c) == 0x7C ? 1 : -1];
typedef char SymbolParts_heading[offsetof(TWindowSubSymbolChatParts, m_88) == 0x88 ? 1 : -1];
typedef char SymbolParts_scroll[offsetof(TWindowSubSymbolChatParts, m_8c) == 0x8C ? 1 : -1];

typedef char TWindowSubSymbolChatParts_fields_begin[offsetof(TWindowSubSymbolChatParts, m_70) == 0x70 ? 1 : -1];

#endif
