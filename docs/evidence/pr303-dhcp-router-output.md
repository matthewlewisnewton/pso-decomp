# DHCP router output and the opaque first argument

Distinct audit at source head `32256785a7f5eb1f1b530344ac20e9101373102e`
and main `e65f11ce6ec99c006909422f81da1c0a46ac062e` (2026-11-11).
This covers accessor `0x8042489C`, size 0x74, independently of the completed
lease accessor and previously rejected allocator, adjacency and reset probes.

## Native argument and result evidence

The source producer declares `s32(void *, void *)`; the sole source caller
declares a short result. Across all 5,021 original split objects there is exactly
one reference: zero-addend `R_PPC_REL24`, misc object offset 0x490. Native call
`0x8014667C` supplies the opaque argument in r3 and the output address in r4,
then executes `extsh.` on the result. The destination is a declared `s32` word
at `0x805D56E4`; its recovered global name is not proof of an original typedef.

The original option table maps getter ID 6 to kind 1, size four, data word
`0x805D7B3C`. The parser supplies this entry from the first word of DHCP option
3. The accessor forwards the existing r4 to the getter after overwriting r3
with ID 6. Although the first argument is unread, its position keeps the output
in r4. Preserve it as opaque; do not infer an interface ID, class receiver or
singleton context.

The producer returns only literal zero and -1. In states 3/4/5 it returns zero
even when the getter fails and diagnostic 0x10 is set. Other states set diagnostic
2 and return -1. The generic getter copies storage when the output is nonnull
even if the option is absent; a null output remains permitted. Add no early
exit, clearing, retry, ownership or bounds behavior. The observed references
do not prove absence of unseen or dynamically constructed callers.

## Type controls and a negative argument-position control

Before production edits, run eight isolated controls varying return width and
output typing independently, with the first argument retained. Producer controls
keep the actual body, volatile globals, getter declaration and active pragmas;
caller controls copy the full actual TU and replace only this local prototype.
Use actual `types.h` and resolved compiler profiles: GC/1.2.5n `-O4,p -inline off`
for the producer, GC/2.6 `-O4,s -inline off -sdata2 4` for the caller. Execution
uses the existing workspace and legacy-exclusive capacity locks; production
source and recorded native outputs remain unchanged.

All four producer variants (`s32`/`s16` return crossed with `void *`/`s32 *`
output) reproduce the complete 116-byte native function and relocation tuples,
with an eight-byte frame. Both short-return caller variants reproduce its full
308-byte native function and relocations, with a 32-byte frame. The word-return
variants keep relocations but replace the status check with a full-word compare.

A ninth, explicitly negative producer control omits the first argument. It grows
from 116 to 120 bytes and changes code and relocation placement because the
output now arrives in r3. This is not a candidate or a cleanup: it demonstrates
why the unused argument position cannot simply be removed. No negative-control
source is applied to production. Independent review confirms all nine controls
and their source/object/tool hashes. None proves a unique historical typedef.

## Bounded shared declaration

Share one C-linkage `s16 TLobby__sub_8042489C(void *, s32 *)` in the DHCP header.
Change only the producer signature and remove the caller's local opaque
declaration. Retain the unnamed opaque first parameter, the entire body, every
caller argument, output/global representation, diagnostic ordering and getter
behavior. No export, configuration or other API changes.

The first candidate passes native validation. Producer, caller and parser
complete objects are raw byte-identical, including metadata and relocations;
all 3,665 compiled-object hashes are unchanged without normalization. Original
DOL SHA-1 remains `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental
metrics, coverage and retention have zero drift. Full sealed-main comparison
passes with 3,599 exact linked units, 18,428 retention entries without drift,
existing +88 data bytes and no new function/code gain or loss. Ordered providers
remain 3,599 source inputs and 1,347 original fallbacks. All fourteen existing
host tests pass. Independent source/native review passes; exact-head review
gates publication.

Only this accessor's declaration mismatch is repaired. Its opaque argument,
adjacent hostname/init interfaces, locked allocation, adjacency, private
creator/raw callback/reset ABI and metadata holds remain. The validated lease
declaration is preserved. Keep draft.
