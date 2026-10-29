#include "types.h"
#include "pso/item/TItemLoad_8010FDF0.h"
#include "pso/item/TItemMag.h"
#include "pso/misc/TLobby.h"
#include "pso/TItemLoad.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct RecoveredGlobal_80019E60_lbl_804340D8 { char value[0x13]; };
typedef char RecoveredGlobal_80019E60_lbl_804340D8_size[sizeof(RecoveredGlobal_80019E60_lbl_804340D8) == 0x13 ? 1 : -1];

extern RecoveredGlobal_80019E60_lbl_804340D8 lbl_804340D8;
extern s32 lbl_805D49D8;
extern u32 item_loader_instance;

void TLobby::free_item_loader() {
    if ((u32) item_loader_instance != 0U) {
        delete (RelocatedFile *)item_loader_instance;
        item_loader_instance = 0U;
        lbl_805D49D8 = 0;
    }
}
void TLobby::load_draw_line_task() {
    RelocatedFile *file = new RelocatedFile(lbl_804340D8.value, 0x4800);
    item_loader_instance = (u32)file;
    if (file != NULL) {
        lbl_805D49D8 = (s32)file->get_root();
    }
}
