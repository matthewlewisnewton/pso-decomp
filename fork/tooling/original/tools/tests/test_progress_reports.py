"""Offline progress publishing and report provenance regressions; no network/builds."""
import json
from pathlib import Path
import re
import tempfile
import unittest
from tools import ci_report as c
from tools import progress_map as p

ROOT = Path(__file__).resolve().parents[2]


def report():
    return {'measures': dict(total_code=150, matched_code=100, complete_code=100,
        total_data=30, matched_data=20, complete_data=20, total_functions=2,
        matched_functions=1, total_units=2, complete_units=1), 'units': [
        {'name': 'psov3/pso/quest/A.cpp', 'metadata': {'complete': True},
         'functions': [{'name': 'match</script>', 'size': 100, 'fuzzy_match_percent': 100,
                        'metadata': {'virtual_address': 0x80000000}}],
         'sections': [{'name': '.data', 'size': 20, 'fuzzy_match_percent': 100,
                       'metadata': {'virtual_address': 0x80400000}}]},
        {'name': 'psov3/pso/ui/B.cpp', 'metadata': {'complete': False},
         'functions': [{'name': 'fn_80000064', 'size': 50, 'fuzzy_match_percent': 80,
                        'metadata': {'virtual_address': 0x80000064}}],
         'sections': [{'name': '.bss', 'size': 10, 'fuzzy_match_percent': 50,
                       'metadata': {'virtual_address': 0x80500000}}]}]}


class ProgressReports(unittest.TestCase):
    def test_manual_fork_main_build_and_report_are_eligible(self):
        workflow = (ROOT / '.github/workflows/progress.yml').read_text()
        trigger = workflow.split('\non:\n', 1)[1].split('\npermissions:', 1)[0]
        self.assertEqual(trigger.strip(), 'workflow_dispatch:')
        ref = re.search(r"github\.ref == '([^']+)'", workflow).group(1)
        self.assertEqual(ref, 'refs/heads/main')
        run = dict(conclusion='success', path='.github/workflows/progress.yml',
                   event='workflow_dispatch', head_branch=ref.removeprefix('refs/heads/'),
                   head_sha='a' * 40)
        self.assertTrue(c.trusted(run, 'a' * 40, set()))
        for key, value in [('head_branch', 'master'), ('head_sha', 'b' * 40),
                           ('conclusion', 'failure'), ('path', '.github/workflows/other.yml')]:
            with self.subTest(key=key):
                self.assertFalse(c.trusted(dict(run, **{key: value}), 'a' * 40, set()))

    def test_only_successful_merged_pr_heads_are_trusted(self):
        run = dict(conclusion='success', path='.github/workflows/ci.yml',
                   event='pull_request', head_sha='b' * 40)
        self.assertTrue(c.trusted(run, 'a' * 40, {'b' * 40}))
        self.assertFalse(c.trusted(run, 'a' * 40, set()))
        self.assertFalse(c.trusted(dict(run, event='push'), 'a' * 40, {'b' * 40}))

    def test_treemap_preserves_code_data_and_bss_accounting(self):
        data = p.treemap_data(report())
        self.assertEqual(data['warnings'], [])
        for kind, total in [('code', 150), ('data', 30)]:
            self.assertEqual(sum(tile[6] for tile in data['layouts'][kind]['tiles']), total)
        altered = report(); altered['measures']['total_data'] = 31
        self.assertTrue(p.treemap_data(altered)['warnings'])

    def test_untrusted_names_cannot_close_script_data(self):
        html = p.render_treemap(report())
        self.assertNotIn('match</script>', html)
        self.assertIn('\\u003c/script>', html)

    def test_badges_keep_measured_and_linked_counts_distinct(self):
        badges = p.badges(report())
        self.assertEqual(badges['code']['message'], '66.67%')
        self.assertEqual(badges['functions']['message'], '50.00% (1 of 2)')
        self.assertEqual(badges['units-linked']['message'], '50.00% (1 of 2)')
        self.assertEqual(p.badges({'measures': {}})['code']['message'], '0.00%')

    def test_generated_files_and_retained_readme_api(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary); source = root / 'report.json'
            source.write_text(json.dumps(report()))
            readme = root / 'README.md'
            readme.write_text('before\n<!-- progress-table -->old<!-- /progress-table -->\nafter')
            self.assertTrue(p.update_readme(readme, source))
            self.assertFalse(p.update_readme(readme, source))
            self.assertTrue(readme.read_text().startswith('before\n'))
            self.assertTrue(readme.read_text().endswith('\nafter'))
            p.generate([source], root / 'site'); p.write_badges(root / 'badges', source)
            self.assertTrue((root / 'site/index.html').is_file())
            self.assertTrue((root / 'site/treemap.html').is_file())
            self.assertEqual(len(list((root / 'badges').glob('*.json'))), 6)


if __name__ == '__main__':
    unittest.main()
