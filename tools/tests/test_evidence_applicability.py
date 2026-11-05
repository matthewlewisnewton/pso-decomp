import hashlib
import importlib.util
import json
from pathlib import Path
import tempfile
import unittest

spec = importlib.util.spec_from_file_location('applicability', Path(__file__).parents[1] / 'evidence_applicability.py')
mod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(mod)


class ComparisonTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.base = Path(self.tmp.name)
        self.paths = []
        for side in ('old', 'new'):
            root = self.base / side
            root.mkdir()
            def entry(name, value=None):
                data = (value or name).encode()
                (root / name).write_bytes(data)
                return {'path': name, 'sha256': hashlib.sha256(data).hexdigest()}
            proofs = {k: entry(k) for k in ('graph', 'inventory_review')}
            if side == 'old':
                proofs['development_receipt'] = entry('receipt')
            doc = {'version': 1, 'revision': ('a' if side == 'old' else 'b') * 40,
                   'root': str(root), 'proofs': proofs,
                   'global_inputs': {k: {k: entry(k)} for k in mod.KINDS},
                   'consumers': {'one': {'inputs': {'source': entry('one.c'), 'header': entry('header.h')}},
                                 'two': {'inputs': {'source': entry('two.c'), 'helper': entry('helper.py')}}}}
            if side == 'old':
                for name in doc['consumers']:
                    doc['consumers'][name]['outputs'] = {'object': entry(name + '.o')}
            path = self.base / (side + '.json')
            path.write_text(json.dumps(doc))
            self.paths.append(path)

    def run_compare(self):
        return mod.compare(*self.paths)

    def change(self, side, group, name, key, value):
        path = self.paths[side]
        doc = json.loads(path.read_text())
        entry = doc[group][name][key] if group == 'global_inputs' else doc[group][name]['inputs'][key]
        data = value.encode()
        (Path(doc['root']) / entry['path']).write_bytes(data)
        entry['sha256'] = hashlib.sha256(data).hexdigest()
        path.write_text(json.dumps(doc))

    def test_unrelated_docs_and_revision_do_not_change_inventory(self):
        (self.base / 'new' / 'README.md').write_text('changed')
        r = self.run_compare()
        self.assertEqual(r['status'], 'compared')
        self.assertEqual(set(r['potentially_reusable_baseline_outputs']), {'one', 'two'})
        self.assertEqual(r['acceptance_freshness'], 'not established')
        self.assertEqual(r['authorization'], 'none')

    def test_header_and_imported_helper_affect_consumers(self):
        self.change(1, 'consumers', 'one', 'header', 'changed header')
        self.change(1, 'consumers', 'two', 'helper', 'changed helper')
        self.assertEqual(set(self.run_compare()['affected_consumers']), {'one', 'two'})

    def test_compiler_flags_and_generated_inputs_affect_all(self):
        for category in ('compiler', 'generated', 'config', 'tool', 'source'):
            with self.subTest(category=category):
                self.change(1, 'global_inputs', category, category, 'changed ' + category)
                r = self.run_compare()
                self.assertIn(category, r['global_changes'])
                self.assertEqual(set(r['affected_consumers']), {'one', 'two'})

    def test_identical_bytes_renamed_consumer_inputs_are_affected(self):
        for consumer, key in (('one', 'source'), ('one', 'header'), ('two', 'helper')):
            with self.subTest(consumer=consumer, key=key):
                doc = json.loads(self.paths[1].read_text())
                item = doc['consumers'][consumer]['inputs'][key]
                root = Path(doc['root'])
                renamed = item['path'] + '.renamed'
                (root / item['path']).rename(root / renamed)
                item['path'] = renamed
                self.paths[1].write_text(json.dumps(doc))
                result = self.run_compare()
                self.assertIn(consumer, result['affected_consumers'])
                self.assertNotIn(consumer, result['potentially_reusable_baseline_outputs'])

    def test_identical_bytes_renamed_global_inputs_affect_all(self):
        for category in ('source', 'tool', 'compiler', 'config', 'generated'):
            with self.subTest(category=category):
                doc = json.loads(self.paths[1].read_text())
                item = doc['global_inputs'][category][category]
                root = Path(doc['root'])
                renamed = item['path'] + '.renamed'
                (root / item['path']).rename(root / renamed)
                item['path'] = renamed
                self.paths[1].write_text(json.dumps(doc))
                result = self.run_compare()
                self.assertIn(category, result['global_changes'])
                self.assertEqual(set(result['affected_consumers']), {'one', 'two'})

    def test_changed_symlink_target_with_same_bytes_is_affected(self):
        for side in (0, 1):
            doc = json.loads(self.paths[side].read_text())
            root = Path(doc['root'])
            original = root / 'header.h'
            target = root / ('old-target' if side == 0 else 'new-target')
            original.rename(target)
            original.symlink_to(target.name)
        result = self.run_compare()
        self.assertIn('one', result['affected_consumers'])
        self.assertNotIn('one', result['potentially_reusable_baseline_outputs'])

    def test_stale_output_fails_closed(self):
        (self.base / 'old' / 'one.o').write_text('stale')
        r = self.run_compare()
        self.assertEqual(r['status'], 'incomplete')
        self.assertFalse(r['potentially_reusable_baseline_outputs'])

    def test_missing_proof_fails_closed(self):
        (self.base / 'old' / 'receipt').unlink()
        r = self.run_compare()
        self.assertEqual(r['status'], 'incomplete')
        self.assertFalse(r['potentially_reusable_baseline_outputs'])

    def test_uninventoried_consumer_fails_closed_for_that_context(self):
        doc = json.loads(self.paths[1].read_text())
        del doc['consumers']['two']
        self.paths[1].write_text(json.dumps(doc))
        r = self.run_compare()
        self.assertIn('two', r['affected_consumers'])
        self.assertNotIn('two', r['potentially_reusable_baseline_outputs'])

    def test_duplicate_json_rejected(self):
        self.paths[0].write_text('{"version":1,"version":1}')
        self.assertEqual(self.run_compare()['status'], 'incomplete')


if __name__ == '__main__':
    unittest.main()
