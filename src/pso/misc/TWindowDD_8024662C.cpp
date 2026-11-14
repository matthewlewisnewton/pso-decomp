#include "types.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowSubStatusDisp.h"

struct RecoveredGlobal_802466E0___vt__11TWindowBase {
    s32 value;
    u8 remaining[0x14];
};

extern "C" {
s32 TWindowCtrlMain__sub_8024CDB0(void *p);
s32 __ct__7TObjectFP7TObject(void *, void *);
extern s32 __vt__11TWindowBase[];
int TWindowSubComCard__sub_8024634C(void*);
void __dl__7TObjectFPv(void *);
void __dt__7TObjectFv(void *, int);
int update_open_close__17TWindowSubComCardFv(void*);
void sub_8026CC28__11TWindowBaseFv(void *);

int TWindowDD::update_com_card() { return TWindowSubComCard__sub_8024634C(this); }
int TWindowDD::initialize_subwindow() { return update_open_close__17TWindowSubComCardFv(this); }
void TWindowBase::render() {  }
void TWindowBase::run_task() {  }

TWindowBase::~TWindowBase() {
    ((TWindowSubStatusDisp *)&m_24)->destroy_all_items();
    sub_8026CC28();
}
TWindowBase::TWindowBase(u8 *descriptor, s16 client, u8 *position)
    : TObject((TObject *)TWindowCtrlMain__sub_8024CDB0((void *)client)) {
    sub_80244F2C((u8 *)descriptor, (u8 *)position, client);
}

}
