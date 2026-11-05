#ifndef PSO_TNECFONTEORFUNCTION_H
#define PSO_TNECFONTEORFUNCTION_H

#include "pso/TObject.h"
#include "types.h"
#include "pso/system/GinjaMaterialState.h"

class TNECFontEORFunction : public TObject {
public:
    TNECFontEORFunction();
    virtual ~TNECFontEORFunction();
    virtual void run_task();
};

extern "C" {
extern s16 *menu_font_palette;
extern u32 menu_font_upload_flags;
extern u8 lbl_805D56C0;
extern TNECFontEORFunction *menu_font_object;
__declspec(section ".data") extern GinjaTextureList menu_font_texture_list;
extern GinjaTextureEntry lbl_8050C090[2];
}

#endif
