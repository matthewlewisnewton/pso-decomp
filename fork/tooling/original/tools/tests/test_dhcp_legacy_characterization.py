"""Characterize checked-in DHCP routines without changing their native behavior.

Only the scanner and option setter are compiled, directly from their definitions.
Fixtures have enough allocated storage for every access, including bytes beyond a
logical short copy. They demonstrate legacy behavior, not an end-to-end packet
exploit or a safety guarantee. This host harness is not a native ABI/codegen test.
"""

from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "src/pso/network/NetworkPacketRuntime.cpp"


def definition(source, start, end):
    """Select an actual top-level definition, not a second implementation."""
    match = re.search(r"(?ms)^" + re.escape(start) + r".*?^" + re.escape(end), source)
    if match is None:
        raise AssertionError(f"Cannot find checked-in definition: {start}")
    return match.group(0)


PRELUDE = r"""
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>
using u8 = std::uint8_t;
using s16 = std::int16_t;
using u32 = std::uint32_t;
using s32 = std::int32_t;
static_assert(sizeof(u32) == 4 && sizeof(s32) == 4, "native word widths");
static_assert(static_cast<s32>(u32(0) - 1) == -1, "signed word conversion");
"""


FIXTURES = r"""
static int last_copy_size = -1;
void NetMemcpy(void *dst, void *src, int size) {
    assert(size >= 0);
    last_copy_size = size;
    std::memcpy(dst, src, static_cast<std::size_t>(size));
}
void NetMemset(void *dst, int value, int size) {
    assert(size >= 0);
    std::memset(dst, value, static_cast<std::size_t>(size));
}
DhcpOption_804FD948 lbl_804FD948[12] = {};
"""


CASES = r"""
int main(int argc, char **argv) {
    assert(argc == 2);
    const char *test = argv[1];
    if (std::strcmp(test, "pad_end") == 0) {
        u8 bytes[32] = {};
        bytes[5] = 0x35; bytes[6] = 1; bytes[7] = 5; bytes[8] = 0xff;
        u8 *out = nullptr;
        assert(find_dhcp_option__6TLobbyFPvUcPv(bytes, 0x35, &out) == 1);
        assert(out == bytes + 7 && *out == 5);
        out = bytes;
        assert(find_dhcp_option__6TLobbyFPvUcPv(bytes, 0x36, &out) == 0);
        assert(out == bytes); // An absent tag does not update the output.
    } else if (std::strcmp(test, "byte_lengths") == 0) {
        u8 bytes[300] = {};
        bytes[4] = 0x35; bytes[5] = 0;
        u8 *out = nullptr;
        assert(find_dhcp_option__6TLobbyFPvUcPv(bytes, 0x35, &out) == 0);
        assert(out == bytes + 6); // Found zero-length and absent both return 0.
        bytes[5] = 255;
        assert(find_dhcp_option__6TLobbyFPvUcPv(bytes, 0x35, &out) == 255);
        assert(out == bytes + 6);
    } else if (std::strcmp(test, "stale_tail") == 0) {
        u8 persistent[32] = {};
        u8 first[32] = {};
        first[8] = 0x35; first[9] = 1; first[10] = 5; first[11] = 0xff;
        std::memcpy(persistent, first, sizeof first);
        u8 next[8] = {};
        std::memcpy(persistent, next, sizeof next); // No implicit tail clear.
        u8 *out = nullptr;
        assert(find_dhcp_option__6TLobbyFPvUcPv(persistent, 0x35, &out) == 1);
        assert(out == persistent + 10 && *out == 5);
        assert(out >= persistent + sizeof next);
    } else if (std::strcmp(test, "truncated_value") == 0) {
        u8 persistent[32] = {};
        persistent[7] = 0xb2; persistent[8] = 0xc3; persistent[9] = 0xd4;
        u8 next[7] = {0, 0, 0, 0, 0x36, 4, 0xa1};
        std::memcpy(persistent, next, sizeof next);
        u8 *out = nullptr;
        assert(find_dhcp_option__6TLobbyFPvUcPv(persistent, 0x36, &out) == 4);
        const u8 expected[] = {0xa1, 0xb2, 0xc3, 0xd4};
        assert(std::memcmp(out, expected, sizeof expected) == 0);
    } else if (std::strcmp(test, "forward_cursor") == 0) {
        u8 bytes[0x600] = {};
        bytes[0x500] = 0x35; bytes[0x501] = 1; bytes[0x502] = 7;
        u8 *out = nullptr;
        assert(find_dhcp_option__6TLobbyFPvUcPv(bytes, 0x35, &out) == 1);
        assert(out == bytes + 0x502 && *out == 7);
    } else if (std::strcmp(test, "fixed_copy") == 0) {
        u8 dst[4] = {};
        u8 value[4] = {0xa1, 0xb2, 0xc3, 0xd4};
        lbl_804FD948[0] = {7, 0, 1, 4, dst};
        assert(TLobby__sub_80425288(7, 1, value) == 0);
        assert(last_copy_size == 4 && lbl_804FD948[0].present == 1);
        assert(std::memcmp(dst, value, sizeof dst) == 0);
        lbl_804FD948[0].kind = 0;
        assert(TLobby__sub_80425288(7, 1, value) == 0);
        assert(last_copy_size == 4);
        assert(dst[0] == 0xa1 && dst[1] == 0 && dst[2] == 0xc3 && dst[3] == 0xd4);
    } else if (std::strcmp(test, "clear_option") == 0) {
        u8 dst[4] = {1, 2, 3, 4};
        lbl_804FD948[0] = {7, 1, 1, 4, dst};
        assert(TLobby__sub_80425288(7, 0, nullptr) == 0);
        assert(lbl_804FD948[0].present == 0 && dst[0] == 1 && dst[3] == 4);
        assert(TLobby__sub_80425288(7, 1, nullptr) == 0);
        const u8 zeros[4] = {};
        assert(std::memcmp(dst, zeros, sizeof dst) == 0);
        assert(TLobby__sub_80425288(99, 1, nullptr) == -1);
    } else {
        return 2;
    }
    std::puts(test);
}
"""


class LegacyDhcpCharacterization(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = shutil.which("g++")
        if compiler is None:
            raise unittest.SkipTest("g++ is required for isolated source characterization")
        source = SOURCE.read_text()
        option = definition(source, "struct DhcpOption_804FD948 {", "};")
        scanner = definition(source, "s32 find_dhcp_option__6TLobbyFPvUcPv(", "}")
        setter = definition(source, "s32 TLobby__sub_80425288(s16 id,", "}")
        tmp = tempfile.TemporaryDirectory()
        cls.addClassCleanup(tmp.cleanup)
        path = Path(tmp.name)
        harness = path / "legacy_dhcp.cpp"
        harness.write_text("\n".join((PRELUDE, option, FIXTURES, scanner, setter, CASES)))
        cls.binary = path / "legacy_dhcp"
        # The game deliberately casts addresses to 32-bit words. GCC's permissive
        # mode permits those exact source casts on a 64-bit host. All fixtures
        # stay within one allocated array and do not test ABI or pointer layout.
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

    def test_padding_end_marker_and_absent_output(self):
        self.run_case("pad_end")

    def test_option_length_is_an_unsigned_byte_including_zero(self):
        self.run_case("byte_lengths")

    def test_short_copy_leaves_old_tlv_visible(self):
        self.run_case("stale_tail")

    def test_advertised_value_length_can_include_old_bytes(self):
        self.run_case("truncated_value")

    def test_base_minus_cursor_is_not_a_forward_bound(self):
        self.run_case("forward_cursor")

    def test_setter_uses_table_size_and_length_only_for_terminator(self):
        self.run_case("fixed_copy")

    def test_null_value_clear_rules(self):
        self.run_case("clear_option")


if __name__ == "__main__":
    unittest.main()
