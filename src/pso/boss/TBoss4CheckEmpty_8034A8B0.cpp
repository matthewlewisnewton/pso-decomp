#include "types.h"
#include "pso/boss/TBoss4CheckEmpty_8034A8B0.h"
#include "pso/TBoss4CheckEmpty.h"

extern "C" {

void __ct__7TObjectFP7TObject(void *);

extern s32 __vt__16TBoss4CheckEmpty[];
extern void *lbl_805D4318;

void *__ct__16TBoss4CheckEmptyFv(void *boss4_check_empty) {
    __ct__7TObjectFP7TObject(boss4_check_empty);
    *(s32 **)((s8 *)boss4_check_empty + 0x18) = __vt__16TBoss4CheckEmpty;
    *(void * *)&((TBoss4CheckEmpty *)boss4_check_empty)->m_name = lbl_805D4318;
    *(u32 *)((s8 *)boss4_check_empty + 0x1C) = 0;
    return boss4_check_empty;
}

}
