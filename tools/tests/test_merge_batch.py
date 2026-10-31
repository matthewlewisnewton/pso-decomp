"""Local-only fixtures: no GitHub writes, original game files or compiler builds."""
import copy
import contextlib
import io
import os
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
    def publication_destination(self):
        with patch.object(m, 'REMOTE', str(self.api.remote)):
            return super().publication_destination()

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

    def test_source_maintenance_zero_gain_and_guard_evidence(self):
        self.batch['policy'] = 'source-maintenance'
        self.batch['prs'][0]['kind'] = 'source-maintenance'
        m.validate_spec(self.batch)
        self.result['delta'] = dict.fromkeys(('matched_code', 'matched_data', 'complete_code', 'complete_data', 'matched_functions', 'total_functions', 'total_code', 'total_data'), 0)
        ranges = ('code_coverage', 'code_exact', 'code_linked', 'data_coverage', 'data_exact', 'data_linked', 'function_coverage', 'function_exact', 'function_linked')
        self.result['zero_lost_address_ranges'] = dict.fromkeys(ranges, 0)
        self.result['raw_report_sha256'] = {'baseline': 'a' * 64, 'candidate': 'b' * 64}
        m.check_validation(self.batch, self.result, self.result['tree'])
        for field in ('zero_lost_address_ranges', 'raw_report_sha256'):
            bad = copy.deepcopy(self.result); del bad[field]
            self.rejects('missing_extent_gate' if field.startswith('zero') else 'missing_raw_reports', lambda: m.check_validation(self.batch, bad, bad['tree']))
        bad = copy.deepcopy(self.result); bad['zero_lost_address_ranges']['code_exact'] = False
        self.rejects('missing_extent_gate', lambda: m.check_validation(self.batch, bad, bad['tree']))
        bad = copy.deepcopy(self.result); bad['delta']['matched_functions'] = -1
        self.rejects('coverage_loss', lambda: m.check_validation(self.batch, bad, bad['tree']))

    def test_source_maintenance_scope_and_mode(self):
        for path in ('src/game/foo.cpp', 'include/game/foo.h'):
            self.assertTrue(m.source_maintenance_path(path))
        for path in ('tools/check_pr.py', 'configure.py', 'src/../tools/check.cpp', 'src/build.ninja', 'docs/foo.cpp', 'src/foo.cpp\n', ''):
            self.assertFalse(m.source_maintenance_path(path), path)
        self.batch['policy'] = 'source-maintenance'
        self.rejects('invalid_policy', lambda: m.validate_spec(self.batch))
        self.batch['prs'][0]['kind'] = 'source-maintenance'
        self.batch['policy'] = 'recovery'
        self.rejects('invalid_policy', lambda: m.validate_spec(self.batch))

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

    def test_omitted_review_base_cannot_import_unreviewed_commit(self):
        hidden = self.batch['prs'][0]['head']
        (self.author / 'selected').write_text('selected delta')
        git(self.author, 'add', 'selected'); git(self.author, 'commit', '-m', 'selected')
        git(self.author, 'push', 'origin', 'feature')
        p = self.batch['prs'][0]
        p.update(head=git(self.author, 'rev-parse', 'HEAD'), review_base=hidden)
        p['review'].update(head=p['head'], base=hidden)
        self.rejects('unreviewed_prerequisite', lambda: self.q.execute('plan'))
        self.assertEqual(self.api.branch('main')['head'], self.batch['target'])

    def wrong_remote(self):
        wrong = self.root / 'wrong.git'
        subprocess.run(['git', 'clone', '--bare', str(self.remote), str(wrong)], check=True, capture_output=True)
        return wrong

    def test_actual_pushurl_is_checked_not_fetch_url(self):
        self.q.execute('plan')
        wrong = self.wrong_remote()
        git(self.q.repo, 'config', 'remote.origin.pushurl', str(wrong))
        self.rejects('unsafe_publication_destination', self.q.publish)
        self.assertEqual(git(wrong, 'rev-parse', 'main'), self.batch['target'])
        self.assertEqual(self.api.branch('main')['head'], self.batch['target'])

    def test_additional_push_destination_rejected(self):
        self.q.execute('plan')
        wrong = self.wrong_remote()
        git(self.q.repo, 'config', '--add', 'remote.origin.pushurl', str(self.remote))
        git(self.q.repo, 'config', '--add', 'remote.origin.pushurl', str(wrong))
        self.rejects('unsafe_publication_destination', self.q.publish)
        self.assertEqual(git(wrong, 'rev-parse', 'main'), self.batch['target'])

    def test_effective_rewritten_push_destination_rejected(self):
        self.q.execute('plan')
        wrong = self.wrong_remote()
        git(self.q.repo, 'config', 'url.' + str(wrong) + '.pushInsteadOf', str(self.remote))
        self.assertEqual(git(self.q.repo, 'remote', 'get-url', '--push', 'origin'), str(wrong))
        self.rejects('unsafe_publication_destination', self.q.publish)
        self.assertEqual(git(wrong, 'rev-parse', 'main'), self.batch['target'])

    def test_exact_old_lease_rejects_selected_ancestor_race(self):
        self.q.execute('plan')
        original = self.q.live_guard
        def guard_then_race():
            original()
            git(self.author, 'push', 'origin', self.batch['prs'][0]['head'] + ':refs/heads/main')
        self.q.live_guard = guard_then_race
        self.rejects('publication_diverged', self.q.publish)
        self.assertEqual(self.api.branch('main')['head'], self.batch['prs'][0]['head'])
        self.assertNotEqual(self.api.branch('main')['head'], self.q.record['candidate'])
        self.assertNotEqual(self.q.record['push_returncode'], 0)

    def invoke_main_publication(self):
        batch = self.root / 'batch.json'; batch.write_text(json.dumps(self.batch))
        original_open = open
        def private_lock(path, *args, **kwargs):
            if str(path) == '/tmp/pso-mechanical-merge-queue.lock':
                path = self.root / 'private.lock'
            return original_open(path, *args, **kwargs)
        out = io.StringIO()
        with patch.object(m, 'Queue', return_value=self.q), \
             patch.object(self.q, 'execute', side_effect=lambda *a: self.q.publish()), \
             patch('builtins.open', private_lock), contextlib.redirect_stdout(out):
            code = m.main(['execute', '--batch', str(batch), '--state', str(self.state)])
        return code, json.loads(out.getvalue())

    def test_postpush_api_outage_reports_uncertain_not_rejected(self):
        self.q.execute('plan')
        with patch.object(self.q, 'recover_publication', side_effect=m.Rejected('command_failed', 'API unavailable')):
            code, output = self.invoke_main_publication()
        self.assertEqual(code, 1)
        self.assertEqual(output['state'], 'publication_uncertain')
        self.assertEqual(output['candidate'], self.api.branch('main')['head'])
        self.assertIn('Rerun', output['recovery'])
        self.assertEqual(json.loads(self.q.journal.read_text())['state'], 'publication_uncertain')
        self.assertTrue(self.q.recover_publication())

    def test_proven_publication_is_durable_before_metadata_failure(self):
        self.q.execute('plan')
        original = self.api.prs
        calls = []
        def metadata_failure(spec):
            calls.append(1)
            if len(calls) > 1:
                raise m.Rejected('command_failed', 'Metadata unavailable')
            return original(spec)
        with patch.object(self.api, 'prs', side_effect=metadata_failure):
            code, output = self.invoke_main_publication()
        self.assertEqual(code, 1)
        self.assertEqual(output['state'], 'published_unverified')
        self.assertEqual(output['published_commit'], self.api.branch('main')['head'])
        self.assertEqual(json.loads(self.q.journal.read_text())['published_commit'], output['published_commit'])
        self.assertTrue(self.q.recover_publication())

    def test_candidate_root_cannot_shadow_unittest(self):
        (self.author / 'configure.py').write_text('')
        (self.author / 'tools/tests').mkdir(parents=True)
        (self.author / 'tools/__init__.py').write_text('')
        (self.author / 'tools/tests/test_fails.py').write_text(
            'import unittest\nclass T(unittest.TestCase):\n def test_fails(self): self.fail("must run")\n')
        git(self.author, 'add', 'configure.py', 'tools'); git(self.author, 'commit', '-m', 'trusted test')
        target = git(self.author, 'rev-parse', 'HEAD')
        (self.author / 'unittest.py').write_text('from pathlib import Path\nPath("shadow-ran").touch()\n')
        git(self.author, 'add', 'unittest.py'); git(self.author, 'commit', '-m', 'shadow')
        head = git(self.author, 'rev-parse', 'HEAD')
        environment = self.root / 'environment.json'; environment.write_text('{}')
        request = self.root / 'request.json'; output = self.root / 'result.json'
        request.write_text(json.dumps({'checkout': str(self.author), 'state': str(self.state), 'target': target,
            'candidate': head, 'tree': git(self.author, 'rev-parse', 'HEAD^{tree}'),
            'environment': str(environment), 'policy': 'recovery', 'output': str(output)}))
        result = subprocess.run([m.sys.executable, '-I', str(MODULE.with_name('merge_batch_validate.py')), str(request)],
                                capture_output=True, text=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('must run', result.stderr)
        self.assertFalse((self.author / 'shadow-ran').exists())
        self.assertFalse(output.exists())

    def test_controlled_configure_and_child_checker_imports(self):
        loader = importlib.util.spec_from_file_location('validator_fixture', MODULE.with_name('merge_batch_validate.py'))
        validator = importlib.util.module_from_spec(loader); loader.loader.exec_module(validator)
        (self.author / 'tools').mkdir()
        (self.author / 'tools/__init__.py').write_text('')
        (self.author / 'json.py').write_text('raise RuntimeError("root shadow ran")')
        (self.author / 'tools/check.py').write_text('import json\nassert json.loads("1") == 1\n')
        (self.author / 'configure.py').write_text('import json,subprocess,sys\nassert json.loads("1") == 1\n'
                                                'subprocess.run([sys.executable,"tools/check.py"],check=True)\n')
        launcher = validator.python_launcher(self.state, [self.author])
        result = subprocess.run([str(launcher), 'configure.py'], cwd=self.author,
                                env=dict(os.environ, PSO_QUEUE_PYTHON=str(launcher)), capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stderr)

    def test_error_journal_write_keeps_real_flock_until_persisted(self):
        # Reproduce the reviewer's exact interleaving at the failed writer's
        # journal update. Real nonblocking flock must prevent B from publishing
        # before A persists its failure. No sleeps or mocked flock results.
        self.batch['publication_freeze'] = True
        environment = self.root / 'environment.json'; environment.write_text('{}')
        self.batch['environment_sha256'] = m.digest(environment)
        validator = self.root / 'validator.py'
        validator.write_text('import json,sys,pathlib\nr=json.loads(pathlib.Path(sys.argv[1]).read_text())\n'
                             + 'v=' + repr(self.result) + '\n'
                             + "v.update(target=r['target'],tree=r['tree'])\n"
                             + "pathlib.Path(r['output']).write_text(json.dumps(v))\n")
        self.q = LocalQueue(self.batch, self.state, self.api)
        self.q.execute('plan')
        batch = self.root / 'batch.json'; batch.write_text(json.dumps(self.batch))
        lockpath = self.root / 'queue.lock'
        original_open = open
        def private_open(path, *args, **kwargs):
            if str(path) == '/tmp/pso-mechanical-merge-queue.lock':
                path = lockpath
            return original_open(path, *args, **kwargs)
        original_write = self.q.write
        observed = {}
        def competing_retry(lock):
            retry = LocalQueue(self.batch, self.state, self.api)
            retry.lock_fd = lock.fileno()
            return retry.execute('execute', validator, m.digest(validator), environment)
        def error_write(**fields):
            if 'last_error' in fields:
                with original_open(lockpath, 'a') as other:
                    try:
                        m.fcntl.flock(other, m.fcntl.LOCK_EX | m.fcntl.LOCK_NB)
                    except BlockingIOError:
                        observed['retry_blocked'] = True
                    else:
                        observed['retry_blocked'] = False
                        observed['early_publication'] = competing_retry(other)['published_commit']
            return original_write(**fields)
        def fail_validation(*args):
            self.q.write(state='validating')
            raise m.Rejected('failed_build_or_checks', 'Synthetic first validation failure')
        output = io.StringIO()
        with patch.object(m, 'Queue', return_value=self.q), \
             patch.object(self.q, 'execute', side_effect=fail_validation), \
             patch.object(self.q, 'write', side_effect=error_write), \
             patch('builtins.open', private_open), contextlib.redirect_stdout(output):
            code = m.main(['execute', '--batch', str(batch), '--state', str(self.state)])
        self.assertEqual(code, 1)
        self.assertEqual(json.loads(output.getvalue())['state'], 'rejected')
        self.assertTrue(observed['retry_blocked'], 'A released its lock before error journaling; B published and A overwrote its receipt')
        self.assertEqual(self.api.branch('main')['head'], self.batch['target'])
        # Once A's error is durable and its lock is released, B can safely finish.
        with original_open(lockpath, 'a') as other:
            m.fcntl.flock(other, m.fcntl.LOCK_EX | m.fcntl.LOCK_NB)
            published = competing_retry(other)
            self.assertEqual(published['state'], 'published')
            recovered = competing_retry(other)
            self.assertEqual(recovered['state'], 'published')
        saved = json.loads(self.q.journal.read_text())
        self.assertEqual(saved['published_commit'], self.api.branch('main')['head'])
        self.assertEqual(saved['state'], 'published')


if __name__ == '__main__':
    unittest.main()
