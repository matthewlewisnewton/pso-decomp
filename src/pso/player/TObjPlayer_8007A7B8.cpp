#include "types.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

// TObjPlayer__sub_8007A7B8: clears the player's velocity/state vectors and
// returns the receiver. The hand-mangled name is the symbol in symbols.txt.
void *TObjPlayer__sub_8007A7B8(void *arg0) {
    ((TObjPlayer *)arg0)->clear_velocity_vectors();
    return arg0;
}

}
