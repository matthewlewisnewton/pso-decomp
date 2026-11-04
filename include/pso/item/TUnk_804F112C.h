#ifndef PSO_ITEM_TUNK_804F112C_H
#define PSO_ITEM_TUNK_804F112C_H
#include "types.h"
#include <stddef.h>
#include "pso/item/TItemObject.h"

class TUnk_804F112C : public TItemObject {
public:
    TUnk_804F112C(TObject *parent, u8 *item);
    // Declared first: its TU (0x803531FC) emits the vtable, not the files
    // holding the destructor and constructor.
    virtual void apply_use_effect();
    virtual ~TUnk_804F112C();
    static TUnk_804F112C *create(u8 *item);

    // Use-effect steps selected by technique index. Each one only uses
    // TObjPlayer *owner. The original object emitted them in the
    // ending-picture unit, so the definitions stay in TEndingPic.cpp.
    void send_obj_position_event(s32 arg1);
    void sub_8035307C();
    void sub_803530A0();
    void sub_803530C4();
    void sub_80353110();
    void sub_80353134();
    void sub_80353158();
    void sub_80353194();
    void sub_803531D0();
    void sub_803531F8();
};

typedef char TUnk_804F112COwnerOffset[(offsetof(TUnk_804F112C, owner) == 0xF0) ? 1 : -1];

#endif
