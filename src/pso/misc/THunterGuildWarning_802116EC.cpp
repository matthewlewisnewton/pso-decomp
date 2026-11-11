#include "types.h"
#include "pso/THunterGuildWarning.h"

extern THunterGuildWarning *THunterGuildWarning__instance;

u8 THunterGuildWarning::is_active() {
    return (u8) (THunterGuildWarning__instance != NULL);
}
