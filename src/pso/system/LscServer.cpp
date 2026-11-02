#pragma readonly_strings on
#include "pso/system/LscStream.h"
#include "pso/system/AdxStreamRuntime.h"
#include "pso/misc/TLobby.h"
#include <string.h>

static char lsc_repeat_filename[0x28];

extern "C" {
AdxStreamFile *adxstm_open_fname_range_ex_rt__6TLobbyFPviiii(const char *name, s32 mode, s32 offset, s32 length, s32 stream);
s32 set_range__6TLobbyFPvii(u8 *file, s32 min_bytes, s32 capacity);

void lsc_poll(LscStream *lsc_stream) {
    LscQueueEntry *entry;
    s32 status;

    if ((s32)lsc_stream->paused == 1) {
        return;
    }
    if (lsc_stream->state != 2) {
        return;
    }
    if (lsc_stream->queued_count <= 0) {
        return;
    }
    if (lsc_stream->entries[lsc_stream->read_index].status == 1) {
        if (lsc_stream->file_handle == 0) {
            TLobby::log_printf("E0007: lsc->fp=NULL");
        } else {
            entry = &lsc_stream->entries[lsc_stream->read_index];
            status = TLobby__sub_803C8B2C((u8 *)lsc_stream->file_handle);
            if (status == 4) {
                lsc_stream->state = 3;
            } else if (status == 2) {
                entry->progress = get_file_offset_relative__6TLobbyFv((AdxStreamFile *)lsc_stream->file_handle);
            } else if (status == 3) {
                entry->progress = lsc_stream->file_sector_count;
                entry->status = 2;
            }
        }
    }
    if (lsc_stream->entries[lsc_stream->read_index].status == 2) {
        struct {
            s32 open_mode;
            s32 range_offset;
            s32 range_length;
        } repeat_range;
        repeat_range.open_mode = 0;
        repeat_range.range_offset = repeat_range.open_mode;
        repeat_range.range_length = repeat_range.open_mode;
        if (lsc_stream->file_handle != 0) {
            TLobby__sub_803C8B38((u8 *)lsc_stream->file_handle);
            lsc_stream->file_handle = 0;
            if ((s32)lsc_stream->repeat == 1) {
                entry = &lsc_stream->entries[lsc_stream->read_index];
                memcpy(lsc_repeat_filename, entry->filename, 0x27);
                repeat_range.open_mode = entry->open_mode;
                repeat_range.range_offset = entry->range_offset;
                repeat_range.range_length = entry->range_length;
            }
            // Freeze the repeat arguments before notifying the queue-empty callback.
            // GC/2.6 retains the native copies when this snapshot stays distinct.
            const s32 saved_range_length = repeat_range.range_length;
            const s32 saved_range_offset = repeat_range.range_offset;
            const s32 saved_open_mode = repeat_range.open_mode;
            lsc_stream->queued_count--;
            lsc_stream->read_index = (lsc_stream->read_index + 1) % 16;
            if (lsc_stream->queued_count <= 0) {
                lsc_notify_queue_empty();
                lsc_stream->state = 1;
            }
            if ((s32)lsc_stream->repeat == 1) {
                lsc_enqueue_range(lsc_stream, lsc_repeat_filename, saved_open_mode, saved_range_offset, saved_range_length);
            }
        }
    }
    if (lsc_stream->entries[lsc_stream->read_index].status == 0) {
        entry = &lsc_stream->entries[lsc_stream->read_index];
        if (lsc_stream->queued_count > 0) {
            if (lsc_stream->file_handle == 0) {
                lsc_stream->file_handle = (void *)adxstm_open_fname_range_ex_rt__6TLobbyFPviiii(entry->filename, entry->open_mode, entry->range_offset, entry->range_length, (s32)lsc_stream->stream);
                if (lsc_stream->file_handle == 0) {
                    TLobby::log_printf("E0004: Can not open '%s'", entry->filename);
                }
                // Keep the byte reset independent of the sector-count store.
                s32 sector_count = (get_field_14__6TLobbyFv((AdxStreamFile *)lsc_stream->file_handle) + 0x7FF) / 0x800;
                lsc_stream->read_started = 0;
                lsc_stream->file_sector_count = sector_count;
                entry->progress = 0;
            }
            if (lsc_stream->read_started == 0) {
                set_range__6TLobbyFPvii((u8 *)lsc_stream->file_handle, lsc_stream->min_buffer_bytes, lsc_stream->buffer_capacity);
                set_scroll_offset__6TLobbyFl((AdxStreamFile *)lsc_stream->file_handle, 0);
                init_stream_position__6TLobbyFv((AdxStreamFile *)lsc_stream->file_handle);
                lsc_stream->read_started = 1;
            }
            entry->status = 1;
        } else if (lsc_stream->file_handle != 0) {
            TLobby::log_printf("E0006: Illigal member nstm='%d' fp='%08x'h", lsc_stream->queued_count, lsc_stream->file_handle);
        }
    }
}

}
