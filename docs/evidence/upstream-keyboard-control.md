# Keyboard control recovery

Original recovery baseline: `224eb99838471c243b20c305eddac75e7ff76c8f` (fork main after #370).
PR rebased and revalidated on `387621104107ed1ff8c650bf2f50ef00c6859ba4` after DHCP #371 merged.
Reference: upstream #208, `ae797d392bb93d5bf7164341870f78f864da23b0`,
`src/pso/ui/keyboard/TKeyBoardControl.cpp`.

Recover glyph/icon/tab drawing at `0x802616BC` (1,820 bytes) and key-frame
drawing at `0x8026227C` (856 bytes). Preserve the fork's typed constructor and
destructor, navigation tables, symbols and class interfaces. Fold the adjacent
already-linked 428-byte constructor/destructor unit into `TKeyBoardControl`.
The resulting text range is `0x80260450..0x802627D8` (9,096 bytes).

## Ownership and interfaces

The native compiler float pool extends through `0x805DD0D8`, including the
previously unowned 16 bytes at `0x805DD0C8`. Float literals reproduce the whole
96-byte pool. The localization tool found no outside consumers for its 24
named globals before marking them local. The normal objdiff report uses
`functionRelocDiffs=data_value`; compiler pool names need not match split labels.
All object sections and relocations match. The ten UV pairs occupy 80 bytes;
the compiler emits the following four alignment bytes. No binary assets or
manual padding data were added.

The frame helper's declared argument order now agrees with its calls (four
floats before color and index). Typed receiver arguments remove three existing
function-pointer casts. The cursor's signed indices and fade value at +0x68
match the byte/float accesses; the child remains at +0x6C. Layout pages retain
mutable `u16 **`, as in upstream: a const-qualified view changed native moves
and zero-extension instructions. These bounded views do not establish the full
original class layout.

The glyph-drawing helper now consistently returns `u8` and takes a `u16` glyph,
`void *` quad and `s32` color across all declarations/callers and its definition.
Its cached-glyph lookup now passes the actual glyph instead of calling through
a no-argument cast. Caller local widths and related declarations were corrected
to keep every previously exact function exact.

One neighboring legacy interface remains unresolved: the mapper declaration in
`TWindowSubStatusDisp_8024FBA8.cpp` retains its existing `s32` input, although the
shared definition takes `u16`. Its return is corrected to `u16`. Narrow-input
probes changed zero-extension/character-combination instructions; no claim is
made that the font interfaces are globally consistent. A port should use one
shared narrow interface with explicit character decoding. Other pre-existing
opaque render interfaces, provisional receiver views and constructor layout
assumptions also remain native recovery debt.

## Compiler constraints and port guidance

Retain existing scoped `pool_data off` for glyph drawing: the fork owns the
geometry tables in this object, while upstream references them externally.
Remove the existing `opt_loop_invariants off`; the original hoists the first
row multiplication. Existing `fp_contract` settings remain, including the folded
tail's reset. Ports can drop optimizer steering and should preserve required
floating-point contraction semantics. No new assembly, intrinsic, hardware
access, pragma or per-unit compiler override. The inventory decreases from
5,772 pragmas in 876 files to 5,771 in 875. Section 7's historical upstream-import
scope is unchanged; the additional native debt is recorded in section 4.

## Validation

Current-main build, baseline and retention passed before editing. Full build
and `tools/check_pr.py` pass with original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. No exact function, code/data address,
linked range or padding is lost. The linked object's 9,096 code bytes and 996
data bytes are exact. Retention adds 29 names and removes none.

| Measure | Before | After | Gain |
|---|---:|---:|---:|
| Exact functions | 27,386 | 27,388 | 2 |
| Exact code bytes | 4,189,632 | 4,192,308 | 2,676 |
| Exact data bytes | 1,470,159 | 1,470,255 | 96 |
| Linked code bytes | 3,673,564 | 3,682,232 | 8,668 |
| Linked data bytes | 1,179,243 | 1,180,239 | 996 |
| Linked units | 3,586 | 3,586 | 0 |

The unit count stays level because this replaces the already-linked tail.
Total units drop from 4,973 to 4,971: that tail and the automatic 16-byte pool
are absorbed. Total code, data and function coverage are unchanged.
Actual ordered linker inputs: 3,586 source objects and 1,385 fallbacks;
SHA-256 `c1b52987f12e82ae1ecade1dcb944430518706e20e0e98ce5290a7d27d8044b7`.

The table and input digest above describe the original recovery baseline.
Revalidation against main `387621104` retains the same incremental gains and
all DHCP coverage. The rebase preserves both exception-register sections;
recovered source is unchanged. Full build, original DOL hash, address/link
no-loss and inventory checks pass on the combined base, as does comparison
against the original `224eb9983` baseline.
