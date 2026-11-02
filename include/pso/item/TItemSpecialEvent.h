#ifndef PSO_ITEM_TITEMSPECIALEVENT_H
#define PSO_ITEM_TITEMSPECIALEVENT_H
#include "types.h"
#include "pso/item/TItemObject.h"

// Tool group 20 (item data byte 1): Chocolate, Candy, Cake, the seven event
// badges, Bouquet and Decoction. ItemPMT type 20 records point at text IDs
// 0x78-0x84 (skipping 0x7B), and use dispatches the technique-indexed
// TEndingPic handler. The executable has no class-name string or vtable RTTI
// for this class; TItemSpecialEvent is an explicit inferred name for the
// special-event item group, not a recovered symbol. See
// docs/evidence/titem-special-event-group-evidence.md.
class TItemSpecialEvent : public TItemObject {
public:
    TItemSpecialEvent(TObject *parent, u8 *item);
    // Declared first: its TU (0x803531FC) emits the vtable, not the files
    // holding the destructor and constructor.
    virtual void apply_use_effect();
    virtual ~TItemSpecialEvent();
    static TItemSpecialEvent *create(u8 *item);
};

#endif
