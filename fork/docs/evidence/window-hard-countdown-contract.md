# Typed Hard countdown predicate

This follows `fa34d393a8b1bb29fd6c104385fd6056e86f0e3e` and changes only the
receiver/field contract of the historical C export at 80247D50, not its original
name or member ownership.

A census of the configured original split objects finds one relocation-backed
call to 80247D50: the Chat predicate loads its receiver from Chat +0x28. Original
Chat construction allocates 0x74 bytes, calls the Hard constructor and stores the
result at that field. This establishes the observed receiver as
TWindowKeyBoardHard, without assuming arbitrary computed calls or universal
runtime lifetime.

The original helper loads receiver +0x68 and computes signed positivity. Hard's
constructor and reset write zero there; Japanese input writes 60. Its task reads
the value as signed and decrements only when positive; rendering also explicitly
tests signed positivity. The field is therefore represented as s32 rather than
u32, preserving width and layout. The positive guard keeps subtraction within
range. The helper now takes TWindowKeyBoardHard* and directly reads m_68 instead
of a byte-offset signed-pointer cast. The caller uses the proven receiver type.
The existing C export and non-member definition remain; no table or lifetime
ownership is inferred. Other raw aliases are not declared universally recovered.

## Validation

The first bounded candidate passes the capacity-gated full native build with
original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All 3,626 active
compiled objects are raw-byte-identical to the preceding validated head,
including complete payloads, symbol metadata, tables and relocations. The DOL,
Ninja graph and generated configuration are also unchanged. No compiler controls,
provider changes, byte coverage gains or layout changes are introduced.

Aggregate no-loss and retention checks pass against the prior head, and the
existing freshly built pinned-main 0a9ac7d62fa6add8c85591af57f296309755b894
comparison retains its qualified fourteen window tails. There is no new padding
claim or validation claim against a later main. Independent source review accepts
the bounded receiver and signed-field evidence. All 347 tool tests and portable
behavior/sanitizer targets pass. A source-extracted host helper also agrees with
the previous signed-offset expression on twelve boundary cases, including both
signed extremes, -1, zero, 1 and the observed countdown value 60, under ASan/UBSan.
That stub test checks expression behavior, not native object provenance or lifetime.

Hard's 28-byte original table provider, trailing word, original placement,
destruction and borrowed-composer lifetime holds remain unchanged. This does not
resolve other mixed Chat/Hard/composer interfaces or change draft readiness.
