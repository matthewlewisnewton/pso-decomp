#include "types.h"
#include "pso/unk/text_802A1144.h"

    extern unsigned char opening_movie_purpose;

unsigned char get_opening_movie_purpose(void) {  return opening_movie_purpose; }

void set_opening_movie_purpose(int a0) { opening_movie_purpose = a0; }
