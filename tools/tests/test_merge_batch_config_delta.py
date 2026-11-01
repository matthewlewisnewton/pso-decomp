"""Pure static checks only; does not authorize configuration execution."""
import ast
import copy
import hashlib
import json
import subprocess
import tempfile
from pathlib import Path
import unittest
from tools import merge_batch_config_delta as c


class StaticConfigDelta(unittest.TestCase):
    def setUp(self):
        self.base = (b'from typing import Dict, Any\n'
                     b'GAME_EXCEPTIONS: Dict[str, Dict[str, Any]] = {\n'
                     b'    "other.cpp": {"cflags": []},\n}\n'
                     b'GAME_COMPILER = "GC/2.6"\n')
        self.one = (b'    # review comment\n'
                    b'    "pso/misc/TOTrapAncient01.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},\n')
        self.two = (b'    # review comment\n    # second comment\n'
                    b'    "pso/misc/TOTrapAncient01.cpp": {"mw_version": "GC/2.0", "cflags": _switch(cflags_pso, "-inline off,deferred")},\n')
    def add(self, entry):
        return self.base.replace(b'    "other.cpp"', entry + b'    "other.cpp"')
    def test_three_closed_transitions(self):
        one,two=self.add(self.one),self.add(self.two)
        for before,after,want in ((self.base,one,('absent','gc26-deferred')),
                                  (one,two,('gc26-deferred','gc20-deferred')),
                                  (self.base,two,('absent','gc20-deferred'))):
            result=c.check(before,after)
            self.assertEqual((result['old_profile'],result['new_profile']),want)
            self.assertEqual(result['unit'],c.UNIT)
    def test_reject_unreviewed_changes_and_malformed_code(self):
        one,two=self.add(self.one),self.add(self.two)
        bad=[self.base, one+b'open("/tmp/sentinel", "w")\n',
             one.replace(b'GC/2.6',b'GC/2.0'),
             one.replace(b'off,deferred',b'off,deferred -i /tmp/evil'),
             two.replace(b'GC/2.0',b'../../malicious'),
             two.replace(b'"GC/2.0"',b'__import__("os").getcwd()'),
             one.replace(b'"other.cpp"',b'"pso/misc/TOTrapAncient01.cpp"'),
             one.replace(b'"cflags":',b'"cflags": 1, "cflags":'),
             one.replace(b'_switch(cflags_pso,',b'_switch(cflags_pso, "-sdata 4",'),
             one.replace(b'other.cpp',b'../other.cpp'),one.replace(b'\n',b'\r\n'),
             one.replace(b'    # review',b'\x0c    # review'),
             one.replace(b'    # review',b'    # \xc2\x85review'),
             one.replace(b'    "other.cpp"',b'    **malicious,\n    "other.cpp"')]
        for after in bad:
            with self.subTest(after=after[:70]), self.assertRaises((ValueError,SyntaxError,UnicodeError)):
                c.check(self.base,after)
        with self.assertRaises(ValueError): c.check(two,one)
        with self.assertRaises(ValueError): c.check(one,self.base)

class PacketTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup)
        self.root=Path(self.tmp.name);self.repo=self.root/'repo';self.repo.mkdir()
        self.git('init','-q');self.git('config','user.name','fixture');self.git('config','user.email','fixture@localhost')
        before=(b'from typing import Dict, Any\nGAME_EXCEPTIONS: Dict[str, Dict[str, Any]] = {\n'
                b'    "other.cpp": {"cflags": []},\n}\n')
        after=before.replace(b'    "other.cpp"',b'    "pso/misc/TOTrapAncient01.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},\n    "other.cpp"')
        path=self.repo/'configure.py';path.write_bytes(before);path.chmod(0o755)
        self.git('add','configure.py');self.git('commit','-qm','base');self.target=self.git('rev-parse','HEAD')
        path.write_bytes(after);self.git('commit','-qam','candidate');self.head=self.git('rev-parse','HEAD')
        self.tree=self.git('rev-parse','HEAD^{tree}')
        self.candidate=self.git('commit-tree',self.tree,'-p',self.target,'-p',self.head,'-m','candidate merge')
        self.git('checkout','--detach',self.candidate)
        self.review=self.root/'source-review.json';self.review.write_text('{}')
        pin={'path':str(self.review),'sha256':hashlib.sha256(self.review.read_bytes()).hexdigest()}
        self.pr={'number':1,'head':self.head,'review_base':self.target,'review':pin}
        self.commits=[{'pr':1,'head':self.head,'commit':self.candidate,'tree':self.tree}]
        change=c.step(self.repo,self.target,self.candidate)
        tool_dir=self.root/'tools-dir'; tool_dir.mkdir(); (tool_dir/'tool').write_text('fixture')
        entries=[['tool',hashlib.sha256((tool_dir/'tool').read_bytes()).hexdigest(),(tool_dir/'tool').stat().st_mode & 0o777]]
        dir_pin={'path':str(tool_dir),'sha256':hashlib.sha256(json.dumps(entries,separators=(',',':')).encode()).hexdigest()}
        self.packet={'version':1,'repository':c.REPO,'policy':'recovery','target':self.target,
                     'candidate':self.candidate,'tree':self.tree,'prs':[{k:self.pr[k] for k in ('number','head','review_base','review')}],'steps':[change],
                     'cumulative':change,'pins':{name:({'path':str(tool_dir/'tool'),'sha256':hashlib.sha256((tool_dir/'tool').read_bytes()).hexdigest()} if name=='compiler' else pin.copy()) for name in c.PIN_NAMES},
                     'effective_argv':[str(self.review),str(tool_dir/'tool'),'-inline','off,deferred'],
                     'configure_paths':{name:(dir_pin if name in ('compilers','binutils') else pin) for name in ('dtk','objdiff','wrapper','compilers','binutils')},
                     'originals':{role:{'tree_sha256':'a'*64,'dol_sha256':'b'*64} for role in ('baseline','candidate')},
                     'ordered_inputs':{role:{'ordered_inputs_sha256':'c'*64,'source_inputs':1,'fallback_inputs':0} for role in ('baseline','candidate')},
                     'verdict':'pass','independent':True,'reviewer':'fixture reviewer'}
        self.file=self.root/'packet.json';self.write()
    def git(self,*args):
        return subprocess.check_output(['git','-C',str(self.repo),*args],stderr=subprocess.DEVNULL,text=True).strip()
    def write(self):
        self.file.write_text(json.dumps(self.packet));return {'path':str(self.file),'sha256':hashlib.sha256(self.file.read_bytes()).hexdigest()}
    def test_plan_accepts_exact_reviewed_blobs(self):
        p=c.read_packet(self.write(),[self.repo]);result=c.verify_plan(self.repo,p,self.target,self.candidate,self.tree,[self.pr],self.commits)
        self.assertEqual(result['candidate'],self.candidate)
    def test_duplicate_unknown_or_stale_packet_rejected(self):
        raw=self.file.read_text();self.file.write_text(raw[:-1]+',"version":1}')
        pin={'path':str(self.file),'sha256':hashlib.sha256(self.file.read_bytes()).hexdigest()}
        with self.assertRaises(ValueError):c.read_packet(pin,[self.repo])
        self.packet['unknown']='bad'
        with self.assertRaises(ValueError):c.read_packet(self.write(),[self.repo])
        del self.packet['unknown'];pin=self.write();self.file.write_text('{}')
        with self.assertRaises(ValueError):c.read_packet(pin,[self.repo])
    def test_stale_tree_review_blob_and_order_rejected(self):
        for field in ('candidate','tree','target'):
            p=copy.deepcopy(self.packet);p[field]='f'*40
            with self.subTest(field=field),self.assertRaises(ValueError):c.verify_plan(self.repo,p,self.target,self.candidate,self.tree,[self.pr],self.commits)
        p=copy.deepcopy(self.packet);p['steps'][0]['after_blob']='f'*40
        with self.assertRaises(ValueError):c.verify_plan(self.repo,p,self.target,self.candidate,self.tree,[self.pr],self.commits)
        self.review.write_text('stale')
        with self.assertRaises(ValueError):c.read_packet(self.write(),[self.repo])
    def test_tool_pin_and_response_file_injection_rejected(self):
        self.packet['effective_argv'].append('@unreviewed')
        with self.assertRaises(ValueError):c.read_packet(self.write(),[self.repo])
        self.packet['effective_argv'].pop();self.packet['pins']['launcher']['sha256']='f'*64
        with self.assertRaises(ValueError):c.read_packet(self.write(),[self.repo])

if __name__=='__main__': unittest.main()
