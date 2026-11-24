"""Characterize the actual DHCP timer's modulo-32-bit millisecond arithmetic.

The checked-in timer definition is compiled with synthetic state and clock/socket
services. UBSan is enabled so the signed-boundary cases detect signed-overflow
regressions even when ordinary native instructions happen to wrap. This is host
source characterization, not a native ABI, concurrency or clock-accuracy proof.
"""

import hashlib
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

from tools.tests.test_dhcp_legacy_characterization import definition


ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "src/pso/unk/text_80421620.cpp"


def extracted_definition():
    return definition(SOURCE.read_text(), "void TLobby__sub_80423298(void) {", "}")


PRELUDE = r"""
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>
using s16 = std::int16_t;
using s32 = std::int32_t;
using u32 = std::uint32_t;
static_assert(sizeof(s32) == 4 && sizeof(u32) == 4, "native word widths");
static_assert(static_cast<s32>(u32(0x80000000)) == (-2147483647 - 1),
              "fixture's signed-word representation");
static_assert(static_cast<s32>(u32(0xffffffff)) == -1,
              "original unsigned-difference assignment to signed word");
volatile s32 dhcp_state, lbl_805D7B0C, lbl_805D7BA0;
s32 dhcp_last_tick_ms;
u32 dhcp_elapsed_ms, dhcp_lease_elapsed;
u32 dhcp_lease_time, dhcp_renewal_time, dhcp_rebinding_time;
s16 dhcp_socket;
static s32 clock_value;
static int clock_calls, close_calls, discover_calls, request_calls, release_calls;
struct TLobby {
    static void get_time_ms(s32 *out) { ++clock_calls; *out = clock_value; }
};
s32 TLobby__sub_80421B3C(s32 socket) {
    assert(socket == 42); ++close_calls; return 0;
}
s32 TLobby__sub_8042422C() { ++discover_calls; return 0; }
s32 TLobby__sub_80423E80() { ++request_calls; return 0; }
s32 TLobby__sub_80423C04() { ++release_calls; return 0; }
"""


CASES = r"""
static void initialize(u32 previous, u32 current, u32 remainder) {
    dhcp_state = 3;
    lbl_805D7B0C = 7;
    lbl_805D7BA0 = 99;
    dhcp_last_tick_ms = static_cast<s32>(previous);
    clock_value = static_cast<s32>(current);
    dhcp_elapsed_ms = remainder;
    dhcp_lease_elapsed = 9;
    dhcp_lease_time = 20;
    dhcp_renewal_time = 15;
    dhcp_rebinding_time = 17;
    dhcp_socket = 42;
    clock_calls = close_calls = discover_calls = request_calls = release_calls = 0;
}
static void verify(u32 remainder, u32 seconds) {
    TLobby__sub_80423298();
    assert(dhcp_last_tick_ms == clock_value);
    assert(dhcp_elapsed_ms == remainder && dhcp_lease_elapsed == seconds);
    assert(dhcp_state == 3 && lbl_805D7B0C == 7 && lbl_805D7BA0 == 0);
    assert(dhcp_socket == 42 && clock_calls == 1 && close_calls == 0);
    assert(discover_calls == 0 && request_calls == 0 && release_calls == 0);
}
int main(int argc, char **argv) {
    assert(argc == 2);
    if (std::strcmp(argv[1], "signed_boundary") == 0) {
        initialize(0x7fffffff, 0x80000000, 999);
        verify(0, 10);
    } else if (std::strcmp(argv[1], "full_wrap") == 0) {
        initialize(0xffffffff, 0, 249);
        verify(250, 9);
    } else if (std::strcmp(argv[1], "boundary_span") == 0) {
        initialize(0x7fffff80, 0x80000080, 800);
        verify(56, 10);
    } else if (std::strcmp(argv[1], "backward_boundary") == 0) {
        // Preserve the old unsigned difference and its signed-word assignment;
        // do not replace backwards clock observations with a clamp or reset.
        initialize(0x80000000, 0x7fffffff, 250);
        verify(249, 9);
    } else {
        return 2;
    }
    std::puts(argv[1]);
}
"""


class DhcpTickCharacterization(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = shutil.which("g++")
        if compiler is None:
            raise unittest.SkipTest("g++ is required for isolated source characterization")
        body = extracted_definition()
        cls.source_sha256 = hashlib.sha256(body.encode()).hexdigest()
        temporary = tempfile.TemporaryDirectory()
        cls.addClassCleanup(temporary.cleanup)
        path = Path(temporary.name)
        harness = path / "dhcp_tick.cpp"
        harness.write_text("\n".join((PRELUDE, body, CASES)))
        cls.binary = path / "dhcp_tick"
        result = subprocess.run(
            [compiler, "-std=c++17", "-O2", "-fsanitize=undefined",
             "-fno-sanitize-recover=undefined", str(harness), "-o", str(cls.binary)],
            capture_output=True, text=True, timeout=30,
        )
        if result.returncode:
            raise AssertionError(result.stdout + result.stderr)

    def run_case(self, name):
        result = subprocess.run([str(self.binary), name], capture_output=True, text=True, timeout=5)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertEqual(result.stdout.strip(), name)

    def test_tick_crosses_signed_boundary_and_carries_one_second(self):
        self.run_case("signed_boundary")

    def test_tick_wraps_at_the_full_unsigned_word(self):
        self.run_case("full_wrap")

    def test_multi_millisecond_span_across_signed_boundary(self):
        self.run_case("boundary_span")

    def test_backward_boundary_keeps_original_modulo_difference(self):
        self.run_case("backward_boundary")


if __name__ == "__main__":
    unittest.main()
