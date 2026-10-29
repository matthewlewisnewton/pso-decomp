#include "pso/enemy/TObjEnemy.h"
#include "types.h"
#include "pso/unk/text_800C3A60.h"

extern "C" {
s32 get_flag_11__16TObjEneRe2FlowerFv();
s32 fn_800C3A60(s32 arg0, s32 arg1) {
    if (get_flag_11__16TObjEneRe2FlowerFv() != 0) {
        switch (arg1) {
        case 0x4003A10E:
            return 0x4003A339;
        case 0x4003A50F:
            return 0x4003A53A;
        case 0x4003AD10:
            return 0x4003A33B;
        case 0x4003A311:
            return 0x4003A63C;
        case 0x4003A812:
            return 0x4003A83D;
        case 0x4003AB13:
            return 0x4003A83E;
        case 0x4003A814:
            return 0x4003A13F;
        case 0x4003A315:
            return 0x4003A341;
        case 0x4003B216:
            return 0x40039942;
        }
    }
    return ((TObjEnemy *)((void *)arg0))->remap_sound_for_area((s32)((void *)arg1));
}

}
