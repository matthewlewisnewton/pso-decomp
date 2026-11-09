#include "pso/misc/TWindowMessageQuest.h"
extern "C" {
extern s32 lbl_805D39A0;
extern s32 local_client_id;
}
TWindowMessageQuest::TWindowMessageQuest(s32 layout)
    : TWindowMessage(layout, 1, local_client_id) {
    m_name = (const char *)lbl_805D39A0;
    m_90 = 0;
}
