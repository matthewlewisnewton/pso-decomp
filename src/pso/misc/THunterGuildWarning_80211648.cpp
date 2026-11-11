#define TOBJECT_OUT_OF_LINE_HELPERS
#include "types.h"
#include "pso/THunterGuildWarning.h"
#include "pso/TObject.h"
#include "pso/misc/TRaderMapCore.h"

extern "C" {

extern THunterGuildWarning *THunterGuildWarning__instance;

void THunterGuildWarning::queue_destruction() {
    if ((TRaderMapCore::is_not_split_screen() == 1) && (THunterGuildWarning__instance != NULL) && (THunterGuildWarning__instance->all_parents_unqueued_for_destruction() != 0)) {
        THunterGuildWarning__instance->TObject::queue_destruction();
    }
}

}
