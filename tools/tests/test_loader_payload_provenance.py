"""Synthetic controls: no original game or payload bytes are required."""

import struct
from pathlib import Path
import tempfile
import unittest

from tools import audit_loader_payload_provenance as audit


def fixture():
    data = bytearray(0x300)
    for offset, value in ((0, 0x100), (0x48, 0x81000000), (0x90, 0x100),
                          (0xD8, 0x82000000), (0xDC, 0x40), (0xE0, 0x81000004)):
        struct.pack_into(">I", data, offset, value)
    return data


class PayloadMetadataTests(unittest.TestCase):
    def test_entry_and_extent_positive_control(self):
        result = audit.payload_metadata(fixture())
        self.assertTrue(result["entry_in_active_text"])
        self.assertFalse(result["entry_in_restore"])
        self.assertFalse(result["active_section_destinations_overlap_restore"])

    def test_hole_stops_loader_without_hiding_later_declared_section(self):
        data = fixture()
        for offset, value in ((8, 0x200), (0x50, audit.WATCH[0]), (0x98, 20), (0xE0, audit.WATCH[0])):
            struct.pack_into(">I", data, offset, value)
        result = audit.payload_metadata(data)
        self.assertEqual(len(result["sections"]), 2)
        self.assertFalse(result["sections"][1]["loader_active"])
        self.assertTrue(result["entry_in_restore"])
        self.assertFalse(result["entry_in_active_text"])
        self.assertFalse(result["active_section_destinations_overlap_restore"])

    def test_active_section_and_bss_watch_controls(self):
        data = fixture()
        for offset, value in ((0x48, audit.WATCH[0] - 4), (0xD8, audit.WATCH[1] - 1)):
            struct.pack_into(">I", data, offset, value)
        result = audit.payload_metadata(data)
        self.assertTrue(result["active_section_destinations_overlap_restore"])
        self.assertTrue(result["bss_overlaps_restore"])
        self.assertFalse(audit.overlap(audit.WATCH[1], 4))
        self.assertFalse(audit.overlap(audit.WATCH[0] - 4, 4))
        self.assertFalse(audit.overlap(audit.WATCH[0], 0))

    def test_reject_truncation_bad_file_extent_and_destination_wrap(self):
        for data in (fixture()[:0xFF], fixture()):
            if len(data) >= 0x100:
                struct.pack_into(">I", data, 0x90, 0x300)
            with self.assertRaises(ValueError):
                audit.parse_dol(data)
        for offset in (0x48, 0xD8):
            data = fixture()
            struct.pack_into(">I", data, offset, 0xFFFFFFF0)
            with self.assertRaises(ValueError):
                audit.parse_dol(data)

    def test_direct_link_and_nonlink_refs_but_not_indirect_target(self):
        data = fixture()
        base = 0x81000000
        target = next(iter(audit.TARGETS))
        branch = 0x48000000 | ((target - base) & 0x03FFFFFC)
        struct.pack_into(">III", data, 0x100, branch | 1, (branch - 4) & ~1, 0x4E800020)
        refs = audit.main_metadata(data)["direct_references"]
        self.assertEqual([row["target"] for row in refs], [target, target])
        self.assertEqual([row["link"] for row in refs], [True, False])

    def test_data_scan_uses_virtual_alignment_and_rejects_unaligned_text(self):
        data = fixture()
        for offset, value in ((0x1C, 0x200), (0x64, 0x82000001), (0xAC, 12)):
            struct.pack_into(">I", data, offset, value)
        target = next(iter(audit.TARGETS))
        struct.pack_into(">I", data, 0x203, target)
        refs = audit.main_metadata(data)["aligned_initialized_data_words"]
        self.assertEqual(refs, [dict(address=0x82000004, value=target, target_name=audit.TARGETS[target])])
        struct.pack_into(">I", data, 0x48, 0x81000001)
        with self.assertRaises(ValueError):
            audit.main_metadata(data)

    def test_existing_output_and_symlink_are_preserved(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "input-or-receipt"
            path.write_bytes(b"preserve")
            alias = Path(directory) / "alias"
            alias.symlink_to(path)
            for output in (path, alias):
                with self.assertRaises(FileExistsError):
                    audit.write_result(output, {})
            self.assertEqual(path.read_bytes(), b"preserve")
            output = Path(directory) / "new-receipt"
            audit.write_result(output, {"ok": True})
            self.assertIn('"ok": true', output.read_text())


if __name__ == "__main__":
    unittest.main()
