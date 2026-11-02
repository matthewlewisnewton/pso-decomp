#!/usr/bin/env python3
"""Pinned local validator for merge_batch.py; original inputs never leave this host.

Recovery batches must preserve the target's complete tools/ and configure.py.
This conservative restriction keeps PR code from weakening its own check harness.
Tooling changes use separately reviewed maintenance batches.
"""
from __future__ import annotations
import fcntl
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import time

DOL_SHA1 = '0d85744b51d7379efb025a943d0cd5aaae2191a3'


# Executed only with Python -I from this pinned external file. The candidate root
# is never a Python import directory. Only the reviewed tools package is loaded
# explicitly; standard library/site packages retain precedence over tools helpers.
PYTHON_DRIVER = r"""
import importlib.util, os, pathlib, sys, unittest
root = pathlib.Path(sys.argv[1]).resolve()
args = sys.argv[2:]
while args and args[0] == '-I':
    args.pop(0)
package = root / 'tools/__init__.py'
if package.exists():
    spec = importlib.util.spec_from_file_location('tools', package,
        submodule_search_locations=[str(root / 'tools')])
    module = importlib.util.module_from_spec(spec)
    sys.modules['tools'] = module
    spec.loader.exec_module(module)
sys.path.append(str(root / 'tools'))
if args == ['--queue-tests']:
    # unittest was imported from the isolated interpreter before project code.
    suite = unittest.defaultTestLoader.discover(str(root / 'tools/tests'))
    raise SystemExit(not unittest.TextTestRunner(verbosity=2).run(suite).wasSuccessful())
script = pathlib.Path(args[0]).resolve()
if script != root / 'configure.py' and not script.is_relative_to(root / 'tools'):
    raise SystemExit('Unreviewed Python entry point: ' + str(script))
if script.suffix != '.py':
    raise SystemExit('Python source entry point required')
launcher = os.environ.get('PSO_QUEUE_PYTHON')
if not launcher:
    raise SystemExit('Pinned Python launcher missing')
sys.executable = launcher
sys.argv = [str(script), *args[1:]]
namespace = {'__name__': '__main__', '__file__': str(script), '__package__': None}
exec(compile(script.read_bytes(), str(script), 'exec'), namespace)
"""


def python_launcher(state, roots):
    path = state / ('trusted-python-' + str(time.time_ns()))
    # No candidate content is interpolated as code. The launcher derives the exact
    # allowed root from cwd and invokes the pinned driver's isolated interpreter.
    source = (f'#!{sys.executable} -I\n'
              'import os,sys\n'
              f'roots = {repr([str(p.resolve()) for p in roots])}\n'
              'root = os.path.realpath(os.getcwd())\n'
              "if root not in roots: raise SystemExit('Unreviewed checkout root')\n"
              f'code = {PYTHON_DRIVER!r}\n'
              f'os.execv({sys.executable!r}, [{sys.executable!r}, "-I", "-c", code, root, *sys.argv[1:]])\n')
    with path.open('x') as out:
        out.write(source)
    path.chmod(0o700)
    return path


def run(args, cwd, env=None, pass_fds=()):
    result = subprocess.run(args, cwd=cwd, env=env, text=True, capture_output=True, pass_fds=pass_fds)
    if result.returncode:
        print(result.stdout[-4000:] + result.stderr[-4000:], file=sys.stderr)
        result.check_returncode()
    return result.stdout


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def fingerprint(paths):
    result = {}
    for path in paths:
        for f in sorted(path.rglob('*')) if path.is_dir() else [path]:
            if f.is_file():
                result[str(f)] = sha(f)
    return result


def selected_inputs(repo, ninja, env):
    output = run([str(ninja), '-t', 'query', 'build/GPOE8P/psov3.elf'], repo, env)
    inputs = [line.strip() for line in output.split('  outputs:')[0].splitlines()
              if line.startswith('    build/') and line.strip().endswith('.o')]
    assert inputs and len(inputs) == len(set(inputs)), 'Missing or duplicate actual link inputs'
    report = json.loads((repo / 'build/GPOE8P/report.json').read_text())
    actual = {p.removeprefix('build/GPOE8P/src/').removesuffix('.o') for p in inputs if '/src/' in p}
    declared = {u['name'].removeprefix('psov3/') for u in report['units'] if u.get('metadata', {}).get('complete')}
    assert actual == declared, 'Report source selection disagrees with actual Ninja linker inputs'
    return {'ordered_inputs_sha256': hashlib.sha256('\n'.join(inputs).encode()).hexdigest(),
            'source_inputs': len(actual), 'fallback_inputs': len(inputs) - len(actual)}


def main():
    request = json.loads(Path(sys.argv[1]).read_text())
    if (request.get('development_only') is True or request.get('publication_authorized') is False
            or request.get('purpose') == 'plan-development'
            or request.get('kind') == 'development-only'
            or request.get('state') in ('planning-development', 'development-planned')):
        raise RuntimeError('development_plan_not_validation')
    repo = Path(request['checkout']).resolve()
    state = Path(request['state']).resolve()
    environment = json.loads(Path(request['environment']).read_text())
    result = {'version': 1, 'target': request['target'], 'tree': request['tree'], 'checks': {}}
    # The pinned harness and all child Python entry points use controlled imports.
    source_env = os.environ.copy()
    source_env.pop('PYTHONPATH', None)
    source_env['PYTHONDONTWRITEBYTECODE'] = '1'
    assert run(['git', 'rev-parse', 'HEAD^{tree}'], repo).strip() == request['tree']
    run(['git', 'diff', '--check', request['target'], request['candidate']], repo)
    if request['policy'] == 'recovery':
        assert not run(['git', 'diff', '--name-only', request['target'], request['candidate'], '--', 'tools', 'configure.py'], repo), 'Recovery batch changes trusted build/check scripts'
    run([sys.executable, '-I', '-m', 'compileall', '-q', 'configure.py', 'tools'], repo)
    run([sys.executable, '-I', '-c', PYTHON_DRIVER, str(repo), '--queue-tests'], repo, source_env)
    result['checks']['source'] = True
    if request['policy'] == 'maintenance':
        Path(request['output']).write_text(json.dumps(result, indent=2))
        return
    changed = run(['git', 'diff', '--name-only', request['target'], request['candidate'], '--', 'tools', 'configure.py'], repo)
    assert not changed, 'Recovery batch changes trusted build/check scripts; review and land a maintenance batch first'
    assert environment['version'] == 1
    toolnames = ('ninja', 'dtk', 'objdiff', 'wrapper', 'compilers', 'binutils')
    tools = {name: Path(environment[name]).resolve(strict=True) for name in toolnames}
    original = Path(environment['original_files']).resolve(strict=True)
    assert hashlib.sha1((original / 'PsoV3.dol').read_bytes()).hexdigest() == DOL_SHA1
    env = os.environ.copy()
    env['PATH'] = str(tools['ninja'].parent) + ':' + env['PATH']
    env['PYTHONDONTWRITEBYTECODE'] = '1'
    env.pop('GITHUB_STEP_SUMMARY', None)
    env.pop('PYTHONPATH', None)
    # Fresh baseline, never reuse evidence against a different target. Keep every
    # old output on retries; checkout state is private and no cleanup is performed.
    baseline = state / ('baseline-' + str(time.time_ns()))
    run(['git', 'clone', '--shared', '--no-checkout', str(repo), str(baseline)], state)
    run(['git', '-c', 'core.hooksPath=/dev/null', 'checkout', '--detach', request['target']], baseline)
    assert not (repo / '.venv').exists(), 'Candidate-local interpreter hooks are not supported'
    launcher = python_launcher(state, [baseline, repo])
    launcher_hash = sha(launcher)
    env['PSO_QUEUE_PYTHON'] = str(launcher)
    waited = time.monotonic()
    # Existing legacy EX gate remains authoritative until the separate admission
    # protocol is fixed/reviewed. No opt-in concurrency bypass here.
    with open('/tmp/pso-decomp-full-build.lock', 'a') as lock:
        fcntl.flock(lock, fcntl.LOCK_EX)
        result['lock_wait_seconds'] = time.monotonic() - waited
        before = fingerprint([original, *tools.values()])
        for checkout in (baseline, repo):
            destination = checkout / 'orig/GPOE8P/files'
            if destination.exists():
                assert fingerprint([destination]) == {str(destination / Path(k).relative_to(original)): v
                                                     for k, v in fingerprint([original]).items()}
            else:
                destination.parent.mkdir(parents=True, exist_ok=True)
                # Local copy only; cp supports reflinks on the development host.
                run(['cp', '-a', '--reflink=auto', str(original), str(destination)], checkout)
            configure = [str(launcher), 'configure.py']
            for name in toolnames[1:]:
                configure += ['--' + name, str(tools[name])]
            run(configure, checkout, env, pass_fds=(lock.fileno(),))
            started = time.monotonic()
            log = state / ('baseline-build.log' if checkout == baseline else 'candidate-build.log')
            with log.open('a') as out:
                subprocess.run([str(tools['ninja']), '-j2'], cwd=checkout, env=env,
                               stdout=out, stderr=subprocess.STDOUT, check=True, pass_fds=(lock.fileno(),))
            result['baseline_build_seconds' if checkout == baseline else 'candidate_build_seconds'] = time.monotonic() - started
            assert hashlib.sha1((checkout / 'build/GPOE8P/psov3.dol').read_bytes()).hexdigest() == DOL_SHA1
            result['baseline_provenance' if checkout == baseline else 'candidate_provenance'] = selected_inputs(checkout, tools['ninja'], env)
        check = state / ('coverage-' + str(time.time_ns()) + '.json')
        # Tools are byte-identical to the trusted target; config/source remains the
        # actual candidate's. Includes original-address and selected-source checks.
        run([str(launcher), 'tools/check_pr.py', '--no-build', '--baseline',
             str(baseline / 'build/GPOE8P/report.json'), '--json', str(check)], repo, env, pass_fds=(lock.fileno(),))
        data = json.loads(check.read_text())
        assert data['result'] == 'pass' and all(c['ok'] is True for c in data['checks'])
        assert not data['delta']['failures']
        assert fingerprint([original, *tools.values()]) == before, 'Shared tools/original inputs changed'
        assert sha(launcher) == launcher_hash, 'Pinned Python launcher changed'
    # Candidate source/config/tools must not have been rewritten by validation.
    assert not run(['git', 'status', '--porcelain', '--untracked-files=no'], repo).strip()
    result.update(checks={k: True for k in ('source', 'build', 'coverage', 'link', 'provenance', 'dol')},
                  losses={'code': 0, 'data': 0, 'link': 0},
                  delta={k: v['delta'] for k, v in data['delta']['metrics'].items()},
                  dol_sha1=DOL_SHA1, coverage_receipt=str(check))
    Path(request['output']).write_text(json.dumps(result, indent=2))


if __name__ == '__main__':
    main()
