"""Pure static checks only; does not authorize configuration execution."""
import ast
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

if __name__=='__main__': unittest.main()
