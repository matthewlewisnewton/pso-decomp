# Native loader restore retention

## Proposed exception; approval pending

This candidate reconstructs and links the 20-byte range at
`0x8042E9FC..0x8042EA10` using the existing disc-generated assembly mechanism
and a scoped `force_active` pragma. It preserves the local symbol, full extent,
split boundaries, LaunchDol provider and initializer. No object patch, invented
reference, symbol widening or coverage-rule change is used.

The requested exception covers both the generated assembly and its retention
pragma. It also requires an explicit porting decision: this fragment has no
independent C calling convention, so a portable build omits it rather than
compiling a fabricated empty C function. This does **not** satisfy the normal
scalar-fallback rule. Approval of that specific departure is pending; the
candidate must not be represented as approved or ready to merge on build
evidence alone.

## Controlled link experiment

The experiment used stock GC/2.6 (compiler SHA-256
`316e2a98236c23f3fc902243b157eaebf8ef2ad6edb88cfd632a15b6676fa9a8`)
and the existing native linker. A shared workspace read lock protected the
donor build at `ce59a0aabbdf4375f3d53bbac4017750741add12`; the standard
exclusive build gate serialized each experiment. The 4,948 ordered linker
inputs and linker script were hashed before and after each run. The only
candidate substitution was the original restore object. This controlled relink
is diagnostic evidence, not a substitute for the candidate's own native build.

| Input for the restore | Result |
|---|---|
| Original split object | Original DOL SHA-1 reproduced |
| Exact generated local assembly, without retention | Restore discarded; initializer moved from `0x8042EA10` to `0x8042E9FC`; 53,341 DOL bytes differed |
| Same source with scoped `force_active` | Restore retained as local at `0x8042E9FC`, size 20; initializer retained at `0x8042EA10`; original DOL SHA-1 reproduced |

Both compiled objects have identical 20-byte `.text`, alignment four, symbol
definitions and no code relocations. Their **complete object files differ in
one byte only**: the retained object's CodeWarrior comment metadata sets the
keep flag. The original DTK split object also carries that keep flag. No
metadata byte was patched; the stock compiler emitted it from the supported
pragma. Objdiff scores the retained restore 100%.

The original executable SHA-1 is
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. The unretained control produced
`630c642233374326fe9ae8c0fb3a46f522468519` instead. This isolates retention
as the cause in this experiment. It reproduces the scale of upstream #174's
reported layout cascade without changing section alignment. It does not claim
to have replayed every historical upstream configuration.

The global retention generator intentionally excludes local symbols. A scoped
source pragma retains this local fragment without exporting it or changing the
generated global `force_active` list. The source uses `push`/`pop` so retention
does not affect any other definition.

## Meaning of completion and porting

With this exception, the restore and initializer span can be fully matched and
linked: 20 bytes of generated assembly plus 196 bytes of existing C++. The
restore is **not newly recovered C++**, and its inferred standalone function
identity is not authenticated by this result. The existing 312-byte LaunchDol
assembly provider is unchanged. Original transfer semantics, possible indirect
entries and source ownership remain investigation topics.

A port should implement the executable-launch operation through its platform
backend. It must not call this frame fragment as a C function, synthesize a
dummy return, or substitute an ordinary returning function-pointer call for
the native nonlinking handoff. A host that executes original PPC code must
preserve the original machine-state semantics instead of using this source
omission as an emulation implementation. No functional host loader is claimed.

Melee and Sunshine keep a handoff followed by frame restoration in their SDK
`Run` assembly routines; Wind Waker uses a frameless assembly handoff helper.
These are precedents for a platform boundary, not proof of PSO ownership:
[Melee](https://github.com/doldecomp/melee/blob/2f8eab8ebd7a2d25541e125abfa246defe1bacec/libs/dolphin/src/dolphin/os/OSReboot.c),
[Sunshine](https://github.com/doldecomp/sms/blob/4b2fd238058bf70822ca226e17f02879a7a46eb4/libs/dolphin/src/os/OSReboot.c),
[Wind Waker](https://github.com/zeldaret/tww/blob/d217e2b5e1c1514e6f3f640835f83f01dd67aa72/libs/dolphin/src/os/OSReboot.c).
No source from those implementations is copied into this candidate.

## Validation

On 2026-11-11 UTC, the unchanged published PR head
`ce59a0aabbdf4375f3d53bbac4017750741add12` and this candidate each passed a native
build in a separate checkout from the diagnostic donor, through the unchanged
exclusive capacity gate at `-j2`. Both reproduce the original DOL SHA-1 above.
The unchanged PR head also passes `check_pr.py` against checked main
`f8a71fae8a52f0bde1b956af4519061fe306cb30`.

- The candidate passes `check_pr.py` against both that main report and the
  freshly built previous PR head. It has 3,601 exact linked units.
- The unchanged strict raw-report guard reports zero lost ranges in all nine
  coverage/exact/link categories against both baselines. Function addresses,
  full extents and total code/data/function counts are unchanged.
- All 3,600 common source-linked complete objects are byte-identical to the
  freshly built previous PR head. The 4,948 ordered linker inputs differ only
  by replacing the restore's original split object with its compiled object.
- The restore has 20 exact code bytes, alignment four, a local function symbol
  of size 20 and no code relocations. The initializer remains exact at its
  original address. The global retention check reports no additions/removals.
- The 36 original-free loader-audit controls pass. The exception inventory and
  changed-line whitespace checks pass.

Relative to the previous PR head this adds 20 matched/source-linked code bytes,
one matched function and one linked unit. Relative to checked main, the whole
PR adds 20 matched bytes, 216 source-linked bytes and two linked units. Neither
comparison turns generated assembly into recovered C++.

The first local baseline was the older published `8803e1ec5c` head. Comparing
it with the newer main report correctly failed because main had meanwhile
linked the action-palette unit. That mismatched-base comparison was discarded;
the checkout was fast-forwarded to the current published PR head and rebuilt
before applying the restore change. No failure was waived or guard changed.

The historical [ownership and behavior investigation](launch-dol-stranded-epilogue.md)
remains applicable within its stated limits; retention does not resolve those
questions. This is implementation validation, not independent review, policy
approval or merge admission.
