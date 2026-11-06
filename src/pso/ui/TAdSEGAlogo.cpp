#include "pso/TAdSEGAlogo.h"
#include "pso/ui/TAdSEGAlogo.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

TAdSEGAlogo::~TAdSEGAlogo() {}

#include "types.h"
#include "pso/misc/TLobby.h"

extern "C" {

void __ct__7TObjectFP7TObject(void *);
void *__nw__7TObjectFUl(int);

extern s32 __vt__11TAdSEGAlogo[];
extern void *TAdSEGAlogo__class_name;
extern u32 TAdSEGAlogo__state;
extern u32 sega_logo_done_flag;
extern void *tl_00;
extern s32 request_destroy__11TAdSEGAlogoFv[];

void *__ct__11TAdSEGAlogoFv(void *ad_seg_alogo) {
    void *o;
    __ct__7TObjectFP7TObject(ad_seg_alogo);
    *(s32 **)((s8 *)ad_seg_alogo + 0x18) = __vt__11TAdSEGAlogo;
    *(void * *)&((TAdSEGAlogo *)ad_seg_alogo)->m_name = TAdSEGAlogo__class_name;
    *(u32 *)((s8 *)ad_seg_alogo + 0x1C) = 0;
    TAdSEGAlogo__state = 0;
    sega_logo_done_flag = 0;
    TAdSinglePlyChrSelectGC::init_logo_state(0);
    o = __nw__7TObjectFUl(0x28);
    if (o != NULL) {
        ((TLobby *)o)->init_fade(tl_00, request_destroy__11TAdSEGAlogoFv);
    }
    return ad_seg_alogo;
}

}
