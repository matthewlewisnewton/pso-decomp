#include "types.h"
#include "pso/misc/TUnk_804CDFE8.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/misc/TWindowChoiceSetting.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowSubTradeMain.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

int TWindowSubStatusDisp::is_flag80_set() { return *(u16 *)&this->m_name & 0x80; }
