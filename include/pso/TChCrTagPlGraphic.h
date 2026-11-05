#ifndef PSO_TCHCRTAGPLGRAPHIC_H
#define PSO_TCHCRTAGPLGRAPHIC_H
#include "pso/TChCrTag.h"
#include "types.h"

class TChCrTagPlGraphic : public TChCrTag {
public:
    virtual ~TChCrTagPlGraphic();
    virtual void render();
    virtual void run_task();
    /* Vtable slot 6 is the recovered selection predicate (implemented by
     * TChCrTagPlGraphic__vt4 in the unit). It is not declared as a virtual:
     * MWCC 2.6 takes over vtable emission for a slot-introducing virtual and
     * cannot reproduce the original 0x20-byte table (see
     * docs/evidence/tchcrtagplgraphic-vtable-evidence.md). */
public:
    static void *create(void *arg0);
    static void create_matching_tags();
    void draw_class_illustration();
};

#endif
