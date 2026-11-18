# Atomic README progress publication

Recovery execution requires `readme_update` in the operator's immutable batch manifest, naming an absolute external `generator` path and its `sha256`. The file must be an independently reviewed and installed copy of `tools/merge_batch_readme.py`; candidate source cannot supply the trusted generator. Source-maintenance and tools-only maintenance do not update README measurements. A plan or legacy dry run can omit the generator, but cannot publish a recovery batch.

The strict external validator must return its bound raw-report paths and hashes, coverage receipt, and both actual ordered linker-input provenance records. The queue reads those private artifacts after full source validation, verifies hashes and the pinned generator, and invokes it twice in isolated Python. It writes only a bounded progress region in `README.md`, retaining unrelated bytes. A no-improvement result preserves the README. Counts and denominators come from the reports; unit and fallback counts must agree with actual linker inputs. Percentages use integer half-up rounding to two decimal places. The attribution identifies the validated source candidate and manifest epoch, avoiding a circular reference to the later README commit.

The queue constructs a deterministic one-parent README-only commit without changing the validated working tree. The durable journal records both the source candidate and publication candidate, the documentation tree/blob, and hashes of the validator output, reports, coverage receipt and generator before the push. Immediately before publication it rechecks evidence, the one-parent/README-only relation, source tree, selected ancestry, live PR readiness and target, and performs one exact-old CAS. A lost push response is reconciled against the recorded publication commit; the generator is not rerun during recovery of an uncertain outcome. No second game build is required for the audited README-only child.

Source availability does not establish installation in a live queue. Runtime changes require independent review, exact installed tool pins and applicable current-main graph and execution qualification. Do not alter a frozen batch or reuse prior successful-looking evidence. Raw reports, private paths, original assets and logs remain local.

## README content scope

Keep the main README focused on the project, build/contributor entry points and
current measured aggregate progress with its validated source attribution. A stats
refresh changes the bounded measurement region only; it must not append worker
status, handoff schemas, queue snapshots, frozen-checkpoint narratives or temporary
validation logs. Preserve the current main README's organization when composing
older branches, rather than restoring removed status material from a branch base.

Reusable, source-safe queue/tool instructions belong in the
[operations reference](operations/README.md), separate from human contributor
guidance. Temporary handoff packets, per-worker reports, detailed coverage reports
and machine-specific evidence stay local; do not mechanically relocate them into
committed documentation. The renderer retains unrelated README bytes, so review
source changes for this scope before publication. This content guidance does not
change executable validation, publication or authorization gates.
