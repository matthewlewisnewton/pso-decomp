"""Characterize the checked-in DHCP ACK/request/parser chain on a host.

Six actual function definitions and their record declarations are extracted from
source. Histories, option storage, clocks and socket services are synthetic.
All copied/scanned bytes are allocated; only a positive, bounded receipt is
delivered to event 1. This is neither native ABI/ingress validation nor a packet
reachability, exploit or safety claim. Original behavior is deliberately retained.
"""

import hashlib
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest

from tools.tests.test_dhcp_legacy_characterization import PRELUDE, definition


ROOT = Path(__file__).resolve().parents[2]
PACKET = "src/pso/network/NetworkPacketRuntime.cpp"
STEPS = "src/pso/unk/text_80421620.cpp"
FUNCTIONS = (
    ("scanner", PACKET, "s32 find_dhcp_option__6TLobbyFPvUcPv(u8 *p, u8 tag, u8 **out) {"),
    ("setter", PACKET, "s32 TLobby__sub_80425288(s16 id, s16 len, void *value) {"),
    ("lease", PACKET, "void dhcp_parse_lease_times(u8 *arg0) {"),
    ("callback", PACKET, "s32 dhcp_handle_reply__6TLobbyFsPv(s16 arg0, u8 *record) {"),
    ("config", STEPS, "s32 TLobby__sub_80423440(BootpPacket *hdr) {"),
    ("request", STEPS, "s32 TLobby__sub_80423E80(void) {"),
)


def extracted_definitions():
    """Require the opening brace so a forward declaration cannot be selected."""
    return {
        name: definition((ROOT / path).read_text(), signature, "}")
        for name, path, signature in FUNCTIONS
    }


FIXTURES = r"""
struct TLobby {
    static void get_time_ms(s32 *out);
    static void get_time_seconds(s32 *out);
};
DhcpClientBuffers lbl_805C1E00 = {};
DhcpOption_804FD948 lbl_804FD948[12] = {};
volatile s32 dhcp_state, lbl_805D7B0C, dhcp_reply_received;
volatile s32 lbl_805D7BA0;
s16 dhcp_socket;
s32 lbl_805D7B14, lbl_805D7B74, lbl_805D7B80;
s32 lbl_805D7B8C, lbl_805D7B90;
u32 lbl_805D7B28, lbl_805D7B4C, lbl_805D7B50, lbl_805D7B94;
s32 lbl_805D7B2C, lbl_805D7B30, dhcp_server_id;
s32 *lbl_805D7B40, *lbl_805D7B44, *lbl_805D7B48;
u8 lbl_805D7B1C[6] = {1, 2, 3, 4, 5, 6};
u32 dhcp_lease_time, dhcp_renewal_time, dhcp_rebinding_time;
u32 dhcp_lease_start, dhcp_lease_expiry, dhcp_lease_elapsed;
static int seconds_calls, milliseconds_calls, close_calls, mode_calls;
static int accepted_copy_calls, accepted_copy_size;
static u32 subnet, broadcast, dns1, dns2, gateway;
static char domain[64], hostname[44];

void TLobby::get_time_ms(s32 *out) { ++milliseconds_calls; *out = 100000; }
void TLobby::get_time_seconds(s32 *out) { ++seconds_calls; *out = 100; }
void NetMemcpy(void *dst, const void *src, s32 size) {
    assert(size >= 0);
    if (dst == &lbl_805C1E00.reply) {
        // This guard belongs to the fixture, not the extracted game code.
        assert(size <= s32(sizeof(DhcpMessage)));
        assert(src == &lbl_805C1E00.received.hdr);
        ++accepted_copy_calls;
        accepted_copy_size = size;
    }
    std::memcpy(dst, src, static_cast<std::size_t>(size));
}
void NetMemset(void *dst, s32 value, s32 size) {
    assert(size >= 0);
    std::memset(dst, value, static_cast<std::size_t>(size));
}
s32 NetMemcmp(const void *a, const void *b, s32 size) {
    assert(size >= 0);
    return std::memcmp(a, b, static_cast<std::size_t>(size));
}
s32 TLobby__sub_80421B3C(s32 socket) {
    assert(socket == 42); ++close_calls; return 0;
}
s32 TLobby__sub_804250A8(s32 mode) {
    assert(mode == 0); ++mode_calls; return 0;
}
s32 TLobby__sub_80424FE0() { std::abort(); }
s32 DhcpMessage::build_request() { std::abort(); }
s16 TUdpSocket__sub_80421BAC(s32, u32 *, u32 *, u16, u32 *, s8,
                            UdpBuf_80421BAC *) { std::abort(); }
"""


CASES = r"""
static void initialize() {
    lbl_805C1E00 = {};
    lbl_805D7B4C = 0x63825363;
    lbl_805D7B50 = 0x12345678;
    lbl_805D7B28 = 0x0a000001;
    lbl_805D7B40 = lbl_805D7B44 = lbl_805D7B48 = nullptr;
    dhcp_lease_time = 999; dhcp_renewal_time = 888; dhcp_rebinding_time = 777;
    dhcp_lease_start = 666; dhcp_lease_expiry = 555; dhcp_lease_elapsed = 9;
    dhcp_reply_received = 0; lbl_805D7B0C = 2; dhcp_socket = 42;
    seconds_calls = milliseconds_calls = close_calls = mode_calls = 0;
    accepted_copy_calls = accepted_copy_size = 0;
    // Synthetic, fully allocated option storage; not imported SDK data.
    lbl_804FD948[0] = {1, 0, 1, 4, &subnet};
    lbl_804FD948[1] = {2, 0, 1, 4, &broadcast};
    lbl_804FD948[2] = {3, 0, 0, sizeof domain, domain};
    lbl_804FD948[3] = {4, 0, 1, 4, &dns1};
    lbl_804FD948[4] = {5, 0, 1, 4, &dns2};
    lbl_804FD948[5] = {6, 0, 1, 4, &gateway};
    lbl_804FD948[6] = {7, 0, 1, 4, &dhcp_lease_time};
    lbl_804FD948[7] = {8, 0, 1, 4, &dhcp_renewal_time};
    lbl_804FD948[8] = {9, 0, 1, 4, &dhcp_rebinding_time};
    lbl_804FD948[9] = {0xe, 0, 1, 4, &dhcp_server_id};
    lbl_804FD948[10] = {0xf, 0, 1, 4, &lbl_805D7B28};
    lbl_804FD948[11] = {0x10, 0, 0, sizeof hostname, hostname};
}

static void historical_ack(DhcpMessage &message, u32 lease, u8 hops) {
    message = {};
    message.hdr.op = 2; message.hdr.htype = 1; message.hdr.hlen = 6;
    message.hdr.hops = hops;
    message.hdr.xid = lbl_805D7B50; message.hdr.yiaddr = lbl_805D7B28;
    message.hdr.cookie = lbl_805D7B4C;
    std::memcpy(message.hdr.chaddr, lbl_805D7B1C, 6);
    message.options[0] = 0x35; message.options[1] = 1; message.options[2] = 5;
    message.options[3] = 0x33; message.options[4] = 4;
    // Values are host-native words for the extracted memcpy-based routines.
    // This does not model wire endianness or the GameCube ABI.
    std::memcpy(message.options + 5, &lease, sizeof lease);
    message.options[9] = 0xff;
}

static u32 stored_lease(const DhcpMessage &message) {
    u32 lease;
    std::memcpy(&lease, message.options + 5, sizeof lease);
    return lease;
}

static void event_zero_lengths() {
    initialize();
    const s16 lengths[] = {0, 1, 239, 1500, 1600, -1};
    DhcpClientBuffers before = lbl_805C1E00;
    for (s16 length : lengths) {
        NetworkReceivePrefix event = {0x400, length, nullptr};
        assert(dhcp_handle_reply__6TLobbyFsPv(0, (u8 *)&event) == 0);
        assert(event.flags == 0x400 && event.length == length);
        assert(event.buffer == (u8 *)&lbl_805C1E00.received.hdr);
        assert(std::memcmp(&before, &lbl_805C1E00, sizeof before) == 0);
        assert(accepted_copy_calls == 0 && dhcp_reply_received == 0);
    }
    // In particular, 1600 and -1 are never delivered to event 1 or copied.
}

static void ack_chain(s32 state, bool full_copy) {
    initialize();
    dhcp_state = state;
    historical_ack(lbl_805C1E00.received, 222, 0xa1);
    historical_ack(lbl_805C1E00.reply, 111, 0xb2);
    DhcpMessage previous_reply = lbl_805C1E00.reply;
    DhcpMessage incoming;
    historical_ack(incoming, 222, 0xc3);
    s16 length = full_copy ? sizeof(DhcpMessage) : 8;
    NetworkReceivePrefix event = {0x400, length, nullptr};
    assert(dhcp_handle_reply__6TLobbyFsPv(0, (u8 *)&event) == 0);
    assert(event.length == length);
    // Emulate one bounded logical receipt into the returned scratch buffer.
    std::memcpy(event.buffer, &incoming, static_cast<std::size_t>(length));
    assert(stored_lease(lbl_805C1E00.received) == 222);
    assert(stored_lease(lbl_805C1E00.reply) == 111);
    assert(dhcp_handle_reply__6TLobbyFsPv(1, (u8 *)&event) == 0);
    assert(dhcp_reply_received == 1 && dhcp_state == state && lbl_805D7B0C == 2);
    assert(accepted_copy_calls == 1 && accepted_copy_size == length);
    assert(std::memcmp(&lbl_805C1E00.reply, &incoming, length) == 0);
    if (!full_copy) {
        assert(std::memcmp((u8 *)&lbl_805C1E00.reply + 8,
                           (u8 *)&previous_reply + 8, sizeof(DhcpMessage) - 8) == 0);
    }
    assert(dhcp_lease_time == 999 && dhcp_renewal_time == 888);
    assert(dhcp_rebinding_time == 777 && dhcp_lease_start == 666);
    assert(dhcp_lease_expiry == 555 && seconds_calls == 0);
    assert(TLobby__sub_80423E80() == 3);
    assert(dhcp_state == 3 && lbl_805D7B0C == 0 && dhcp_socket == -1);
    assert(close_calls == 1 && mode_calls == (state == 2 ? 1 : 0));
    assert(milliseconds_calls == 1 && seconds_calls == (state == 2 ? 1 : 2));
    assert(dhcp_lease_time == (full_copy ? 222u : 111u));
    assert(dhcp_renewal_time == (full_copy ? 111u : 55u));
    assert(dhcp_rebinding_time == (full_copy ? 193u : 95u));
    assert(dhcp_lease_start == 100 && dhcp_lease_expiry == (full_copy ? 322u : 211u));
    assert(dhcp_lease_elapsed == (state == 2 ? 9u : 0u));
}

int main(int argc, char **argv) {
    assert(argc == 2);
    if (std::strcmp(argv[1], "lengths") == 0) {
        event_zero_lengths();
    } else if (std::strcmp(argv[1], "full") == 0) {
        for (s32 state : {2, 4, 5}) ack_chain(state, true);
    } else {
        s32 state = std::atoi(argv[1]);
        assert(state == 2 || state == 4 || state == 5);
        ack_chain(state, false);
    }
    std::puts(argv[1]);
}
"""


class DhcpAckChainCharacterization(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = shutil.which("g++")
        if compiler is None:
            raise unittest.SkipTest("g++ is required for isolated source characterization")
        packet = (ROOT / PACKET).read_text()
        steps = (ROOT / STEPS).read_text()
        declarations = (ROOT / "include/pso/network/DhcpClient.h").read_text()
        prefix = (ROOT / "include/pso/network/NetworkReceiveCallback.h").read_text()
        records = [definition(declarations, f"struct {name} {{", "};")
                   for name in ("BootpPacket", "DhcpMessage", "DhcpClientBuffers")]
        records.append(definition(prefix, "struct NetworkReceivePrefix {", "};"))
        records.append(definition(packet, "struct DhcpOption_804FD948 {", "};"))
        record = re.search(r"(?m)^struct UdpBuf_80421BAC \{[^\n]+\};$", steps)
        if record is None:
            raise AssertionError("Cannot find checked-in UdpBuf_80421BAC declaration")
        records.append(record.group(0))
        bodies = extracted_definitions()
        cls.source_sha256 = {name: hashlib.sha256(body.encode()).hexdigest()
                             for name, body in bodies.items()}
        temporary = tempfile.TemporaryDirectory()
        cls.addClassCleanup(temporary.cleanup)
        path = Path(temporary.name)
        harness = path / "dhcp_ack_chain.cpp"
        harness.write_text("\n".join([
            PRELUDE, "#include <cstdlib>\n#include <cstddef>\n#include <initializer_list>\n"
                     "using s8 = std::int8_t;\nusing u16 = std::uint16_t;",
            *records, 'static_assert(sizeof(DhcpMessage) == 1500, "allocated message extent");',
            'static_assert(offsetof(BootpPacket, cookie) == 236, "fixture option origin");',
            FIXTURES, *bodies.values(), CASES,
        ]))
        cls.binary = path / "dhcp_ack_chain"
        # Permissive mode admits the scanner's original pointer-to-word casts
        # on a 64-bit host, as well as casts in unexecuted send branches.
        result = subprocess.run(
            [compiler, "-std=c++17", "-O2", "-fpermissive", str(harness), "-o", str(cls.binary)],
            capture_output=True, text=True, timeout=30,
        )
        if result.returncode:
            raise AssertionError(result.stdout + result.stderr)

    def run_case(self, name):
        result = subprocess.run([str(self.binary), name], capture_output=True, text=True, timeout=5)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertEqual(result.stdout.strip(), name)

    def test_event_zero_preserves_signed_lengths_without_copying(self):
        self.run_case("lengths")

    def test_request_ack_applies_persistent_stale_lease(self):
        self.run_case("2")

    def test_renewal_ack_applies_persistent_stale_lease(self):
        self.run_case("4")

    def test_rebinding_ack_applies_persistent_stale_lease(self):
        self.run_case("5")

    def test_full_synthetic_receipt_replaces_the_old_lease(self):
        self.run_case("full")


if __name__ == "__main__":
    unittest.main()
