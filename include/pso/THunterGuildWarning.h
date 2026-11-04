#ifndef PSO_THUNTERGUILDWARNING_H
#define PSO_THUNTERGUILDWARNING_H

#include "pso/TObject.h"
#include "types.h"
#include <stddef.h>

class TWindowMessage;

class THunterGuildWarning : public TObject {
public:
    THunterGuildWarning(TObject *arg1, void *arg2);
    virtual ~THunterGuildWarning();
    virtual void run_task();
public:
    static void queue_destruction();
    static void create_instance(s32 arg0);
    static u8 is_active();
    void close_windows();

    s32 m_warning_type;
    s32 m_timer;
    TWindowMessage *m_windows[4];
};

typedef char THunterGuildWarning_size[sizeof(THunterGuildWarning) == 0x34 ? 1 : -1];
typedef char THunterGuildWarning_mode_offset[offsetof(THunterGuildWarning, m_warning_type) == 0x1C ? 1 : -1];
typedef char THunterGuildWarning_timer_offset[offsetof(THunterGuildWarning, m_timer) == 0x20 ? 1 : -1];
typedef char THunterGuildWarning_windows_offset[offsetof(THunterGuildWarning, m_windows) == 0x24 ? 1 : -1];

#endif
