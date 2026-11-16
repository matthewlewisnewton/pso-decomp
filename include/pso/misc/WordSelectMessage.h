#ifndef PSO_MISC_WORDSELECTMESSAGE_H
#define PSO_MISC_WORDSELECTMESSAGE_H

#include "types.h"

// Compact word-select payload, independent of the window displaying it.
struct WordSelectMessage {
    s16 count;
    s16 type;
    s16 ids[4];
};

typedef char WordSelectMessage_size[sizeof(WordSelectMessage) == 12 ? 1 : -1];

// The dispatcher and language formatters share the 16-bit speaker entity ID.
extern "C" {
// Spanish prefix categories, loaded from the word-select archive header.
extern u8 *lbl_805D6E4C;

void show_word_select_message(WordSelectMessage *words, u16 player);
s32 format_word_select_message(WordSelectMessage *words, char *buffer, u16 player);
s32 format_word_select_japanese(WordSelectMessage *words, char *buffer);
s32 format_word_select_english(WordSelectMessage *words, char *buffer, u16 player);
s32 format_word_select_german(WordSelectMessage *words, char *buffer, u16 player);
s32 format_word_select_french(WordSelectMessage *words, char *buffer, u16 player);
s32 format_word_select_spanish(WordSelectMessage *words, char *buffer, u16 player);
s32 word_select_player_gender(u16 player);
}

#endif
