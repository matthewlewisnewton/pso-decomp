#!/usr/bin/env python3
"""Compare independently prepared evidence inventories; never authorize reuse."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import sys

KINDS = frozenset(('source', 'tool', 'compiler', 'config', 'generated'))
HEX = re.compile(r'^[0-9a-f]{64}$')


def pairs(items):
    result = {}
    for key, value in items:
        if key in result:
            raise ValueError(f'duplicate key: {key}')
        result[key] = value
    return result


def read_json(path):
    return json.loads(Path(path).read_text(), object_pairs_hook=pairs)


def checked_files(root, entries, label, errors):
    result = {}
    if not isinstance(entries, dict) or not entries:
        errors.append(f'{label}: missing inventory')
        return result
    for name, item in sorted(entries.items()):
        try:
            if not isinstance(name, str) or not name or not isinstance(item, dict):
                raise ValueError('invalid entry')
            if set(item) != {'path', 'sha256'} or not HEX.fullmatch(item['sha256']):
                raise ValueError('expected path and lowercase SHA-256')
            lexical = item['path']
            if not isinstance(lexical, str) or not lexical or Path(lexical).is_absolute() or '..' in Path(lexical).parts:
                raise ValueError('path must be root-relative without parent traversal')
            path = (root / lexical).resolve(strict=True)
            if not path.is_relative_to(root) or not path.is_file():
                raise ValueError('file outside root or not a regular file')
            digest = hashlib.sha256(path.read_bytes()).hexdigest()
            if digest != item['sha256']:
                raise ValueError('content hash mismatch')
            result[name] = {'path': lexical, 'resolved_path': path.relative_to(root).as_posix(), 'sha256': digest}
        except (OSError, TypeError, ValueError, KeyError) as exc:
            errors.append(f'{label}/{name}: {exc}')
    return result


def snapshot(path, baseline):
    errors = []
    try:
        raw = read_json(path)
        if set(raw) != {'version', 'revision', 'root', 'proofs', 'global_inputs', 'consumers'} or raw['version'] != 1:
            raise ValueError('invalid snapshot fields or version')
        if not isinstance(raw['revision'], str) or not re.fullmatch(r'[0-9a-f]{40}', raw['revision']):
            raise ValueError('revision must be a full commit ID')
        root = Path(raw['root']).resolve(strict=True)
        if not root.is_dir():
            raise ValueError('root must be a directory')
        proofs = raw['proofs']
        required = {'graph', 'inventory_review'} | ({'development_receipt'} if baseline else set())
        if not isinstance(proofs, dict) or set(proofs) != required:
            raise ValueError('missing or unexpected proof inventory')
        checked_files(root, proofs, 'proofs', errors)
        inputs = raw['global_inputs']
        if not isinstance(inputs, dict) or set(inputs) != KINDS:
            raise ValueError('all global input categories are required')
        global_inputs = {kind: checked_files(root, inputs[kind], f'global/{kind}', errors) for kind in sorted(KINDS)}
        consumers = raw['consumers']
        if not isinstance(consumers, dict) or not consumers:
            raise ValueError('missing consumers')
        parsed = {}
        for name, entry in sorted(consumers.items()):
            if not isinstance(name, str) or not name or not isinstance(entry, dict) or set(entry) != ({'inputs', 'outputs'} if baseline else {'inputs'}):
                errors.append(f'consumer {name}: invalid fields')
                continue
            parsed[name] = {'inputs': checked_files(root, entry['inputs'], f'consumer/{name}/inputs', errors)}
            if baseline:
                checked = checked_files(root, entry['outputs'], f'consumer/{name}/outputs', errors)
                parsed[name]['outputs'] = {key: {'path': str((root / entry['outputs'][key]['path']).resolve()), 'sha256': value['sha256']}
                                           for key, value in checked.items()}
        return {'revision': raw['revision'], 'global': global_inputs, 'consumers': parsed}, errors
    except (OSError, ValueError, TypeError, KeyError, json.JSONDecodeError) as exc:
        return None, [f'{path}: {exc}']


def compare(baseline_path, current_path):
    old, old_errors = snapshot(baseline_path, True)
    new, new_errors = snapshot(current_path, False)
    errors = old_errors + new_errors
    result = {'version': 1, 'status': 'incomplete' if errors else 'compared', 'errors': errors,
              'historical_proof': ('incomplete' if errors else 'files verified only; receipt semantics and independent review require human verification'),
              'acceptance_freshness': 'not established', 'authorization': 'none', 'global_changes': [],
              'affected_consumers': {}, 'potentially_reusable_baseline_outputs': {}}
    if not old or not new:
        return result
    result['baseline_revision'], result['current_revision'] = old['revision'], new['revision']
    result['global_changes'] = [k for k in sorted(KINDS) if old['global'][k] != new['global'][k]]
    for name in sorted(set(old['consumers']) | set(new['consumers'])):
        reasons = []
        if name not in old['consumers'] or name not in new['consumers']:
            reasons.append('consumer added or removed')
        elif old['consumers'][name]['inputs'] != new['consumers'][name]['inputs']:
            reasons.append('consumer inputs changed')
        if result['global_changes']:
            reasons.append('global inputs changed')
        if errors:
            reasons.append('evidence incomplete')
        if reasons:
            result['affected_consumers'][name] = reasons
        else:
            result['potentially_reusable_baseline_outputs'][name] = old['consumers'][name]['outputs']
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('baseline')
    parser.add_argument('current')
    args = parser.parse_args()
    result = compare(args.baseline, args.current)
    print(json.dumps(result, indent=2, sort_keys=True))
    return 1 if result['errors'] else 0


if __name__ == '__main__':
    sys.exit(main())
