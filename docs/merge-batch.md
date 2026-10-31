# Reviewed local merge batches

`tools/merge_batch.py` takes an explicit ordered selection from the coordinator,
constructs the actual combined tree against the current personal-fork default
branch, validates it, and publishes all merge commits with one atomic expected-old ref update.
It only supports `matthewlewisnewton/pso-decomp`. It never rewrites history, changes
branch rules, deletes branches, submits approvals, or uploads build artifacts.

The coordinator selects the batch and records independent exact-head review.
Mechanical execution does not replace source review. Resolve feedback and publish
any necessary dependency updates **before** selecting immutable heads. A draft,
missing required check, changed head/base/default branch, missing prerequisite,
conflict, or failed validation rejects the whole batch before publication. There is
no conflict resolver or automatic switch to a weaker merge path.

## Publication and interruption contract

The tool makes one local two-parent merge commit per PR, in the supplied order.
The final ref update uses an exact expected-old SHA lease to the default branch,
after independently proving the expected old commit is an ancestor of the candidate.
This narrowly scoped `--force-with-lease=REF:EXPECTED_SHA` is compare-and-swap, not
permission to discard history; unconditional force and divergent candidates are
never allowed. A target move to even a selected ancestor rejects publication. Thus a push
rejection publishes **no prefix of the batch**. Every original PR head remains an
ancestor, allowing GitHub to recognize it as merged; metadata is verified afterward.
The journal distinguishes `publishing`, `publication_uncertain`, `not_published`,
`published_unverified`, `published_metadata_pending` and `published`. A public error
after an uncertain push includes the exact candidate and recovery action; it never
claims rejection when publication may have happened. Proven remote ancestry is
recorded durably before PR metadata is fetched. If the push response is lost, rerun the same command/state: it
checks remote ancestry and PR metadata before retrying any mutation. It can report
publication success with metadata still pending; do not submit duplicate merges.
If the remote has diverged after an uncertain attempt, it rejects for investigation.

All CLI invocations serialize on `/tmp/pso-mechanical-merge-queue.lock`; do not delete
or replace that lock. The coordinator must pause other merge writers and freeze the
selected PR heads for the short final publication phase. GitHub offers no transaction
that atomically asserts multiple PR heads and updates the default ref. The tool
rechecks every live head/base/check immediately before push, and the exact-SHA lease
rejects every target change, but cannot eliminate an external PR-head
update racing *after* the last read. This is a cooperative local queue, not a server
side merge queue or a security sandbox. `execute` additionally requires the explicit
`publication_freeze: true` attestation. Do not set it when that freeze is unavailable.
The effective `origin` push URLs (including pushurl and URL rewrites) are resolved
immediately before publication; exactly one personal-fork URL is required. Extra
or different destinations reject before any write. Client Git hooks are disabled
for queue Git operations. Branch rules that require a different merge route cause
rejection, never bypass.

State directories are private, retained evidence. Do not share them or commit them:
they contain local original inputs and build logs. Source publication is only the
selected Git commits. State/receipt paths and command diagnostics contain no tokens;
Git/gh use the operator's existing authentication without changing credentials.
Do not edit a state checkout or the pinned validator/environment during execution.

## Input

Save a JSON manifest with this shape (replace every placeholder):

```json
{
  "version": 1,
  "repository": "matthewlewisnewton/pso-decomp",
  "default_branch": "main",
  "target": "CURRENT_DEFAULT_COMMIT_40_HEX",
  "policy": "recovery",
  "authorization": "Parent batch selection and publication-freeze reference",
  "publication_freeze": true,
  "commit_epoch": 1793476000,
  "environment_sha256": "SHA256_OF_LOCAL_ENVIRONMENT_JSON",
  "prs": [{
    "number": 123,
    "head": "REVIEWED_HEAD_40_HEX",
    "head_ref": "codex/fork-feature",
    "base_ref": "main",
    "base_sha": "LIVE_PR_BASE_COMMIT_40_HEX",
    "review_base": "INDEPENDENT_REVIEW_BASE_40_HEX",
    "kind": "recovery",
    "required_checks": ["source-checks"],
    "review": {
      "verdict": "pass", "independent": true,
      "reviewer": "Independent reviewer identity",
      "head": "REVIEWED_HEAD_40_HEX",
      "base": "INDEPENDENT_REVIEW_BASE_40_HEX",
      "path": "/absolute/private/review.txt",
      "sha256": "SHA256_OF_REVIEW_FILE"
    }
  }]
}
```

Use check-run names, not workflow names. Required checks must be successful on each
exact PR head; queued self-hosted checks are not a pass. Select the actual mandatory
hosted source checks; binary correctness comes from local full validation. The tool
requires PRs to be ready, not drafts. The coordinator handles that transition after
review. `base_sha` must match current GitHub metadata; `review_base` preserves the
independent review boundary. Both the live base and the independent review base must already be ancestors of
the accumulated candidate; order dependencies explicitly. No hidden discovery broadens the batch.

A `recovery` batch requires no lost exact code/data/address coverage or source links,
plus positive matched code/data or source-linked code/data gain across the whole
batch. Necessary zero-gain structural items have `kind: prerequisite` and a concrete
`reason`; they can land with a dependent positive-gain recovery, never as speculative
filler. DOL success alone is not gain and fallback is never counted as source linkage.

An explicitly authorized `maintenance` batch requires every item to have
`kind: maintenance` and restricts its changed paths to `tools/`, `docs/`, `.github/`,
README/CONTRIBUTING/AGENTS. It runs source checks without claiming binary validation
or positive game coverage. Review remains mandatory. Build-system changes outside
that bounded scope reject and need a separately reviewed extension.

## Validator and local environment

Copy the **reviewed** `merge_batch_validate.py` outside all candidate/state checkouts
and pin its SHA256 on the command line. The CLI rejects a validator inside its own
candidate, hash changes, missing result flags and a result for a different tree.
The bundled validator builds a fresh target baseline and candidate under the existing
exclusive `/tmp/pso-decomp-full-build.lock`, using `ninja -j2`. It never enables the
separate experimental concurrent-build protocol. Acquisition preserves old workers.
Each retry uses a new baseline directory and reruns checks rather than trusting a
receipt for another tree. This is conservative; exact-tree reuse can be added later
with separately reviewed invariants.

Recovery batches may not change `configure.py` or anything in `tools/`: the existing
check/build scripts must be byte-identical to the trusted target. This prevents a
candidate from weakening its own harness. Land independently reviewed tooling as
maintenance first. All child Python entry points use a pinned isolated launcher:
stdlib unittest is loaded before the reviewed tools package, the candidate root
is never an import directory, and configure/generated Ninja/check subprocesses
use that same controlled launcher. Root modules such as `unittest.py` cannot
shadow the harness. Candidate-local `.venv` interpreters are rejected for recovery.
Build children inherit the legacy lock descriptor so interruption cannot release
the gate while a compiler/build child is still running. The harness checks:

- Syntax, synthetic tests, and changed-line whitespace.
- Fresh baseline and candidate full builds and original DOL SHA1.
- `check_pr` original-address code/data coverage and source-link validity.
- Actual ordered Ninja linker inputs versus objdiff source-selection metadata.
- Shared input/tool fingerprints before and after; tracked candidate remains clean.

Shared inputs/tools must remain stable by worker coordination. These checks detect
changes, but do not make reviewed arbitrary build commands a sandbox. Original files
are copied only into private local checkouts, never into Git or published receipts.

The environment JSON for recovery is local and contains only paths:

```json
{
  "version": 1,
  "original_files": "/absolute/local/orig/GPOE8P/files",
  "ninja": "/absolute/local/ninja",
  "dtk": "/absolute/local/dtk",
  "objdiff": "/absolute/local/objdiff-cli",
  "wrapper": "/absolute/local/wibo",
  "compilers": "/absolute/local/compilers",
  "binutils": "/absolute/local/binutils"
}
```

Maintenance uses an empty environment JSON `{}` whose hash is still pinned. No
persistent credentials, service installs or permissions are managed by this tool.
Existing compiler/network sandbox approvals remain the executor's responsibility.

## Commands

Use a unique state directory per manifest. A changed manifest requires a new state;
retry the same manifest/state to recover an interrupted publication.

```sh
python3 /trusted/merge_batch.py plan --batch /private/batch.json --state /private/batch-state
python3 /trusted/merge_batch.py dry-run --batch /private/batch.json --state /private/batch-state \
  --validator /trusted/merge_batch_validate.py --validator-sha256 REVIEWED_SHA256 \
  --environment /private/build-environment.json
python3 /trusted/merge_batch.py execute --batch /private/batch.json --state /private/batch-state \
  --validator /trusted/merge_batch_validate.py --validator-sha256 REVIEWED_SHA256 \
  --environment /private/build-environment.json
```

`plan` fetches immutable objects and constructs local merge commits without building
or publishing. `dry-run` also runs full policy validation but never publishes.
`execute` validates afresh and publishes only on success. All modes return structured
JSON; failures have stable codes and concrete diagnostics. Run fixtures with:

```sh
python3 -m unittest discover -s tools/tests -p 'test_merge_batch.py' -v
```

Fixtures use private local bare repositories and synthetic files; they never contact
GitHub, alter production locks, or require game assets. They test stale inputs,
review/check failures, code/data/link loss, conflict, atomic rejection and retry.
