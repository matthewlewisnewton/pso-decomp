#include "types.h"
#include "pso/unk/text_803CC294.h"
#include "pso/misc/TLobby.h"

extern "C" {

u8 *alloc_from_heap__6TLobbyFPv(s32);
u8 *link_into_list__6TLobbyFv();
s32 strncpy(void *, const char *, s32);

struct FileLoadEntry {
    s32 state;
    s32 unused_04;
    char name[0x20];
    s32 unused_28;
    s32 unused_2c;
    s32 file_count;
    s32 field_34;
    s32 unused_38;
    s32 field_3c;
    void (*callback)(void *);
    // Eight words are copied starting at +0x44. Callback-specific fields
    // occupy the beginning of this storage; the whole copy spans 0x20 bytes.
    u8 params[0x20];
    u8 rest[0x68 - 0x64];
};

typedef char FileLoadEntry_size[sizeof(FileLoadEntry) == 0x68 ? 1 : -1];
typedef char FileLoadEntry_callback[offsetof(FileLoadEntry, callback) == 0x40 ? 1 : -1];

s32 TLobby::create_file_load_entry(const char *name, s32 arg1, void (*callback)(void *), void *arg3, void **arg4) {
    FileLoadEntry *entry;
    AdxfHandle *file;

    if (arg4 != NULL) {
        *arg4 = NULL;
    }
    file = ADXF_Open(name, 0);
    if (file == NULL) {
        return -2;
    }
    if (ADXF_GetFsizeByte(file) > 0x40000) {
        ADXF_Close(file);
        return -3;
    }
    entry = (FileLoadEntry *)alloc_from_heap__6TLobbyFPv(0x68);
    if (entry != NULL) {
        entry = (FileLoadEntry *)link_into_list__6TLobbyFv();
    }
    strncpy(entry->name, name, 0x20);
    entry->state = 2;
    entry->field_3c = arg1;
    entry->file_count = ADXF_GetFsizeSct(file);
    ADXF_Close(file);
    entry->field_34 = 0;
    entry->callback = callback;
    if (callback != NULL) {
        move_words(entry->params, arg3, 8);
    }
    if (arg4 != NULL) {
        *arg4 = entry;
    }
    return 0;
}

}
