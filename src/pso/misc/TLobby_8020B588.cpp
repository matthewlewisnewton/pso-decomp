#include "pso/system/byteswap.h"
#include "pso/unk/text_8020B47C.h"

extern "C" void bswap_4_words__6TLobbyFv(FloorFlagsBuffer *buffer) {
    bswap_32(&buffer->object_offset);
    bswap_32(&buffer->word_04);
    bswap_32(&buffer->enemy_offset);
    bswap_32(&buffer->word_0c);
}
