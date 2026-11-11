#ifndef PSO_MISC_TWINDOWDD_WS_WORD_H
#define PSO_MISC_TWINDOWDD_WS_WORD_H
#include "types.h"
#include "pso/misc/TWindowBase.h"

class TUnk_804CFA28;

struct TWindowDDWordEntryList {
    u32 count;
    TUnk_804CFA28 **items;
};

class TWindowDD_WS_Word : public TWindowBase {
public:
    virtual ~TWindowDD_WS_Word();
    virtual void render();
    s32 sub_80341AC0();
    s32 can_scroll(s32);
    void *destroy(s16);
    u8 sub_80342268();
    s32 sub_80342254();
    s32 m_60;
    s32 point_table_index;
    s32 m_68;
    s32 m_6c;
    u8 unk_70[0x4];
    s32 m_74;
    s32 visible_row_count;
    s32 m_7c;
    void * m_80;
    u8 unk_84[0x4];
    f32 scroll_offset;
    s32 m_8c;
};
typedef char TWindowDD_WS_Word_size[sizeof(TWindowDD_WS_Word) == 0x90 ? 1 : -1];

typedef char TWindowDD_WS_Word_point_table_index[offsetof(TWindowDD_WS_Word, point_table_index) == 0x64 ? 1 : -1];
typedef char TWindowDD_WS_Word_visible_row_count[offsetof(TWindowDD_WS_Word, visible_row_count) == 0x78 ? 1 : -1];
typedef char TWindowDD_WS_Word_scroll_offset[offsetof(TWindowDD_WS_Word, scroll_offset) == 0x88 ? 1 : -1];

#endif
