#ifndef PSO_UNK_TUNK_804A4020_H
#define PSO_UNK_TUNK_804A4020_H
#include "types.h"
#include "pso/TItemShootModel.h"

class TUnk_804A4020 : public TItemShootModel {
public:
    virtual ~TUnk_804A4020();
    virtual void hook();
    virtual void render();
};
typedef char TUnk_804A4020_size[sizeof(TUnk_804A4020) == 0x6C ? 1 : -1];

#endif
