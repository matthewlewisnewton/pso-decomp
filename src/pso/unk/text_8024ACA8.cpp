#include "pso/ui/PlayerWindowDispatch.h"
#include "types.h"
#include "pso/unk/text_8024ACA8.h"

#include <stddef.h>

extern "C" {
extern PlayerWindowCommand lbl_804CEA40;
void TWindowReturnCity__sub_8024ACA8(s32 arg0) {
    PlayerWindowCommand callback = lbl_804CEA40;
    dispatch_player_window_command(arg0, callback);
}

}
