#include "pso/misc/WindowLayoutDescriptor.h"
#include "types.h"
#include "pso/misc/TWindowMenu.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowChatSymbol_802486A8.h"
#include "pso/misc/TWindowSubSymbolChat.h"
#include "pso/misc/TUnk_804CE7D0.h"
#include "pso/misc/TWindowChatSymbol.h"
#include "pso/misc/TWindowDD.h"

extern "C" {
// Existing two-float size-copy boundary; wider helper ownership remains qualified.
void fn_8024491C(void *, void *);
extern u8 symbol_chat_layout_sprite_records[];
WindowLayoutDescriptor window_chat_symbol_settings = {{203.0f, 78.0f}, 50100.0f, symbol_chat_layout_sprite_records, 11};
extern const char *lbl_805D38A8;
void __dl__7TObjectFPv(void *);
void __dt__7TObjectFv(void *, int);

TWindowChatSymbol::~TWindowChatSymbol() {}

TWindowChatSymbol::TWindowChatSymbol(void *position, void *size)
    : TWindowBase((u8 *)&window_chat_symbol_settings, 4, (u8 *)position) {
    m_name = lbl_805D38A8;
    fn_8024491C(this, size);
    m_60 = 0;
    m_64 = 0;
}

void TUnk_804CE7D0::render() {  }
void TUnk_804CE7D0::run_task() {
    ((TWindowSubSymbolChat *)(this->m_20))->set_from_key(((TWindowMenu *)(*(s32 *)&this->unk_1C))->get_selected_value());
}

extern s32 lbl_804CE7D0[];

// Historical symbol; receiver is the separate TObject selection controller.
void *destroy__17TWindowChatSymbolFs(TUnk_804CE7D0 *self, s16 arg1) {
    if (self != NULL) {
        *(s32 **)((s8 *)self + 0x18) = lbl_804CE7D0;
        if (*(void **)&self->m_20 != NULL) { ((TWindowBase *)*(void **)&self->m_20)->close(); *(void **)&self->m_20 = 0; }
        if (*(void **)&self->unk_1C != NULL) { ((TWindowBase *)*(void **)&self->unk_1C)->close(); *(void **)&self->unk_1C = 0; }
        __dt__7TObjectFv(self, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(self);
        }
    }
    return self;
}

}
