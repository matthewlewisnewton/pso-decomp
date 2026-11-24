# Local evidence and handoff tools

These tools consume operator-supplied evidence. A file hash verifies bytes, not
receipt authenticity, completeness, independent review, admission or publication
permission. Source availability does not establish live installation or activation.
Keep all actual snapshots, receipts, databases, control files and logs outside the
repository. The main README is for the project overview and aggregate measurements.

## Evidence comparison

```sh
python3 tools/evidence_applicability.py BASELINE.json CURRENT.json
```

The comparator reads independently prepared inventories and reports missing or
changed inputs. It never builds, changes receipts, grants reuse or establishes
current-main acceptance freshness. An unchanged aggregate report alone does not
prove binary equivalence.

Version 1 inventories supply a full `revision`, absolute `root`, `proofs`,
`global_inputs` and a nonempty `consumers` object. Proofs bind the graph and
inventory review; the baseline also binds its development receipt. File entries
use root-relative `path` and `sha256` fields. Supplied paths and resolved paths are
both compared, so a renamed or changed symlink target is a change even if its
bytes match. Global source, tool, compiler, configuration and generated inputs,
plus every consumer's inputs and baseline outputs, must be complete.

An independent verifier must assess graph and receipt semantics, exact review
bindings and inventory completeness before the queue considers reuse. A whole
preparation-graph hash is not a per-consumer dependency inventory. Changed global
inputs affect all consumers; changed consumer inputs affect that consumer. Missing,
new or removed consumers require explicit treatment. All applicable current-main,
raw no-loss, original-DOL and ordered-link-input gates still apply.

## Snapshot reporting

```sh
python3 tools/handoff_report.py snapshot.json
```

The reporter prints JSON without changing the snapshot, queue, repository or
evidence. Refresh observed heads and main from authoritative sources. The snapshot
schema and examples live in [the source](../../tools/handoff_report.py) and
[synthetic tests](../../tools/tests/test_handoff_report.py), rather than in a
committed live queue snapshot.

Source, development, graph, acceptance and publication are distinct claims. The
report checks supplied digests and head/base bindings; it does not parse proof
contents or establish who produced them. Source and development keep their
recorded baselines; graph, acceptance and publication require current-main
bindings. A reported finished turn or held slot is a prompt to confirm release,
not evidence that a release occurred. `ready_eligible` is only a summary of supplied
claims and pending requests; it grants neither readiness nor admission.

## Durable routing

[handoff_state.py](../../tools/handoff_state.py) records receipt references and
routing events in a private SQLite database. `Store.observe` records an explicit
inventory refresh; it cannot make a stage pass. An independent verifier issues
`PinnedReceipts` only after checking the underlying proof, immutable subject and
reviewer independence. Hashing an arbitrary PASS file does not verify it.

`Store.ingest` records a pinned receipt and routing event atomically. Request IDs
are unique: identical replay is safe, conflicting reuse fails. `Store.current`
returns the current event and next owner/action. `Store.events` is historical data,
not a dispatch queue. Close the store when finished. See the source and tests for
the exact envelope fields, stages and allowed verdicts.

Typed actions request review, validation, a queue transaction or publication
reconciliation. They do not grant capacity or publication authority. The existing
queue transaction already validates and publishes; a second dry run or build would
duplicate work. Reconcile an uncertain remote outcome before attempting it again.
HOLD, failure, denial and uncertainty must not be erased by relabelling evidence.
A durable event ID does not promise exactly-once remote completion.

## Optional local development resume

[handoff_resume.py](../../tools/handoff_resume.py) implements a local, disabled-by-
default adapter for an already released development build. It is not a daemon or
an acceptance/publication mechanism. Source merge, runtime installation, graph
qualification, scheduling release and trial authorization are separate actions.

The sole queue installs independently reviewed adapter and wrapper bytes outside
candidate roots and pins their Python/runtime identities. At an existing finite
release, `publish_companion` serializes that release; it cannot grant admission.
An independent verifier checks the actual subject, root, prepared receipt, graph,
inputs, launcher, Ninja and release before issuing its matching approval. The
queue-owned control binds that approval, companion, installed code and a private
persistent journal. Candidate code must never create or edit these trust inputs.
The exact closed schemas are in the source and its tests.

Only an explicitly authorized, independently qualified control may invoke
`resume_one`. It preserves normal resource, maintenance, capacity and frozen-graph
gates. Intent is durable before launch, and the release is consumed immediately
before execution. A changed control, root, output or companion cannot select a
second attempt. Preserve the same journal across restarts; never delete intent to
retry. Uncertain completion blocks relaunch. Disabling control cannot cancel a job
that already crossed the launch boundary; let it finish and retain its locks and
records.

A zero wrapper exit establishes only that invocation's result. The implementation
owner still performs DOL, raw no-loss, source-selection, ordered-input and consumer
validation, fixes review findings and explicitly releases its lane. Legacy
preparation without a full Ninja identity needs the separately authenticated
provenance described in the source contract; never rewrite a historical receipt
or infer its missing inode/time. Optional resume compatibility must not delay
ordinary released work or cause a completed build to run again.

## Synthetic checks

```sh
python3 -m unittest tools.tests.test_evidence_applicability tools.tests.test_handoff_report tools.tests.test_handoff_state
PSO_TEST_NINJA=/absolute/path/to/ninja python3 -m unittest tools.tests.test_handoff_resume -v
```

Use a real Ninja executable for the resume fixtures. These are synthetic tooling
checks, not game-build evidence, admission, a live trial result or measured queue
latency. Keep actual trial measurements and temporary routing reports local.
