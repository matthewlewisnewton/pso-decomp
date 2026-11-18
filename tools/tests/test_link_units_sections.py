"""Synthetic BE ELF32 fixtures; no game data or compiler installation required."""
import struct
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from tools import link_units as link
from tools.mwcc_parts import Unproven, inspect_mwcat_orphans, mwcat_discarded_text_bytes


def elf(path, sections, symbols=()):
    """Write allocated sections and (name, section index, offset, size, type) symbols."""
    names = bytearray(b'\0')
    def string(table, value):
        offset = len(table)
        table.extend(value.encode() + b'\0')
        return offset
    headers = [(0,) * 10]
    data = bytearray(52)
    for name, payload, alignment, typ in sections:
        off = len(data)
        if typ != 8:
            data.extend(payload)
        headers.append((string(names, name), typ, 6 if name == '.text' else 2,
                        0, off, len(payload), 0, 0, alignment, 0))
    strings = bytearray(b'\0')
    symdata = bytearray(16)
    for name, index, offset, size, typ in symbols:
        symdata.extend(struct.pack('>IIIBBH', string(strings, name), offset,
                                   size, 0x10 | typ, 0, index))
    strings_index = len(headers)
    headers.append((string(names, '.strtab'), 3, 0, 0, len(data), len(strings), 0, 0, 1, 0))
    data.extend(strings)
    headers.append((string(names, '.symtab'), 2, 0, 0, len(data), len(symdata), strings_index, 1, 4, 16))
    data.extend(symdata)
    shstr_index = len(headers)
    name_offset = string(names, '.shstrtab')
    headers.append((name_offset, 3, 0, 0, len(data), len(names), 0, 0, 1, 0))
    data.extend(names)
    shoff = len(data)
    for header in headers:
        data.extend(struct.pack('>10I', *header))
    data[:16] = b'\x7fELF\x01\x02\x01' + bytes(9)
    struct.pack_into('>HHIIIIIHHHHHH', data, 16, 1, 20, 1, 0, 0, shoff, 0,
                     52, 0, 0, 40, len(headers), shstr_index)
    path.write_bytes(data)
    return path


def text(size, alignment=4):
    return ('.text', bytes(size), alignment, 1)


class RepeatedSections(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)

    def test_single_section_unchanged(self):
        obj = elf(self.root / 'one.o', [text(12)], [('late', 1, 8, 4, 2), ('early', 1, 0, 8, 2)])
        self.assertEqual(link.elf_alloc_section_layout(obj), {'.text': (12, 4)})
        self.assertEqual(link.elf_function_order_by_section(obj), {'.text': ['early', 'late']})
        self.assertEqual(link.elf_section_bytes(obj, '.text'), bytes(12))

    def test_repeated_sections_keep_index_order_and_alignment(self):
        obj = elf(self.root / 'many.o', [text(12), ('.data', b'abcd', 4, 1), text(4, 16), text(8)],
                  [('last', 4, 0, 8, 2), ('middle', 3, 0, 4, 2), ('first', 1, 0, 12, 2)])
        self.assertEqual(link.elf_alloc_section_layout(obj), {'.text': (28, 16), '.data': (4, 4)})
        self.assertEqual(link.elf_function_order_by_section(obj), {'.text': ['first', 'middle', 'last']})
        self.assertEqual(len(link.elf_section_bytes(obj, '.text')), 28)

    def test_data_symbols_and_bytes_use_concatenated_offsets(self):
        obj = elf(self.root / 'data.o', [('.data', b'abcd', 4, 1), ('.data', b'efgh', 8, 1)],
                  [('first', 1, 0, 4, 1), ('second', 2, 0, 4, 1)])
        self.assertEqual(link.elf_global_object_layout(obj), {'first': ('.data', 0), 'second': ('.data', 8)})
        self.assertEqual(link.elf_section_bytes(obj, '.data'), b'abcd\0\0\0\0efgh')
        self.assertTrue(link._tail_has_named_symbols(obj, '.data', 8, 12))
        self.assertFalse(link._tail_has_named_symbols(obj, '.data', 12, 16))
        self.assertTrue(link._tail_has_named_symbols(obj, '.data', 4, 8))

    def test_nobits_and_missing_sections(self):
        obj = elf(self.root / 'bss.o', [('.bss', bytes(4), 4, 8), ('.bss', bytes(8), 8, 8)])
        self.assertEqual(link.elf_alloc_sections(obj), {'.bss': 16})
        self.assertIsNone(link.elf_section_bytes(obj, '.bss'))
        self.assertIsNone(link.elf_section_bytes(obj, '.missing'))

    def test_real_checks_accept_equivalent_parts_and_reject_order_size_alignment(self):
        splitdir, objdir = self.root / 'split', self.root / 'obj'
        splitdir.mkdir(); objdir.mkdir()
        split = elf(splitdir / 'unit.o', [text(12)], [('a', 1, 0, 8, 2), ('b', 1, 8, 4, 2)])
        obj = elf(objdir / 'unit.o', [text(8), text(4)], [('a', 1, 0, 8, 2), ('b', 2, 0, 4, 2)])
        unit = {'name': 'unit.cpp', 'sections': [{'name': '.text', 'size': 12,
                'metadata': {'virtual_address': 0x1004}}]}
        with patch.object(link, 'SPLIT_OBJ_DIR', splitdir), patch.object(link, 'OBJ_DIR', objdir), \
             patch.object(link, 'stripped_functions', return_value={}):
            self.assertEqual(link.section_size_mismatch(unit), [])
            self.assertEqual(link.function_order_mismatch(unit), [])
            elf(obj, [text(8), text(4)], [('b', 1, 0, 4, 2), ('a', 2, 0, 8, 2)])
            self.assertTrue(link.function_order_mismatch(unit))
            elf(obj, [text(8), text(8)], [('a', 1, 0, 8, 2), ('b', 2, 0, 4, 2)])
            self.assertEqual(link.section_size_mismatch(unit), ['.text:12!=16'])
            elf(obj, [text(8), text(4, 16)], [('a', 1, 0, 8, 2), ('b', 2, 0, 4, 2)])
            self.assertEqual(link.section_size_mismatch(unit), ['.text:12!=20'])
            self.assertTrue(link.section_alignment_mismatch(unit))

    def test_repeated_data_movement_is_still_rejected(self):
        splitdir, objdir = self.root / 'split', self.root / 'obj'
        splitdir.mkdir(); objdir.mkdir()
        elf(splitdir / 'unit.o', [('.data', bytes(8), 4, 1)], [('a', 1, 0, 4, 1), ('b', 1, 4, 4, 1)])
        obj = objdir / 'unit.o'
        elf(obj, [('.data', bytes(4), 4, 1), ('.data', bytes(4), 4, 1)], [('a', 1, 0, 4, 1), ('b', 2, 0, 4, 1)])
        with patch.object(link, 'SPLIT_OBJ_DIR', splitdir), patch.object(link, 'OBJ_DIR', objdir):
            self.assertEqual(link.global_data_layout_mismatch({'name': 'unit.cpp'}), [])
            elf(obj, [('.data', bytes(4), 4, 1), ('.data', bytes(4), 4, 1)], [('b', 1, 0, 4, 1), ('a', 2, 0, 4, 1)])
            self.assertEqual(len(link.global_data_layout_mismatch({'name': 'unit.cpp'})), 2)

    def test_ambiguous_catalogs_and_exception_sections_get_no_discount(self):
        obj = elf(self.root / 'catalog.o', [text(4), text(4)])
        with self.assertRaisesRegex(Unproven, 'duplicate .text'):
            inspect_mwcat_orphans(obj)
        self.assertEqual(mwcat_discarded_text_bytes(obj), 0)
        obj = elf(self.root / 'exception.o', [('extab', bytes(4), 4, 1), ('extab', bytes(4), 4, 1)])
        self.assertEqual(link.stripped_exception_bytes(obj, {'function'}), {})

    def test_stripping_from_repeated_text_is_not_blindly_subtracted(self):
        splitdir, objdir = self.root / 'split', self.root / 'obj'
        splitdir.mkdir(); objdir.mkdir()
        elf(splitdir / 'unit.o', [text(12)])
        elf(objdir / 'unit.o', [text(8), text(4, 16)])
        with patch.object(link, 'SPLIT_OBJ_DIR', splitdir), patch.object(link, 'OBJ_DIR', objdir), \
             patch.object(link, 'stripped_functions', return_value={'extra': 8}):
            self.assertIn('cannot prove', link.section_size_mismatch({'name': 'unit.cpp'})[0])

    def test_empty_contributions_and_zero_alignment(self):
        obj = elf(self.root / 'empty.o', [text(4, 0), text(0, 8), text(4, 4)])
        self.assertEqual(link.elf_alloc_section_layout(obj), {'.text': (12, 8)})
        self.assertEqual(link.elf_alloc_sections(elf(self.root / 'zero.o', [text(0)])), {})

    def test_invalid_alignment_fails_closed(self):
        obj = elf(self.root / 'invalid.o', [text(4, 3)])
        with self.assertRaises(ValueError):
            link.elf_alloc_sections(obj)


if __name__ == '__main__':
    unittest.main()
