#include "types.h"
#include "pso/unk/TUnk_804A5D10.h"
#include "pso/player/TObjPlayer_8012E760.h"

extern "C" {

int queue_destruction__7TObjectFv(void*);


}
TUnk_804A5D10::~TUnk_804A5D10() {

}
int expire_weapon_casing(void* p) { return queue_destruction__7TObjectFv(p); }
