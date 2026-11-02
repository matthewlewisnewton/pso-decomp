"""Durable routing observations for a queue adapter. No dispatch implementation.

PinnedReceipts is the closed ingestion boundary: its pins must be issued by an
independent verifier, never derived by the reducer from an untrusted receipt.
The reducer records supplied verdicts; it cannot manufacture verification.
"""
import hashlib
import json
import sqlite3
from pathlib import Path

from tools.handoff_report import SHA, DIGEST, string

STAGES = ('source', 'development', 'graph', 'acceptance', 'publication')
ACTIONS = ('request_source_review', 'request_development_validation',
           'request_graph_review', 'request_queue_transaction',
           'request_publication_reconciliation')
FIELDS = {'request_id', 'item', 'head', 'base', 'stage', 'verdict',
          'producer', 'reviewer', 'completed_ms'}


def canonical(value):
    return json.dumps(value, sort_keys=True, separators=(',', ':'))


def commit(value):
    if not isinstance(value, str) or not SHA.fullmatch(value):
        raise ValueError('full lowercase commit SHA required')


class PinnedReceipts:
    """Caller-owned independent verification pins, not a user receipt allowlist.

    Reviewers issue pins only after checking the actual stage, scope, immutable
    head/base, result, and underlying evidence. Hashing alone is insufficient.
    No CLI constructs these pins and no external adapter is enabled here.
    """
    def __init__(self, pins):
        self._pins = dict(pins)
        for key, digest in self._pins.items():
            string(key, 'request_id')
            if not isinstance(digest, str) or not DIGEST.fullmatch(digest):
                raise ValueError('invalid independent verification pin')

    def read(self, request_id, path):
        raw = Path(path).read_bytes()
        digest = hashlib.sha256(raw).hexdigest()
        if self._pins.get(request_id) != digest:
            raise ValueError('receipt is not independently pinned')
        data = json.loads(raw)
        if not isinstance(data, dict) or set(data) != FIELDS:
            raise ValueError('closed receipt schema required')
        for field in ('request_id', 'item', 'producer', 'reviewer'):
            string(data[field], field)
        if data['request_id'] != request_id or data['reviewer'] == data['producer']:
            raise ValueError('independent receipt identity required')
        commit(data['head'])
        commit(data['base'])
        if data['stage'] not in STAGES or data['verdict'] not in (
                'pass', 'fail', 'unknown', 'hold', 'denied', 'uncertain'):
            raise ValueError('invalid typed receipt')
        if type(data['completed_ms']) is not int or data['completed_ms'] < 0:
            raise ValueError('invalid completion time')
        return data, digest, str(Path(path).resolve())


class Store:
    """Single SQLite transaction persists receipt, next-action event and pointer.

    next_action values are routing requests only. They confer no admission,
    permission, release, build invocation or publication authority. In particular
    request_queue_transaction refers to the existing queue's single transaction;
    there is no second dry-run/build stage here.
    """
    def __init__(self, path):
        self.db = sqlite3.connect(path, isolation_level=None)
        self.db.execute('PRAGMA synchronous=FULL')
        self.db.executescript('''
          CREATE TABLE IF NOT EXISTS items (
            id TEXT PRIMARY KEY, config TEXT NOT NULL, action TEXT, view TEXT);
          CREATE TABLE IF NOT EXISTS receipts (
            id TEXT PRIMARY KEY, item TEXT NOT NULL, digest TEXT NOT NULL,
            path TEXT NOT NULL, body TEXT NOT NULL);
          CREATE TABLE IF NOT EXISTS events (
            id TEXT PRIMARY KEY, item TEXT NOT NULL, body TEXT NOT NULL,
            created_ms INTEGER NOT NULL);
        ''')

    def close(self):
        self.db.close()

    def _atomic(self, operation):
        self.db.execute('BEGIN IMMEDIATE')
        try:
            result = operation()
            self.db.execute('COMMIT')
            return result
        except BaseException:
            self.db.execute('ROLLBACK')
            raise

    def observe(self, item, head, main, revision, owners, now_ms):
        """Explicit inventory refresh; never claims any stage passed.

        revision is an operator-issued monotonic inventory sequence. Repeated
        identical observations are safe; conflicting or older ones are rejected.
        """
        string(item, 'item')
        commit(head)
        commit(main)
        if type(revision) is not int or revision < 0:
            raise ValueError('invalid inventory revision')
        if set(owners) != set(STAGES):
            raise ValueError('one explicit routing owner per stage required')
        for owner in owners.values():
            string(owner, 'owner')
        config = dict(head=head, main=main, revision=revision, owners=owners)
        def update():
            old = self.db.execute('SELECT config FROM items WHERE id=?', (item,)).fetchone()
            if old:
                prior = json.loads(old[0])
                if revision < prior['revision'] or (revision == prior['revision'] and config != prior):
                    raise ValueError('out-of-order or conflicting inventory')
            self.db.execute('INSERT INTO items VALUES (?, ?, NULL, NULL) ON CONFLICT(id) '
                            'DO UPDATE SET config=excluded.config', (item, canonical(config)))
            return self._reduce(item, now_ms)
        return self._atomic(update)

    def ingest(self, verifier, request_id, path, now_ms, fault=lambda point: None):
        if type(verifier) is not PinnedReceipts:
            raise TypeError('closed pinned receipt interface required')
        data, digest, reference = verifier.read(request_id, path)
        if data['completed_ms'] > now_ms:
            raise ValueError('receipt completion is in the future')
        def update():
            if not self.db.execute('SELECT 1 FROM items WHERE id=?', (data['item'],)).fetchone():
                raise ValueError('unknown item')
            old = self.db.execute('SELECT digest FROM receipts WHERE id=?', (request_id,)).fetchone()
            if old and old[0] != digest:
                raise ValueError('conflicting duplicate request ID')
            self.db.execute('INSERT OR IGNORE INTO receipts VALUES (?, ?, ?, ?, ?)',
                            (request_id, data['item'], digest, reference, canonical(data)))
            fault('after_receipt')
            result = self._reduce(data['item'], now_ms)
            fault('after_event')
            return result
        result = self._atomic(update)
        fault('after_commit')
        return result

    def _reduce(self, item, now_ms):
        if type(now_ms) is not int or now_ms < 0:
            raise ValueError('invalid observation time')
        config = json.loads(self.db.execute('SELECT config FROM items WHERE id=?', (item,)).fetchone()[0])
        receipts = [json.loads(row[0]) for row in self.db.execute(
            'SELECT body FROM receipts WHERE item=? ORDER BY id', (item,))]
        stages = {}
        blockers = []
        for stage in STAGES:
            relevant = [r for r in receipts if r['stage'] == stage and r['head'] == config['head']
                        and (stage in ('source', 'development') or r['base'] == config['main'])]
            stages[stage] = 'pass' if relevant and all(r['verdict'] == 'pass' for r in relevant) else 'missing'
            for r in relevant:
                if r['verdict'] != 'pass':
                    blockers.append(r['request_id'] + ': ' + r['verdict'])
        # Denial and uncertain mutation outcomes survive inventory changes.
        # This first version has no unblock/retry API. A human must reconcile.
        blockers += [r['request_id'] + ': ' + r['verdict'] for r in receipts
                     if r['verdict'] in ('denied', 'uncertain')]
        view = dict(item=item, head=config['head'], current_main=config['main'],
                    stages=stages, dispatch_enabled=False, next_owner=None,
                    next_action=None, blocked_reason=None)
        if blockers:
            view.update(next_owner=config['owners']['acceptance'],
                        blocked_reason='; '.join(sorted(set(blockers))))
        else:
            missing = next((s for s in STAGES if stages[s] != 'pass'), None)
            if missing:
                view.update(next_owner=config['owners'][missing],
                            next_action=ACTIONS[STAGES.index(missing)])
        # Stable logical action identity excludes receipt arrival order and time.
        # Main only affects actions that actually depend on current main.
        identity = dict(item=item, head=config['head'], owner=view['next_owner'],
                        action=view['next_action'], blocked=view['blocked_reason'])
        if view['next_action'] in ACTIONS[2:] or blockers:
            identity['main'] = config['main']
        event_id = hashlib.sha256(canonical(identity).encode()).hexdigest()
        view['event_id'] = event_id
        self.db.execute('INSERT OR IGNORE INTO events VALUES (?, ?, ?, ?)',
                        (event_id, item, canonical(view), now_ms))
        self.db.execute('UPDATE items SET action=?, view=? WHERE id=?',
                        (event_id, canonical(view), item))
        return self.current(item)

    def current(self, item):
        row = self.db.execute('SELECT view FROM items WHERE id=?', (item,)).fetchone()
        if row is None:
            raise ValueError('unknown item')
        return json.loads(row[0])

    def events(self, item):
        """Audit only. Old events are superseded; never dispatch this history."""
        return [dict(event=json.loads(body), created_ms=created) for body, created in
                self.db.execute('SELECT body, created_ms FROM events WHERE item=? ORDER BY rowid', (item,))]
