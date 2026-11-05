#ifndef PSO_MISC_SOFTKEYBOARDWINDOWDESCRIPTOR_H
#define PSO_MISC_SOFTKEYBOARDWINDOWDESCRIPTOR_H

#include "types.h"
#include <stddef.h>

// Observed prefix used by the window constructor; source ownership and names
// of the fields remain provisional.
struct SoftKeyboardWindowDescriptor {
    f32 extent[2];
    f32 order;
    void *layout_entries;
    u32 flags;
};
typedef char SoftKeyboardWindowDescriptor_size[sizeof(SoftKeyboardWindowDescriptor) == 0x14 ? 1 : -1];
typedef char SoftKeyboardWindowDescriptor_layout_offset[offsetof(SoftKeyboardWindowDescriptor, layout_entries) == 0xC ? 1 : -1];
typedef char SoftKeyboardWindowDescriptor_flags_offset[offsetof(SoftKeyboardWindowDescriptor, flags) == 0x10 ? 1 : -1];
extern "C" {
extern SoftKeyboardWindowDescriptor soft_keyboard_window_and_action_data;
}
#endif
