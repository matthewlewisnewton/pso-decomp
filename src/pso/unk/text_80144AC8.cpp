#include "pso/TNECFontEORFunction.h"

extern "C" const char *TNECFontEORFunction__name;

TNECFontEORFunction::TNECFontEORFunction() : TObject(&end_of_render_root) {
    m_name = TNECFontEORFunction__name;
}
