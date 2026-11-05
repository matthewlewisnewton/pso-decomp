#include "types.h"
#include "pso/misc/TOWreckAncientBrakable.h"

#pragma readonly_strings on

extern "C" {

void *TOWreckAncientBrakable__ct(TOWreckAncientBrakable *arg0);
void *__dt__22TOWreckAncientBrakableFv(void *arg0, s16 arg1);
void TOWreckAncient__ct(void *);
void __dl__7TObjectFPv(void *);
void *__dt__14TOWreckAncientFv(void *arg0, s16 arg1);

extern s32 __vt__22TOWreckAncientBrakable[];

void *__dt__22TOWreckAncientBrakableFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__22TOWreckAncientBrakable;
        __dt__14TOWreckAncientFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

extern void *TOWreckAncientBrakable__name;

void *TOWreckAncientBrakable__ct(TOWreckAncientBrakable *wreck_ancient_brakable) {
    TOWreckAncient__ct(wreck_ancient_brakable);
    *(s32 **)((s8 *)wreck_ancient_brakable + 0x18) = __vt__22TOWreckAncientBrakable;
    *(void * *)&wreck_ancient_brakable->m_name = TOWreckAncientBrakable__name;
    wreck_ancient_brakable->m_b4 = 0;
    wreck_ancient_brakable->m_b8 = -1;
    return wreck_ancient_brakable;
}

void *TOWreckAncientBrakable__name = (char *)"TOWreckAncientBrakable";

}
