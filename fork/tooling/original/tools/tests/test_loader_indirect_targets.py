"""Original-free controls for the deliberately incomplete PPC target tracker."""
import struct
import unittest

from tools import audit_loader_indirect_targets as audit


BASE = 0x81000000
TARGET = 0x90001000
WATCH = (TARGET, TARGET + 20)


def d(op, rt, ra, immediate):
    return (op << 26) | (rt << 21) | (ra << 16) | (immediate & 0xFFFF)


def x(xo, rs, ra=0, rb=0, rc=0):
    return (31 << 26) | (rs << 21) | (ra << 16) | (rb << 11) | (xo << 1) | rc


def spr(xo, reg, number):
    return (31 << 26) | (reg << 21) | ((number & 31) << 16) | ((number >> 5) << 11) | (xo << 1)


def address(reg=3, value=TARGET):
    return [d(15, reg, 0, value >> 16), d(24, reg, reg, value)]


def branch_events(result):
    return [event for event in result["events"] if event["kind"].startswith("branch_")]


class LocalTrackingTests(unittest.TestCase):
    def run_words(self, words, boundaries=(), **kwargs):
        return audit.analyze([(BASE, tuple(words))], boundaries, WATCH, **kwargs)

    def test_nonadjacent_lr_copy_barrier_and_masked_destination(self):
        words = address(value=TARGET + 3)
        words += [d(36, 4, 1, 16), d(32, 4, 1, 20), x(444, 3, 7, 3),
                  0x4C00012C, spr(467, 7, 8), 0x4E800020]
        result = self.run_words(words)
        event = branch_events(result)[0]
        self.assertEqual(event["target"], TARGET)
        self.assertEqual(event["origins"], [BASE, BASE + 4, BASE + 16, BASE + 24])
        self.assertEqual(len(result["watched_candidates"]), 2)

    def test_ctr_linking_branch_uses_old_target_then_clears(self):
        result = self.run_words(address(value=TARGET + 4) + [spr(467, 3, 9), 0x4E800421, 0x4E800420])
        events = branch_events(result)
        self.assertEqual(events[0]["target"], TARGET + 4)
        self.assertTrue(events[0]["link"])
        self.assertIsNone(events[1]["target"])

    def test_lr_to_gpr_to_ctr_and_physical_r0(self):
        words = address(0) + [spr(467, 0, 8), spr(339, 4, 8), d(14, 4, 4, 8), spr(467, 4, 9), 0x4E800420]
        self.assertEqual(branch_events(self.run_words(words))[0]["target"], TARGET + 8)

    def test_addi_r0_base_is_literal_zero_but_ori_reads_r0(self):
        state = audit.State()
        self.assertTrue(state.integer(d(14, 0, 0, 0x1200), BASE))
        self.assertTrue(state.integer(d(14, 3, 0, 7), BASE + 4))
        self.assertEqual(state.gpr[3].value, 7)
        self.assertTrue(state.integer(d(24, 0, 4, 0x34), BASE + 8))
        self.assertEqual(state.gpr[4].value, 0x1234)

    def test_signed_arithmetic_aliases_and_wraparound(self):
        state = audit.State()
        for i, word in enumerate([d(15, 3, 0, 0x9001), d(14, 3, 3, -0x1000), d(14, 4, 0, -1), x(266, 5, 3, 4), x(40, 6, 4, 3)]):
            self.assertTrue(state.integer(word, BASE + i * 4))
        self.assertEqual(state.gpr[3].value, 0x9000F000)
        self.assertEqual(state.gpr[5].value, 0x9000EFFF)
        self.assertEqual(state.gpr[6].value, 0x9000F001)
        state.integer(d(14, 4, 4, 1), BASE + 24)
        self.assertEqual(state.gpr[4].value, 0)

    def test_logical_immediates_and_register_destinations(self):
        state = audit.State()
        words = [d(14, 3, 0, 0x1234), d(25, 3, 4, 0x9000),
                 d(27, 4, 5, 0x1000), d(28, 5, 6, 0xFF),
                 d(29, 5, 7, 0xF000), d(26, 6, 8, 0xFF),
                 x(316, 7, 9, 5), x(28, 9, 10, 4)]
        for index, word in enumerate(words):
            self.assertTrue(state.integer(word, BASE + index * 4))
        self.assertEqual([state.gpr[n].value for n in range(4, 11)],
                         [0x90001234, 0x80001234, 0x34, 0x80000000, 0xCB, 0x1234, 0x1234])

    def test_multiply_and_float_load_preserve_only_appropriate_registers(self):
        state = audit.State()
        for index, word in enumerate([d(14, 3, 0, 5), d(7, 4, 3, -2),
                                      d(48, 4, 1, 0), d(49, 4, 3, 0)]):
            self.assertTrue(state.integer(word, BASE + index * 4))
        self.assertEqual(state.gpr[4].value, 0xFFFFFFF6)
        self.assertIsNone(state.gpr[3])

    def test_load_clobber_prevents_target(self):
        result = self.run_words(address() + [d(32, 3, 1, 4), spr(467, 3, 8), 0x4E800020])
        self.assertIsNone(branch_events(result)[0]["target"])

    def test_update_load_and_store_invalidate_base(self):
        for word in (d(33, 4, 3, 4), d(37, 4, 3, 4)):
            with self.subTest(word=word):
                result = self.run_words(address() + [word, spr(467, 3, 8), 0x4E800020])
                self.assertIsNone(branch_events(result)[0]["target"])

    def test_lmw_clobbers_entire_loaded_range(self):
        result = self.run_words(address(31) + [d(46, 30, 1, 0), spr(467, 31, 8), 0x4E800020])
        self.assertIsNone(branch_events(result)[0]["target"])

    def test_invalid_update_lmw_and_spr_forms_are_full_barriers(self):
        for word in (d(33, 3, 3, 4), d(37, 4, 0, 4), d(46, 30, 31, 0), spr(467, 3, 8) | 1, spr(467, 3, 1)):
            with self.subTest(word=word):
                result = self.run_words(address() + [spr(467, 3, 8), word, 0x4E800020])
                self.assertIsNone(branch_events(result)[0]["target"])
                self.assertEqual(result["counts"]["unsupported_barriers"], 1)

    def test_unsupported_instruction_clears_gpr_and_both_sprs(self):
        words = address() + [spr(467, 3, 8), spr(467, 3, 9), 0xFFFFFFFF,
                             spr(467, 3, 8), 0x4E800020, 0x4E800420]
        result = self.run_words(words)
        self.assertTrue(all(event["target"] is None for event in branch_events(result)))

    def test_calls_and_conditional_boundaries_never_carry_facts(self):
        for word in (0x48000005, 0x48000010, 0x40820004, 0x44000002, 0x4C000064):
            with self.subTest(word=word):
                result = self.run_words(address() + [spr(467, 3, 8), word, spr(467, 3, 9), 0x4E800420])
                self.assertIsNone(branch_events(result)[-1]["target"])

    def test_declared_and_direct_target_entries_reset_unknown(self):
        words = address() + [spr(467, 3, 8), 0x4E800020]
        self.assertIsNone(branch_events(self.run_words(words, [BASE + 4]))[0]["target"])
        # A separate later branch names the middle of the earlier construction.
        words += [0x4BFFFFF4]  # PC BASE+16 -> BASE+4.
        self.assertIsNone(branch_events(self.run_words(words))[0]["target"])

    def test_discovered_indirect_entry_discards_first_pass_claim(self):
        target = BASE + 4
        words = address(value=target) + [spr(467, 3, 9), 0x4E800420]
        result = self.run_words(words)
        self.assertEqual(result["passes"], 2)
        self.assertEqual(result["indirect_leaders_added"], 1)
        self.assertIsNone(branch_events(result)[0]["target"])

    def test_no_reachability_is_inferred_for_unreachable_raw_words(self):
        result = self.run_words([0x48000020] + address() + [spr(467, 3, 8), 0x4E800020])
        self.assertEqual(branch_events(result)[0]["target"], TARGET)

    def test_unknown_initial_lr_and_invalid_bcctr_remain_unknown(self):
        self.assertIsNone(branch_events(self.run_words([spr(339, 3, 8), spr(467, 3, 9), 0x4E800420]))[0]["target"])
        invalid = (19 << 26) | (16 << 21) | (528 << 1)  # CTR-decrement form.
        result = self.run_words(address() + [spr(467, 3, 9), invalid])
        self.assertIsNone(branch_events(result)[0]["target"])

    def test_reserved_indirect_branch_fields_remain_unknown(self):
        for spr_number, word in ((8, 0x4E800020), (9, 0x4E800420)):
            for reserved in (0x800, 0x1000, 0x8000):
                with self.subTest(spr=spr_number, reserved=reserved):
                    result = self.run_words(address() + [spr(467, 3, spr_number), word | reserved])
                    event = branch_events(result)[0]
                    self.assertFalse(event["supported_encoding"])
                    self.assertIsNone(event["target"])

    def test_unknown_writer_locations_do_not_create_values(self):
        words = [d(32, 3, 4, 0xE0), 0x4C00012C, spr(467, 3, 8), 0x4E800020]
        result = self.run_words(words)
        assignment = result["events"][0]
        event = branch_events(result)[0]
        self.assertIsNone(assignment["value"])
        self.assertEqual(assignment["source_gpr"], 3)
        self.assertEqual(assignment["last_source_writer"], BASE)
        self.assertEqual(event["last_spr_writer"], BASE + 8)
        self.assertIsNone(event["target"])
        cleared = self.run_words(words[:3] + [0xFFFFFFFF, 0x4E800020])
        self.assertIsNone(branch_events(cleared)[0]["last_spr_writer"])

    def test_provenance_exhaustion_becomes_unknown(self):
        result = self.run_words(address() + [spr(467, 3, 8), 0x4E800020], origin_limit=2)
        self.assertIsNone(branch_events(result)[0]["target"])

    def test_rotates_and_wrapping_mask_follow_msb_bit_numbering(self):
        self.assertEqual(audit.rotate(0x80000001, 1), 3)
        self.assertEqual(audit.ppc_mask(0, 31), 0xFFFFFFFF)
        self.assertEqual(audit.ppc_mask(28, 3), 0xF000000F)
        state = audit.State()
        for i, word in enumerate(address(value=0x81234567)):
            state.integer(word, BASE + i * 4)
        rlwinm = (21 << 26) | (3 << 21) | (4 << 16) | (4 << 11) | (28 << 6) | (3 << 1)
        state.integer(rlwinm, BASE + 8)
        self.assertEqual(state.gpr[4].value, 0x10000008)

    def test_dol_header_validation(self):
        with self.assertRaises(ValueError):
            audit.text_segments(bytes(20))
        header = bytearray(0x100)
        for off, value in ((0, 0x100), (0x48, BASE), (0x90, 8)):
            struct.pack_into(">I", header, off, value)
        with self.assertRaises(ValueError):
            audit.text_segments(bytes(header) + bytes(4))
        self.assertEqual(audit.text_segments(bytes(header) + bytes(8)), [(BASE, (0, 0))])

    def test_report_boundaries_require_all_three_preserved_extents(self):
        anchors = [(0x8042E8C4, 312), (0x8042E9FC, 20), (0x8042EA10, 196)]
        segments = [(anchors[0][0], (0,) * (528 // 4))]

        def report(rows):
            return {"units": [{"metadata": {"module_name": "psov3"}, "functions": [
                {"size": str(size), "metadata": {"virtual_address": str(start)}}
                for start, size in rows]}]}

        self.assertEqual(audit.report_boundaries(report(anchors), segments),
                         {start for start, _ in anchors})
        for rows in (anchors[:1] + anchors[2:],
                     [anchors[0], (anchors[1][0], 16), anchors[2]],
                     [anchors[0], (anchors[1][0], 0), anchors[2]]):
            with self.subTest(rows=rows), self.assertRaises(ValueError):
                audit.report_boundaries(report(rows), segments)


if __name__ == "__main__":
    unittest.main()
