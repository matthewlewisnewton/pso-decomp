#include "types.h"
#include "pso/misc/TLobby_800FA2A0.h"
#include "pso/unk/text_803CC294.h"
#include "pso/misc/TLobby.h"

extern "C" {

u8 *alloc_from_heap__6TLobbyFPv(s32);
u8 *link_into_list__6TLobbyFv();
s32 strncpy(void *, void *, int);

}

struct NamedDownloadEntry {
    s32 state;
    s32 unused_04;
    char name[0x20];
    s32 buffer;
    s32 file_size;
    s32 field_30;
    s32 field_34;
    s32 unused_38;
    s32 unused_3c;
    void (*callback)(Lobby_8001FA1C *);
    // Eight words are copied starting at +0x44. Callback-specific fields
    // occupy the beginning of this storage; the whole copy spans 0x20 bytes.
    u8 params[0x20];
    u8 rest[0x68 - 0x64];
};

typedef char NamedDownloadEntry_size[sizeof(NamedDownloadEntry) == 0x68 ? 1 : -1];
typedef char NamedDownloadEntry_callback[offsetof(NamedDownloadEntry, callback) == 0x40 ? 1 : -1];

s32 TLobby::create_named_entry(void *name, s32 arg1, void (*callback)(Lobby_8001FA1C *), void *src, void **arg4) {
    NamedDownloadEntry *entry;
    AdxfHandle *file;

    if (arg4 != NULL) {
        *arg4 = NULL;
    }
    file = ADXF_Open(name, 0);
    if (file == NULL) {
        return -2;
    }
    entry = (NamedDownloadEntry *)alloc_from_heap__6TLobbyFPv(0x68);
    if (entry != NULL) {
        entry = (NamedDownloadEntry *)link_into_list__6TLobbyFv();
    }
    strncpy(entry->name, name, 0x20);
    entry->state = 1;
    entry->buffer = arg1;
    entry->file_size = ADXF_GetFsizeByte(file);
    entry->field_30 = ADXF_GetFsizeSct(file);
    ADXF_Close(file);
    entry->field_34 = 0;
    entry->callback = callback;
    if (callback != NULL) {
        move_words(entry->params, src, 8);
    }
    if (arg4 != NULL) {
        *arg4 = entry;
    }
    return entry->file_size;
}
