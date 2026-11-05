#include "types.h"
struct E_802A9568 { s32 a; s32 b; };

extern "C" {
extern E_802A9568 *indirect_recipe_buffer;
E_802A9568 *get_indirect_recipe(s32 i);
E_802A9568 *get_indirect_recipe(s32 i) {
    if (i >= 0x40) return 0;
    return &indirect_recipe_buffer[i];
}

}
