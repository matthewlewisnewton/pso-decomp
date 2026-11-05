#include "pso/misc/TCheckMemoryCard.h"

extern "C" void fn_8033BCDC(TCheckMemoryCard *card, s32 kind, s32 menu, s32 first, s32 second);

void TCheckMemoryCard::update_card_display(s32 kind, s32 menu, s32 first, s32 second) {
    close_windows();
    fn_8033BCDC(this, kind, menu, first, second);
}
