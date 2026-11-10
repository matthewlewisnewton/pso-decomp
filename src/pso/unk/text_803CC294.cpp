#include "types.h"
#include "pso/misc/TLobby_803CD804.h"
#include "pso/system/AdxStreamRuntime.h"
#include "pso/system/SjRingBuffer.h"
#include "pso/unk/text_803CC294.h"
#include "pso/misc/TLobby.h"

struct RecoveredGlobal_803CC500_lbl_8047C910 {
    s32 value;
    u8 remaining[0x28];
};

struct RecoveredGlobal_803CC53C_lbl_8047C93C {
    s32 value;
    u8 remaining[0x70];
};

struct RecoveredGlobal_803CCB5C_lbl_8047CA28 {
    s32 value;
    u8 remaining[0x150];
};

struct Obj_803CC4C0 { u8 a; s8 b; };

struct Chunk_803CC294 { u16 id; u16 len; s32 off; };

struct Ent_803CC294 {
    struct Ent_803CC294 *next; s32 f4; s32 f8; u16 fc; u8 pad_e[2]; char name[0x100];
    s32 f110; u16 f114; u16 arr[1];
};

struct Ent_803CD5C4 {
    u8 pad_0[4]; s32 f4; s32 f8; u16 fc; u8 pad_e[0x114 - 0xE]; s16 f114; s16 arr[1];
};

struct LogEnt_803CD16C {
    s8 type;
    s8 phase;
    u16 seq;
    union {
        s32 a;
        const void *name;
        AdxfHandle *handle;
    };
    s32 b;
    union {
        s32 c;
        void *destination;
    };
};

struct Buf_803CD16C { u8 data[0x10C]; };

struct LogHdr_803CD16C {
    u8 pad[2];
    u16 open_sequence;
    u16 seq;
    u16 close_sequence;
    u16 read_sequence;
    u16 stop_sequence;
    u16 seek_sequence;
    u8 pad2[0x12];
};

struct AdxfHandle {
    s8 used;
    s8 state;
    s8 f2;
    u8 f3;
    AdxStreamFile *stream;
    SjRingBuffer *buffer;
    s32 sector_count;
    s32 byte_size;
    s32 sector_position;
    s32 read_start_sector;
    s32 read_sector_count;
    s32 sectors_read;
    void *read_destination;
    s32 read_buffer_size;
    s32 f2c;
    s32 archive_start_sector;
    u8 pad_34[0x138 - 0x34];
};

typedef char AdxfHandleSize[sizeof(AdxfHandle) == 0x138 ? 1 : -1];
typedef char AdxfHandleByteSizeOffset[offsetof(AdxfHandle, byte_size) == 0x10 ? 1 : -1];
typedef AdxfHandle Slot_803CD16C;

typedef AdxfHandle Snd_803CC980;

struct Hdr_803CCE9C { u8 used; u8 f1; };

extern "C" {
extern RecoveredGlobal_803CC500_lbl_8047C910 lbl_8047C910;
extern RecoveredGlobal_803CC53C_lbl_8047C93C lbl_8047C93C;
extern RecoveredGlobal_803CCB5C_lbl_8047CA28 lbl_8047CA28;
extern char lbl_8047C88C[];
s32 strncpy(void *, void *, int);
extern s32 adx_afs_partition_id_range_error[];
extern s32 afs_file_id_out_of_range_error[];
extern Ent_803CC294 *afs_archive_toc_table[];
s32 memcmp(void *, void *, int);
extern char lbl_8047C818[];
extern s32 lobby_adxf_current_file_id;
extern AdxfHandle *lobby_adxf_open_file_handle;
extern s32 lobby_afs_toc_entry_index;
extern u8 *lbl_805D75EC;
extern s32 lbl_805E0D88;
extern s32 lbl_8047CB7C[];
extern LogHdr_803CD16C lbl_8057B7B0;
extern LogEnt_803CD16C lbl_8057B7D0[];
extern Slot_803CD16C adxf_file_handle_pool[];
extern s32 adxf_log_write_index;
extern s32 lbl_8047CBA4[];
extern s32 lbl_8047CBD8[];
void invalidate_cache__6TLobbyFv(void *address, u32 length);
extern s32 lbl_8047C9B0[];
extern s32 lbl_8047C9D4[];
extern s32 lbl_805D75E4;
void *memset(void *, int, unsigned long);
typedef char RecoveredGlobal_803CC500_lbl_8047C910_size[sizeof(RecoveredGlobal_803CC500_lbl_8047C910) == 0x2C ? 1 : -1];

#pragma push
#pragma inline_depth(4)
#pragma dont_inline off
inline s32 check_803CC294(s32 arg0, s32 arg1) {
    if (arg0 < 0 || arg0 >= 0x100) {
        TLobby::notify_error((const char *)adx_afs_partition_id_range_error);
        return -3;
    }
    if (afs_archive_toc_table[arg0] == NULL) {
        TLobby::notify_error((const char *)adx_afs_partition_id_range_error);
        return -3;
    }
    if (arg1 < 0 || arg1 >= afs_archive_toc_table[arg0]->f8) {
        TLobby::notify_error((const char *)afs_file_id_out_of_range_error);
        return -3;
    }
    return 0;
}
s32 TLobby::get_afs_file_info(s32 arg0, s32 arg1, char *arg2, s32 *arg3, s32 *arg4, s32 *arg5) {
    s32 st;
    Ent_803CC294 *e;
    u16 *arr;
    s32 sum;
    s32 i;
    Ent_803CC294 *next;
    st = check_803CC294(arg0, arg1);
    if (st < 0) {
        *arg3 = 0;
        *arg4 = -1;
        *arg5 = -1;
        return st;
    }
    e = afs_archive_toc_table[arg0];
    while ((next = e->next) != NULL) {
        Chunk_803CC294 *c = (Chunk_803CC294 *)&e->f114;
        for (i = 0; i < e->fc; i++, c++) {
            if (c->id == arg1) {
                strncpy(arg2, e->name, 0x100);
                *arg3 = e->f110;
                *arg4 = c->off;
                *arg5 = c->len;
                return st;
            }
        }
        e = next;
    }
    sum = e->f114;
    arr = e->arr;
    for (i = 0; i < arg1; i++) {
        sum += arr[i];
    }
    strncpy(arg2, e->name, 0x100);
    *arg3 = e->f110;
    *arg4 = sum;
    *arg5 = arr[arg1];
    return st;
}
#pragma pop

s32 ADXF_GetStat(AdxfHandle *p) {
    if (p == 0) {
        TLobby::notify_error((const char *)lbl_8047C88C);
        return -3;
    }
    return p->state;
}

s32 ADXF_GetFsizeByte(AdxfHandle *arg0) {
    if (arg0 == NULL) {
        TLobby::notify_error((const char *)(&lbl_8047C910.value));
        return -3;
    }
    return arg0->byte_size;
}
typedef char RecoveredGlobal_803CC53C_lbl_8047C93C_size[sizeof(RecoveredGlobal_803CC53C_lbl_8047C93C) == 0x74 ? 1 : -1];
s32 ADXF_GetFsizeSct(AdxfHandle *arg0) {
    if (arg0 == NULL) {
        TLobby::notify_error((const char *)(&lbl_8047C93C.value));
        return -3;
    }
    return arg0->sector_count;
}
typedef char RecoveredGlobal_803CCB5C_lbl_8047CA28_size[sizeof(RecoveredGlobal_803CCB5C_lbl_8047CA28) == 0x154 ? 1 : -1];

#pragma push
#pragma inline_depth(4)
#pragma dont_inline off

static inline s32 finish_stop_adxf_file(AdxfHandle *arg0, const char *null_message, const char *stream_message) {
    s32 sp8;
    if (arg0 == NULL) {
        TLobby::notify_error(null_message);
        return -3;
    }
    if (arg0->state == 1) {
        return arg0->sector_position;
    }
    if (arg0->state == 3) {
        arg0->state = 1;
        return arg0->sector_position;
    }
    if (arg0->stream == 0) {
        TLobby::notify_error(stream_message);
        return -1;
    }
    TLobby::init_once();
    TLobby__sub_803C89C4((u8 *)arg0->stream);
    TLobby__sub_803C85AC((u8 *)arg0->stream, &sp8);
    arg0->sectors_read = sp8;
    if (arg0->buffer != NULL && arg0->f2 == 0) {
        if (lbl_805D75E4 == 1) {
            invalidate_cache__6TLobbyFv(arg0->read_destination, arg0->read_buffer_size);
        }
        arg0->buffer->interface->destroy(arg0->buffer);
        arg0->buffer = NULL;
    }
    arg0->state = 1;
    TLobby::release_ref();
    {
        s32 i = adxf_log_write_index % 256;
        LogEnt_803CD16C *e = &lbl_8057B7D0[adxf_log_write_index = i];
        e->type = 5;
        e->phase = 1;
        e->seq = lbl_8057B7B0.stop_sequence;
        e->handle = arg0;
        e->b = -1;
        e->c = -1;
        adxf_log_write_index = i + 1;
    }
    return arg0->sector_position;
}

// The inlined stop path publishes its sequence between the last two payload stores.
static inline s32 stop_adxf_file_for_seek(AdxfHandle *arg0, const char *messages) {
    {
        LogEnt_803CD16C *e;
        s32 i = (adxf_log_write_index %= 256);
        u16 seq;
        e = &lbl_8057B7D0[i];
        seq = lbl_8057B7B0.stop_sequence + 1;
        e->type = 5;
        e->phase = 0;
        e->seq = seq;
        e->handle = arg0;
        e->b = -1;
        lbl_8057B7B0.stop_sequence = seq;
        e->c = -1;
        adxf_log_write_index = i + 1;
    }
    return finish_stop_adxf_file(arg0, messages + 0x198, messages + 0x1BC);
}

s32 ADXF_Seek(AdxfHandle *file, s32 offset, s32 origin) {
    // The seek and read diagnostics share the original ADXF string block.
    const char *messages = lbl_8047C818;
    {
        s32 i = (adxf_log_write_index %= 256);
        LogEnt_803CD16C *entry = &lbl_8057B7D0[i];
        u16 seq = lbl_8057B7B0.seek_sequence + 1;
        entry->type = 6;
        entry->phase = 0;
        entry->seq = seq;
        entry->handle = file;
        entry->b = offset;
        lbl_8057B7B0.seek_sequence = seq;
        entry->c = origin;
        adxf_log_write_index = i + 1;
    }
    if (file == NULL) {
        TLobby::notify_error(messages + 0x174);
        return -3;
    }

    if (file->state == 2) {
        stop_adxf_file_for_seek(file, messages);
    }

    if (origin == 0) {
        file->sector_position = offset;
    } else if (origin == 1) {
        file->sector_position += offset;
    } else if (origin == 2) {
        file->sector_position = file->sector_count + offset;
    } else {
        TLobby::notify_error(messages + 0x1E8);
        return -3;
    }
    if (file->sector_position < 0) {
        file->sector_position = 0;
    } else if (file->sector_position > file->sector_count) {
        file->sector_position = file->sector_count;
    }

    {
        s32 i = adxf_log_write_index % 256;
        LogEnt_803CD16C *entry = &lbl_8057B7D0[adxf_log_write_index = i];
        entry->type = 6;
        entry->phase = 1;
        entry->seq = lbl_8057B7B0.seek_sequence;
        entry->handle = file;
        entry->b = offset;
        entry->c = origin;
        adxf_log_write_index = i + 1;
    }
    return file->sector_position;
}

void TLobby__sub_803CC884(void) {
    AdxfHandle *p;
    s32 i;
    s32 sp8;
    TLobby::init_once();
    for (i = 0; i < 0x10; i++) {
        p = &adxf_file_handle_pool[i];
        if (p->used == 1 && p->state == 2) {
            p->state = TLobby__sub_803C8B2C((u8 *)p->stream);
            TLobby__sub_803C85AC((u8 *)p->stream, &sp8);
            p->sectors_read = sp8;
            if (p->state == 3 || p->state == 4) {
                p->sector_position += p->sectors_read;
                if (p->buffer != NULL && p->f2 == 0) {
                    if (lbl_805D75E4 == 1) {
                        invalidate_cache__6TLobbyFv(p->read_destination, p->read_buffer_size);
                    }
                    p->buffer->interface->destroy(p->buffer);
                    p->buffer = NULL;
                }
            }
        }
    }
    TLobby::release_ref();
}

s32 ADXF_Stop(AdxfHandle *arg0) {
    {
        LogEnt_803CD16C *e;
        s32 i = adxf_log_write_index % 256;
        u16 seq;
        e = &lbl_8057B7D0[i];
        adxf_log_write_index = i;
        seq = ++lbl_8057B7B0.stop_sequence;
        e->type = 5;
        e->phase = 0;
        e->seq = seq;
        e->handle = arg0;
        e->b = -1;
        e->c = -1;
        adxf_log_write_index = i + 1;
    }
    return finish_stop_adxf_file(arg0, (const char *)lbl_8047C9B0, (const char *)lbl_8047C9D4);
}
#pragma pop

s32 TLobby::read_checked_align(void *file, s32 count, void *dest) {
    if (((u32)dest & 0x1F) != 0) {
        TLobby::notify_error((const char *)(&lbl_8047CA28.value));
        return -3;
    }
    return ADXF_ReadNw32((AdxfHandle *)file, count, dest);
}

s32 ADXF_ReadNw32(AdxfHandle *file, s32 sectors, void *destination) {
    const char *messages = lbl_8047C818;
    {
        s32 i = (adxf_log_write_index %= 256);
        LogEnt_803CD16C *entry = &lbl_8057B7D0[i];
        u16 seq = ++lbl_8057B7B0.read_sequence;
        entry->type = 4;
        entry->phase = 0;
        entry->seq = seq;
        entry->handle = file;
        entry->b = sectors;
        entry->destination = destination;
        adxf_log_write_index = i + 1;
    }
    if (file == NULL) {
        TLobby::notify_error(messages + 0x244);
        return -3;
    }
    if (sectors < 0) {
        TLobby::notify_error(messages + 0x26C);
        return -3;
    }
    if (destination == NULL) {
        TLobby::notify_error(messages + 0x298);
        return -3;
    }
    if (file->state == 2) {
        return 0;
    }
    if (file->buffer != NULL) {
        TLobby::notify_error(messages + 0x2C0);
        return -1;
    }

    s32 bytes = (u32)sectors << 11;
    SjRingBuffer *buffer = sj_ring_buffer_create(destination, bytes, 0);
    if (buffer == NULL) {
        return -2;
    }

    file->read_destination = destination;
    file->read_buffer_size = bytes;
    TLobby::init_once();
    if (lbl_805D75E4 == 1) {
        invalidate_cache__6TLobbyFv(file->read_destination, file->read_buffer_size);
    }
    if (TLobby__sub_803C8B2C((u8 *)file->stream) != 1) {
        TLobby__sub_803C89C4((u8 *)file->stream);
    }

    // The outer reference covers the destination buffer setup. This one covers starting the stream.
    TLobby::init_once();
    file->read_start_sector = file->archive_start_sector + file->sector_position;
    s32 remaining = file->sector_count - file->sector_position;
    file->read_sector_count = sectors < remaining ? sectors : remaining;
    s32 result;
    file->sectors_read = result = 0;
    if (file->read_sector_count == 0) {
        file->state = 3;
    } else {
        TLobby__sub_803C8514((u8 *)file->stream, file->read_sector_count);
        set_scroll_position__6TLobbyFl(file->stream, -1);
        set_buffer__6TLobbyFPPv(file->stream, buffer);
        set_field_10_and_notify__6TLobbyFl(file->stream, file->archive_start_sector + file->sector_position);
        TLobby__sub_803C8578((u8 *)file->stream, file->f2c);
        file->state = 2;
        init_stream_position__6TLobbyFv(file->stream);
        result = file->read_sector_count;
    }
    TLobby::release_ref();

    if (result <= 0) {
        buffer->interface->destroy(buffer);
    } else {
        file->buffer = buffer;
    }
    file->f2 = 0;
    TLobby::release_ref();

    {
        s32 i = adxf_log_write_index % 256;
        LogEnt_803CD16C *entry = &lbl_8057B7D0[adxf_log_write_index = i];
        entry->type = 4;
        entry->phase = 1;
        entry->seq = lbl_8057B7B0.read_sequence;
        entry->handle = file;
        entry->b = sectors;
        entry->destination = destination;
        adxf_log_write_index = i + 1;
    }
    return result;
}

#define LE32_803CD5C4(p) ((p)[0] | ((p)[1] << 8) | ((p)[2] << 16) | ((p)[3] << 24))
#pragma push
#pragma inline_depth(4)
#pragma dont_inline off
inline s32 rd32_803CD5C4(u8 *p) {
    return p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
}
inline s32 state_803CD5C4(s32 base) {
    if (lobby_adxf_open_file_handle == NULL) {
        TLobby::notify_error((const char *)(base + 0x74));
        return -3;
    }
    return lobby_adxf_open_file_handle->state;
}

#pragma push
#pragma inline_depth(4)
#pragma dont_inline off
inline Slot_803CD16C *find_803CD16C(void) {
    Slot_803CD16C *r = NULL;
    s32 i;
    for (i = 0; i < 16; i++) {
        if (adxf_file_handle_pool[i].used == 0) {
            r = &adxf_file_handle_pool[i];
            break;
        }
    }
    return r;
}
inline Slot_803CD16C *alloc_803CD16C(void) {
    Slot_803CD16C *s = find_803CD16C();
    if (s == NULL) {
        return NULL;
    }
    s->state = 1;
    s->stream = 0;
    s->read_start_sector = 0;
    s->read_sector_count = 0;
    s->sectors_read = 0;
    s->f2c = 0x200;
    s->f2 = 0;
    s->buffer = 0;
    s->used = 1;
    return s;
}
inline s32 open_803CD16C(Slot_803CD16C *s, s32 arg0, s32 arg1) {
    Buf_803CD16C buf;
    s32 c;
    s32 b;
    s32 a;
    AdxStreamFile *h;
    if (TLobby::get_afs_file_info(arg0, arg1, (char *)&buf, &a, &b, &c) < 0) {
        return -3;
    }
    s->archive_start_sector = b;
    h = adxstm_open_fname_range__6TLobbyFPviiii((const char *)&buf, a, b, c, 0);
    s->stream = h;
    if (h == 0) {
        TLobby::notify_error((const char *)lbl_8047CB7C);
        return -1;
    }
    s->sector_count = c;
    s->byte_size = c << 11;
    return 0;
}

void TLobby::release_used_slots() {
    s32 i;
    Slot_803CD16C *p;
    for (i = 0; i < 0x10; i++) {
        p = &adxf_file_handle_pool[i];
        if (p->used == 1) {
            ADXF_Close(p);
        }
    }
}

#pragma push
#pragma inline_depth(4)
#pragma dont_inline off
inline s32 close_803CCE9C(Snd_803CC980 *arg0) {
    s32 sp8;
    {
        LogEnt_803CD16C *e;
        s32 i = adxf_log_write_index % 256;
        u16 seq;
        e = &lbl_8057B7D0[i];
        adxf_log_write_index = i;
        seq = lbl_8057B7B0.stop_sequence + 1;
        e->type = 5;
        e->phase = 0;
        e->seq = seq;
        e->handle = arg0;
        e->b = -1;
        lbl_8057B7B0.stop_sequence = seq;
        e->c = -1;
        adxf_log_write_index = i + 1;
    }
    if (arg0 == NULL) {
        TLobby::notify_error((const char *)lbl_8047C9B0);
        return -3;
    }
    if (arg0->state == 1) {
        return arg0->sector_position;
    }
    if (arg0->state == 3) {
        arg0->state = 1;
        return arg0->sector_position;
    }
    if (arg0->stream == 0) {
        TLobby::notify_error((const char *)lbl_8047C9D4);
        return -1;
    }
    TLobby::init_once();
    TLobby__sub_803C89C4((u8 *)arg0->stream);
    TLobby__sub_803C85AC((u8 *)arg0->stream, &sp8);
    arg0->sectors_read = sp8;
    if (arg0->buffer != NULL && arg0->f2 == 0) {
        if (lbl_805D75E4 == 1) {
            invalidate_cache__6TLobbyFv(arg0->read_destination, arg0->read_buffer_size);
        }
        arg0->buffer->interface->destroy(arg0->buffer);
        arg0->buffer = NULL;
    }
    arg0->state = 1;
    TLobby::release_ref();
    {
        s32 i = adxf_log_write_index % 256;
        LogEnt_803CD16C *e = &lbl_8057B7D0[adxf_log_write_index = i];
        e->type = 5;
        e->phase = 1;
        e->seq = lbl_8057B7B0.stop_sequence;
        e->handle = arg0;
        e->b = -1;
        e->c = -1;
        adxf_log_write_index = i + 1;
    }
    return arg0->sector_position;
}
void ADXF_Close(AdxfHandle *file) {
    {
        LogEnt_803CD16C *e;
        s32 i = adxf_log_write_index % 256;
        u16 seq;
        e = &lbl_8057B7D0[i];
        adxf_log_write_index = i;
        seq = ++lbl_8057B7B0.close_sequence;
        e->type = 3;
        e->phase = 0;
        e->seq = seq;
        e->handle = file;
        e->b = -1;
        e->c = -1;
        adxf_log_write_index = i + 1;
    }
    if (file != NULL) {
        TLobby::init_once();
        if ((s32)file->state == 2) {
            close_803CCE9C(file);
        }
        if (file->stream != 0) {
            TLobby__sub_803C8B38((u8 *)file->stream);
        }
        memset(file, 0, 0x138);
        TLobby::release_ref();
        {
            s32 i = adxf_log_write_index % 256;
            LogEnt_803CD16C *e = &lbl_8057B7D0[adxf_log_write_index = i];
            e->type = 3;
            e->phase = 1;
            e->seq = lbl_8057B7B0.close_sequence;
            e->handle = file;
            e->b = -1;
            e->c = -1;
            adxf_log_write_index = i + 1;
        }
    }
}
#pragma pop

AdxfHandle *ADXF_OpenAfs(s32 arg0, s32 arg1) {
    Slot_803CD16C *s;
    {
        LogEnt_803CD16C *e;
        s32 i = adxf_log_write_index % 256;
        u16 seq;
        e = &lbl_8057B7D0[i];
        adxf_log_write_index = i;
        seq = lbl_8057B7B0.seq + 1;
        e->type = 2;
        e->phase = 0;
        e->seq = seq;
        e->a = arg0;
        e->b = arg1;
        lbl_8057B7B0.seq = seq;
        e->c = -1;
        adxf_log_write_index = i + 1;
    }
    TLobby::init_once();
    s = alloc_803CD16C();
    if (s != NULL) {
        if (open_803CD16C(s, arg0, arg1) < 0) {
            ADXF_Close(s);
            s = NULL;
        }
    }
    TLobby::release_ref();
    {
        s32 i = adxf_log_write_index % 256;
        LogEnt_803CD16C *e = &lbl_8057B7D0[adxf_log_write_index = i];
        e->type = 2;
        e->phase = 1;
        e->seq = lbl_8057B7B0.seq;
        e->a = arg0;
        e->b = arg1;
        e->c = -1;
        adxf_log_write_index = i + 1;
    }
    return s;
}
#pragma pop

#pragma push
#pragma inline_depth(4)
#pragma dont_inline off
inline Slot_803CD16C *find_803CD3A8(void) {
    Slot_803CD16C *r = NULL;
    s32 i;
    for (i = 0; i < 16; i++) {
        if (adxf_file_handle_pool[i].used == 0) {
            r = &adxf_file_handle_pool[i];
            break;
        }
    }
    return r;
}
inline Slot_803CD16C *alloc_803CD3A8(void) {
    Slot_803CD16C *s = find_803CD3A8();
    if (s == NULL) {
        return NULL;
    }
    s->state = 1;
    s->stream = 0;
    s->read_start_sector = 0;
    s->read_sector_count = 0;
    s->sectors_read = 0;
    s->f2c = 0x200;
    s->f2 = 0;
    s->buffer = 0;
    s->used = 1;
    return s;
}
inline s32 open_803CD3A8(Slot_803CD16C *s, const void *name, s32 mode) {
    AdxStreamFile *h;
    s32 sz;
    if (name == NULL) {
        TLobby::notify_error((const char *)lbl_8047CBA4);
        return -1;
    }
    h = TLobby__sub_803C8CDC((const char *)name, mode, 0);
    if (h == 0) {
        TLobby::notify_error((const char *)lbl_8047CBD8);
        return -1;
    }
    s->stream = h;
    sz = get_field_14__6TLobbyFv(h);
    s->sector_count = (sz + 0x7FF) / 2048;
    s->byte_size = sz;
    return 0;
}
AdxfHandle *ADXF_Open(const void *name, s32 mode) {
    Slot_803CD16C *s;
    {
        LogEnt_803CD16C *e;
        s32 i = adxf_log_write_index % 256;
        u16 seq;
        e = &lbl_8057B7D0[i];
        adxf_log_write_index = i;
        seq = lbl_8057B7B0.open_sequence + 1;
        e->type = 1;
        e->phase = 0;
        e->seq = seq;
        e->name = name;
        e->b = mode;
        lbl_8057B7B0.open_sequence = seq;
        e->c = -1;
        adxf_log_write_index = i + 1;
    }
    TLobby::init_once();
    s = alloc_803CD3A8();
    if (s != NULL) {
        if (open_803CD3A8(s, name, mode) < 0) {
            ADXF_Close(s);
            s = NULL;
        }
    }
    TLobby::release_ref();
    {
        s32 i = adxf_log_write_index % 256;
        LogEnt_803CD16C *e = &lbl_8057B7D0[adxf_log_write_index = i];
        e->type = 1;
        e->phase = 1;
        e->seq = lbl_8057B7B0.open_sequence;
        e->name = name;
        e->b = mode;
        e->c = -1;
        adxf_log_write_index = i + 1;
    }
    return s;
}
#pragma pop

s32 TLobby::read_afs_toc(s32 arg0) {
    s16 *arr;
    Ent_803CD5C4 *e;
    s32 st;
    s32 i;
    s32 base = (s32)lbl_8047C818;
    if (arg0 != lobby_adxf_current_file_id) {
        TLobby::notify_error((const char *)(base + 0x4D0));
        return -3;
    }
    st = state_803CD5C4(base);
    if (st != 3) {
        return st;
    }
    e = ((Ent_803CD5C4 * *)&afs_archive_toc_table)[arg0];
    arr = e->arr;
    if (e->f8 == 0) {
        s32 n;
        if (memcmp(lbl_805D75EC, &lbl_805E0D88, 3) != 0) {
            TLobby::notify_error((const char *)(base + 0x504));
            TLobby__sub_803CD804();
            return 4;
        }
        n = rd32_803CD5C4(lbl_805D75EC + 4);
        if (n > 0x10000) {
            TLobby::notify_error((const char *)(base + 0x538));
            TLobby__sub_803CD804();
            return 4;
        }
        e->fc = n;
        i = 3;
        e->f8 = (u16)n;
        e->f4 = ((e->f8 + 1) * 2 + 0x116) & ~3;
        e->f114 = LE32_803CD5C4(lbl_805D75EC + 8) / 2048;
    } else {
        i = 1;
    }
    for (; i < 0x200; i += 2) {
        u8 *q = lbl_805D75EC + i * 4;
        arr[lobby_afs_toc_entry_index++] = (LE32_803CD5C4(q) + 0x7FF) / 2048;
        if (lobby_afs_toc_entry_index >= e->f8) {
            st = 3;
            TLobby__sub_803CD804();
            break;
        }
    }
    if (i >= 0x200) {
        if (ADXF_ReadNw32(lobby_adxf_open_file_handle, 1, lbl_805D75EC) < 0) {
            st = 4;
            TLobby__sub_803CD804();
        } else {
            st = lobby_adxf_open_file_handle->state;
        }
    }
    return st;
}
#pragma pop

}
