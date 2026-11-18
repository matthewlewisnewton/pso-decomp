#!/usr/bin/env python3
"""Pinned external README renderer for bound acceptance report evidence."""
import datetime
import hashlib
import json
import re
import sys
from pathlib import Path

FIELDS = ('total_code', 'matched_code', 'complete_code', 'total_data', 'matched_data',
          'complete_data', 'total_functions', 'matched_functions', 'total_units', 'complete_units')
START = '<!-- progress-table -->'
END = '\n## Target\n'
OLD = re.compile(r'<!-- progress-table -->\n\| \| Matched \| Linked \|\n\|:--\|--:\|--:\|\n\| Code \| [0-9.%, of()]+ \| [0-9.%, of()]+ \|\n\| Data \| [0-9.%, of()]+ \| [0-9.%, of()]+ \|\n\| Functions \| [0-9.%, of()]+ \| \|\n\| Units \| \| [0-9.%, of()]+ \|\n<!-- /progress-table -->\n\nMeasured on `PsoV3\.dol` on \d{4}-\d\d-\d\d at commit\n\[`[0-9a-f]{10}`\]\(https://github\.com/matthewlewisnewton/pso-decomp/commit/[0-9a-f]{40}\)\.\nA function is matched when it compiles to the original\'s exact bytes\. Code, data and\nunits are linked when the build takes them from compiled source instead of the original\. Data includes `\.bss`\.\nThe build still uses [0-9,]+ original-object fallback units; matched functions in those units are not counted as\nsource-linked coverage\. Unit counts can change when translation units are consolidated\.\n')
NEW = re.compile(r'<!-- progress-table -->\n\| \| Matched \| Linked \|\n\|:--\|--:\|--:\|\n\| Code \| [0-9.%, of()]+ \| [0-9.%, of()]+ \|\n\| Data \| [0-9.%, of()]+ \| [0-9.%, of()]+ \|\n\| Functions \| [0-9.%, of()]+ \| \|\n\| Units \| \| [0-9.%, of()]+ \|\n<!-- /progress-table -->\n\nMeasured on `PsoV3\.dol` on \d{4}-\d\d-\d\d at validated source commit\n\[`[0-9a-f]{10}`\]\(https://github\.com/matthewlewisnewton/pso-decomp/commit/[0-9a-f]{40}\)\.\nThe README-only publication commit records the measurements of its parent source tree\.\nA function is matched when it compiles to the original\'s exact bytes\. Code, data and\nunits are linked when the build takes them from compiled source instead of the original\. Data includes `\.bss`\.\nThe build still uses [0-9,]+ original-object fallback units; matched functions in those units are not counted as\nsource-linked coverage\. Unit counts can change when translation units are consolidated\.\n')

def integer(value):
    if type(value) is int: n = value
    elif isinstance(value, str) and value.isascii() and value.isdecimal(): n = int(value)
    else: raise ValueError('invalid metric')
    if n < 0 or n > 0xffffffff: raise ValueError('metric out of range')
    return n

def measures(report, provenance):
    if not isinstance(report, dict) or not isinstance(report.get('measures'), dict) or not isinstance(report.get('units'), list): raise ValueError('invalid report')
    m = {k: integer(report['measures'][k]) for k in FIELDS}
    for total, names in [('total_code', ('matched_code','complete_code')), ('total_data', ('matched_data','complete_data')), ('total_functions', ('matched_functions',)), ('total_units', ('complete_units',))]:
        if not m[total] or any(m[n] > m[total] for n in names): raise ValueError('invalid denominator')
    if not isinstance(provenance, dict) or set(provenance) != {'ordered_inputs_sha256', 'source_inputs', 'fallback_inputs'} or not re.fullmatch('[0-9a-f]{64}', str(provenance['ordered_inputs_sha256'])): raise ValueError('invalid provenance')
    source, fallback = (integer(provenance[k]) for k in ('source_inputs','fallback_inputs'))
    if source != m['complete_units'] or source + fallback != m['total_units'] or len(report['units']) != m['total_units']: raise ValueError('link/report mismatch')
    return m

def pct(n, d):
    # Integer half-up rounding to two decimal places, independent of locale.
    scaled = (n * 10000 * 2 + d) // (2 * d)
    return f'{scaled // 100}.{scaled % 100:02d}%'

def render(readme, before, after, before_inputs, after_inputs, source, epoch):
    if not re.fullmatch('[0-9a-f]{40}', source) or type(epoch) is not int or epoch <= 0: raise ValueError('invalid source attribution')
    a = measures(before, before_inputs); b = measures(after, after_inputs)
    if readme.count(START) != 1 or readme.count('<!-- /progress-table -->') != 1 or readme.count(END) != 1: raise ValueError('ambiguous README boundaries')
    start, end = readme.index(START), readme.index(END)
    block = readme[start:end]
    if not (OLD.fullmatch(block) or NEW.fullmatch(block)): raise ValueError('unexpected README progress text')
    if not any(b[k] > a[k] for k in ('matched_code','matched_data','matched_functions','complete_code','complete_data','complete_units')): return readme
    day = datetime.datetime.fromtimestamp(epoch, datetime.timezone.utc).strftime('%Y-%m-%d')
    num = lambda k: f"{b[k]:,}"
    cell = lambda k,d: f"{pct(b[k],b[d])} ({num(k)} of {num(d)})"
    table = f'''<!-- progress-table -->
| | Matched | Linked |
|:--|--:|--:|
| Code | {cell('matched_code','total_code')} | {cell('complete_code','total_code')} |
| Data | {cell('matched_data','total_data')} | {cell('complete_data','total_data')} |
| Functions | {cell('matched_functions','total_functions')} | |
| Units | | {cell('complete_units','total_units')} |
<!-- /progress-table -->

Measured on `PsoV3.dol` on {day} at validated source commit
[`{source[:10]}`](https://github.com/matthewlewisnewton/pso-decomp/commit/{source}).
The README-only publication commit records the measurements of its parent source tree.
A function is matched when it compiles to the original's exact bytes. Code, data and
units are linked when the build takes them from compiled source instead of the original. Data includes `.bss`.
The build still uses {after_inputs['fallback_inputs']:,} original-object fallback units; matched functions in those units are not counted as
source-linked coverage. Unit counts can change when translation units are consolidated.
'''
    return readme[:start] + table + readme[end:]

def main():
    req=json.loads(Path(sys.argv[1]).read_text())
    reports=[]
    for role in ('baseline','candidate'):
        entry=req['reports'][role]; p=Path(entry['path'])
        if not p.is_absolute() or p.is_symlink() or p.resolve()!=p: raise ValueError('invalid report path')
        raw=p.read_bytes()
        if hashlib.sha256(raw).hexdigest()!=entry['sha256']: raise ValueError('stale report')
        reports.append(json.loads(raw))
    readme=Path(req['readme']).read_text()
    value=render(readme, *reports, req['inputs']['baseline'], req['inputs']['candidate'], req['source'], req['epoch'])
    with Path(req['output']).open('x') as out: out.write(value)

if __name__ == '__main__': main()
