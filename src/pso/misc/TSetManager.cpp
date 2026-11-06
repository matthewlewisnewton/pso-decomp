#include "types.h"
#include "pso/misc/TSetManager.h"
#include "pso/TSetManager.h"

extern "C" {

void __ct__7TObjectFP7TObject(void *);

extern s32 __vt__11TSetManager[];
extern void *lbl_805D3638;

void *TSetManager__ct(void *set_manager) {
    __ct__7TObjectFP7TObject(set_manager);
    *(s32 **)((s8 *)set_manager + 0x18) = __vt__11TSetManager;
    *(void * *)&((TSetManager *)set_manager)->m_name = lbl_805D3638;
    *(u32 *)((s8 *)set_manager + 0x1C) = 0;
    return set_manager;
}

}
