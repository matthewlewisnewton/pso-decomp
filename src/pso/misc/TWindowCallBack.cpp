#include "pso/misc/TWindowCallBack.h"
#include "pso/misc/WindowLayoutDescriptor.h"
#include "pso/protocol/protocol_types.h"
#include "pso/misc/TLobby_801E43E4.h"
#include "types.h"
#include "pso/misc/TWindowBase.h"
#include "pso/boss/TBoss6GravBall.h"
#include "pso/boss/TBoss6Type2.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowSubSymbolChatPartsSet.h"

extern "C" {
void set_field_60__15TWindowCallBackFPvi(void* p, s32 v);
WindowLayoutDescriptor window_callback_base_params = { { 0.0f, 0.0f }, 50045.0f, NULL, 0x23 };
extern s32 lbl_805D3E58;
void fn_802ACD40(void* p);
void fn_802ACD60(void* p);

s32 TBoss6Type2::get_state() { return this->m_374; }
s32 TBoss6GravBall::get_state() { return *(s32*)((char*)this + 0x374); }
void TBoss6Type2::update_and_send() { handle_olga_action(); send_subcommand((u8 *)this); }
void TBoss6Type2::handle_olga_action() { ((G_ClientIDHeader *)this)->bswap(); }
void TBoss6Type2::init_packet() { *(u8*)((char*)this + 0x0) = 165; *(u8*)((char*)this + 0x1) = 5; }
void fn_802ACD40(void* p) { ((G_ClientIDHeader *)p)->bswap(); }
void fn_802ACD60(void* p) { fn_802ACD40(p); send_subcommand((u8 *)p); }
}
void build_6xA3_olga_flow_boss_actions(void* p);
void build_6xA3_olga_flow_boss_actions(void* p) { *(u8*)((char*)p + 0x0) = 163; *(u8*)((char*)p + 0x1) = 5; }
void set_field_60__15TWindowCallBackFPvi(void* p, s32 v) { *(s32*)((char*)p + 0x60) = v; }

void TWindowCallBack::render() {
    s32 r = TWindowDD::draw_default_entry((s32)this);
    if (callback != NULL) {
        callback(this, r);
    }
}

void TWindowCallBack::run_task() { ((TWindowDD *)this)->initialize_subwindow(); update_fade(); }

TWindowCallBack::~TWindowCallBack() {}

TWindowCallBack::TWindowCallBack(u8 *position, u8 *scale, s32 callback)
    : TWindowBase((u8 *)&window_callback_base_params, 4, position) {
    m_name = (const char *)lbl_805D3E58;
    ((TWindowSubSymbolChatPartsSet *)&m_38)->copy_vec2(scale);
    save_position();
    set_field_60__15TWindowCallBackFPvi(this, callback);
}
