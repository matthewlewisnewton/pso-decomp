import unittest

from tools.orig_asm import bodies


def disassembly(suffix):
    return (
        "# .text:0x0 | 0x80001000 | size: 0xC\n"
        ".fn wrapper, global\n"
        "/* 80001000 00000000  7C A6 2B 78 */ mr r6, r5\n"
        "# .text:0x4 | 0x80001004 | size: 0x0\n"
        ".sym shared_entry, global\n"
        + suffix
        + "/* 80001008 00000008  4E 80 00 20 */ blr\n"
        ".endfn wrapper\n"
    )


class EntrySuffixTests(unittest.TestCase):
    def test_extracts_entry_without_wrapper_prefix_or_redeclared_label(self):
        asm = disassembly("/* 80001004 00000004  E0 05 00 00 */ psq_l f0, 0(r5), 0, qr0\n")
        result = bodies(asm, {"wrapper", "shared_entry"})
        self.assertEqual(result["shared_entry"], [
            "nofralloc", "opword 0xE0050000", "opword 0x4E800020",
        ])
        self.assertEqual(result["wrapper"][1:3], ["opword 0x7CA62B78", "entry shared_entry"])

    def test_refuses_relative_branch_back_into_wrapper(self):
        asm = disassembly("/* 80001004 00000004  4B FF FF FC */ b .L_80001000\n")
        self.assertIn("branch", bodies(asm, {"shared_entry"})["shared_entry"])

    def test_refuses_relocation(self):
        asm = disassembly("/* 80001004 00000004  3C 80 00 00 */ lis r4, matrix@ha\n")
        self.assertIn("relocation", bodies(asm, {"shared_entry"})["shared_entry"])

    def test_refuses_traps_and_system_calls(self):
        for encoded, mnemonic in (
            ("0C 00 00 00", "twi 0, r0, 0"),
            ("7C 00 00 08", "tw 0, r0, r0"),
            ("44 00 00 02", "sc"),
        ):
            with self.subTest(mnemonic=mnemonic):
                asm = disassembly(f"/* 80001004 00000004  {encoded} */ {mnemonic}\n")
                self.assertIn("trap", bodies(asm, {"shared_entry"})["shared_entry"])
