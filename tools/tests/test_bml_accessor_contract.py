"""Source contract checks; native object validation remains a separate gate."""
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[2]
ACCESSORS = (
    ('get_bml_model', 'NJS_OBJECT', 'pso/system/BmlResource.h'),
    ('TObjFish__sub_8001EDB0', 'GinjaTextureList', 'pso/system/BmlTextureList.h'),
)


class BmlAccessorContractTests(unittest.TestCase):
    def test_every_consumer_includes_the_canonical_header(self):
        for name, _, header in ACCESSORS:
            consumers = [p for p in (ROOT / 'src').rglob('*.cpp')
                         if re.search(r'\b' + name + r'\b', p.read_text())]
            self.assertTrue(consumers)
            for path in consumers:
                with self.subTest(accessor=name, path=str(path.relative_to(ROOT))):
                    source = path.read_text()
                    self.assertIn(f'#include "{header}"', source)
                    self.assertNotRegex(source, r'#\s*define\s+' + name + r'\b')

    def test_one_declaration_and_one_definition(self):
        for name, result, header in ACCESSORS:
            declaration = re.compile(
                r'^\s*(?:extern\s+"C"\s+)?(?:s32|u32|int|void|[A-Z]\w*)\s*\**\s*'
                + name + r'\([^;{}]*\)\s*;', re.MULTILINE)
            definition = re.compile(
                r'^' + result + r'\s*\*' + name + r'\(BmlResource\s*\*resource, '
                r's32 index\)\s*\{', re.MULTILINE)
            declarations, definitions = [], []
            for directory in ('src', 'include/pso'):
                for path in (ROOT / directory).rglob('*'):
                    if path.suffix not in ('.cpp', '.h'):
                        continue
                    source = path.read_text()
                    declarations.extend([str(path.relative_to(ROOT))]
                                        * len(declaration.findall(source)))
                    definitions.extend([str(path.relative_to(ROOT))]
                                       * len(definition.findall(source)))
            with self.subTest(accessor=name):
                self.assertEqual(declarations, ['include/' + header])
                self.assertEqual(definitions, ['src/pso/object/TObjFish_8001ED90.cpp'])
                self.assertIn(f'extern "C" {result} *{name}(BmlResource *resource, s32 index);',
                              (ROOT / 'include' / header).read_text())

    def test_model_and_texture_storage_use_pointer_contracts(self):
        resource = (ROOT / 'include/pso/system/BmlResourceClass.h').read_text()
        entry = re.search(r'struct BmlModelEntry \{(.*?)\};', resource, re.DOTALL)
        self.assertIsNotNone(entry)
        self.assertRegex(entry.group(1), r'\bNJS_OBJECT \*model;')
        self.assertRegex(entry.group(1), r'\bGinjaTextureList \*m_c;')
        self.assertIn('s32 find_model_node(u32 root, s32 index);',
                      (ROOT / 'include/pso/system/NinjaUtil.h').read_text())
        self.assertIn('return resource->models[index].model;',
                      (ROOT / 'src/pso/object/TObjFish_8001ED90.cpp').read_text())


if __name__ == '__main__':
    unittest.main()
