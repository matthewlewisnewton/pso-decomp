import copy
import hashlib
import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

from tools.handoff_report import report

A, B, C = 'a' * 40, 'b' * 40, 'c' * 40


class HandoffReportTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / 'receipt').write_text('synthetic evidence')
        self.digest = hashlib.sha256(b'synthetic evidence').hexdigest()
        self.item = {'id': 'PR-1', 'owner': 'author', 'state': 'turn_complete',
                     'head': A, 'observed_head': A, 'evidence': [], 'requests': []}
        self.snapshot = {'version': 1, 'current_main': B, 'items': [self.item]}

    def evidence(self, stage, verdict='pass', head=A, base=B, path='receipt'):
        return {'stage': stage, 'verdict': verdict, 'head': head, 'base': base,
                'path': path, 'sha256': self.digest}

    def request(self, kind='review', head=A):
        return {'id': 'req-1', 'kind': kind, 'head': head,
                'state': 'pending', 'owner': 'reviewer'}

    def test_duplicate_pending_and_completed_turn(self):
        req = self.request()
        self.item['requests'] = [req, copy.deepcopy(req)]
        self.item['slot'] = {'state': 'held', 'owner': 'queue'}
        result = report(self.snapshot, self.root)
        self.assertEqual(len(result['pending_reviews']), 1)
        self.assertIn('completed turn has pending work', result['items'][0]['issues'])
        self.assertEqual(result['slot_releases'][0]['owner'], 'queue')
        self.item['requests'][1]['owner'] = 'other'
        with self.assertRaisesRegex(ValueError, 'conflicting duplicate'):
            report(self.snapshot, self.root)

    def test_main_advances_only_current_main_evidence(self):
        self.item['evidence'] = [self.evidence('source', base=C),
                                 self.evidence('development', base=C),
                                 self.evidence('graph', base=C),
                                 self.evidence('acceptance', base=C)]
        row = report(self.snapshot, self.root)['items'][0]
        self.assertEqual(row['stages']['development'], 'pass')
        self.assertEqual(row['stages']['graph'], 'stale_main')
        self.assertEqual(row['stages']['acceptance'], 'stale_main')
        self.assertTrue(row['ready_eligible'])

    def test_fail_unknown_and_missing_or_changed_receipts(self):
        self.item['evidence'] = [self.evidence('source', 'fail'),
                                 self.evidence('development', 'unknown'),
                                 self.evidence('graph', path='missing')]
        row = report(self.snapshot, self.root)['items'][0]
        self.assertEqual(row['stages']['source'], 'fail')
        self.assertEqual(row['stages']['development'], 'unknown')
        self.assertEqual(row['stages']['graph'], 'unverified')
        self.assertFalse(row['ready_eligible'])
        (self.root / 'receipt').write_text('changed')
        self.assertEqual(report(self.snapshot, self.root)['items'][0]['stages']['source'], 'unverified')

    def test_stale_heads_and_admission(self):
        self.item['evidence'] = [self.evidence('source', head=C)]
        self.item['requests'] = [self.request('admission', head=C)]
        result = report(self.snapshot, self.root)
        self.assertEqual(result['items'][0]['stages']['source'], 'stale_head')
        self.assertTrue(result['pending_admissions'][0]['stale_head'])
        self.item['observed_head'] = C
        self.item['evidence'] = [self.evidence('source')]
        self.assertEqual(report(self.snapshot, self.root)['items'][0]['stages']['source'], 'stale_head')

    def test_invalid_and_duplicate_identifiers_fail_closed(self):
        self.item['head'] = 'main'
        with self.assertRaises(ValueError):
            report(self.snapshot, self.root)
        self.item['head'] = A
        self.snapshot['items'].append(copy.deepcopy(self.item))
        with self.assertRaises(ValueError):
            report(self.snapshot, self.root)

    def test_cli_reads_without_modifying_snapshot_or_receipt(self):
        path = self.root / 'snapshot.json'
        path.write_text(json.dumps(self.snapshot))
        before = path.read_bytes()
        script = Path(__file__).resolve().parents[1] / 'handoff_report.py'
        run = subprocess.run([sys.executable, str(script), str(path)], capture_output=True, text=True)
        self.assertEqual(run.returncode, 0, run.stderr)
        self.assertEqual(json.loads(run.stdout)['items'][0]['id'], 'PR-1')
        self.assertEqual(path.read_bytes(), before)
        self.assertEqual((self.root / 'receipt').read_text(), 'synthetic evidence')


if __name__ == '__main__':
    unittest.main()
