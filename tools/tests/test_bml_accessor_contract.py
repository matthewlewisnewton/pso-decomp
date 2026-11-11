"""Source contract checks; native object validation remains a separate gate."""
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[2]
HEADER = 'pso/system/BmlResource.h'


class BmlAccessorContractTests(unittest.TestCase):
    def test_every_consumer_includes_the_canonical_header(self):
        consumers = [p for p in (ROOT / 'src').rglob('*.cpp')
                     if re.search(r'\bget_bml_model\b', p.read_text())]
        self.assertTrue(consumers)
        for path in consumers:
            with self.subTest(path=str(path.relative_to(ROOT))):
                source = path.read_text()
                self.assertIn(f'#include "{HEADER}"', source)
                self.assertNotRegex(source, r'#\s*define\s+get_bml_model\b')

    def test_one_declaration_and_one_definition(self):
        declaration = re.compile(
            r'^\s*(?:extern\s+"C"\s+)?(?:s32|u32|int|void|[A-Z]\w*)\s*\**\s*'
            r'get_bml_model\([^;{}]*\)\s*;', re.MULTILINE)
        declarations = []
        definitions = []
        definition = re.compile(
            r'^NJS_OBJECT\s*\*get_bml_model\(BmlResource\s*\*resource, '
            r's32 index\)\s*\{', re.MULTILINE)
        for directory in ('src', 'include/pso'):
            for path in (ROOT / directory).rglob('*'):
                if path.suffix not in ('.cpp', '.h'):
                    continue
                source = path.read_text()
                declarations.extend([str(path.relative_to(ROOT))]
                                    * len(declaration.findall(source)))
                definitions.extend([str(path.relative_to(ROOT))]
                                   * len(definition.findall(source)))
        self.assertEqual(declarations, ['include/' + HEADER])
        self.assertEqual(definitions, ['src/pso/object/TObjFish_8001ED90.cpp'])
        self.assertIn('extern "C" NJS_OBJECT *get_bml_model(BmlResource *resource, s32 index);',
                      (ROOT / 'include' / HEADER).read_text())

    def test_native_integer_boundaries_remain_explicit(self):
        resource = (ROOT / 'include/pso/system/BmlResourceClass.h').read_text()
        entry = re.search(r'struct BmlModelEntry \{(.*?)\};', resource, re.DOTALL)
        self.assertIsNotNone(entry)
        self.assertRegex(entry.group(1), r'\bs32 model;')
        self.assertIn('s32 find_model_node(u32 root, s32 index);',
                      (ROOT / 'include/pso/system/NinjaUtil.h').read_text())
        self.assertIn('return (NJS_OBJECT *)resource->models[index].model;',
                      (ROOT / 'src/pso/object/TObjFish_8001ED90.cpp').read_text())


if __name__ == '__main__':
    unittest.main()
