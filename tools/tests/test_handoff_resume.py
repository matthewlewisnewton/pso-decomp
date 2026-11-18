"""No real builds, production locks, release files or network operations."""
from contextlib import redirect_stdout
import io
import copy
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import threading
import types
import unittest
from unittest.mock import patch

from tools import handoff_resume as h
from tools.tests.test_merge_batch_config_development import discover_test_ninja


class ResumeTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.repo = self.root / 'repo'
        self.repo.mkdir()
        self.git('init', '-q')
        self.git('config', 'user.name', 'fixture')
        self.git('config', 'user.email', 'fixture@localhost')
        (self.repo / 'source').write_text('synthetic')
        self.git('add', 'source')
        self.git('commit', '-qm', 'fixture')
        head = self.git('rev-parse', 'HEAD')
        (self.repo / 'build.ninja').write_text('rule progress\n  command = true\nbuild progress: progress\nbuild build.ninja: phony\n')
        self.launcher = self.file('launcher', 'synthetic pinned launcher')
        executable = discover_test_ninja()
        self.ninja = dict(path=str(executable), sha256=h.digest(executable))
        for directory in ('build', 'config/GPOE8P', 'orig/GPOE8P/files'):
            (self.repo / directory).mkdir(parents=True, exist_ok=True)
        (self.repo / 'objdiff.json').write_text('{}')
        (self.repo / 'config/GPOE8P/data.json').write_text('{"files":[]}')
        (self.repo / 'orig/GPOE8P/files/PsoV3.dol').write_bytes(b'synthetic fixture only')
        # Obtain an actual preparation receipt from wrapper main with a real
        # Ninja. Only capacity/lock admission is replaced by a private fixture.
        capacity = self.capacity()
        prepared = self.root / 'prepared.json'
        with patch.object(sys, 'argv', [str(h.WRAPPER), '--repo', str(self.repo),
                '--receipt', str(prepared), '--prepare-only']), \
             patch.object(capacity, 'acquire', return_value=([], {})), redirect_stdout(io.StringIO()):
            with self.assertRaises(SystemExit) as exc:
                capacity.main()
            self.assertEqual(exc.exception.code, 0)
        self.prepared = dict(path=str(prepared), sha256=h.digest(prepared))
        self.admission = json.loads(prepared.read_text())['admission']
        self.approval = self.file('approved.json', json.dumps(dict(
            version=1, independent=True, producer='worker', reviewer='independent',
            verdict='pass', item='fixture', head=head, root=str(self.repo),
            prepared_sha256=self.prepared['sha256'], graph_sha256=h.digest(self.repo / 'build.ninja'),
            inputs_sha256=self.admission['inputs_sha256'], action=h.ACTION)))
        self.release = dict(version=1, queue=h.QUEUE, action=h.ACTION, release_id='release-one',
            item='fixture', head=head, root=str(self.repo), prepared=self.prepared,
            graph_sha256=h.digest(self.repo / 'build.ninja'), inputs_sha256=self.admission['inputs_sha256'],
            approval=self.approval, notice=self.file('release-notice', 'Existing RELEASED decision'),
            launcher=self.launcher, ninja=self.ninja, output=str(self.root / 'result.json'), issued_ms=100)
        companion = h.publish_companion(self.release, self.root / 'companion.json')
        self.config = dict(version=1, enabled=True, trial_id='fixture-trial', companion=companion,
            approval_sha256=self.approval['sha256'], adapter_sha256=h.digest(h.HERE),
            wrapper_sha256=h.digest(h.WRAPPER), python_sha256=h.digest(h.PYTHON),
            journal=str(self.root / 'attempts.sqlite'))
        self.control = self.root / 'control.json'
        self.save_control()
        self.launches = 0

    def git(self, *args):
        return subprocess.check_output(['/usr/bin/git', '-C', str(self.repo), *args], text=True).strip()

    def file(self, name, data):
        path = self.root / name
        path.write_text(data)
        return dict(path=str(path), sha256=h.digest(path))

    def save_control(self):
        self.control.write_text(json.dumps(self.config))

    def fake_wrapper(self, argv, env, check):
        self.assertEqual(argv[:4], [str(h.PYTHON), '-I', '-B', str(h.WRAPPER)])
        self.assertNotIn('PYTHONPATH', env)
        self.assertNotIn('PYTHONHOME', env)
        self.assertEqual(argv[argv.index('--lane') + 1], 'development')
        invocation = h.capture(self.control)
        h.claim(invocation)
        self.launches += 1
        Path(self.release['output']).write_text('{"synthetic_returncode":0}')
        h.finish(invocation, 0, True)
        return types.SimpleNamespace(returncode=0)

    def fake_process(self, run=None):
        return patch.object(h, 'subprocess', types.SimpleNamespace(
            check_output=subprocess.check_output, run=run or self.fake_wrapper))

    def test_fixed_launch_replay_and_actual_monotonic_latency(self):
        with self.fake_process():
            row = h.resume_one(self.control)
            again = h.resume_one(self.control)
        self.assertEqual(self.launches, 1)
        self.assertEqual(row, again)
        self.assertEqual(row['state'], 'finished')
        self.assertLessEqual(row['observed_ns'], row['intent_ns'])
        self.assertLessEqual(row['intent_ns'], row['started_ns'])
        self.assertLessEqual(row['started_ns'], row['finished_ns'])
        self.assertGreaterEqual(row['started_ns'] - row['observed_ns'], 0)
        self.assertIsNone(row['blocked_reason'])

    def test_concurrent_duplicate_only_invokes_one_wrapper(self):
        results = []
        errors = []
        def run():
            try:
                results.append(h.resume_one(self.control))
            except BaseException as exc:
                errors.append(exc)
        with self.fake_process():
            threads = [threading.Thread(target=run) for _ in range(3)]
            for t in threads: t.start()
            for t in threads: t.join()
        self.assertEqual(errors, [])
        self.assertEqual(self.launches, 1)
        self.assertEqual(len(results), 3)

    def test_schema_action_approval_head_and_pin_drift_are_closed(self):
        bad = copy.deepcopy(self.release)
        for action in ('acceptance', 'publish', 'retry_denied', 'arbitrary_command'):
            bad['action'] = action
            with self.assertRaises(ValueError):
                h.publish_companion(bad, self.root / 'bad.json')
        self.config['approval_sha256'] = 'c' * 64
        self.save_control()
        with self.assertRaisesRegex(ValueError, 'unapproved'):
            h.resume_one(self.control)
        self.config['approval_sha256'] = self.approval['sha256']
        self.save_control()
        (self.repo / 'build.ninja').write_text('drift')
        with self.assertRaisesRegex(ValueError, 'graph drift'):
            h.resume_one(self.control)

    def test_head_change_hold_and_denied_approval_cannot_launch(self):
        self.git('commit', '--allow-empty', '-qm', 'advance')
        with self.assertRaisesRegex(ValueError, 'head drift'):
            h.resume_one(self.control)
        self.git('reset', '--hard', self.release['head'])
        approval = json.loads(Path(self.approval['path']).read_text())
        for verdict in ('hold', 'denied', 'unknown'):
            approval['verdict'] = verdict
            self.approval = self.file('approved.json', json.dumps(approval))
            self.release['approval'] = self.approval
            path = self.root / (verdict + '.json')
            self.config['companion'] = h.publish_companion(self.release, path)
            self.config['approval_sha256'] = self.approval['sha256']
            self.save_control()
            with self.assertRaisesRegex(ValueError, 'independent approval required'):
                h.resume_one(self.control)

    def test_disabled_before_start_and_while_waiting_for_capacity(self):
        self.config['enabled'] = False
        self.save_control()
        with self.assertRaisesRegex(ValueError, 'disabled'):
            h.resume_one(self.control)
        self.config['enabled'] = True
        self.save_control()
        def disable(*args, **kwargs):
            self.config['enabled'] = False
            self.save_control()
            with self.assertRaisesRegex(ValueError, 'disabled'):
                h.claim(h.capture(self.control))
        with self.fake_process(disable):
            row = h.resume_one(self.control)
        self.assertEqual(row['state'], 'intent')
        self.assertIsNotNone(row['blocked_reason'])
        self.assertEqual(self.launches, 0)

    def test_process_crashes_leave_no_automatic_retry(self):
        # Process death after durable intent, including the gap before spawn.
        script = '''
import os, sys
from tools.handoff_resume import resume_one
def crash(phase):
    if phase == 'after_intent': os._exit(17)
resume_one(sys.argv[1], crash)
'''
        result = subprocess.run([sys.executable, '-c', script, str(self.control)])
        self.assertEqual(result.returncode, 17)
        with self.fake_process():
            row = h.resume_one(self.control)
        self.assertEqual(self.launches, 0)
        self.assertEqual(row['state'], 'intent')
        self.assertIn('never relaunch', row['blocked_reason'])
        # Claim then process death leaves a started attempt, not a new release.
        script = '''
import os, sys
from tools.handoff_resume import claim, capture
claim(capture(sys.argv[1]), lambda phase: os._exit(19))
'''
        result = subprocess.run([sys.executable, '-c', script, str(self.control)])
        self.assertEqual(result.returncode, 19)
        with self.fake_process():
            row = h.resume_one(self.control)
        self.assertEqual(row['state'], 'started')
        self.assertEqual(self.launches, 0)

    def test_conflicting_release_reuse_does_not_create_new_attempt(self):
        with self.fake_process(): h.resume_one(self.control)
        self.config['trial_id'] = 'alias'
        self.save_control()
        with self.assertRaisesRegex(ValueError, 'conflicting release reuse'):
            h.resume_one(self.control)
        with self.assertRaises(FileExistsError):
            h.publish_companion(self.release, self.root / 'companion.json')

    def test_wrapper_failure_and_uncertain_return_are_blocked(self):
        def uncertain(*args, **kwargs):
            h.claim(h.capture(self.control))
            return types.SimpleNamespace(returncode=1)
        with self.fake_process(uncertain):
            row = h.resume_one(self.control)
        self.assertEqual(row['state'], 'started')
        self.assertIsNotNone(row['blocked_reason'])
        h.finish(h.capture(self.control), 1, True)
        with self.fake_process(): row = h.resume_one(self.control)
        self.assertEqual(row['state'], 'failed')
        self.assertIsNotNone(row['blocked_reason'])
        self.assertEqual(self.launches, 0)

    def capacity(self):
        spec = importlib.util.spec_from_file_location('fixture_capacity', h.WRAPPER)
        capacity = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(capacity)
        capacity.NINJA = self.ninja['path']
        capacity.CAPACITY = self.root / 'private-capacity'
        return capacity

    def invoke_actual_wrapper(self, acquire=None, on_child=None):
        capacity = self.capacity()
        real_run = subprocess.run
        def child(argv, **kwargs):
            if argv[0] == '/usr/bin/time':
                self.launches += 1
                if on_child:
                    on_child()
            return real_run(argv, **kwargs)
        def invoke(argv, **kwargs):
            with patch.object(sys, 'argv', argv[3:]), \
                 patch.object(capacity, 'enabled_policy', return_value={}), \
                 patch.object(capacity, 'capacity_policy', return_value=1), \
                 patch.object(capacity, 'acquire', side_effect=acquire or (lambda *a, **k: ([], {}))), \
                 patch.object(capacity, 'subprocess', types.SimpleNamespace(
                     run=child, check_output=subprocess.check_output, STDOUT=subprocess.STDOUT)), \
                 redirect_stdout(io.StringIO()):
                capacity.main()
        return invoke

    def run_actual_wrapper(self, acquire=None, on_child=None):
        invoke = self.invoke_actual_wrapper(acquire, on_child)
        def run(argv, **kwargs):
            try:
                invoke(argv, **kwargs)
            except SystemExit as exc:
                self.assertEqual(exc.code, 0)
        return run

    def reserve_other(self, other):
        other.release['release_id'] = 'release-B'
        other.config['trial_id'] = 'trial-B'
        other.config['companion'] = h.publish_companion(other.release, other.root / 'companion-B.json')
        other.save_control()
        invocation = h.capture(other.control)
        c, d = invocation.config, invocation.release
        db = h.connect(c['journal'])
        db.execute('INSERT INTO attempts VALUES (?, ?, ?, ?, ?, ?, NULL, NULL, NULL, NULL)',
                   (d['release_id'], c['companion']['sha256'], c['trial_id'], 'intent', 1, 1))
        db.close()
        return invocation

    def row(self, journal, release):
        db = h.connect(journal)
        try:
            return h.status(db, release)
        finally:
            db.close()

    def test_local_wrapper_hook_real_preparation_and_real_ninja_identity(self):
        full = self.admission['ninja_tool']
        self.assertEqual(set(full), {'path', 'sha256', 'device', 'inode', 'size', 'mtime_ns'})
        self.assertEqual(self.capacity().pin_ninja(self.repo, full), full)
        h.load(self.control)
        with self.fake_process(self.run_actual_wrapper()):
            row = h.resume_one(self.control)
            h.resume_one(self.control)
        self.assertEqual(row['state'], 'finished')
        self.assertEqual(self.launches, 1)
        result = json.loads(Path(self.release['output']).read_text())
        self.assertEqual(result['returncode'], 0)
        self.assertEqual(result['admission']['ninja_tool'], full)

    def test_real_identity_stat_drift_rejected_even_when_file_pin_matches(self):
        prior = json.loads(Path(self.prepared['path']).read_text())
        prior['admission']['ninja_tool']['inode'] += 1
        prepared = self.file('bad-prepared.json', json.dumps(prior))
        release = copy.deepcopy(self.release)
        release['prepared'] = prepared
        approved = json.loads(Path(self.approval['path']).read_text())
        approved['prepared_sha256'] = prepared['sha256']
        release['approval'] = self.file('bad-approved.json', json.dumps(approved))
        self.config['companion'] = h.publish_companion(release, self.root / 'bad-companion.json')
        self.config['approval_sha256'] = release['approval']['sha256']
        self.save_control()
        with self.assertRaisesRegex(ValueError, 'Ninja identity differs'):
            h.resume_one(self.control)

    def test_actual_wrapper_control_replacement_during_admission_blocks_both_roots(self):
        for different_journal in (False, True):
            with self.subTest(different_journal=different_journal):
                # Each case uses real wrapper-generated preparation receipts.
                a, b = ResumeTests(), ResumeTests()
                a.setUp(); b.setUp()
                try:
                    if not different_journal:
                        b.config['journal'] = a.config['journal']
                    self.reserve_other(b)
                    def replace(*args, **kwargs):
                        a.control.write_text(json.dumps(b.config))
                        return [], {}
                    with a.fake_process(a.invoke_actual_wrapper(acquire=replace)):
                        with self.assertRaisesRegex(ValueError, 'control changed during admission'):
                            h.resume_one(a.control)
                    self.assertEqual(a.launches, 0)
                    self.assertEqual(self.row(a.config['journal'], 'release-one')['state'], 'preflight_failed')
                    self.assertEqual(self.row(b.config['journal'], 'release-B')['state'], 'intent')
                    self.assertFalse(Path(b.release['output']).exists())
                finally:
                    a.doCleanups(); b.doCleanups()

    def legacy_contract(self):
        # Synthetic copy emulates the legacy schema; the real modern receipt
        # remains unchanged. Live RLC originals are checked separately read-only.
        original = json.loads(Path(self.prepared['path']).read_bytes())
        identity = original['admission'].pop('ninja_tool')
        self.prepared = self.file('legacy-prepared.json', json.dumps(original))
        self.release['prepared'] = self.prepared
        wrapper = self.file('legacy-wrapper.py', 'NINJA = ' + repr(self.ninja['path']) + '\n')
        stat = Path(self.ninja['path']).stat()
        manifest = self.file('legacy-tools.json', json.dumps({self.ninja['path']: dict(
            sha256=self.ninja['sha256'], bytes=stat.st_size, mode=oct(stat.st_mode & 0o777))}))
        root = dict(path=self.release['root'], head=self.release['head'],
                    preparation=self.prepared, graph_sha256=self.release['graph_sha256'],
                    inputs_sha256=self.release['inputs_sha256'])
        plan = self.file('legacy-plan.json', json.dumps(dict(
            tools=dict(ninja=self.ninja['path']), tool_manifest_sha256=manifest['sha256'],
            roots={'baseline': root})))
        packet = self.file('legacy-packet.json', json.dumps(dict(
            plan=plan, wrapper=wrapper, tool_manifest=manifest, roots={'baseline': root})))
        self.release['legacy_preparation'] = dict(packet=packet, current_ninja_tool=identity)
        approval = json.loads(Path(self.approval['path']).read_text())
        approval['prepared_sha256'] = self.prepared['sha256']
        approval['legacy_preparation_sha256'] = h.legacy_binding_hash(self.release['legacy_preparation'])
        self.release['approval'] = self.file('legacy-approved.json', json.dumps(approval))
        self.config['approval_sha256'] = self.release['approval']['sha256']
        self.config['companion'] = h.publish_companion(self.release, self.root / 'legacy-companion.json')
        self.save_control()
        return wrapper['sha256'], original

    def test_legacy_manifest_binding_preserves_original_and_strict_wrapper_checks(self):
        wrapper_sha, original = self.legacy_contract()
        raw = Path(self.prepared['path']).read_bytes()
        with patch.object(h, 'LEGACY_WRAPPERS', {wrapper_sha}):
            h.load(self.control)
            identity = h.preparation_ninja(self.release, original)
        capacity = self.capacity()
        current = dict(original['admission'], ninja_tool=identity)
        capacity.check_prepared(self.repo, Path(self.prepared['path']),
            self.release['graph_sha256'], current, legacy_ninja_identity=identity)
        with self.assertRaisesRegex(RuntimeError, 'ninja_tool'):
            capacity.check_prepared(self.repo, Path(self.prepared['path']),
                                   self.release['graph_sha256'], current)
        self.assertEqual(Path(self.prepared['path']).read_bytes(), raw)
        self.assertNotIn('ninja_tool', json.loads(raw)['admission'])

    def test_legacy_evidence_requires_pinned_supported_chain_and_current_identity(self):
        wrapper_sha, original = self.legacy_contract()
        with self.assertRaisesRegex(ValueError, 'unsupported legacy wrapper'):
            h.preparation_ninja(self.release, original)
        with patch.object(h, 'LEGACY_WRAPPERS', {wrapper_sha}):
            changed = copy.deepcopy(self.release)
            changed['legacy_preparation']['current_ninja_tool']['inode'] += 1
            with self.assertRaisesRegex(ValueError, 'Ninja identity differs'):
                h.preparation_ninja(changed, original)
            changed = copy.deepcopy(self.release)
            changed['head'] = 'c' * 40
            with self.assertRaisesRegex(ValueError, 'root/head provenance'):
                h.preparation_ninja(changed, original)
            Path(self.prepared['path']).write_text('{}')
            with self.assertRaisesRegex(ValueError, 'changed pinned file'):
                h.preparation_ninja(self.release, original)

    def test_actual_wrapper_rejects_trial_or_journal_only_change_during_wait(self):
        for field, value in (('trial_id', 'changed-trial'),
                             ('journal', str(self.root / 'different.sqlite'))):
            with self.subTest(field=field):
                a = ResumeTests(); a.setUp()
                try:
                    original = copy.deepcopy(a.config)
                    def replace(*args, **kwargs):
                        replacement = dict(a.config, **{field: value})
                        a.control.write_text(json.dumps(replacement))
                        return [], {}
                    with a.fake_process(a.invoke_actual_wrapper(acquire=replace)):
                        with self.assertRaisesRegex(ValueError, 'control changed during admission'):
                            h.resume_one(a.control)
                    self.assertEqual(a.launches, 0)
                    self.assertEqual(self.row(original['journal'], 'release-one')['state'], 'preflight_failed')
                finally:
                    a.doCleanups()

    def test_actual_wrapper_finishes_original_after_control_disabled_or_removed(self):
        for change in ('disable', 'remove'):
            with self.subTest(change=change):
                a = ResumeTests(); a.setUp()
                try:
                    def mutate():
                        if change == 'remove':
                            a.control.unlink()
                        else:
                            a.config['enabled'] = False
                            a.save_control()
                    with a.fake_process(a.run_actual_wrapper(on_child=mutate)):
                        row = h.resume_one(a.control)
                    self.assertEqual(row['state'], 'finished')
                    self.assertEqual(a.launches, 1)
                    self.assertEqual(self.row(a.config['journal'], 'release-one')['state'], 'finished')
                finally:
                    a.doCleanups()

    def test_actual_wrapper_completion_retains_original_after_control_replacement(self):
        b = ResumeTests(); b.setUp()
        try:
            self.reserve_other(b)
            original = copy.deepcopy(self.config)
            def replace():
                self.control.write_text(json.dumps(b.config))
            with self.fake_process(self.run_actual_wrapper(on_child=replace)):
                row = h.resume_one(self.control)
            self.assertEqual(row['state'], 'finished')
            self.assertEqual(self.launches, 1)
            self.assertEqual(self.row(original['journal'], 'release-one')['state'], 'finished')
            self.assertEqual(self.row(b.config['journal'], 'release-B')['state'], 'intent')
            self.assertFalse(Path(b.release['output']).exists())
        finally:
            b.doCleanups()

    def test_control_replacement_before_wrapper_entry_cannot_rebind_parent_intent(self):
        b = ResumeTests(); b.setUp()
        try:
            self.reserve_other(b)
            invoke = self.invoke_actual_wrapper()
            def replace(argv, **kwargs):
                self.control.write_text(json.dumps(b.config))
                return invoke(argv, **kwargs)
            with self.fake_process(replace):
                with self.assertRaisesRegex(RuntimeError, 'identity changed before wrapper entry'):
                    h.resume_one(self.control)
            self.assertEqual(self.launches, 0)
            self.assertEqual(self.row(self.config['journal'], 'release-one')['state'], 'intent')
            self.assertEqual(self.row(b.config['journal'], 'release-B')['state'], 'intent')
        finally:
            b.doCleanups()


if __name__ == '__main__':
    unittest.main()
