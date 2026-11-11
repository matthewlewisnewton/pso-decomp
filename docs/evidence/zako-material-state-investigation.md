# Zako material-state investigation

## Pinned scope

This follow-up investigates the still-held shadow-renderer and typed-unit fold
from #303. The research baseline is fork main
`345ac133c05f9f825331c770d42b2c537a958d71`; later main changes are excluded.
The constructor/resource work from #440 and BML contract from #436 are already
in this baseline. They are not new matching or linking gains here. The original
#303 branch and all earlier review/build checkpoints remain intact.

## Executable contract, not a historical prototype

The original function at `0x803DED78` has a twelve-byte extent. It stores incoming
r3 to `chunk_polygon_flags_and_mask`, stores incoming r4 to
`chunk_polygon_flags_or_mask`, and returns. It reads no other argument register,
performs no stack argument access and has no further calls. That establishes its
observable two-input behavior. It does not recover the number or types of unused
parameters in an unknown historical source declaration, nor prove a historical
return type. A wider or variadic declaration is not justified by that uncertainty.

The active original split inventory contains 62 references to this entry, all
text-section `R_PPC_REL24` relocations with addend zero. They agree with 62 direct
calls in the original DOL, from 52 containing functions. There are no resolved
references or direct branches into the other instructions of its extent, and no
aligned data-section words pointing into it. These are static reference checks,
not a claim that arbitrary runtime-generated addresses can be ruled out.

Some current decompiled callers use incompatible four/six-argument declarations
or casts. Those are reconstruction artifacts to investigate, not independent
source evidence for a wider API. The shared two-input declaration agrees with
the callee's observed effect; it is not historical source material either.

## The actual Zako state transaction

At the shadow renderer `0x8030A9B0`, the original image performs these global
accesses before the call at `0x8030AA00`:

| Address | Access |
| --- | --- |
| `8030A9C8` | Read the entry render flags into r8. |
| `8030A9D0` | Read the entry AND mask into r7. |
| `8030A9DC` | Read the override constant `lbl_805DF138`. |
| `8030A9E0` | Read the entry OR mask into r6. |
| `8030A9E8` | Store entry flags with bit `0x10` cleared. |
| `8030A9F0` | Save the entry flags to the shared backup global. |
| `8030A9F4` | Save the entry AND mask to its shared backup. |
| `8030A9F8` | Save the entry OR mask to its shared backup. |
| `8030A9FC` | Store the cleared flags ORed with the override constant. |

The helper receives `0xFF00` and `0x900` in r3/r4. The remaining values in r5-r8
are the cleared flags and snapshots used by the already-completed stores. Their
presence at the call boundary is not proof of four more source parameters. The
callee does not consume them, and they have no subsequent use as these values
in the caller.

After drawing, the original reloads the three `saved_*` globals. An implementation
must preserve that reload behavior, not restore from entry locals or an RAII/stack
snapshot: intervening renderer calls can replace the shared saved state.

## Nearby Falz comparison

The initializer `TObjPlayer__sub_80052390` has the same five-store state
transaction: clear the render flag, save the three entry words, then apply a
render override. Its original reads precede its first state write. Its existing
source calls the helper with two inputs and matches the original.

This is corroboration of the state transaction, not proof of identical source
text. Its render-override constant is `0x8829` rather than Zako's `0x82C`, and
its helper OR mask is `0x800` rather than `0x900`. Its floating input, later color
work and register allocation also differ. Reusing the whole initializer would
add unrelated color effects and a call, so it is not a replacement for Zako's
setup. The existing `save_model_draw_state` helpers operate on a different
`color_draw_saved_*` bank and likewise are not interchangeable with this state.

## One bounded source hypothesis

The original three pre-mutation reads and their real backup-store uses support
one reconstruction hypothesis: make the entry AND/OR values explicit locals
alongside the existing entry-flags local, consume them only in the existing
backup stores, and call the helper directly with two inputs. Independent
read-only evidence review supported testing this hypothesis, without claiming
it was the historical source or predicting a register match.

The test preserves every global store and its order, the later restore-from-
globals behavior, all other source, original unit boundaries and every existing
compiler control. No fake arguments, casts, dummy uses, volatile accesses,
pragmas, flag changes, or assembly are added. The previous failed call-only
probe is not repeated. Further variants require materially new source evidence.

## Negative result and remaining hold

The one snapshot experiment failed the native DOL checksum. The 408-byte shadow
function remained the same size and scored 99.65686%, but seven instructions
changed register fields. The original uses r7 for the entry AND mask, r6 for the
entry OR mask and r5 for the cleared flags. The experiment uses r6, r5 and r7,
respectively. The affected original addresses are `8030A9D0`, `8030A9D8`,
`8030A9E0`, `8030A9E8`, `8030A9EC`, `8030A9F4` and `8030A9F8`.

The linked DOL differs in exactly seven bytes at those seven instruction words;
its header, length and all other bytes are unchanged. Its SHA-1 is
`15bbceacbe4f01483c5b4add58770a997f918273`, versus the authenticated original
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

A complete comparison of all 3,632 source objects and 4,944 active original split
objects found only the shadow-renderer source object changed. Its relocation
records, symbol records, section order, size, alignment, flags and BSS bytes are
unchanged. There were no symbol mappings or other normalizations. The ordered
3,610 source and 1,334 fallback providers are unchanged. Retention still passes
with 18,650 entries. None of these observations overrides the failed native
checksum or makes a register-only mismatch acceptable.

The fresh report and `check_pr.py --no-build` correctly reject the experiment:
matched functions fall from 27,444 to 27,443 and matched code from 4,241,872 to
4,241,464 bytes. Matched data remains 1,477,679 bytes. The linked-unit check also
fails for `pso/boss/TBoss4ZakoDraw_8030A96C.cpp`. No matching or linking gains are
claimed. The baseline itself passed native DOL, no-loss, linked-unit and retention
checks before the experiment.

The actual experimental setup and restore statements were extracted into a
small host fixture. Both optimized and ASan/UBSan builds passed 10,000
deterministic 32-bit state cases, including replacement of the shared backups
before restoration. This characterizes those state statements only. It is not
an end-to-end renderer, native ABI, pointer-layout, GPU or floating-point proof.

The explicit snapshots are a plausible representation of the observed state
transaction, but they did not recover the original register allocation under
the unchanged compiler profile. The observed two-input callee does not justify
inventing unused parameters to recover those assignments. No source-supported
matching replacement has been established, and the typed fold remains held,
including its proposed compiler-profile migration. No further source variants
were attempted after this result.

This evidence-only branch changes no production source, headers, compiler
controls, symbols, splits or link metadata. The failed experiment is preserved
separately and is not proposed for merging. A future implementation attempt
needs materially new evidence about genuine source structure or ownership,
followed by native, whole-object, no-loss and independent source review. Matching
bytes alone would still not establish an honest API.

## Reproduction and provenance

The baseline was built independently through the repository's shared native
build-capacity gate with locally pinned tools and authenticated original inputs.
The baseline and experiment used identical tool binaries and 659 original input
files. The experiment changed only the existing shadow renderer's entry-mask
snapshots and replaced its incompatible cast with the direct two-input call;
the rest of that file and all other source inputs stayed unchanged.

Useful reproduction points are the original helper `0x803DED78`, the Zako
shadow renderer `0x8030A9B0`, and the neighboring initializer `0x80052390`.
Enumerate the generated config's active original-object inventory, rather than
all `.o` files on disk. Scan original text direct and conditional branches, and
compare helper relocations across that inventory. Inspect the real loads,
backup stores and post-draw restore loads in both callers before proposing a
source change. Keep disassemblies, originals, compiler binaries and private
build receipts local.

The original-free `tools/probe_zako_material_snapshot.py` accepts an explicit
trusted local experimental source via `--source`; it never rewrites production
code or silently removes the incompatible call. Run it once normally and again
with `--sanitize`. Each run emits the source and extracted-statement hashes,
host compiler version, flags and scope. UBSan errors are configured to be fatal,
so a diagnostic cannot be reported as a passing run merely because the process
continued. The source hash for the preserved failed
experiment is recorded in the JSON summary. This script intentionally cannot
characterize the unchanged production file's incompatible cast as a direct call.

The adjacent JSON summary records the immutable baseline, tested source/patch
hashes and public-safe result facts. Full native artifacts were retained locally
for independent review, not included in this branch. The investigation follows
Matthew Newton's #303 work and its recorded Cursor co-authorship; it does not
claim authorship of those earlier constructor, resource or typed-renderer changes.
