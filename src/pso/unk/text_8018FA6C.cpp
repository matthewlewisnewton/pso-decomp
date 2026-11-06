#include "types.h"
struct Obj_8018FA6C { u8 pad0[0x6]; u16 id; u8 pad8[0x4]; Obj_8018FA6C *next; u8 pad10[0x4]; Obj_8018FA6C *children; };

extern "C" {
s32 check_value_equals__13TUnk_804B6C24Fl(void *, s32);
extern s32 TObjDoorKey__class_name;
extern Obj_8018FA6C *tl_05;
Obj_8018FA6C *fn_8018FA6C(u16 id);
Obj_8018FA6C *fn_8018FA6C(u16 id) {
    Obj_8018FA6C *next = tl_05->children;
    Obj_8018FA6C *cur;
    while (tl_05->children != 0 && next != 0) {
        cur = next;
        next = cur->next;
        if (check_value_equals__13TUnk_804B6C24Fl(cur, TObjDoorKey__class_name) != 0 && cur->id == id) {
            return cur;
        }
    }
    return 0;
}

}
