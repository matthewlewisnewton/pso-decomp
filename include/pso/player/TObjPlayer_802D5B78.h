#ifndef PSO_PLAYER_TOBJPLAYER_802D5B78_H
#define PSO_PLAYER_TOBJPLAYER_802D5B78_H

#include <dolphin/mtx/GeoTypes.h>

// Keep the callback's hit argument provisional; the implementation qualifies
// its ActorBodyHit/CollisionBody layout. Both vectors require live Vec storage.
extern "C" void TObjPlayer__sub_802D5B78(void *hit, Vec *output, const Vec *direction);

#endif
