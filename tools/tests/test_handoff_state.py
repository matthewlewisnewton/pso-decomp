import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

from tools.handoff_state import PinnedReceipts, Store, STAGES

A, B, C = 'a' * 40, 'b' * 40, 'c' * 40


class StateTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.path = self.root / 'state.sqlite'
        self.store = Store(self.path)
        self.addCleanup(lambda: self.store.close())
        self.owners = dict.fromkeys(STAGES, 'sole-queue')
        self.owners['source'] = 'source-reviewer'
        self.observe()

    def observe(self, head=A, main=B, revision=1):
        return self.store.observe('one', head, main, revision, self.owners, 100)

    def receipt(self, stage, verdict='pass', head=A, base=B, rid=None, completed=100):
        rid = rid or stage
        body = dict(request_id=rid, item='one', stage=stage, verdict=verdict,
                    head=head, base=base, producer='worker', reviewer='independent',
                    completed_ms=completed)
        path = self.root / (rid + '.json')
        path.write_text(json.dumps(body))
        digest = hashlib.sha256(path.read_bytes()).hexdigest()
        return PinnedReceipts({rid: digest}), rid, path

    def ingest(self, stage, **kw):
        return self.store.ingest(*self.receipt(stage, **kw), now_ms=110)

    def test_sequential_and_replay_have_one_logical_action(self):
        receipt = self.receipt('source')
        first = self.store.ingest(*receipt, now_ms=110)
        again = self.store.ingest(*receipt, now_ms=120)
        self.assertEqual(first, again)
        self.assertEqual(first['next_action'], 'request_development_validation')
        self.assertEqual(len(self.store.events('one')), 2)
        self.assertFalse(first['dispatch_enabled'])

    def test_out_of_order_does_not_repeat_or_advance_past_missing_gate(self):
        initial = self.store.current('one')['event_id']
        row = self.ingest('development')
        self.assertEqual(row['event_id'], initial)
        self.assertEqual(row['stages']['development'], 'pass')
        self.assertEqual(row['next_action'], 'request_source_review')
        self.assertEqual(self.ingest('source')['next_action'], 'request_graph_review')

    def test_main_advance_retains_development_and_invalidates_acceptance(self):
        for stage in ('source', 'development', 'graph', 'acceptance'):
            self.ingest(stage)
        row = self.observe(main=C, revision=2)
        self.assertEqual(row['stages']['development'], 'pass')
        self.assertEqual(row['stages']['acceptance'], 'missing')
        self.assertEqual(row['next_action'], 'request_graph_review')
        old_event = row['event_id']
        row = self.observe(head=C, main=C, revision=3)
        self.assertEqual(row['next_action'], 'request_source_review')
        self.assertNotEqual(row['event_id'], old_event)
        with self.assertRaises(ValueError):
            self.observe(revision=1)

    def test_hold_fail_unknown_never_become_pass_or_auto_retry(self):
        for verdict in ('hold', 'fail', 'unknown'):
            row = self.ingest('source', verdict=verdict, rid=verdict)
            self.assertIsNone(row['next_action'])
            self.assertIn(verdict, row['blocked_reason'])
        row = self.ingest('source', rid='later-pass')
        self.assertIsNone(row['next_action'])

    def test_denial_and_uncertain_push_survive_inventory_refresh(self):
        self.ingest('acceptance', verdict='denied')
        self.ingest('publication', verdict='uncertain')
        row = self.observe(head=C, main=C, revision=2)
        self.assertIsNone(row['next_action'])
        self.assertIn('denied', row['blocked_reason'])
        self.assertIn('uncertain', row['blocked_reason'])

    def test_unpinned_changed_conflicting_and_self_reviewed_receipts_rejected(self):
        verifier, rid, path = self.receipt('source')
        self.store.ingest(verifier, rid, path, 110)
        with self.assertRaises(ValueError):
            self.store.ingest(*self.receipt('development', rid='source'), now_ms=110)
        path.write_text('{}')
        with self.assertRaises(ValueError):
            self.store.ingest(verifier, rid, path, 110)
        verifier, rid, path = self.receipt('source', rid='self-review')
        data = json.loads(path.read_text())
        data['reviewer'] = data['producer']
        path.write_text(json.dumps(data))
        verifier = PinnedReceipts({rid: hashlib.sha256(path.read_bytes()).hexdigest()})
        with self.assertRaises(ValueError):
            self.store.ingest(verifier, rid, path, 110)
        with self.assertRaises(TypeError):
            self.store.ingest(object(), rid, path, 110)

    def test_process_crashes_rollback_both_rows_and_postcommit_replay_is_safe(self):
        verifier, rid, path = self.receipt('source')
        digest = hashlib.sha256(path.read_bytes()).hexdigest()
        for point in ('after_receipt', 'after_event', 'after_commit'):
            script = '''
import os, sys
from tools.handoff_state import Store, PinnedReceipts
s = Store(sys.argv[1])
def crash(point):
    if point == sys.argv[4]: os._exit(17)
s.ingest(PinnedReceipts({'source': sys.argv[3]}), 'source', sys.argv[2], 110, crash)
'''
            run = subprocess.run([sys.executable, '-c', script, str(self.path), str(path), digest, point])
            self.assertEqual(run.returncode, 17)
            count = self.store.db.execute('SELECT COUNT(*) FROM receipts').fetchone()[0]
            self.assertEqual(count, 1 if point == 'after_commit' else 0)
        self.store.ingest(verifier, rid, path, 120)
        self.assertEqual(len(self.store.events('one')), 2)
        self.assertEqual(self.store.current('one')['next_action'], 'request_development_validation')

    def test_fixture_relay_count_and_receipt_to_action_latency(self):
        # Baseline fixture: parent reads each receipt then relays its next action.
        baseline_relays = 4
        completion_times = []
        for n, stage in enumerate(('source', 'development', 'graph', 'acceptance')):
            completed = 100 + n * 20
            receipt = self.receipt(stage, completed=completed)
            row = self.store.ingest(*receipt, now_ms=completed + 7)
            self.store.ingest(*receipt, now_ms=completed + 9)  # duplicate delivery
            completion_times.append(completed)
        events = self.store.events('one')[1:]
        self.assertEqual(len(events), baseline_relays)
        self.assertEqual([e['created_ms'] - t for e, t in zip(events, completion_times)], [7] * 4)
        # Prospective adapter can consume these four IDs with no parent relay;
        # actual dispatch is disabled in this PR, so no live savings are claimed.
        self.assertTrue(all(not e['event']['dispatch_enabled'] for e in events))
        self.assertEqual(row['next_action'], 'request_publication_reconciliation')
        self.assertFalse(any('build' in e['event']['next_action'] for e in events))


if __name__ == '__main__':
    unittest.main()
