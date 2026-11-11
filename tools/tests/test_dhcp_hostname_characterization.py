"""Exercise the actual hostname setter and option setter with allocated fixtures.

This preserves the legacy 16-bit acceptance checks and fixed-size copy. It is
an original-free host characterization, not an ingress, native ABI or safety
proof. Every source/destination has storage for every executed access.
"""

from pathlib import Path
import hashlib
import re
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]
PACKET = ROOT / "src/pso/network/NetworkPacketRuntime.cpp"
STEPS = ROOT / "src/pso/unk/text_80421620.cpp"


def definition(source, start, end):
    match = re.search(r"(?ms)^" + start + r".*?^" + re.escape(end), source)
    if match is None:
        raise AssertionError(f"Cannot find checked-in definition: {start}")
    return match.group(0)


def extracted_definitions():
    packet = PACKET.read_text()
    return {
        "option_record": definition(packet, r"struct DhcpOption_804FD948 \{", "};"),
        "option_setter": definition(packet, r"s32 TLobby__sub_80425288\(s16 id,", "}"),
        "hostname_setter": definition(
            STEPS.read_text(), r"s(?:16|32) TLobby__sub_8042455C\([^;\n]*\) \{", "}"),
    }


PRELUDE = r"""
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
static_assert(sizeof(u16) == 2 && sizeof(u32) == 4, "native integer widths");
static volatile s32 lbl_805D7BA0;
static int copies, last_copy_size, length_calls;
void NetMemcpy(void *dst, void *src, int size) {
    assert(size >= 0);
    ++copies;
    last_copy_size = size;
    std::memcpy(dst, src, static_cast<std::size_t>(size));
}
void NetMemset(void *dst, int value, int size) {
    assert(size >= 0);
    std::memset(dst, value, static_cast<std::size_t>(size));
}
u32 NetStringLength(const char *text) {
    ++length_calls;
    return static_cast<u32>(std::strlen(text));
}
"""


FIXTURES = r"""
DhcpOption_804FD948 lbl_804FD948[12] = {};
static u8 hostname_storage[0x2c];
static void reset_fixture() {
    // Actual option 0x10 is string kind 0, fixed size 32, backed by 44 bytes.
    std::memset(lbl_804FD948, 0, sizeof lbl_804FD948);
    std::memset(hostname_storage, 0xc3, sizeof hostname_storage);
    lbl_804FD948[11] = {0x10, 1, 0, 32, hostname_storage};
    lbl_805D7BA0 = 99;
    copies = 0;
    last_copy_size = -1;
    length_calls = 0;
}
"""


CASES = r"""
static void rejected_lengths() {
    reset_fixture();
    assert(TLobby__sub_8042455C(nullptr) == -1);
    assert(lbl_805D7BA0 == 1 && length_calls == 0 && copies == 0);
    assert(lbl_804FD948[11].present == 1);
    for (u8 byte : hostname_storage) assert(byte == 0xc3);
    for (std::size_t length : {0u, 32u, 65536u, 65568u}) {
        reset_fixture();
        std::vector<char> input(length + 44, 'x');
        input[length] = 0;
        assert(TLobby__sub_8042455C(input.data()) == -1);
        assert(lbl_805D7BA0 == 1 && length_calls == 1 && copies == 0);
        assert(lbl_804FD948[11].present == 1);
        for (u8 byte : hostname_storage) assert(byte == 0xc3);
    }
}
static void short_names_copy_fixed_extent() {
    for (std::size_t length : {1u, 31u}) {
        reset_fixture();
        char input[44];
        std::memset(input, 'q', sizeof input);
        input[length] = 0;
        assert(TLobby__sub_8042455C(input) == 0);
        assert(lbl_805D7BA0 == 0 && length_calls == 1 && copies == 1);
        assert(last_copy_size == 32 && lbl_804FD948[11].present == 1);
        assert(std::memcmp(hostname_storage, input, 32) == 0);
        // Bytes after the source terminator are still copied; the tail of the
        // 44-byte destination beyond the table's fixed extent is untouched.
        for (std::size_t i = 32; i < sizeof hostname_storage; ++i)
            assert(hostname_storage[i] == 0xc3);
    }
}
static void long_names_use_low_sixteen_bits() {
    for (std::size_t length : {65537u, 65567u}) {
        reset_fixture();
        std::vector<char> input(length + 44, 'x');
        input[length] = 0;
        assert(TLobby__sub_8042455C(input.data()) == 0);
        assert(lbl_805D7BA0 == 0 && length_calls == 1 && copies == 1);
        assert(last_copy_size == 32 && lbl_804FD948[11].present == 1);
        std::size_t narrowed = static_cast<u16>(length);
        for (std::size_t i = 0; i < 32; ++i)
            assert(hostname_storage[i] == (i == narrowed ? 0 : 'x'));
        for (std::size_t i = 32; i < sizeof hostname_storage; ++i)
            assert(hostname_storage[i] == 0xc3);
    }
}
int main(int argc, char **argv) {
    assert(argc == 2);
    if (std::strcmp(argv[1], "reject") == 0) rejected_lengths();
    else if (std::strcmp(argv[1], "fixed") == 0) short_names_copy_fixed_extent();
    else if (std::strcmp(argv[1], "narrow") == 0) long_names_use_low_sixteen_bits();
    else return 2;
    std::puts(argv[1]);
}
"""


class DhcpHostnameCharacterization(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = shutil.which("g++")
        if compiler is None:
            raise unittest.SkipTest("g++ is required for isolated source characterization")
        bodies = extracted_definitions()
        cls.source_sha256 = {name: hashlib.sha256(body.encode()).hexdigest()
                             for name, body in bodies.items()}
        temporary = tempfile.TemporaryDirectory()
        cls.addClassCleanup(temporary.cleanup)
        path = Path(temporary.name)
        harness = path / "dhcp_hostname.cpp"
        harness.write_text("\n".join([
            PRELUDE, bodies["option_record"], FIXTURES,
            bodies["option_setter"], bodies["hostname_setter"], CASES,
        ]))
        cls.binary = path / "dhcp_hostname"
        result = subprocess.run(
            [compiler, "-std=c++17", "-O2", str(harness), "-o", str(cls.binary)],
            capture_output=True, text=True, timeout=30,
        )
        if result.returncode:
            raise AssertionError(result.stdout + result.stderr)

    def run_case(self, name):
        result = subprocess.run([str(self.binary), name], capture_output=True, text=True, timeout=5)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertEqual(result.stdout.strip(), name)

    def test_null_and_rejected_lengths_keep_previous_storage(self):
        self.run_case("reject")

    def test_short_names_still_copy_the_full_table_extent(self):
        self.run_case("fixed")

    def test_long_names_are_accepted_after_sixteen_bit_narrowing(self):
        self.run_case("narrow")


if __name__ == "__main__":
    unittest.main()
