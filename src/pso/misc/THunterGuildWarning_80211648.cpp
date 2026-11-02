#include "types.h"
#include "pso/THunterGuildWarning.h"
#include "pso/TObject.h"
#include "pso/misc/TRaderMapCore.h"

extern "C" {

void queue_destruction__7TObjectFv(void *arg0);

extern THunterGuildWarning *THunterGuildWarning__instance;

void THunterGuildWarning::queue_destruction() {
    if ((TRaderMapCore::is_not_split_screen() == 1) && (THunterGuildWarning__instance != NULL) && (THunterGuildWarning__instance->all_parents_unqueued_for_destruction() != 0)) {
        queue_destruction__7TObjectFv(THunterGuildWarning__instance);
    }
}

}
