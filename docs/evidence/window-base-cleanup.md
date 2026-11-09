# Native Deposit, LockOn, and Photon cleanup

This follows validated PR #268 checkpoint
`8093f079751c5045078d2be2350286582d027dde` on main
`9924ce113b5e6dff309a5ae94065265d3066fb24`.

Deposit, LockOn, and SubMagPhoton already have native constructors and ordinary
construction factories. Their destructors now perform automatic Base cleanup
instead of calling its native ABI entry point from a C-named destroyer.
Their render functions are native members as well. Photon uses main's actual
`TWindowDD::draw_default_entry((s32)this)` declaration; the old no-argument C
view concealed the incoming object argument. Constructor contracts and main's
existing field types remain unchanged.

All three compiler tables have four function slots: destructor, task, render,
and inherited TObject shadow rendering. Their complete instruction sections
reproduce the original bytes: Deposit 600, LockOn 3,556, and Photon 2,716.

| Class | Actual compiler table | Separate zero tail |
| --- | --- | --- |
| Deposit | `[804CEB84,804CEB9C)` | `[804CEB9C,804CEBA0)` |
| LockOn | `[804D02C8,804D02E0)` | none |
| SubMagPhoton | `[804D17FC,804D1814)` | `[804D1814,804D1818)` |

The former 28-byte Deposit/Photon catalog entries included a zero word;
they are corrected to 24 bytes. There is no fifth function slot. The owning
units now supply the compiler-generated tables, with no hand-written table.

## Descriptor ownership and emitted layout

An initial isolated-table link failed the DOL hash: the emitted data sections
require eight-byte alignment, while Deposit and Photon tables start four bytes
off that boundary. Their adjacent descriptors have independently supported
ownership, not merely a convenient length. Each is referenced only by its
own constructor, and Base's initializer consumes the observed 20-byte record:
two extent floats, an order float, an entry-table pointer, and flags.

`WindowLayoutDescriptor` records that provisional field schema with size and
offset assertions. It parallels the existing soft-keyboard descriptor pattern;
it does not claim an original C++ type name or change the keyboard type.
The existing entry tables at `0x804CEB30` and `0x804D1720` remain opaque
external data. Only the two scalar/pointer descriptors become source-owned.

The compiler naturally emits each descriptor followed by its table at offset
`0x14`: 44 bytes total, with eight-byte section alignment. The supported claims
are `[804CEB70,804CEB9C)` and `[804D17E8,804D1814)`. No alignment override,
manual padding, wrapper table, pragma, or compiler change is introduced. This
establishes source/data ownership for linkage, not original translation units.

Deposit's four-byte tail is reproduced by linker alignment before the already
source-owned DuelResult data at `0x804CEBA0`. Photon's tail remains in original
input `auto_07_804D1814_data.o`, with no relocation in that word. Both tails
are zero in the original and rebuilt image. The report excludes Deposit's
four padding bytes from data coverage; the existing zero-padding check accepts
this, and the complete DOL remains identical.

## Qualification and remaining boundary

The full build reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. `check_pr.py` against the
published checkpoint passes with zero function, meaningful data, code,
non-padding address-coverage, or linked-unit regressions. The only coverage
removal is the verified four-byte zero tail described above. Exact functions remain 27,369;
all 3,575 linked units remain exact. Three tables and two descriptors add
112 matched/linked data bytes. Retention is clean at 17,601 entries, and the
refreshed porting inventory passes.

Against fresh main, the PR retains one additional exact function, 600 matched
code bytes, 728 linked code bytes, and now 284 matched/linked data bytes.
Three more destroyer units no longer need the Base destructor ABI binding.
The shared interface still has five constructor and three destructor entry
declarations for other raw-storage callers. Log's constructor mismatch and the
remaining Base/Addition/MenuIconLine lifetime work keep the draft hold active.
