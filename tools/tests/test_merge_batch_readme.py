import copy
import importlib.util
from pathlib import Path
import unittest

SCRIPT = Path(__file__).resolve().parents[1] / 'merge_batch_readme.py'
spec = importlib.util.spec_from_file_location('readme_renderer', SCRIPT)
r = importlib.util.module_from_spec(spec); spec.loader.exec_module(r)
README = Path(__file__).resolve().parents[2] / 'README.md'

def report():
    return {'measures': {'total_code': 10, 'matched_code': 5, 'complete_code': 4,
            'total_data': 10, 'matched_data': 5, 'complete_data': 4,
            'total_functions': 10, 'matched_functions': 5, 'total_units': 2, 'complete_units': 1},
            'units': [{}, {}]}

def inputs(): return {'ordered_inputs_sha256': 'a'*64, 'source_inputs': 1, 'fallback_inputs': 1}

class Renderer(unittest.TestCase):
    def setUp(self):
        self.a=report(); self.b=copy.deepcopy(self.a); self.i=inputs(); self.readme=README.read_text()
    def render(self): return r.render(self.readme,self.a,self.b,self.i,self.i,'a'*40,1793476000)
    def test_no_improvement_preserves_every_byte(self): self.assertEqual(self.render(),self.readme)
    def test_exact_counts_link_distinction_and_rounding(self):
        self.b['measures']['matched_code']=6
        output=self.render(); self.assertIn('60.00% (6 of 10)',output); self.assertIn('40.00% (4 of 10)',output)
        self.assertIn('validated source commit', output); self.assertIn('1 original-object fallback',output)
        self.assertEqual(output.split('<!-- progress-table -->')[0],self.readme.split('<!-- progress-table -->')[0])
        self.assertEqual(output.split('\n## Target\n')[1],self.readme.split('\n## Target\n')[1])
        self.assertEqual(r.pct(1, 32),'3.13%')
        self.assertEqual(r.render(output,self.a,self.b,self.i,self.i,'a'*40,1793476000),output)
    def test_reject_bad_metrics_and_inputs(self):
        for field,value in [('total_code',0),('matched_code',11),('matched_data',True),('total_units',3)]:
            b=copy.deepcopy(self.b);b['measures'][field]=value
            with self.subTest(field=field),self.assertRaises((ValueError,KeyError)):r.render(self.readme,self.a,b,self.i,self.i,'a'*40,1793476000)
        bad=dict(self.i, fallback_inputs=0)
        with self.assertRaises(ValueError):r.render(self.readme,self.a,self.b,self.i,bad,'a'*40,1793476000)
    def test_reject_ambiguous_and_malicious_progress(self):
        for text in (self.readme.replace('<!-- progress-table -->','<!-- progress-table -->\n<!-- progress-table -->'), self.readme.replace('A function is matched','<script>bad</script>\nA function is matched'),self.readme.replace('94.56%', '<script>bad</script>'),self.readme.replace('## Target','## Other')):
            with self.subTest(),self.assertRaises(ValueError):r.render(text,self.a,self.b,self.i,self.i,'a'*40,1793476000)

if __name__ == '__main__': unittest.main()
