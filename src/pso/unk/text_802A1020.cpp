#include "types.h"
#include "pso/unk/text_802A1020.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
typedef struct Entry_802A1020 {
    s32 file;
    u32 size;
    u32 crc;
} Entry_802A1020;

extern "C" {
u8 *set_stream_and_load_file__6TLobbyFi(s32);
u32 get_file_size__6TLobbyFv(s32);
extern Entry_802A1020 file_integrity_table[];
extern s32 lobby_cursor_active_flag;
s32 fn_802A1020(void) {
    s32 i;
    u32 size;
    u8 *buf;
    u8 *p;
    u32 crc;
    s32 j;
    s32 k;
    for (i = 0; i < 11; i++) {
        size = get_file_size__6TLobbyFv(file_integrity_table[i].file);
        if (size != file_integrity_table[i].size) {
            lobby_cursor_active_flag = 1;
            return 1;
        }
        if (file_integrity_table[i].size <= 1000000) {
            buf = set_stream_and_load_file__6TLobbyFi(file_integrity_table[i].file);
            if (buf == NULL) {
                TAdSinglePlyChrSelectGC::safe_free((u32)buf);
                lobby_cursor_active_flag = 0;
                return 0;
            }
            crc = 0xFFFFFFFF;
            for (j = 0; j < (s32)size; j++) {
                crc ^= buf[j] << 24;
                for (k = 0; k < 8; k++) {
                    if (crc & 0x80000000) {
                        crc = (crc << 1) ^ 0x04C11DB7;
                    } else {
                        crc = crc << 1;
                    }
                }
            }
            TAdSinglePlyChrSelectGC::safe_free((u32)buf);
            if (~crc != file_integrity_table[i].crc) {
                lobby_cursor_active_flag = 1;
                return 1;
            }
        }
    }
    lobby_cursor_active_flag = 0;
    return 0;
}

}
