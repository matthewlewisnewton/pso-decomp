#include "types.h"
#include "pso/unk/text_803CE568.h"
#include "pso/misc/TLobby_803CFE68.h"
#include "pso/misc/TLobby.h"



void cvfs_forward_error(s32, const char *message, s32 handle) {
    if (cvfs_completion_callback != NULL) {
        cvfs_completion_callback(lbl_805D75FC, message, handle);
    }
}

void TLobby__sub_803CFE9C(s32, DVDFileInfo *) {

}
