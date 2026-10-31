#!/usr/bin/env python3
"""Private fail-closed guard over raw reports from reviewed acceptance roots."""
import hashlib
import types
import json
import math
import re
from pathlib import Path
import sys

LOSS_FIELDS = ('regressions', 'data_regressions', 'data_coverage_lost',
               'padding_coverage_lost', 'linked_functions_lost',
               'linked_data_lost', 'missing_functions')
METRICS = ('matched_functions', 'matched_code', 'matched_data', 'complete_code',
           'complete_data', 'total_functions', 'total_code', 'total_data')

def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def number(value, name):
    if isinstance(value, bool) or not (isinstance(value, int) or
            isinstance(value, str) and value.isascii() and value.isdecimal()):
        raise RuntimeError('invalid_integer: ' + name)
    n = int(value)
    if n < 0 or n > 0xffffffff:
        raise RuntimeError('integer_out_of_range: ' + name)
    return n

def percent(row):
    if 'fuzzy_match_percent' not in row:
        return False
    value = row['fuzzy_match_percent']
    if isinstance(value, bool) or not isinstance(value, (int, float)) or not math.isfinite(value) or not 0 <= value <= 100:
        raise RuntimeError('invalid_match_percent')
    return value == 100

def intervals(report):
    if not isinstance(report, dict) or not isinstance(report.get('units'), list) or not report['units'] or not isinstance(report.get('measures'), dict):
        raise RuntimeError('invalid_raw_report')
    measures = {k: number(report['measures'].get(k), k) for k in METRICS}
    sets = {k: {} for k in ('code_coverage', 'code_exact', 'code_linked',
                            'data_coverage', 'data_exact', 'data_linked',
                            'function_coverage', 'function_exact', 'function_linked')}
    seen_functions = set()
    def add(label, key, start, end):
        sets[label].setdefault(key, []).append((start, end))
    for unit in report['units']:
        if not isinstance(unit, dict) or not isinstance(unit.get('name'), str) or not unit['name']:
            raise RuntimeError('invalid_unit')
        meta = unit.get('metadata')
        if not isinstance(meta, dict) or not isinstance(meta.get('module_name'), str) or not meta['module_name']:
            raise RuntimeError('invalid_unit_metadata')
        complete = meta.get('complete', False)
        if not isinstance(complete, bool):
            raise RuntimeError('invalid_link_status')
        module = meta['module_name']
        for field in ('sections', 'functions'):
            rows = unit.get(field, [])
            if not isinstance(rows, list):
                raise RuntimeError('invalid_' + field)
            for row in rows:
                if not isinstance(row, dict) or not isinstance(row.get('name'), str) or not row['name'] or not isinstance(row.get('metadata'), dict):
                    raise RuntimeError('invalid_report_row')
                start = number(row['metadata'].get('virtual_address'), 'address')
                size = number(row.get('size'), 'size')
                end = start + size
                if end > 0x100000000:
                    raise RuntimeError('invalid_range')
                exact = percent(row)
                if field == 'functions':
                    key = (module, start)
                    if key in seen_functions:
                        raise RuntimeError('duplicate_function_address')
                    seen_functions.add(key)
                    # Point identity plus full extent catches disappearing and shrinking functions.
                    group, key = 'function', (module, start)
                    if size == 0:
                        raise RuntimeError('zero_size_function')
                else:
                    if size == 0:
                        continue
                    name = row['name']
                    group = 'code' if name in ('.init', '.text', '.fini') or name.startswith(('.text.', '.init.', '.fini.')) else 'data'
                    key = (module, name)
                add(group + '_coverage', key, start, end)
                if exact: add(group + '_exact', key, start, end)
                if complete: add(group + '_linked', key, start, end)
    for group in sets.values():
        for key, rows in group.items():
            merged = []
            for start, end in sorted(rows):
                if merged and start <= merged[-1][1]: merged[-1] = (merged[-1][0], max(end, merged[-1][1]))
                else: merged.append((start, end))
            group[key] = merged
    if not seen_functions or not sets['code_coverage'] or not sets['data_coverage']:
        raise RuntimeError('incomplete_raw_report')
    return sets, measures

def has_loss(old, new):
    for key, rows in old.items():
        targets = new.get(key, [])
        for start, end in rows:
            cursor = start
            for first, last in targets:
                if last <= cursor: continue
                if first > cursor: break
                cursor = max(cursor, last)
                if cursor >= end: break
            if cursor < end: return True
    return False

def require_zero_loss(coverage, before, after):
    if not isinstance(coverage, dict) or coverage.get('result') != 'pass' or not isinstance(coverage.get('delta'), dict):
        raise RuntimeError('invalid_coverage_receipt')
    delta = coverage['delta']
    for key in LOSS_FIELDS:
        if not isinstance(delta.get(key), list): raise RuntimeError('missing_or_invalid_loss_field: ' + key)
    for key in sorted(set(LOSS_FIELDS) | {k for k in delta if 'lost' in k or 'regress' in k or k.startswith('missing')}):
        if not isinstance(delta[key], list) or delta[key]: raise RuntimeError('independent_extent_audit_required: ' + key)
    old, first = intervals(before)
    new, last = intervals(after)
    metrics = delta.get('metrics')
    if not isinstance(metrics, dict): raise RuntimeError('missing_receipt_metrics')
    for key in METRICS:
        row = metrics.get(key)
        if not isinstance(row, dict) or set(row) != {'before', 'after', 'delta'} or any(type(v) is not int for v in row.values()) or row != {'before': first[key], 'after': last[key], 'delta': last[key]-first[key]}:
            raise RuntimeError('raw_receipt_metrics_mismatch: ' + key)
    for key in old:
        if has_loss(old[key], new[key]): raise RuntimeError('raw_range_loss: ' + key)
    return {key: 0 for key in old}

def validate(request):
    environment = json.loads(Path(request['environment']).read_text())
    entry = environment['strict_loss_guard']['adapter']
    path = Path(entry['path'])
    if not path.is_absolute() or not path.is_file() or path.is_symlink(): raise RuntimeError('invalid_pinned_adapter')
    for executable in (path, Path(__file__).resolve()):
        if executable.resolve().is_relative_to(Path(request['checkout']).resolve()): raise RuntimeError('validator_inside_candidate')
    if digest(path) != entry['sha256']: raise RuntimeError('stale_pinned_adapter')
    adapter = types.ModuleType('_reviewed_acceptance_adapter')
    adapter.__file__ = str(path)
    exec(compile(path.read_bytes(), str(path), 'exec'), adapter.__dict__)
    result = adapter.validate(request)
    if request.get('policy') == 'source-maintenance':
        builds = result.get('acceptance_builds', {})
        before_inputs = builds.get('baseline', {}).get('provenance')
        after_inputs = builds.get('candidate', {}).get('provenance')
        if not isinstance(before_inputs, dict) or before_inputs != after_inputs or set(before_inputs) != {'ordered_inputs_sha256', 'source_inputs', 'fallback_inputs'} or not re.fullmatch(r'[0-9a-f]{64}', str(before_inputs.get('ordered_inputs_sha256', ''))) or any(type(before_inputs.get(k)) is not int or before_inputs[k] < 0 for k in ('source_inputs', 'fallback_inputs')) or not before_inputs['source_inputs'] + before_inputs['fallback_inputs']:
            raise RuntimeError('ordered_link_inputs_changed_or_missing')
    if digest(path) != entry['sha256']: raise RuntimeError('adapter_changed_during_validation')
    # The adapter pins and revalidates this review and its prepared roots after both
    # builds and check_pr. Derive fixed report paths from that same reviewed binding.
    review_entry = environment['acceptance_capacity']['review']
    review_path = Path(review_entry['path'])
    if not review_path.is_absolute() or review_path.is_symlink() or digest(review_path) != review_entry['sha256'] or result.get('review_sha256') != review_entry['sha256']:
        raise RuntimeError('stale_review_binding')
    review = json.loads(review_path.read_text())
    for key in ('target', 'candidate', 'tree'):
        if review.get(key) != request[key]: raise RuntimeError('stale_review_binding: ' + key)
    reports = []
    for role in ('baseline', 'candidate'):
        root = Path(review['roots'][role]['path'])
        if not root.is_absolute() or root.resolve() != root: raise RuntimeError('invalid_reviewed_root')
        if any(item.resolve().is_relative_to(root) for item in (path, Path(__file__))): raise RuntimeError('validator_inside_prepared_root')
        report = root / 'build/GPOE8P/report.json'
        if report.is_symlink() or not report.is_file() or report.resolve() != report: raise RuntimeError('invalid_raw_report_path')
        raw = report.read_bytes()
        reports.append((report, hashlib.sha256(raw).hexdigest(), json.loads(raw)))
    coverage_path = Path(result['coverage_receipt'])
    state = Path(request['state']).resolve()
    if not coverage_path.is_absolute() or coverage_path.is_symlink() or coverage_path.resolve() != coverage_path or not coverage_path.is_relative_to(state) or not coverage_path.is_file():
        raise RuntimeError('invalid_coverage_receipt_path')
    coverage_raw = coverage_path.read_bytes()
    coverage_sha = hashlib.sha256(coverage_raw).hexdigest()
    coverage = json.loads(coverage_raw)
    result['zero_lost_address_ranges'] = require_zero_loss(coverage, reports[0][2], reports[1][2])
    for key in METRICS:
        if result.get('delta', {}).get(key) != coverage['delta']['metrics'][key]['delta']:
            raise RuntimeError('validator_receipt_delta_mismatch: ' + key)
    if any(digest(path) != sha for path, sha, _ in reports) or digest(review_path) != review_entry['sha256'] or digest(coverage_path) != coverage_sha:
        raise RuntimeError('evidence_changed_during_guard')
    result['raw_report_sha256'] = {role: reports[i][1] for i, role in enumerate(('baseline', 'candidate'))}
    result['extent_gate'] = 'Unfiltered raw coverage, exact and source-linked intervals preserved.'
    return result

def main():
    request = json.loads(Path(sys.argv[1]).read_text())
    result = validate(request)
    with Path(request['output']).open('x') as output:
        json.dump(result, output, indent=2); output.write('\n')

if __name__ == '__main__': main()
