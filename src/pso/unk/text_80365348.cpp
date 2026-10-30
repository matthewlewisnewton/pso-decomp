#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/unk/text_80365348.h"

typedef struct Ent_803653A4 { s32 id; s32 arg; } Ent_803653A4;

extern "C" {
extern u32 labo_design_object_table[];
}
extern Ent_803653A4 lbl_804F2C08[];
void free_object_table(void) {
    s32 i;
    for (i = 5; i >= 0; i--) {
        if (labo_design_object_table[i] != 0) {
            delete (BmlResource *)((void *)labo_design_object_table[i]);
            labo_design_object_table[i] = 0;
        }
    }
}

void fn_803653A4(void) {
    s32 i;
    Ent_803653A4 *e;
    void *p;
    for (i = 0; i < 6; i++) {
        labo_design_object_table[i] = 0;
    }
    e = lbl_804F2C08;
    if (e != NULL) {
        while (e->id != -1) {
            p = new BmlResource(5, (BmlResourceDescriptor *)(e->arg), 0, 0, (void *)(0));
            labo_design_object_table[e->id] = (u32)p;
            e++;
        }
    }
}
