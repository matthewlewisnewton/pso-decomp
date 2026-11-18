#include "types.h"
#include "pso/misc/TWindowChoiceSetting_80249610.h"
#include "pso/misc/TUnk_804D0658.h"
#include "pso/misc/TWindowChoiceSetting.h"
#include "pso/misc/TWindowFukidasi.h"
#include "pso/misc/TWindowSubComCard.h"

typedef struct Ctrl_8024966C {
    u8 pad0[0x14];
    TWindowFukidasi *head;
} Ctrl_8024966C;

extern "C" {
s32 TWindowCtrlMain__sub_8024CDD0(s32 arg0);

int TUnk_804D0658::is_selected() { return (this->m_70 >> 5) & 0x1; }
TWindowFukidasi *TWindowFukidasi::find_viewport_overlap(const f32 *position, const f32 *size, s32 viewport) {
    Ctrl_8024966C *ctrl = (Ctrl_8024966C *)TWindowCtrlMain__sub_8024CDD0(viewport);
    return find_overlapping_balloon(position, size, ctrl->head);
}
}

void resolve_chat_balloon_overlaps(void) {
    s32 i;
    TWindowFukidasi *p;
    TWindowFukidasi *q;
    for (i = 0; i < 6; i++) {
        p = ((Ctrl_8024966C *)TWindowCtrlMain__sub_8024CDD0(i))->head;
        if (p != NULL) {
            while (p != NULL) {
                p->hide();
                p = p->next;
            }
        }
    }
    for (i = 0; i < 6; i++) {
        p = ((Ctrl_8024966C *)TWindowCtrlMain__sub_8024CDD0(i))->head;
        if (p != NULL) {
            while (p->next != NULL) {
                q = p->find_balloon_overlap_for(p->next);
                while (q != NULL) {
                    if (p->get_visible_flag() != 0) {
                        TWindowFukidasi__sub_80249788(q);
                    } else if (q->get_visible_flag() != 0) {
                        TWindowFukidasi__sub_80249788(p);
                    } else if (p->rise > q->rise) {
                        TWindowFukidasi__sub_80249788(p);
                    } else {
                        TWindowFukidasi__sub_80249788(q);
                    }
                    q = p->find_balloon_overlap_for(q->next);
                }
                p = p->next;
            }
        }
    }
}

void TWindowFukidasi__sub_80249788(void* p) { *(u32*)((char*)p + 0x2c) |= 0x400; }
void TWindowFukidasi::hide() { *(u32*)((char*)this + 0x2c) &= 0xfffffbff; }
