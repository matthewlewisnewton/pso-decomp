#include "types.h"
#include "pso/misc/TWindowKeyBoardBase.h"
#include "pso/misc/TWindowKeyBoardHard.h"
#include "pso/misc/CharacterSaveFlagQueries.h"

int TWindowKeyBoardBase::sub_8025EB68() { return (this->m_60 >> 3) & 0x1; }

int test_saved_character_flag_128(s32 client) { return TWindowKeyBoardHard::test_card_flag(client, 128); }
int test_saved_character_flag_64(s32 client) { return TWindowKeyBoardHard::test_card_flag(client, 64); }
int test_saved_character_flag_32(s32 client) { return TWindowKeyBoardHard::test_card_flag(client, 32); }
int test_saved_character_flag_16(s32 client) { return TWindowKeyBoardHard::test_card_flag(client, 16); }
