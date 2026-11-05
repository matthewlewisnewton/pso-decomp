#ifndef PSO_MISC_TQUESTLISTOFFLINE_H
#define PSO_MISC_TQUESTLISTOFFLINE_H
#include "types.h"
#include "pso/TShopWindowBase.h"

class TWindowMessage;

class TQuestListOffline : public TShopWindowBase {
public:
    virtual ~TQuestListOffline();
    void *close_shop_subwindows(s16);
    void init_quest_list_window();
    virtual void vfunc_11();
    u8 unk_1C[0x8];
    void *m_entity;
    u8 unk_28[0x10];
    void * m_38;
    u8 unk_3C[0x4];
    void * m_40;
    TWindowMessage *m_message;
    u8 unk_48[0x10];
public:
    void update_list_navigation();
};
typedef char TQuestListOffline_size[sizeof(TQuestListOffline) == 0x58 ? 1 : -1];

#endif
