#include "types.h"
#include "pso/unk/text_80309890.h"
extern "C" {
void create__22TChCrTagInformationStrFP7TObjectl(void);
extern s32 char_creation_tag_info_selected_index;
void fn_80309890(void *o, s32 v) {
    if (v == char_creation_tag_info_selected_index || v < -1 || v >= 0xF) {
        return;
    }
    char_creation_tag_info_selected_index = v;
    if (v != -1) {
        create__22TChCrTagInformationStrFP7TObjectl();
    }
}

}
