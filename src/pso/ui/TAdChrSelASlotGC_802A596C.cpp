#include "types.h"
#include "pso/misc/TWindowMenu.h"
#include "pso/ui/TAdChrSelASlotGC.h"
#include "pso/misc/TWindowMessageYesNo.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowSubShortMail.h"
#include "pso/misc/TWindowSubTradeMain.h"
#include "pso/object/TObjCityMainWarp.h"

extern "C" {

int open_yes_no_prompt(void* a0 = 0, void* a1 = 0, void* a2 = 0, void* a3 = 0);

void TAdChrSelASlotGC::forward_slot_selection(void* a1, void* a2) { open_yes_no_prompt(this, (void*)0, a1, a2); }

}
