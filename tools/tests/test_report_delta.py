import tempfile
import unittest
from pathlib import Path

from tools import report_delta as delta


class PaddingEvidenceTests(unittest.TestCase):
    def setUp(self):
        self.row = {"module": "psov3", "section": "extab", "address": "0x80000004", "size": 4}

    def test_symbol_inventory_includes_undotted_sections(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "symbols.txt"
            path.write_text("entry = extab:0x80000004; // type:object\n"
                            "other = .data:0x80000010; // type:object\n")
            starts = delta.symbol_starts(path)
        self.assertEqual(starts["extab"], [0x80000004])
        self.assertFalse(delta.is_alignment_padding(self.row, lambda a, n: bytes(n), starts))

    def test_missing_or_empty_inventory_cannot_prove_padding(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "symbols.txt"
            self.assertIsNone(delta.symbol_starts(path))
            path.write_text("")
            self.assertIsNone(delta.symbol_starts(path))
        self.assertFalse(delta.is_alignment_padding(self.row, lambda a, n: bytes(n), None))

    def test_short_dol_read_cannot_prove_padding(self):
        self.assertFalse(delta.is_alignment_padding(self.row, lambda a, n: bytes(n - 1), {}))
        self.assertTrue(delta.is_alignment_padding(self.row, lambda a, n: bytes(n), {}))
        self.assertFalse(delta.is_alignment_padding(self.row, lambda a, n: b"\0\0\0\1", {}))

    def test_truncated_dol_segment_is_not_padding(self):
        header = bytearray(0x100)
        header[0:4] = (0x100).to_bytes(4, "big")
        header[0x48:0x4c] = (0x80000000).to_bytes(4, "big")
        header[0x90:0x94] = (8).to_bytes(4, "big")
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "test.dol"
            path.write_bytes(header + bytes(6))
            self.assertFalse(delta.is_alignment_padding(self.row, delta.dol_reader(path), {}))

    def test_compare_keeps_symbol_bearing_lost_range_as_failure(self):
        before = {"units": [{"name": "unit", "metadata": {"module_name": "psov3"},
                             "sections": [{"name": "extab", "size": 4,
                                           "metadata": {"virtual_address": 0x80000004}}]}]}
        after = {"units": []}
        result = delta.compare(before, after, read=lambda a, n: bytes(n),
                               starts={"extab": [0x80000004]})
        self.assertEqual(result["data_coverage_lost"], [self.row])
        self.assertIn("Original data addresses disappeared from coverage", result["failures"])


if __name__ == "__main__":
    unittest.main()
