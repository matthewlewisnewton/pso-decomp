#ifndef PSO_PROTOCOL_NETWORK_RUNTIME_SLOTS_H
#define PSO_PROTOCOL_NETWORK_RUNTIME_SLOTS_H
#include "types.h"
#include <stddef.h>
#include "dolphin/os/OSMessage.h"
#include "dolphin/os/OSMutex.h"
#include "dolphin/os/OSAlarm.h"

struct NetworkAlarmSlot {
    s32 active;
    OSAlarm alarm;
    OSMessageQueue queue;
    OSMessage message;
};
struct NetworkMutexSlot {
    s32 active;
    u32 handle;
    OSMutex mutex;
};
struct NetworkMessageSlot {
    s32 active;
    u8 data[20];
};
struct NetworkMessageQueueSlot {
    s32 active;
    u32 handle;
    OSMessageQueue queue;
    NetworkMessageSlot messages[32];
    OSMessage pending[32];
};
// Native array strides and handle targets used by runtime initialization.
typedef char NetworkAlarmSlot_size[(sizeof(NetworkAlarmSlot) == 0x58) ? 1 : -1];
typedef char NetworkMutexSlot_size[(sizeof(NetworkMutexSlot) == 0x20) ? 1 : -1];
typedef char NetworkMessageQueueSlot_size[(sizeof(NetworkMessageQueueSlot) == 0x3A8) ? 1 : -1];
typedef char NetworkMutexSlot_mutex_offset[(offsetof(NetworkMutexSlot, mutex) == 8) ? 1 : -1];
typedef char NetworkMessageQueueSlot_queue_offset[(offsetof(NetworkMessageQueueSlot, queue) == 8) ? 1 : -1];

extern "C" {
extern NetworkAlarmSlot lobby_alarm_slot_table[64];
extern NetworkMutexSlot network_mutex_slot_table[8];
extern NetworkMessageQueueSlot network_message_queue_slot_table[2];
}
#endif
