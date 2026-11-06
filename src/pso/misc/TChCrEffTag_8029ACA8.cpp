#include "types.h"
#include "pso/misc/TChCrEffTag_8029ACA8.h"
#include "pso/TChCrEffTag.h"

extern "C" {

void *__ct__11TChCrEffTagFv(void *, void *);
void *__nw__7TObjectFUl(int);

    extern int TChCrEffTag__selected_heading;
void TChCrEffTag::set_eff_tag(int a0) { TChCrEffTag__selected_heading = a0; }
}

void *create_TChCrEffTag(void *ch_cr_eff_tag) {
    void *o = __nw__7TObjectFUl(0x2C);
    if (o != NULL) {
        o = __ct__11TChCrEffTagFv(o, ch_cr_eff_tag);
    }
    return o;
}
