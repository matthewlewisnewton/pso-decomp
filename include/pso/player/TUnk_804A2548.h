#ifndef PSO_PLAYER_TUNK_804A2548_H
#define PSO_PLAYER_TUNK_804A2548_H
#include "types.h"
#include "pso/item/TUnk_804E355C.h"

class TUnk_804A2548 : public TUnk_804E355C {
public:
    virtual ~TUnk_804A2548();
    virtual void run_task();
    u8 unk_C4[0x4];
};
typedef char TUnk_804A2548_size[sizeof(TUnk_804A2548) == 0xC8 ? 1 : -1];


// Legacy entry for construction in storage allocated by the caller.
extern "C" void *construct_explosion_collider__13TUnk_804A2548Fv(void *storage, TObject *parent, void *params);

#endif
