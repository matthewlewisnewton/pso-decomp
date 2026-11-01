#!/usr/bin/env python3
"""Private development-only validator. Never publishes or approves a graph."""
from __future__ import annotations

import hashlib
import types
import json
import os
from pathlib import Path
import subprocess
import sys
import time


def require(condition, code):
    if not condition:
        raise RuntimeError(code)


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def pinned(entry):
    path = Path(entry['path'])
    require(path.is_absolute() and path.is_file() and not path.is_symlink(), 'invalid_pinned_file')
    require(digest(path) == entry['sha256'], 'stale_pinned_file: ' + path.name)
    return path


def canonical_hash(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


_safety = types.ModuleType('_trusted_queue_git_safety')
exec(compile(r'''#!/usr/bin/env python3
"""Callback-free Git boundary and raw checkout checks for trusted queue tools."""
import hashlib
import os
from pathlib import Path
import re
import subprocess


def environment(base=None):
    env={k:v for k,v in (os.environ if base is None else base).items() if not k.startswith('GIT_')}
    env.update(GIT_CONFIG_GLOBAL='/dev/null',GIT_CONFIG_NOSYSTEM='1',GIT_ATTR_NOSYSTEM='1',
               GIT_TERMINAL_PROMPT='0',LC_ALL='C')
    return env


def git(root,*args):
    return subprocess.check_output(['/usr/bin/git','-c','core.hooksPath=/dev/null',
        '-c','core.fsmonitor=false','-c','diff.external=', '-C',str(root),*args],env=environment())


def boundary(root):
    root=Path(root)
    if not root.is_absolute() or root.resolve()!=root or not root.is_dir(): raise ValueError('invalid Git root')
    dot=root/'.git'
    if dot.is_symlink() or not dot.is_dir() or dot.resolve()!=dot: raise ValueError('unsupported Git metadata')
    for path in (dot/'config',dot/'config.worktree',dot/'info/attributes'):
        if path.is_symlink() or path.resolve()!=path or (path.exists() and not path.is_file()): raise ValueError('unsafe Git configuration path')
    for path in (dot/'config.worktree',dot/'info/attributes'):
        if path.exists() and path.read_bytes(): raise ValueError('unsafe Git attribute or worktree config')
    raw=git(root,'config','--local','--no-includes','--null','--list')
    for row in raw.split(b'\0'):
        if not row: continue
        key=row.split(b'\n',1)[0].decode('utf-8').lower()
        if (key.startswith(('filter.','include.','includeif.')) or
            key in ('core.attributesfile','core.fsmonitor','core.hookspath','core.sshcommand','extensions.worktreeconfig','diff.external') or
            re.fullmatch(r'merge\..*\.driver',key) or re.fullmatch(r'diff\..*\.(command|textconv)',key)):
            raise ValueError('unsafe local Git configuration: '+key)


def raw_tree(root,commit):
    root=Path(root);boundary(root)
    if not re.fullmatch(r'[0-9a-f]{40}',commit): raise ValueError('invalid commit')
    for record in git(root,'ls-tree','-r','-z',commit).split(b'\0'):
        if not record: continue
        metadata,raw_path=record.split(b'\t',1);mode,kind,blob=metadata.split(b' ')
        if kind!=b'blob' or mode not in (b'100644',b'100755'): raise ValueError('invalid tracked tree mode')
        path=root/os.fsdecode(raw_path)
        if path.is_symlink() or path.resolve()!=path or not path.is_file() or not path.resolve().is_relative_to(root): raise ValueError('invalid tracked path')
        raw=path.read_bytes();oid=hashlib.sha1(b'blob '+str(len(raw)).encode()+b'\0'+raw).hexdigest().encode()
        if oid!=blob or bool(path.stat().st_mode & 0o111)!=(mode==b'100755'): raise ValueError('tracked tree differs')


def untracked_inputs(root, *, generated):
    root=Path(root);boundary(root)
    # These are disjoint inventories: Git's --ignored reports only ignored
    # paths, while --exclude-standard alone reports ordinary untracked paths.
    for options in (('--others','--exclude-standard'),
                    ('--others','--ignored','--exclude-standard')):
        for raw in git(root,'ls-files',*options,'-z').split(b'\0'):
            if not raw: continue
            path=root/os.fsdecode(raw)
            if path.is_symlink() or path.resolve()!=path or not path.is_file(): raise ValueError('invalid untracked input')
            if path.stat().st_mode & 0o111: raise ValueError('untracked executable')
            lower=raw.lower()
            if lower.endswith((b'.py',b'.pyc',b'.pyo',b'.pth',b'.so',b'.pyd',b'.h',b'.hpp',b'.hh',b'.hxx',b'.c',b'.cc',b'.cpp',b'.cxx',b'.sh',b'.bash',b'.pl',b'.rb',b'.js',b'.exe',b'.dll',b'.jar')) or b'__pycache__/' in lower:
                raise ValueError('untracked source or import input')
            # The original copy and reviewed generated graph outputs are the
            # only untracked trees permitted. Source and imports remain forbidden
            # even within these trees. Generated .s and .inc files are outputs
            # used by the existing reviewed build graph.
            if raw.startswith(b'orig/GPOE8P/files/'):
                continue
            if generated and (raw.startswith(b'build/GPOE8P/') or raw.startswith(b'build/capacity-tmp-') or raw in (b'build.ninja',b'objdiff.json',b'compile_commands.json',b'.ninja_log',b'.ninja_deps')):
                continue
            raise ValueError('unexpected untracked input')
''', '<trusted queue git boundary>', 'exec'), _safety.__dict__)

def git(repo, *args):
    _safety.boundary(Path(repo).resolve())
    return _safety.git(repo,*args).decode().strip()

def checked_root(entry):
    root = Path(entry['path'])
    require(root.is_absolute() and root.resolve() == root and root.is_dir(), 'invalid_prepared_root')
    require(git(root, 'rev-parse', 'HEAD') == entry['commit'], 'stale_prepared_commit')
    require(git(root, 'rev-parse', 'HEAD^{tree}') == entry['tree'], 'stale_prepared_tree')
    require(not git(root, 'status', '--porcelain', '--untracked-files=no'), 'dirty_prepared_tree')
    require(not (root / '.venv').exists(), 'candidate_local_interpreter')
    require(digest(root / 'build.ninja') == entry['graph_sha256'], 'stale_reviewed_graph')
    preparation = pinned(entry['preparation'])
    old = json.loads(preparation.read_text())
    require(old.get('prepared') is True and old.get('returncode') == 0, 'missing_exclusive_preparation')
    admission = old['admission']
    for key, expected in {'protocol': 'pso-build-capacity-v2', 'revision': 4,
                          'repo': str(root), 'ninja_sha256': entry['graph_sha256'],
                          'inputs_sha256': entry['inputs_sha256']}.items():
        require(admission.get(key) == expected, 'stale_preparation: ' + key)
    return root


def config_contract(request, environment, review, roots):
    config=request.get('config_admission')
    if config is None: return
    require(request.get('policy')=='recovery' and config==environment.get('config_admission'), 'stale_config_admission')
    checker_path=pinned(config['checker'])
    for root in [Path(request['checkout']).resolve(),*roots.values()]:
        require(not checker_path.resolve().is_relative_to(root), 'checker_inside_root')
    checker=types.ModuleType('_reviewed_config_checker');checker.__file__=str(checker_path)
    exec(compile(checker_path.read_bytes(),str(checker_path),'exec'),checker.__dict__)
    packet=checker.read_packet(config['packet'],[Path(request['checkout']),*roots.values()])
    require(packet['pins']['checker']==config['checker'] and packet['pins']['cli']==request['cli'] and packet['pins']['guard']==request['validator'], 'stale_config_runtime')
    require(packet['pins']['adapter']=={'path':str(Path(__file__).resolve()),'sha256':digest(Path(__file__).resolve())}, 'stale_config_adapter')
    require(Path(packet['pins']['python']['path'])==Path(sys.executable).resolve() and Path(packet['pins']['ninja']['path'])==Path(environment['ninja']).resolve() and Path(packet['pins']['compiler_wrapper']['path'])==Path(environment['wrapper']).resolve(), 'stale_config_tools')
    require(all(Path(packet['configure_paths'][name]['path']) == Path(environment[name]).resolve() for name in ('dtk','objdiff','wrapper','compilers','binutils')), 'stale_config_paths')
    require(packet['pins']['wrapper']==environment['development_capacity']['wrapper'] and packet['pins']['base_validator']==environment['development_capacity']['base_validator'], 'stale_config_harness')
    plan_entry=request['config_plan']
    require(isinstance(plan_entry,dict) and set(plan_entry)=={'path','sha256','packet_sha256'} and plan_entry['packet_sha256']==config['packet']['sha256'], 'missing_config_plan')
    plan=checker.strict_json(checker.file_pin({'path':plan_entry['path'],'sha256':plan_entry['sha256']},[Path(request['checkout']),*roots.values()]).read_bytes())
    require(plan=={'packet_sha256':config['packet']['sha256'],'target':request['target'],'candidate':request['candidate'],'tree':request['tree'],'effective_argv':packet['effective_argv']}, 'stale_config_plan')
    checker.verify_plan(request['checkout'],packet,request['target'],request['candidate'],request['tree'],request['prs'],request['commits'])
    require(review.get('config_plan_sha256')==plan_entry['sha256'] and review.get('config_packet_sha256')==config['packet']['sha256'] and review.get('effective_compile_argv')==packet['effective_argv'] and review.get('configuration_edge_review') is True and review.get('unlisted_edges_unchanged') is True and review.get('compiler_binding_reviewed') is True and review.get('no_setup_execution') is True and review.get('ordered_input_provenance') == packet['ordered_inputs'] and review.get('dependent_compile')==packet['dependent_compile'] and (packet['cumulative']['unit']!=checker.PLAYER_UNIT or review.get('caller_gc26_reviewed') is True), 'missing_config_graph_review')
    expected_argv=hashlib.sha256(json.dumps(packet['effective_argv'],separators=(',',':')).encode()).hexdigest()
    for role in ('baseline','candidate'):
        root=roots[role];entry=review['roots'][role];receipt=pinned(entry['config_preflight'])
        require(not receipt.resolve().is_relative_to(root), 'config_receipt_inside_root')
        pre=checker.strict_json(receipt.read_bytes())
        expected={'version':1,'prepared_config':True,'packet_sha256':config['packet']['sha256'],
                  'root':str(root),'role':role,'target':request['target'],'candidate':request['candidate'],
                  'tree':request['tree'],'root_commit':entry['commit'],'root_tree':entry['tree'],
                  'graph_sha256':entry['graph_sha256'],'checker_sha256':config['checker']['sha256'],
                  'preparer_sha256':packet['pins']['preparer']['sha256'],
                  'original_tree_sha256':entry['original_tree_sha256'],'plan_sha256':plan_entry['sha256'],'effective_argv_sha256':expected_argv}
        require(pre==expected and entry['original_tree_sha256']==packet['originals'][role]['tree_sha256'] and checker.tree_digest(root/'orig/GPOE8P/files')==packet['originals'][role]['tree_sha256'], 'stale_config_preparation')
        checker.check_compile_graph(root,packet,role)
    require(digest(checker_path)==config['checker']['sha256'], 'config_checker_changed')


def load_contract(request, environment):
    capacity = environment['development_capacity']
    require(capacity.get('lane') == 'development', 'development_lane_required')
    wrapper = pinned(capacity['wrapper'])
    base_validator = pinned(capacity['base_validator'])
    review_path = pinned(capacity['review'])
    review = json.loads(review_path.read_text())
    require(review.get('version') == 1 and review.get('verdict') == 'pass'
            and review.get('independent') is True and bool(review.get('reviewer')),
            'independent_graph_review_required')
    for key in ('target', 'candidate', 'tree'):
        require(review.get(key) == request[key], 'stale_review_binding: ' + key)
    require(review.get('wrapper_sha256') == digest(wrapper), 'stale_wrapper_review')
    require(review.get('base_validator_sha256') == digest(base_validator), 'stale_harness_review')
    require(review.get('roots_reserved_until_terminal') is True
            and review.get('shared_inputs_immutable') is True
            and review.get('graph_python_imports_isolated') is True, 'missing_operator_isolation_attestation')
    roots = review['roots']
    require(set(roots) == {'baseline', 'candidate'}, 'two_prepared_roots_required')
    require(roots['baseline']['commit'] == request['target'], 'wrong_baseline_commit')
    require(roots['candidate']['commit'] == request['candidate']
            and roots['candidate']['tree'] == request['tree'], 'wrong_candidate_commit')
    if request.get('config_admission') is not None:
        require(digest(request['environment'])==request.get('environment_sha256'), 'stale_config_environment')
        checkout=Path(request['checkout']).resolve()
        all_roots=[checkout,*(Path(entry['path']).resolve() for entry in roots.values())]
        config=request['config_admission']
        checker_path=pinned(config['checker'])
        require(all(not checker_path.resolve().is_relative_to(root) for root in all_roots), 'checker_inside_root')
        checker=types.ModuleType('_preflight_config_checker');checker.__file__=str(checker_path)
        exec(compile(checker_path.read_bytes(),str(checker_path),'exec'),checker.__dict__)
        packet=checker.read_packet(config['packet'],all_roots)
        require(packet['pins']['checker']==config['checker'] and packet['pins']['cli']==request['cli'], 'stale_config_runtime')
        _safety.boundary(checkout)
        _safety.raw_tree(checkout,request['candidate'])
        _safety.untracked_inputs(checkout,generated=False)
        for entry in roots.values():
            root=Path(entry['path']).resolve()
            _safety.boundary(root)
            _safety.raw_tree(root,entry['commit'])
            _safety.untracked_inputs(root,generated=True)
    paths = {role: checked_root(entry) for role, entry in roots.items()}
    require(not paths['baseline'].is_relative_to(paths['candidate'])
            and not paths['candidate'].is_relative_to(paths['baseline']), 'overlapping_prepared_roots')
    # Neither build root may contain the private evidence or trusted Python code.
    for root in paths.values():
        for evidence in (wrapper, base_validator, review_path, Path(request['environment']),
                         Path(request['state']), Path(__file__).resolve()):
            require(not evidence.resolve().is_relative_to(root), 'evidence_inside_build_root')
    config_contract(request, environment, review, paths)
    return capacity, review, paths


def build(wrapper_entry, entry, receipt, env):
    """Only the reviewed wrapper owns build locks; never take an outer EX gate."""
    wrapper = pinned(wrapper_entry)
    root = checked_root(entry)
    command = [sys.executable, '-I', str(wrapper), '--repo', str(root),
               '--receipt', str(receipt), '--mode', 'isolated', '--lane', 'development',
               '--prepared-receipt', str(pinned(entry['preparation'])),
               '--reviewed-graph-sha256', entry['graph_sha256']]
    # No timeout, lock removal, fallback, or SH->EX escalation: resource and
    # maintenance admission waits remain entirely in the reviewed wrapper.
    with receipt.with_suffix('.adapter.log').open('x') as log:
        result = subprocess.run(command, env=env, stdout=log, stderr=subprocess.STDOUT)
    pinned(wrapper_entry)
    require(result.returncode == 0, 'development_build_rejected: ' + str(receipt))
    record = json.loads(receipt.read_text())
    require(record.get('returncode') == 0 and record.get('lane') == 'development'
            and record.get('slot') in ('development-0', 'development-1') and record.get('mode') == 'isolated'
            and record.get('repo') == str(root), 'invalid_development_receipt')
    for key, value in {'protocol': 'pso-build-capacity-v2', 'revision': 4,
                       'repo': str(root), 'ninja_sha256': entry['graph_sha256'],
                       'inputs_sha256': entry['inputs_sha256']}.items():
        require(record.get('admission', {}).get(key) == value, 'stale_build_admission: ' + key)
    checked_root(entry)
    return record


def check_shared(base, paths, expected):
    current = base.fingerprint(paths)
    require(canonical_hash(current) == expected, 'stale_shared_tools_or_originals')
    return current


def validate(request):
    require(request.get('policy') == 'recovery' and request.get('config_admission') is not None, 'development_config_recovery_required')
    environment = json.loads(Path(request['environment']).read_text())
    capacity, review, roots = load_contract(request, environment)
    base_path = pinned(capacity['base_validator'])
    base = types.ModuleType('_pinned_base_validator')
    base.__file__ = str(base_path)
    exec(compile(base_path.read_bytes(), str(base_path), 'exec'), base.__dict__)
    repo = Path(request['checkout']).resolve()
    state = Path(request['state']).resolve()
    require(git(repo, 'rev-parse', 'HEAD') == request['candidate']
            and git(repo, 'rev-parse', 'HEAD^{tree}') == request['tree'], 'wrong_cli_candidate')
    require(not git(repo, 'status', '--porcelain', '--untracked-files=no'), 'dirty_cli_candidate')
    require(not git(repo, 'diff', '--name-only', request['target'], request['candidate'], '--', 'tools'), 'unsupported_harness_change')
    config_changed=bool(git(repo, 'diff', '--name-only', request['target'], request['candidate'], '--', 'configure.py'))
    require(config_changed == (request.get('config_admission') is not None), 'unsupported_config_change')
    git(repo, 'diff', '--check', request['target'], request['candidate'])
    toolnames = ('ninja', 'dtk', 'objdiff', 'wrapper', 'compilers', 'binutils')
    require(all(Path(environment[name]).is_absolute() for name in toolnames), 'absolute_tools_required')
    tools = {name: Path(environment[name]).resolve(strict=True) for name in toolnames}
    require(all(not tool.is_relative_to(root) for tool in tools.values() for root in roots.values()), 'tool_inside_build_root')
    original = Path(environment['original_files']).resolve(strict=True)
    # Pin all actual reference copies, tools, and the explicitly reviewed graph's
    # Python launcher, not only the canonical source original directory.
    launchers = [pinned(item) for item in review['python_launchers']]
    require(bool(launchers), 'reviewed_python_launcher_required')
    shared = [original, *tools.values(), *launchers,
              *(root / 'orig/GPOE8P/files' for root in roots.values())]
    require(all(p.exists() for p in shared), 'missing_shared_input')
    before = check_shared(base, shared, review['shared_fingerprint_sha256'])
    for root in [original, *(p / 'orig/GPOE8P/files' for p in roots.values())]:
        require(hashlib.sha1((root / 'PsoV3.dol').read_bytes()).hexdigest() == base.DOL_SHA1, 'wrong_original_dol')
    env = os.environ.copy()
    env.pop('PYTHONPATH', None)
    env.pop('GITHUB_STEP_SUMMARY', None)
    env['PYTHONDONTWRITEBYTECODE'] = '1'
    env['PSO_BUILD_NINJA'] = str(tools['ninja'])
    if request.get('config_admission') is not None:
        env['PSO_CONFIG_PACKET_PATH']=request['config_admission']['packet']['path']
        env['PSO_CONFIG_PACKET_SHA256']=request['config_admission']['packet']['sha256']
        request_file=Path(sys.argv[1]).resolve()
        require(request_file.is_file() and json.loads(request_file.read_text())==request, 'stale_config_request')
        env['PSO_CONFIG_REQUEST_PATH']=str(request_file)
        env['PSO_CONFIG_REQUEST_SHA256']=digest(request_file)
    # Existing prepared graph commands use independently reviewed pinned launchers.
    # This new isolated launcher is only for post-build checks, never configure.
    base.PYTHON_DRIVER = 'import sys; sys.dont_write_bytecode=True\n' + base.PYTHON_DRIVER
    launcher = base.python_launcher(state, list(roots.values()))
    env['PSO_QUEUE_PYTHON'] = str(launcher)
    candidate = roots['candidate']
    load_contract(request, environment)
    base.run([sys.executable, '-I', '-B', '-c', "import pathlib; [compile(p.read_bytes(),str(p),'exec') for p in [pathlib.Path('configure.py'),*pathlib.Path('tools').rglob('*.py')]]"], candidate, env)
    load_contract(request, environment)
    base.run([sys.executable, '-I', '-c', base.PYTHON_DRIVER, str(candidate), '--queue-tests'], candidate, env)
    results = {}
    for role in ('baseline', 'candidate'):
        # Recheck all identities before each job, including while the preceding
        # role was waiting for resources/maintenance or compiling.
        load_contract(request, environment)
        require(base.fingerprint(shared) == before, 'shared_inputs_changed_before_build')
        receipt = state / ('development-' + role + '-' + str(time.time_ns()) + '.json')
        record = build(capacity['wrapper'], review['roots'][role], receipt, env)
        root = roots[role]
        require(hashlib.sha1((root / 'build/GPOE8P/psov3.dol').read_bytes()).hexdigest() == base.DOL_SHA1, 'built_dol_mismatch')
        results[role] = {'receipt': str(receipt), 'measurement': record.get('measurement'),
                         'waits': {k: v for k, v in record.items() if k.endswith('wait_seconds')},
                         'provenance': base.selected_inputs(root, tools['ninja'], env)}
    if request.get('config_admission') is not None:
        require(all(results[role]['provenance']==review['ordered_input_provenance'][role] for role in ('baseline','candidate')), 'ordered_input_provenance_changed')
    check = state / ('development-coverage-' + str(time.time_ns()) + '.json')
    load_contract(request, environment)
    base.run([str(launcher), 'tools/check_pr.py', '--no-build', '--baseline',
              str(roots['baseline'] / 'build/GPOE8P/report.json'), '--json', str(check)], candidate, env)
    coverage = json.loads(check.read_text())
    require(coverage['result'] == 'pass' and all(c['ok'] is True for c in coverage['checks'])
            and not coverage['delta']['failures'], 'coverage_or_link_rejected')
    load_contract(request, environment)
    require(base.fingerprint(shared) == before, 'shared_inputs_changed_during_validation')
    require(not git(repo, 'status', '--porcelain', '--untracked-files=no'), 'cli_candidate_changed')
    # The public entry point is not wrapped by the acceptance guard. Run its
    # pinned raw-interval and unfiltered loss checks directly before reporting.
    guard_path = pinned(request['validator'])
    require(all(not guard_path.resolve().is_relative_to(root) for root in roots.values()), 'guard_inside_build_root')
    guard = types.ModuleType('_pinned_zero_loss_guard'); guard.__file__ = str(guard_path)
    exec(compile(guard_path.read_bytes(), str(guard_path), 'exec'), guard.__dict__)
    reports = []
    for role in ('baseline', 'candidate'):
        report = roots[role] / 'build/GPOE8P/report.json'
        require(report.is_file() and not report.is_symlink() and report.resolve() == report, 'invalid_raw_report_path')
        raw = report.read_bytes(); reports.append((report, hashlib.sha256(raw).hexdigest(), json.loads(raw)))
    coverage_sha = digest(check)
    zero_losses = guard.require_zero_loss(coverage, reports[0][2], reports[1][2])
    require(all(digest(path) == sha for path, sha, _ in reports) and digest(check) == coverage_sha
            and digest(guard_path) == request['validator']['sha256'], 'evidence_changed_during_guard')
    load_contract(request, environment)
    require(base.fingerprint(shared) == before, 'shared_inputs_changed_during_guard')
    return {'version': 1, 'kind': 'development-only', 'target': request['target'], 'tree': request['tree'],
            'checks': {k: True for k in ('source', 'build', 'coverage', 'link', 'provenance', 'dol')},
            'losses': {'code': 0, 'data': 0, 'link': 0},
            'delta': {k: v['delta'] for k, v in coverage['delta']['metrics'].items()},
            'dol_sha1': base.DOL_SHA1, 'coverage_receipt': str(check),
            'development_builds': results, 'zero_lost_address_ranges': zero_losses,
            'raw_report_sha256': {role: reports[i][1] for i, role in enumerate(('baseline', 'candidate'))},
            'coverage_receipt_sha256': coverage_sha, 'review_sha256': digest(pinned(capacity['review']))}


def main():
    if len(sys.argv)==3 and sys.argv[1]=='--check-config':
        request=json.loads(Path(sys.argv[2]).read_text())
        require(request.get('config_admission') is not None, 'missing_config_admission')
        environment=json.loads(Path(request['environment']).read_text())
        load_contract(request,environment)
        return
    request = json.loads(Path(sys.argv[1]).read_text())
    state = Path(request['state'])
    output_path = Path(request['output'])
    require(state.is_absolute() and state.resolve() == state and state.is_dir(), 'invalid_state')
    require(output_path.is_absolute() and output_path.parent.resolve() == state and not output_path.is_symlink(), 'invalid_development_output')
    result = validate(request)
    # Create only a private development result, never a publication artifact.
    with output_path.open('x') as output:
        json.dump(result, output, indent=2)
        output.write('\n')


if __name__ == '__main__':
    main()
