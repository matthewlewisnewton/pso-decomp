import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from tools import report_delta as delta


class PaddingEvidenceTests(unittest.TestCase):
    def setUp(self):
        self.row = {"module": "psov3", "section": "extab", "address": "0x80000004", "size": 4}

    def test_symbol_inventory_includes_undotted_sections(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "symbols.txt"
            path.write_text("entry = extab:0x80000004; // type:object size:0x1\n"
                            "other = .data:0x80000010; // type:object size:0x1\n")
            starts = delta.symbol_extents(path)
        self.assertEqual(starts["extab"], [(0x80000004, 0x80000005)])
        self.assertFalse(delta.is_alignment_padding(self.row, lambda a, n: bytes(n), starts))

    def test_missing_or_empty_inventory_cannot_prove_padding(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "symbols.txt"
            self.assertIsNone(delta.symbol_extents(path))
            path.write_text("")
            self.assertIsNone(delta.symbol_extents(path))
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
                               starts={"extab": [(0x80000004, 0x80000005)]})
        self.assertEqual(result["data_coverage_lost"], [self.row])
        self.assertIn("Original data addresses disappeared from coverage", result["failures"])

    def test_object_tail_loss_cannot_be_masked_by_unrelated_gains(self):
        def unit(name, address, size, exact, complete):
            return {"name": name, "metadata": {"module_name": "psov3", "complete": complete},
                    "sections": [{"name": "extab", "size": size,
                                  "fuzzy_match_percent": 100 if exact else 0,
                                  "metadata": {"virtual_address": address}}]}

        before = {"measures": {"total_data": 16, "matched_data": 8, "complete_data": 8},
                  "units": [unit("A", 0x80000000, 8, True, True),
                            unit("B", 0x80000010, 8, False, False)]}
        after = {"measures": {"total_data": 12, "matched_data": 12, "complete_data": 12},
                 "units": [unit("A", 0x80000000, 4, True, True),
                           unit("B", 0x80000010, 8, True, True)]}
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "symbols.txt"
            path.write_text("A = extab:0x80000000; // type:object size:0x8\n"
                            "B = extab:0x80000010; // type:object size:0x8\n")
            result = delta.compare(before, after, read=lambda a, n: bytes(n),
                                   starts=delta.symbol_extents(path))
        self.assertEqual(result["data_coverage_lost"], [self.row])
        self.assertEqual(result["data_regressions"], [self.row])
        self.assertEqual(result["linked_data_lost"], [self.row])
        self.assertTrue(result["failures"])

    def test_gap_after_symbol_end_and_nested_extents(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "symbols.txt"
            path.write_text("A = extab:0x80000000; // type:object size:0x4\n"
                            "B = extab:0x80000008; // type:object size:0x8\n")
            self.assertTrue(delta.is_alignment_padding(self.row, lambda a, n: bytes(n),
                                                       delta.symbol_extents(path)))
            path.write_text("A = extab:0x80000000; // type:object size:0x8\n"
                            "nested = extab:0x80000002; // type:object size:0x1\n")
            self.assertFalse(delta.is_alignment_padding(self.row, lambda a, n: bytes(n),
                                                        delta.symbol_extents(path)))

    def test_uncertain_inventory_cannot_hide_object_tail_loss(self):
        def unit(name, address, size, exact, complete):
            return {"name": name, "metadata": {"module_name": "psov3", "complete": complete},
                    "sections": [{"name": "extab", "size": size,
                                  "fuzzy_match_percent": 100 if exact else 0,
                                  "metadata": {"virtual_address": address}}]}

        before = {"measures": {"total_data": 16, "matched_data": 8, "complete_data": 8},
                  "units": [unit("A", 0x80000000, 8, True, True),
                            unit("B", 0x80000010, 8, False, False)]}
        after = {"measures": {"total_data": 12, "matched_data": 12, "complete_data": 12},
                 "units": [unit("A", 0x80000000, 4, True, True),
                           unit("B", 0x80000010, 8, True, True)]}
        cases = ["type:object", "type:object size:0xZZ", "type:object size:0x0",
                 "type:object size:-0x8", "type:object size:8"]
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "symbols.txt"
            lines = [f"A = extab:0x80000000; // {case}\n" for case in cases]
            lines.append(" A = extab:0x80000000; // type:object size:0x8\n")
            for line in lines:
                with self.subTest(line=line):
                    path.write_text(line + "B = extab:0x80000010; // type:object size:0x8\n")
                    with patch.object(delta, "symbol_extents", return_value=delta.symbol_extents(path)):
                        result = delta.compare(before, after, read=lambda a, n: bytes(n))
                    self.assertEqual(result["data_coverage_lost"], [self.row])
                    self.assertEqual(result["data_regressions"], [self.row])
                    self.assertEqual(result["linked_data_lost"], [self.row])
                    self.assertTrue(result["failures"])

    def test_no_loss_does_not_require_symbol_inventory(self):
        with patch.object(delta, "symbol_extents", side_effect=AssertionError("unneeded")):
            self.assertFalse(delta.compare({"units": []}, {"units": []})["failures"])


if __name__ == "__main__":
    unittest.main()
