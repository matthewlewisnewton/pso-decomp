#!/usr/bin/env python3
"""Nonexecuting shape check for the narrowly reviewed Ancient01 profiles.

This helper is not an admission token. A reviewed preparation launcher must bind
and recheck the complete packet, source tree and tools under the exclusive lock
before candidate configuration executes. Until integrated, config changes stay
rejected by the existing validator.
"""
import ast
import hashlib
import unicodedata

UNIT = 'pso/misc/TOTrapAncient01.cpp'
PROFILES = {
    'gc26-deferred': '{"cflags": _switch(cflags_pso, "-inline off,deferred")}',
    'gc20-deferred': '{"mw_version": "GC/2.0", "cflags": _switch(cflags_pso, "-inline off,deferred")}',
}
DUMPS = {name: ast.dump(ast.parse(expression, mode='eval').body)
         for name, expression in PROFILES.items()}
TRANSITIONS = {('absent', 'gc26-deferred'), ('gc26-deferred', 'gc20-deferred'),
               ('absent', 'gc20-deferred')}


def shape(raw):
    if not isinstance(raw, bytes) or not raw.endswith(b'\n') or any((b < 32 and b != 10) or b == 127 for b in raw):
        raise ValueError('invalid configuration framing')
    text = raw.decode('utf-8')
    if any(unicodedata.category(ch) in ('Cc', 'Cf') and ch != '\n' for ch in text):
        raise ValueError('invalid configuration controls')
    tree = ast.parse(text, filename='configure.py')
    assignments = [node for node in tree.body if isinstance(node, ast.AnnAssign)
                   and isinstance(node.target, ast.Name) and node.target.id == 'GAME_EXCEPTIONS']
    stores = [node for node in ast.walk(tree) if isinstance(node, ast.Name)
              and isinstance(node.ctx, ast.Store) and node.id == 'GAME_EXCEPTIONS']
    if len(assignments) != 1 or len(stores) != 1 or not isinstance(assignments[0].value, ast.Dict):
        raise ValueError('invalid GAME_EXCEPTIONS declaration')
    mapping = assignments[0].value
    keys = [key.value if isinstance(key, ast.Constant) and type(key.value) is str else None
            for key in mapping.keys]
    if None in keys or len(keys) != len(set(keys)):
        raise ValueError('nonliteral or duplicate unit keys')
    if UNIT not in keys:
        return {'profile': 'absent', 'outside': raw, 'span': b''}
    index = keys.index(UNIT)
    key, value = mapping.keys[index], mapping.values[index]
    if not isinstance(value, ast.Dict): raise ValueError('unsupported profile')
    fields = [k.value if isinstance(k, ast.Constant) and type(k.value) is str else None for k in value.keys]
    if None in fields or len(fields) != len(set(fields)):
        raise ValueError('nonliteral or duplicate profile fields')
    profiles = [name for name, dump in DUMPS.items() if ast.dump(value) == dump]
    if len(profiles) != 1: raise ValueError('unsupported profile')
    lines = raw.split(b'\n')
    first, last = key.lineno - 1, value.end_lineno
    if key.lineno != value.end_lineno or not lines[first].startswith(b'    "' + UNIT.encode() + b'":') or not lines[first].rstrip().endswith(b'},'):
        raise ValueError('invalid entry framing')
    while first > mapping.lineno and lines[first - 1].startswith(b'    #'):
        first -= 1
    # split(b'\\n') preserves all original bytes on rejoining, including final LF.
    return {'profile': profiles[0], 'outside': b'\n'.join(lines[:first] + lines[last:]),
            'span': b'\n'.join(lines[first:last]) + b'\n'}


def check(before, after):
    old, new = shape(before), shape(after)
    if old['outside'] != new['outside'] or (old['profile'], new['profile']) not in TRANSITIONS:
        raise ValueError('configuration change outside reviewed profiles')
    return {'unit': UNIT, 'old_profile': old['profile'], 'new_profile': new['profile'],
            'before_sha256': hashlib.sha256(before).hexdigest(),
            'after_sha256': hashlib.sha256(after).hexdigest(),
            'before_span_sha256': hashlib.sha256(old['span']).hexdigest(),
            'after_span_sha256': hashlib.sha256(new['span']).hexdigest()}
