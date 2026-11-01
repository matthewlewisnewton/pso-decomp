#!/usr/bin/env python3
"""Cooperative PSO build slots; reviewed graphs only, not a security sandbox."""
import argparse
from contextlib import ExitStack
import fcntl
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import tempfile
import time

LEGACY = Path('/tmp/pso-decomp-full-build.lock')
CAPACITY = Path('/tmp/pso-build-capacity-v2')
ENABLE = Path('/tmp/pso-build-capacity-v2-enabled.json')
PROTOCOL = 'pso-build-capacity-v2'
REVISION = 4
# All workers must use the same stable, reviewed Ninja executable.
NINJA = os.environ.get('PSO_BUILD_NINJA', '')
PINNED_NINJA = None
BLOCKED_RULES = {'configure', 'split', 'download_tool'}
KNOWN_RULES = BLOCKED_RULES | {'decompctx', 'link', 'elf2dol', 'mwcc', 'mwcc_sjis',
    'mwcc_extab', 'mwcc_sjis_extab', 'as', 'mwcc_pch', 'mwcc_pch_sjis', 'orig_asm',
    'verify_pso_data', 'makerel', 'check', 'progress', 'report', 'report_changes',
    'changes_fmt', 'changes_md', 'dol_diff', 'dol_apply'}
FIXED = ['build.ninja', 'objdiff.json', 'compile_commands.json', '.ninja_log', '.ninja_deps']


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def pin_ninja(repo, expected=None):
    """Require an explicitly reviewed absolute tool; never search candidate PATH."""
    global PINNED_NINJA
    configured = Path(NINJA)
    if not NINJA or not configured.is_absolute():
        raise RuntimeError('PSO_BUILD_NINJA must name an explicit reviewed absolute executable')
    executable = configured.resolve(strict=True)
    roots = [repo.resolve()]
    registry = CAPACITY / 'roots.json'
    if registry.exists():
        roots.extend(Path(root).resolve() for root in json.loads(registry.read_text()))
    if any(executable.is_relative_to(root) or configured.is_relative_to(root) for root in roots):
        raise RuntimeError('Ninja executable is inside a candidate writable workspace')
    if not executable.is_file() or not os.access(executable, os.X_OK):
        raise RuntimeError('Ninja is not an executable regular file')
    stat = executable.stat()
    identity = dict(path=str(executable), sha256=digest(executable),
                    device=stat.st_dev, inode=stat.st_ino, size=stat.st_size,
                    mtime_ns=stat.st_mtime_ns)
    if expected is not None and identity != expected:
        raise RuntimeError('Ninja identity differs from preparation evidence')
    if PINNED_NINJA is not None and identity != PINNED_NINJA:
        raise RuntimeError('Ninja executable changed during operation')
    PINNED_NINJA = identity
    return identity


def ninja_command(repo):
    return pin_ninja(repo)['path']


def safe_destination(repo, path):
    """Reject symlinks at every component, even inward links; reject hardlinks."""
    path = Path(os.path.abspath(path))
    if not path.is_relative_to(repo):
        raise RuntimeError(f'write outside checkout: {path}')
    for part in [path, *path.parents]:
        if part == repo:
            break
        if part.is_symlink():
            raise RuntimeError(f'symlink in writable path: {part}')
        if part.is_file() and part.stat().st_nlink != 1:
            raise RuntimeError(f'hard-linked writable file: {part}')
    return path


def writable_trees(repo):
    # Covers undeclared DTK outputs, compiler depfiles, Ninja response files,
    # original-assembly includes, temporary files, and config scan reports.
    for name in ['build', 'config']:
        root = safe_destination(repo, repo / name)
        if root.exists():
            for parent, dirs, files in os.walk(root, followlinks=False):
                for item in dirs + files:
                    safe_destination(repo, Path(parent) / item)
    for name in FIXED:
        safe_destination(repo, repo / name)


def frozen_graph(text):
    """Keep command identities; replace setup edges with existing-file phony edges.

    Only after setup_preflight verifies the untouched graph needs no setup work.
    Phony leaves preserve existing output mtimes without executing setup commands.
    """
    logical = re.sub(r'\$\r?\n[ \t]*', '', text)
    result, skip_bindings = [], False
    for line in logical.splitlines():
        if re.match(r'^(include|subninja)\s', line) or re.match(r'^\s*builddir\s*=', line):
            raise RuntimeError('included graphs and custom Ninja builddir are not admitted')
        if line.startswith('rule ') and line[5:].strip() not in KNOWN_RULES:
            raise RuntimeError(f'unreviewed rule: {line[5:].strip()}')
        if line.startswith('build '):
            if '$:' in line or '$ ' in line:
                raise RuntimeError('escaped build paths require separate review')
            left, right = line.split(':', 1)
            skip_bindings = right.split()[0] in BLOCKED_RULES
            if skip_bindings:
                # Keep both explicit and implicit outputs, without any dependencies.
                line = left.replace(' | ', ' ') + ': phony'
        elif line and not line[0].isspace() and not line.startswith('#'):
            skip_bindings = False
        elif skip_bindings and line[:1].isspace():
            continue
        result.append(line)
    return '\n'.join(result) + '\n'


def setup_preflight(repo, original_snapshot):
    """Dry-run the unmodified graph; never execute or rewrite a setup command."""
    entries = json.loads(subprocess.check_output(
        [ninja_command(repo), '-f', str(original_snapshot), '-t', 'compdb', *sorted(BLOCKED_RULES)],
        cwd=repo, text=True))
    blocked = {entry['command'] for entry in entries}
    if any('\n' in command for command in blocked):
        raise RuntimeError('multiline setup commands require separate review')
    evidence = []
    env = dict(os.environ, NINJA_STATUS='[%f/%t] ', LC_ALL='C')
    for target in ('build.ninja', 'progress'):
        proc = subprocess.run([ninja_command(repo), '-f', str(original_snapshot), '-n', '-v', target],
                              cwd=repo, text=True, capture_output=True, env=env)
        if proc.returncode:
            raise RuntimeError(f'preflight failed for {target}: {proc.stdout} {proc.stderr}')
        planned = [m.group(1) for line in proc.stdout.splitlines()
                   if (m := re.match(r'^\[\d+/\d+\] (.*)$', line))]
        dirty = sorted(set(planned) & blocked)
        if dirty:
            raise RuntimeError(f'exclusive preparation required; setup is dirty: {dirty}')
        evidence.append(dict(target=target, planned_commands=len(planned), setup_commands=0))
    return evidence


def side_destinations(text):
    """Expand only path bindings in the generated single-file PSO Ninja dialect."""
    logical = re.sub(r'\$\r?\n[ \t]*', '', text)
    global_vars, rules, edges = {}, {}, []
    scope = global_vars
    for line in logical.splitlines():
        if not line or line.startswith('#'):
            continue
        if line.startswith('rule '):
            scope = rules.setdefault(line[5:].strip(), {})
        elif line.startswith('build '):
            # Generated paths do not use Ninja's escaped colon/space syntax.
            if '$:' in line or '$ ' in line:
                raise RuntimeError('escaped build paths require separate review')
            left, right = line[6:].split(':', 1)
            rule = right.split()[0]
            scope = {}
            edges.append((left.split('|')[0].strip(), rule, scope))
        elif line[0].isspace():
            if '=' in line:
                key, value = line.strip().split('=', 1)
                scope[key.strip()] = value.strip()
        elif '=' in line:
            key, value = line.split('=', 1)
            global_vars[key.strip()] = value.strip()
            scope = global_vars
        else:
            scope = global_vars
    token = re.compile(r'\$\{([^}]+)\}|\$([a-zA-Z0-9_]+)')
    for outputs, rule, edge in edges:
        if rule == 'phony':
            continue
        values = dict(global_vars, **edge)
        values['out'] = outputs
        def expand(value, seen=()):
            def replace(match):
                key = match.group(1) or match.group(2)
                if key in seen or key not in values:
                    raise RuntimeError(f'unresolved path binding: {key}')
                return expand(values[key], seen + (key,))
            result = token.sub(replace, value)
            if '$' in result or any(c.isspace() for c in result):
                raise RuntimeError(f'unsupported path binding: {result}')
            return result
        for key in ('depfile', 'rspfile'):
            value = edge.get(key, rules.get(rule, {}).get(key))
            if value:
                yield expand(value)
        for key in ('basedir', 'out_dir', 'asm_dir'):
            if key in edge:
                yield expand(edge[key])


def inputs_fingerprint(repo):
    # All tracked source/config/tool code, plus generated objdiff configuration.
    paths = subprocess.check_output(['git', 'ls-files', '-z'], cwd=repo).decode().split('\0')
    paths = sorted(set(p for p in paths if p) | {'build.ninja', 'objdiff.json'})
    h = hashlib.sha256()
    for name in paths:
        path = repo / name
        if path.is_symlink():
            raise RuntimeError(f'tracked input symlink needs separate review: {name}')
        h.update(name.encode() + b'\0')
        h.update(path.read_bytes())
        h.update(b'\0')
    return h.hexdigest()


def audit(repo):
    repo = repo.resolve(strict=True)
    writable_trees(repo)
    graph = (repo / 'build.ninja').read_text()
    frozen_graph(graph)
    for value in side_destinations(graph):
        path = safe_destination(repo, repo / value)
        if not path.is_relative_to(repo / 'build'):
            raise RuntimeError(f'side output outside build tree: {value}')
    rows = subprocess.check_output([ninja_command(repo), '-t', 'targets', 'all'], cwd=repo, text=True).splitlines()
    outputs = []
    for row in rows:
        value, rule = row.rsplit(': ', 1)
        if rule == 'phony':
            continue
        path = safe_destination(repo, repo / value)
        # Review of this PSO graph permits side effects only in these trees/files.
        if not (path.is_relative_to(repo / 'build') or path.is_relative_to(repo / 'config')
                or value in FIXED or (value, rule) in {('progress', 'progress'),
                    ('changes', 'changes_fmt'), ('changes_all', 'changes_fmt'),
                    ('dol_diff', 'dol_diff'), ('dol_apply', 'dol_apply')}):
            raise RuntimeError(f'output outside reviewed writable roots: {value}')
        for suffix in ('.d', '.rsp'):
            safe_destination(repo, Path(str(path) + suffix))
        outputs.append(value)
    # Match the actual generated verify command, not the tool's CLI default.
    logical = re.sub(r'\$\r?\n[ \t]*', '', graph)
    disc_args = re.findall(r'tools/pso_assets\.py verify --disc-root ([^\s]+)', logical)
    if len(disc_args) > 1 or (disc_args and '$' in disc_args[0]):
        raise RuntimeError('ambiguous original-input root requires review')
    disc = repo / (disc_args[0] if disc_args else 'orig/GPOE8P')
    manifest = repo / 'config/GPOE8P/data.json'
    data = json.loads(manifest.read_text())
    missing = [r['path'] for r in data['files'] if not (disc / r['path']).is_file()]
    if not (disc / 'files/PsoV3.dol').is_file():
        missing.append('files/PsoV3.dol')
    if missing:
        raise RuntimeError(f'original extraction would be needed: {missing}')
    return dict(protocol=PROTOCOL, revision=REVISION, repo=str(repo), admitted=True,
                ninja_sha256=digest(repo / 'build.ninja'),
                inputs_sha256=inputs_fingerprint(repo), ninja_tool=pin_ninja(repo), output_count=len(outputs),
                original_root=str(disc.resolve()), no_original_extraction_needed=True,
                limitation='Reviewed PSO commands only; shared inputs/tools must remain immutable.')


def take(stack, path, mode):
    path.parent.mkdir(parents=True, exist_ok=True)
    handle = stack.enter_context(path.open('a'))
    fcntl.flock(handle, mode)
    return handle


def register_root(repo, capacity):
    """Persistent cooperative registry rejects nested checkout roots, even after exit."""
    with ExitStack() as stack:
        take(stack, capacity / 'registry.lock', fcntl.LOCK_EX)
        path = capacity / 'roots.json'
        roots = json.loads(path.read_text()) if path.exists() else []
        root = str(repo.resolve())
        for other in map(Path, roots):
            if other != Path(root) and (other.is_relative_to(root) or Path(root).is_relative_to(other)):
                raise RuntimeError(f'overlapping registered checkout roots: {root}, {other}')
        if root not in roots:
            # Readers/writers all hold registry.lock. No automatic registry cleanup.
            with tempfile.NamedTemporaryFile(mode='w', dir=capacity, delete=False) as output:
                json.dump(roots + [root], output)
                temp = output.name
            os.replace(temp, path)


def capacity_policy(marker):
    development = marker.get('development_slots', 1)
    total = marker.get('total_slots', 2)
    if type(development) is not int or development not in (1, 2) or total != 1 + development:
        raise RuntimeError('expected one acceptance slot and one/two development slots')
    if total > 2 and not (marker.get('expansion_authorization') and marker.get('measurement_receipt')):
        raise RuntimeError('three slots require parent authorization and measured trial receipt')
    return development


def resources_available(lane):
    """Conservative machine-wide admission guard; never interrupts active work."""
    available = int(re.search(r'^MemAvailable:\s+(\d+)',
                    Path('/proc/meminfo').read_text(), re.M).group(1)) * 1024
    # Development leaves another build's reserve available for acceptance.
    reserve = (24 if lane == 'development' else 12) * 1024**3
    limit = max(1, os.cpu_count() or 1) * 1.5
    return available >= reserve and os.getloadavg()[0] <= limit


def acquire(stack, repo, isolated, legacy=LEGACY, capacity=CAPACITY,
            lane='development', development_slots=1, resource_guard=None):
    if lane not in ('acceptance', 'development') or development_slots not in (1, 2):
        raise RuntimeError('invalid lane configuration')
    started = time.monotonic()
    register_root(repo, capacity)
    key = hashlib.sha256(str(repo.resolve()).encode()).hexdigest()
    workspace = take(stack, capacity / ('workspace-' + key + '.lock'), fcntl.LOCK_EX)
    workspace_done = time.monotonic()
    # Advertise acceptance only after owning the workspace, before slot/legacy waits.
    # Otherwise same-workspace development can wait on intent while acceptance
    # waits on its workspace. Kernel descriptor lifetime avoids stale PID files.
    intent = stack.enter_context((capacity / 'acceptance-intent.lock').open('a'))
    if lane == 'acceptance':
        fcntl.flock(intent, fcntl.LOCK_SH)
    handles = [workspace]
    slot_name = None
    if isolated:
        names = ['acceptance'] if lane == 'acceptance' else [f'development-{i}' for i in range(development_slots)]
        slots = [stack.enter_context((capacity / f'{name}.lock').open('a')) for name in names]
        while slot_name is None:
            for name, slot in zip(names, slots):
                try:
                    fcntl.flock(slot, fcntl.LOCK_EX | fcntl.LOCK_NB)
                    slot_name = name
                    handles.append(slot)
                    break
                except BlockingIOError:
                    continue
            if slot_name is None:
                time.sleep(0.1)
    slot_done = time.monotonic()
    gate = stack.enter_context(legacy.open('a'))
    # New maintenance announces its request through the turnstile. Once acquired,
    # active shared holders drain; new shared admissions cannot replenish them.
    turn = stack.enter_context((capacity / 'maintenance-turnstile.lock').open('a'))
    while True:
        turn_held = intent_held = False
        try:
            if lane == 'development':
                fcntl.flock(intent, fcntl.LOCK_EX | fcntl.LOCK_NB)
                intent_held = True
            if resource_guard is not None and not resource_guard(lane):
                raise BlockingIOError('resource reserve')
            fcntl.flock(turn, (fcntl.LOCK_SH if isolated else fcntl.LOCK_EX) | fcntl.LOCK_NB)
            turn_held = True
            if isolated:
                fcntl.flock(gate, fcntl.LOCK_SH | fcntl.LOCK_NB)
            else:
                # A waiting exclusive operation holds the turnstile to prevent
                # new shared jobs starving it. Existing legacy holders finish.
                fcntl.flock(gate, fcntl.LOCK_EX)
            break
        except BlockingIOError:
            pass
        finally:
            if turn_held:
                fcntl.flock(turn, fcntl.LOCK_UN)
            if intent_held:
                fcntl.flock(intent, fcntl.LOCK_UN)
        time.sleep(0.1)
    if lane == 'acceptance':
        fcntl.flock(intent, fcntl.LOCK_UN)
    handles.append(gate)
    gate_done = time.monotonic()
    return handles, dict(workspace_wait_seconds=workspace_done-started,
        capacity_wait_seconds=slot_done-workspace_done, legacy_gate_wait_seconds=gate_done-slot_done,
        total_queue_wait_seconds=gate_done-started, slot=slot_name, lane=lane)


def reserve_receipts(path):
    if not path.is_absolute() or path.suffix != '.json':
        raise RuntimeError('receipt must be an absolute .json path')
    paths = [path, path.with_suffix('.time.json'), path.with_suffix('.build.log')]
    path.parent.mkdir(parents=True, exist_ok=True)
    # Exclusive creation prevents races, existing siblings and dangling symlinks.
    # Partial reservations deliberately remain after a failure; use a new label.
    for item in paths:
        with item.open('x'):
            pass
    return paths


def check_prepared(repo, prepared, reviewed_sha, current, legacy_ninja_identity=None):
    prior = json.loads(prepared.read_text())
    if not prior.get('prepared') or prior.get('returncode') != 0:
        raise RuntimeError('successful exclusive preparation receipt required')
    old = prior['admission']
    for key in ('protocol', 'revision', 'repo', 'ninja_sha256', 'inputs_sha256', 'ninja_tool'):
        expected = old.get(key)
        if key == 'ninja_tool' and key not in old and legacy_ninja_identity is not None:
            expected = legacy_ninja_identity  # separate verified current identity, never receipt mutation
        if expected != current[key]:
            raise RuntimeError(f'preparation is stale: {key}')
    if reviewed_sha != current['ninja_sha256']:
        raise RuntimeError('explicitly reviewed graph SHA-256 required')


def enabled_policy(require_wrapper_match=False):
    enabled = json.loads(ENABLE.read_text())
    if (enabled.get('protocol') != PROTOCOL or enabled.get('revision') != REVISION
            or enabled.get('enabled') is not True or not enabled.get('parent_broadcast')):
        raise RuntimeError('current parent rollout broadcast marker required')
    capacity_policy(enabled)
    if require_wrapper_match and enabled.get('wrapper_sha256') != digest(Path(__file__)):
        raise RuntimeError('enabled marker does not authorize this audit wrapper')
    return enabled


def qualified_audit(repo, prepared, reviewed_sha, enabled):
    # Called only after workspace EX, acceptance slot, and legacy SH acquisition.
    # Recheck the marker after waiting; never silently fall back or upgrade to EX.
    if enabled_policy(require_wrapper_match=True) != enabled:
        raise RuntimeError('enabled marker changed while audit was queued')
    prior = json.loads(prepared.read_text())
    if prior.get('mode') != 'legacy':
        raise RuntimeError('exclusive preparation receipt required')
    if 'ninja_tool' not in prior.get('admission', {}):
        raise RuntimeError('preparation receipt lacks pinned Ninja evidence')
    pin_ninja(repo, prior['admission']['ninja_tool'])
    current = audit(repo)
    check_prepared(repo, prepared, reviewed_sha, current)
    temporary = Path(tempfile.mkdtemp(prefix='capacity-audit-', dir=repo / 'build'))
    safe_destination(repo, temporary)
    original = temporary / 'prepared.ninja'
    original.write_bytes((repo / 'build.ninja').read_bytes())
    preflight = setup_preflight(repo, original)
    if inputs_fingerprint(repo) != current['inputs_sha256']:
        raise RuntimeError('inputs changed during qualified audit; result invalid')
    pin_ninja(repo)
    return current, preflight


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--repo', type=Path, required=True)
    ap.add_argument('--receipt', type=Path, required=True)
    ap.add_argument('--mode', choices=['legacy', 'isolated'], default='legacy')
    operation = ap.add_mutually_exclusive_group()
    operation.add_argument('--audit-only', action='store_true')
    operation.add_argument('--prepare-only', action='store_true')
    ap.add_argument('--lane', choices=['acceptance', 'development'], default='development')
    ap.add_argument('--prepared-receipt', type=Path)
    ap.add_argument('--resume-control', type=Path, help='Reviewed one-shot local trial only')
    ap.add_argument('--resume-invocation-sha256')
    ap.add_argument('--reviewed-graph-sha256')
    args = ap.parse_args()
    repo = args.repo.resolve(strict=True)
    resume = None
    resume_started = False
    resume_invocation = None
    if args.resume_invocation_sha256 and not args.resume_control:
        raise RuntimeError('resume control required')
    if args.resume_control:
        # Load only this installation's companion module after verifying its
        # bytes against queue-owned trial control. No plugin/command path input.
        if args.mode != 'isolated' or args.lane != 'development' or args.audit_only or args.prepare_only:
            raise RuntimeError('resume supports isolated development builds only')
        import types
        adapter = Path(__file__).resolve().parents[1] / 'handoff_resume.py'
        control = json.loads(args.resume_control.read_bytes())
        raw = adapter.read_bytes()
        if hashlib.sha256(raw).hexdigest() != control['adapter_sha256']:
            raise RuntimeError('resume adapter changed')
        resume = types.ModuleType('_reviewed_handoff_resume')
        resume.__file__ = str(adapter)
        exec(compile(raw, str(adapter), 'exec'), resume.__dict__)
        resume_invocation = resume.capture(args.resume_control)
        if resume_invocation.sha256 != args.resume_invocation_sha256:
            raise RuntimeError('resume invocation identity changed before wrapper entry')
        config, release = resume_invocation.config, resume_invocation.release
        if (release['root'] != str(repo) or release['output'] != str(args.receipt)
                or release['prepared']['path'] != str(args.prepared_receipt)
                or release['graph_sha256'] != args.reviewed_graph_sha256):
            raise RuntimeError('resume invocation binding mismatch')
    pin_ninja(repo)
    isolated = args.mode == 'isolated'
    if args.prepare_only and isolated:
        raise RuntimeError('preparation must hold legacy exclusive lock')
    shared_audit = args.audit_only and isolated and args.lane == 'acceptance'
    development_slots = 1
    enabled = None
    if isolated and (not args.audit_only or shared_audit):
        enabled = enabled_policy(require_wrapper_match=shared_audit)
        development_slots = capacity_policy(enabled)
        if not args.prepared_receipt or not args.prepared_receipt.is_absolute():
            raise RuntimeError('absolute --prepared-receipt required')
        if shared_audit and not args.reviewed_graph_sha256:
            raise RuntimeError('reviewed graph SHA-256 required for shared acceptance audit')
    receipt, timing, log = reserve_receipts(args.receipt)
    record = dict(protocol=PROTOCOL, revision=REVISION, repo=str(repo), mode=args.mode,
                  queued_epoch=time.time(), prepared=False)
    code = 1
    try:
        with ExitStack() as stack:
            # Only explicitly qualified acceptance audits share the legacy gate.
            # Other audits retain the existing exclusive behavior.
            handles, waits = acquire(stack, repo, isolated and (not args.audit_only or shared_audit),
                legacy=LEGACY, capacity=CAPACITY,
                lane=args.lane, development_slots=development_slots,
                resource_guard=None if args.audit_only else resources_available)
            record.update(waits)
            if args.audit_only:
                record['legacy_gate_mode'] = 'shared' if shared_audit else 'exclusive'
                record['qualified_acceptance_audit'] = shared_audit
                if shared_audit:
                    record['admission'], record['setup_preflight'] = qualified_audit(
                        repo, args.prepared_receipt, args.reviewed_graph_sha256, enabled)
                else:
                    record['admission'] = audit(repo)
                code = 0
            else:
                env = os.environ.copy()
                if Path(NINJA).is_absolute():
                    env['PATH'] = str(Path(ninja_command(repo)).parent) + ':' + env['PATH']
                env['PYTHONDONTWRITEBYTECODE'] = '1'
                env.pop('GITHUB_STEP_SUMMARY', None)
                writable_trees(repo)
                (repo / 'build').mkdir(exist_ok=True)
                temporary = Path(tempfile.mkdtemp(prefix='capacity-tmp-', dir=repo / 'build'))
                safe_destination(repo, temporary)
                env.update(TMPDIR=str(temporary), TMP=str(temporary), TEMP=str(temporary))
                command = [ninja_command(repo), '-j2']
                if args.prepare_only:
                    command += ['build.ninja']
                elif isolated:
                    prior = json.loads(args.prepared_receipt.read_text())
                    legacy_ninja = None
                    if 'ninja_tool' not in prior.get('admission', {}):
                        if not resume:
                            raise RuntimeError('preparation receipt lacks pinned Ninja evidence')
                        # Only the captured reviewed resume contract can supply
                        # the separate legacy manifest/current-identity binding.
                        legacy_ninja = resume.preparation_ninja(resume_invocation.release, prior)
                    expected_ninja = prior['admission'].get('ninja_tool', legacy_ninja)
                    pin_ninja(repo, expected_ninja)
                    current = audit(repo)
                    check_prepared(repo, args.prepared_receipt, args.reviewed_graph_sha256,
                                   current, legacy_ninja_identity=legacy_ninja)
                    record['admission'] = current
                    original = temporary / 'prepared.ninja'
                    original.write_bytes((repo / 'build.ninja').read_bytes())
                    record['setup_preflight'] = setup_preflight(repo, original)
                    snapshot = temporary / 'frozen.ninja'
                    snapshot.write_text(frozen_graph((repo / 'build.ninja').read_text()))
                    # Different manifest filename prevents automatic build.ninja regeneration.
                    # Setup edges are inert existing-file leaves after a clean original preflight.
                    command += ['-f', str(snapshot), 'progress']
                fmt = '{"wall_seconds":%e,"user_seconds":%U,"sys_seconds":%S,"max_rss_kib":%M,"exit_status":%x}'
                if resume:
                    resume.claim(resume_invocation)
                    resume_started = True
                record['started_epoch'] = time.time()
                with log.open('w') as output:
                    child = subprocess.run(['/usr/bin/time', '-f', fmt, '-o', str(timing), *command],
                        cwd=repo, env=env, stdout=output, stderr=subprocess.STDOUT,
                        pass_fds=tuple(h.fileno() for h in handles))
                pin_ninja(repo)
                code = child.returncode
                record['finished_epoch'] = time.time()
                record['measurement'] = json.loads(timing.read_text().splitlines()[-1])
                if args.prepare_only and code == 0:
                    record['admission'] = audit(repo)
                    record['prepared'] = True
                elif isolated:
                    if inputs_fingerprint(repo) != record['admission']['inputs_sha256']:
                        raise RuntimeError('inputs changed during isolated build; result invalid')
    except BaseException as error:
        record['error'] = f'{type(error).__name__}: {error}'
        code = 1
        raise
    finally:
        record['returncode'] = code
        receipt.write_text(json.dumps(record, indent=2) + '\n')
        if resume:
            with receipt.open('rb') as completed:
                os.fsync(completed.fileno())
            resume.fsync_dir(receipt.parent)
            resume.finish(resume_invocation, code, resume_started)
    print(json.dumps(record, indent=2))
    raise SystemExit(code)


if __name__ == '__main__':
    main()
