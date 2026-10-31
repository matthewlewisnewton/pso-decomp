#!/usr/bin/env python3
"""Private, preselected acceptance adapter. Never prepares or approves a graph."""
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


def git(repo, *args):
    return subprocess.check_output(['git', '-c', 'core.hooksPath=/dev/null', *args],
                                   cwd=repo, text=True).strip()


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


def load_contract(request, environment):
    capacity = environment['acceptance_capacity']
    require(capacity.get('lane') == 'acceptance', 'acceptance_lane_required')
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
    paths = {role: checked_root(entry) for role, entry in roots.items()}
    require(not paths['baseline'].is_relative_to(paths['candidate'])
            and not paths['candidate'].is_relative_to(paths['baseline']), 'overlapping_prepared_roots')
    # Neither build root may contain the private evidence or trusted Python code.
    for root in paths.values():
        for evidence in (wrapper, base_validator, review_path, Path(request['environment']),
                         Path(request['state']), Path(__file__).resolve()):
            require(not evidence.resolve().is_relative_to(root), 'evidence_inside_build_root')
    return capacity, review, paths


def build(wrapper_entry, entry, receipt, env):
    """Only the reviewed wrapper owns build locks; never take an outer EX gate."""
    wrapper = pinned(wrapper_entry)
    root = checked_root(entry)
    command = [sys.executable, '-I', str(wrapper), '--repo', str(root),
               '--receipt', str(receipt), '--mode', 'isolated', '--lane', 'acceptance',
               '--prepared-receipt', str(pinned(entry['preparation'])),
               '--reviewed-graph-sha256', entry['graph_sha256']]
    # No timeout, lock removal, fallback, or SH->EX escalation: resource and
    # maintenance admission waits remain entirely in the reviewed wrapper.
    with receipt.with_suffix('.adapter.log').open('x') as log:
        result = subprocess.run(command, env=env, stdout=log, stderr=subprocess.STDOUT)
    pinned(wrapper_entry)
    require(result.returncode == 0, 'acceptance_build_rejected: ' + str(receipt))
    record = json.loads(receipt.read_text())
    require(record.get('returncode') == 0 and record.get('lane') == 'acceptance'
            and record.get('slot') == 'acceptance' and record.get('mode') == 'isolated'
            and record.get('repo') == str(root), 'invalid_acceptance_receipt')
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
    require(request['policy'] in ('recovery', 'source-maintenance'), 'acceptance_adapter_source_only')
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
    require(not git(repo, 'diff', '--name-only', request['target'], request['candidate'],
                    '--', 'tools', 'configure.py'), 'unsupported_harness_change')
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
    # Existing prepared graph commands use independently reviewed pinned launchers.
    # This new isolated launcher is only for post-build checks, never configure.
    launcher = base.python_launcher(state, list(roots.values()))
    env['PSO_QUEUE_PYTHON'] = str(launcher)
    candidate = roots['candidate']
    base.run([sys.executable, '-I', '-m', 'compileall', '-q', 'configure.py', 'tools'], candidate, env)
    base.run([sys.executable, '-I', '-c', base.PYTHON_DRIVER, str(candidate), '--queue-tests'], candidate, env)
    results = {}
    for role in ('baseline', 'candidate'):
        # Recheck all identities before each job, including while the preceding
        # role was waiting for resources/maintenance or compiling.
        load_contract(request, environment)
        require(base.fingerprint(shared) == before, 'shared_inputs_changed_before_build')
        receipt = state / ('acceptance-' + role + '-' + str(time.time_ns()) + '.json')
        record = build(capacity['wrapper'], review['roots'][role], receipt, env)
        root = roots[role]
        require(hashlib.sha1((root / 'build/GPOE8P/psov3.dol').read_bytes()).hexdigest() == base.DOL_SHA1, 'built_dol_mismatch')
        results[role] = {'receipt': str(receipt), 'measurement': record.get('measurement'),
                         'waits': {k: v for k, v in record.items() if k.endswith('wait_seconds')},
                         'provenance': base.selected_inputs(root, tools['ninja'], env)}
    check = state / ('acceptance-coverage-' + str(time.time_ns()) + '.json')
    base.run([str(launcher), 'tools/check_pr.py', '--no-build', '--baseline',
              str(roots['baseline'] / 'build/GPOE8P/report.json'), '--json', str(check)], candidate, env)
    coverage = json.loads(check.read_text())
    require(coverage['result'] == 'pass' and all(c['ok'] is True for c in coverage['checks'])
            and not coverage['delta']['failures'], 'coverage_or_link_rejected')
    load_contract(request, environment)
    require(base.fingerprint(shared) == before, 'shared_inputs_changed_during_validation')
    require(not git(repo, 'status', '--porcelain', '--untracked-files=no'), 'cli_candidate_changed')
    return {'version': 1, 'target': request['target'], 'tree': request['tree'],
            'checks': {k: True for k in ('source', 'build', 'coverage', 'link', 'provenance', 'dol')},
            'losses': {'code': 0, 'data': 0, 'link': 0},
            'delta': {k: v['delta'] for k, v in coverage['delta']['metrics'].items()},
            'dol_sha1': base.DOL_SHA1, 'coverage_receipt': str(check),
            'acceptance_builds': results, 'review_sha256': digest(pinned(capacity['review']))}


def main():
    request = json.loads(Path(sys.argv[1]).read_text())
    result = validate(request)
    # No success artifact on rejection; the unchanged CLI journals the failure.
    with Path(request['output']).open('x') as output:
        json.dump(result, output, indent=2)
        output.write('\n')


if __name__ == '__main__':
    main()
