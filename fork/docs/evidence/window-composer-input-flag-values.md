# Composer input-flag value helpers

This follows PR #268 checkpoint `3cf7cae4e4bc02d93a9e3d5a763793c6cddc9bf8`.
Four historical Control C helpers now have their evidenced composer owner,
`TWindowKeyBoardBase`. Their nonvirtual void methods operate on the existing
word at 0xB4; they add no class layout or virtual-table claim.

## Original calls and actual receivers

All-section inspection of original objects finds only direct zero-addend text
calls, with no address-taking or other-section references:

| Address | Native method | Body bytes | Original calls |
| --- | --- | ---: | ---: |
| 8025CBC0 | set_input_flags_212 | 12 | 3 |
| 8025CBCC | set_input_flags_112 | 56 | 3 |
| 8025CC04 | set_input_flags_92 | 56 | 3 |
| 8025CC3C | set_input_flags_12 | 12 | 5 |

The suffixes name hexadecimal values: 0x212, 0x112, 0x92 and 0x12. No extra
language, LED, cancellation or ownership meaning is assigned to those values.
The twelve outer calls pass the composer through Control's field 0x20, Hard's
field 0x70 or Soft's borrowed field 0x6C. Control creates the native 0xB8 composer;
Hard's established constructor retains that argument at 0x70. The two original
Soft-constructor paths pass the same composer, which its initializer stores at
0x6C. The four legacy Soft outer helpers forward that borrowed pointer.

The remaining two calls are the compound helpers' calls to the 0x12 setter on
the same receiver. The 0x112 helper preserves that call followed by reloading and
ORing word 0xB4 with 0x100; the 0x92 helper preserves the corresponding OR with
0x80. These are not collapsed into single literal assignments. The simple
helpers still assign 0x212 and 0x12. All caller null guards and subsequent calls
are retained, including Hard's separate fn_8025FF8C path, which also forwards
the proven composer at field 0x70.

## Exact object and executable validation

The first ordinary native-owner probe preserves all five complete source texts
and their original resolved text relocation targets:

| Unit | Text bytes |
| --- | ---: |
| TKeyBoardControl_8025CB70 | 416 |
| TKeyBoardControl_80131C58 | 3284 |
| TKeyBoardControl_8025EC04 | 5000 |
| TKeyBoardControl | 9096 |
| text_8025FF8C | 104 |

All allocated section headers, flags, sizes, alignment, data/constants and
resolved text/data relocations remain unchanged from 3cf7. Each source object
remains selected exactly once. The four recovered bodies independently match
original at 12, 56, 56 and 12 bytes. No source selection, split, data/table
provider, original remainder, compiler control or ABI binding changes.

The capacity-gated full build retains DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. `check_pr` passes against published
3cf7 with four catalog renames and zero metric or coverage delta, and against
separately built main `4bec40d6cca74a85e91c848ea2d9f25425a313ad` with no
regression. Retention is clean at 17,895 and port inventory passes. Totals remain
27,406 exact functions, 3,587 exact linked units and 3,641 source-bearing units.

## Remaining qualifications

The adjacent historical Chat reset and language-derived flag helper are
unchanged; their wider interfaces and holder records are not recovered here.
The legacy Soft outer helper names remain qualified, and no complete Soft
class, borrowed-pointer ownership or native child lifetime is claimed.
The native composer constructor/destructor and its existing table are unchanged.

Raw Base/Addition calls remain 22 across twelve units and four bindings. All
record, capacity, CMName, lifetime, constant and ownership holds persist. The
nameplate reconstruction still differs in 139 words and its original provider
remains selected. The PR stays draft; this family claims source fidelity, with
no coverage or activation gain.
