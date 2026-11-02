"""Local Git fixtures only. No live PR/queue, compiler, preparation or push."""
import contextlib
import io
import copy
import importlib.util
import json
from pathlib import Path
import subprocess
import sys
import unittest
from unittest.mock import patch

from tools.tests import test_merge_batch as fixtures

m = fixtures.m


class DevelopmentPlanTests(unittest.TestCase):
    def setUp(self):
        self.f = fixtures.QueueTests('test_wrong_repository')
        self.f.setUp()
        self.addCleanup(self.f.tearDown)
        self.q, self.batch, self.api = self.f.q, self.f.batch, self.f.api
        self.api.overrides = {'draft': True}

    def rejects(self, code, fn):
        with self.assertRaises(m.Rejected) as caught:
            fn()
        self.assertEqual(caught.exception.code, code)

    def test_draft_plan_deterministic_no_refs_no_validation_or_publication(self):
        before = fixtures.git(self.f.remote, 'for-each-ref', '--format=%(refname) %(objectname)')
        private = fixtures.git(self.q.repo, 'for-each-ref', '--format=%(refname) %(objectname)')
        with patch.object(self.q, 'verify') as verify, patch.object(self.q, 'prepare_readme') as readme, \
             patch.object(self.q, 'publish') as publish, patch.object(self.q, 'recover_publication') as recover:
            first = copy.deepcopy(self.q.execute('plan-development'))
            again = self.q.execute('plan-development')
        for call in (verify, readme, publish, recover): call.assert_not_called()
        self.assertEqual(first, again)
        self.assertEqual(first['state'], 'development-planned')
        self.assertTrue(first['development_only'])
        self.assertFalse(first['publication_authorized'])
        self.assertEqual(first['purpose'], 'plan-development')
        self.assertEqual(json.loads(self.q.journal.read_text()), first)
        self.assertEqual(fixtures.git(self.f.remote, 'for-each-ref', '--format=%(refname) %(objectname)'), before)
        self.assertEqual(fixtures.git(self.q.repo, 'for-each-ref', '--format=%(refname) %(objectname)'), private)
        self.assertFalse((self.q.repo / 'build').exists())
        self.assertEqual({p.name for p in self.f.state.iterdir()}, {'checkout', 'receipt.json'})
        # Objects and selected commit composition are identical to a fresh ready
        # normal plan; only the authority/provenance differs.
        self.api.overrides = {'draft': False}
        state = self.f.root / 'normal'; state.mkdir()
        normal = fixtures.LocalQueue(self.batch, state, self.api)
        subprocess.run(['git', 'clone', str(self.f.remote), str(normal.repo)], check=True, capture_output=True)
        ready = normal.execute('plan')
        for key in ('candidate', 'tree', 'commits'):
            self.assertEqual(first[key], ready[key])
        self.assertEqual(ready['state'], 'planned')

    def test_all_normal_modes_still_reject_drafts(self):
        for mode in ('plan', 'dry-run', 'execute'):
            with self.subTest(mode=mode):
                self.rejects('unresolved_pr', lambda: self.q.execute(mode))

    def test_real_number_open_pr_review_ci_head_base_and_target_required(self):
        for number in (0, -1, '1', None):
            bad = copy.deepcopy(self.batch);bad['prs'][0]['number'] = number
            self.rejects('invalid_spec', lambda: m.validate_spec(bad))
        self.batch['prs'][0]['review']['independent'] = False
        self.rejects('missing_review', lambda: self.q.execute('plan-development'))
        self.batch['prs'][0]['review']['independent'] = True
        for override, error in (({'state': 'closed'}, 'unresolved_pr'),
                                ({'checks': {'source-checks': 'queued'}}, 'missing_checks'),
                                ({'checks': {'source-checks': 'failure'}}, 'missing_checks'),
                                ({'head': 'c' * 40}, 'stale_pr'),
                                ({'base_sha': 'c' * 40}, 'stale_pr'),
                                ({'head_ref': 'different'}, 'stale_pr'),
                                ({'base_ref': 'different'}, 'stale_pr')):
            self.api.overrides = dict(draft=True, **override)
            self.rejects(error, lambda: self.q.execute('plan-development'))
        self.api.overrides = {'draft': True}
        self.f.review.write_text('changed evidence')
        self.rejects('stale_review', lambda: self.q.execute('plan-development'))

    def test_stale_target_and_head_race_fail_closed(self):
        original = self.api.branch
        with patch.object(self.api, 'branch', return_value={'name':'main', 'head':'c' * 40}):
            self.rejects('stale_target', lambda: self.q.execute('plan-development'))
        self.assertEqual(self.api.branch, original)
        guard = self.q.live_guard
        calls = 0
        def race():
            nonlocal calls
            calls += 1
            if calls == 2: self.api.overrides['head'] = 'c' * 40
            return guard()
        with patch.object(self.q, 'live_guard', side_effect=race):
            self.rejects('stale_pr', lambda: self.q.execute('plan-development'))
        self.assertFalse(self.q.record['publication_authorized'])
        self.rejects('development_only', self.q.publish)
        # Failed post-construction checks can be replanned in the same scoped
        # directory, while normal modes remain forbidden.
        self.api.overrides = {'draft':True}
        self.assertEqual(self.q.execute('plan-development')['state'], 'development-planned')

    def test_ancestry_and_config_checks_are_not_bypassed(self):
        hidden = self.batch['prs'][0]['head']
        (self.f.author / 'new').write_text('selected')
        fixtures.git(self.f.author, 'add', 'new');fixtures.git(self.f.author, 'commit', '-m', 'selected')
        fixtures.git(self.f.author, 'push', 'origin', 'feature')
        pr = self.batch['prs'][0]
        pr.update(head=fixtures.git(self.f.author,'rev-parse','HEAD'),review_base=hidden)
        pr['review'].update(head=pr['head'],base=hidden)
        self.rejects('unreviewed_prerequisite', lambda: self.q.execute('plan-development'))

    def test_gratuitous_or_unreviewed_config_rejected_without_executing_checker(self):
        evidence = self.f.root / 'config.json'; evidence.write_text('{}')
        entry = dict(path=str(evidence), sha256=m.digest(evidence))
        self.batch['config_admission'] = dict(checker=entry, packet=entry)
        self.rejects('invalid_config_admission', lambda: self.q.execute('plan-development'))
        self.assertEqual(list(self.f.state.glob('config-plan-*')), [])

    def test_development_journal_cannot_resume_or_be_promoted_by_direct_calls(self):
        record = self.q.execute('plan-development')
        self.api.overrides = {'draft':False}
        reloaded = fixtures.LocalQueue(self.batch,self.f.state,self.api)
        for queue in (self.q, reloaded):
            for mode in ('plan', 'dry-run', 'execute'):
                self.rejects('development_only', lambda: queue.execute(mode))
            for call in (queue.construct, queue.live_guard, queue.publish, queue.recover_publication,
                         queue.publication_destination, queue.check_config_before_publication,
                         queue.check_readme_publication, lambda: queue.verify(None,None,None),
                         lambda: queue.prepare_readme(None)):
                self.rejects('development_only', call)
        self.q.write(state='validated',development_only=False,publication_authorized=True,purpose='acceptance')
        self.assertFalse(self.q.record['publication_authorized'])
        self.rejects('development_only', self.q.publish)
        for result in (record, dict(self.f.result, development_only=True),
                       dict(self.f.result, publication_authorized=False),
                       dict(self.f.result, kind='development-only')):
            self.rejects('development_only', lambda: m.check_validation(self.batch,result,result['tree']))
        bad = dict(self.batch, evidence=record)
        self.rejects('development_only', lambda: m.validate_spec(bad))

    def test_cli_outputs_keep_scope_on_success_and_failure_without_live_lock(self):
        batch = self.f.root / 'batch.json'; batch.write_text(json.dumps(self.batch))
        original_open = open
        def private_lock(path, *args, **kwargs):
            if str(path) == '/tmp/pso-mechanical-merge-queue.lock':
                path = self.f.root / 'fixture-only.lock'
            return original_open(path, *args, **kwargs)
        for fail in (False, True):
            self.api.overrides = {'draft':True, 'checks':{'source-checks':'queued' if fail else 'success'}}
            output = io.StringIO()
            with patch.object(m, 'Queue', return_value=self.q), \
                 patch('builtins.open', private_lock), contextlib.redirect_stdout(output):
                code = m.main(['plan-development','--batch',str(batch),'--state',str(self.f.state)])
            result = json.loads(output.getvalue())
            self.assertEqual(code, 1 if fail else 0)
            self.assertTrue(result['development_only'])
            self.assertFalse(result['publication_authorized'])
            if fail: self.assertEqual(result['code'], 'missing_checks')
        self.assertFalse(self.q._development_planning)

    def test_rejected_scope_switch_preserves_existing_normal_journal(self):
        self.api.overrides = {'draft':False}
        self.q.execute('plan')
        before = self.q.journal.read_bytes()
        batch = self.f.root / 'batch.json';batch.write_text(json.dumps(self.batch))
        original_open = open
        def private_lock(path, *args, **kwargs):
            if str(path) == '/tmp/pso-mechanical-merge-queue.lock': path = self.f.root / 'fixture-only.lock'
            return original_open(path,*args,**kwargs)
        output = io.StringIO()
        with patch.object(m, 'Queue', return_value=self.q), patch('builtins.open',private_lock), contextlib.redirect_stdout(output):
            code = m.main(['plan-development','--batch',str(batch),'--state',str(self.f.state)])
        self.assertEqual(code,1)
        self.assertEqual(json.loads(output.getvalue())['code'],'different_planning_scope')
        self.assertEqual(self.q.journal.read_bytes(),before)
        reloaded = fixtures.LocalQueue(self.batch,self.f.state,self.api)
        self.assertEqual(reloaded.execute('plan')['state'],'planned')

    def test_standalone_acceptance_validators_and_resume_reject_plan_records(self):
        result = self.q.execute('plan-development')
        for module in ('merge_batch_validate_acceptance','merge_batch_validate_zero_loss',
                       'merge_batch_validate_development'):
            spec = importlib.util.spec_from_file_location(module,fixtures.MODULE.with_name(module+'.py'))
            adapter = importlib.util.module_from_spec(spec);spec.loader.exec_module(adapter)
            with self.assertRaisesRegex(RuntimeError, 'development_plan_not_validation'):
                adapter.validate(result)
            if module in ('merge_batch_validate_acceptance', 'merge_batch_validate_development'):
                with self.assertRaisesRegex(RuntimeError, 'development_plan_not_validation'):
                    adapter.load_contract(result,{})
        path = self.f.root / 'dev-record.json';path.write_text(json.dumps(result))
        proc = subprocess.run([sys.executable,'-I',str(fixtures.MODULE.with_name('merge_batch_validate.py')),str(path)],capture_output=True,text=True)
        self.assertNotEqual(proc.returncode,0)
        self.assertIn('development_plan_not_validation',proc.stderr)
        from tools import handoff_resume
        with self.assertRaisesRegex(ValueError,'closed release schema'):
            handoff_resume.validate(result)


if __name__ == '__main__':
    unittest.main()
