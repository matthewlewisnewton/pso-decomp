#!/usr/bin/env python3
"""Deterministic, fork-only reviewed batch validation and atomic publication."""
from __future__ import annotations
import argparse
from contextlib import ExitStack
import fcntl
import hashlib
import json
import math
import os
from pathlib import Path
import re
import subprocess
import sys
import time

REPOSITORY = 'matthewlewisnewton/pso-decomp'
REMOTE = 'git@github.com:' + REPOSITORY + '.git'
SHA = re.compile(r'[0-9a-f]{40}')
CHECKS = {'source', 'build', 'coverage', 'link', 'provenance', 'dol'}


class Rejected(Exception):
    def __init__(self, code, detail):
        self.code, self.detail = code, detail
        super().__init__(f'{code}: {detail}')


def require(condition, code, detail):
    if not condition:
        raise Rejected(code, detail)


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def canonical(value):
    return json.dumps(value, sort_keys=True, separators=(',', ':'))


def save(path, value):
    # Durable same-directory replace; state directory is private to this invocation.
    tmp = path.with_suffix('.tmp')
    with tmp.open('w') as out:
        out.write(json.dumps(value, indent=2) + '\n')
        out.flush()
        os.fsync(out.fileno())
    os.replace(tmp, path)
    fd = os.open(path.parent, os.O_RDONLY | os.O_DIRECTORY)
    try:
        os.fsync(fd)
    finally:
        os.close(fd)


def run(args, cwd=None, env=None):
    result = subprocess.run(args, cwd=cwd, env=env, text=True, capture_output=True)
    require(result.returncode == 0, 'command_failed', {
        'command': args[:3], 'returncode': result.returncode,
        'diagnostic': result.stderr[-2000:]})
    return result.stdout.strip()


def source_maintenance_path(path):
    # Only C/C++ source and headers in project source trees; no graph/config/tool edits.
    return bool(re.fullmatch(r'(?:src|include)/[A-Za-z0-9_./+\-]+\.(?:c|cc|cpp|h|hpp)', path)) and all(part not in ('', '.', '..') for part in path.split('/'))


def validate_spec(spec):
    require(spec.get('version') == 1 and spec.get('repository') == REPOSITORY,
            'wrong_repository', 'Only schema 1 and the personal fork are supported')
    require(spec.get('default_branch') in ('master', 'main'), 'wrong_base', 'Unsupported default branch')
    require(SHA.fullmatch(spec.get('target', '')), 'invalid_spec', 'Immutable target SHA required')
    require(spec.get('policy') in ('recovery', 'maintenance', 'source-maintenance'), 'invalid_policy', 'Recognized operator policy required')
    require(isinstance(spec.get('commit_epoch'), int) and spec['commit_epoch'] > 0,
            'invalid_spec', 'Positive fixed commit_epoch required')
    require(spec.get('authorization'), 'missing_authorization', 'Record parent/user batch authorization')
    require(isinstance(spec.get('prs'), list) and spec['prs'], 'empty_batch', 'Explicit ordered PRs required')
    seen = set()
    for pr in spec['prs']:
        number = pr.get('number')
        require(type(number) is int and number > 0 and number not in seen, 'invalid_spec', 'Unique positive PR numbers required')
        seen.add(number)
        for key in ('head', 'base_sha', 'review_base'):
            require(SHA.fullmatch(pr.get(key, '')), 'invalid_spec', f'PR {number}: {key} missing')
        require(pr.get('base_ref') and pr.get('head_ref'), 'invalid_spec', 'Both branch names required')
        review = pr.get('review', {})
        require(review.get('verdict') == 'pass' and review.get('independent') is True
                and review.get('head') == pr['head'] and review.get('base') == pr['review_base']
                and review.get('reviewer'), 'missing_review', f'PR {number}: independent exact-head review required')
        require(pr.get('kind') in ('recovery', 'prerequisite', 'maintenance', 'source-maintenance'), 'invalid_spec', 'PR kind required')
        require(pr['kind'] != 'prerequisite' or pr.get('reason'), 'missing_prerequisite_reason', number)
        require(spec['policy'] != 'maintenance' or pr['kind'] == 'maintenance', 'invalid_policy', number)
        require(spec['policy'] != 'source-maintenance' or pr['kind'] == 'source-maintenance', 'invalid_policy', number)
        require(spec['policy'] == 'source-maintenance' or pr['kind'] != 'source-maintenance', 'invalid_policy', number)
        require(isinstance(pr.get('required_checks'), list) and pr['required_checks'],
                'missing_checks', f'PR {number}: explicit hosted check names required')


def evidence(spec):
    config=spec.get('config_admission')
    if config is not None:
        require(spec['policy']=='recovery' and isinstance(config, dict) and set(config)=={'checker','packet'}, 'invalid_config_admission', '')
        for entry in config.values():
            require(isinstance(entry, dict) and set(entry)=={'path','sha256'}, 'invalid_config_admission', '')
            path=Path(entry['path'])
            require(path.is_absolute() and path.is_file() and not path.is_symlink() and digest(path)==entry['sha256'], 'stale_config_admission', '')
    for pr in spec['prs']:
        r = pr['review']
        path = Path(r.get('path', ''))
        require(path.is_absolute() and path.is_file() and not path.is_symlink(), 'missing_review', pr['number'])
        require(digest(path) == r.get('sha256'), 'stale_review', pr['number'])


def check_live(spec, live, branch):
    require(branch['name'] == spec['default_branch'] and branch['head'] == spec['target'],
            'stale_target', branch)
    for pr in spec['prs']:
        actual = live[pr['number']]
        expected = {k: pr[k] for k in ('head', 'base_sha', 'base_ref', 'head_ref')}
        require(actual['repository'] == REPOSITORY, 'wrong_repository', pr['number'])
        require(actual['state'] == 'open' and not actual['draft'], 'unresolved_pr', pr['number'])
        require(all(actual[k] == v for k, v in expected.items()), 'stale_pr', {'pr': pr['number'], 'expected': expected, 'actual': actual})
        require(all(actual['checks'].get(c) == 'success' for c in pr['required_checks']),
                'missing_checks', {'pr': pr['number'], 'required': pr['required_checks'], 'actual': actual['checks']})


def check_validation(spec, result, tree):
    require(result.get('version') == 1 and result.get('target') == spec['target']
            and result.get('tree') == tree, 'wrong_validation_tree', result)
    needed = {'source'} if spec['policy'] == 'maintenance' else CHECKS
    require(all(result.get('checks', {}).get(k) is True for k in needed), 'failed_checks', result.get('checks'))
    if spec['policy'] in ('recovery', 'source-maintenance'):
        require(result.get('losses') == {'code': 0, 'data': 0, 'link': 0}, 'coverage_loss', result.get('losses'))
        delta = result.get('delta', {})
        keys = ('matched_code', 'matched_data', 'complete_code', 'complete_data')
        require(all(type(delta.get(k)) in (int, float) and math.isfinite(delta[k]) and delta[k] >= 0 for k in keys), 'coverage_loss', delta)
        if spec['policy'] == 'recovery':
            require(any(delta[k] > 0 for k in keys), 'zero_gain', 'Prerequisites require a net-positive recovery batch')
        else:
            ranges = ('code_coverage', 'code_exact', 'code_linked', 'data_coverage', 'data_exact', 'data_linked', 'function_coverage', 'function_exact', 'function_linked')
            raw_ranges = result.get('zero_lost_address_ranges')
            require(isinstance(raw_ranges, dict) and set(raw_ranges) == set(ranges) and all(type(v) is int and v == 0 for v in raw_ranges.values()), 'missing_extent_gate', raw_ranges)
            extra = ('matched_functions', 'total_functions', 'total_code', 'total_data')
            require(all(type(delta.get(k)) is int and delta[k] >= 0 for k in extra), 'coverage_loss', delta)
            hashes = result.get('raw_report_sha256')
            require(isinstance(hashes, dict) and set(hashes) == {'baseline', 'candidate'} and all(isinstance(v, str) and re.fullmatch(r'[0-9a-f]{64}', v) for v in hashes.values()), 'missing_raw_reports', hashes)
        require(result.get('dol_sha1') == '0d85744b51d7379efb025a943d0cd5aaae2191a3', 'wrong_dol', result.get('dol_sha1'))


class GitHub:
    def get(self, suffix):
        return json.loads(run(['gh', 'api', 'repos/' + REPOSITORY + ('/' + suffix if suffix else '')]))

    def branch(self, name):
        repo = self.get('')
        require(repo['full_name'] == REPOSITORY and repo['default_branch'] == name,
                'wrong_base', 'Repository/default branch changed')
        return {'name': name, 'head': self.get('branches/' + name)['commit']['sha']}

    def prs(self, spec):
        result = {}
        for pr in spec['prs']:
            p = self.get('pulls/' + str(pr['number']))
            # Latest run by check name wins. Paginate: a large stack must not hide failures.
            checks = {}
            page = 1
            while True:
                rows = self.get(f"commits/{p['head']['sha']}/check-runs?per_page=100&page={page}")['check_runs']
                for row in sorted(rows, key=lambda x: x['id'], reverse=True):
                    checks.setdefault(row['name'], row['conclusion'] if row['status'] == 'completed' else row['status'])
                if len(rows) < 100:
                    break
                page += 1
            result[pr['number']] = {
                'repository': p['base']['repo']['full_name'], 'head': p['head']['sha'],
                'head_repository': p['head']['repo']['full_name'], 'head_ref': p['head']['ref'],
                'base_sha': p['base']['sha'], 'base_ref': p['base']['ref'],
                'state': p['state'], 'draft': p['draft'], 'checks': checks,
                'merged': p['merged'], 'merge_commit': p['merge_commit_sha']}
            require(result[pr['number']]['head_repository'] == REPOSITORY,
                    'wrong_repository', 'Only same-fork heads are supported')
        return result


class Queue:
    def __init__(self, spec, state, api=None):
        self.spec, self.state = spec, state
        self.api = api or GitHub()
        self.repo = state / 'checkout'
        self.journal = state / 'receipt.json'
        self.record = {'version': 1, 'spec_sha256': hashlib.sha256(canonical(spec).encode()).hexdigest(), 'state': 'new'}
        if self.journal.exists():
            self.record = json.loads(self.journal.read_text())
            require(self.record['spec_sha256'] == hashlib.sha256(canonical(spec).encode()).hexdigest(),
                    'different_batch', 'Use a new state directory for a changed manifest')

    def write(self, **fields):
        self.record.update(fields)
        save(self.journal, self.record)

    def git(self, *args, env=None):
        return run(['git', '-c', 'core.hooksPath=/dev/null', '-C', str(self.repo), *args], env=env)

    def live_guard(self):
        evidence(self.spec)
        check_live(self.spec, self.api.prs(self.spec), self.api.branch(self.spec['default_branch']))

    def construct(self):
        if not self.repo.exists():
            run(['git', 'init', str(self.repo)])
            self.git('remote', 'add', 'origin', REMOTE)
        require(self.git('remote', 'get-url', 'origin') == REMOTE, 'wrong_repository', 'Unexpected checkout remote')
        require(not self.git('status', '--porcelain', '--untracked-files=no'),
                'dirty_state_checkout', 'Preserve and investigate tracked state edits; no reset is performed')
        # Fetch only immutable selected objects, never fetch/push a wildcard refspec.
        self.git('fetch', '--no-tags', 'origin', self.spec['target'], *[p['head'] for p in self.spec['prs']])
        current = self.spec['target']
        commits = []
        env = os.environ.copy()
        env.update(GIT_AUTHOR_NAME='PSO mechanical queue', GIT_AUTHOR_EMAIL='queue@localhost',
                   GIT_COMMITTER_NAME='PSO mechanical queue', GIT_COMMITTER_EMAIL='queue@localhost',
                   GIT_AUTHOR_DATE=f"@{self.spec['commit_epoch']} +0000",
                   GIT_COMMITTER_DATE=f"@{self.spec['commit_epoch']} +0000")
        for pr in self.spec['prs']:
            # An explicit ordered batch can include structural bases, but never omit one.
            self.git('merge-base', '--is-ancestor', pr['base_sha'], current)
            self.git('merge-base', '--is-ancestor', pr['review_base'], pr['head'])
            covered = subprocess.run(['git', '-C', str(self.repo), 'merge-base', '--is-ancestor',
                                      pr['review_base'], current], capture_output=True)
            require(covered.returncode == 0, 'unreviewed_prerequisite',
                    {'pr': pr['number'], 'review_base': pr['review_base'], 'accumulated': current})
            merged = subprocess.run(['git', '-C', str(self.repo), 'merge-tree', '--write-tree', current, pr['head']],
                                    text=True, capture_output=True)
            require(merged.returncode == 0, 'conflict', {'pr': pr['number'], 'diagnostic': merged.stdout[-2000:]})
            tree = merged.stdout.splitlines()[0]
            require(SHA.fullmatch(tree), 'invalid_tree', pr['number'])
            current = self.git('commit-tree', tree, '-p', current, '-p', pr['head'], '-m',
                               f"Merge reviewed fork PR #{pr['number']}", env=env)
            commits.append({'pr': pr['number'], 'commit': current, 'tree': tree, 'head': pr['head']})
        self.git('checkout', '--detach', current)
        self.git('diff', '--check', self.spec['target'], current)
        if self.spec['policy'] == 'maintenance':
            paths = self.git('diff', '--name-only', self.spec['target'], current).splitlines()
            require(all(p.startswith(('tools/', 'docs/', '.github/')) or p in ('README.md', 'CONTRIBUTING.md', 'AGENTS.md')
                        for p in paths), 'maintenance_scope', paths)
        if self.spec['policy'] == 'source-maintenance':
            # Preserve every filename byte: the normal git helper strips stdout.
            diff = subprocess.run(['git', '-c', 'core.hooksPath=/dev/null', '-C', str(self.repo),
                                   'diff', '--no-renames', '--name-only', '-z', self.spec['target'], current],
                                  capture_output=True)
            require(diff.returncode == 0, 'command_failed', {'command': 'git diff --name-only -z', 'returncode': diff.returncode})
            raw = diff.stdout
            require(bool(raw) and raw.endswith(b'\0'), 'source_maintenance_scope', 'Empty or malformed path list')
            paths = [os.fsdecode(path) for path in raw[:-1].split(b'\0')]
            require(all(source_maintenance_path(p) for p in paths), 'source_maintenance_scope', paths)
        if self.spec['policy'] == 'recovery':
            changed = subprocess.run(['git','-c','core.hooksPath=/dev/null','-C',str(self.repo),
                                      'diff','--no-ext-diff','--name-only','-z',self.spec['target'],current,'--','configure.py'],capture_output=True)
            require(changed.returncode==0, 'command_failed', 'config diff')
            config = self.spec.get('config_admission')
            require(bool(changed.stdout)==(config is not None), 'invalid_config_admission', 'Configuration change requires exactly one reviewed packet')
            if config is not None:
                evidence(self.spec)
                checker=Path(config['checker']['path'])
                require(not checker.resolve().is_relative_to(self.repo.resolve()), 'invalid_config_admission', 'Checker must be external')
                request=self.state/('config-plan-request-'+str(time.time_ns())+'.json')
                output=self.state/('config-plan-result-'+str(time.time_ns())+'.json')
                save(request, {'mode':'plan','repo':str(self.repo.resolve()),'packet':config['packet'],'checker':config['checker'],
                               'cli':{'path':str(Path(__file__).resolve()),'sha256':digest(Path(__file__).resolve())},
                               'target':self.spec['target'],'candidate':current,'tree':tree,'prs':self.spec['prs'],
                               'commits':commits,'output':str(output.resolve())})
                result=subprocess.run([sys.executable,'-I',str(checker),str(request.resolve())],capture_output=True,text=True)
                require(result.returncode==0 and output.is_file() and not output.is_symlink(), 'config_preflight_rejected', result.stderr[-2000:])
                plan=json.loads(output.read_text())
                require(isinstance(plan,dict) and set(plan)=={'packet_sha256','target','candidate','tree','effective_argv'} and plan['packet_sha256']==config['packet']['sha256'] and plan['target']==self.spec['target'] and plan['candidate']==current and plan['tree']==tree and isinstance(plan['effective_argv'],list) and bool(plan['effective_argv']), 'config_preflight_rejected', 'Invalid plan receipt')
                require(digest(checker)==config['checker']['sha256'] and digest(config['packet']['path'])==config['packet']['sha256'], 'stale_config_admission', '')
                self.record['config_plan']={'path':str(output),'sha256':digest(output),'packet_sha256':config['packet']['sha256']}
        self.write(state='planned', candidate=current, tree=tree, commits=commits)
        return current, tree

    def verify(self, validator, expected_hash, environment):
        require(validator.is_absolute() and validator.is_file() and not validator.is_symlink(), 'untrusted_validator', str(validator))
        require(not validator.is_relative_to(self.repo.resolve()) and digest(validator) == expected_hash,
                'untrusted_validator', 'Validator must be pinned outside candidate checkout')
        require(environment.is_absolute() and digest(environment) == self.spec.get('environment_sha256'),
                'stale_environment', str(environment))
        output = self.state / ('validation-' + str(time.time_ns()) + '.json')
        request = self.state / 'validation-request.json'
        save(request, {'version': 1, 'repository': REPOSITORY, 'target': self.spec['target'],
                       'candidate': self.record['candidate'], 'tree': self.record['tree'],
                       'checkout': str(self.repo), 'state': str(self.state), 'policy': self.spec['policy'],
                       'environment': str(environment), 'output': str(output),
                       'config_admission': self.spec.get('config_admission'), 'config_plan':self.record.get('config_plan'), 'prs': self.spec['prs'], 'commits': self.record['commits'],
                       'validator': {'path':str(validator), 'sha256':expected_hash},
                       'cli': {'path':str(Path(__file__).resolve()), 'sha256':digest(Path(__file__).resolve())}})
        request_sha256=digest(request)
        self.write(state='validating', validator_sha256=expected_hash, validator_path=str(validator), environment_path=str(environment))
        # Validator code is supplied by the operator, never by candidate content.
        with (self.state / 'validator.log').open('a') as log:
            result = subprocess.run([sys.executable, '-I', str(validator), str(request)], text=True,
                                    stdout=log, stderr=subprocess.STDOUT,
                                    pass_fds=(self.lock_fd,) if hasattr(self, 'lock_fd') else ())
        require(result.returncode == 0 and output.is_file(), 'failed_build_or_checks', {'returncode': result.returncode, 'log': str(self.state / 'validator.log')})
        require(digest(validator) == expected_hash and digest(environment) == self.spec['environment_sha256'] and digest(request)==request_sha256,
                'changed_validator', 'Harness/environment changed during validation')
        check_validation(self.spec, json.loads(output.read_text()), self.record['tree'])
        require(self.git('rev-parse', 'HEAD') == self.record['candidate'] and
                not self.git('status', '--porcelain', '--untracked-files=no'), 'candidate_changed', 'Tracked tree changed during validation')
        self.write(state='validated', validation=str(output), validation_sha256=digest(output), validation_request=str(request), validation_request_sha256=request_sha256)

    def prepare_readme(self, environment):
        # Opt-in migration: the operator pins trusted code outside the checkout.
        config = self.spec.get('readme_update')
        if config is None:
            return
        require(self.spec['policy'] == 'recovery', 'invalid_readme_policy', 'Only fresh recovery measurements update README')
        generator = Path(config.get('generator', ''))
        require(generator.is_absolute() and generator.is_file() and not generator.is_symlink() and
                not generator.resolve().is_relative_to(self.repo.resolve()) and digest(generator) == config.get('sha256'),
                'stale_readme_generator', str(generator))
        validation = Path(self.record['validation'])
        require(digest(validation) == self.record['validation_sha256'], 'stale_validation', str(validation))
        data = json.loads(validation.read_text())
        env_data = json.loads(Path(environment).read_text())
        review = env_data['acceptance_capacity']['review']
        review_path = Path(review['path'])
        require(review_path.is_absolute() and not review_path.is_symlink() and digest(review_path) == review['sha256'] == data.get('review_sha256'), 'stale_review', '')
        reports = data.get('raw_report_paths', {})
        report_hashes = data.get('raw_report_sha256', {})
        builds = data.get('acceptance_builds', {})
        require(set(reports) == set(report_hashes) == {'baseline', 'candidate'} and set(builds) == {'baseline', 'candidate'}, 'missing_readme_evidence', '')
        entries = {}
        for role in ('baseline', 'candidate'):
            path = Path(reports[role])
            require(path.is_absolute() and path.resolve() == path and path.is_file() and not path.is_symlink() and digest(path) == report_hashes[role], 'stale_raw_report', role)
            entries[role] = {'path': str(path), 'sha256': report_hashes[role]}
        inputs = {role: builds[role]['provenance'] for role in ('baseline', 'candidate')}
        coverage = Path(data['coverage_receipt'])
        require(coverage.is_absolute() and coverage.resolve() == coverage and coverage.is_file() and coverage.is_relative_to(self.state.resolve()), 'invalid_coverage_receipt', '')
        coverage_sha = data.get('coverage_receipt_sha256')
        require(isinstance(coverage_sha, str) and re.fullmatch(r'[0-9a-f]{64}', coverage_sha) is not None, 'missing_coverage_binding', '')
        require(digest(coverage) == coverage_sha, 'stale_coverage_receipt', '')
        source = self.record['candidate']
        mode = self.git('ls-tree', source, '--', 'README.md').split()
        require(len(mode) == 4 and mode[0:2] == ['100644', 'blob'] and mode[3] == 'README.md', 'invalid_readme_mode', mode)
        original = self.state / ('readme-input-' + str(time.time_ns()))
        original.write_bytes(subprocess.check_output(['git', '-C', str(self.repo), 'show', source + ':README.md']))
        req = self.state / ('readme-request-' + str(time.time_ns()) + '.json')
        first = self.state / ('readme-output-' + str(time.time_ns()))
        args = {'reports': entries, 'inputs': inputs, 'readme': str(original), 'source': source,
                'epoch': self.spec['commit_epoch'], 'output': str(first)}
        save(req, args)
        for output in (first, self.state / ('readme-repeat-' + str(time.time_ns()))):
            args['output'] = str(output); save(req, args)
            run([sys.executable, '-I', str(generator), str(req)], cwd=self.state)
            require(output.is_file() and not output.is_symlink(), 'invalid_readme_output', '')
            require(output.read_bytes() == first.read_bytes(), 'nondeterministic_readme', '')
        require(digest(generator) == config['sha256'] and digest(validation) == self.record['validation_sha256'] and digest(coverage) == coverage_sha and all(digest(Path(v['path'])) == v['sha256'] for v in entries.values()), 'stale_readme_evidence', '')
        old, new = original.read_bytes(), first.read_bytes()
        start, end = b'<!-- progress-table -->', b'\n## Target\n'
        require(old.count(start) == new.count(start) == old.count(end) == new.count(end) == 1 and old.split(start, 1)[0] == new.split(start, 1)[0] and old.split(end, 1)[1] == new.split(end, 1)[1], 'readme_scope', 'Content outside progress region changed')
        if new == old:
            self.write(publication_candidate=source, publication_tree=self.record['tree'], readme_evidence={'generator': str(generator), 'generator_sha256': config['sha256'], 'reports': entries, 'coverage': str(coverage), 'coverage_sha256': coverage_sha, 'review': str(review_path), 'review_sha256': review['sha256']})
            return
        blob = subprocess.check_output(['git', '-C', str(self.repo), 'hash-object', '-w', '--stdin'], input=first.read_bytes()).decode().strip()
        index = self.state / ('readme-index-' + str(time.time_ns()))
        env = os.environ.copy(); env['GIT_INDEX_FILE'] = str(index)
        self.git('read-tree', source, env=env)
        self.git('update-index', '--add', '--cacheinfo', '100644,' + blob + ',README.md', env=env)
        tree = self.git('write-tree', env=env)
        require(self.git('diff-tree', '--no-commit-id', '--name-only', '-r', source, tree) == 'README.md', 'readme_scope', '')
        env.update(GIT_AUTHOR_NAME='PSO mechanical queue', GIT_AUTHOR_EMAIL='queue@localhost', GIT_COMMITTER_NAME='PSO mechanical queue', GIT_COMMITTER_EMAIL='queue@localhost', GIT_AUTHOR_DATE=f"@{self.spec['commit_epoch']} +0000", GIT_COMMITTER_DATE=f"@{self.spec['commit_epoch']} +0000")
        final = self.git('commit-tree', tree, '-p', source, '-m', 'Update README progress from validated source', env=env)
        self.write(publication_candidate=final, publication_tree=tree, readme_blob=blob,
                   readme_evidence={'generator': str(generator), 'generator_sha256': config['sha256'], 'reports': entries, 'coverage': str(coverage), 'coverage_sha256': coverage_sha, 'review': str(review_path), 'review_sha256': review['sha256']})

    def check_readme_publication(self):
        if 'publication_candidate' not in self.record:
            require(self.spec.get('readme_update') is None, 'missing_readme_transaction', '')
            return self.record['candidate']
        evidence = self.record['readme_evidence']
        if self.record.get('validator_path'):
            require(digest(self.record['validator_path']) == self.record['validator_sha256'] and digest(self.record['environment_path']) == self.spec['environment_sha256'], 'stale_validation_pins', '')
        validation = json.loads(Path(self.record['validation']).read_text())
        require(validation.get('coverage_receipt') == evidence['coverage'] and validation.get('coverage_receipt_sha256') == evidence['coverage_sha256'], 'coverage_binding_mismatch', '')
        require(digest(evidence['review']) == evidence['review_sha256'] and digest(evidence['generator']) == evidence['generator_sha256'] and digest(evidence['coverage']) == evidence['coverage_sha256'] and digest(self.record['validation']) == self.record['validation_sha256'] and all(digest(v['path']) == v['sha256'] for v in evidence['reports'].values()), 'stale_readme_evidence', '')
        source, final = self.record['candidate'], self.record['publication_candidate']
        require(self.git('rev-parse', final + '^{tree}') == self.record['publication_tree'], 'readme_tree_changed', '')
        if final != source:
            require(self.git('show', '-s', '--format=%P', final) == source and self.git('diff-tree', '--no-commit-id', '--name-only', '-r', source, final) == 'README.md' and self.git('rev-parse', final + ':README.md') == self.record['readme_blob'] and self.git('ls-tree', final, '--', 'README.md').startswith('100644 blob '), 'readme_scope', '')
        return final

    def recover_publication(self):
        # A lost push response is never blindly retried. Inspect the remote graph first.
        current = self.api.branch(self.spec['default_branch'])['head']
        self.git('fetch', '--no-tags', 'origin', current)
        result = subprocess.run(['git', '-C', str(self.repo), 'merge-base', '--is-ancestor', self.record.get('publication_candidate', self.record['candidate']), current], capture_output=True)
        if result.returncode != 0:
            require(not self.record.get('published_commit'), 'publication_diverged',
                    'Previously verified publication is no longer reachable; investigate, never republish blindly')
            require(current == self.spec['target'], 'publication_diverged', {'remote': current, 'candidate': self.record['candidate']})
            self.write(state='not_published', remote_head=current)
            return False
        # Persist proven publication before any fallible metadata API lookup.
        self.write(state='published_unverified', remote_head=current,
                   published_commit=self.record.get('publication_candidate', self.record['candidate']))
        prs = self.api.prs(self.spec)
        pending = [p['number'] for p in self.spec['prs'] if not prs[p['number']]['merged']]
        self.write(state='published_metadata_pending' if pending else 'published', remote_head=current,
                   published_commit=self.record.get('publication_candidate', self.record['candidate']), pending_pr_metadata=pending,
                   pr_statuses={str(n): {'merged': p['merged'], 'merge_commit': p['merge_commit']} for n, p in prs.items()})
        return True

    def publication_destination(self):
        # get-url --push --all resolves pushurl and url.* rewrites. Inspect the
        # effective write destinations, not merely the fetch URL. No extra target.
        urls = self.git('remote', 'get-url', '--push', '--all', 'origin').splitlines()
        require(urls == [REMOTE], 'unsafe_publication_destination',
                'Expected exactly the personal-fork publication URL; pushurl/rewrite/additional destination rejected')
        return urls[0]

    def check_config_before_publication(self):
        if self.spec.get('config_admission') is None: return
        require(self.spec['policy']=='recovery' and self.record.get('validation_request'), 'missing_config_validation', '')
        environment=Path(self.record['environment_path'])
        require(digest(environment)==self.spec['environment_sha256'] and digest(self.record['validator_path'])==self.record['validator_sha256'], 'stale_config_admission', '')
        data=json.loads(environment.read_text())
        entry=data['strict_loss_guard']['adapter']
        adapter=Path(entry['path'])
        require(adapter.is_absolute() and adapter.is_file() and not adapter.is_symlink() and not adapter.resolve().is_relative_to(self.repo.resolve()) and digest(adapter)==entry['sha256'], 'stale_config_adapter', '')
        request=Path(self.record['validation_request'])
        require(digest(request)==self.record.get('validation_request_sha256'), 'stale_config_request', '')
        values=json.loads(request.read_text())
        require(values.get('prs')==self.spec['prs'] and values.get('commits')==self.record['commits'] and values.get('config_plan')==self.record.get('config_plan'), 'stale_config_request', '')
        require(values.get('candidate')==self.record['candidate'] and values.get('tree')==self.record['tree'] and values.get('target')==self.spec['target'] and values.get('config_admission')==self.spec['config_admission'] and values.get('environment')==str(environment), 'stale_config_request', '')
        result=subprocess.run([sys.executable,'-I',str(adapter),'--check-config',str(request)],capture_output=True,text=True)
        require(result.returncode==0 and digest(adapter)==entry['sha256'] and digest(environment)==self.spec['environment_sha256'] and digest(request)==self.record['validation_request_sha256'], 'stale_config_admission', result.stderr[-2000:])

    def publish(self):
        self.live_guard()
        self.publication_destination()
        self.check_config_before_publication()
        # The lease is a narrowly scoped expected-old compare-and-swap. Prove
        # ancestry independently so this operation cannot discard any history.
        self.git('merge-base', '--is-ancestor', self.spec['target'], self.record['candidate'])
        require(self.git('rev-parse', self.record['candidate'] + '^{tree}') == self.record['tree'],
                'candidate_changed', 'Candidate tree changed before publication')
        publication = self.check_readme_publication()
        self.git('merge-base', '--is-ancestor', self.spec['target'], publication)
        for pr in self.spec['prs']:
            self.git('merge-base', '--is-ancestor', pr['head'], publication)
        self.write(state='publishing')  # fsync before any remote mutation
        # Re-resolve immediately before the write; do not use a literal URL that
        # can have different pushInsteadOf semantics from an explicit pushurl.
        self.publication_destination()
        ref = 'refs/heads/' + self.spec['default_branch']
        result = subprocess.run(['git', '-c', 'core.hooksPath=/dev/null', '-C', str(self.repo),
                                 'push', '--atomic', '--force-with-lease=' + ref + ':' + self.spec['target'],
                                 'origin', publication + ':' + ref],
                                text=True, capture_output=True,
                                pass_fds=(self.lock_fd,) if hasattr(self, 'lock_fd') else ())
        self.write(push_returncode=result.returncode, push_diagnostic=result.stderr[-2000:])
        # Even an error can be an interrupted response after successful publication.
        require(self.recover_publication(), 'publication_rejected', self.record.get('push_diagnostic'))

    def execute(self, mode, validator=None, validator_hash=None, environment=None):
        if self.record['state'] in ('publishing', 'publication_uncertain', 'published_unverified', 'published', 'published_metadata_pending'):
            if self.recover_publication():
                return self.record
        self.live_guard()
        self.construct()
        if mode == 'plan':
            return self.record
        require(validator is not None and validator_hash and environment is not None,
                'missing_validator', 'Pinned external validator and environment required')
        # Rebuild on retry: no unverifiable reuse of a successful-looking receipt.
        self.verify(validator, validator_hash, environment)
        if mode == 'execute' and self.spec['policy'] == 'recovery':
            require(self.spec.get('readme_update') is not None, 'missing_readme_transaction', 'Recovery publication requires pinned README generator')
        self.prepare_readme(environment)
        self.live_guard()
        if mode == 'execute':
            require(self.spec.get('publication_freeze') is True, 'missing_publication_freeze',
                    'Coordinator must freeze selected heads and other merge writers during publication')
            self.publish()
        else:
            self.write(state='dry_run_pass')
        return self.record


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('mode', choices=('plan', 'dry-run', 'execute'))
    ap.add_argument('--batch', type=Path, required=True)
    ap.add_argument('--state', type=Path, required=True, help='Unique private state directory; retained for recovery')
    ap.add_argument('--validator', type=Path)
    ap.add_argument('--validator-sha256')
    ap.add_argument('--environment', type=Path)
    args = ap.parse_args(argv)
    # Keep failure handling and every journal write inside the acquired lock's
    # lifetime. A retry must not publish between failure and receipt persistence.
    with ExitStack() as lifetime:
        queue = None
        try:
            spec = json.loads(args.batch.read_text())
            validate_spec(spec)
            state = args.state.resolve()
            state.mkdir(parents=True, exist_ok=True)
            # One process across all batches; same existing inode, never delete locks.
            lock = lifetime.enter_context(open('/tmp/pso-mechanical-merge-queue.lock', 'a'))
            fcntl.flock(lock, fcntl.LOCK_EX)
            queue = Queue(spec, state)
            queue.lock_fd = lock.fileno()
            result = queue.execute(args.mode, args.validator, args.validator_sha256, args.environment)
            print(json.dumps(result, indent=2))
            return 0
        except (Rejected, OSError, ValueError, KeyError, TypeError, AttributeError) as exc:
            error = {'state': 'rejected', 'code': getattr(exc, 'code', 'invalid_input'),
                     'detail': getattr(exc, 'detail', str(exc))}
            if queue:
                state = queue.record.get('state')
                if state in ('publishing', 'publication_uncertain', 'published_unverified',
                             'published_metadata_pending', 'published'):
                    error.update(state='published_unverified' if queue.record.get('published_commit')
                                 else 'publication_uncertain', candidate=queue.record.get('candidate'),
                                 published_commit=queue.record.get('published_commit'),
                                 remote_head=queue.record.get('remote_head'),
                                 recovery='Rerun the identical manifest and state directory to inspect remote ancestry and metadata; do not submit a new merge')
                    queue.write(state=error['state'], last_error=error)
                else:
                    queue.write(last_error=error)
            print(json.dumps(error, indent=2))
            return 1


if __name__ == '__main__':
    raise SystemExit(main())
