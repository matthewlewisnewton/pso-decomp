"""Original-free controls for the deliberately bounded syntactic audit."""

import unittest

from tools import audit_loader_phase_requests as audit


BASE = 0x80001000


def branch(pc, target):
    return 0x48000001 | ((target - pc) & 0x03FFFFFC)


def store(op, address, ra=13):
    return (op << 26) | (3 << 21) | (ra << 16) | ((address - audit.SDA) & 0xFFFF)


class PhaseRequestAuditTests(unittest.TestCase):
    def test_adjacent_literal_is_a_pattern_not_an_all_paths_value(self):
        words = [0x38600013, branch(BASE + 4, audit.SETTER), 0x38600000,
                 branch(BASE + 12, audit.SETTER), branch(BASE + 16, BASE + 40)]
        requests, stores = audit.scan_patterns([(BASE, words)])
        self.assertEqual([r["preceding_li_r3"] for r in requests], [19, 0])
        self.assertTrue(all(r["link"] for r in requests))
        self.assertEqual(stores, [])

    def test_nonadjacent_literal_is_left_unknown(self):
        words = [0x38600013, 0x60000000, branch(BASE + 8, audit.SETTER)]
        requests, _ = audit.scan_patterns([(BASE, words)])
        self.assertIsNone(requests[0]["preceding_li_r3"])

    def test_sda_partial_store_overlap_and_other_base_are_distinct(self):
        words = [store(36, audit.INSTANCE), store(38, audit.INSTANCE + 3),
                 store(44, audit.INSTANCE - 1), store(38, audit.INSTANCE + 4),
                 store(36, audit.INSTANCE, ra=12)]
        _, stores = audit.scan_patterns([(BASE, words)])
        self.assertEqual([row["pc"] for row in stores], [BASE, BASE + 4, BASE + 8])
        self.assertEqual([row["width"] for row in stores], [4, 1, 2])

    def test_conflicting_extents_are_unresolved(self):
        result = audit.declarations(
            "a = .text:0x80001000; // type:function size:0x10\n"
            "alias = .text:0x80001000; // type:function size:0x10\n"
            "b = .text:0x80002000; // type:function size:0x10\n"
            "conflict = .text:0x80002000; // type:function size:0x20\n")
        self.assertEqual(result[BASE]["names"], ["a", "alias"])
        self.assertNotIn(0x80002000, result)

    def test_internal_branches_and_indirect_encodings_do_not_invent_edges(self):
        targets, indirect = audit.edges([branch(BASE, BASE + 4), branch(BASE + 4, BASE + 0x100),
                                         0x4E800020, 0x4E800421], BASE, 16)
        self.assertEqual(targets, {BASE + 0x100})
        self.assertEqual(indirect, [BASE + 8, BASE + 12])

    def test_depth_limit_cycles_and_reached_frontier(self):
        graph = {1:{2}, 2:{1, 3}, 3:set(), 4:{3}}
        seen, paths, frontier = audit.bounded_walk([1], graph.__getitem__, {3}, 1)
        self.assertEqual(seen, {1, 2})
        self.assertEqual(paths, {})
        self.assertEqual(frontier, {3})
        seen, paths, frontier = audit.bounded_walk([1, 4], graph.__getitem__, {3}, 2)
        self.assertEqual(paths[3], [4, 3])
        self.assertEqual(frontier, set())


if __name__ == "__main__":
    unittest.main()
