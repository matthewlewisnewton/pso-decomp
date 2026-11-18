#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/THunterGuildWarning.h"

extern THunterGuildWarning *THunterGuildWarning__instance;

void THunterGuildWarning::run_task() {
    switch (m_warning_type) {
    case 0:
    case 1:
        if (--m_timer < 0) {
            this->TObject::queue_destruction();
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
