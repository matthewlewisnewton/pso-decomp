#!/usr/bin/env python3
"""Report explicit handoffs; never schedule work or authorize a gate."""
import argparse
import hashlib
import json
import re
import sys
from pathlib import Path

SHA = re.compile(r'^[0-9a-f]{40}$')
DIGEST = re.compile(r'^[0-9a-f]{64}$')
STAGES = ('source', 'development', 'graph', 'acceptance', 'publication')


def sha(value, label):
    if not isinstance(value, str) or not SHA.fullmatch(value):
        raise ValueError(f'{label}: expected full lowercase commit SHA')
    return value


def string(value, label):
    if not isinstance(value, str) or not value.strip():
        raise ValueError(f'{label}: expected nonempty string')
    return value


def report(data, root):
    if not isinstance(data, dict) or data.get('version') != 1:
        raise ValueError('expected version 1 object')
    main = sha(data.get('current_main'), 'current_main')
    items = data.get('items')
    if not isinstance(items, list):
        raise ValueError('items must be a list')
    seen = set()
    result = {'version': 1, 'current_main': main, 'items': [],
              'pending_reviews': [], 'pending_admissions': [], 'slot_releases': []}
    for item in items:
        if not isinstance(item, dict):
            raise ValueError('item must be an object')
        name = string(item.get('id'), 'item id')
        if name in seen:
            raise ValueError(f'duplicate item id: {name}')
        seen.add(name)
        head = sha(item.get('head'), name + ' head')
        observed = sha(item.get('observed_head'), name + ' observed_head')
        owner = string(item.get('owner'), name + ' owner')
        state = item.get('state')
        if state not in ('active', 'turn_complete', 'complete'):
            raise ValueError(f'{name}: invalid state')
        evidence = item.get('evidence', [])
        requests = item.get('requests', [])
        if not isinstance(evidence, list) or not isinstance(requests, list):
            raise ValueError(f'{name}: evidence and requests must be lists')
        stages = {stage: 'missing' for stage in STAGES}
        issues = []
        for ev in evidence:
            if not isinstance(ev, dict) or ev.get('stage') not in STAGES:
                raise ValueError(f'{name}: invalid evidence stage')
            stage = ev['stage']
            if stages[stage] != 'missing':
                raise ValueError(f'{name}: duplicate evidence stage {stage}')
            bound_head = sha(ev.get('head'), name + ' evidence head')
            base = sha(ev.get('base'), name + ' evidence base')
            verdict = ev.get('verdict')
            if verdict not in ('pass', 'fail', 'unknown'):
                raise ValueError(f'{name}: invalid verdict')
            path = string(ev.get('path'), name + ' evidence path')
            digest = ev.get('sha256')
            if not isinstance(digest, str) or not DIGEST.fullmatch(digest):
                raise ValueError(f'{name}: invalid evidence sha256')
            try:
                actual = hashlib.sha256((root / path).read_bytes()).hexdigest()
            except OSError:
                actual = None
            if actual != digest:
                status = 'unverified'
            elif bound_head != head or observed != head:
                status = 'stale_head'
            elif stage in ('graph', 'acceptance', 'publication') and base != main:
                status = 'stale_main'
            else:
                status = verdict
            stages[stage] = status
            if status != 'pass':
                issues.append(f'{stage}: {status}')
        unique = {}
        for request in requests:
            if not isinstance(request, dict) or request.get('kind') not in ('review', 'admission'):
                raise ValueError(f'{name}: invalid request kind')
            rid = string(request.get('id'), name + ' request id')
            rhead = sha(request.get('head'), name + ' request head')
            rstate = request.get('state')
            if rstate not in ('pending', 'done', 'cancelled'):
                raise ValueError(f'{name}: invalid request state')
            assignee = string(request.get('owner'), name + ' request owner')
            canonical = (request['kind'], rhead, rstate, assignee)
            if rid in unique and unique[rid] != canonical:
                raise ValueError(f'{name}: conflicting duplicate request {rid}')
            unique[rid] = canonical
        pending = []
        for rid, (kind, rhead, rstate, assignee) in sorted(unique.items()):
            if rstate != 'pending':
                continue
            stale = rhead != head or observed != head
            row = {'item': name, 'request': rid, 'owner': assignee,
                   'head': rhead, 'stale_head': stale}
            result['pending_' + kind + 's'].append(row)
            pending.append(row)
        slot = item.get('slot')
        if slot is not None:
            if not isinstance(slot, dict) or slot.get('state') not in ('held', 'released'):
                raise ValueError(f'{name}: invalid slot')
            string(slot.get('owner'), name + ' slot owner')
            if slot['state'] == 'held' and state in ('turn_complete', 'complete'):
                result['slot_releases'].append({'item': name, 'owner': slot['owner'],
                                                'action': 'confirm and record release'})
        if observed != head:
            issues.append('observed head differs from requested head')
        if state == 'turn_complete' and pending:
            issues.append('completed turn has pending work')
        # A report of prerequisites only, never permission to publish.
        eligible = (observed == head and not pending
                    and all(stages[s] == 'pass' for s in ('source', 'development')))
        result['items'].append({'id': name, 'owner': owner, 'state': state,
                                'head': head, 'observed_head': observed, 'stages': stages,
                                'ready_eligible': eligible, 'issues': issues})
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('snapshot', type=Path, help='versioned JSON snapshot')
    args = parser.parse_args()
    try:
        data = json.loads(args.snapshot.read_text(encoding='utf-8'))
        print(json.dumps(report(data, args.snapshot.resolve().parent), indent=2, sort_keys=True))
    except (ValueError, OSError) as exc:
        print(f'handoff report: {exc}', file=sys.stderr)
        return 2
    return 0


if __name__ == '__main__':
    sys.exit(main())
