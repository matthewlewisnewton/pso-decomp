"""No real builds, production locks, release files or network operations."""
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
        (self.repo / 'build.ninja').write_text('rule progress\n  command = true\nbuild progress: progress\n')
        self.launcher = self.file('launcher', 'synthetic pinned launcher')
        self.ninja = self.file('ninja', 'synthetic pinned Ninja')
        self.prepared = self.file('prepared.json', json.dumps(dict(
            prepared=True, returncode=0, admission=dict(repo=str(self.repo),
            ninja_sha256=h.digest(self.repo / 'build.ninja'), inputs_sha256='b' * 64,
            ninja_tool=self.ninja))))
        self.approval = self.file('approved.json', json.dumps(dict(
            version=1, independent=True, producer='worker', reviewer='independent',
            verdict='pass', item='fixture', head=head, root=str(self.repo),
            prepared_sha256=self.prepared['sha256'], graph_sha256=h.digest(self.repo / 'build.ninja'),
            inputs_sha256='b' * 64, action=h.ACTION)))
        self.release = dict(version=1, queue=h.QUEUE, action=h.ACTION, release_id='release-one',
            item='fixture', head=head, root=str(self.repo), prepared=self.prepared,
            graph_sha256=h.digest(self.repo / 'build.ninja'), inputs_sha256='b' * 64,
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
        h.claim(self.control)
        self.launches += 1
        Path(self.release['output']).write_text('{"synthetic_returncode":0}')
        h.finish(self.control, 0, True)
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
                h.claim(self.control)
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
from tools.handoff_resume import claim
claim(sys.argv[1], lambda phase: os._exit(19))
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
            h.claim(self.control)
            return types.SimpleNamespace(returncode=1)
        with self.fake_process(uncertain):
            row = h.resume_one(self.control)
        self.assertEqual(row['state'], 'started')
        self.assertIsNotNone(row['blocked_reason'])
        h.finish(self.control, 1, True)
        with self.fake_process(): row = h.resume_one(self.control)
        self.assertEqual(row['state'], 'failed')
        self.assertIsNotNone(row['blocked_reason'])
        self.assertEqual(self.launches, 0)

    def test_local_wrapper_hook_reaches_one_synthetic_child(self):
        spec = importlib.util.spec_from_file_location('fixture_capacity', h.WRAPPER)
        capacity = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(capacity)
        admission = json.loads(Path(self.prepared['path']).read_text())['admission']
        def synthetic_child(argv, **kwargs):
            self.launches += 1
            Path(argv[4]).write_text('{"exit_status":0}')
            return types.SimpleNamespace(returncode=0)
        def invoke_wrapper(argv, **kwargs):
            with patch.object(sys, 'argv', argv[3:]), \
                 patch.object(capacity, 'pin_ninja'), \
                 patch.object(capacity, 'enabled_policy', return_value={}), \
                 patch.object(capacity, 'capacity_policy', return_value=1), \
                 patch.object(capacity, 'acquire', return_value=([], {})), \
                 patch.object(capacity, 'writable_trees'), \
                 patch.object(capacity, 'ninja_command', return_value=self.ninja['path']), \
                 patch.object(capacity, 'audit', return_value=admission), \
                 patch.object(capacity, 'check_prepared'), \
                 patch.object(capacity, 'setup_preflight', return_value={}), \
                 patch.object(capacity, 'inputs_fingerprint', return_value=self.release['inputs_sha256']), \
                 patch.object(capacity, 'subprocess', types.SimpleNamespace(run=synthetic_child, STDOUT=subprocess.STDOUT)):
                with self.assertRaises(SystemExit) as exc:
                    capacity.main()
                self.assertEqual(exc.exception.code, 0)
        with self.fake_process(invoke_wrapper):
            row = h.resume_one(self.control)
            h.resume_one(self.control)
        self.assertEqual(row['state'], 'finished')
        self.assertEqual(self.launches, 1)
        result = json.loads(Path(self.release['output']).read_text())
        self.assertEqual(result['returncode'], 0)


if __name__ == '__main__':
    unittest.main()
