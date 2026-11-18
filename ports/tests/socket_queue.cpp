#include "pso/port/SocketQueue.h"

#ifdef NDEBUG
#error Socket queue comparisons require assertions
#endif

#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstring>

TcpState tcp_protocol_state;
static TcpTcb control;
static const u32 queue_base = 0x81130000u;
static const u32 data_base = 0x81120000u;
static TcpSendRequest ring[65];
static u8 data[8192];

struct Completion {
    u32 kind, handle, callback, status;
    TcpSendRequest request;
};

// Layout of the game records consumed by the differential stream.
typedef char FragmentLayout[sizeof(NetPacketFragment) == 12 && offsetof(NetPacketFragment, buffer) == 4 ? 1 : -1];
typedef char PacketLayout[sizeof(NetPacket) == 0x9c && offsetof(NetPacket, fragments) == 12 ? 1 : -1];
typedef char RequestLayout[sizeof(TcpSendRequest) == 16 && offsetof(TcpSendRequest, callback) == 12 ? 1 : -1];
typedef char ControlLayout[offsetof(TcpTcb, snd_buf) == 0x10 && offsetof(TcpTcb, req) == 0x2c &&
                           offsetof(TcpTcb, send_done) == 0x1fc && offsetof(TcpTcb, f530) == 0x530 ? 1 : -1];
typedef char EventLayout[sizeof(Completion) == 32 && offsetof(Completion, request) == 16 ? 1 : -1];

static Completion events[66];
static u32 event_count;
static bool move_head;

static u8 *buffer_bytes(const NetBufferRef &ref, u32 length) {
    assert(ref.kind == 1 && ref.value >= data_base);
    const u32 offset = ref.value - data_base;
    assert(offset <= sizeof(data) && length <= sizeof(data) - offset);
    return data + offset;
}

static TcpSendRequest &ring_entry(const NetBufferRef &ref) {
    assert(ref.kind == 1 && ref.value >= queue_base);
    const u32 offset = ref.value - queue_base;
    assert(offset % sizeof(TcpSendRequest) == 0 && offset < sizeof(ring));
    return ring[offset / sizeof(TcpSendRequest)];
}

void read_socket_request(const NetBufferRef &source, TcpSendRequest &request) {
    request = ring_entry(source);
}

void write_socket_request(const NetBufferRef &dest, const TcpSendRequest &request) {
    ring_entry(dest) = request;
}

void NetMemcpy(void *dest, void *source, int bytes) {
    std::memmove(dest, source, bytes);
}

void TLobby__sub_80406EB8(NetBufferRef *buffer, u32 bytes) {
    buffer->value += bytes;
}

void TLobby__sub_80406FD8(void *dest, void *source, u32 bytes) {
    std::memmove(buffer_bytes(*static_cast<NetBufferRef *>(dest), bytes),
                 buffer_bytes(*static_cast<NetBufferRef *>(source), bytes), bytes);
}

s32 complete_request_callback__6TLobbyFv(s16 handle, TcpSendCallback callback, s16 status,
                                         const TcpSendRequest *request) {
    assert(event_count < 66);
    Completion &event = events[event_count++];
    event.kind = 1;
    event.handle = handle;
    event.callback = callback;
    event.status = status;
    event.request = *request;
    if (move_head && event_count == 1 && control.f20) {
        const u32 old_head = control.f24;
        control.f24 = (old_head + 17) % 65;
        ring[control.f24] = ring[old_head];
    }
    return 0;
}

s32 set_thread_state_and_resume__6TLobbyFv(s32 handle, TcpOperationCallback callback, s16 status) {
    assert(event_count < 66);
    Completion &event = events[event_count++];
    event.kind = 2;
    event.handle = handle;
    event.callback = callback;
    event.status = status;
    std::memset(&event.request, 0, sizeof(event.request));
    return 0;
}

static u32 random_state = 0x74a81bf2;
static u32 next_word() {
    random_state ^= random_state << 13;
    random_state ^= random_state >> 17;
    random_state ^= random_state << 5;
    return random_state;
}

static void check_sack() {
    for (u32 trial = 0; trial < 200000; ++trial) {
        TcpTcb actual = {};
        actual.last_reasm = static_cast<s16>(next_word() % 33) - 1;
        actual.seg_top = next_word();
        actual.una = next_word();
        actual.pad322[0] = next_word();
        actual.pad322[1] = next_word();
        const u32 base = trial % 2 ? next_word() : 0xfffffff0u;
        for (size_t i = 0; i < 5; ++i) {
            actual.sack[i].start = base + (next_word() & 127);
            actual.sack[i].end = actual.sack[i].start + (next_word() & 31);
        }
        for (size_t i = 0; i < 32; ++i) {
            const u32 start = base + (next_word() & 127);
            actual.reasm[i].start = static_cast<s32>(start);
            actual.reasm[i].end = static_cast<s32>(start + (next_word() & 31));
        }
        TcpTcb expected = actual;
        if (expected.last_reasm >= 0) {
            TcpSeqRange *sack = expected.sack;
            std::memmove(sack + 1, sack, 4 * sizeof(*sack));
            const TcpReasmRange &range = expected.reasm[expected.last_reasm];
            sack[0].start = range.start;
            sack[0].end = range.end;
            for (int i = 4; i > 0; --i) {
                if (sack[i].start == sack[i].end) continue;
                for (int j = 0; j < i; ++j) {
                    if (s32(sack[i].start - sack[j].start) >= 0 && s32(sack[i].end - sack[j].end) <= 0) {
                        std::memmove(sack + i, sack + i + 1, (4 - i) * sizeof(*sack));
                        sack[4].start = sack[4].end = 0;
                        break;
                    }
                }
            }
        }
        TLobby__sub_8041FED4(&actual);
        assert(std::memcmp(&actual, &expected, sizeof(actual)) == 0);
    }
}

static void check_ring() {
    control.f204_b7 = 1;
    control.snd_buf.kind = 1;
    control.snd_buf.value = queue_base;
    control.f20 = 2;
    control.f24 = 64;
    control.req.total_bytes = 22;
    ring[64].length = 8;
    ring[64].callback = 11;
    ring[64].buffer.value = data_base;
    ring[64].buffer.kind = 1;
    ring[0].length = 14;
    ring[0].offset = 1;
    ring[0].callback = 12;
    ring[0].buffer.value = data_base + 32;
    ring[0].buffer.kind = 1;
    NetPacket packet = {};
    assert(TLobby__sub_80420410(6, 5, &packet, &control) == 0);
    assert(packet.fragment_count == 2 && packet.total_bytes == 5);
    assert(packet.fragments[0].length == 3 && packet.fragments[0].buffer.value == data_base + 32);
    assert(packet.fragments[1].length == 2 && packet.fragments[1].buffer.value == data_base + 6);
    move_head = true;
    assert(TLobby__sub_8041FFF8(12, &control) == 0);
    assert(control.f20 == 1 && control.f24 == 17 && control.req.total_bytes == 10);
    assert(event_count == 1 && events[0].callback == 11);
    assert(ring[17].length == 10 && ring[17].offset == 5 && ring[0].length == 14);
    assert(TLobby__sub_8041FFF8(10, &control) == 0);
    assert(control.f20 == 0 && !control.f204_b7 && events[1].callback == 12);
}

static bool read_bytes(void *output, size_t size) {
    return std::fread(output, 1, size, stdin) == size;
}

static bool write_bytes(const void *input, size_t size) {
    return std::fwrite(input, 1, size, stdout) == size;
}

// A native-endian test stream, generated from the contributor's own DOL.
// Transfer the queue flag as a scalar because C++ bit-field ordering is ABI-specific.
static int compare_stream() {
    const u32 endian_marker = 0x01020304;
    if (!write_bytes(&endian_marker, sizeof(endian_marker)) || std::fflush(stdout)) return 1;
    while (true) {
        u32 args[4];
        size_t count = std::fread(args, 1, sizeof(args), stdin);
        if (count == 0 && std::feof(stdin)) return 0;
        NetPacket packet;
        if (count != sizeof(args) || !read_bytes(&control, sizeof(control)) ||
            !read_bytes(&packet, sizeof(packet)) || !read_bytes(ring, sizeof(ring)) ||
            !read_bytes(data, sizeof(data))) return 1;
        control.f204_b7 = args[0] & 1;
        move_head = args[0] & 2;
        event_count = 0;
        s32 status;
        if (args[1] == 0) status = TLobby__sub_80420410(args[2], args[3], &packet, &control);
        else if (args[1] == 1) status = TLobby__sub_8041FFF8(args[3], &control);
        else return 1;
        const u32 queued = control.f204_b7;
        control.f204_b7 = 0;
        if (!write_bytes(&status, sizeof(status)) || !write_bytes(&queued, sizeof(queued)) ||
            !write_bytes(&control, sizeof(control)) || !write_bytes(&packet, sizeof(packet)) ||
            !write_bytes(ring, sizeof(ring)) || !write_bytes(data, sizeof(data)) ||
            !write_bytes(&event_count, sizeof(event_count)) ||
            !write_bytes(events, event_count * sizeof(Completion)) || std::fflush(stdout)) return 1;
    }
}

int main(int argc, char **argv) {
    tcp_protocol_state.tcbs = &control;
    if (argc == 2 && std::strcmp(argv[1], "--stream") == 0) return compare_stream();
    if (argc != 1) return 1;
    check_sack();
    check_ring();
    std::puts("200000 SACK cases and queued send, ring wrap and reentrant ACK checks passed");
    return 0;
}
