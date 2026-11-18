#include "pso/misc/WindowLayoutDescriptor.h"
#include "pso/TMainTask.h"
#include "pso/ui/ItemTextureConstants.h"
#include "types.h"
#include "pso/misc/TWindowLoadItemTexture.h"
#include "pso/misc/TWindowSubStatusDisp_8025B050.h"
#include "pso/item/TItemTexLoad.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowDD.h"

#pragma push
#pragma opt_common_subs off

extern "C" {

#pragma push
#pragma fp_contract on
TWindowLoadItemTexture *fn_802628C0(void *layout, void *table, s32 id) {
    TWindowLoadItemTexture *window;
    s32 sprite;

    window = new TWindowLoadItemTexture(layout, table, id);
    fn_80262C2C(window);
    sprite = (s32)window->get_array_entry(0);
    *(f32 *)(sprite + 0x8) = 0.5f * window->m_38 - 32.0f - 4.0f;
    *(f32 *)(sprite + 0xC) = 0.5f * window->unk_3c - 32.0f - 1e+01f;
    *(f32 *)(sprite + 0x10) = 64.0f;
    *(f32 *)(sprite + 0x14) = 64.0f;
    set_sprite_uv_bounds((void *)sprite, 0.0f, 0.0f, 1.0f, 1.0f);
    return window;
}
#pragma pop
}

#pragma pop

extern "C" {

extern u8 lbl_804D0020[];
WindowLayoutDescriptor lbl_804D0058 = {
    {0.0f, 0.0f}, 38000.0f, lbl_804D0020, 0x2B
};
extern const char *lbl_805D3940;

s32 draw_visible_window_entries(void *, void *, s32);

int initialize_subwindow__9TWindowDDFv(void*);

extern s32 lbl_8044F280[];

TWindowLoadItemTexture *TWindowLoadItemTexture::create(void *position, s32 client) {
    TWindowLoadItemTexture *o;
    o = new TWindowLoadItemTexture(position, lbl_8044F280, client);
    set_sprite_uv_bounds(o->get_array_entry(0), 0.0f, 0.0f, 0.625f, 0.46875f);
    return o;
}

void TWindowLoadItemTexture::render() {
    TWindowLoadItemTexture *arg0 = this;
    s32 temp_r31;

    if ((s32) arg0->m_60 == 1) {
        arg0->m_70 = arg0->m_6c->ready_texture_list();
        if ((u32) arg0->m_70 != 0U) {
            fn_8026287C(arg0);
            arg0->m_60 = 1U;
        }
    }
    temp_r31 = ((TWindowBase *)arg0)->setup_window_draw_context((s32)((u8 *)arg0 + 0x64));
    if (arg0->m_61 & 1) {
        ((TWindowBase *)arg0)->draw_window_frame((void *)temp_r31);
    }
    draw_visible_window_entries(arg0, (u8 *)arg0 + 0x24, temp_r31);
}

void TWindowLoadItemTexture::run_task() { initialize_subwindow__9TWindowDDFv(this); update_fade(); update_window_entry_list((char*)this + 0x24); }

TWindowLoadItemTexture::~TWindowLoadItemTexture() {
    queue_destruction__7TObjectFv(m_6c);
}

TWindowLoadItemTexture::TWindowLoadItemTexture(void *position, void *extent, s32 client)
    : TWindowBase((u8 *)&lbl_804D0058, (s16)client, (u8 *)position) {
    void *e;
    m_name = lbl_805D3940;
    switch (TCameraCtrl::get_camera_id()) {
    case 1:
        m_68 = m_64 = 1.0f;
        break;
    case 2:
        m_68 = m_64 = 0.5f;
        break;
    case 3:
    case 4:
        m_68 = m_64 = 0.37f;
        break;
    }
    m_38 = *(f32 *)extent;
    m_3c = *((f32 *)extent + 1);
    save_position();
    e = get_array_entry(0);
    *(f32 *)((s8 *)e + 0x10) = *(f32 *)extent;
    *(f32 *)((s8 *)e + 0x14) = *((f32 *)extent + 1);
    m_6c = TItemTexLoad::create(tl_07);
    m_61 = 0;
    m_60 = 2;
}

void fn_80262C2C(TWindowLoadItemTexture *window) { window->m_61 |= 1; }

}
