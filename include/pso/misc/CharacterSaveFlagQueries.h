#ifndef PSO_MISC_CHARACTER_SAVE_FLAG_QUERIES_H
#define PSO_MISC_CHARACTER_SAVE_FLAG_QUERIES_H

#include "types.h"

// These queries forward the observed client word to the save-record lookup.
// They do not receive a hardware-keyboard object. Suffixes are decimal masks.
int test_saved_character_flag_128(s32 client);
int test_saved_character_flag_64(s32 client);
int test_saved_character_flag_32(s32 client);
int test_saved_character_flag_16(s32 client);

#endif
