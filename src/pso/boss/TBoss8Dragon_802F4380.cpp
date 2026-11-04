#include "types.h"
#include "pso/TMainTask.h"
#include "pso/boss/TBoss8Dragon.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/player/demo_mode.h"

// TBoss8Dragon stores __vt__12TBoss8Dragon at offset 0x18. MWCC puts that vptr
// after the leading 0x18 bytes and inserts two header words, so the declared
// slots below are table indices 2..105 and draw_motion_model is index 106
// (call offset 0x1A8). The class itself stays non-polymorphic: a compiler
// vtable would collide with the linked hand-written __vt__12TBoss8Dragon.
struct TBoss8DragonDrawView {
    s32 m_0;
    u8 unk_4[0x4];
    f32 m_8;
    u8 unk_C[0x4];
    f32 m_10;
    u8 unk_14[0x4];
    virtual void dt();
    virtual void run_task();
    virtual void sub_802F4380();
    virtual void render_shadows();
    virtual void vfunc_6();
    virtual void fn_801A1F48();
    virtual void TObjPlayer__sub_80018F64();
    virtual void TObjPlayer__sub_80018F5C();
    virtual void fn_801A2340();
    virtual void fn_801A212C();
    virtual void get_name();
    virtual void interact();
    virtual void TObjPlayer__sub_80011210();
    virtual void consume_timer_field();
    virtual void TObjPlayer__sub_8001119C();
    virtual void TObjPlayer__sub_80018EE4();
    virtual void vfunc_18();
    virtual void TObjPlayer__sub_80011704();
    virtual void TObjPlayer__sub_80016454();
    virtual void TObjPlayer__sub_80015DE8();
    virtual void TObjPlayer__sub_80014108();
    virtual void calc_direct_attack_damage();
    virtual void TObjPlayer__sub_80011824();
    virtual void TObjPlayer__sub_8001401C();
    virtual void try_start_action();
    virtual void TObjPlayer__sub_800162E0();
    virtual void vfunc_28();
    virtual void vfunc_29();
    virtual void TObjPlayer__sub_8001745C();
    virtual void test_flag_256();
    virtual void test_flag30_512();
    virtual void has_flag_0x800();
    virtual void test_flag_1000();
    virtual void TObjPlayer__sub_800171A0();
    virtual void TObjPlayer__sub_80016FF8();
    virtual void vfunc_37();
    virtual void update_flag30_timer();
    virtual void TObjPlayer__sub_80016D78();
    virtual void update_shock_clock();
    virtual void TObjPlayer__sub_80016944();
    virtual void TObjPlayer__sub_800166DC();
    virtual void vfunc_43();
    virtual void vfunc_44();
    virtual void vfunc_45();
    virtual void vfunc_46();
    virtual void vfunc_47();
    virtual void vfunc_48();
    virtual void vfunc_49();
    virtual void vfunc_50();
    virtual void TObjPlayer__sub_80014E74();
    virtual void TObjPlayer__sub_80014C78();
    virtual void TObjPlayer__sub_80014C1C();
    virtual void TObjPlayer__sub_80014B5C();
    virtual void TObjPlayer__sub_80014900();
    virtual void TObjPlayer__sub_8001489C();
    virtual void TObjPlayer__sub_800105E4();
    virtual void vfunc_58();
    virtual void vfunc_59();
    virtual void vfunc_60();
    virtual void vfunc_61();
    virtual void vfunc_62();
    virtual void vfunc_63();
    virtual void reset_pose();
    virtual void get_anim_node_position();
    virtual void vfunc_66();
    virtual void vfunc_67();
    virtual void get_pos();
    virtual void apply_switch_attack();
    virtual void TObjPlayer__sub_80010B44();
    virtual void trigger_switch_attack();
    virtual void TObjPlayer__sub_80010A84();
    virtual void recalc_stats();
    virtual void vfunc_74();
    virtual void vfunc_75();
    virtual void vfunc_76();
    virtual void vfunc_77();
    virtual void vfunc_78();
    virtual void vfunc_79();
    virtual void apply_hit_message_flags();
    virtual void TObjPlayer__sub_800F698C();
    virtual void clear_lobby_object_state();
    virtual void vfunc_83();
    virtual void vfunc_84();
    virtual void vfunc_85();
    virtual void vfunc_86();
    virtual void sub_802FA4E4();
    virtual void update_colliders();
    virtual void vfunc_89();
    virtual void vfunc_90();
    virtual void vfunc_91();
    virtual void vfunc_92();
    virtual void vfunc_93();
    virtual void vfunc_94();
    virtual void vfunc_95();
    virtual void vfunc_96();
    virtual void vfunc_97();
    virtual void vfunc_98();
    virtual void vfunc_99();
    virtual void vfunc_100();
    virtual void vfunc_101();
    virtual void vfunc_102();
    virtual void vfunc_103();
    virtual void vfunc_104();
    virtual void sub_802F4360();
    virtual void draw_motion_model();
};

extern "C" s32 is_split_screen();

extern "C" void TBoss8Dragon__sub_802F4380(TBoss8Dragon *self) {
    s32 view = 0;
    u8 pos[0xC];

    if (check_demo_mode() != 0) {
        ((TBoss8DragonDrawView *)self)->draw_motion_model();
        return;
    }
    if (is_split_screen() != 0) {
        view = TCameraCtrl::get_camera_mode();
    }
    self->sub_802F4098(pos);
    if (((TObject *)self)->defer_render() != 0) {
        if ((TCameraCtrl::get_mode(&main_task) & MAIN_TASK_SCENE_PASSES) == 0) {
            self->render_body_model();
            self->copy_vectors();
        }
        if (self->renderFadeStates[view].isFading() == 0) {
            self->draw_with_fade((s32)pos, view);
        }
        self->render_nodes_flagged();
    } else if (self->renderFadeStates[view].isFading() != 0) {
        self->draw_with_fade((s32)pos, view);
    }
}
