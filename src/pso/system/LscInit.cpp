#include "pso/system/LscStream.h"
#include "pso/misc/TLobby.h"

extern "C" {
void enter_lock__6TLobbyFv(void *);
void notify_dvd_read__6TLobbyFv(void *);
void *memset(void *, int, unsigned long);

const char *const volatile lsc_version_string = "\nLSC/GC Ver 2.07 Build:Jun 13 2002 19:00:24\n";
s32 lsc_init_count;
LscStream lsc_slot_table[16];

void lsc_shutdown(void) {
    u8 lock[8];
    enter_lock__6TLobbyFv(lock);
    if (--lsc_init_count == 0) {
        for (s32 i = 0; i < 16; i++) {
            if (static_cast<s32>(lsc_slot_table[i].in_use) == 1) {
                lsc_destroy(&lsc_slot_table[i]);
            }
        }
        memset(lsc_slot_table, 0, sizeof(lsc_slot_table));
        TLobby::set_callback(0, 0);
    }
    notify_dvd_read__6TLobbyFv(lock);
}

void lsc_init(void) {
    u8 lock[8];
    // Retain the middleware build banner through its volatile pointer.
    lsc_version_string;
    enter_lock__6TLobbyFv(lock);
    if (lsc_init_count == 0) {
        memset(lsc_slot_table, 0, sizeof(lsc_slot_table));
        TLobby::set_callback(0, 0);
    }
    lsc_init_count++;
    notify_dvd_read__6TLobbyFv(lock);
}
}
