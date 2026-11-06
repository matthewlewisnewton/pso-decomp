#include "types.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/ui/TAdSoniclogo.h"
#include "pso/TAdSoniclogo.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/misc/TLobby.h"

extern "C" {

void __ct__7TObjectFP7TObject(void *);
void *__nw__7TObjectFUl(int);

extern s32 __vt__12TAdSoniclogo[];
extern void *TAdSoniclogo__class_name;
extern u32 TAdSoniclogo__state;
extern u32 TLogo__exit_requested_flag;
extern void *tl_00;
extern s32 request_destroy__12TAdSoniclogoFv[];

void *__ct__12TAdSoniclogoFv(void *ad_soniclogo) {
    void *o;
    __ct__7TObjectFP7TObject(ad_soniclogo);
    *(s32 **)((s8 *)ad_soniclogo + 0x18) = __vt__12TAdSoniclogo;
    *(void * *)&((TAdSoniclogo *)ad_soniclogo)->m_name = TAdSoniclogo__class_name;
    *(u32 *)((s8 *)ad_soniclogo + 0x1C) = 0;
    TAdSoniclogo__state = 0;
    TLogo__exit_requested_flag = 0;
    TAdSinglePlyChrSelectGC::init_logo_state(1);
    o = __nw__7TObjectFUl(0x28);
    if (o != NULL) {
        ((TLobby *)o)->init_fade(tl_00, request_destroy__12TAdSoniclogoFv);
    }
    return ad_soniclogo;
}

void TLogo__sub_8001C360(void) {  }

    extern int sonic_logo_object;
void TLogo__sub_8001C364(void) { sonic_logo_object = get_logo_texture_e_handle(); }

}
