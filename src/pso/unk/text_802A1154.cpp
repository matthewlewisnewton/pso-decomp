#include "pso/TMainTask.h"
#include "types.h"
#include "pso/unk/text_802A1154.h"
#include "pso/system/main_loop.h"
#include "pso/TObject.h"

struct RecoveredGlobal_802A1154_main_task {
    s32 value;
    u8 remaining[0x30];
};

extern "C" {
typedef char RecoveredGlobal_802A1154_main_task_size[sizeof(RecoveredGlobal_802A1154_main_task) == 0x34 ? 1 : -1];
void fn_802A1154(void) {
    main_task.delete_layer_children();
    render_tick();
}

}
