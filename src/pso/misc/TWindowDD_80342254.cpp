#include "pso/misc/WindowWordSelectionAbi.h"
#include "pso/misc/TWindowBase.h"
#include "pso/system/ArrayAllocation.h"
#include "types.h"
#include "pso/TObject.h"
#include "pso/misc/TWindowDD_80342254.h"
#include "pso/misc/TWindowDD_WS_Word.h"
#include "pso/misc/TWindowDD.h"

struct RecoveredGlobal_80342384_TWindowDD__data_804EFC50 { s32 value; u8 remaining[0x3C]; };
typedef char RecoveredGlobal_80342384_TWindowDD__data_804EFC50_size[sizeof(RecoveredGlobal_80342384_TWindowDD__data_804EFC50) == 0x40 ? 1 : -1];

extern "C" {
s32 apply_entry_layout__9TWindowDDFPv(void *);
s32 TWindowDD__sub_803435A0(void *);
s32 TWindowDD__sub_80347C50();
s32 TWindowDD__sub_803482B0(void *);
s32 TWindowDD__sub_803484C4(void *);
s32 reset_fields__9TWindowDDFv(void *, void *);
// Existing target-ABI helper; its broader receiver/mapper interfaces remain qualified.
void load_element_list__9TWindowDDFv(void *);
extern s32 lbl_805D42E0;
extern const f32 TWindowDD__data_805DFCA8;
extern s32 TWindowDD__data_805DFC14;
extern const f32 TWindowDD__data_805DFB6C;
extern const f32 lbl_805DFB70;
extern const f32 TWindowDD__data_805DFB74;
extern const f32 lbl_805DFB78;
extern const f32 lbl_805DFC1C;
extern void *TWindowDD__data_804EFC50[9];
void *TWindowDD__data_804EFC50[9] = {
    (void *)0x1, (void *)0x1, (void *)0x3, (void *)0x0,
    (void *)0x0, (void *)0x3e4ccccd, (void *)0x0, (void *)0x40,
    (void *)0x0,
};
__declspec(section ".data") void *lbl_804EFC74[2] = {
    (void *)0x0, (void *)0x0,
};
void *lbl_804EFC7C[5] = {
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)&TWindowDD__data_804EFC50,
    (void *)0x3,
};

#define TWindowDD__data_804EFC50 (*(RecoveredGlobal_80342384_TWindowDD__data_804EFC50 *)TWindowDD__data_804EFC50)

// Deferred compilation emits these definitions in reverse order. This keeps
// the native vtable available for the constructor's shared metadata base.
void TWindowDD__sub_80342428(u8 *window_dd) {
  u8 *new_var;
  TWindowDD__sub_80347C50();
  ((TWindowDD *)window_dd)->update_selection_state();
  if (((TWindowDD *)window_dd)->test_input_flag_4())
  {
    TWindowDD::play_sound();
    if (((s32) (*((s32 *) (((s8 *) window_dd) + 0xB0)))) == 0xA)
    {
      new_var = window_dd;
      new_var = new_var + ((*((s32 *) (((s8 *) window_dd) + 0x20))) * 4);
      if ((s16)TWindowDD__sub_80342158((u8 *) (*((s32 *) (((s8 *) new_var) + 0x24)))) == 0x685)
      {
        *((s32 *) (((s8 *) window_dd) + 0xB4)) = 0x14;
        ((TWindowDD *)window_dd)->m_a8 = -0x3C;
        TWindowDD__sub_803435A0((void *) window_dd);
        return;
      }
      TWindowDD__sub_803484C4((void *) window_dd);
      return;
    }
    TWindowDD__sub_803484C4((void *) window_dd);
    return;
  }
  if (TWindowDD__sub_803482B0((void *) window_dd) != 0)
  {
    TWindowDD::play_se();
    apply_entry_layout__9TWindowDDFPv((void *) window_dd);
  }
}

void TWindowDD__sub_803423E0(void) {
    *(s32 *)((s8 *)&TWindowDD__data_804EFC50.value + 0x18) = TWindowDD__data_805DFC14;
    ((f32 *)lbl_804EFC74)[0] = TWindowDD__data_805DFB6C;
    ((f32 *)lbl_804EFC74)[1] = lbl_805DFB70;
    ((f32 *)lbl_804EFC7C)[0] = TWindowDD__data_805DFB74;
    ((f32 *)lbl_804EFC7C)[1] = lbl_805DFB78;
    ((f32 *)lbl_804EFC7C)[2] = lbl_805DFC1C;
}

s32 TWindowDD__sub_80342384(s32 arg0, s32 arg1) {
    *(s32 *)((s8 *)&TWindowDD__data_804EFC50.value + 4) = arg1;
    return (s32)new TWindowDD_WS_Word(arg0, arg1);
}

TWindowDD_WS_Word::TWindowDD_WS_Word(s32 list_id, s32 visible_count)
    : TWindowBase((u8 *)lbl_804EFC7C, 4, (u8 *)lbl_804EFC74) {
    const char *assigned_name = reinterpret_cast<const char *>(lbl_805D42E0);
    m_name = assigned_name;
    visible_row_count = visible_count;
    point_table_index = 0;
    scroll_offset = TWindowDD__data_805DFCA8;
    m_84 = TWindowDD__data_805DFCA8;
    m_60 = 0;
    element_list_id = list_id;
    reset_fields__9TWindowDDFv(this, (void *)assigned_name);
    load_element_list__9TWindowDDFv(this);
    m_5c = 0x01000000;
}

TWindowDD_WS_Word::~TWindowDD_WS_Word() {
    if (m_80 != NULL) {
        ::operator delete[](m_80);
        m_80 = 0;
    }
}

s32 TWindowDD_WS_Word::sub_80342268() {
    TWindowDD_WS_Word *self = this;
    return !(self->m_60 & 1);
}

s32 TWindowDD_WS_Word::sub_80342254() {
    TWindowDD_WS_Word *self = this;
    return !(self->m_60 & 1);
}

}

__declspec(section ".ctors") static void *const __sinit_TWindowDD_80342254_cpp_ref = (void *)TWindowDD__sub_803423E0;
