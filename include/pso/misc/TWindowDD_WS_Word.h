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
    virtual void run_task();
    void add_scroll_offset(int offset);
    s32 sub_80341AC0();
    s32 can_scroll(s32);
    void *destroy(s16);
    s32 sub_80342268();
    s32 sub_80342254();
    s32 m_60;
    u8 unk_64[0x4];
    s32 m_68;
    s32 m_6c;
    u8 unk_70[0x4];
    s32 m_74;
    s32 m_78;
    s32 m_7c;
    void * m_80;
    f32 m_84;
    f32 m_88;
    s32 m_8c;
};
typedef char TWindowDD_WS_Word_size[sizeof(TWindowDD_WS_Word) == 0x90 ? 1 : -1];

#endif
