#include "pso/misc/PageIndicator_8026CB44.h"
#include "pso/misc/TWindowDrawContext.h"
#include "types.h"
#include "pso/misc/TWindowMessage.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowHelpItem_80255AB4.h"
#include "pso/misc/TWindowSubComCard_8007A810.h"
#include "pso/misc/TWindowSubCustomEquip_80275D9C.h"
#include "pso/misc/TWindowSubCustomSelect_80275D84.h"
#include "pso/misc/TWindowSubStatusDisp_80228CC0.h"
#include "pso/unk/text_80076E84.h"
#include "pso/unk/text_80263A20.h"
#include "pso/misc/TWindowMenu.h"
#include "pso/misc/TUnk_804D1160.h"
#include "pso/misc/TWindowSubComCardList.h"
#include "pso/misc/TWindowSubCustomEquip.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TWindowOptionCtrl.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowSubCustomSelect.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/object/TObjCityMainWarp.h"
#include "pso/ui/Language.h"


struct Win_802758C8 {
    u8 pad0[0x20];
    s32 player;
    u8 pad24[0x30 - 0x24];
    s32 lobby;
    u16 kind;
    u16 id;
};

struct Ev_802758C8 {
    u16 kind;
    u16 id;
};

class VObj_80275A8C {
public:
    u8 pad0[0x18];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
};

struct Self_80275A8C {
    u8 pad0[0x1C];
    u8 state;
    u8 pad1d[3];
    s32 f20;
    VObj_80275A8C *f24;
    s32 f28;
    void *f2c;
};

extern "C" {
u32 get_item_field_6__10TObjPlayerFPv(void *);
s32 get_shared_text_buffer();
s32 weapon_has_extra_attack();
void *get_player_by_client_id(s32);
u8 get_cast_technique_level(void *, s16);
s32 validate_and_clear_slot__10TObjPlayerFv(void *, s16);
void TWindowSubStatusDisp__sub_80228F5C(s32);
void text_builder_append();
u8 *calc_technique_parameters(u16, u8, s32);
void *__nw__7TObjectFUl(u32);
void set_depth__11TWindowBaseFf(void *);
f32 TWindowSubEquip__sub_80263AF8(u8 *, u32);
}

void text_builder_reset();
s32 get_palette_consumable_count(u16, s32);
void TUnk_804D1160::update_customize_help_text(void *ev_arg) {
    Win_802758C8 *self = (Win_802758C8 *)this;
    Ev_802758C8 *ev = (Ev_802758C8 *)ev_arg;
    u8 *pl;
    s32 lvl;
    toggle_help_window_on_button(self->lobby, self->player);
    if (ev == NULL) {
        return;
    }
    pl = (u8 *)get_player_by_client_id(self->player);
    if (pl == NULL) {
        return;
    }
    if (self->id == ev->id && self->kind == ev->kind) {
        return;
    }
    self->kind = ev->kind;
    self->id = ev->id;
    text_builder_reset();
    switch (ev->kind) {
    case 0:
        break;
    case 2:
        if (ev->id == 2 && (get_item_field_6__10TObjPlayerFPv(pl) == 0 || weapon_has_extra_attack() != 1)) {
            break;
        }
        get_help_text_string(ev->id + 0x13);
        text_builder_append();
        break;
    case 3:
        if (validate_and_clear_slot__10TObjPlayerFv(pl + 0x428, ev->id) != 0) {
            break;
        }
        get_technique_name(ev->id);
        text_builder_append();
        if (ev->id != 0x11 && ev->id != 0xE) {
            lvl = get_cast_technique_level(pl + 0x428, ev->id);
            if (current_language != LANGUAGE_JAPANESE) {
                append_text_space();
            }
            get_help_text_string(0x2D);
            text_builder_append();
            TWindowSubStatusDisp__sub_80228F5C(lvl + 1);
        }
        get_help_text_string(0x2E);
        text_builder_append();
        TWindowSubStatusDisp__sub_80228F5C(*(s16 *)(calc_technique_parameters(ev->id, lvl, 0xFFFF) + 0x10));
        get_help_text_string(ev->id);
        text_builder_append();
        break;
    case 4:
        if (get_palette_consumable_count(ev->id, self->player) == -1) {
            break;
        }
        get_help_text_string(ev->id + 0x16);
        text_builder_append();
        break;
    case 7:
        break;
    }
    ((TWindowMessage *)(self->lobby))->append_line(get_shared_text_buffer(), 0x82);
}

void TUnk_804D1160::render() {  }
void TUnk_804D1160::run_task() {
    Self_80275A8C *self = (Self_80275A8C *)this;
    Ev_802758C8 ev;
    void *p;
    switch (self->state) {
    case 0:
    case 1:
        if (self->f2c != NULL) {
            ((TWindowBase *)self->f2c)->close();
            self->f2c = NULL;
        }
        ((TWindowSubCustomEquip *)(this->m_28))->clear_flag_and_set_entry_state();
        self->state = 2;
    case 2:
        ((TWindowSubCustomEquip *)(this->m_28))->get_cursor_pos(&ev);
        ((TUnk_804D1160 *)self)->update_customize_help_text(&ev);
        if (TWindowSubCustomEquip__sub_80275DA8((void *)this->m_28) != 0) {
            self->f24->v7();
            self->state = 5;
        } else if (((TWindowSubCustomEquip *)(this->m_28))->is_selected() != 0) {
            self->state = 3;
        }
        break;
    case 3:
        p = __nw__7TObjectFUl(0x84);
        if (p != NULL) {
            p = TWindowSubCustomSelect__ct((TWindowSubCustomSelect *)((u8 *)p), this->m_20);
        }
        self->f2c = p;
        TWindowSubEquip__sub_80263AF8((u8 *)self->f24, 1);
        set_depth__11TWindowBaseFf(self->f2c);
        self->state = 4;
    case 4:
        ((TUnk_804D1160 *)self)->update_customize_help_text(((TWindowSubCustomSelect *)self->f2c)->sub_80277290());
        if (fn_80275D90(self->f2c) != 0) {
            self->state = 1;
        }
        if (((TWindowSubCustomSelect *)(self->f2c))->is_active() != 0) {
            Ev_802758C8 *e = (Ev_802758C8 *)((TWindowSubCustomSelect *)self->f2c)->sub_80277290();
            ((TWindowSubCustomEquip *)(this->m_28))->toggle_action_binding(e);
            self->state = 1;
        }
        break;
    case 5:
        break;
    }
}

#include "types.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowSubCustomEquip.h"
#include "pso/misc/TUnk_804D1160.h"
#include "pso/misc/TWindowSubEquip.h"

struct Equip_80275CB0 {
    u8 pad0[0x18];
    s32 *vt;
    s8 x1c;
    u8 pad1d[3];
    s32 x20;
    void *parent;
    void *custom;
    s32 x2c;
    void *list;
    s16 x34;
    s16 x36;
};

extern "C" {
void *__nw__7TObjectFUl(u32);
void __ct__7TObjectFP7TObject(void *, void *);
void set_depth__11TWindowBaseFf(void *);
void call_if_split_screen(void *, s32);
f32 TWindowSubEquip__sub_80263AF8(u8 *arg0, u32 arg1);
void *create__14TWindowMessageFlPCvUll(void *, void *, s32, s32);
void *get_window_layout_position(s32);
extern u8 lbl_8044F718[];
extern s32 lbl_804D1160[];
void *TWindowSubEquip__sub_80275CB0(void *arg0, void *arg1, s32 arg2);
void __dl__7TObjectFPv(void *);
void __dt__7TObjectFv(void *, int);

void *TUnk_804D1160::destroy(s16 arg1) {
    if (this != NULL) {
        *(s32 **)((s8 *)this + 0x18) = lbl_804D1160;
        if (*(void * *)&(*(u32 *)((u8 *)this + 0x2C)) != NULL) { ((TWindowBase *)(*(void * *)&(*(u32 *)((u8 *)this + 0x2C))))->close(); *(s32 *)&(*(u32 *)((u8 *)this + 0x2C)) = 0; }
        if (*(void * *)&(this->m_30) != NULL) { ((TWindowBase *)(*(void * *)&(this->m_30)))->close(); *(s32 *)&(this->m_30) = 0; }
        if (*(void * *)&(this->m_28) != NULL) { ((TWindowBase *)(*(void * *)&(this->m_28)))->close(); *(s32 *)&(this->m_28) = 0; }
        __dt__7TObjectFv(this, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(this);
        }
    }
    return this;
}
#define self ((Equip_80275CB0 *)arg0)
void *TWindowSubEquip__sub_80275CB0(void *arg0, void *arg1, s32 arg2) {
    __ct__7TObjectFP7TObject(arg0, arg1);
    self->vt = lbl_804D1160;
    self->parent = arg1;
    self->x20 = arg2;
    self->custom = new TWindowSubCustomEquip(self->x20);
    TWindowSubEquip__sub_80263AF8((u8 *)self->parent, 0);
    set_depth__11TWindowBaseFf(self->custom);
    self->list = create__14TWindowMessageFlPCvUll(get_window_layout_position(0x11), lbl_8044F718, 1, self->x20);
    TWindowSubEquip__sub_80263AF8((u8 *)self->parent, 2);
    set_depth__11TWindowBaseFf(self->list);
    call_if_split_screen(self->list, self->x20);
    self->x2c = 0;
    self->x34 = 0;
    self->x36 = 0;
    self->x1c = 0;
    return arg0;
}
#undef self

}
