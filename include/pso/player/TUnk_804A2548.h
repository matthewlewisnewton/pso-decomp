#ifndef PSO_PLAYER_TUNK_804A2548_H
#define PSO_PLAYER_TUNK_804A2548_H
#include "types.h"
#include "pso/item/TUnk_804E355C.h"

class TUnk_804A2548 : public TUnk_804E355C {
public:
    virtual ~TUnk_804A2548();
    TUnk_804A2548(TObject *parent, void *params);
    virtual void run_task();
    u8 unk_C4[0x4];
};
typedef char TUnk_804A2548_size[sizeof(TUnk_804A2548) == 0xC8 ? 1 : -1];

extern "C" {
void *__dt__13TUnk_804A2548Fv(void *arg0, s16 arg1);
}

#endif
