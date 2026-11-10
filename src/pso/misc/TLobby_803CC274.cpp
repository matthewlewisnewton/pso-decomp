#include <dolphin/os/OSCache.h>

extern "C" void invalidate_cache__6TLobbyFv(void *address, u32 length) {
    DCInvalidateRange(address, length);
}
