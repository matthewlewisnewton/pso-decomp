import copy
import hashlib
import subprocess
import sys
import tempfile
import importlib.util
import json
from pathlib import Path
import unittest

p=Path(__file__).resolve().parents[1] / 'merge_batch_validate_zero_loss.py'
spec=importlib.util.spec_from_file_location('guard',p); g=importlib.util.module_from_spec(spec);spec.loader.exec_module(g)

def unit(name, addr, size, exact=True, linked=True, section='.data', function=False):
    row={'name': name, 'size': size, 'metadata': {'virtual_address':addr}}
    if exact: row['fuzzy_match_percent']=100
    return {'name': name, 'metadata': {'module_name':'psov3','complete':linked}, ('functions' if function else 'sections'):[row]}
def report():
    return {'measures': {k:10 for k in g.METRICS}, 'units':[unit('fn',4096,8,function=True),unit('.text',4096,8,section='.text'),unit('.data',8192,8)]}
def receipt(a,b):
    return {'result':'pass','delta':{**{k:[] for k in g.LOSS_FIELDS},'metrics':{k:{'before':int(a['measures'][k]),'after':int(b['measures'][k]),'delta':int(b['measures'][k])-int(a['measures'][k])} for k in g.METRICS}}}

class GuardTests(unittest.TestCase):
    def check(self,a,b): return g.require_zero_loss(receipt(a,b),a,b)
    def test_clean_and_split_merge_and_gain(self):
        a=report();b=copy.deepcopy(a)
        b['units'][-1:]=[unit('.data',8192,4),unit('.data',8196,4),unit('.data',8200,4)]
        self.assertTrue(self.check(a,b))
        self.assertTrue(self.check(b,b))
    def test_retained_coverage_loses_exact_or_link_status(self):
        for mode in ('exact','link','both'):
            a=report();b=copy.deepcopy(a)
            b['units'][-1:]=[unit('.data',8192,4),unit('.data',8196,4,exact=mode=='link',linked=mode=='exact'),unit('.data',8200,16)]
            b['measures']['matched_data'] += 16; b['measures']['complete_data'] += 16
            with self.subTest(mode=mode), self.assertRaisesRegex(RuntimeError,'raw_range_loss: data_'):
                self.check(a,b)
    def test_each_class_rejects_loss(self):
        for index, group in ((0,'function'),(1,'code'),(2,'data')):
            for mode in ('coverage','exact','linked'):
                a=report();b=copy.deepcopy(a); row=b['units'][index]
                field='functions' if index==0 else 'sections'
                if mode=='coverage': row[field][0]['size']=4
                if mode=='exact': row[field][0].pop('fuzzy_match_percent')
                if mode=='linked': row['metadata']['complete']=False
                with self.subTest(group=group,mode=mode),self.assertRaisesRegex(RuntimeError,'raw_range_loss: '+group+'_'):
                    self.check(a,b)
    def test_function_address_cannot_be_hidden_by_overlap(self):
        a=report();a['units'].append(unit('second',4100,4,function=True));b=copy.deepcopy(a);b['units'].pop()
        with self.assertRaisesRegex(RuntimeError,'raw_range_loss: function_coverage'):self.check(a,b)
    def test_rejects_malformed_and_inconsistent(self):
        a=report()
        for change in ('units','address','size','status','match','measure','metrics','duplicate'):
            b=copy.deepcopy(a); c=receipt(a,b)
            if change=='units': b['units']=[]
            if change=='address': del b['units'][0]['functions'][0]['metadata']['virtual_address']
            if change=='size': b['units'][0]['functions'][0]['size']=-1
            if change=='status': b['units'][0]['metadata']['complete']='yes'
            if change=='match': b['units'][0]['functions'][0]['fuzzy_match_percent']=None
            if change=='measure': del b['measures']['total_code']
            if change=='metrics': c['delta']['metrics']['total_code']['after']=999
            if change=='duplicate': b['units'].append(copy.deepcopy(b['units'][0]))
            with self.subTest(change=change),self.assertRaises((RuntimeError,KeyError,TypeError)):
                g.require_zero_loss(c,a,b)
    def test_filtered_and_future_loss_reject(self):
        a=report();c=receipt(a,a)
        for key in (*g.LOSS_FIELDS,'future_range_lost'):
            d=copy.deepcopy(c);d['delta'][key]=[{'size':4}]
            with self.subTest(key=key),self.assertRaises(RuntimeError):g.require_zero_loss(d,a,a)
    def test_real_subprocess_binding_and_no_output_on_loss(self):
        with tempfile.TemporaryDirectory() as tmp:
            root=Path(tmp); checkout=root/'checkout';checkout.mkdir()
            paths={}
            for role in ('baseline','candidate'):
                paths[role]=root/role
                (paths[role]/'build/GPOE8P').mkdir(parents=True)
            a=report();b=copy.deepcopy(a)
            for role,data in [('baseline',a),('candidate',b)]:
                (paths[role]/'build/GPOE8P/report.json').write_text(json.dumps(data))
            review=root/'review.json'
            review.write_text(json.dumps({'target':'t','candidate':'c','tree':'x','roots':{k:{'path':str(v)} for k,v in paths.items()}}))
            sha=lambda path:hashlib.sha256(path.read_bytes()).hexdigest()
            coverage=root/'coverage.json';coverage.write_text(json.dumps(receipt(a,b)))
            adapter=root/'adapter.py';adapter.write_text('def validate(request):\n return '+repr({'coverage_receipt':str(coverage),'review_sha256':sha(review),'delta':{k:0 for k in g.METRICS}, 'acceptance_builds':{role:{'provenance':{'ordered_inputs_sha256':'a'*64, 'source_inputs':1, 'fallback_inputs':0}} for role in ('baseline','candidate')}})+'\n')
            env=root/'env.json';env.write_text(json.dumps({'strict_loss_guard':{'adapter':{'path':str(adapter),'sha256':sha(adapter)}},'acceptance_capacity':{'review':{'path':str(review),'sha256':sha(review)}}}))
            output=root/'output.json';request=root/'request.json';request.write_text(json.dumps({'environment':str(env),'checkout':str(checkout),'state':str(root),'target':'t','candidate':'c','tree':'x','policy':'source-maintenance','output':str(output)}))
            def run(): return subprocess.run([sys.executable,'-I',str(p),str(request)],cwd=checkout,capture_output=True,text=True)
            marker=root/'shadow';(checkout/'json.py').write_text('open('+repr(str(marker))+',"w").close()')
            proc=run();self.assertEqual(proc.returncode,0,proc.stderr);self.assertTrue(output.exists());self.assertFalse(marker.exists())
            self.assertEqual(json.loads(output.read_text())['coverage_receipt_sha256'],sha(coverage))
            output.unlink()
            original = adapter.read_text(); adapter.write_text(original.replace("'ordered_inputs_sha256': 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa'", "'ordered_inputs_sha256': 'bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb'", 1))
            env_data=json.loads(env.read_text()); env_data['strict_loss_guard']['adapter']['sha256']=sha(adapter); env.write_text(json.dumps(env_data))
            proc=run();self.assertNotEqual(proc.returncode,0);self.assertIn('ordered_link_inputs_changed_or_missing',proc.stderr);self.assertFalse(output.exists())
            adapter.write_text(original);env_data['strict_loss_guard']['adapter']['sha256']=sha(adapter);env.write_text(json.dumps(env_data))
            b['units'][-1]['metadata']['complete']=False
            (paths['candidate']/'build/GPOE8P/report.json').write_text(json.dumps(b))
            proc=run();self.assertNotEqual(proc.returncode,0);self.assertIn('raw_range_loss: data_linked',proc.stderr);self.assertFalse(output.exists())
            (paths['candidate']/'build/GPOE8P/report.json').unlink()
            proc=run();self.assertNotEqual(proc.returncode,0);self.assertFalse(output.exists())
            review.write_text('{}');proc=run();self.assertNotEqual(proc.returncode,0);self.assertFalse(output.exists())

if __name__=='__main__':unittest.main()
