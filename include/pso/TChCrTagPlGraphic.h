#ifndef PSO_TCHCRTAGPLGRAPHIC_H
#define PSO_TCHCRTAGPLGRAPHIC_H
#include "pso/TChCrTag.h"
#include "types.h"

class TChCrTagPlGraphic : public TChCrTag {
public:
    virtual void render_shadows();
    virtual ~TChCrTagPlGraphic();
    virtual void render();
    virtual void run_task();
public:
    static void *create(void *arg0);
    static void create_matching_tags();
    void draw_class_illustration();
};

#endif
