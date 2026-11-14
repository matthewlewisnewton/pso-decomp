#include "pso/misc/TextEntryMeasurement.h"
#include "pso/misc/WindowLayoutDescriptor.h"
#include "types.h"
#include "pso/misc/TWindowDD_80341334.h"
#include "pso/misc/TWindowSubStatusDisp_8025A9B4.h"
#include "pso/misc/TWindowDD_WS_String.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowHelpItem.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/misc/TWindowSubSymbolChatPartsSet.h"

#pragma readonly_strings on

extern "C" {
const char *lbl_805D42D8 = "TWindowDD_WS_String";
}


extern "C" {
extern u8 lbl_804EFC00[];
extern WindowLayoutDescriptor TWindowDD__data_804EFC24;
void copy_vec2__28TWindowSubSymbolChatPartsSetFPv(void *, void *);
extern const char *lbl_805D42D8;
extern const s32 lbl_805DFC18;
extern const f32 lbl_805DFC94;
extern const s32 TWindowDD__data_805DFC14;
extern const f32 lbl_805DFC20;
s32 __nw__7TObjectFUl(int);
extern const f32 TWindowDD__data_805DFB20;

TWindowDD_WS_String::~TWindowDD_WS_String() {}
TWindowDD_WS_String::TWindowDD_WS_String(void *position, void *size, s32 str, s32 mode)
    : TWindowBase((u8 *)&TWindowDD__data_804EFC24, 4, (u8 *)position) {
    m_name = lbl_805D42D8;
    copy_vec2__28TWindowSubSymbolChatPartsSetFPv(m_position, position);
    copy_vec2__28TWindowSubSymbolChatPartsSetFPv(m_size, size);
    m_mode = mode;
    u8 *entry = (u8 *)get_array_entry(0);
    if (entry != NULL) {
        set_text_entry_string(entry, str, 0x80);
        *(f32 *)(entry + 8) = lbl_805DFC94;
        *(f32 *)(entry + 0xC) = lbl_805DFC94;
        measure_text_entry(entry);
        ((TWindowHelpItem *)entry)->reset_float_field();
    }
    if ((m_mode == 1) || (m_mode == 3)) {
        *(s32 *)(entry + 0x24) = lbl_805DFC18;
    }
    m_5c = 0x01000000;
}
s32 TWindowDD__sub_8034146C(s32 arg0, s32 arg1, s32 str, s32 arg3, f32 farg0) {
    TWindowDD__data_804EFC24.extent[0] = farg0;
    TWindowDD__data_804EFC24.extent[1] = TWindowDD__data_805DFB20;
    return (s32)new TWindowDD_WS_String((void *)arg0, (void *)arg1, str, arg3);
}

void TWindowDD__sub_803414DC(void) {
    *(s32 *)(lbl_804EFC00 + 0x18) = (s32) TWindowDD__data_805DFC14;
    TWindowDD__data_804EFC24.order = (f32) lbl_805DFC20;
}

static void (*s_ctor_defaults)(void) __attribute__((section(".ctors"))) = TWindowDD__sub_803414DC;


}
