#include "types.h"
#include "pso/misc/TLobby_800FA2A0.h"
#include "pso/unk/text_803CC294.h"
#include "pso/misc/TLobby.h"

extern "C" {

u8 *alloc_from_heap__6TLobbyFPv(s32);
u8 *link_into_list__6TLobbyFv();
s32 strncpy(void *, void *, int);
s32 TLobby__sub_803CC53C(TLobby *);

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
    u8 params[8];
    u8 rest[0x68 - 0x4C];
};

typedef char NamedDownloadEntry_size[sizeof(NamedDownloadEntry) == 0x68 ? 1 : -1];
typedef char NamedDownloadEntry_callback[offsetof(NamedDownloadEntry, callback) == 0x40 ? 1 : -1];

s32 TLobby::create_named_entry(void *name, s32 arg1, void (*callback)(Lobby_8001FA1C *), void *src, void **arg4) {
    NamedDownloadEntry *entry;
    TLobby *file;

    if (arg4 != NULL) {
        *arg4 = NULL;
    }
    file = TLobby::adxf_open(name, 0);
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
    entry->file_size = file->adxf_get_fsize_byte();
    entry->field_30 = TLobby__sub_803CC53C(file);
    file->close_adxf_handle();
    entry->field_34 = 0;
    entry->callback = callback;
    if (callback != NULL) {
        ((TLobby *)entry->params)->move_words((u32 *)src, 8);
    }
    if (arg4 != NULL) {
        *arg4 = entry;
    }
    return entry->file_size;
}
