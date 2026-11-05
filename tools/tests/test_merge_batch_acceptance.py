import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import time
import unittest
from unittest.mock import patch

spec = importlib.util.spec_from_file_location('acceptance_adapter', Path(__file__).parents[1] / 'merge_batch_validate_acceptance.py')
a = importlib.util.module_from_spec(spec)
spec.loader.exec_module(a)

# The wrapper fixture owns only private locks. The no-outer-lock test rejects
# any parent flock call before it could deadlock the child shared acquisition.
WRAPPER = r'''
import argparse,fcntl,json,os,time
from pathlib import Path
p=argparse.ArgumentParser()
for n in ('repo','receipt','mode','lane','prepared-receipt','reviewed-graph-sha256'):p.add_argument('--'+n,required=True)
x=p.parse_args(); private=Path(__file__).parent
assert x.mode=='isolated' and x.lane=='acceptance'
with open(private/'legacy.lock','a') as lock:
 fcntl.flock(lock,fcntl.LOCK_SH)
 start=time.monotonic()
 while (private/'resource-blocked').exists() or (private/'maintenance-blocked').exists():time.sleep(.01)
 with open(private/'acceptance.lock','a') as slot:
  fcntl.flock(slot,fcntl.LOCK_EX)
  old=json.loads(Path(x.prepared_receipt).read_text())
  if (private/'reject').exists():raise SystemExit(7)
  out=dict(returncode=0,lane=x.lane,slot=x.lane,mode=x.mode,repo=x.repo,
           admission=old['admission'],total_queue_wait_seconds=time.monotonic()-start,
           measurement={'wall_seconds':0})
  Path(x.receipt).write_text(json.dumps(out))
'''


class AcceptanceAdapterTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='acceptance-adapter-fixture-')
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.wrapper = self.root / 'wrapper.py'; self.wrapper.write_text(WRAPPER)
        self.base = self.root / 'base.py'; self.base.write_text('# fixture trusted harness\n')
        self.roots = {}
        for role in ('baseline', 'candidate'):
            repo = self.root / role; repo.mkdir()
            subprocess.run(['git','init','-q',str(repo)],check=True)
            (repo/'source.txt').write_text('source\n')
            subprocess.run(['git','add','source.txt'],cwd=repo,check=True)
            subprocess.run(['git','-c','user.name=fixture','-c','user.email=fixture@localhost',
                            'commit','-qm','fixture'],cwd=repo,check=True)
            (repo/'build.ninja').write_text('# explicitly reviewed fixture\n')
            head=a.git(repo,'rev-parse','HEAD');tree=a.git(repo,'rev-parse','HEAD^{tree}')
            prep=self.root/(role+'-prep.json')
            admission=dict(protocol='pso-build-capacity-v2',revision=4,repo=str(repo),
                           ninja_sha256=a.digest(repo/'build.ninja'),inputs_sha256='f'*64)
            prep.write_text(json.dumps(dict(prepared=True,returncode=0,admission=admission)))
            self.roots[role]=dict(path=str(repo),commit=head,tree=tree,
                graph_sha256=admission['ninja_sha256'],inputs_sha256='f'*64,preparation=self.pin(prep))
        self.review=dict(version=1,verdict='pass',independent=True,reviewer='fixture independent reviewer',
            roots_reserved_until_terminal=True,shared_inputs_immutable=True,graph_python_imports_isolated=True,
            target=self.roots['baseline']['commit'],candidate=self.roots['candidate']['commit'],
            tree=self.roots['candidate']['tree'],roots=self.roots,
            wrapper_sha256=a.digest(self.wrapper),base_validator_sha256=a.digest(self.base))
        self.review_path=self.root/'review.json'
        self.env_path=self.root/'environment.json'
        self.state=self.root/'state';self.state.mkdir()
        self.request={k:self.review[k] for k in ('target','candidate','tree')}
        self.request.update(environment=str(self.env_path),state=str(self.state))
        self.refresh()

    def pin(self,path):return dict(path=str(path),sha256=a.digest(path))

    def refresh(self):
        self.review_path.write_text(json.dumps(self.review))
        self.env={'acceptance_capacity':dict(lane='acceptance',wrapper=self.pin(self.wrapper),
            base_validator=self.pin(self.base),review=self.pin(self.review_path))}
        self.env_path.write_text(json.dumps(self.env))

    def build(self):
        return a.build(self.env['acceptance_capacity']['wrapper'],self.roots['candidate'],
                       self.state/'run.json',os.environ.copy())

    def test_ordinary_adapter_never_imports_sibling_cli(self):
        script=self.root/'merge_batch_validate_acceptance.py'
        script.write_bytes(Path(a.__file__).read_bytes())
        sibling=self.root/'merge_batch.py';marker=self.root/'sibling-executed'
        for content in (None,'raise RuntimeError("modified sibling")',
                        'from pathlib import Path; Path('+repr(str(marker))+').touch()'):
            if content is None: sibling.unlink(missing_ok=True)
            else: sibling.write_text(content)
            spec=importlib.util.spec_from_file_location('isolated_adapter_fixture',script)
            module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
            self.assertEqual(module.git(self.root/'candidate','rev-parse','HEAD'),self.roots['candidate']['commit'])
            self.assertFalse(marker.exists())

    def test_explicit_review_contract(self):
        _,_,roots=a.load_contract(self.request,self.env)
        self.assertEqual(roots['candidate'],self.root/'candidate')

    def test_acceptance_only_and_no_outer_flock(self):
        with patch('fcntl.flock',side_effect=AssertionError('adapter must not acquire locks')):
            result=self.build()
        self.assertEqual(result['lane'],'acceptance')
        self.assertEqual(result['slot'],'acceptance')
        self.assertFalse((self.root/'development.lock').exists())

    def test_stale_wrapper_rejects_before_execution(self):
        self.wrapper.write_text(WRAPPER+'\n# changed')
        with self.assertRaisesRegex(RuntimeError,'stale_pinned_file'):self.build()
        self.assertFalse((self.root/'legacy.lock').exists())

    def test_stale_graph_rejects_before_execution(self):
        (self.root/'candidate/build.ninja').write_text('# different graph')
        with self.assertRaisesRegex(RuntimeError,'stale_reviewed_graph'):self.build()

    def test_stale_preparation_rejects(self):
        path=Path(self.roots['candidate']['preparation']['path']);path.write_text('{}')
        with self.assertRaisesRegex(RuntimeError,'stale_pinned_file'):self.build()

    def test_review_for_different_tree_rejects(self):
        self.request['tree']='0'*40
        with self.assertRaisesRegex(RuntimeError,'stale_review_binding'):a.load_contract(self.request,self.env)

    def test_missing_independent_review_rejects(self):
        self.review['independent']=False;self.refresh()
        with self.assertRaisesRegex(RuntimeError,'independent_graph_review'):a.load_contract(self.request,self.env)

    def test_development_lane_rejects(self):
        self.env['acceptance_capacity']['lane']='development'
        with self.assertRaisesRegex(RuntimeError,'acceptance_lane_required'):a.load_contract(self.request,self.env)

    def test_dirty_source_rejects(self):
        (self.root/'candidate/source.txt').write_text('unreviewed')
        with self.assertRaisesRegex(RuntimeError,'dirty_prepared_tree'):self.build()

    def test_harness_hash_change_rejects(self):
        self.base.write_text('# changed harness')
        with self.assertRaisesRegex(RuntimeError,'stale_pinned_file'):a.load_contract(self.request,self.env)

    def test_build_failure_does_not_return_success(self):
        (self.root/'reject').touch()
        with self.assertRaisesRegex(RuntimeError,'acceptance_build_rejected'):self.build()
        self.assertFalse((self.state/'run.json').exists())

    def test_resource_and_maintenance_waits_are_not_bypassed(self):
        for name in ('resource-blocked','maintenance-blocked'):(self.root/name).touch()
        # A real child releases fixture admission barriers after a bounded wait.
        child=subprocess.Popen([sys.executable,'-c',
            'import pathlib,time,sys; time.sleep(.25); '
            '[p.unlink() for p in pathlib.Path(sys.argv[1]).glob("*-blocked")]',str(self.root)])
        self.addCleanup(lambda:child.wait(timeout=5))
        result=self.build()
        self.assertGreater(result['total_queue_wait_seconds'],.1)
        self.assertEqual(child.wait(timeout=5),0)

    def test_stale_shared_tool_rejected(self):
        class Base:
            @staticmethod
            def fingerprint(paths):return {str(p):a.digest(p) for p in paths}
        expected=a.canonical_hash(Base.fingerprint([self.wrapper]))
        a.check_shared(Base,[self.wrapper],expected)
        self.wrapper.write_text(WRAPPER+'# changed')
        with self.assertRaisesRegex(RuntimeError,'stale_shared_tools_or_originals'):
            a.check_shared(Base,[self.wrapper],expected)

    def test_real_maintenance_lock_wait_completes(self):
        child=subprocess.Popen([sys.executable,'-c',
            'import fcntl,pathlib,sys,time; p=pathlib.Path(sys.argv[1]); '
            'f=open(p/"legacy.lock","a"); fcntl.flock(f,fcntl.LOCK_EX); '
            '(p/"maintenance-ready").touch(); time.sleep(.4)',str(self.root)])
        self.addCleanup(lambda:child.wait(timeout=5))
        deadline=time.monotonic()+5
        while not (self.root/'maintenance-ready').exists():
            self.assertLess(time.monotonic(),deadline);time.sleep(.01)
        start=time.monotonic();self.build()
        self.assertGreater(time.monotonic()-start,.2)
        self.assertEqual(child.wait(timeout=5),0)

    def test_missing_root_reservation_rejects(self):
        self.review['roots_reserved_until_terminal']=False;self.refresh()
        with self.assertRaisesRegex(RuntimeError,'missing_operator_isolation'):
            a.load_contract(self.request,self.env)



if __name__=='__main__':unittest.main()
