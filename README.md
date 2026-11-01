# Phantasy Star Online Episode I & II Plus

A work-in-progress matching decompilation of *Phantasy Star Online Episode I & II Plus* for the Nintendo
GameCube, USA version 1.02 (`GPOE8P`): C and C++ source that compiles to the same code as the game's executable,
function for function, in its original translation units.

Nothing from the game is included here. You need your own copy of the game to build it; see [Legal](#legal).

## Progress

<!-- progress-table -->
| | Matched | Linked |
|:--|--:|--:|
| Code | 94.71% (4,122,892 of 4,353,092) | 76.77% (3,341,952 of 4,353,092) |
| Data | 73.16% (1,288,599 of 1,761,375) | 53.36% (939,823 of 1,761,375) |
| Functions | 98.88% (27,263 of 27,572) | |
| Units | | 69.88% (3,540 of 5,066) |
<!-- /progress-table -->

Measured on `PsoV3.dol` on 2026-11-01 at validated source commit
[`2555fc32dc`](https://github.com/matthewlewisnewton/pso-decomp/commit/2555fc32dc1b5e14de89a260106324f5e1980ee4).
The README-only publication commit records the measurements of its parent source tree.
A function is matched when it compiles to the original's exact bytes. Code, data and
units are linked when the build takes them from compiled source instead of the original. Data includes `.bss`.
The build still uses 1,526 original-object fallback units; matched functions in those units are not counted as
source-linked coverage. Unit counts can change when translation units are consolidated.

## Target

| | |
|---|---|
| Game | Phantasy Star Online Episode I & II Plus, USA v1.02 (`GPOE8P`) |
| Disc | SHA-1 `0ff155311f4cc57951c03baeb1a8cc15de5fe1cd` |
| Executable | `files/PsoV3.dol`, SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3` |
| Compiler | Metrowerks CodeWarrior for GameCube: GC/2.6 for most game code, older versions for the SDK, MetroTRK, MusyX and some game units |

## Building

You need Python 3.10 or newer, [Ninja](https://ninja-build.org/) and your own dump of the disc.

1. Put the disc image (ISO, GCM, RVZ, WIA, GCZ or CISO) in `orig/GPOE8P/`.
2. Run:

       python configure.py
       ninja

The first build downloads the compilers, [decomp-toolkit](https://github.com/encounter/decomp-toolkit),
[objdiff](https://github.com/encounter/objdiff) and binutils into `build/`. On Linux and macOS the compilers run
through [wibo](https://github.com/decompals/wibo); to use Wine instead, pass its path to `configure.py --wrapper`.

`ninja` rebuilds `PsoV3.dol` and checks it against the original's SHA-1, along with the 648 relocatable data files
and the language files the game loads. Code that is not decompiled yet still comes from the disc, so a passing
build does not mean the decompilation is complete. The same goes for the functions Nintendo and Metrowerks wrote
in assembly: `tools/orig_asm.py` rebuilds their bodies from your disc before anything is compiled.

## Objdiff and the progress page

`ninja` also writes `objdiff.json` in the repository folder and the objdiff progress report,
`build/GPOE8P/report.json`.

- **objdiff.** Download [objdiff](https://github.com/encounter/objdiff/releases) and open the repository folder
  in it. It reads `objdiff.json`, rebuilds a unit when you save its source and shows each function next to the
  original.
- **Progress page.** Turn the report into a page you can browse by unit and function:

      python tools/progress_map.py build/GPOE8P/report.json -o build/progress

  Then open `build/progress/index.html` in a browser. Add `--readme README.md` to refresh the table above.

## Working on it

- **Check for regressions.** Run `ninja baseline` before a change and `python tools/check_pr.py` after it. It
  rebuilds, compares the reports by original address, so renaming, folding or splitting units never hides a lost
  match, and checks that every linked unit still links from source.

The GiFoie orbit task now reproduces its original 900-byte update in targeted compiler checks, preserving the
unit's other functions and native task vtable. Its candidate source selection still awaits the full build,
original-address regression checks and proof that the linker takes the compiled object.

[CONTRIBUTING.md](CONTRIBUTING.md) covers what a change can do and the rules for it.
[docs/architecture.md](docs/architecture.md) describes how the executable and the source tree are laid out.
The [documentation index](docs/README.md) links to contributor guides and recovery evidence.

## Credits

Built with [decomp-toolkit](https://github.com/encounter/decomp-toolkit), [objdiff](https://github.com/encounter/objdiff)
and [dtk-template](https://github.com/encounter/dtk-template). The Dolphin SDK and runtime sources are adapted from
other GameCube decompilations; [third_party/](third_party/README.md) lists them.

## Legal

This repository contains no game assets, no game files, no assembly and no code copied from the game. Every line of
source was written by hand, by this project's contributors or by the open-source projects credited above, to
compile into the same machine code as the original. Everything else the build needs comes from your own legally
obtained copy of the game, on your machine, when you build.

*Phantasy Star Online* is a trademark of SEGA. This project is not affiliated with or endorsed by SEGA or Nintendo.

## License

[MIT](LICENSE). Code adapted from other projects keeps its original notices.

### Development evidence comparison

`python3 tools/evidence_applicability.py BASELINE.json CURRENT.json` compares
independently prepared, reviewed inventories. It prints JSON and exits nonzero
when evidence is missing or a file hash does not match. It never changes a
receipt, runs a build, authorizes reuse, or establishes acceptance freshness.
An unchanged aggregate coverage report is not proof of binary equivalence.

Both JSON snapshots have `version: 1`, a full 40-character `revision`, an
absolute `root`, `proofs`, `global_inputs`, and a nonempty `consumers` object.
Every file entry is `{"path": "relative/path", "sha256": "<lowercase 64-digit SHA-256>"}`;
paths must be root-relative, contain no parent traversal, and resolve to regular files inside the snapshot root. Both the supplied path and its resolved root-relative path are compared, so a rename or changed symlink target is treated as a change even when bytes match. `proofs` contains
`graph` and `inventory_review`; the baseline also contains
`development_receipt`. Each is a file entry. `global_inputs` contains nonempty
file-entry maps under each of `source`, `tool`, `compiler`, `config`, and
`generated`. Each consumer has a nonempty `inputs` file-entry map. The baseline
consumer also has a nonempty `outputs` map. Stable keys identify equivalent
inputs across snapshots; all relevant compiler flags, transitive headers,
imported helpers, generated inputs, tools and output artifacts must be covered.
Output paths and hashes in the report identify baseline files only.

These inventories and proof files are **inputs to review**, not independently
verified claims of completeness, successful builds, or proof authenticity. The
operator must independently verify the graph and receipt semantics, the review
binding to both exact inventories, and their completeness before considering the
comparison. Whole-graph hashes from existing preparation receipts alone are not
per-consumer dependency inventories. Missing or stale files make the comparison
incomplete; changed global inputs affect every consumer, and changed consumer
inputs affect that consumer. New or removed consumers are affected. The queue
alone decides whether any artifact may be used, after independent review and
all applicable current-main, raw no-loss, DOL and ordered-link-input gates.

## Handoff snapshot report

`python3 tools/handoff_report.py snapshot.json` prints a JSON report and does
not change the snapshot, queue, repository, or evidence files. The snapshot is
an operator-supplied inventory, not a scheduler or an admission decision. Keep
private snapshots and receipts outside the repository. Refresh observed heads
and current main from authoritative sources before relying on the report.

A version 1 snapshot has this shape (replace the illustrative IDs and hashes):

```json
{
  "version": 1,
  "current_main": "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
  "items": [{
    "id": "PR-1",
    "owner": "author",
    "state": "turn_complete",
    "head": "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
    "observed_head": "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
    "evidence": [{
      "stage": "development",
      "verdict": "pass",
      "head": "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
      "base": "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
      "path": "development-receipt.json",
      "sha256": "0000000000000000000000000000000000000000000000000000000000000000"
    }],
    "requests": [{
      "id": "review-1",
      "kind": "review",
      "state": "pending",
      "owner": "reviewer",
      "head": "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    }],
    "slot": {"state": "held", "owner": "queue"}
  }]
}
```

Use full lowercase 40-character commit IDs and SHA-256 digests. Evidence paths
are relative to the snapshot directory (absolute paths also work). Each stage
may appear once: `source`, `development`, `graph`, `acceptance`, and
`publication` are separate claims. Verdicts are `pass`, `fail`, or
`unknown`. The report checks file bytes against the supplied digest, and
checks claimed head and base bindings; it does **not** parse receipts, verify
their authors, or prove their contents support the supplied claims. Missing or
changed files are unverified. Development and source evidence retain their
recorded base when main advances; graph, acceptance, and publication claims
must name current main. Refresh current-main acceptance after a main change.

Item states are `active`, `turn_complete`, and `complete`. Request kinds
are `review` and `admission`, and request states are `pending`, `done`,
and `cancelled`. Identical repeated request IDs within an item are deduplicated;
conflicting duplicates and invalid input fail the whole report. Pending requests
name the owner who owes the next action, including requests whose head is stale.
A held slot on a finished turn is a prompt to confirm release, not proof of
release. The `ready_eligible` field only means the supplied, hash-verified source
and development claims pass for the observed head and no requests remain
pending. It does not replace independent review, project-specific gates, queue
admission, current-main acceptance, or publication. Labels never grant admission.
Run the synthetic tests with `python3 -m unittest tools.tests.test_handoff_report`.

The separate `tools/handoff_state.py` module provides a durable routing reducer
for a future sole-queue adapter. `handoff_report.py` remains read-only. Store its
SQLite database and receipt files outside the repository; no live integration or
dispatch adapter is included. Import `Store` and `PinnedReceipts` from Python.

- `Store.observe(item, head, main, revision, owners, now_ms)` records an explicit
  inventory refresh. `owners` must supply all five stage owners. Inventory
  revisions must increase when inputs change; old or conflicting observations
  are rejected. An observation cannot establish a passing stage.
- `PinnedReceipts({request_id: sha256})` is the trust boundary. A separate
  independent verifier must issue each pin **after** checking the receipt and
  its underlying evidence, including stage, result, immutable head/base and
  reviewer independence. Do not automatically hash arbitrary files to make pins.
  The module enforces integrity and the closed envelope schema, not the quality
  or identity of the external verifier. It has no CLI for issuing pins.
- `Store.ingest(verifier, request_id, path, now_ms)` records a pinned receipt
  and its routing event atomically. Each JSON envelope has exactly `request_id`,
  `item`, `head`, `base`, `stage`, `verdict`, `producer`, `reviewer`, and
  `completed_ms`. Commit IDs and stages follow the report contract above;
  verdicts are `pass`, `fail`, `unknown`, `hold`, `denied`, or `uncertain`.
  Producer and reviewer must differ. Times are nonnegative integer milliseconds
  on a common clock. Request IDs are globally unique: identical replay is safe,
  but conflicting reuse fails.
- `Store.current(item)` returns one current `event_id`, `next_owner`, typed
  `next_action`, stage observations and any `blocked_reason`.
  `Store.events(item)` is historical audit data, including superseded events;
  it must never be treated as a dispatch queue. `Store.close()` closes the store.

The typed actions are requests for source review, development validation,
graph review, the sole queue transaction, and publication reconciliation.
`request_queue_transaction` leaves all admission, fresh applicability, strict
no-loss, DOL, ordered-link and CAS gates to the existing queue. Its existing
transaction already validates and publishes; adding another dry-run or build
would duplicate work. A publication reconciliation request checks an observed
outcome and conveys no authority to push. Source/development receipts remain
historical when main advances, while graph/acceptance/publication must bind the
current main. Head changes require fresh evidence. Nonpassing receipts block;
conflicting pass receipts cannot erase a HOLD or failure. Denied and uncertain
outcomes remain blocked even across head changes. This first version has no
unblock or denial-retry API; resolution requires independent human handling.

SQLite uses a full-synchronous transaction for the receipt reference, retained
receipt body, event and current pointer. A crash before commit rolls all back;
replaying after commit returns the same logical event ID. Receipt arrival order
and duplicate delivery cannot create another event for the same next action.
There is no external dispatch, so this does not promise exactly-once remote
execution. Any future adapter must be independently reviewed, consume only the
current event, deduplicate its ID, recheck live authority and bind the existing
queue journal; uncertain remote outcomes require reconciliation before retry.

Run `python3 -m unittest tools.tests.test_handoff_state -v`. The sequential
fixture defines a parent relay as one receipt-read/next-owner message after a
stage completes: four receipts require four relays in the manual baseline.
The reducer yields four durable action IDs (zero duplicate IDs on replay),
which a future adapter could consume without those relays. Receipt-to-next-action
latency is the event's `created_ms` minus its triggering receipt's
`completed_ms`: all four fixture values are 7 ms. These are synthetic routing
measurements, not measured live latency or realized compute savings; dispatch
is disabled and live parent relays remain necessary.

The optional `tools/handoff_resume.py` source implements a **disabled-by-default
local trial** for `resume_released_development_build`. It has no daemon, CLI,
peer messaging, acceptance or publication action. The repository wrapper copy
supports `--resume-control`; deployed wrappers and live queue files are separate
and must not be changed until independent executable-source review and a
controlled trial are authorized. Reducer `next_action` events alone cannot
activate this adapter.

Integration instructions for the sole queue:

1. Independently review the exact adapter, local wrapper patch and tests. Copy
   the reviewed files together to a trusted installation with this layout:
   `handoff_resume.py` beside `local_build_capacity/build_capacity.py`. Pin both
   installed source hashes and the resolved `/usr/bin/python3` hash. Existing
   runtime adoption, capacity policy and independent graph review remain gates.
2. At the queue's **existing RELEASED decision**, call
   `publish_companion(release, destination)` once to serialize that same finite
   release. It creates an exclusive, fsynced immutable JSON companion, returning
   its path/hash. It never decides whether to release work. The closed schema
   is `FIELDS` in the module; `test_handoff_resume.py:setUp` is a complete
   synthetic example. Supply the real existing release notice pin and reviewed
   root/head, prepared receipt, graph/input hashes, launcher and Ninja pins,
   fixed output receipt, item and unique release ID. Do not reuse or reinterpret
   a historical release whose owner may already have acted.
3. Supply an independently issued approved-receipt envelope, matching the
   closed schema in `load()`. Its pin must come from the independent verifier
   after checking all underlying evidence, not from automatically hashing an
   arbitrary PASS document. The schema binds action, item, immutable head,
   prepared receipt, actual root, graph/input hashes, reviewer and producer.
   The queue-owned control file separately pins this approval and the entire
   release companion. This control file is a trusted authorization boundary;
   untrusted candidate code must never create or edit it.
4. Create the private control JSON with exactly `version: 1`, `enabled: false`,
   `trial_id`, `companion: {path, sha256}`, `approval_sha256`, `adapter_sha256`,
   `wrapper_sha256`, `python_sha256`, and an absolute private `journal` path.
   Keep it and the journal outside all build roots. Preserve one journal across
   process restarts and trial IDs; never reset it to evade a consumed release.
   Independently review these exact bindings before explicitly enabling one
   controlled release. No enabled control file ships with this patch.
5. At the same local handoff boundary, the sole queue explicitly calls
   `resume_one(control_path)` synchronously. It uses only the fixed local
   wrapper and isolated development arguments, sanitizes the environment,
   persists intent before invoking the wrapper, and returns a structured result.
   The wrapper retains its normal resource/lock admission and frozen-graph
   checks, rechecks control/pins after waiting, then atomically consumes the
   release immediately before launch. No new slot or permission is issued.
6. A `finished` result means only that this wrapper invocation returned zero.
   The owner still owes raw no-loss, original DOL, ordered-input/source gates,
   final review and explicit slot-release reporting. No PASS receipt is created
   by the adapter. Return HOLD, review requests, failures and uncertain outcomes
   through the queue's existing parent result route; never call a peer directly.

Set `enabled: false` to stop new launches; the wrapper checks again after its
admission wait. The final check cannot retroactively cancel a launch that has
already crossed that boundary. Let running work finish and preserve all locks,
receipts and journals. On rollback, remove the optional adapter invocation and
restore the prior independently reviewed wrapper only after active work is
terminal. Never delete intent to get another attempt. A crash before/after
spawn leaves `intent`/`started` without a definitive completion and blocks
relaunch. There is at most one automatic launch attempt per consumed release;
exactly-once completion across arbitrary process crashes is not promised.

Run `PSO_TEST_NINJA=/absolute/real/ninja python3 -m unittest tools.tests.test_handoff_resume -v` before adoption.
The fixtures exercise concurrent/duplicate calls, actual process death around
intent/launch, drift, unsupported actions, HOLD/denial, off-switch changes during
capacity wait, uncertain outcomes, and the actual local wrapper hook with a
synthetic child. They acquire no production locks and run no game builds.
For the controlled trial, `started_ns - observed_ns` measures actual local
receipt-observation-to-resume latency on one monotonic clock; `intent_ns` and
`finished_ns` separate dispatch and completion, and the existing wrapper receipt
records admission wait. Count actual parent relay messages for the same local
handoff: baseline one, adapter target zero. Record launch count (must equal one),
replay launch count (must equal zero), and blocked outcomes. These live metrics
are acceptance criteria, not claims of a trial already performed.

Resume invocation binding: the adapter captures the full verified control and
companion before reservation and sends their identity digest to the fixed wrapper
using `--resume-invocation-sha256`. The wrapper retains an immutable captured
invocation, checks that digest at entry, and compares the complete capture again
after admission. A changed companion, root, output, trial or journal cannot
select another attempt. Completion uses only the captured original journal and
release, even if control is replaced, disabled or removed after launch. The
companion Ninja pin remains path/hash; preparation retains the wrapper's full
path/hash/device/inode/size/mtime identity, which is verified without rewriting
the receipt. Resume fixtures obtain preparation receipts from actual wrapper
main with real Ninja, replacing only production admission with a private fixture.

A finite legacy-preparation path supports the reviewed protocol-4 wrapper with
source hash `f3dce1112a33dff0a8c4c8185faec2ed529da0c34a72d5af9a11f6832a0a160b`.
It does not modify or normalize old receipts. If `admission.ninja_tool` is absent,
the companion must additionally supply `legacy_preparation` with exactly:

- `packet`: a path/hash pin to the authenticated original preparation packet;
- `current_ninja_tool`: a full, separately observed current identity using the
  six fields required by the modern wrapper.

The independently issued approval must also bind `legacy_preparation_sha256`
to `legacy_binding_hash(companion['legacy_preparation'])`. This is a binding to
existing historical evidence and current observations; the adapter issues no
approval, and source/runtime re-review is required before use. The verifier
checks the packet's pinned original receipt, plan, supported legacy wrapper and
tool manifest; fixed wrapper/plan Ninja paths; root/head, graph and input
bindings; recorded executable content hash/size/mode; and current full identity.
Historical inode/mtime are **not** inferred. Modern receipts retain their exact
full-identity requirement and reject legacy overrides. Without the captured
verified resume contract, ordinary wrapper and acceptance-audit behavior stays
strict. This path supplies a separate current identity only to the existing
prepared-receipt comparison and never rewrites the original admission object.
If any provenance binding is missing, retain the hold and use a future ordinary
fresh preparation for the trial; do not repeat completed preparation merely to
make the trial eligible or block the owner's ordinary released work.
