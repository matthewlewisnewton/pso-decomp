#include "pso/THunterGuildWarning.h"
#include "pso/object/TObject_80019A50.h"

extern THunterGuildWarning *THunterGuildWarning__instance;

void THunterGuildWarning::run_task() {
    switch (m_warning_type) {
    case 0:
    case 1:
        if (--m_timer < 0) {
            queue_destruction__7TObjectFv(this);
        }
        break;
    case 2:
        break;
    }
}

THunterGuildWarning::~THunterGuildWarning() {
    close_windows();
    THunterGuildWarning__instance = 0;
}
