#include "types.h"
#include "pso/boss/TObjBoss5FloorGrass_8028AAB8.h"
#include "pso/TObjBoss5FloorGrass.h"

extern "C" {

void __ct__7TObjectFP7TObject(void *);

extern s32 __vt__19TObjBoss5FloorGrass[];
extern void *lbl_805D3B20;

void *__ct__19TObjBoss5FloorGrassFv(void *boss5_floor_grass) {
    __ct__7TObjectFP7TObject(boss5_floor_grass);
    *(s32 **)((s8 *)boss5_floor_grass + 0x18) = __vt__19TObjBoss5FloorGrass;
    *(void * *)&((TObjBoss5FloorGrass *)boss5_floor_grass)->m_name = lbl_805D3B20;
    return boss5_floor_grass;
}

}
