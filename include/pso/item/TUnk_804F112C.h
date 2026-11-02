#ifndef PSO_ITEM_TUNK_804F112C_H
#define PSO_ITEM_TUNK_804F112C_H
#include "types.h"
#include "pso/item/TItemObject.h"

// Tool group 20 (item data byte 1): Chocolate, Candy, the event badges,
// Bouquet, Decoction and Christmas Present. ItemPMT type 20 records point at
// text IDs 0x78-0x84, and use dispatches the technique-indexed TEndingPic
// handler. The executable has no class-name string or vtable RTTI for this
// class, so it keeps its vtable-address placeholder. See
// docs/evidence/tunk-804f112c-event-item-group-evidence.md.
class TUnk_804F112C : public TItemObject {
public:
    TUnk_804F112C(TObject *parent, u8 *item);
    // Declared first: its TU (0x803531FC) emits the vtable, not the files
    // holding the destructor and constructor.
    virtual void apply_use_effect();
    virtual ~TUnk_804F112C();
    static TUnk_804F112C *create(u8 *item);
};

#endif
