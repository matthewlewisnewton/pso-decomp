"""One-shot queue-owned development resume adapter; no CLI or peer dispatch.

Control files are queue-owned activation/configuration, not untrusted requests.
Receipt pins are supplied by an independent verifier, never inferred here.
"""
from dataclasses import dataclass
import hashlib
import json
import os
from pathlib import Path
import re
import sqlite3
import subprocess
import time

QUEUE = '01a19401-c64f-72eb-a3cc-ab2d74fe102a'
ACTION = 'resume_released_development_build'
HERE = Path(__file__).resolve()
WRAPPER = HERE.parent / 'local_build_capacity' / 'build_capacity.py'
PYTHON = Path('/usr/bin/python3').resolve()
HEX = re.compile(r'^[a-f0-9]{64}$')
COMMIT = re.compile(r'^[a-f0-9]{40}$')
FIELDS = {'version', 'queue', 'action', 'release_id', 'item', 'head', 'root',
          'prepared', 'graph_sha256', 'inputs_sha256', 'approval', 'notice',
          'launcher', 'ninja', 'output', 'issued_ms'}
CONTROL = {'version', 'enabled', 'trial_id', 'companion', 'approval_sha256',
           'adapter_sha256', 'wrapper_sha256', 'python_sha256', 'journal'}


def require(condition, reason):
    if not condition:
        raise ValueError(reason)


def unique(pairs):
    result = {}
    for key, value in pairs:
        require(key not in result, 'duplicate JSON key')
        result[key] = value
    return result


def read(path):
    return json.loads(Path(path).read_bytes(), object_pairs_hook=unique)


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def absolute(path):
    p = Path(path)
    require(p.is_absolute() and p.resolve() == p, 'noncanonical path')
    return p


def pin(entry):
    require(isinstance(entry, dict) and set(entry) == {'path', 'sha256'}, 'invalid pin')
    p = absolute(entry['path'])
    require(p.is_file() and not p.is_symlink(), 'invalid pinned file')
    require(isinstance(entry['sha256'], str) and HEX.fullmatch(entry['sha256']), 'invalid digest')
    require(digest(p) == entry['sha256'], 'changed pinned file')
    return p


def publish_companion(release, destination):
    """Called ONLY by the sole queue immediately after its existing RELEASED
    decision. Serializes that decision; it does not decide release/admission.
    Independent review and a separately enabled control remain necessary.
    """
    validate(release)
    output = absolute(destination)
    output.parent.mkdir(parents=True, exist_ok=True)
    raw = (json.dumps(release, sort_keys=True, indent=2) + '\n').encode()
    # Exclusive immutable publication; interrupted files are never overwritten.
    with output.open('xb') as stream:
        stream.write(raw)
        stream.flush()
        os.fsync(stream.fileno())
    fsync_dir(output.parent)
    return {'path': str(output), 'sha256': hashlib.sha256(raw).hexdigest()}


def fsync_dir(path):
    fd = os.open(path, os.O_RDONLY | os.O_DIRECTORY)
    try:
        os.fsync(fd)
    finally:
        os.close(fd)


def validate(data):
    require(isinstance(data, dict) and set(data) == FIELDS, 'closed release schema required')
    require(data['version'] == 1 and data['queue'] == QUEUE and data['action'] == ACTION,
            'unsupported queue/action/version')
    for key in ('release_id', 'item'):
        require(isinstance(data[key], str) and bool(data[key].strip()), 'missing identity')
    require(isinstance(data['head'], str) and COMMIT.fullmatch(data['head']), 'immutable head required')
    for key in ('graph_sha256', 'inputs_sha256'):
        require(isinstance(data[key], str) and HEX.fullmatch(data[key]), 'invalid graph/input digest')
    require(type(data['issued_ms']) is int and data['issued_ms'] >= 0, 'invalid issue time')
    root = absolute(data['root'])
    require(root.is_dir() and not root.is_symlink(), 'invalid root')
    for key in ('prepared', 'approval', 'notice', 'launcher', 'ninja'):
        path = pin(data[key])
        require(not path.is_relative_to(root), 'trusted pin inside build root')
    output = absolute(data['output'])
    require(output.suffix == '.json' and not output.is_relative_to(root), 'invalid output receipt')


def load(control_path):
    control_path = absolute(control_path)
    require(control_path.is_file() and not control_path.is_symlink(), 'invalid queue control')
    c = read(control_path)
    require(isinstance(c, dict) and set(c) == CONTROL and c['version'] == 1, 'invalid control')
    require(c['enabled'] is True, 'trial disabled')
    require(isinstance(c['trial_id'], str) and bool(c['trial_id'].strip()), 'invalid trial identity')
    require(digest(HERE) == c['adapter_sha256'] and digest(WRAPPER) == c['wrapper_sha256']
            and digest(PYTHON) == c['python_sha256'], 'runtime identity drift')
    companion = pin(c['companion'])
    d = read(companion)
    validate(d)
    # This separate pin must be supplied by the independent verifier in the
    # trusted activation config, not copied automatically from the companion.
    require(d['approval']['sha256'] == c['approval_sha256'], 'unapproved receipt')
    approval = read(pin(d['approval']))
    require(isinstance(approval, dict) and set(approval) == {
        'version', 'independent', 'reviewer', 'producer', 'verdict', 'item', 'head',
        'root', 'prepared_sha256', 'graph_sha256', 'inputs_sha256', 'action'}, 'closed approval schema required')
    require(approval['version'] == 1 and approval['independent'] is True
            and approval['verdict'] == 'pass' and bool(approval['reviewer'])
            and approval['reviewer'] != approval['producer'], 'independent approval required')
    for key in ('item', 'head', 'root', 'graph_sha256', 'inputs_sha256', 'action'):
        require(approval[key] == d[key], 'approval binding mismatch: ' + key)
    require(approval['prepared_sha256'] == d['prepared']['sha256'], 'preparation review mismatch')
    prior = read(pin(d['prepared']))
    require(prior.get('prepared') is True and prior.get('returncode') == 0, 'preparation incomplete')
    admitted = prior['admission']
    for key, expected in {'repo': d['root'], 'ninja_sha256': d['graph_sha256'],
                          'inputs_sha256': d['inputs_sha256']}.items():
        require(admitted.get(key) == expected, 'preparation binding mismatch')
    expected_ninja = admitted.get('ninja_tool')
    require(isinstance(expected_ninja, dict) and set(expected_ninja) == {
        'path', 'sha256', 'device', 'inode', 'size', 'mtime_ns'}, 'full Ninja preparation identity required')
    require({key: expected_ninja[key] for key in ('path', 'sha256')} == d['ninja'],
            'Ninja preparation pin mismatch')
    executable = pin(d['ninja'])
    stat = executable.stat()
    actual_ninja = dict(path=str(executable), sha256=digest(executable),
                        device=stat.st_dev, inode=stat.st_ino, size=stat.st_size,
                        mtime_ns=stat.st_mtime_ns)
    require(os.access(executable, os.X_OK) and actual_ninja == expected_ninja,
            'Ninja identity differs from preparation evidence')
    root = Path(d['root'])
    require(digest(root / 'build.ninja') == d['graph_sha256'], 'graph drift')
    # Isolated Git observation disables local hooks, includes and executable
    # Git overrides. The wrapper retains its complete input/graph checks.
    env = {'PATH': '/usr/bin:/bin', 'GIT_CONFIG_GLOBAL': '/dev/null',
           'GIT_CONFIG_NOSYSTEM': '1', 'GIT_TERMINAL_PROMPT': '0'}
    dotgit = root / '.git'
    require(dotgit.is_dir() and not dotgit.is_symlink(), 'private clone required')
    config = dotgit / 'config'
    require(config.is_file() and not config.is_symlink(), 'invalid Git config')
    raw_config = subprocess.check_output(['/usr/bin/git', 'config', '--file', str(config),
        '--no-includes', '--name-only', '--list'], env=env, text=True).lower().splitlines()
    require(not any(k.startswith(('include.', 'includeif.')) for k in raw_config), 'Git includes forbidden')
    head = subprocess.check_output(['/usr/bin/git', '-c', 'core.hooksPath=/dev/null',
        '-c', 'core.fsmonitor=false', '-C', str(root), 'rev-parse', 'HEAD'], env=env, text=True).strip()
    require(head == d['head'], 'head drift')
    journal = absolute(c['journal'])
    require(not journal.is_relative_to(root) and not journal.is_symlink(), 'invalid journal')
    return c, d


def connect(path):
    path = absolute(path)
    require(not path.is_symlink(), 'journal symlink forbidden')
    db = sqlite3.connect(path, isolation_level=None)
    db.execute('PRAGMA synchronous=FULL')
    db.execute('''CREATE TABLE IF NOT EXISTS attempts (
      release_id TEXT PRIMARY KEY, companion TEXT NOT NULL, trial TEXT NOT NULL,
      state TEXT NOT NULL, observed_ns INTEGER NOT NULL, intent_ns INTEGER NOT NULL,
      started_ns INTEGER, finished_ns INTEGER, returncode INTEGER, reason TEXT)''')
    return db


def status(db, release):
    db.row_factory = sqlite3.Row
    row = db.execute('SELECT * FROM attempts WHERE release_id=?', (release,)).fetchone()
    return dict(row) if row else None


@dataclass(frozen=True)
class Invocation:
    # Canonical strings prevent caller-owned dictionaries from mutating the
    # identity captured before admission. Completion never reloads control.
    control_path: str
    config_json: str
    release_json: str

    @property
    def config(self):
        return json.loads(self.config_json)

    @property
    def release(self):
        return json.loads(self.release_json)

    @property
    def sha256(self):
        return hashlib.sha256((self.config_json + '\n' + self.release_json).encode()).hexdigest()


def capture(control_path):
    c, d = load(control_path)
    return Invocation(str(absolute(control_path)), json.dumps(c, sort_keys=True),
                      json.dumps(d, sort_keys=True))


def claim(invocation, fault=lambda phase: None):
    """Consume only the invocation captured before admission.

    Re-read mutable control for disable/drift checks, but never select a new
    release, root, companion, trial or journal from it after waiting.
    """
    require(type(invocation) is Invocation, 'captured invocation required')
    current = capture(invocation.control_path)
    require(current == invocation, 'control changed during admission')
    c, d = invocation.config, invocation.release
    db = connect(c['journal'])
    try:
        db.execute('BEGIN IMMEDIATE')
        row = status(db, d['release_id'])
        require(row is not None and row['state'] == 'intent'
                and row['companion'] == c['companion']['sha256']
                and row['trial'] == c['trial_id'], 'release already consumed or unreserved')
        db.execute('UPDATE attempts SET state=?,started_ns=? WHERE release_id=?',
                   ('started', time.monotonic_ns(), d['release_id']))
        db.execute('COMMIT')
        fault('after_started')
    finally:
        db.close()


def finish(invocation, returncode, started):
    """Attribute completion to the captured original, even after disable/rebind.

    No read of the mutable control, companion, or other release files occurs.
    """
    require(type(invocation) is Invocation, 'captured invocation required')
    c, d = invocation.config, invocation.release
    db = connect(c['journal'])
    try:
        db.execute('BEGIN IMMEDIATE')
        row = status(db, d['release_id'])
        require(row and row['companion'] == c['companion']['sha256']
                and row['trial'] == c['trial_id'], 'completion identity mismatch')
        expected = 'started' if started else 'intent'
        if row['state'] == expected:
            db.execute('UPDATE attempts SET state=?,finished_ns=?,returncode=? WHERE release_id=?',
                       (('finished' if returncode == 0 else 'failed') if started else 'preflight_failed', time.monotonic_ns(),
                        returncode, d['release_id']))
        db.execute('COMMIT')
    finally:
        db.close()


def resume_one(control_path, fault=lambda phase: None):
    """Explicit synchronous queue call. No polling, retry or arbitrary argv."""
    observed = time.monotonic_ns()
    invocation = capture(control_path)
    c, d = invocation.config, invocation.release
    db = connect(c['journal'])
    try:
        db.execute('BEGIN IMMEDIATE')
        row = status(db, d['release_id'])
        if row:
            require(row['companion'] == c['companion']['sha256']
                    and row['trial'] == c['trial_id'], 'conflicting release reuse')
            db.execute('COMMIT')
            return dict(row, blocked_reason=None if row['state'] == 'finished' else
                        'consumed release: reconcile existing attempt; never relaunch')
        # Reserve the logical attempt before any wrapper process can exist.
        db.execute('INSERT INTO attempts VALUES (?, ?, ?, ?, ?, ?, NULL, NULL, NULL, NULL)',
                   (d['release_id'], c['companion']['sha256'], c['trial_id'], 'intent',
                    observed, time.monotonic_ns()))
        db.execute('COMMIT')
        fault('after_intent')
        # Recheck the kill switch and identity immediately before invoking the
        # fixed wrapper. Its claim() repeats this check after admission waits.
        fresh_c, fresh_d = load(control_path)
        require(fresh_c == c and fresh_d == d, 'control changed after reservation')
        env = {'PATH': '/usr/bin:/bin', 'HOME': '/nonexistent', 'LANG': 'C',
               'PYTHONDONTWRITEBYTECODE': '1', 'PSO_QUEUE_PYTHON': d['launcher']['path'],
               'PSO_BUILD_NINJA': d['ninja']['path']}
        argv = [str(PYTHON), '-I', '-B', str(WRAPPER), '--repo', d['root'],
                '--receipt', d['output'], '--mode', 'isolated', '--lane', 'development',
                '--prepared-receipt', d['prepared']['path'],
                '--reviewed-graph-sha256', d['graph_sha256'],
                '--resume-control', invocation.control_path,
                '--resume-invocation-sha256', invocation.sha256]
        subprocess.run(argv, env=env, check=False)
        fault('after_wrapper')
        row = status(db, d['release_id'])
        return dict(row, blocked_reason=None if row['state'] == 'finished' else
                    'consumed release: reconcile existing attempt; never relaunch')
    finally:
        db.close()
