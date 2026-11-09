#include "types.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TWindowAddition.h"
#include "pso/misc/TWindowMenuIconLine.h"
#include "pso/misc/TUnk_804D0948.h"
#include "pso/misc/TLobby.h"

extern "C" {


extern const char *lbl_805D39D0;
extern f32 lbl_805DD340;
extern f32 lbl_805DD344;

void TUnk_804D0948::sub_8026DE94(s32 heading) {
    m_name = lbl_805D39D0;
    ensure_status_display(heading);
    create_menu_scroll_bar();
    this->set_depth(lbl_805DD340);
    if (TCameraCtrl::get_camera_id() > 2) {
        set_position_xy(lbl_805DD344, lbl_805DD344);
    }
    *(s32 *)&this->unk_88 = 0;
}

}
