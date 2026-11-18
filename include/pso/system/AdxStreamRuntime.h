#ifndef PSO_SYSTEM_ADXSTREAMRUNTIME_H
#define PSO_SYSTEM_ADXSTREAMRUNTIME_H

#include "types.h"
#include <stddef.h>

struct LscStream;
struct SjRingBuffer;
typedef struct Ent_803C9608 {
    char state;
    s8 stat;
    u8 pad_2[0x4 - 0x2];
    s32 f4;
    u8 *f8;
    s32 fC;
    u8 pad_10[0x18 - 0x10];
    SjRingBuffer *f18[2]; // one per channel; 2 is inferred (stereo), the code only proves the index
    u8 pad_20[0x48 - 0x20];
    s32 f48;
    u8 pad_4C[0x60 - 0x4C];
    s16 f60;
    u8 pad_62[0x70 - 0x62];
    s8 f70;
    u8 f71;
    s8 f72;
    u8 pad_73[0x94 - 0x73];
    LscStream *f94;
    u8 pad_98[0x9C - 0x98];
    s32 f9C;
    s32 fA0;
    u8 pad_A4[0xA8 - 0xA4];
} Ent_803C9608;
typedef char Ent_803C9608_size[sizeof(Ent_803C9608) == 0xA8 ? 1 : -1];

struct AdxStreamFile {
    s8 used;
    s8 b1;
    s8 b2;
    u8 pad3;
    union {
        s32 arg;
        SjRingBuffer *buffer;
    };
    u32 handle;
    s32 fC;
    s32 f10;
    s32 size;
    s32 read_chunk_size;
    s32 read_threshold;
    u8 pad20[0xC];
    s32 f2C;
    s32 sectors;
    s32 field34;
    u8 pad38[8];
};
typedef char AdxStreamFile_size[sizeof(AdxStreamFile) == 0x40 ? 1 : -1];
typedef char AdxStreamFile_field34_offset[offsetof(AdxStreamFile, field34) == 0x34 ? 1 : -1];


struct AdxDecoderFormatView {
    u8 reserved[0xA8];
    s16 format;
};

extern "C" {
void TLobby__sub_803C34F4(AdxDecoderFormatView *decoder);
s32 get_field_14__6TLobbyFv(AdxStreamFile *file);
s32 get_file_offset_relative__6TLobbyFv(AdxStreamFile *file);
s32 set_scroll_offset__6TLobbyFl(AdxStreamFile *file, s32 offset);
s32 init_stream_position__6TLobbyFv(AdxStreamFile *file);
// Keep the linked symbol names while using the stream-file receiver.
void set_field_10_and_notify__6TLobbyFl(AdxStreamFile *file, s32 offset);
void set_scroll_position__6TLobbyFl(AdxStreamFile *file, s32 sector);
void set_buffer__6TLobbyFPPv(AdxStreamFile *file, SjRingBuffer *buffer);
AdxStreamFile *TLobby__sub_803C8CDC(const char *name, s32 mode, s32 arg);
AdxStreamFile *adxstm_open_fname_range__6TLobbyFPviiii(const char *name, s32 mode, s32 off, s32 nsect, s32 arg);
}

extern "C" {
AdxStreamFile *TLobby__sub_803C8BAC(const char *name, s32 arg);
void TLobby__sub_803C5D00(u8 *arg0);
void TLobby__sub_803C5D24(u8 *arg0);
void TLobby__sub_803C5E58(void);
void TLobby__sub_803C5E68(void);
void TLobby__sub_803C5E78(void);
void TLobby__sub_803C60F0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void TLobby__sub_803C610C(u8 *arg0);
void TLobby__sub_803C6118(u8 *arg0);
void TLobby__sub_803C8514(u8 *arg0, s32 arg1);
s32 TLobby__sub_803C8578(u8 *arg0, s32 arg1);
s32 TLobby__sub_803C8594(u8 *arg0, s32 *arg1, s32 *arg2);
s32 TLobby__sub_803C85AC(u8 *arg0, s32 *arg1);
void TLobby__sub_803C89C4(u8 *arg0);
s32 TLobby__sub_803C8B2C(u8 *arg0);
void TLobby__sub_803C8B38(u8 *arg0);
void TLobby__sub_803C9350(u8 *arg0, s32 arg1);
s32 TLobby__sub_803C9358(u8 *arg0);
void TLobby__sub_803C94B8(void);
void TLobby__sub_803C94D8(void);
void TLobby__sub_803C94DC(u8 *arg0, s32 arg1);
void TLobby__sub_803C9608(void);
void TLobby__sub_803C96A8(u8 *arg0, s32 arg1);
s16 TLobby__sub_803C96B0(u8 *arg0);
s32 TLobby__sub_803C9740(u8 *arg0);
s32 TLobby__sub_803C97B8(u8 *arg0);
s8 TLobby__sub_803C9CB0(u8 *arg0);
void TLobby__sub_803C9DB4(u8 *arg0);
void TLobby__sub_803CB194(u8 *arg0);
void TLobby__sub_803CB4A4(u8 *arg0);
void TLobby__sub_803CB570(u8 *arg0, u8 *arg1, s16 *arg2);
void TLobby__sub_803CB74C(s32 *arg0);
void TLobby__sub_803CB7F8(s32 context, const char *message, s32 handle);
void TLobby__sub_803CB81C(void);
s32 TLobby__sub_803CB844(void);
void TLobby__sub_803CBA18(void);
void TLobby__sub_803CBA38(void);
void TLobby__sub_803CBB14(void);
s32 adx_get_data_start_offset(u16 *arg0, s32 arg1, s32 *arg2);
void adx_process_encoder_output(u8 *arg0p);
}
void append_music_stream_segment(u8 *arg0, s32 arg1, s32 arg2);
extern "C" {
void inl_803C9608(void);
s32 set_range__6TLobbyFPvii(u8 *arg0, s32 arg1, s32 arg2);
}
void stop_audio_stream(u8 *arg0);
void update_active_stream_reads(void);

// --- C functions defined in AdxStreamRuntime.cpp ---
extern "C" {
void TLobby__sub_803C5D00(u8 *arg0);
void TLobby__sub_803C5D24(u8 *lobby);
void TLobby__sub_803C5E58(void);
void TLobby__sub_803C5E68(void);
void TLobby__sub_803C5E78(void);
void TLobby__sub_803C60F0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void TLobby__sub_803C610C(u8 *arg0);
void TLobby__sub_803C6118(u8 *arg0);
void TLobby__sub_803C8514(u8 *arg0, s32 arg1);
s32 TLobby__sub_803C8578(u8 *arg0, s32 arg1);
s32 TLobby__sub_803C8594(u8 *arg0, s32 *arg1, s32 *arg2);
s32 TLobby__sub_803C85AC(u8 *arg0, s32 *arg1);
void TLobby__sub_803C89C4(u8 *arg0);
s32 TLobby__sub_803C8B2C(u8 *arg0);
void TLobby__sub_803C8B38(u8 *arg0);
void TLobby__sub_803C9350(u8 *arg0, s32 arg1);
s32 TLobby__sub_803C9358(u8 *arg0);
void TLobby__sub_803C94B8(void);
void TLobby__sub_803C94D8(void);
void TLobby__sub_803C94DC(u8 *arg0, s32 arg1);
void TLobby__sub_803C9608(void);
void TLobby__sub_803C96A8(u8 *arg0, s32 arg1);
s16 TLobby__sub_803C96B0(u8 *arg0);
s32 TLobby__sub_803C9740(u8 *arg0);
s32 TLobby__sub_803C97B8(u8 *arg0);
s8 TLobby__sub_803C9CB0(u8 *arg0);
void TLobby__sub_803C9DB4(u8 *arg0);
void TLobby__sub_803CB194(u8 *arg0);
void TLobby__sub_803CB4A4(u8 *arg0);
void TLobby__sub_803CB570(u8 *arg0, u8 *arg1, s16 *arg2);
void TLobby__sub_803CB74C(s32 *arg0);
void TLobby__sub_803CB7F8(s32 context, const char *message, s32 handle);
void TLobby__sub_803CB81C(void);
s32 TLobby__sub_803CB844(void);
void TLobby__sub_803CBA18(void);
void TLobby__sub_803CBA38(void);
void TLobby__sub_803CBB14(void);
s32 adx_get_data_start_offset(u16 *arg0, s32 arg1, s32 *arg2);
void adx_process_encoder_output(u8 *arg0p);
void inl_803C9608(void);
s32 set_range__6TLobbyFPvii(u8 *arg0, s32 arg1, s32 arg2);
}
// --- end of C functions

#endif
