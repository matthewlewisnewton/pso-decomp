#include "types.h"
#include "pso/THunterGuildWarning.h"
#include "pso/misc/TRaderMapCore.h"

extern "C" {


extern THunterGuildWarning *THunterGuildWarning__instance;
extern TObject *tl_05;

void THunterGuildWarning::create_instance(s32 arg0) {
    if ((TRaderMapCore::is_not_split_screen() == 1) && (THunterGuildWarning__instance == NULL)) {
        new THunterGuildWarning(tl_05, arg0);
    }
}

}
