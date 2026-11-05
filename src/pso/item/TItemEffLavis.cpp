#include "pso/item/TItemEffLavis.h"

extern const char* TItemEffLavis__class_name;
extern const f32 lbl_805DAB40;

void TItemEffLavis::hook() {}
TItemEffLavis::~TItemEffLavis() {}

TItemEffLavis::TItemEffLavis(void* owner, const Vec* start,
                           const Vec* endpoint, f32 life)
    : TItemShootModel(owner, start, endpoint, life) {
    m_name = TItemEffLavis__class_name;
}

TItemEffLavis* create_lavis_shot(void* owner, const Vec* start,
                              const Vec* endpoint, f32 life) {
    TItemEffLavis* result = 0;
    if (lbl_805DAB40 != life && owner != 0) {
        result = new TItemEffLavis(owner, start, endpoint, life);
    }
    return result;
}
