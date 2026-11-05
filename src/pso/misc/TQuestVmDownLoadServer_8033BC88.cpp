#include "pso/misc/TCheckMemoryCard.h"

void TCheckMemoryCard::init(const void *message, s32 selection, u32 first, u32 second) {
    close_windows();
    create_message_and_menu(message, selection, first, second);
}
