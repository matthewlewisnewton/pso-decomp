"""Private Git and lock fixtures for pre-configuration admission."""
import copy
import fcntl
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import threading
import time
import unittest
from unittest.mock import patch
from tools import merge_batch_config_delta as c
from tools import merge_batch_config_prepare as p
from tools import merge_batch_validate_acceptance as adapter

class PreparationTests(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup)
        self.root=Path(self.temp.name);self.repo=self.root/'repo';self.repo.mkdir()
        self.git('init','-q');self.git('config','user.name','fixture');self.git('config','user.email','fixture@localhost')
        self.marker=self.root/'configured';self.lock=self.root/'legacy.lock'
        base=("from typing import Dict, Any\nfrom pathlib import Path\n"
              "def _switch(*args): return []\ncflags_pso=[]\n"
              "GAME_EXCEPTIONS: Dict[str, Dict[str, Any]] = {\n"
              "    \"other.cpp\": {\"cflags\": []},\n}\n"
              f"Path({str(self.marker)!r}).touch()\nPath('build.ninja').write_text('fixture graph')\n").encode()
        after=base.replace(b'    "other.cpp"',b'    "pso/misc/TOTrapAncient01.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},\n    "other.cpp"')
        config=self.repo/'configure.py';config.write_bytes(base);config.chmod(0o755)
        (self.repo/'.gitignore').write_text('orig/\nbuild.ninja\n')
        source=self.repo/'src/unit.cpp';source.parent.mkdir();source.write_text('source\n')
        header=self.repo/'include/unit.h';header.parent.mkdir();header.write_text('header\n')
        self.git('add','configure.py','.gitignore','src/unit.cpp','include/unit.h');self.git('commit','-qm','base');self.target=self.git('rev-parse','HEAD')
        config.write_bytes(after);self.git('commit','-qam','candidate');self.head=self.git('rev-parse','HEAD');self.tree=self.git('rev-parse','HEAD^{tree}')
        self.candidate=self.git('commit-tree',self.tree,'-p',self.target,'-p',self.head,'-m','candidate merge');self.git('checkout','--detach',self.candidate)
        dol=self.repo/'orig/GPOE8P/files/PsoV3.dol';dol.parent.mkdir(parents=True);dol.write_bytes(b'fixture')
        self.original_sha=hashlib.sha256(dol.read_bytes()).hexdigest();self.original_sha1=hashlib.sha1(dol.read_bytes()).hexdigest()
        self.review=self.root/'review.json';self.review.write_text('{}')
        self.tool=self.root/'tool';self.tool.write_text('# fixture');self.tool.chmod(0o755)
        self.launcher=self.root/'launcher';self.launcher.write_text('#!/usr/bin/python3\nimport os,sys\nos.execv('+repr(sys.executable)+',['+repr(sys.executable)+',"-I",*sys.argv[1:]])\n');self.launcher.chmod(0o755)
        td=self.root/'tool-dir';td.mkdir();(td/'a').write_text('fixture')
        entries=[['a',hashlib.sha256((td/'a').read_bytes()).hexdigest(),(td/'a').stat().st_mode & 0o777]]
        directory={'path':str(td),'sha256':c.tree_digest(td)}
        self.checker=self.root/'checker.py';self.checker.write_bytes(Path(c.__file__).read_bytes());preparer=Path(p.__file__).resolve()
        pins={name:self.pin(self.tool) for name in c.PIN_NAMES}
        pins.update(compiler=self.pin(td/'a'),checker=self.pin(self.checker),preparer=self.pin(preparer),python=self.pin(Path(sys.executable).resolve()),git=self.pin(Path('/usr/bin/git').resolve()),launcher=self.pin(self.launcher))
        self.pr={'number':1,'head':self.head,'base_sha':self.target,'review_base':self.target,'review':dict(self.pin(self.review),verdict='pass',independent=True,reviewer='fixture',head=self.head,base=self.target)}
        self.commits=[{'pr':1,'head':self.head,'commit':self.candidate,'tree':self.tree}]
        change=c.step(self.repo,self.target,self.candidate)
        self.packet={'version':1,'repository':c.REPO,'policy':'recovery','target':self.target,'candidate':self.candidate,'tree':self.tree,'prs':[{'number':1,'head':self.head,'base_sha':self.target,'review_base':self.target,'review':{'path':self.pr['review']['path'],'sha256':self.pr['review']['sha256']}}],'steps':[change],'cumulative':change,'pins':pins,
                     'configure_paths':{name:(directory if name in ('compilers','binutils') else self.pin(self.tool)) for name in ('dtk','objdiff','wrapper','compilers','binutils')},
                     'originals':{role:{'tree_sha256':p.original_tree_sha256(self.repo),'dol_sha256':self.original_sha} for role in ('baseline','candidate')},
                     'dependent_compile':[], 'ordered_inputs':{role:{'ordered_inputs_sha256':'c'*64,'source_inputs':1,'fallback_inputs':0} for role in ('baseline','candidate')},
                     'effective_argv':[str(self.tool),str(td/'a'),'-inline','off,deferred','-c','src/'+c.UNIT],'verdict':'pass','independent':True,'reviewer':'fixture'}
        self.ninja=self.root/'ninja';self.ninja.write_text('#!/usr/bin/python3\nimport json\nprint('+repr(json.dumps([{'file':'src/'+c.UNIT,'command':' '.join(self.packet['effective_argv'])+' && fixture'}]))+')\n');self.ninja.chmod(0o755)
        self.packet['pins']['ninja']=self.pin(self.ninja)
        self.packet_file=self.root/'packet.json';self.write_packet();self.make_plan()
        self.request={'packet':self.pin(self.packet_file),'repo':str(self.repo),'role':'candidate','target':self.target,'candidate':self.candidate,'tree':self.tree,'prs':[self.pr],'commits':self.commits,'receipt':str(self.root/'receipt.json'),'original_sha256':self.original_sha,'original_tree_sha256':p.original_tree_sha256(self.repo),'plan_receipt':self.pin(self.plan_output)}
    def git(self,*args):return subprocess.check_output(['git','-C',str(self.repo),*args],stderr=subprocess.DEVNULL,text=True).strip()
    def pin(self,path):return {'path':str(path),'sha256':hashlib.sha256(path.read_bytes()).hexdigest()}
    def write_packet(self):self.packet_file.write_text(json.dumps(self.packet))
    def make_plan(self):
        self.plan_output=self.root/'plan-result.json'
        if self.plan_output.exists():self.plan_output.unlink()
        req={'mode':'plan','repo':str(self.repo),'packet':self.pin(self.packet_file),'checker':self.pin(self.checker),'cli':self.packet['pins']['cli'],
             'target':self.target,'candidate':self.candidate,'tree':self.tree,'prs':[self.pr],'commits':self.commits,'output':str(self.plan_output)}
        file=self.root/'plan-request.json';file.write_text(json.dumps(req))
        subprocess.run([sys.executable,'-I',str(self.checker),str(file)],check=True,capture_output=True)
    def run_prep(self):
        with patch.object(p,'DOL_SHA1',self.original_sha1):return p.prepare(self.request,str(self.checker),self.pin(self.checker)['sha256'],lock_path=self.lock)
    def test_valid_preflight_executes_and_receipt_binds_packet(self):
        result=self.run_prep();self.assertTrue(self.marker.exists())
        self.assertEqual(result['packet_sha256'],self.request['packet']['sha256'])
        self.assertEqual(json.loads(Path(self.request['receipt']).read_text()),result)
        with self.assertRaises(ValueError):self.run_prep()
    def test_preparation_receipts_bind_into_acceptance_contract(self):
        self.packet['pins']['adapter']=self.pin(Path(adapter.__file__).resolve())
        self.write_packet();self.request['packet']=self.pin(self.packet_file);self.make_plan();self.request['plan_receipt']=self.pin(self.plan_output)
        self.assertEqual(json.loads(self.plan_output.read_text())['packet_sha256'],self.pin(self.packet_file)['sha256'])
        candidate_receipt=self.run_prep()
        baseline=self.root/'baseline'
        subprocess.run(['git','clone','-q',str(self.repo),str(baseline)],check=True)
        subprocess.run(['git','-C',str(baseline),'checkout','-q','--detach',self.target],check=True)
        dol=baseline/'orig/GPOE8P/files/PsoV3.dol';dol.parent.mkdir(parents=True);dol.write_bytes(b'fixture')
        other=dict(self.request,repo=str(baseline),role='baseline',receipt=str(self.root/'baseline-receipt.json'),original_tree_sha256=p.original_tree_sha256(baseline))
        with patch.object(p,'DOL_SHA1',self.original_sha1):baseline_receipt=p.prepare(other,str(self.checker),self.pin(self.checker)['sha256'],lock_path=self.lock)
        roots={'baseline':baseline,'candidate':self.repo}
        graph={}
        for role,receipt in (('baseline',baseline_receipt),('candidate',candidate_receipt)):
            graph[role]={'commit':receipt['root_commit'],'tree':receipt['root_tree'],'graph_sha256':receipt['graph_sha256'],
                         'original_tree_sha256':receipt['original_tree_sha256'],'config_preflight':self.pin(Path(other['receipt'] if role=='baseline' else self.request['receipt']))}
        config={'checker':self.pin(self.checker),'packet':self.pin(self.packet_file)}
        request={'checkout':str(self.repo),'policy':'recovery','target':self.target,'candidate':self.candidate,'tree':self.tree,
                 'prs':[self.pr],'commits':self.commits,'config_admission':config,
                 'cli':self.packet['pins']['cli'],'validator':self.packet['pins']['guard'],
                 'config_plan':dict(self.pin(self.plan_output),packet_sha256=config['packet']['sha256'])}
        environment={'config_admission':config,'ninja':self.packet['pins']['ninja']['path'],**{name:self.packet['configure_paths'][name]['path'] for name in ('dtk','objdiff','wrapper','compilers','binutils')},
                     'acceptance_capacity':{'wrapper':self.packet['pins']['wrapper'],'base_validator':self.packet['pins']['base_validator']}}
        review={'config_plan_sha256':self.pin(self.plan_output)['sha256'],'config_packet_sha256':config['packet']['sha256'],'effective_compile_argv':self.packet['effective_argv'],
                'configuration_edge_review':True,'unlisted_edges_unchanged':True,'compiler_binding_reviewed':True,'no_setup_execution':True,
                'ordered_input_provenance':self.packet['ordered_inputs'],'dependent_compile':[],'roots':graph}
        adapter.config_contract(request,environment,review,roots)
        # Recheck through the real isolated adapter entry point before publication.
        for role,root in roots.items():
            admission={'protocol':'pso-build-capacity-v2','revision':4,'repo':str(root),
                       'ninja_sha256':graph[role]['graph_sha256'],'inputs_sha256':'f'*64}
            prep=self.root/(role+'-wrapper-preparation.json');prep.write_text(json.dumps({'prepared':True,'returncode':0,'admission':admission}))
            graph[role].update(path=str(root),inputs_sha256='f'*64,preparation=self.pin(prep))
        review.update(version=1,verdict='pass',independent=True,reviewer='independent fixture',
                      roots_reserved_until_terminal=True,shared_inputs_immutable=True,graph_python_imports_isolated=True,
                      target=self.target,candidate=self.candidate,tree=self.tree,
                      wrapper_sha256=self.packet['pins']['wrapper']['sha256'],base_validator_sha256=self.packet['pins']['base_validator']['sha256'])
        review_path=self.root/'graph-review.json';review_path.write_text(json.dumps(review))
        environment['acceptance_capacity'].update(lane='acceptance',review=self.pin(review_path))
        env_path=self.root/'environment.json';env_path.write_text(json.dumps(environment))
        state=self.root/'state';state.mkdir()
        request.update(environment=str(env_path),state=str(state))
        request_path=self.root/'adapter-request.json';request_path.write_text(json.dumps(request))
        cmd=[sys.executable,'-I',str(Path(adapter.__file__).resolve()),'--check-config',str(request_path)]
        result=subprocess.run(cmd,capture_output=True,text=True);self.assertEqual(result.returncode,0,result.stderr)
        review['effective_compile_argv']=['changed']
        with self.assertRaisesRegex(RuntimeError,'missing_config_graph_review'):adapter.config_contract(request,environment,review,roots)
        review['effective_compile_argv']=self.packet['effective_argv']
        Path(other['receipt']).write_text('{}')
        with self.assertRaisesRegex(RuntimeError,'stale_pinned_file'):adapter.config_contract(request,environment,review,roots)

    def test_malicious_top_level_configuration_never_starts(self):
        evil=self.root/'evil-sentinel';config=self.repo/'configure.py'
        config.write_text(config.read_text()+f"\nPath({str(evil)!r}).touch()\n")
        self.git('commit','-qam','malicious top level');head=self.git('rev-parse','HEAD');tree=self.git('rev-parse','HEAD^{tree}')
        candidate=self.git('commit-tree',tree,'-p',self.target,'-p',head,'-m','malicious merge');self.git('checkout','--detach',candidate)
        pr=copy.deepcopy(self.pr);pr['head']=head;pr['review']['head']=head
        commits=[{'pr':1,'head':head,'commit':candidate,'tree':tree}]
        self.packet.update(candidate=candidate,tree=tree)
        self.packet['prs']=[{'number':1,'head':head,'base_sha':self.target,'review_base':self.target,
                             'review':{'path':pr['review']['path'],'sha256':pr['review']['sha256']}}]
        for item in (self.packet['steps'][0],self.packet['cumulative']):item['after']=candidate
        self.write_packet()
        plan={'packet_sha256':self.pin(self.packet_file)['sha256'],'target':self.target,'candidate':candidate,'tree':tree,'effective_argv':self.packet['effective_argv']}
        self.plan_output.write_text(json.dumps(plan))
        req=dict(self.request,packet=self.pin(self.packet_file),candidate=candidate,tree=tree,prs=[pr],commits=commits,plan_receipt=self.pin(self.plan_output))
        with patch.object(p,'DOL_SHA1',self.original_sha1), self.assertRaises(ValueError):
            p.prepare(req,str(self.checker),self.pin(self.checker)['sha256'],lock_path=self.lock)
        self.assertFalse(evil.exists());self.assertFalse(self.marker.exists());self.assertFalse(Path(req['receipt']).exists())

    def test_changed_packet_or_source_prevents_execution(self):
        for case in ('packet','source'):
            with self.subTest(case=case):
                if case=='packet':self.packet_file.write_text('{}')
                else:(self.repo/'configure.py').write_text('malicious')
                with self.assertRaises((ValueError,subprocess.CalledProcessError)):self.run_prep()
                self.assertFalse(self.marker.exists())
                if case=='packet':self.write_packet()
                else:self.git('checkout','--','configure.py')
    def test_changed_inputs_while_waiting_on_lock_never_execute(self):
        targets={'tool':self.tool, 'checker':self.checker, 'launcher':self.launcher, 'packet':self.packet_file, 'source-review':self.review,
                 'configuration':self.repo/'configure.py', 'original':self.repo/'orig/GPOE8P/files/PsoV3.dol'}
        for name,path in targets.items():
            with self.subTest(name=name):
                ready=threading.Event();errors=[];orig=fcntl.flock;saved=path.read_bytes()
                def observed(fd,operation):
                    if operation==fcntl.LOCK_EX:ready.set()
                    return orig(fd,operation)
                with self.lock.open('a') as held:
                    orig(held,fcntl.LOCK_EX)
                    with patch.object(p.fcntl,'flock',side_effect=observed), patch.object(p,'DOL_SHA1',self.original_sha1):
                        def worker():
                            try:p.prepare(self.request,str(self.checker),self.pin(self.checker)['sha256'],lock_path=self.lock)
                            except Exception as exc:errors.append(exc)
                        thread=threading.Thread(target=worker);thread.start()
                        self.assertTrue(ready.wait(5));path.write_bytes(saved+b'changed')
                        orig(held,fcntl.LOCK_UN);thread.join(5)
                self.assertFalse(thread.is_alive());self.assertTrue(errors);self.assertFalse(self.marker.exists());self.assertFalse(Path(self.request['receipt']).exists())
                path.write_bytes(saved)

    def test_assume_unchanged_source_and_header_drift_are_rejected(self):
        for name in ('src/unit.cpp','include/unit.h'):
            with self.subTest(name=name):
                self.git('update-index','--assume-unchanged',name)
                path=self.repo/name;saved=path.read_bytes();path.write_bytes(saved+b'drift')
                self.assertEqual(self.git('status','--porcelain','--untracked-files=all'),'')
                with self.assertRaises(ValueError):self.run_prep()
                self.assertFalse(self.marker.exists())
                path.write_bytes(saved);self.git('update-index','--no-assume-unchanged',name)

    def test_ignored_header_in_source_tree_rejected(self):
        hidden=self.repo/'include/hidden.h';hidden.write_text('malicious')
        (self.repo/'.git/info/exclude').write_text('include/hidden.h\n')
        with self.assertRaisesRegex(ValueError,'unexpected ignored input'):self.run_prep()
        self.assertFalse(self.marker.exists())

    def test_hidden_python_module_and_dirty_closure_rejected_before_execution(self):
        hidden=self.repo/'tools/__pycache__/malicious.pyc';hidden.parent.mkdir(parents=True);hidden.write_bytes(b'fixture')
        # Make it ignored to exercise the ignored-file audit explicitly.
        (self.repo/'.git/info/exclude').write_text('tools/__pycache__/\n')
        with self.assertRaises(ValueError):self.run_prep()
        self.assertFalse(self.marker.exists())


if __name__=='__main__':unittest.main()
