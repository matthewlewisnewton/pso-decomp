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
PLAYER_UNIT = 'pso/player/TObjPlayer_802D5B78.cpp'
DARKFALZ_UNIT = 'pso/boss/TBoss4DarkFalz_8004C93C.cpp'
PLAYER_CALLER = 'pso/player/TObjPlayer_802D5174.cpp'
PLAYER_COMPILER_SHA256 = '7cbae0a5bd81e07d7fa8975bbc4e969b5dea265cc29c5ee6bae0453a6e25f225'
CALLER_COMPILER_SHA256 = '316e2a98236c23f3fc902243b157eaebf8ef2ad6edb88cfd632a15b6676fa9a8'
PROFILES = {
    UNIT: {
        'gc26-deferred': '{"cflags": _switch(cflags_pso, "-inline off,deferred")}',
        'gc20-deferred': '{"mw_version": "GC/2.0", "cflags": _switch(cflags_pso, "-inline off,deferred")}',
    },
    PLAYER_UNIT: {'gc132-default-flags': '{"mw_version": "GC/1.3.2"}'},
    DARKFALZ_UNIT: {'gc26-deferred-sym-on': '{"cflags": _switch(cflags_pso, "-inline deferred", "-sym on")}'},
}
DUMPS = {unit: {name: ast.dump(ast.parse(expression, mode='eval').body)
                for name, expression in profiles.items()} for unit, profiles in PROFILES.items()}
TRANSITIONS = {
    UNIT: {('absent', 'gc26-deferred'), ('gc26-deferred', 'gc20-deferred'), ('absent', 'gc20-deferred')},
    PLAYER_UNIT: {('absent', 'gc132-default-flags')},
    DARKFALZ_UNIT: {('absent', 'gc26-deferred-sym-on')},
}



def shape(raw, unit=UNIT):
    if unit not in PROFILES: raise ValueError('unsupported unit')
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
    if unit in (PLAYER_UNIT, DARKFALZ_UNIT):
        defaults=[node for node in tree.body if isinstance(node,ast.Assign) and len(node.targets)==1 and isinstance(node.targets[0],ast.Name) and node.targets[0].id=='GAME_COMPILER']
        stores=[node for node in ast.walk(tree) if isinstance(node,ast.Name) and isinstance(node.ctx,ast.Store) and node.id=='GAME_COMPILER']
        if len(defaults)!=1 or len(stores)!=1 or not isinstance(defaults[0].value,ast.Constant) or defaults[0].value.value!='GC/2.6' or (unit == PLAYER_UNIT and PLAYER_CALLER in keys):
            raise ValueError('default compiler changed')
    if unit not in keys:
        return {'profile': 'absent', 'outside': raw, 'span': b''}
    index = keys.index(unit)
    key, value = mapping.keys[index], mapping.values[index]
    if not isinstance(value, ast.Dict): raise ValueError('unsupported profile')
    fields = [k.value if isinstance(k, ast.Constant) and type(k.value) is str else None for k in value.keys]
    if None in fields or len(fields) != len(set(fields)):
        raise ValueError('nonliteral or duplicate profile fields')
    profiles = [name for name, dump in DUMPS[unit].items() if ast.dump(value) == dump]
    if len(profiles) != 1: raise ValueError('unsupported profile')
    lines = raw.split(b'\n')
    first, last = key.lineno - 1, value.end_lineno
    if key.lineno != value.end_lineno or not lines[first].startswith(b'    "' + unit.encode() + b'":') or not lines[first].rstrip().endswith(b'},'):
        raise ValueError('invalid entry framing')
    while first > mapping.lineno and lines[first - 1].startswith(b'    #'):
        first -= 1
    # split(b'\\n') preserves all original bytes on rejoining, including final LF.
    return {'profile': profiles[0], 'outside': b'\n'.join(lines[:first] + lines[last:]),
            'span': b'\n'.join(lines[first:last]) + b'\n'}


def check(before, after, unit=UNIT):
    old, new = shape(before,unit), shape(after,unit)
    if old['outside'] != new['outside'] or (old['profile'], new['profile']) not in TRANSITIONS[unit]:
        raise ValueError('configuration change outside reviewed profiles')
    return {'unit': unit, 'old_profile': old['profile'], 'new_profile': new['profile'],
            'before_sha256': hashlib.sha256(before).hexdigest(),
            'after_sha256': hashlib.sha256(after).hexdigest(),
            'before_span_sha256': hashlib.sha256(old['span']).hexdigest(),
            'after_span_sha256': hashlib.sha256(new['span']).hexdigest()}

# Strict, private operator packet. This module is intended to be installed and
# pinned outside every candidate root; candidate code is never imported here.
import json
import os
from pathlib import Path
import re
import shlex
import subprocess
import sys

SHA1 = re.compile(r'[0-9a-f]{40}')
SHA256 = re.compile(r'[0-9a-f]{64}')
REPO = 'matthewlewisnewton/pso-decomp'
PIN_NAMES = frozenset(('checker', 'cli', 'python', 'launcher', 'wrapper', 'adapter',
                       'guard', 'base_validator', 'compiler', 'compiler_wrapper', 'git', 'preparer', 'ninja'))
PACKET_FIELDS = frozenset(('version', 'repository', 'policy', 'target', 'candidate', 'tree',
                           'prs', 'steps', 'cumulative', 'pins', 'effective_argv', 'configure_paths', 'originals', 'ordered_inputs', 'dependent_compile', 'verdict', 'independent', 'reviewer'))
STEP_FIELDS = frozenset(('before', 'after', 'before_blob', 'after_blob', 'diff_sha256',
                         'unit', 'old_profile', 'new_profile', 'before_sha256', 'after_sha256',
                         'before_span_sha256', 'after_span_sha256'))


def fail(message):
    raise ValueError(message)


def strict_json(raw):
    def pairs(items):
        result = {}
        for key, value in items:
            if key in result: fail('duplicate JSON key')
            result[key] = value
        return result
    return json.loads(raw, object_pairs_hook=pairs, parse_constant=lambda _: fail('invalid JSON constant'))


def exact_keys(value, keys):
    if type(value) is not dict or set(value) != set(keys): fail('invalid packet fields')


def full_sha(value, regex):
    if not isinstance(value, str) or not regex.fullmatch(value): fail('invalid digest')
    return value


def file_pin(entry, forbidden_roots=()):
    exact_keys(entry, ('path', 'sha256'))
    path = Path(entry['path'])
    if not path.is_absolute() or path.is_symlink() or path.resolve() != path or not path.is_file(): fail('invalid pinned file')
    if any(path.is_relative_to(Path(root).resolve()) for root in forbidden_roots): fail('pin inside writable root')
    full_sha(entry['sha256'], SHA256)
    raw = path.read_bytes()
    if hashlib.sha256(raw).hexdigest() != entry['sha256']: fail('stale pinned file')
    return path


def tree_digest(path):
    if path.is_symlink() or not path.is_dir(): fail('invalid input directory')
    entries=[['.','directory',path.stat().st_mode & 0o777]]
    for parent, dirs, files in os.walk(path,followlinks=False):
        for name in sorted(dirs+files):
            item=Path(parent)/name
            if item.is_symlink(): fail('input symlink')
            relative=str(item.relative_to(path)); mode=item.stat().st_mode & 0o777
            if item.is_file(): entries.append([relative,'file',mode,hashlib.sha256(item.read_bytes()).hexdigest()])
            elif item.is_dir(): entries.append([relative,'directory',mode])
            else: fail('unsupported input')
    if len(entries)==1: fail('empty input directory')
    return hashlib.sha256(json.dumps(sorted(entries),separators=(',',':')).encode()).hexdigest()


def path_pin(entry, forbidden_roots=()):
    """Pin a regular file or a complete, symlink-free tool directory."""
    exact_keys(entry, ('path', 'sha256'))
    path = Path(entry['path'])
    if not path.is_absolute() or path.is_symlink() or path.resolve() != path or not path.exists(): fail('invalid tool path')
    if any(path.is_relative_to(Path(root).resolve()) or Path(root).resolve().is_relative_to(path) for root in forbidden_roots): fail('tool/root overlap')
    full_sha(entry['sha256'], SHA256)
    if path.is_file():
        value=hashlib.sha256(path.read_bytes()).hexdigest()
    elif path.is_dir():
        value=tree_digest(path)
    else: fail('invalid tool type')
    if value != entry['sha256']: fail('stale tool path')
    return path


def git_bytes(repo, *args):
    return subprocess.check_output(['/usr/bin/git', '-c', 'core.hooksPath=/dev/null', '-c', 'core.fsmonitor=false', '-c', 'diff.algorithm=myers',
                                    '-c', 'diff.noprefix=false', '-c', 'diff.mnemonicprefix=false',
                                    '-c', 'core.quotepath=true', '-C', str(repo), *args],
                                   env={'PATH': '/usr/bin:/bin', 'LC_ALL':'C', 'GIT_CONFIG_NOSYSTEM':'1',
                                        'GIT_CONFIG_GLOBAL':'/dev/null', 'GIT_ATTR_NOSYSTEM':'1', 'GIT_TERMINAL_PROMPT':'0'})


def blob(repo, commit):
    line = git_bytes(repo, 'ls-tree', commit, '--', 'configure.py')
    match = re.fullmatch(rb'100755 blob ([0-9a-f]{40})\tconfigure\.py\n', line)
    if not match: fail('configure mode or path changed')
    return match.group(1).decode(), git_bytes(repo, 'show', commit + ':configure.py')


def step(repo, before, after, unit=UNIT):
    before_blob, a = blob(repo, before)
    after_blob, b = blob(repo, after)
    if a == b: return None
    result = check(a, b, unit)
    diff = git_bytes(repo, 'diff', '--no-ext-diff', '--no-textconv', '--no-renames',
                     '--full-index', '--binary', before, after, '--', 'configure.py')
    return dict(before=before, after=after, before_blob=before_blob, after_blob=after_blob,
                diff_sha256=hashlib.sha256(diff).hexdigest(), **result)


def require_compile_argv(argv, unit, wrapper, compiler, inline):
    if type(argv) is not list or len(argv)<3 or argv[:2]!=[wrapper,compiler] or any(type(x) is not str or not x or '@' in x or '..' in x or any(ord(ch)<32 or ord(ch)==127 or ch in ';|&`$\\' for ch in x) for x in argv):
        fail('invalid compile argv')
    def pairs(flag,value): return sum(argv[i:i+2]==[flag,value] for i in range(len(argv)-1))
    if pairs('-c','src/'+unit)!=1 or argv.count('-inline')!=1 or pairs('-inline',inline)!=1:
        fail('wrong compile target or inline profile')
    if unit in (PLAYER_UNIT,PLAYER_CALLER,DARKFALZ_UNIT) and (argv.count('-O4,s')!=1 or argv.count('-sdata2')!=1 or pairs('-sdata2','4')!=1):
        fail('default flags changed')
    if unit == DARKFALZ_UNIT:
        if argv.count('-sym')!=1 or pairs('-sym','on')!=1 or argv.index('-inline')>argv.index('-sym') or any((x.startswith('-sdata') and x != '-sdata2') or (x.startswith('-sym') and x != '-sym') or x.startswith('-inline=') or x in ('-g','-g1','-g2','-g3','-gdwarf','-debug') or (x.startswith('-O') and x != '-O4,s') for x in argv):
            fail('wrong Dark Falz profile flags')


def darkfalz_baseline_argv(candidate):
    baseline=list(candidate)
    inline=baseline.index('-inline');baseline[inline+1]='off'
    sym=baseline.index('-sym');del baseline[sym:sym+2]
    return baseline


def check_compile_graph(root,packet,role):
    """Compare actual reviewed Ninja compdb commands without executing a build."""
    ninja=file_pin(packet['pins']['ninja'],[root])
    graph=Path(root)/'build.ninja'
    if graph.is_symlink() or not graph.is_file(): fail('missing reviewed graph')
    graph_sha=hashlib.sha256(graph.read_bytes()).hexdigest()
    raw=subprocess.check_output([str(ninja),'-f',str(graph),'-t','compdb','mwcc','mwcc_sjis'],cwd=root,
                                env={'PATH':'/usr/bin:/bin','LC_ALL':'C'})
    rows=strict_json(raw)
    if type(rows) is not list: fail('invalid compile database')
    checks=[]
    unit=packet['cumulative']['unit']
    if role=='candidate': checks.append((unit,packet['effective_argv']))
    elif role=='baseline' and unit==DARKFALZ_UNIT: checks.append((unit,darkfalz_baseline_argv(packet['effective_argv'])))
    checks.extend((dep['unit'],dep['argv']) for dep in packet['dependent_compile'])
    for unit,expected in checks:
        found=[row for row in rows if isinstance(row,dict) and row.get('file')=='src/'+unit]
        if len(found)!=1 or not isinstance(found[0].get('command'),str): fail('missing unique compile edge')
        tokens=shlex.split(found[0]['command'])
        if tokens.count('&&')!=1 or tokens[:tokens.index('&&')]!=expected: fail('compile argv differs from reviewed graph')
    if hashlib.sha256(graph.read_bytes()).hexdigest()!=graph_sha: fail('graph changed during query')
    file_pin(packet['pins']['ninja'],[root])


def read_packet(entry, forbidden_roots=()):
    path = file_pin(entry, forbidden_roots)
    raw = path.read_bytes()
    if hashlib.sha256(raw).hexdigest() != entry['sha256']: fail('packet changed')
    packet = strict_json(raw)
    exact_keys(packet, PACKET_FIELDS)
    if type(packet['version']) is not int or packet['version'] != 1 or packet['repository'] != REPO or packet['policy'] != 'recovery' or packet['verdict'] != 'pass' or packet['independent'] is not True or not isinstance(packet['reviewer'], str) or not packet['reviewer'].strip(): fail('wrong packet scope')
    for key in ('target', 'candidate', 'tree'): full_sha(packet[key], SHA1)
    if type(packet['prs']) is not list or not packet['prs']: fail('missing ordered PRs')
    for pr in packet['prs']:
        exact_keys(pr, ('number', 'head', 'base_sha', 'review_base', 'review'))
        if type(pr['number']) is not int or pr['number'] <= 0: fail('invalid PR number')
        for key in ('head', 'base_sha', 'review_base'): full_sha(pr[key], SHA1)
        file_pin(pr['review'], forbidden_roots)
    exact_keys(packet['pins'], PIN_NAMES)
    for value in packet['pins'].values(): file_pin(value, forbidden_roots)
    for mapping, fields in (('originals', ('tree_sha256','dol_sha256')), ('ordered_inputs', ('ordered_inputs_sha256','source_inputs','fallback_inputs'))):
        exact_keys(packet[mapping], ('baseline','candidate'))
        for item in packet[mapping].values():
            exact_keys(item, fields)
            if mapping=='originals':
                for value in item.values(): full_sha(value,SHA256)
            else:
                full_sha(item['ordered_inputs_sha256'],SHA256)
                if any(type(item[k]) is not int or item[k] < 0 for k in ('source_inputs','fallback_inputs')) or item['source_inputs']+item['fallback_inputs']==0: fail('invalid ordered input counts')
    exact_keys(packet['configure_paths'], ('dtk', 'objdiff', 'wrapper', 'compilers', 'binutils'))
    for name, item in packet['configure_paths'].items():
        tool=path_pin(item, forbidden_roots)
        if name in ('compilers','binutils') and not tool.is_dir(): fail('tool directory required')
        if name in ('dtk','objdiff','wrapper') and not tool.is_file(): fail('tool executable required')
    if packet['configure_paths']['wrapper'] != packet['pins']['compiler_wrapper'] or not Path(packet['pins']['compiler']['path']).is_relative_to(Path(packet['configure_paths']['compilers']['path'])):
        fail('compiler or wrapper binding mismatch')
    if type(packet['effective_argv']) is not list or not packet['effective_argv'] or any(type(x) is not str or not x or '@' in x or '..' in x or any(ord(c)<32 or ord(c)==127 or c in ';|&`$\\' for c in x) for x in packet['effective_argv']): fail('invalid effective argv')
    if type(packet['steps']) is not list or not packet['steps']: fail('missing incremental steps')
    unit=packet['cumulative'].get('unit') if isinstance(packet['cumulative'],dict) else None
    if unit not in PROFILES or any(not isinstance(x,dict) or x.get('unit')!=unit for x in packet['steps']): fail('mixed or unsupported units')
    if type(packet['dependent_compile']) is not list: fail('invalid dependent compile')
    inline={UNIT:'off,deferred',PLAYER_UNIT:'off',DARKFALZ_UNIT:'deferred'}[unit]
    require_compile_argv(packet['effective_argv'],unit,packet['pins']['compiler_wrapper']['path'],packet['pins']['compiler']['path'],inline)
    if unit==DARKFALZ_UNIT and packet['pins']['compiler']['sha256']!=CALLER_COMPILER_SHA256: fail('unapproved Dark Falz compiler')
    if unit==PLAYER_UNIT:
        if packet['pins']['compiler']['sha256']!=PLAYER_COMPILER_SHA256 or len(packet['dependent_compile'])!=1: fail('unapproved player compiler')
        dep=packet['dependent_compile'][0];exact_keys(dep,('unit','compiler','argv'))
        if dep['unit']!=PLAYER_CALLER or dep['compiler']['sha256']!=CALLER_COMPILER_SHA256: fail('unapproved caller compiler')
        file_pin(dep['compiler'],forbidden_roots)
        if not Path(dep['compiler']['path']).is_relative_to(Path(packet['configure_paths']['compilers']['path'])): fail('caller compiler outside toolchain')
        require_compile_argv(dep['argv'],PLAYER_CALLER,packet['pins']['compiler_wrapper']['path'],dep['compiler']['path'],'off')
    elif packet['dependent_compile']: fail('unexpected dependent compiler')
    for entry in [*packet['steps'], packet['cumulative']]:
        exact_keys(entry, STEP_FIELDS)
        for key in ('before', 'after', 'before_blob', 'after_blob'): full_sha(entry[key], SHA1)
        for key in ('diff_sha256', 'before_sha256', 'after_sha256', 'before_span_sha256', 'after_span_sha256'): full_sha(entry[key], SHA256)
    return packet


def verify_plan(repo, packet, target, candidate, tree, prs, commits):
    root = Path(repo).resolve()
    if (packet['target'],packet['candidate'],packet['tree']) != (target,candidate,tree): fail('stale candidate binding')
    if type(prs) is not list or not prs or len({p.get('number') for p in prs}) != len(prs): fail('invalid PR selection')
    for pr in prs:
        review=pr.get('review',{})
        if review.get('verdict')!='pass' or review.get('independent') is not True or not isinstance(review.get('reviewer'),str) or not review['reviewer'].strip() or review.get('head')!=pr.get('head') or review.get('base')!=pr.get('review_base'):
            fail('missing exact-head source review')
    expected_prs = [{'number': p['number'], 'head': p['head'], 'base_sha': p['base_sha'], 'review_base': p['review_base'],
                     'review': {'path': p['review']['path'], 'sha256': p['review']['sha256']}} for p in prs]
    if packet['prs'] != expected_prs or [p['head'] for p in prs] != [c['head'] for c in commits]: fail('stale ordered reviews')
    if git_bytes(root, 'rev-parse', candidate+'^{tree}').strip().decode() != tree: fail('stale candidate tree')
    changed=git_bytes(root, 'diff', '--no-ext-diff', '--no-textconv', '--no-renames', '--name-only', '-z', target, candidate)
    paths=changed.split(b'\0')
    if any(path==b'tools' or path.startswith(b'tools/') or path.split(b'/')[-1] in (b'.gitattributes',b'.gitmodules') for path in paths if path):
        fail('trusted tools or checkout attributes changed')
    chain=[target] + [c['commit'] for c in commits]
    if len(commits)!=len(prs) or chain[-1] != candidate: fail('invalid candidate chain')
    for index,(pr,record) in enumerate(zip(prs,commits)):
        if set(record) != {'pr','commit','tree','head'} or record['head'] != pr['head'] or record['pr'] != pr['number']:
            fail('invalid merge record')
        full_sha(record['commit'],SHA1); full_sha(record['tree'],SHA1)
        parents=git_bytes(root,'show','-s','--format=%P',record['commit']).strip().decode().split()
        if parents != [chain[index],pr['head']] or git_bytes(root,'rev-parse',record['commit']+'^{tree}').strip().decode()!=record['tree']:
            fail('invalid merge ancestry')
        try: git_bytes(root,'merge-base','--is-ancestor',pr['base_sha'],chain[index])
        except subprocess.CalledProcessError: fail('missing PR prerequisite')
        for later in (chain[index],pr['head']):
            try: git_bytes(root,'merge-base','--is-ancestor',pr['review_base'],later)
            except subprocess.CalledProcessError: fail('unreviewed prerequisite')
    unit=packet['cumulative']['unit']
    observed=[]
    for before, after in zip(chain, chain[1:]):
        change=step(root,before,after,unit)
        if change: observed.append(change)
    if not observed or observed != packet['steps']: fail('stale incremental configuration')
    if step(root,target,candidate,unit) != packet['cumulative']: fail('stale cumulative configuration')
    return {'packet_sha256': None, 'target':target, 'candidate':candidate, 'tree':tree,
            'effective_argv': packet['effective_argv']}


def plan_request(request):
    exact_keys(request, ('mode','repo','packet','checker','cli','target','candidate','tree','prs','commits','output'))
    if request['mode'] != 'plan': fail('invalid checker mode')
    repo=Path(request['repo']).resolve()
    checker=file_pin(request['checker'],[repo])
    if checker != Path(__file__).resolve() or request['checker']['sha256'] != hashlib.sha256(Path(__file__).read_bytes()).hexdigest(): fail('checker identity mismatch')
    packet=read_packet(request['packet'],[repo])
    if packet['pins']['checker'] != request['checker'] or packet['pins']['cli'] != request['cli']: fail('checker or CLI packet mismatch')
    if Path(packet['pins']['python']['path']) != Path(sys.executable).resolve(): fail('python identity mismatch')
    if Path(packet['pins']['git']['path']) != Path('/usr/bin/git').resolve(): fail('git identity mismatch')
    result=verify_plan(repo,packet,request['target'],request['candidate'],request['tree'],request['prs'],request['commits'])
    result['packet_sha256']=request['packet']['sha256']
    output=Path(request['output'])
    if not output.is_absolute() or output.is_symlink() or output.exists() or output.resolve()!=output or output.is_relative_to(repo): fail('invalid output path')
    with output.open('x') as out:
        json.dump(result,out,sort_keys=True);out.write('\n');out.flush();os.fsync(out.fileno())


def main():
    if len(sys.argv)!=2: fail('request file required')
    request=Path(sys.argv[1])
    if not request.is_absolute() or request.is_symlink(): fail('invalid request file')
    plan_request(strict_json(request.read_bytes()))

if __name__ == '__main__': main()
