"""Localization must fail closed on an incomplete consumer census; no private inputs."""
import contextlib
import io
import json
import struct
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from tools import localize_split_globals as local
from tools.tests.test_link_units_sections import elf


class LocalizationTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.split = self.root / 'build/obj'
        self.compiled = self.root / 'build/src'
        self.cfg = self.root / 'config'
        for p in (self.split, self.compiled, self.cfg):
            p.mkdir(parents=True)
        self.report = self.root / 'report.json'
        self.config = self.root / 'split-config.json'
        self.symbols = self.cfg / 'symbols.txt'
        self.splits = self.cfg / 'splits.txt'
        self.blocked = self.cfg / 'blocked.json'
        self.original_symbols = 'bias = .rodata:0x1000; // type:object size:0x8\n'
        self.symbols.write_text(self.original_symbols)
        self.splits.write_text('owner.cpp:\n .rodata start:0x1000 end:0x1008\n')
        self.units = [
            {'name': 'psov3/owner', 'metadata': {'module_name': 'psov3', 'source_path': 'src/owner.cpp'},
             'sections': [{'name': '.rodata', 'size': 8, 'fuzzy_match_percent': 100}]},
            {'name': 'psov3/auto_data', 'metadata': {'module_name': 'psov3', 'auto_generated': True}}]
        self.config_units = [
            {'name': 'owner.cpp', 'object': 'build/obj/owner.o'},
            {'name': 'auto_data', 'object': 'build/obj/auto_data.o'}]
        self.write_census()
        self.blocked.write_text(json.dumps({'owner.cpp': ['missing bias']}))
        self.make(self.split / 'owner.o', defines=True)
        self.make(self.compiled / 'owner.o')
        self.make(self.split / 'auto_data.o')
        for name, value in {'ROOT': self.root, 'SPLIT_OBJ_DIR': self.split, 'OBJ_DIR': self.compiled,
                            'REPORT': self.report, 'SPLIT_CONFIG': self.config, 'SPLITS': self.splits,
                            'SYMBOLS': self.symbols}.items():
            self.enterContext(patch.object(local.lu, name, value))
        self.enterContext(patch.object(local, 'SYMBOLS', self.symbols))
        self.enterContext(patch.object(local, 'BLOCKED', self.blocked))
        # Other link checks read the symbol inventory; reset its global cache.
        self.enterContext(patch.object(local.lu, '_DOL_NAMES', None))

    def write_census(self):
        self.report.write_text(json.dumps({'units': self.units}))
        self.config.write_text(json.dumps({'units': self.config_units}))

    def make(self, path, defines=False, references=False, payload=b'constant'):
        # Default payload is arbitrary. The conversion-pool tests pass the two
        # MWCC biases explicitly; those bytes alone are not enough without the
        # 8-byte object and inventory checks.
        return elf(path, [('.rodata', payload, 8, 1)],
                   [('bias', 1 if defines else 0, 0, len(payload) if defines else 0, 1)]
                   if defines or references else [])

    def run_plan(self, write=True, extra=()):
        output = io.StringIO()
        argv = ['localize', *extra] + (['--write'] if write else [])
        with patch.object(sys, 'argv', argv), contextlib.redirect_stdout(output):
            self.assertEqual(local.main(), 0)
        return output.getvalue()

    def unchanged(self):
        self.assertEqual(self.symbols.read_text(), self.original_symbols)

    def test_complete_census_localizes_and_ignores_retired_objects(self):
        self.make(self.split / 'retired.o', references=True)
        out = self.run_plan()
        self.assertIn('1 units / 1 symbols localizable', out)
        self.assertIn('scope:local', self.symbols.read_text())

    def test_generated_extensionless_consumer_prevents_localization(self):
        self.make(self.split / 'auto_data.o', references=True)
        out = self.run_plan()
        self.assertIn('bias <- build/obj/auto_data.o', out)
        self.assertIn('0 units / 0 symbols localizable', out)
        self.unchanged()

    def test_owner_compiled_reference_still_blocks(self):
        self.make(self.compiled / 'owner.o', references=True)
        self.assertIn('bias <- build/src/owner.o', self.run_plan())
        self.unchanged()

    def test_other_compiled_consumer_blocks(self):
        self.units.append({'name': 'psov3/consumer', 'metadata': {'source_path': 'src/consumer.cpp'}})
        self.config_units.append({'name': 'consumer.cpp', 'object': 'build/obj/consumer.o'})
        self.write_census()
        self.make(self.split / 'consumer.o')
        self.make(self.compiled / 'consumer.o', references=True)
        self.assertIn('bias <- build/src/consumer.o', self.run_plan())
        self.unchanged()

    def test_source_extension_on_uncompiled_split_is_normalized(self):
        self.config_units[1]['name'] = 'auto_data.cpp'
        self.write_census()
        self.assertIn('1 units / 1 symbols localizable', self.run_plan())

    def test_inconsistent_object_path_refuses(self):
        self.config_units[1]['object'] = 'build/obj/retired.o'
        self.write_census()
        with self.assertRaisesRegex(ValueError, 'inconsistent split object path'):
            self.run_plan()
        self.unchanged()

    def test_missing_current_split_or_compiled_object_refuses_whole_write(self):
        for path in (self.split / 'auto_data.o', self.compiled / 'owner.o'):
            with self.subTest(path=path):
                saved = path.read_bytes()
                path.unlink()
                with self.assertRaises(OSError):
                    self.run_plan()
                self.unchanged()
                path.write_bytes(saved)

    def test_bad_current_object_refuses_even_read_only_plan(self):
        (self.split / 'auto_data.o').write_bytes(b'not ELF')
        with self.assertRaisesRegex(ValueError, 'ELF32'):
            self.run_plan(write=False)
        self.unchanged()

    def test_mismatched_duplicate_or_empty_census_refuses(self):
        for units in (self.units[:-1], self.units + self.units[:1], []):
            with self.subTest(units=units):
                self.report.write_text(json.dumps({'units': units}))
                with self.assertRaises(ValueError):
                    self.run_plan()
                self.unchanged()

    def test_stale_missing_symbol_plan_refuses(self):
        self.make(self.compiled / 'owner.o', defines=True)
        with self.assertRaisesRegex(ValueError, 'cached missing symbols changed'):
            self.run_plan()
        self.unchanged()

    def test_stale_report_or_layout_refuses(self):
        self.units[0]['sections'][0]['fuzzy_match_percent'] = 99
        self.write_census()
        with self.assertRaisesRegex(ValueError, 'no longer exact'):
            self.run_plan()
        self.units[0]['sections'][0]['fuzzy_match_percent'] = 100
        self.write_census()
        elf(self.compiled / 'owner.o', [('.rodata', b'constantconstant', 8, 1)])
        with self.assertRaisesRegex(ValueError, 'section_size_mismatch'):
            self.run_plan()
        self.unchanged()

    def test_changed_consumer_during_scan_refuses(self):
        original = local.elf_symbols
        def inspect(path):
            result = original(path)
            if path.name == 'auto_data.o':
                target = self.split / 'owner.o'
                b = bytearray(target.read_bytes())
                b[52] ^= 1
                target.write_bytes(b)
            return result
        with patch.object(local, 'elf_symbols', side_effect=inspect):
            with self.assertRaisesRegex(ValueError, 'input changed during localization'):
                self.run_plan()
        self.unchanged()

    def test_missing_duplicate_or_local_symbol_inventory_refuses(self):
        for text in ('', self.original_symbols * 2,
                     self.original_symbols.rstrip() + ' scope:local\n'):
            with self.subTest(text=text):
                self.symbols.write_text(text)
                with self.assertRaises(ValueError):
                    self.run_plan()
                self.assertEqual(self.symbols.read_text(), text)

    def test_explicit_global_scope_is_replaced(self):
        self.symbols.write_text(self.original_symbols.rstrip() + ' scope:global\n')
        self.run_plan()
        self.assertIn('scope:local', self.symbols.read_text())
        self.assertNotIn('scope:global', self.symbols.read_text())

    def test_weak_undefined_is_a_reference(self):
        path = self.split / 'auto_data.o'
        self.make(path, references=True)
        b = bytearray(path.read_bytes())
        shoff = int.from_bytes(b[32:36], 'big')
        # Fixture's second non-null section is .strtab, then .symtab.
        symoff = int.from_bytes(b[shoff + 3 * 40 + 16:shoff + 3 * 40 + 20], 'big')
        b[symoff + 16 + 12] = 0x21
        path.write_bytes(b)
        self.assertIn('bias <- build/obj/auto_data.o', self.run_plan())
        self.unchanged()

    def test_both_biases_are_recognized_and_other_bytes_are_not(self):
        path = self.split / 'kind.o'
        for payload, kind in ((bytes.fromhex('4330000000000000'), 'unsigned'),
                              (bytes.fromhex('4330000080000000'), 'signed')):
            self.make(path, defines=True, payload=payload)
            self.assertEqual(local.lu.conversion_pool_kind(path, 'bias'), kind)
        self.make(path, defines=True, payload=b'constant')
        self.assertIsNone(local.lu.conversion_pool_kind(path, 'bias'))
        self.assertIsNone(local.lu.conversion_pool_kind(path, 'missing'))

    def test_unreferenced_bias_is_labeled_and_localized(self):
        signed = bytes.fromhex('4330000080000000')
        self.original_symbols = 'bias = .rodata:0x1000; // type:object size:0x8 align:8 data:double\n'
        self.symbols.write_text(self.original_symbols)
        self.make(self.split / 'owner.o', defines=True, payload=signed)
        self.make(self.compiled / 'owner.o', payload=signed)
        out = self.run_plan(extra=['--pools-only'])
        self.assertIn('compiler-generated conversion pool: signed', out)
        self.assertIn('1 units / 1 conversion-pool constants localizable', out)
        self.assertIn('scope:local', self.symbols.read_text())

    def test_referenced_bias_is_recognized_and_not_localized(self):
        unsigned = bytes.fromhex('4330000000000000')
        self.original_symbols = 'bias = .rodata:0x1000; // type:object size:0x8 align:8 data:double\n'
        self.symbols.write_text(self.original_symbols)
        self.make(self.split / 'owner.o', defines=True, payload=unsigned)
        self.make(self.compiled / 'owner.o', payload=unsigned)
        self.make(self.split / 'auto_data.o', references=True, payload=unsigned)
        out = self.run_plan(extra=['--pools-only'])
        self.assertIn('compiler-generated conversion pool: unsigned', out)
        self.assertIn('bias [compiler-generated conversion pool: unsigned] <- build/obj/auto_data.o', out)
        self.assertIn('0 units / 0 conversion-pool constants localizable', out)
        self.unchanged()

    def test_unreferenced_bias_is_localized_when_a_sibling_symbol_is_referenced(self):
        signed = bytes.fromhex('4330000080000000')
        payload = signed + b'xxxx'
        self.units[0]['sections'][0]['size'] = 12
        self.write_census()
        self.original_symbols = (
            'bias = .rodata:0x1000; // type:object size:0x8 align:8 data:double\n'
            'other = .rodata:0x1008; // type:object size:0x4\n')
        self.symbols.write_text(self.original_symbols)
        self.blocked.write_text(json.dumps({'owner.cpp': ['missing bias', 'missing other']}))
        elf(self.split / 'owner.o', [('.rodata', payload, 8, 1)],
            [('bias', 1, 0, 8, 1), ('other', 1, 8, 4, 1)])
        elf(self.compiled / 'owner.o', [('.rodata', payload, 8, 1)],
            [('other', 0, 0, 0, 1)])
        out = self.run_plan()
        self.assertIn('compiler-generated conversion pool: signed', out)
        self.assertIn('other <- build/src/owner.o', out)
        text = self.symbols.read_text()
        self.assertIn('bias = .rodata:0x1000; // type:object size:0x8 align:8 data:double scope:local\n', text)
        self.assertEqual(text.splitlines()[1], 'other = .rodata:0x1008; // type:object size:0x4')

    def test_pools_only_leaves_an_ordinary_unreferenced_symbol(self):
        out = self.run_plan(extra=['--pools-only'])
        self.assertIn('0 units / 0 conversion-pool constants localizable', out)
        self.unchanged()

    def test_inventory_size_must_agree_before_a_bias_is_labeled(self):
        signed = bytes.fromhex('4330000080000000')
        self.original_symbols = 'bias = .rodata:0x1000; // type:object size:0x10\n'
        self.symbols.write_text(self.original_symbols)
        self.make(self.split / 'owner.o', defines=True, payload=signed)
        self.make(self.compiled / 'owner.o', payload=signed)
        out = self.run_plan(extra=['--pools-only'])
        self.assertNotIn('compiler-generated conversion pool', out)
        self.assertIn('0 units / 0 conversion-pool constants localizable', out)
        self.unchanged()

    def test_sixteen_byte_object_is_not_a_conversion_pool_constant(self):
        payload = bytes.fromhex('4330000080000000') * 2
        self.units[0]['sections'][0]['size'] = 16
        self.write_census()
        self.make(self.split / 'owner.o', defines=True, payload=payload)
        self.make(self.compiled / 'owner.o', payload=payload)
        out = self.run_plan()
        self.assertNotIn('compiler-generated conversion pool', out)
        self.assertIn('scope:local', self.symbols.read_text())


class StrictElfTests(unittest.TestCase):
    def test_reject_unsupported_or_malformed_consumer_objects(self):
        with tempfile.TemporaryDirectory() as d:
            path = Path(d) / 'obj.o'
            elf(path, [('.rodata', b'constant', 8, 1)], [('bias', 0, 0, 8, 1)])
            valid = path.read_bytes()
            self.assertEqual(local.elf_symbols(path), (set(), {'bias'}))
            shoff = int.from_bytes(valid[32:36], 'big')
            symoff = int.from_bytes(valid[shoff + 3 * 40 + 16:shoff + 3 * 40 + 20], 'big')
            bad = []
            for offset, data in ((4, b'\x02'), (5, b'\x01'), (16, b'\x00\x02'),
                                 (18, b'\x00\x03'), (46, b'\x00\x00'),
                                 (shoff + 3 * 40 + 24, struct.pack('>I', 99)),
                                 (shoff + 3 * 40 + 36, struct.pack('>I', 0)),
                                 (symoff + 16, struct.pack('>I', 0xffffffff)),
                                 (symoff + 16 + 14, b'\xff\xff')):
                b = bytearray(valid); b[offset:offset + len(data)] = data; bad.append(b)
            bad.extend([valid[:40], valid[:shoff + 20], b'not elf'])
            for b in bad:
                with self.subTest(data=bytes(b[:25])):
                    path.write_bytes(b)
                    with self.assertRaises(ValueError):
                        local.elf_symbols(path)


if __name__ == '__main__':
    unittest.main()
