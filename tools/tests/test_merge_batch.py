"""Local-only fixtures: no GitHub writes, original game files or compiler builds."""
import copy
import hashlib
import importlib.util
import json
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch

MODULE = Path(__file__).resolve().parents[1] / 'merge_batch.py'
spec = importlib.util.spec_from_file_location('merge_batch_under_test', MODULE)
m = importlib.util.module_from_spec(spec)
spec.loader.exec_module(m)


def git(path, *args):
    return subprocess.check_output(['git', '-C', str(path), *args], text=True, stderr=subprocess.DEVNULL).strip()


class LocalAPI:
    def __init__(self, remote, spec):
        self.remote, self.spec, self.overrides = remote, spec, {}

    def branch(self, name):
        return {'name': name, 'head': git(self.remote, 'rev-parse', 'refs/heads/' + name)}

    def prs(self, spec):
        result = {}
        target = self.branch('main')['head']
        for p in spec['prs']:
            merged = subprocess.run(['git', '-C', str(self.remote), 'merge-base', '--is-ancestor', p['head'], target], capture_output=True).returncode == 0
            result[p['number']] = dict(p, repository=m.REPOSITORY, state='closed' if merged else 'open',
                                      draft=False, checks={'source-checks': 'success'}, merged=merged,
                                      merge_commit=target if merged else None)
            result[p['number']].update(self.overrides)
        return result


class LocalQueue(m.Queue):
    # Deliberate test-only transport: production code has no local-remote override.
    def git(self, *args, **kw):
        if args == ('remote', 'get-url', 'origin'):
            return m.REMOTE
        return super().git(*args, **kw)


class QueueTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        self.remote = self.root / 'remote.git'
        self.author = self.root / 'author'
        subprocess.run(['git', 'init', '--bare', str(self.remote)], check=True, capture_output=True)
        subprocess.run(['git', 'init', str(self.author)], check=True, capture_output=True)
        git(self.author, 'config', 'user.name', 'Fixture')
        git(self.author, 'config', 'user.email', 'fixture@localhost')
        git(self.author, 'checkout', '-b', 'main')
        (self.author / 'file').write_text('base\n')
        git(self.author, 'add', 'file'); git(self.author, 'commit', '-m', 'base')
        target = git(self.author, 'rev-parse', 'HEAD')
        git(self.author, 'remote', 'add', 'origin', str(self.remote))
        git(self.author, 'push', 'origin', 'main')
        git(self.author, 'checkout', '-b', 'feature')
        (self.author / 'file').write_text('recovery\n')
        git(self.author, 'commit', '-am', 'change')
        head = git(self.author, 'rev-parse', 'HEAD')
        git(self.author, 'push', 'origin', 'feature')
        self.review = self.root / 'review.txt'; self.review.write_text('independent fixture review')
        self.batch = {'version': 1, 'repository': m.REPOSITORY, 'default_branch': 'main', 'target': target,
                      'policy': 'recovery', 'authorization': 'fixture', 'commit_epoch': 1793476000,
                      'prs': [{'number': 1, 'head': head, 'head_ref': 'feature', 'base_ref': 'main',
                               'base_sha': target, 'review_base': target, 'kind': 'recovery',
                               'required_checks': ['source-checks'], 'review': {
                                   'verdict': 'pass', 'independent': True, 'reviewer': 'fixture reviewer',
                                   'head': head, 'base': target, 'path': str(self.review), 'sha256': m.digest(self.review)}}]}
        self.state = self.root / 'state'; self.state.mkdir()
        self.api = LocalAPI(self.remote, self.batch)
        self.q = LocalQueue(self.batch, self.state, self.api)
        subprocess.run(['git', 'clone', str(self.remote), str(self.q.repo)], check=True, capture_output=True)
        self.result = {'version': 1, 'target': target, 'tree': head, 'checks': dict.fromkeys(m.CHECKS, True),
                       'losses': {'code': 0, 'data': 0, 'link': 0},
                       'delta': {'matched_code': 4, 'matched_data': 0, 'complete_code': 0, 'complete_data': 0},
                       'dol_sha1': '0d85744b51d7379efb025a943d0cd5aaae2191a3'}

    def tearDown(self):
        self.temp.cleanup()

    def rejects(self, code, fn):
        with self.assertRaises(m.Rejected) as caught:
            fn()
        self.assertEqual(caught.exception.code, code)

    def test_wrong_repository(self):
        self.batch['repository'] = 'zeroz41/pso-decomp'
        self.rejects('wrong_repository', lambda: m.validate_spec(self.batch))

    def test_missing_review(self):
        self.batch['prs'][0]['review']['independent'] = False
        self.rejects('missing_review', lambda: m.validate_spec(self.batch))

    def test_changed_review_evidence(self):
        self.review.write_text('changed')
        self.rejects('stale_review', self.q.live_guard)

    def test_stale_head_and_base(self):
        for field in ('head', 'base_sha', 'base_ref', 'head_ref'):
            with self.subTest(field=field):
                self.api.overrides = {field: 'different'}
                self.rejects('stale_pr', self.q.live_guard)

    def test_missing_hosted_check(self):
        self.api.overrides = {'checks': {'source-checks': 'queued'}}
        self.rejects('missing_checks', self.q.live_guard)

    def test_failed_build_and_missing_validation_check(self):
        for key in m.CHECKS:
            r = copy.deepcopy(self.result); r['checks'][key] = False
            self.rejects('failed_checks', lambda: m.check_validation(self.batch, r, r['tree']))

    def test_code_data_and_link_loss(self):
        for key in ('code', 'data', 'link'):
            r = copy.deepcopy(self.result); r['losses'][key] = 1
            self.rejects('coverage_loss', lambda: m.check_validation(self.batch, r, r['tree']))

    def test_zero_gain_prerequisite_batch_rejected(self):
        self.result['delta']['matched_code'] = 0
        self.rejects('zero_gain', lambda: m.check_validation(self.batch, self.result, self.result['tree']))

    def test_validation_wrong_tree(self):
        self.rejects('wrong_validation_tree', lambda: m.check_validation(self.batch, self.result, 'f' * 40))

    def test_plan_preserves_remote_and_deterministic_lineage(self):
        before = self.api.branch('main')['head']
        first = self.q.execute('plan')['candidate']
        second = self.q.execute('plan')['candidate']
        self.assertEqual(first, second)
        self.assertEqual(self.api.branch('main')['head'], before)
        self.assertEqual(git(self.q.repo, 'show', '-s', '--format=%P', first).split(),
                         [before, self.batch['prs'][0]['head']])

    def test_conflict_rejects_without_publication(self):
        git(self.author, 'checkout', 'main')
        (self.author / 'file').write_text('conflicting base\n')
        git(self.author, 'commit', '-am', 'conflict'); git(self.author, 'push', 'origin', 'main')
        self.batch['target'] = git(self.author, 'rev-parse', 'HEAD')
        self.batch['prs'][0]['base_sha'] = self.batch['target']
        self.rejects('conflict', self.q.construct)
        self.assertEqual(self.api.branch('main')['head'], self.batch['target'])

    def test_atomic_publication_and_idempotent_recovery(self):
        self.q.execute('plan')
        self.q.publish()
        self.assertEqual(self.q.record['state'], 'published')
        self.assertEqual(self.api.branch('main')['head'], self.q.record['candidate'])
        fresh = LocalQueue(self.batch, self.state, self.api)
        self.assertEqual(fresh.execute('execute')['state'], 'published')

    def test_push_failure_changes_no_remote_prefix(self):
        self.q.execute('plan')
        hook = self.remote / 'hooks/pre-receive'
        hook.write_text('#!/bin/sh\nexit 1\n'); hook.chmod(0o755)
        self.rejects('publication_rejected', self.q.publish)
        self.assertEqual(self.api.branch('main')['head'], self.batch['target'])
        self.assertEqual(self.q.record['state'], 'not_published')

    def test_lost_response_after_push_is_recovered(self):
        self.q.execute('plan')
        # Simulate interruption exactly after remote success but before receipt.
        self.q.write(state='publishing')
        git(self.q.repo, 'push', '--atomic', 'origin', self.q.record['candidate'] + ':refs/heads/main')
        fresh = LocalQueue(self.batch, self.state, self.api)
        self.assertEqual(fresh.execute('execute')['state'], 'published')

    def test_stale_target_before_mutation(self):
        self.q.execute('plan')
        git(self.author, 'checkout', 'main')
        (self.author / 'other').write_text('external update')
        git(self.author, 'add', 'other'); git(self.author, 'commit', '-m', 'external'); git(self.author, 'push', 'origin', 'main')
        self.rejects('stale_target', self.q.publish)

    def test_changed_manifest_cannot_reuse_state(self):
        self.q.execute('plan')
        self.batch['commit_epoch'] += 1
        self.rejects('different_batch', lambda: LocalQueue(self.batch, self.state, self.api))

    def test_failed_external_validator_never_publishes(self):
        self.q.execute('plan')
        validator = self.root / 'fail.py'; validator.write_text('raise SystemExit(2)\n')
        environment = self.root / 'environment.json'; environment.write_text('{}')
        self.batch['environment_sha256'] = m.digest(environment)
        self.rejects('failed_build_or_checks', lambda: self.q.verify(validator, m.digest(validator), environment))
        self.assertEqual(self.api.branch('main')['head'], self.batch['target'])

    def add_second_pr(self):
        git(self.author, 'checkout', '-b', 'second')
        (self.author / 'second').write_text('second recovery')
        git(self.author, 'add', 'second'); git(self.author, 'commit', '-m', 'second')
        git(self.author, 'push', 'origin', 'second')
        p = copy.deepcopy(self.batch['prs'][0])
        p.update(number=2, head=git(self.author, 'rev-parse', 'HEAD'), head_ref='second',
                 base_ref='feature', base_sha=self.batch['prs'][0]['head'],
                 review_base=self.batch['prs'][0]['head'])
        p['review'].update(head=p['head'], base=p['review_base'])
        self.batch['prs'].append(p)

    def test_two_pr_batch_has_no_partial_publication_on_rejection(self):
        self.add_second_pr()
        self.q.execute('plan')
        self.assertEqual(len(self.q.record['commits']), 2)
        hook = self.remote / 'hooks/pre-receive'
        hook.write_text('#!/bin/sh\nexit 1\n'); hook.chmod(0o755)
        self.rejects('publication_rejected', self.q.publish)
        self.assertEqual(self.api.branch('main')['head'], self.batch['target'])
        self.assertTrue(all(not p['merged'] for p in self.api.prs(self.batch).values()))

    def test_two_pr_publication_preserves_both_lineages(self):
        self.add_second_pr()
        self.q.execute('plan'); self.q.publish()
        self.assertTrue(all(p['merged'] for p in self.api.prs(self.batch).values()))
        rows = self.q.record['commits']
        self.assertEqual(git(self.q.repo, 'show', '-s', '--format=%P', rows[1]['commit']).split(),
                         [rows[0]['commit'], self.batch['prs'][1]['head']])

    def test_wrong_dependency_order_rejected(self):
        self.add_second_pr()
        self.batch['prs'].reverse()
        self.rejects('command_failed', self.q.construct)

    def test_successful_synthetic_dry_run_does_not_publish(self):
        validator = self.root / 'fixture_validator.py'
        validator.write_text('import json,sys,pathlib\nr=json.loads(pathlib.Path(sys.argv[1]).read_text())\n'
                             + 'v=' + repr(self.result) + '\n'
                             + "v.update(target=r['target'],tree=r['tree'])\n"
                             + "pathlib.Path(r['output']).write_text(json.dumps(v))\n")
        environment = self.root / 'environment.json'; environment.write_text('{}')
        self.batch['environment_sha256'] = m.digest(environment)
        r = self.q.execute('dry-run', validator, m.digest(validator), environment)
        self.assertEqual(r['state'], 'dry_run_pass')
        self.assertEqual(self.api.branch('main')['head'], self.batch['target'])

    def test_nonfinite_delta_rejected(self):
        self.result['delta']['matched_code'] = float('inf')
        self.rejects('coverage_loss', lambda: m.check_validation(self.batch, self.result, self.result['tree']))

    def test_bundled_maintenance_validator_supports_project_imports(self):
        (self.author / 'configure.py').write_text('')
        (self.author / 'tools/tests').mkdir(parents=True)
        (self.author / 'tools/__init__.py').write_text('VALUE = 7')
        (self.author / 'tools/tests/test_fixture.py').write_text(
            'import unittest,tools\nclass Test(unittest.TestCase):\n'
            ' def test_import(self): self.assertEqual(tools.VALUE,7)\n')
        git(self.author, 'add', 'configure.py', 'tools')
        git(self.author, 'commit', '-m', 'fixture source checks')
        head = git(self.author, 'rev-parse', 'HEAD')
        environment = self.root / 'environment.json'; environment.write_text('{}')
        request = self.root / 'request.json'
        output = self.root / 'result.json'
        request.write_text(json.dumps({'checkout': str(self.author), 'state': str(self.state),
            'target': head, 'candidate': head, 'tree': git(self.author, 'rev-parse', 'HEAD^{tree}'),
            'environment': str(environment), 'policy': 'maintenance', 'output': str(output)}))
        subprocess.run([m.sys.executable, '-I', str(MODULE.with_name('merge_batch_validate.py')), str(request)],
                       check=True, capture_output=True)
        self.assertEqual(json.loads(output.read_text())['checks'], {'source': True})

    def test_dirty_state_checkout_is_preserved(self):
        self.q.execute('plan')
        (self.q.repo / 'file').write_text('preserve local work')
        self.rejects('dirty_state_checkout', self.q.construct)
        self.assertEqual((self.q.repo / 'file').read_text(), 'preserve local work')


if __name__ == '__main__':
    unittest.main()
