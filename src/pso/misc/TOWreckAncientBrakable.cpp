#include "types.h"
#include "pso/misc/TOWreckAncientBrakable.h"

extern "C" {

void *TOWreckAncientBrakable__ct(TOWreckAncientBrakable *arg0);
void TOWreckAncient__ct(void *);

extern s32 __vt__22TOWreckAncientBrakable[];

TOWreckAncientBrakable::~TOWreckAncientBrakable() {}

extern const char *TOWreckAncientBrakable__name;

void *TOWreckAncientBrakable__ct(TOWreckAncientBrakable *wreck_ancient_brakable) {
    TOWreckAncient__ct(wreck_ancient_brakable);
    *(s32 **)((s8 *)wreck_ancient_brakable + 0x18) = __vt__22TOWreckAncientBrakable;
    wreck_ancient_brakable->m_name = TOWreckAncientBrakable__name;
    wreck_ancient_brakable->m_b4 = 0;
    wreck_ancient_brakable->m_b8 = -1;
    return wreck_ancient_brakable;
}


}
