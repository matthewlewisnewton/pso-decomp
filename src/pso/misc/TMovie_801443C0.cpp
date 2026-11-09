#include "pso/system/RelModuleBuffer.h"
#include "types.h"
#include "pso/misc/TMovie_801443C0.h"
#include "pso/misc/TMovie.h"
#include "pso/system/main_loop.h"
#include "pso/misc/TLobby.h"

extern "C" {

s32 render_until_finished__6TMovieFv(void *);
s32 __dl__7TObjectFPv(void *);
s32 __dt__7TObjectFv(void *, s32);

extern void *__vt__6TMovie[];

void *__dt__6TMovieFv(TMovie *arg0, s16 arg1) {
    s32 (*temp_r12)(void *);
    u32 t;

    if (arg0 != NULL) {
        *(void **)((s8 *)arg0 + 0x18) = __vt__6TMovie;
        render_until_finished__6TMovieFv(arg0);
        render_tick();
        t = arg0->m_20;
        if (t != 0U) {
            close__6TMovieFis(t, 1);
            arg0->m_20 = 0U;
        }
        render_tick();
        render_tick();
        RelModuleBuffer *module = arg0->m_1c;
        if (module != 0) {
            fn_80320358(module, 1);
            arg0->m_1c = 0;
        }
        render_tick();
        temp_r12 = *(s32 (**)(void *))((s8 *)arg0 + 0x44);
        if (temp_r12 != NULL) {
            temp_r12(arg0);
        }
        TLobby::set_pre_retrace_callback();
        __dt__7TObjectFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

}
