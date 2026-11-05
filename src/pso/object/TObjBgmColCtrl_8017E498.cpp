#include "types.h"
#include "pso/object/TObjBgmColCtrl_8017E498.h"
#include "pso/object/TObjBgmColCtrl.h"

extern "C" {

void __ct__7TObjectFP7TObject(void *);

extern s32 __vt__14TObjBgmColCtrl[];
extern void *TObjBgmColCtrl__name;
extern u32 TObjBgmColCtrl__current_theme_id;

void *TObjBgmColCtrl__ct(void *bgm_col_ctrl) {
    __ct__7TObjectFP7TObject(bgm_col_ctrl);
    *(s32 **)((s8 *)bgm_col_ctrl + 0x18) = __vt__14TObjBgmColCtrl;
    *(void * *)&((TObjBgmColCtrl *)bgm_col_ctrl)->m_name = TObjBgmColCtrl__name;
    ((TObjBgmColCtrl *)bgm_col_ctrl)->m_1c = 3;
    TObjBgmColCtrl__current_theme_id = 0;
    return bgm_col_ctrl;
}

}
