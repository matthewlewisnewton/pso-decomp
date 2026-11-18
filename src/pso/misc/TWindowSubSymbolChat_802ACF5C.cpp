#include "types.h"
#include "pso/unk/text_8026CB5C.h"
#include "pso/misc/TWindowSubSymbolChat.h"
#include "pso/ui/TAdEnterSerialAccessGC.h"

void *TWindowSubSymbolChat::update_display(WindowCallback callback) {
    s32 zero_vec2;

    zero_vec2 = (s32)get_zero_vec2();
    return TAdEnterSerialAccessGC::create_callback((void *)(get_zero_vec2()), (void *)zero_vec2, callback);
}
