#include "types.h"
#include "pso/system/SjRingBuffer.h"
#include "pso/misc/TLobby.h"
#include "pso/system/AdxStreamRuntime.h"
#include "pso/unk/text_803D2F1C.h"

struct RecoveredGlobal_803C0B08_lbl_80570AC0 {
    s32 value;
    u8 remaining[0x9BC];
};

struct RecoveredGlobal_803C0AD8_lbl_80570AC0 {
    s32 value;
    u8 remaining[0x9BC];
};

struct Obj_803C07E8 { u8 a; s8 b; };

typedef struct Vt_803C0628 {
    u8 pad0[0x18];
    void (*fn18)(struct Obj_803C0628 *, s32, s32, void *);
} Vt_803C0628;

typedef struct Obj_803C0628 {
    Vt_803C0628 *vt;
} Obj_803C0628;

typedef struct Rec_803C0628 {
    s32 a;
    s32 b;
} Rec_803C0628;

typedef struct S_803C0628 {
    s32 f0;
    s32 f4;
    s32 f8;
    Obj_803C0628 *objs[4];
    Rec_803C0628 recs[3];
    s32 f34;
    s32 f38;
    s32 f3C;
    s32 f40;
} S_803C0628;

struct Snd_803C0F98 {
    u8 pad0[4];
    s32 state;
    s32 lobby;
    u8 pad0C[2];
    s8 channels;
    u8 pad0F[0x50 - 0x0F];
    u8 *src;
    s32 max;
    u8 pad58[0x64 - 0x58];
    s16 *dst;
    s32 size;
    s32 rofs;
    s32 pos;
    s32 avail;
    s32 unk78;
    u8 pad7C[0x88 - 0x7C];
    void (*get)(s32, s32 *, s32 *, s32 *);
    s32 getCtx;
    void (*put)(s32, s32, s32);
    s32 putCtx;
    u8 pad98[0xA0 - 0x98];
    s32 count;
    s32 bytes;
};

struct Snd_803C0BE8 {
    u8 pad0[4];
    s32 state;
    s32 lobby;
    u8 pad0C[2];
    s8 channels;
    u8 pad0F[0x50 - 0x0F];
    u8 *src;
    s32 max;
    u8 pad58[0x64 - 0x58];
    s16 *dst;
    s32 size;
    s32 rofs;
    s32 pos;
    s32 avail;
    s32 unk78;
    u8 pad7C[0x88 - 0x7C];
    void (*get)(s32, s32 *, s32 *, s32 *);
    s32 getCtx;
    void (*put)(s32, s32, s32);
    s32 putCtx;
    u8 pad98[0xA0 - 0x98];
    s32 count;
    s32 bytes;
};

struct Rec_803C0018 { u8 state; u8 pad[0x9B]; };

struct AudioStreamSource;

struct AudioStreamSourceVtable {
    void *pad[6];
    void (*lock)(AudioStreamSource *, s32, s32, SjChunk *);
    void (*unlock)(AudioStreamSource *, s32, SjChunk *);
    void (*put)(AudioStreamSource *, s32, SjChunk *);
    s32 (*get_available)(AudioStreamSource *, s32);
};

struct AudioStreamSource { AudioStreamSourceVtable *vt; };

struct AudioStreamInputState {
    s8 in_use;
    s8 state;
    u8 channel_count;
    s8 end_when_empty;
    u32 decoder_handle;
    AudioStreamSource *source;
    SjRingBuffer *rings[2];
    SjChunk input_chunk;
    SjChunk output_chunks[2];
    s32 decoded_samples;
    s32 decoded_bytes;
    s32 decode_position;
    s32 max_decode_samples;
    s32 trap_position;
    s32 trap_samples;
    s32 trap_bytes;
    void (*trap_callback)(void *);
    void *trap_context;
    void (*output_callback)(void *, s32, u8 *, s32);
    void *output_context;
    u8 header[0x40];
    s32 header_size;
};

typedef char AudioStreamInputStateSize[sizeof(AudioStreamInputState) == 0x9C ? 1 : -1];

extern "C" {
void TLobby__sub_803BFE58(u8 *arg0);
void TLobby__sub_803BFEE8(u8 *arg0);
s32 TLobby__sub_803C3ABC(u8 *arg0);
s32 TLobby__sub_803C3AC4(u8 *arg0);
s32 TLobby__sub_803C3B38(u8 *);
s32 TLobby__sub_803C3B44(u8 *arg0);
s32 get_field_a8__6TLobbyFv(int);
void TLobby__sub_803BFFC0(u8 *arg0);
void TLobby__sub_803BFFFC(u8 *arg0, s32 arg1, s32 arg2);
s32 TLobby__sub_803C0010(u8 *arg0);
void TLobby__sub_803C39CC(u8 *arg0);
void TLobby__sub_803C0758(u8 *arg0);
s32 TLobby__sub_803C1A00(int);
s32 memset(void *, int, int);
RecoveredGlobal_803C0B08_lbl_80570AC0 lbl_80570AC0;
void TLobby__sub_803C406C(void);
void TLobby__sub_803C133C(Snd_803C0BE8 *arg0);
void TLobby__sub_803C0B3C(u8 *arg0);
s32 TLobby__sub_803C07E8(Obj_803C07E8 *self);
s32 memcmp(void *, void *, int);
extern s32 lbl_805E0CB0;
extern s32 lbl_805E0CB8;

void TLobby__sub_803C0628(void *arg0_, s32 *arg1, s32 *arg2, s32 *arg3);
void EXIGetID(Snd_803C0BE8 *arg0);
void GXFlush(void);
void TLobby__sub_803C0238(AudioStreamInputState *);
void TLobby__sub_803C3A04(u8 *);
void TLobby__sub_803C3984(u8 *);
s32 TLobby__sub_803C3B68(s32 arg0, u16 *hdr, s32 size);
void *memcpy(void *, const void *, u32);
void process_audio_stream_input(AudioStreamInputState *arg0);
u32 alloc_record__6TLobbyFiiii(s32 channels, u8 *buffer, s32 size, s32 total);
void TLobby__sub_803C3B5C(u32 record, void (*callback)(void *, s32 *, s32 *, s32 *), void *context);
AudioStreamInputState *TLobby__sub_803C0848(AudioStreamSource *source, s32 channels, SjRingBuffer **rings);
s32 TLobby::get_offset_58() {
    s32 arg0 = (s32)this;
    return arg0 + 0x58;
}
void TLobby__sub_803BFE58(u8 *arg0) {
    ((TLobby *)(*(s32 *)((s8 *)arg0 + 4)))->get_field_34();
}
void TLobby::dispatch_field4_event() {
    u8 *arg0 = (u8 *)this;
    ((TLobby *)(*(s32 *)((s8 *)arg0 + 4)))->get_field30();
}
void TLobby::send_with_offset4_alt() {
    u8 *arg0 = (u8 *)this;
    ((TLobby *)(*(s32 *)((s8 *)arg0 + 4)))->get_field_2c();
}
void TLobby::notify_client() {
    u8 *arg0 = (u8 *)this;
    ((TLobby *)(*(s32 *)((s8 *)arg0 + 4)))->get_field_28();
}
void TLobby__sub_803BFEE8(u8 *arg0) {
    ((TLobby *)(*(s32 *)((s8 *)arg0 + 4)))->get_slot();
}
void TLobby::send_packet_by_id() {
    u8 *arg0 = (u8 *)this;
    TLobby__sub_803C3ABC((u8 *)(*(s32 *)((s8 *)arg0 + 4)));
}
void TLobby::notify_field_4_alt() {
    u8 *arg0 = (u8 *)this;
    TLobby__sub_803C3AC4((u8 *)(*(s32 *)((s8 *)arg0 + 4)));
}
void TLobby::send_packet_by_id_2() {
    u8 *arg0 = (u8 *)this;
    ((TLobby *)(*(s32 *)((s8 *)arg0 + 4)))->get_packet_flag_for_state();
}
void TLobby::send_with_offset4() {
    u8 *arg0 = (u8 *)this;
    TLobby__sub_803C3B38(*(u8 **)(arg0 + 4));
}
void TLobby::notify_field_4() {
    u8 *arg0 = (u8 *)this;
    TLobby__sub_803C3B44((u8 *)(*(s32 *)((s8 *)arg0 + 4)));
}
void TLobby__sub_803BFFC0(u8 *arg0) {
    get_field_a8__6TLobbyFv((int) (*(s32 *)((s8 *)arg0 + 4)));
}
void TLobby::set_field_44(s32 arg1) {
    u8 *arg0 = (u8 *)this;
    *(s32 *)((s8 *)arg0 + 0x44) = arg1;
}
void TLobby::set_field_40(s32 arg1) {
    u8 *arg0 = (u8 *)this;
    *(s32 *)((s8 *)arg0 + 0x40) = arg1;
}
void TLobby::set_field_3c(s32 arg1) {
    u8 *arg0 = (u8 *)this;
    *(s32 *)((s8 *)arg0 + 0x3C) = arg1;
}
void TLobby__sub_803BFFFC(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)((s8 *)arg0 + 0x48) = arg1;
    *(s32 *)((s8 *)arg0 + 0x4C) = arg2;
}
void TLobby::set_count(s32 arg1) {
    u8 *arg0 = (u8 *)this;
    *(s32 *)((s8 *)arg0 + 0x34) = arg1;
}
s32 TLobby__sub_803C0010(u8 *arg0) {
    return *(s32 *)((s8 *)arg0 + 0x2C);
}

struct Obj_803C0628;

void GXFlush(void) {
    s32 i;
    for (i = 0; i < 0x10; i++) {
        if ((s32)((Rec_803C0018 *)&lbl_80570AC0)[i].state == 1) {
            process_audio_stream_input((AudioStreamInputState *)(&((Rec_803C0018 *)&lbl_80570AC0)[i]));
        }
    }
}

#pragma push
#pragma inline_depth(4)
#pragma dont_inline off
inline void parse_audio_stream_input_header(AudioStreamInputState *arg0) {
    SjChunk b;
    SjChunk b2;
    AudioStreamSource *s = arg0->source;
    s32 h = arg0->decoder_handle;
    s32 n;
    s->vt->lock(s, 1, 0x1000, &b);
    if (b.size < 0x10) {
        s->vt->unlock(s, 1, &b);
        return;
    }
    n = TLobby__sub_803C3B68(h, (u16 *)b.data, b.size);
    if (n == 0 || n > b.size) {
        s->vt->unlock(s, 1, &b);
        return;
    }
    arg0->header_size = n;
    if (get_field_a8__6TLobbyFv(h) == 4) {
        arg0->end_when_empty = 1;
    }
    if (get_field_a8__6TLobbyFv(h) == 2) {
        memcpy(arg0->header, b.data, b.size < 0x40 ? b.size : 0x40);
    }
    if (get_field_a8__6TLobbyFv(h) == 10) {
        s->vt->unlock(s, 1, &b);
    } else {
        TLobby__sub_803D3130(&b, n, &b, &b2);
        s->vt->put(s, 0, &b);
        s->vt->unlock(s, 1, &b2);
    }
    arg0->state = 2;
}
void process_audio_stream_input(AudioStreamInputState *arg0) {
    if (arg0->state == 2) {
        TLobby__sub_803C0238(arg0);
    } else if (arg0->state == 1) {
        parse_audio_stream_input_header(arg0);
    }
}

static inline void prepare_decode(AudioStreamInputState *stream) {
    TLobby *input_decoder = (TLobby *)stream->decoder_handle;
    AudioStreamSource *source = stream->source;
    if (stream->end_when_empty == 1 && source->vt->get_available(source, 1) == 0) {
        stream->state = 3;
    } else {
        source->vt->lock(source, 1, 0x7FFFFFFF, &stream->input_chunk);
        // An ADX footer ends the stream before the next block is submitted.
        if (input_decoder->get_field_a8() == 0 && stream->input_chunk.size >= 2 &&
            (u16)*(s16 *)stream->input_chunk.data == 0x8001) {
            stream->state = 3;
            source->vt->unlock(source, 1, &stream->input_chunk);
        } else if (stream->decode_position >= TLobby__sub_803C3ABC((u8 *)stream->decoder_handle)) {
            stream->state = 3;
            source->vt->unlock(source, 1, &stream->input_chunk);
        } else {
            int minimum = TLobby__sub_803C3AC4((u8 *)stream->decoder_handle);
            SjRingBuffer *ring = stream->rings[0];
            int room = ring->interface->get_available(ring, 0);
            if (room / 2 < minimum) {
                source->vt->unlock(source, 1, &stream->input_chunk);
            } else {
                if (input_decoder->get_field_a8() == 10) {
                    source->vt->unlock(source, 1, &stream->input_chunk);
                }
                input_decoder->init_scroll((s32)stream->input_chunk.data, stream->input_chunk.size);
                TLobby__sub_803C3A04((u8 *)input_decoder);
            }
        }
    }
}

static inline void publish_decode(AudioStreamInputState *stream) {
    // This declaration order gives CodeWarrior the original saved registers and chunk slots.
    s32 written;
    SjChunk used;
    SjChunk unused;
    AudioStreamSource *source = stream->source;
    TLobby *output_decoder = (TLobby *)stream->decoder_handle;
    s32 samples = TLobby__sub_803C3ABC((u8 *)output_decoder);
    s32 input_bytes = output_decoder->get_field_0xa4();
    s32 decoded_samples = output_decoder->get_field_a0();
    samples -= stream->decode_position;
    written = samples;
    if (decoded_samples < samples) {
        written = decoded_samples;
    }

    TLobby__sub_803D3130(&stream->input_chunk, input_bytes, &used, &unused);
    source->vt->put(source, 0, &used);
    source->vt->unlock(source, 1, &unused);

    s32 channel;
    for (channel = 0; channel < TLobby__sub_803C3B38((u8 *)stream->decoder_handle); ++channel) {
        TLobby__sub_803D3130(&stream->output_chunks[channel], written * 2, &used, &unused);
        if (stream->output_callback != NULL) {
            stream->output_callback(stream->output_context, channel, used.data, used.size);
        }
        stream->rings[channel]->interface->put_chunk(stream->rings[channel], 1, &used);
        stream->rings[channel]->interface->unget_chunk(stream->rings[channel], 0, &unused);
    }
    stream->decoded_samples += written;
    stream->decoded_bytes += input_bytes;
    stream->decode_position += written;
    stream->trap_samples += written;
    stream->trap_bytes += input_bytes;
    if (stream->trap_position >= 0 && stream->trap_samples >= stream->trap_position && stream->trap_callback != NULL) {
        stream->trap_callback(stream->trap_context);
    }
    TLobby__sub_803C3984((u8 *)output_decoder);
}

static inline void advance_decode(AudioStreamInputState *stream) {
    TLobby *output_decoder = (TLobby *)stream->decoder_handle;
    s32 remaining = TLobby__sub_803C3ABC((u8 *)output_decoder);
    int input_bytes = output_decoder->get_field_0xa4();
    s32 decoded_samples = output_decoder->get_field_a0();
    remaining -= stream->decode_position;
    decoded_samples = decoded_samples < remaining ? decoded_samples : remaining;
    stream->decoded_samples += decoded_samples;
    stream->decoded_bytes += input_bytes;
    stream->decode_position += decoded_samples;
}

void TLobby__sub_803C0238(AudioStreamInputState *stream) {
    TLobby *decoder = (TLobby *)stream->decoder_handle;
    if (decoder->get_entry_id() == 0) {
        prepare_decode(stream);
    }

    TLobby__sub_803C34F4(reinterpret_cast<AdxDecoderFormatView *>(decoder));
    if (decoder->get_entry_id() == 3) {
        publish_decode(stream);
    }

    // Format 10 also updates the counters outside the output-ring path.
    if (reinterpret_cast<const AdxDecoderFormatView *>(decoder)->format == 10) {
        advance_decode(stream);
    }
}

#pragma pop

void TLobby__sub_803C0628(void *arg0_, s32 *arg1, s32 *arg2, s32 *arg3) {
    S_803C0628 *arg0 = (S_803C0628 *)arg0_;
    s32 h;
    s32 i;
    s32 t;
    s32 v;
    h = (s32)arg0->objs[0];
    for (i = 0; i < TLobby__sub_803C3B38((u8 *)arg0->f4); i++) {
        arg0->objs[i]->vt->fn18(arg0->objs[i], 0, 0x4000, &arg0->recs[i]);
    }
    *arg1 = (arg0->recs[0].a - (s32)sj_ring_buffer_get_buffer((SjRingBuffer*)h)) / 2;
    v = arg0->f38;
    t = arg0->recs[0].b / 2;
    if (t < v) {
        v = t;
    }
    *arg2 = v;
    if (arg0->f3C >= 0) {
        *arg3 = arg0->f3C - arg0->f40;
    } else {
        *arg3 = 0x1FFFFFFF;
    }
    ((TLobby *)(arg0->f4))->get_field_0x3c();
}

void TLobby::reset_flag() {
    u8 *arg0 = (u8 *)this;
    TLobby__sub_803C39CC((u8 *)(*(s32 *)((s8 *)arg0 + 4)));
    *(s8 *)((s8 *)arg0 + 1) = 0;
}
void TLobby__sub_803C0758(u8 *arg0) {
    *(s32 *)((s8 *)arg0 + 0x98) = 0;
    *(s32 *)((s8 *)arg0 + 0x2C) = 0;
    *(s32 *)((s8 *)arg0 + 0x30) = 0;
    *(s32 *)((s8 *)arg0 + 0x34) = 0;
    *(s32 *)((s8 *)arg0 + 0x38) = 0x7FFFFFFF;
    *(s32 *)((s8 *)arg0 + 0x3C) = -1;
    *(s32 *)((s8 *)arg0 + 0x40) = 0;
    *(s32 *)((s8 *)arg0 + 0x44) = 0;
    *(s8 *)((s8 *)arg0 + 3) = 0;
    *(s8 *)((s8 *)arg0 + 1) = 1;
}
void TLobby::set_network_result(s32 arg1) {
    u8 *arg0 = (u8 *)this;
    *(s32 *)((s8 *)arg0 + 0x38) = arg1;
    TLobby__sub_803C1A00((int) (*(s32 *)((s8 *)arg0 + 4)));
}
void TLobby::set_param_and_notify(s32 arg1) {
    u8 *arg0 = (u8 *)this;
    *(s32 *)((s8 *)arg0 + 8) = arg1;
    ((TLobby *)(*(s32 *)((s8 *)arg0 + 4)))->invoke_notify_callback();
}

s32 TLobby__sub_803C07E8(Obj_803C07E8 *self) {
    return self->b;
}

void TLobby::reset_entry() {
    u8 *arg0 = (u8 *)this;
    u8 *lobby;
    if (arg0 != NULL) {
        lobby = (u8 *)(*(u8 **)((s8 *)arg0 + 4));
        if (lobby != NULL) {
            ((TLobby *)lobby)->clear_record();
        }
        TLobby::init_once();
        memset(arg0, 0, 0x9C);
        TLobby::release_ref();
    }
}
AudioStreamInputState *TLobby__sub_803C0848(AudioStreamSource *source, s32 channels, SjRingBuffer **rings) {
    AudioStreamInputState *st;
    s32 i;
    u8 *buffer;
    SjRingBuffer *ring = rings[0];
    s32 size;
    for (i = 0; i < 0x10; i++) {
        if (((AudioStreamInputState *)&lbl_80570AC0)[i].in_use == 0) {
            break;
        }
    }
    if (i == 0x10) {
        return NULL;
    }
    st = &((AudioStreamInputState *)&lbl_80570AC0)[i];
    buffer = sj_ring_buffer_get_buffer(ring);
    size = sj_ring_buffer_get_buffer_size(ring) / 2;
    st->decoder_handle = alloc_record__6TLobbyFiiii(channels, buffer, size, size + sj_ring_buffer_get_extra_buffer_size(ring) / 2);
    if (st->decoder_handle == 0) {
        return NULL;
    }
    TLobby__sub_803C3B5C(st->decoder_handle, TLobby__sub_803C0628, st);
    st->source = source;
    st->channel_count = channels;
    for (i = 0; i < channels; i++) {
        st->rings[i] = rings[i];
    }
    st->state = 0;
    st->header_size = 0;
    st->decoded_samples = 0;
    st->decoded_bytes = 0;
    st->decode_position = 0;
    st->max_decode_samples = 0x7FFFFFFF;
    st->trap_position = -1;
    st->trap_samples = 0;
    st->trap_bytes = 0;
    st->end_when_empty = 0;
    st->trap_callback = NULL;
    st->trap_context = NULL;
    st->output_callback = NULL;
    st->output_context = NULL;
    st->in_use = 1;
    return st;
}

void TLobby::clear_session_buffer() {
    memset((void *) (&(*(RecoveredGlobal_803C0AD8_lbl_80570AC0 *)&lbl_80570AC0).value), 0, 0x9C0);
}
void TLobby::reset_sound_buffers() {
    TLobby__sub_803C406C();
    memset(&lbl_80570AC0.value, 0, 0x9C0);
}
void TLobby__sub_803C0B3C(u8 *lobby) {
    s16 temp_r0;
    temp_r0 = *(s16 *)((s8 *)lobby + 0xAA);
    if (temp_r0 == 2) {
        EXIGetID((Snd_803C0BE8 *)(lobby));
        return;
    }
    if (temp_r0 == 1) {
        ((TLobby *)lobby)->convert_pcm_u8_to_s16();
        return;
    }
    if (temp_r0 == 0) {
        TLobby__sub_803C133C((Snd_803C0BE8 *)(lobby));
    }
}
s32 TLobby::is_riff_wave() {
    u8 *arg0 = (u8 *)this;
    if (memcmp(arg0, &lbl_805E0CB0, 4) == 0 && memcmp((u8 *)&this->m_prev, &lbl_805E0CB8, 4) == 0) {
        return 1;
    }
    return 0;
}

void EXIGetID(Snd_803C0BE8 *arg0) {
    u8 *src = arg0->src;
    s16 *l;
    s16 *r;
    s32 i;
    s32 n;
    if (arg0->state == 1 && ((TLobby *)(arg0->lobby))->get_client_count() == 0) {
        arg0->get(arg0->getCtx, &arg0->pos, &arg0->avail, &arg0->unk78);
        n = arg0->size - arg0->pos;
        if (n > arg0->avail) {
            n = arg0->avail;
        }
        if (n > arg0->max) {
            n = arg0->max;
        }
        l = arg0->dst + arg0->pos;
        if (arg0->channels == 2) {
            r = arg0->dst + (arg0->rofs + arg0->pos);
            for (i = 0; i < n; i++) {
                l[i] = src[i * 4] | (src[i * 4 + 2] << 8);
                r[i] = src[i * 4 + 1] | (src[i * 4 + 3] << 8);
            }
        } else {
            for (i = 0; i < n; i++) {
                l[i] = src[i * 2] | (src[i * 2 + 1] << 8);
            }
        }
        arg0->count = n;
        arg0->bytes = arg0->channels * (n * 2);
        arg0->state = 2;
    }
    if (arg0->state == 2) {
        arg0->put(arg0->putCtx, arg0->bytes, arg0->count);
        arg0->state = 3;
    }
}

void TLobby::convert_pcm_u8_to_s16() {
    Snd_803C0F98 *arg0 = (Snd_803C0F98 *)this;
    u8 *src = arg0->src;
    s16 *l;
    s16 *r;
    s32 i;
    s32 n;
    if (arg0->state == 1 && ((TLobby *)(arg0->lobby))->get_client_count() == 0) {
        arg0->get(arg0->getCtx, &arg0->pos, &arg0->avail, &arg0->unk78);
        n = arg0->size - arg0->pos;
        if (n > arg0->avail) {
            n = arg0->avail;
        }
        if (n > arg0->max) {
            n = arg0->max;
        }
        l = arg0->dst + arg0->pos;
        if (arg0->channels == 2) {
            r = arg0->dst + (arg0->rofs + arg0->pos);
            for (i = 0; i < n; i++) {
                l[i] = (u8)(src[i * 2] - 0x80) << 8;
                r[i] = (u8)(src[i * 2 + 1] - 0x80) << 8;
            }
        } else {
            for (i = 0; i < n; i++) {
                l[i] = (u8)(src[i] - 0x80) << 8;
            }
        }
        arg0->count = n;
        arg0->bytes = n * arg0->channels;
        arg0->state = 2;
    }
    if (arg0->state == 2) {
        arg0->put(arg0->putCtx, arg0->bytes, arg0->count);
        arg0->state = 3;
    }
}

void TLobby__sub_803C133C(Snd_803C0BE8 *arg0) {
    u16 *src = (u16 *)arg0->src;
    s16 *l;
    s16 *r;
    s32 i;
    s32 n;
    if (arg0->state == 1 && ((TLobby *)(arg0->lobby))->get_client_count() == 0) {
        arg0->get(arg0->getCtx, &arg0->pos, &arg0->avail, &arg0->unk78);
        n = arg0->size - arg0->pos;
        if (n > arg0->avail) {
            n = arg0->avail;
        }
        if (n > arg0->max) {
            n = arg0->max;
        }
        l = arg0->dst + arg0->pos;
        if (arg0->channels == 2) {
            r = arg0->dst + (arg0->rofs + arg0->pos);
            for (i = 0; i < n; i++) {
                l[i] = (((src[i * 2]) & 0xFF) << 8) | (((src[i * 2]) >> 8) & 0xFF);
                r[i] = (((src[i * 2 + 1]) & 0xFF) << 8) | (((src[i * 2 + 1]) >> 8) & 0xFF);
            }
        } else {
            for (i = 0; i < n; i++) {
                l[i] = (((src[i]) & 0xFF) << 8) | (((src[i]) >> 8) & 0xFF);
            }
        }
        arg0->count = n;
        arg0->bytes = arg0->channels * (n * 2);
        arg0->state = 2;
    }
    if (arg0->state == 2) {
        arg0->put(arg0->putCtx, arg0->bytes, arg0->count);
        arg0->state = 3;
    }
}

typedef char RecoveredGlobal_803C0B08_lbl_80570AC0_size[sizeof(RecoveredGlobal_803C0B08_lbl_80570AC0) == 0x9C0 ? 1 : -1];
typedef char RecoveredGlobal_803C0AD8_lbl_80570AC0_size[sizeof(RecoveredGlobal_803C0AD8_lbl_80570AC0) == 0x9C0 ? 1 : -1];

}
