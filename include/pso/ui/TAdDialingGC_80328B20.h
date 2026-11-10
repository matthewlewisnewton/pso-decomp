#ifndef PSO_UI_TADDIALINGGC_80328B20_H
#define PSO_UI_TADDIALINGGC_80328B20_H

class TAdDialingGC;
struct ColorLineVertex;

extern "C" {
void TAdDialingGC__sub_80328B20(TAdDialingGC *dialing);
void draw_dialing_rectangle(const ColorLineVertex *origin, const ColorLineVertex *extent);
}

#endif
