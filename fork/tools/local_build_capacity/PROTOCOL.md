# Local build capacity and qualified acceptance audits

This cooperative Linux protocol reserves one acceptance slot and one development
slot for reviewed PSO build graphs. It is not a security sandbox or a proof that
arbitrary build commands are safe. Deployment requires independent review and a
coordinated idle transition; adding these files does not deploy the scheduler.

## Configuration

Run `tools/local_build_capacity/build_capacity.py` from this repository. Every job
supplies its own absolute `--repo` and unique absolute `.json` `--receipt` paths.
The checkout root must exist; receipt parent directories are created as needed.
Set `PSO_BUILD_NINJA=/absolute/path/to/ninja` to an explicitly reviewed executable.
There is no PATH fallback: missing or relative settings are rejected before any
subprocess changes directory. The configured and resolved paths must be outside the
current candidate and all registered writable checkout roots. The same canonical
absolute executable is used throughout each operation. Its path, SHA-256 and file
identity are bound into preparation evidence and checked before Ninja queries,
preflight, execution, and after execution; stale or replaced tools reject admission.
All workers must use a stable compatible Ninja version.
Do not change tool binaries or environment configuration during admitted work.

All workers on a host share these coordination paths:

- Legacy gate: `/tmp/pso-decomp-full-build.lock`
- Workspace/lane locks and root registry: `/tmp/pso-build-capacity-v2/`
- Enable marker: `/tmp/pso-build-capacity-v2-enabled.json`

These are shared protocol identifiers, not per-job configuration. Do not rename,
delete, replace, or bypass lock files to obtain capacity. Existing exclusive workers
must use the same legacy inode. A persistent root registry rejects nested checkout
roots; equal roots serialize through a workspace lock. No automatic cleanup occurs.

## Inputs and write boundaries

Each job needs a disjoint real checkout with exclusive ownership of its writable
outputs. Source/configuration must remain unchanged during preparation, audit, and
build. Review the exact graph and referenced scripts; a successful pathname audit
alone is not sufficient approval for untrusted build code.

Reviewed writes are confined to checkout-local `build/`, `config/`, `build.ninja`,
`objdiff.json`, `compile_commands.json`, `.ninja_log`, and `.ninja_deps`. Admission
checks declared outputs, expanded depfile/response-file paths, known output-directory
bindings, and existing writable trees. Symlinks and hard-linked writable files are
rejected. Unsupported graph rules, included graphs, custom builddir, path syntax,
and out-of-bound outputs fail closed.

Original inputs remain local. Every manifest input and the required DOL must exist;
missing inputs reject isolation rather than permitting extraction into shared input
storage. Shared originals and explicitly referenced tool binaries must be immutable.
Extraction, tool updates/downloads, shared compiler caches and shared Wine prefixes
remain exclusive maintenance operations. The reviewed graph uses Wibo.

Each operation gets private temporary files under its checkout. Python bytecode
writes are disabled for launched build commands and GITHUB_STEP_SUMMARY is removed.
No donor-input permissions, security settings, or persistent services are changed.

## Preparation and graph stability

Prepare under the legacy exclusive gate, using the job's true lane:

```bash
python3 tools/local_build_capacity/build_capacity.py \
  --repo /absolute/checkout --receipt /absolute/receipts/prepare.json \
  --prepare-only --lane acceptance
```

Preparation requests only `ninja -j2 build.ninja`, audits the result, and fingerprints
tracked source/config/tool inputs plus generated build and objdiff configuration.
It does not request a default full build. Missing tools or inputs may need separate,
explicitly scoped exclusive preparation. Review the resulting graph/scripts and
record its `admission.ninja_sha256`; do not relabel old preparation receipts.

Isolated execution checks the preparation receipt and graph hash, then dry-runs the
unchanged graph for both `build.ninja` and `progress`. If setup commands are pending,
it rejects the operation and requires exclusive preparation. Ninja status formatting
is fixed during this check so environment customization cannot hide planned commands.

The execution snapshot preserves rule commands, replacing only configure, split,
and download setup edges with phony leaves for their existing outputs. This avoids
invalidating Ninja's command hashes while removing setup execution from isolated
work. A different manifest filename prevents automatic original-graph regeneration.
No success records are forged. Inputs are fingerprinted again after execution;
workers must prevent concurrent edits because detection cannot undo a race.

## Reserved slots and lock order

The initial policy is one acceptance slot and one development slot, total two.
Development never borrows acceptance capacity. Each build uses `-j2`. A second
development slot requires a measured trial and explicit parent authorization before
changing the marker to total three; no such expansion is implicit in this code.

Order: root registration, workspace EX, acceptance intent, named slot, maintenance
turnstile, legacy gate. Acceptance intent comes **after workspace ownership** to avoid
a same-workspace deadlock. Acceptance uses `acceptance.lock`; development uses
`development-0.lock`. Isolated jobs hold legacy SH; maintenance holds legacy EX.
A maintenance turnstile prevents continuous shared admissions from starving an
already-admitted exclusive maintenance operation. Pending acceptance prevents new
development admission once acceptance owns its workspace.

Machine-wide admission checks require at least 12 GiB MemAvailable for acceptance,
24 GiB for development, and one-minute load no greater than 1.5 times host CPU count.
These are admission thresholds, not resource reservations or cgroup limits. Active
jobs are never killed. Old exclusive workers finish safely; priority is cooperative,
not preemption or an absolute latency guarantee.

Maintenance is one bounded, scoped invocation, never a loop holding the gate across
unrelated work. Do not invoke the wrapper beneath an already-held workspace or legacy
lock. There are no SH-to-EX upgrades. Child processes inherit the held descriptors;
normal failures release wrapper locks and surviving children retain inherited locks.
Do not assume this handles arbitrary daemonization or deliberate descriptor closure.

## Qualified shared acceptance audits

Prefer omitting a redundant standalone audit when prior graph/script review and the
isolated build's existing rechecks already provide the necessary evidence. An audit
never establishes binary correctness or substitutes for a build.

When needed, request a qualified audit explicitly:

```bash
python3 tools/local_build_capacity/build_capacity.py \
  --repo /absolute/checkout --receipt /absolute/receipts/audit.json \
  --audit-only --mode isolated --lane acceptance \
  --prepared-receipt /absolute/receipts/prepare.json \
  --reviewed-graph-sha256 REVIEWED_GRAPH_SHA256
```

This requires the enabled current marker to match the executing wrapper hash, a
successful exclusive preparation receipt, matching checkout/graph/input fingerprints,
and the exact reviewed graph hash. Marker validation repeats after waiting for locks.
Missing/stale proof rejects the request without silently falling back or upgrading.
The audit performs unchanged-graph preflight and a final input fingerprint check.
It holds workspace EX, acceptance intent, acceptance slot, turnstile SH, and legacy
SH, allowing another isolated development build but excluding shared maintenance.
Default/unqualified audits remain exclusive. Receipts report the actual gate mode
and qualification; they are never marked as preparation or successful binary builds.

For a ready acceptance job, operators may briefly pause NEW development submissions
while acceptance crosses bounded preparation/audit/build admission. Let active jobs
finish safely, then resume submissions once acceptance acquires legacy SH. Complete
human review before this brief pause; never hold an indefinite pause for review.
This is an operator handoff, not a daemon or a persistent pending barrier. Observed
concurrency proves overlap only, not throughput improvement or a twofold speedup.

## Controlled rollout and execution

After independent review, pause submissions and wait for active/waiting wrapper
invocations to finish before replacing live source. Never replace code while a worker
might import it. Preserve lock inodes and receipts. Verify the deployed SHA-256 and
coordinate the matching marker update while idle. Initial marker creation must be
exclusive; an existing marker must not be blindly overwritten. Keep provenance and
a rollout receipt. An initial marker has this form:

```json
{"protocol":"pso-build-capacity-v2","revision":4,"enabled":true,"development_slots":1,"total_slots":2,"parent_broadcast":"ACTUAL_AUTHORIZATION_REFERENCE","wrapper_sha256":"REVIEWED_DEPLOYED_SHA256"}
```

Resume only when deployed source and marker agree. Every job still needs its own
fresh preparation and reviewed graph proof, including the pinned Ninja identity.
Receipts from older wrappers without that tool evidence must be regenerated. Build using:

```bash
python3 tools/local_build_capacity/build_capacity.py \
  --repo /absolute/checkout --receipt /absolute/receipts/build.json \
  --mode isolated --lane acceptance \
  --prepared-receipt /absolute/receipts/prepare.json \
  --reviewed-graph-sha256 REVIEWED_GRAPH_SHA256
```

Development uses `--lane development` for both preparation and execution. Merge
serialization remains separately owned; build capacity never authorizes parallel
merges. Main receipts and `.time.json`/`.build.log` siblings use exclusive reservation.
Choose fresh absolute labels; partial reservations remain after failures. Treat an
incomplete receipt after interruption as unknown, never successful.

## Tests

```bash
PYTHONDONTWRITEBYTECODE=1 python3 tools/local_build_capacity/test_build_capacity.py
```

Set PSO_BUILD_NINJA to an explicitly reviewed absolute Ninja executable. Tests use private lock/marker
namespaces and synthetic input files; no original assets or production builds are
needed. Coverage includes graph freshness, path isolation, proof/marker rejection,
qualified-audit overlap, maintenance exclusion, default exclusive behavior, reserved
lanes, same-workspace deadlock prevention, and child lock inheritance. Integration
fixtures use a synthetic input fingerprint while exercising real admission/preflight
and locking. This standalone suite is separate from portable `tools/tests`.
