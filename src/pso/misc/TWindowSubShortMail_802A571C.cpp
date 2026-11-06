#include "types.h"
#include "pso/misc/TWindowMenu.h"
#include "pso/misc/TWindowSubComCardList.h"
#include "pso/misc/TWindowSubShortMail.h"
#include "pso/misc/TWindowMessageYesNo.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowSubTradeMain.h"
#include "pso/object/TObjCityMainWarp.h"
#include "pso/ui/TAdChrSelASlotGC.h"

void TWindowSubShortMail::notify_warp_flag70() { void* m = *(void* *)&this->m_2c; if (m) ((TWindowSubComCardList *)m)->set_flag70_bit10(); }
