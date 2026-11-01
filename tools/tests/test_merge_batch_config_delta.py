"""Pure static checks only; does not authorize configuration execution."""
import ast
import copy
import hashlib
import json
import shlex
import subprocess
import tempfile
from pathlib import Path
import unittest
from unittest.mock import patch
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
    def test_player_profile_is_separate_and_preserves_caller(self):
        player=(b'    # fixture player compiler\n'
                b'    "pso/player/TObjPlayer_802D5B78.cpp": {"mw_version": "GC/1.3.2"},\n')
        candidate=self.add(player)
        result=c.check(self.base,candidate,c.PLAYER_UNIT)
        self.assertEqual((result['unit'],result['old_profile'],result['new_profile']),
                         (c.PLAYER_UNIT,'absent','gc132-default-flags'))
        with self.assertRaises(ValueError):c.check(self.base,candidate,c.UNIT)
        cases=[candidate.replace(b'GC/1.3.2',b'GC/1.3.2r'),
               candidate.replace(b'TObjPlayer_802D5B78.cpp',b'TObjPlayer_802D5174.cpp'),
               candidate.replace(b'{"mw_version":',b'{"cflags": [], "mw_version":'),
               candidate.replace(b'"GC/1.3.2"',b'__import__("os").getcwd()'),
               candidate.replace(b'GAME_COMPILER = "GC/2.6"',b'GAME_COMPILER = "GC/1.3.2"'),
               candidate.replace(player,player+player),
               candidate.replace(player,player+b'    "pso/player/TObjPlayer_802D5174.cpp": {"mw_version": "GC/1.3.2"},\n'),
               self.add(player+self.one)]
        for altered in cases:
            with self.subTest(altered=altered[:80]),self.assertRaises((ValueError,SyntaxError)):
                c.check(self.base,altered,c.PLAYER_UNIT)

    def test_darkfalz_exact_reviewed_blobs_and_adversarial_profiles(self):
        base=subprocess.check_output(['git','show','1f86b6699d129d93d5c2b81c16883600b42ef803:configure.py'])
        self.assertEqual(hashlib.sha256(base).hexdigest(),'3db524955b1840a4f896168a0df5d3df6ed839211f7145b155fa2e143eb64eaf')
        entry=(b'    # Source-file sections put the native initializer before its shared helpers.\n'
               b'    "pso/boss/TBoss4DarkFalz_8004C93C.cpp": {"cflags": _switch(cflags_pso, "-inline deferred", "-sym on")},\n')
        marker=b'GAME_EXCEPTIONS: Dict[str, Dict[str, Any]] = {\n'
        after=base.replace(marker,marker+entry)
        self.assertEqual(hashlib.sha256(after).hexdigest(),'d75b6ce618d66ea7e8bf5b451904e5f5b24ab983b5626aaf538d4a59327da27c')
        result=c.check(base,after,c.DARKFALZ_UNIT)
        self.assertEqual((result['old_profile'],result['new_profile']),('absent','gc26-deferred-sym-on'))
        self.assertEqual(c.shape(base,c.DARKFALZ_UNIT)['outside'],c.shape(after,c.DARKFALZ_UNIT)['outside'])
        cases=[after.replace(b'-sym on',b'-sym off'),after.replace(b'-inline deferred',b'-inline off,deferred'),
               after.replace(b'-inline deferred',b'-inline auto'),after.replace(b'"-inline deferred", "-sym on"',b'"-sym on", "-inline deferred"'),
               after.replace(b'"-sym on"',b'"-sym on", "-sym on"'),after.replace(b'"-sym on"',b'"-sdata 4", "-sym on"'),
               after.replace(b'{"cflags": _switch(cflags_pso, "-inline deferred", "-sym on")}',b'{"mw_version": "GC/2.0", "cflags": _switch(cflags_pso, "-inline deferred", "-sym on")}'),
               after.replace(b'{"cflags": _switch(cflags_pso, "-inline deferred", "-sym on")}',b'{"drop": True}'),
               after.replace(b'-sym on',b'-sym on\x00'),after.replace(entry,entry+entry),
               after.replace(b'GAME_COMPILER = "GC/2.6"',b'GAME_COMPILER = "GC/2.0"'),
               after.replace(entry,entry+b'    "other.cpp": {"cflags": []},\n'),
               after.replace(b'TBoss4DarkFalz_8004C93C.cpp',b'TBoss4DarkFalz_other.cpp'),
               after.replace(b'"-sym on"',b'computed()'),after+b'# unrelated\n']
        for bad in cases:
            with self.subTest(bad=hashlib.sha256(bad).hexdigest()[:12]),self.assertRaises((ValueError,SyntaxError,UnicodeError)):
                c.check(base,bad,c.DARKFALZ_UNIT)
        with self.assertRaises(ValueError):c.check(after,base,c.DARKFALZ_UNIT)
        with self.assertRaises(ValueError):c.check(after,after,c.DARKFALZ_UNIT)

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
        self.pr={'number':1,'head':self.head,'base_sha':self.target,'review_base':self.target,'review':dict(pin,verdict='pass',independent=True,reviewer='fixture',head=self.head,base=self.target)}
        self.commits=[{'pr':1,'head':self.head,'commit':self.candidate,'tree':self.tree}]
        change=c.step(self.repo,self.target,self.candidate)
        tool_dir=self.root/'tools-dir'; tool_dir.mkdir(); (tool_dir/'tool').write_text('fixture')
        entries=[['tool',hashlib.sha256((tool_dir/'tool').read_bytes()).hexdigest(),(tool_dir/'tool').stat().st_mode & 0o777]]
        dir_pin={'path':str(tool_dir),'sha256':c.tree_digest(tool_dir)}
        self.packet={'version':1,'repository':c.REPO,'policy':'recovery','target':self.target,
                     'candidate':self.candidate,'tree':self.tree,'prs':[{'number':1,'head':self.head,'base_sha':self.target,'review_base':self.target,'review':{'path':self.pr['review']['path'],'sha256':self.pr['review']['sha256']}}],'steps':[change],
                     'cumulative':change,'pins':{name:({'path':str(tool_dir/'tool'),'sha256':hashlib.sha256((tool_dir/'tool').read_bytes()).hexdigest()} if name=='compiler' else pin.copy()) for name in c.PIN_NAMES},
                     'effective_argv':[str(self.review),str(tool_dir/'tool'),'-inline','off,deferred','-c','src/'+c.UNIT],
                     'configure_paths':{name:(dir_pin if name in ('compilers','binutils') else pin) for name in ('dtk','objdiff','wrapper','compilers','binutils')},
                     'originals':{role:{'tree_sha256':'a'*64,'dol_sha256':'b'*64} for role in ('baseline','candidate')},
                     'dependent_compile':[], 'ordered_inputs':{role:{'ordered_inputs_sha256':'c'*64,'source_inputs':1,'fallback_inputs':0} for role in ('baseline','candidate')},
                     'verdict':'pass','independent':True,'reviewer':'fixture reviewer'}
        self.file=self.root/'packet.json';self.write()
    def git(self,*args):
        return subprocess.check_output(['git','-C',str(self.repo),*args],stderr=subprocess.DEVNULL,text=True).strip()
    def write(self):
        self.file.write_text(json.dumps(self.packet));return {'path':str(self.file),'sha256':hashlib.sha256(self.file.read_bytes()).hexdigest()}
    def test_plan_accepts_exact_reviewed_blobs(self):
        p=c.read_packet(self.write(),[self.repo]);result=c.verify_plan(self.repo,p,self.target,self.candidate,self.tree,[self.pr],self.commits)
        self.assertEqual(result['candidate'],self.candidate)
    def test_player_packet_requires_exact_compiler_and_caller_graph_profile(self):
        self.git('checkout','-B','player',self.target)
        path=self.repo/'configure.py'
        before=path.read_bytes()+b'GAME_COMPILER = "GC/2.6"\n';path.write_bytes(before);self.git('commit','-qam','player baseline')
        target=self.git('rev-parse','HEAD')
        player=b'    "pso/player/TObjPlayer_802D5B78.cpp": {"mw_version": "GC/1.3.2"},\n'
        path.write_bytes(before.replace(b'    "other.cpp"',player+b'    "other.cpp"'))
        self.git('commit','-qam','player profile');head=self.git('rev-parse','HEAD');tree=self.git('rev-parse','HEAD^{tree}')
        candidate=self.git('commit-tree',tree,'-p',target,'-p',head,'-m','player merge');self.git('checkout','--detach',candidate)
        tool_dir=Path(self.packet['configure_paths']['compilers']['path']);caller=tool_dir/'caller';caller.write_text('caller compiler')
        entries=[[p.name,hashlib.sha256(p.read_bytes()).hexdigest(),p.stat().st_mode & 0o777] for p in sorted(tool_dir.iterdir())]
        self.packet['configure_paths']['compilers']['sha256']=c.tree_digest(tool_dir)
        caller_pin={'path':str(caller),'sha256':hashlib.sha256(caller.read_bytes()).hexdigest()}
        wrapper=self.packet['pins']['compiler_wrapper']['path'];target_compiler=self.packet['pins']['compiler']
        flags=['-O4,s','-inline','off','-sdata2','4']
        self.packet['effective_argv']=[wrapper,target_compiler['path'],*flags,'-c','src/'+c.PLAYER_UNIT]
        self.packet['dependent_compile']=[{'unit':c.PLAYER_CALLER,'compiler':caller_pin,'argv':[wrapper,caller_pin['path'],*flags,'-c','src/'+c.PLAYER_CALLER]}]
        pr=copy.deepcopy(self.pr);pr.update(head=head,base_sha=target,review_base=target);pr['review'].update(head=head,base=target)
        commits=[{'pr':1,'head':head,'commit':candidate,'tree':tree}]
        change=c.step(self.repo,target,candidate,c.PLAYER_UNIT)
        self.packet.update(target=target,candidate=candidate,tree=tree,steps=[change],cumulative=change,
                           prs=[{'number':1,'head':head,'base_sha':target,'review_base':target,'review':{'path':pr['review']['path'],'sha256':pr['review']['sha256']}}])
        with patch.object(c,'PLAYER_COMPILER_SHA256',target_compiler['sha256']),patch.object(c,'CALLER_COMPILER_SHA256',caller_pin['sha256']):
            packet=c.read_packet(self.write(),[self.repo]);c.verify_plan(self.repo,packet,target,candidate,tree,[pr],commits)
            self.packet['dependent_compile'][0]['argv'][1]=target_compiler['path']
            with self.assertRaises(ValueError):c.read_packet(self.write(),[self.repo])
            self.packet['dependent_compile'][0]['argv'][1]=caller_pin['path']
            self.packet['pins']['compiler']['sha256']='f'*64
            with self.assertRaises(ValueError):c.read_packet(self.write(),[self.repo])

    def test_darkfalz_packet_binds_reviewed_profile_compiler_and_full_argv(self):
        self.git('checkout','-B','dark',self.target)
        path=self.repo/'configure.py';before=path.read_bytes()+b'GAME_COMPILER = "GC/2.6"\n'
        path.write_bytes(before);self.git('commit','-qam','baseline');target=self.git('rev-parse','HEAD')
        entry=b'    "pso/boss/TBoss4DarkFalz_8004C93C.cpp": {"cflags": _switch(cflags_pso, "-inline deferred", "-sym on")},\n'
        path.write_bytes(before.replace(b'    "other.cpp"',entry+b'    "other.cpp"'))
        self.git('commit','-qam','candidate');head=self.git('rev-parse','HEAD');tree=self.git('rev-parse','HEAD^{tree}')
        candidate=self.git('commit-tree',tree,'-p',target,'-p',head,'-m','candidate merge');self.git('checkout','--detach',candidate)
        change=c.step(self.repo,target,candidate,c.DARKFALZ_UNIT)
        pr=copy.deepcopy(self.pr);pr.update(head=head,base_sha=target,review_base=target);pr['review'].update(head=head,base=target)
        commits=[{'pr':1,'head':head,'commit':candidate,'tree':tree}]
        self.packet.update(target=target,candidate=candidate,tree=tree,steps=[change],cumulative=change,
            prs=[{'number':1,'head':head,'base_sha':target,'review_base':target,'review':{'path':pr['review']['path'],'sha256':pr['review']['sha256']}}])
        compiler=self.packet['pins']['compiler'];wrapper=self.packet['pins']['compiler_wrapper']['path']
        self.packet['effective_argv']=[wrapper,compiler['path'],'-O4,s','-inline','deferred','-sdata2','4','-sym','on','-c','src/'+c.DARKFALZ_UNIT]
        with patch.object(c,'CALLER_COMPILER_SHA256',compiler['sha256']):
            packet=c.read_packet(self.write(),[self.repo]);c.verify_plan(self.repo,packet,target,candidate,tree,[pr],commits)
            original=copy.deepcopy(self.packet)
            for field in ('target','candidate','tree'):
                bad=copy.deepcopy(packet);bad[field]='f'*40
                with self.subTest(field=field),self.assertRaises(ValueError):c.verify_plan(self.repo,bad,target,candidate,tree,[pr],commits)
            self.packet['pins']['compiler']['sha256']='f'*64
            with self.assertRaises(ValueError):c.read_packet(self.write(),[self.repo])
            self.packet=copy.deepcopy(original);self.packet['configure_paths']['compilers']['sha256']='f'*64
            with self.assertRaises(ValueError):c.read_packet(self.write(),[self.repo])
            self.packet=copy.deepcopy(original);self.packet['pins']['compiler_wrapper']['sha256']='f'*64
            with self.assertRaises(ValueError):c.read_packet(self.write(),[self.repo])
            self.packet=copy.deepcopy(original);self.packet['dependent_compile']=[{'unit':'other'}]
            with self.assertRaises(ValueError):c.read_packet(self.write(),[self.repo])
            self.packet=copy.deepcopy(original);self.packet['steps'][0]['unit']=c.UNIT
            with self.assertRaises(ValueError):c.read_packet(self.write(),[self.repo])
            self.packet=copy.deepcopy(original);self.review.write_text('stale review')
            with self.assertRaises(ValueError):c.read_packet(self.write(),[self.repo])

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
    def test_checkout_attributes_are_rejected_before_candidate_checkout(self):
        path=self.repo/'.gitattributes';path.write_text('*.cpp filter=unsafe\n')
        self.git('add','.gitattributes');self.git('commit','-qm','unreviewed checkout attributes')
        head=self.git('rev-parse','HEAD');tree=self.git('rev-parse','HEAD^{tree}')
        candidate=self.git('commit-tree',tree,'-p',self.target,'-p',head,'-m','candidate merge')
        pr=copy.deepcopy(self.pr);pr['head']=head;pr['review']['head']=head
        commits=[{'pr':1,'head':head,'commit':candidate,'tree':tree}]
        packet=copy.deepcopy(self.packet);packet.update(candidate=candidate,tree=tree)
        packet['prs']=[{'number':1,'head':head,'base_sha':self.target,'review_base':self.target,
                        'review':{'path':pr['review']['path'],'sha256':pr['review']['sha256']}}]
        change=c.step(self.repo,self.target,candidate);packet['steps']=[change];packet['cumulative']=change
        with self.assertRaisesRegex(ValueError,'checkout attributes'):c.verify_plan(self.repo,packet,self.target,candidate,tree,[pr],commits)

    def test_prerequisite_and_source_review_binding_rejected(self):
        for change in ('base_sha','review_head','duplicate_pr'):
            prs=copy.deepcopy([self.pr]);commits=copy.deepcopy(self.commits)
            if change=='base_sha':prs[0]['base_sha']='f'*40
            elif change=='review_head':prs[0]['review']['head']='f'*40
            else:prs.append(copy.deepcopy(prs[0]));commits.append(copy.deepcopy(commits[0]))
            with self.subTest(change=change),self.assertRaises((ValueError,subprocess.CalledProcessError)):
                c.verify_plan(self.repo,self.packet,self.target,self.candidate,self.tree,prs,commits)

    def test_changed_config_mode_and_symlink_rejected(self):
        for case in ('mode','symlink'):
            self.git('checkout','-B','bad-'+case,self.target)
            path=self.repo/'configure.py'
            if case=='mode':path.chmod(0o644)
            else:path.unlink();path.symlink_to('other.py')
            self.git('add','configure.py');self.git('commit','-qm','invalid mode');head=self.git('rev-parse','HEAD')
            with self.subTest(case=case),self.assertRaises(ValueError):c.step(self.repo,self.target,head)

    def test_tool_pin_and_response_file_injection_rejected(self):
        for value in ('@unreviewed','-I../../escape','shell;command','safe\\evil'):
            self.packet['effective_argv'].append(value)
            with self.subTest(value=value),self.assertRaises(ValueError):c.read_packet(self.write(),[self.repo])
            self.packet['effective_argv'].pop()
        self.packet['pins']['launcher']['sha256']='f'*64
        with self.assertRaises(ValueError):c.read_packet(self.write(),[self.repo])

class DarkFalzRealGraphTests(unittest.TestCase):
    def setUp(self):
        from tools.tests.test_merge_batch_config_prepare import discover_test_ninja
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup)
        self.root=Path(self.tmp.name);self.ninja=discover_test_ninja()
        self.argv=['/wrapper','/compiler26','-O4,s','-inline','deferred','-sdata2','4','-sym','on','-c','src/'+c.DARKFALZ_UNIT]
        self.packet={'cumulative':{'unit':c.DARKFALZ_UNIT},'effective_argv':self.argv,'dependent_compile':[],
                     'pins':{'ninja':{'path':str(self.ninja),'sha256':hashlib.sha256(self.ninja.read_bytes()).hexdigest()}}}
    def graph(self,root,argv,duplicate=False):
        root.mkdir(exist_ok=True)
        text='rule mwcc\n  command = '+shlex.join(argv)+' && true\nbuild output.o: mwcc src/'+c.DARKFALZ_UNIT+'\n'
        if duplicate:text+='build output2.o: mwcc src/'+c.DARKFALZ_UNIT+'\n'
        (root/'build.ninja').write_text(text)
    def test_actual_ninja_baseline_and_candidate_commands(self):
        candidate=self.root/'candidate';baseline=self.root/'baseline'
        self.graph(candidate,self.argv);self.graph(baseline,c.darkfalz_baseline_argv(self.argv))
        c.check_compile_graph(candidate,self.packet,'candidate');c.check_compile_graph(baseline,self.packet,'baseline')
        for root,role,argv in ((candidate,'candidate',self.argv),(baseline,'baseline',c.darkfalz_baseline_argv(self.argv))):
            for altered in (argv+['-sym','on'],argv[:-1]+['src/wrong.cpp'],[('/wrong' if x=='/compiler26' else x) for x in argv]):
                self.graph(root,altered)
                with self.assertRaises(ValueError):c.check_compile_graph(root,self.packet,role)
            self.graph(root,argv,duplicate=True)
            with self.assertRaises(ValueError):c.check_compile_graph(root,self.packet,role)
            self.graph(root,argv)
    def test_darkfalz_argv_rejects_conflicts(self):
        c.require_compile_argv(self.argv,c.DARKFALZ_UNIT,'/wrapper','/compiler26','deferred')
        reordered=self.argv[:2]+['-sym','on','-O4,s','-inline','deferred','-sdata2','4','-c','src/'+c.DARKFALZ_UNIT]
        cases=[reordered,self.argv+['-sym','on'],self.argv+['-sdata','4'],self.argv+['-O0'],self.argv+['-sdata2=8'],self.argv+['-g'],
               [x for x in self.argv if x!='-sym'],[('off' if x=='on' else x) for x in self.argv],
               [('off,deferred' if x=='deferred' else x) for x in self.argv]]
        for argv in cases:
            with self.subTest(argv=argv),self.assertRaises(ValueError):c.require_compile_argv(argv,c.DARKFALZ_UNIT,'/wrapper','/compiler26','deferred')


class CompileGraphTests(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup)
        self.root=Path(self.temp.name);self.repo=self.root/'repo';self.repo.mkdir();(self.repo/'build.ninja').write_text('fixture')
        self.ninja=self.root/'ninja'
        target=['/wrapper','/compiler132','-O4,s','-inline','off','-sdata2','4','-c','src/'+c.PLAYER_UNIT]
        caller=['/wrapper','/compiler26','-O4,s','-inline','off','-sdata2','4','-c','src/'+c.PLAYER_CALLER]
        self.rows=[{'file':'src/'+c.PLAYER_UNIT,'command':shlex.join(target)+' && safe-tail'},
                   {'file':'src/'+c.PLAYER_CALLER,'command':shlex.join(caller)+' && safe-tail'}]
        self.packet={'cumulative':{'unit':c.PLAYER_UNIT},'effective_argv':target,
                     'dependent_compile':[{'unit':c.PLAYER_CALLER,'argv':caller}]}
        self.write_ninja()
    def write_ninja(self):
        self.ninja.write_text('#!/usr/bin/python3\nimport json\nprint('+repr(json.dumps(self.rows))+')\n');self.ninja.chmod(0o755)
        self.packet['pins']={'ninja':{'path':str(self.ninja),'sha256':hashlib.sha256(self.ninja.read_bytes()).hexdigest()}}
    def test_candidate_and_baseline_caller_graphs_must_match(self):
        c.check_compile_graph(self.repo,self.packet,'candidate')
        c.check_compile_graph(self.repo,self.packet,'baseline')
        self.rows[1]['command']=self.rows[1]['command'].replace('/compiler26','/compiler132');self.write_ninja()
        with self.assertRaisesRegex(ValueError,'compile argv differs'):c.check_compile_graph(self.repo,self.packet,'candidate')
        with self.assertRaisesRegex(ValueError,'compile argv differs'):c.check_compile_graph(self.repo,self.packet,'baseline')
    def test_duplicate_or_missing_edges_fail(self):
        self.rows.append(copy.deepcopy(self.rows[1]));self.write_ninja()
        with self.assertRaisesRegex(ValueError,'unique compile edge'):c.check_compile_graph(self.repo,self.packet,'candidate')
        self.rows=[];self.write_ninja()
        with self.assertRaisesRegex(ValueError,'unique compile edge'):c.check_compile_graph(self.repo,self.packet,'candidate')

if __name__=='__main__': unittest.main()
