#define TOBJECT_OUT_OF_LINE_HELPERS
#include "types.h"
#include "pso/system/main_loop.h"
#include "pso/misc/TLoadCtrl.h"
#include "pso/TAdFadeGC.h"
#include "pso/TMainTask.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TKeyBoardControl.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TNowLoading.h"
#include "pso/system/vector.h"

struct Base_8001C8B8_8001C61C { char pad[0x18]; };
struct VObj_8001C8B8_8001C61C : Base_8001C8B8_8001C61C {
    virtual void m0(s32);
};

extern "C" {
s32 __nw__7TObjectFUl(int);
TAdFadeGC *__ct__9TAdFadeGCFP7TObjectPv(TAdFadeGC *storage, TObject *parent, void *mode);
bool TLoadCtrl__sub_8001C60C(void);
void TNowLoading__sub_8001D4D4(void);
u8 *TCameraCtrl__ct(u8 *arg0, void *parent);
void TLoadCtrl__sub_80226DA0(s32 index);
s32 select_area_entrance(void *);
void TAdLoadQuestGC__sub_80309850(void);
void fn_8034AD2C(void);
extern s32 lbl_80515BA0[];
void set_active_camera_pose(u8 *arg0, u8 *arg1);
s32 activate_camera_mode(s32 arg0);
}
void update_sound_request_slots(void);
extern "C" {
s32 TAdLoadQuestGC__ct(s32, void *);
s32 __ct__14TAdFloorLoadGCFP7TObjectPv(s32, void *, int);
extern const char TLoadCtrl__class_name_string[] = "TLoadCtrl";
const char *TLoadCtrl__class_name = TLoadCtrl__class_name_string;
TLoadCtrl *TLoadCtrl__instance;
s32 TLoadCtrl__loading_mode;
TObject *TLoadCtrl__fade_task;
static const Vec now_loading_position = {0.0f, 0.0f, -100.0f};
void TAdLoadQuestGC__sub_8030984C(void);
void TNowLoading__sub_8001D4D0(void);
void fn_8034AD28(void);
void reset__11TCameraCtrlFv(void);

bool TLoadCtrl__sub_8001C60C(void) {
    return TLoadCtrl__instance != NULL;
}

void TLoadCtrl::render() {}

extern void *camera_ctrl_instance;

// Keep the three initializer addresses independent in the native object.
#ifdef __MWERKS__
#pragma push
#pragma pool_data off
#endif
void TLoadCtrl::run_task() {
    s32 o;
    if (TLoadCtrl__instance != NULL) {
        if (TLoadCtrl__fade_task != NULL && TLoadCtrl__fade_task->all_parents_unqueued_for_destruction() == 0) {
            TLoadCtrl__fade_task = NULL;
        }
        if (++m_20 == 2) {
            switch (TLoadCtrl__loading_mode) {
            case 0:
                o = __nw__7TObjectFUl(0x3C);
                if ((u32)o != 0) {
                    TNowLoading__ct(reinterpret_cast<TNowLoading_8001D3A8 *>(o), this, &now_loading_position);
                }
                break;
            case 1:
                o = __nw__7TObjectFUl(0x20);
                if ((u32)o != 0) {
                    TAdLoadQuestGC__ct(o, this);
                }
                break;
            case 2:
                break;
            case 3:
                o = __nw__7TObjectFUl(0x1C);
                if ((u32)o != 0) {
                    __ct__14TAdFloorLoadGCFP7TObjectPv(o, this, 0);
                }
                break;
            case 4:
                o = __nw__7TObjectFUl(0x1C);
                if ((u32)o != 0) {
                    __ct__14TAdFloorLoadGCFP7TObjectPv(o, this, 1);
                }
                break;
            }
        }
        if (m_1c != 0) {
            controller_stuff();
            TKeyBoardControl::update_input_frame();
        }
        update_sound_request_slots();
        Vec camera_position = {0.0f, 0.0f, 0.0f};
        Vec camera_direction = {0.0f, 0.0f, -1.0f};
        activate_camera_mode(9);
        set_active_camera_pose((u8 *)&camera_position, (u8 *)&camera_direction);
    }
}

#ifdef __MWERKS__
#pragma pop
#endif

TLoadCtrl::~TLoadCtrl() {
    if (TLoadCtrl__fade_task != NULL) {
        TLoadCtrl__fade_task->queue_destruction();
        TLoadCtrl__fade_task = NULL;
    }
    if (TLoadCtrl__instance != NULL) {
        TLoadCtrl__instance = NULL;
    }
}

} // extern "C"

TLoadCtrl::TLoadCtrl(TObject *parent) : TObject(parent) {
    m_1c = 1;
    TLoadCtrl__fade_task = NULL;
    m_20 = 0;
    m_name = TLoadCtrl__class_name;
    if (static_cast<u32>(TLoadCtrl__loading_mode) == 0U || static_cast<u32>(TLoadCtrl__loading_mode) == 1U) {
        // The fade task's header only declares its interface. The original
        // allocation includes 0x1C bytes of fade state after TObject.
        TAdFadeGC *fade = static_cast<TAdFadeGC *>(TObject::operator new(0x38));
        if (fade != NULL) {
            fade = __ct__9TAdFadeGCFP7TObjectPv(fade, tl_fade, reinterpret_cast<void *>(2));
        }
        TLoadCtrl__fade_task = fade;
    }
}

extern "C" {
void TLoadCtrl::cleanup_scene() {
    TLoadCtrl *instance = TLoadCtrl__instance;
    if (instance != NULL) {
        instance->queue_destruction();
        TLoadCtrl__instance = NULL;
    }
    switch (TLoadCtrl__loading_mode) {
    case 0:
        TLobby::release_bgm_resource();
        TNowLoading__sub_8001D4D0();
        break;
    case 1:
        TLobby::release_bgm_resource();
        TAdLoadQuestGC__sub_8030984C();
        break;
    case 3:
    case 4:
        TLobby::release_bgm_resource();
        fn_8034AD28();
        break;
    }
    TCameraCtrl::reset_default_view();
    reset__11TCameraCtrlFv();
    if (camera_ctrl_instance != NULL) {
        if (camera_ctrl_instance != NULL) {
            ((VObj_8001C8B8_8001C61C *)camera_ctrl_instance)->m0(1);
        }
        camera_ctrl_instance = NULL;
    }
    TCameraCtrl::reset_view_state();
    TCameraCtrl::init_default_view();
    TCameraCtrl::create();
}

void TLoadCtrl::start_loading(u32 arg0) {
    s32 temp_r3;
    u8 *temp_cam;
    u32 var_r31;
    var_r31 = arg0;
    TCameraCtrl::reset_view_state();
    TCameraCtrl::init_default_view();
    if (var_r31 == 2U) {
        temp_r3 = select_area_entrance(lbl_80515BA0);
        if (temp_r3 == 0) {
            var_r31 = 3U;
        } else if (temp_r3 == 1) {
            var_r31 = 4U;
        } else {
            var_r31 = 0U;
        }
    }
    switch ((s32) var_r31) {
    case 0:
        TNowLoading__sub_8001D4D4();
        break;
    case 1:
        TAdLoadQuestGC__sub_80309850();
        break;
    case 3:
    case 4:
        fn_8034AD2C();
        break;
    }
    TLoadCtrl__loading_mode = static_cast<s32>(var_r31);
    switch ((s32) var_r31) {
    case 2:
        break;
    case 0:
        TLoadCtrl__sub_80226DA0(0);
        break;
    case 1:
        TLoadCtrl__sub_80226DA0(3);
        break;
    case 3:
        TLoadCtrl__sub_80226DA0(1);
        break;
    case 4:
        TLoadCtrl__sub_80226DA0(2);
        break;
    }
    temp_cam = (u8 *) __nw__7TObjectFUl(0x1D4);
    if (temp_cam != NULL) {
        TCameraCtrl__ct(temp_cam, tl_camera);
    }
    TLoadCtrl__instance = new TLoadCtrl(tl_su);
}

void TLoadCtrl::poll_default() { TLoadCtrl::start_loading((u32)((void*)(0))); }
}
