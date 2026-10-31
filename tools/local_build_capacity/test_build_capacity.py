"""Private fixtures only: no production locks, marker, or actual builds."""
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import time
import unittest
from contextlib import ExitStack
from unittest.mock import patch

SCRIPT = Path(__file__).with_name('build_capacity.py')
spec = importlib.util.spec_from_file_location('capacity', SCRIPT)
c = importlib.util.module_from_spec(spec)
spec.loader.exec_module(c)


class Admission(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(prefix='capacity-review-test-')
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.repo = self.root / 'repo'
        for name in ('build', 'config/GPOE8P', 'orig/GPOE8P/files'):
            (self.repo / name).mkdir(parents=True)
        (self.repo / 'config/GPOE8P/data.json').write_text('{"files": []}')
        (self.repo / 'orig/GPOE8P/files/PsoV3.dol').write_bytes(b'fixture')
        (self.repo / 'build.ninja').write_text('rule link\n  command = false\n  depfile = $out.d\n  rspfile = $out.rsp\n  rspfile_content = x\nbuild build/output: link\n')
        self.patch = patch.object(c, 'inputs_fingerprint', return_value='fixture')
        self.patch.start()
        self.addCleanup(self.patch.stop)

    def test_normal(self):
        self.assertTrue(c.audit(self.repo)['admitted'])

    def test_symlink_depfile_and_rspfile(self):
        for suffix in ('.d', '.rsp'):
            with self.subTest(suffix=suffix):
                p = self.repo / ('build/output' + suffix)
                p.symlink_to(self.root / 'external')
                with self.assertRaisesRegex(RuntimeError, 'symlink'):
                    c.audit(self.repo)
                p.unlink()

    def test_hardlinked_sidefile(self):
        external = self.root / 'external'; external.write_text('untouched')
        os.link(external, self.repo / 'build/output.d')
        with self.assertRaisesRegex(RuntimeError, 'hard-linked'):
            c.audit(self.repo)
        self.assertEqual(external.read_text(), 'untouched')

    def test_external_explicit_depfile(self):
        p = self.repo / 'build.ninja'
        p.write_text(p.read_text().replace('$out.d', str(self.root / 'external.d')))
        with self.assertRaisesRegex(RuntimeError, 'outside checkout'):
            c.audit(self.repo)

    def test_undeclared_sidefile_symlink(self):
        (self.repo / 'build/undeclared').symlink_to(self.root / 'external')
        with self.assertRaisesRegex(RuntimeError, 'symlink'):
            c.audit(self.repo)

    def test_temp_root_symlink(self):
        (self.repo / 'build').rmdir()
        (self.repo / 'build').symlink_to(self.root)
        with self.assertRaisesRegex(RuntimeError, 'symlink'):
            c.audit(self.repo)

    def test_missing_original(self):
        (self.repo / 'orig/GPOE8P/files/PsoV3.dol').unlink()
        with self.assertRaisesRegex(RuntimeError, 'extraction'):
            c.audit(self.repo)

    def test_graph_freeze(self):
        for rule in c.BLOCKED_RULES:
            graph = f'rule {rule}\n  command = touch forbidden\n  generator = 1\nbuild build/setup: {rule} input\n'
            result = c.frozen_graph(graph)
            self.assertIn('command = touch forbidden', result)
            self.assertIn('build build/setup: phony', result)
            self.assertNotIn(f'build build/setup: {rule}', result)
        for graph in ('include other.ninja\n', 'subninja other.ninja\n', 'builddir = /elsewhere\n', 'rule unknown\n'):
            with self.assertRaises(RuntimeError): c.frozen_graph(graph)

    def test_prepared_split_command_hash_and_stale_input(self):
        graph = ('rule split\n  command = cp input build/setup\n'
                 'rule configure\n  command = touch build.ninja\n  generator = 1\n'
                 'rule progress\n  command = true\n'
                 'build build/setup: split input\n'
                 'build build.ninja: configure build/setup\n'
                 'build progress: progress build/setup\ndefault progress\n')
        (self.repo / 'input').write_text('fixture')
        source = self.repo / 'build.ninja';source.write_text(graph)
        result = subprocess.run([c.NINJA, 'build.ninja'], cwd=self.repo, capture_output=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        original = self.repo / 'build/prepared.ninja';original.write_text(graph)
        # Reproduce r3: replacing a non-generator command invalidates its log hash.
        broken = self.repo / 'build/broken.ninja'
        broken.write_text(graph.replace('cp input build/setup', '/usr/bin/false'))
        dry = subprocess.check_output([c.NINJA, '-f', str(broken), '-n', '-v', 'progress'], cwd=self.repo, text=True)
        self.assertIn('/usr/bin/false', dry)
        with patch.dict(os.environ, {'NINJA_STATUS': 'custom-status '}):
            c.setup_preflight(self.repo, original)
        frozen = self.repo / 'build/frozen.ninja';frozen.write_text(c.frozen_graph(graph))
        before = (self.repo / 'build/setup').stat().st_mtime_ns
        result = subprocess.run([c.NINJA, '-f', str(frozen), 'progress'], cwd=self.repo, capture_output=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual((self.repo / 'build/setup').stat().st_mtime_ns, before)
        self.assertEqual(source.read_text(), graph)
        # Timestamp-only stale inputs are caught even if their contents are unchanged.
        newer = time.time() + 5
        os.utime(self.repo / 'input', (newer, newer))
        with patch.dict(os.environ, {'NINJA_STATUS': 'custom-status '}):
            with self.assertRaisesRegex(RuntimeError, 'setup is dirty'):
                c.setup_preflight(self.repo, original)

    def test_policy_requires_authorized_expansion(self):
        self.assertEqual(c.capacity_policy({}), 1)
        with self.assertRaises(RuntimeError):
            c.capacity_policy({'development_slots': 2, 'total_slots': 3})
        self.assertEqual(c.capacity_policy({'development_slots': 2, 'total_slots': 3,
            'expansion_authorization': 'parent-reference', 'measurement_receipt': '/trial.json'}), 2)

    def test_machine_resource_reserve(self):
        with patch.object(c.Path, 'read_text', return_value='MemAvailable: 16777216 kB\n'), \
             patch.object(c.os, 'getloadavg', return_value=(0, 0, 0)):
            self.assertTrue(c.resources_available('acceptance'))
            self.assertFalse(c.resources_available('development'))
        with patch.object(c.Path, 'read_text', return_value='MemAvailable: 67108864 kB\n'), \
             patch.object(c.os, 'getloadavg', return_value=(100000, 0, 0)):
            self.assertFalse(c.resources_available('acceptance'))
            self.assertFalse(c.resources_available('development'))

    def test_ninja_requires_absolute_external_executable(self):
        for value in ('', 'ninja', './ninja', 'relative/bin/ninja'):
            with self.subTest(value=value), patch.object(c, 'NINJA', value), patch.object(c, 'PINNED_NINJA', None):
                with self.assertRaisesRegex(RuntimeError, 'explicit reviewed absolute'):
                    c.pin_ninja(self.repo)
        candidate = self.repo/'build/ninja'
        candidate.write_text('#!/bin/sh\nexit 0\n');candidate.chmod(0o700)
        with patch.object(c, 'NINJA', str(candidate)), patch.object(c, 'PINNED_NINJA', None):
            with self.assertRaisesRegex(RuntimeError, 'candidate writable'):
                c.pin_ninja(self.repo)

    def test_ninja_identity_replacement_and_stale_evidence(self):
        executable = self.root/'reviewed-ninja'
        executable.write_text('#!/bin/sh\nexit 0\n');executable.chmod(0o700)
        with patch.object(c, 'NINJA', str(executable)), patch.object(c, 'PINNED_NINJA', None):
            identity = c.pin_ninja(self.repo)
            executable.write_text('#!/bin/sh\nexit 1\n')
            with self.assertRaisesRegex(RuntimeError, 'changed during operation'):
                c.ninja_command(self.repo)
            with self.assertRaisesRegex(RuntimeError, 'differs from preparation'):
                c.pin_ninja(self.repo, identity)

    def test_preparation_receipt(self):
        current = c.audit(self.repo)
        p = self.root / 'prepared.json'
        p.write_text(json.dumps({'prepared': True, 'returncode': 0, 'admission': current}))
        c.check_prepared(self.repo, p, current['ninja_sha256'], current)
        with self.assertRaisesRegex(RuntimeError, 'reviewed graph'):
            c.check_prepared(self.repo, p, 'wrong', current)
        newer = dict(current, inputs_sha256='changed')
        with self.assertRaisesRegex(RuntimeError, 'stale'):
            c.check_prepared(self.repo, p, current['ninja_sha256'], newer)

    def test_receipt_exclusive_absolute_siblings(self):
        with self.assertRaises(RuntimeError): c.reserve_receipts(Path('relative.json'))
        p = self.root / 'one.json'
        c.reserve_receipts(p)
        with self.assertRaises(FileExistsError): c.reserve_receipts(p)
        p = self.root / 'two.json'
        p.with_suffix('.build.log').symlink_to(self.root / 'not-created')
        with self.assertRaises(FileExistsError): c.reserve_receipts(p)
        self.assertFalse((self.root / 'not-created').exists())

    def test_disjoint_roots(self):
        capacity = self.root / 'locks'
        c.register_root(self.repo, capacity)
        c.register_root(self.repo, capacity)
        c.register_root(self.root / 'other', capacity)
        for nested in (self.repo / 'nested', self.root):
            with self.assertRaisesRegex(RuntimeError, 'overlapping'):
                c.register_root(nested, capacity)


class Locks(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(prefix='capacity-lock-review-')
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.children = []
        self.addCleanup(self.stop_children)

    def stop_children(self):
        for child in self.children:
            if child.poll() is None: child.kill()
            child.wait(timeout=5)

    def worker(self, number, isolated=True, fail=False, inherited=False, lane='development', workspace=None):
        code = '''
import importlib.util, sys, time, subprocess
from pathlib import Path
from contextlib import ExitStack
s=importlib.util.spec_from_file_location('c',sys.argv[1]);c=importlib.util.module_from_spec(s);s.loader.exec_module(c)
r=Path(sys.argv[2]);n=sys.argv[3]
original_take=c.take
def observed_take(stack,path,mode):
 if path.name.startswith('workspace-'): (r/('workspace-wait'+n)).touch()
 handle=original_take(stack,path,mode)
 if path.name.startswith('workspace-'): (r/('workspace-owned'+n)).touch()
 return handle
c.take=observed_take
with ExitStack() as stack:
 h,_=c.acquire(stack,r/('repo'+sys.argv[8]),sys.argv[4]=='True',legacy=r/'legacy.lock',capacity=r/'slots',lane=sys.argv[7])
 if sys.argv[6]=='True':
  child=subprocess.Popen([sys.executable,'-c','import time; time.sleep(2)'],pass_fds=tuple(x.fileno() for x in h))
  (r/('child'+n)).write_text(str(child.pid))
 (r/('ready'+n)).touch()
 if sys.argv[5]=='True': raise RuntimeError('intentional failure')
 while not (r/('release'+n)).exists(): time.sleep(.02)
'''
        p = subprocess.Popen([sys.executable, '-B', '-c', code, str(SCRIPT), str(self.root),
            str(number), str(isolated), str(fail), str(inherited), lane,
            str(number if workspace is None else workspace)], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        self.children.append(p)
        return p

    def ready(self, number, timeout=4):
        deadline = time.monotonic() + timeout
        while not (self.root / f'ready{number}').exists():
            if time.monotonic() > deadline: self.fail(f'worker {number} not ready')
            time.sleep(.02)

    def release(self, number):
        (self.root / f'release{number}').touch()

    def blocked(self, number):
        time.sleep(.15)
        self.assertFalse((self.root / f'ready{number}').exists())

    def test_two_slots_legacy_and_waiter(self):
        with ExitStack() as stack:
            c.take(stack, self.root / 'legacy.lock', c.fcntl.LOCK_EX)
            self.worker(0);self.worker(1, lane='acceptance')
            self.blocked(0);self.blocked(1)
        self.ready(0);self.ready(1)
        self.worker(2);self.blocked(2)
        self.release(0);self.ready(2)
        self.worker(3, isolated=False);self.blocked(3)
        self.release(1);self.blocked(3)
        self.release(2);self.ready(3);self.release(3)
        for p in self.children: self.assertEqual(p.wait(timeout=4), 0)

    def test_development_cannot_take_acceptance_slot(self):
        self.worker(0);self.ready(0)
        self.worker(1);self.blocked(1)
        self.worker(2, lane='acceptance');self.ready(2)
        self.blocked(1)
        self.release(2);self.blocked(1)
        self.release(0);self.ready(1);self.release(1)

    def test_acceptance_pending_prevents_new_development_admission(self):
        with ExitStack() as stack:
            c.take(stack, self.root / 'legacy.lock', c.fcntl.LOCK_EX)
            self.worker(0, lane='acceptance');self.blocked(0)
            self.worker(1);self.blocked(1)
        self.ready(0)
        # Development can join only after acceptance has acquired the shared gate.
        self.ready(1)
        self.release(0);self.release(1)

    def test_waiting_maintenance_stops_shared_replenishment(self):
        self.worker(0, lane='acceptance');self.ready(0)
        self.worker(1, isolated=False);self.blocked(1)
        self.worker(2, lane='acceptance');self.blocked(2)
        self.release(0);self.ready(1);self.blocked(2)
        self.release(1);self.ready(2);self.release(2)

    def test_same_workspace_acceptance_cannot_deadlock_development(self):
        def observed(name):
            deadline = time.monotonic() + 4
            while not (self.root / name).exists():
                if time.monotonic() > deadline: self.fail(f'missing observation: {name}')
                time.sleep(.02)
        with ExitStack() as stack:
            c.take(stack, self.root / 'legacy.lock', c.fcntl.LOCK_EX)
            development = self.worker(0, workspace='shared')
            observed('workspace-owned0')
            acceptance = self.worker(1, lane='acceptance', workspace='shared')
            observed('workspace-wait1')
            self.assertFalse((self.root / 'ready0').exists())
            self.assertFalse((self.root / 'ready1').exists())
        self.ready(0)
        self.assertFalse((self.root / 'ready1').exists())
        self.release(0)
        self.assertEqual(development.wait(timeout=4), 0)
        self.ready(1);self.release(1)
        self.assertEqual(acceptance.wait(timeout=4), 0)

    def audit_fixture(self):
        repo = self.root / 'audit-repo'
        for name in ('build', 'config/GPOE8P', 'orig/GPOE8P/files'):
            (repo / name).mkdir(parents=True)
        (repo / 'config/GPOE8P/data.json').write_text('{"files": []}')
        (repo / 'orig/GPOE8P/files/PsoV3.dol').write_text('fixture')
        (repo / 'build.ninja').write_text('build build.ninja: phony\nbuild progress: phony\n')
        (repo / 'source').write_text('fixture input')
        with patch.object(c, 'inputs_fingerprint', side_effect=lambda r: c.digest(r / 'source')):
            current = c.audit(repo)
        prepared = self.root / 'prepared.json'
        prepared.write_text(json.dumps(dict(prepared=True, mode='legacy', returncode=0, admission=current)))
        marker = self.root / 'enabled.json'
        marker.write_text(json.dumps(dict(protocol=c.PROTOCOL, revision=c.REVISION, enabled=True,
            parent_broadcast='private test', development_slots=1, total_slots=2,
            wrapper_sha256=c.digest(SCRIPT))))
        return repo, prepared, marker, current['ninja_sha256']

    def audit_worker(self, fixture, label='audit', qualified=True, environment=None):
        repo, prepared, marker, graph = fixture
        code = r"""
import importlib.util,sys
from pathlib import Path
s=importlib.util.spec_from_file_location('c',sys.argv[1]);c=importlib.util.module_from_spec(s);s.loader.exec_module(c)
r=Path(sys.argv[2]);repo=Path(sys.argv[3]);label=sys.argv[7]
c.LEGACY=r/'legacy.lock';c.CAPACITY=r/'slots';c.ENABLE=Path(sys.argv[5])
# Synthetic fixture input fingerprint; admission, graph, proof and locking are real.
c.inputs_fingerprint=lambda repo:c.digest(repo/'source')
original=c.acquire
def observed(*args,**kwargs):
 (r/(label+'-queued')).touch()
 return original(*args,**kwargs)
c.acquire=observed
sys.argv=['capacity','--repo',str(repo),'--receipt',str(r/(label+'.json')),'--audit-only','--lane','acceptance'] + (['--mode','isolated','--prepared-receipt',sys.argv[4],'--reviewed-graph-sha256',sys.argv[6]] if sys.argv[8]=='True' else [])
c.main()
"""
        process = subprocess.Popen([sys.executable, '-B', '-c', code, str(SCRIPT), str(self.root),
            str(repo), str(prepared), str(marker), graph, label, str(qualified)],
            stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, env=environment)
        self.children.append(process)
        return process

    def test_qualified_audit_overlaps_development(self):
        fixture = self.audit_fixture()
        development = self.worker(0);self.ready(0)
        audit = self.audit_worker(fixture)
        self.assertEqual(audit.wait(timeout=5), 0)
        self.assertIsNone(development.poll())
        receipt = json.loads((self.root / 'audit.json').read_text())
        self.assertTrue(receipt['qualified_acceptance_audit'])
        self.assertEqual((receipt['slot'], receipt['legacy_gate_mode']), ('acceptance', 'shared'))
        self.release(0)

    def test_qualified_audit_waits_for_maintenance(self):
        fixture = self.audit_fixture()
        self.worker(0, isolated=False);self.ready(0)
        audit = self.audit_worker(fixture)
        time.sleep(.2);self.assertIsNone(audit.poll())
        self.release(0)
        self.assertEqual(audit.wait(timeout=5), 0)

    def test_unqualified_audit_remains_exclusive(self):
        fixture = self.audit_fixture()
        self.worker(0);self.ready(0)
        audit = self.audit_worker(fixture, qualified=False)
        time.sleep(.2);self.assertIsNone(audit.poll())
        self.release(0)
        self.assertEqual(audit.wait(timeout=5), 0)
        receipt = json.loads((self.root / 'audit.json').read_text())
        self.assertFalse(receipt['qualified_acceptance_audit'])
        self.assertEqual(receipt['legacy_gate_mode'], 'exclusive')

    def test_qualified_audit_rejects_stale_proofs(self):
        fixture = self.audit_fixture()
        repo, prepared, marker, graph = fixture
        initial = {p: p.read_text() for p in (repo/'build.ninja', repo/'source', prepared, marker)}
        mutations = [
            (repo/'build.ninja', initial[repo/'build.ninja']+'# changed\n'),
            (repo/'source', 'changed input'),
            (prepared, json.dumps(dict(json.loads(initial[prepared]), mode='isolated'))),
            (prepared, json.dumps(dict(json.loads(initial[prepared]), returncode=1))),
            (marker, json.dumps(dict(json.loads(initial[marker]), enabled=False))),
            (marker, json.dumps(dict(json.loads(initial[marker]), revision=3))),
            (marker, json.dumps(dict(json.loads(initial[marker]), wrapper_sha256='stale'))),
        ]
        for i, (path, value) in enumerate(mutations):
            with self.subTest(path=path, case=i):
                path.write_text(value)
                self.assertNotEqual(self.audit_worker(fixture, label=f'stale{i}').wait(timeout=5), 0)
                path.write_text(initial[path])

    def test_qualified_audit_rejects_candidate_path_ninja_without_execution(self):
        fixture = self.audit_fixture()
        repo = fixture[0]
        sentinel = self.root/'outside-write'
        stub = repo/'ninja'
        stub.write_text('#!/bin/sh\nprintf executed > "'+str(sentinel)+'"\nexit 0\n')
        stub.chmod(0o700)
        for i, configured in enumerate((None, './ninja', str(stub))):
            environment = dict(os.environ, PATH='.:/usr/bin')
            if configured is None:
                environment.pop('PSO_BUILD_NINJA', None)
            else:
                environment['PSO_BUILD_NINJA'] = configured
            process = self.audit_worker(fixture, label=f'unsafe-tool{i}', environment=environment)
            self.assertNotEqual(process.wait(timeout=5), 0)
            self.assertFalse(sentinel.exists())
        # A different explicit external tool must also fail preparation proof
        # before any Ninja query invokes it.
        external = self.root/'different-ninja'
        external.write_bytes(stub.read_bytes());external.chmod(0o700)
        process = self.audit_worker(fixture, label='different-tool',
            environment=dict(os.environ, PSO_BUILD_NINJA=str(external)))
        self.assertNotEqual(process.wait(timeout=5), 0)
        self.assertFalse(sentinel.exists())

    def test_qualified_audit_rechecks_marker_after_wait(self):
        fixture = self.audit_fixture()
        self.worker(0, isolated=False);self.ready(0)
        audit = self.audit_worker(fixture)
        deadline = time.monotonic()+4
        while not (self.root/'audit-queued').exists():
            if time.monotonic()>deadline:self.fail('audit did not queue')
            time.sleep(.02)
        marker = fixture[2]
        marker.write_text(json.dumps(dict(json.loads(marker.read_text()), enabled=False)))
        self.release(0)
        self.assertNotEqual(audit.wait(timeout=5), 0)
        self.assertIn('broadcast marker', json.loads((self.root/'audit.json').read_text())['error'])

    def test_failure_releases_all_locks(self):
        p = self.worker(0, fail=True);self.ready(0)
        self.assertNotEqual(p.wait(timeout=4), 0)
        p = self.worker(0);self.release(0)
        self.assertEqual(p.wait(timeout=4), 0)
        self.worker(1, isolated=False);self.ready(1);self.release(1)

    def test_wrapper_death_child_retains_lock(self):
        p = self.worker(0, inherited=True);self.ready(0)
        p.kill();p.wait(timeout=4)
        self.worker(1, isolated=False);self.blocked(1)
        self.ready(1, timeout=5);self.release(1)


if __name__ == '__main__':
    unittest.main(verbosity=2)
