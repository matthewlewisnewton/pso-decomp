# Window constructor chain: native probe and integration blocker

This investigation starts from GuildWarning PR #268's validated source commit
`74966a46e24be7e560e55fa7b91d8b808e53e9a8`. The probe is retained only in
the local diagnostic branch `sol61/pr268-constructors`, checkpoint
`4ebd08190c7a1e2459fa228764953c2dd3f814f0`. Its implementation is not activated
by this evidence update, and has not passed a full linked build.

## Correcting the earlier constructor explanation

The earlier failure came from leaving the actual base construction outside the
C++ initializer chain. A real `TWindowMessage` constructor implicitly initialized
the declared base with a default constructor, then its body called the legacy
construction helper. That introduces an extra base call and virtual-table store.

The function currently named `TWindowDD::construct_base` at `0x802466E0`
calls `TObject` with the parent selected for its client and initializes the
`TWindowBase` image. In the probe it is a real `TWindowBase` constructor.
`construct_with_parent` at `0x80244448` becomes the real `TWindowAddition`
constructor, with `TWindowBase(descriptor, client, position)` in its initializer.
The message constructor initializes `TWindowAddition` directly. The corresponding
destructors use the ordinary compiler-generated base destruction and vptr stores.

This eliminates the extra calls without a hand-written virtual table, assembly,
new pragma, or compiler override. It also corrects the earlier inference that
the `destroy_window` name in an original slot rules out a C++ destructor:
that name is project-assigned, and the native compiler's destructor has the same
instructions and occupies the same slot.

## Native results

The pinned GC/2.6 compiler and existing unit flags were used under the shared
build lock. Complete unrelocated `.text` section bytes compare as follows:

| Unit | Original bytes | Probe bytes | Identical |
| --- | ---: | ---: | --- |
| `TWindowDD_8024662C` | 288 | 288 | yes |
| `TWindowAddition` | 284 | 284 | yes |
| `TWindowMessage` | 2,748 | 2,748 | yes |
| `text_80244238` | 440 | 440 | yes |

The corresponding `.text` relocation comparisons also agree: 13, 19, 89,
and 9 records respectively. Constructor/destructor/vtable/helper names are
normalized by the explicit old-to-new project-symbol mapping. Compiler-local
constant labels are compared by their unchanged `.rodata` / `.sdata2` section
offsets; relocation offsets, types and addends must still agree.

These units include the six constructor/destructor bodies and the addition
initializer. The initializer's descriptor argument is retained even though its
current body does not use it: the original constructor passes it, and removing
the argument changes the call sequence. The argument's type and project symbol
change together in the probe.

The compiler also emits a 24-byte virtual table for each class. The data bytes
and four slot relocations match the original tables at `0x804CE018`,
`0x804CDFE8`, and `0x804D0730`, respectively. The two project-assigned
`destroy_window*` names are normalized to their corresponding real destructor
names for that comparison. There is no hand-written table in the probe.

The raw-byte and normalized-relocation comparisons are not a claim that the
current PR contains these constructors or that their renamed references already link. A full
integration must retarget the constructor/destructor symbols and every reference,
assign the emitted data to its owning units, regenerate split objects and retention
metadata, and rerun address coverage, linked-unit and original-DOL checks.

## Caller-width blocker

The exact chain uses a short client parameter on the base and addition
constructors. `TWindowMessage` receives a word and narrows it at the observed
base-constructor call. Existing `fn_80268384` and `fn_802683F4` pass the client
as a word into the legacy helper, then narrow it for a later virtual call.

An explicit test calling the real short constructor from those two functions
changes instruction selection and scheduling; their whole unit is 224 bytes
instead of the original 228, and is no longer exact. Keeping the earlier
word-valued local declaration under a new mangled name would hide that disagreement,
so that is not an accepted integration.

Two coordinated wider-carrier probes also failed to retain the complete match.
With `s32` or native `int` constructor client carriers, the base constructor's
instruction order changes and the message unit grows from 2,748 to 2,752 bytes.
The base setup helper itself still compiles identically with a word parameter,
but that does not repair the caller/constructor chain. These measurements do not
establish that no source-correct solution exists.

## Remaining lifetime and qualification work

`TWindowAddition` still has an incomplete field declaration: its methods access
the prefix through `0x6C`, while the current class declaration ends at `0x60`
and descendants carry their own copies of that storage. The probe preserves
that existing arrangement rather than asserting complete field ownership.
Recovering the shared prefix must preserve every descendant's size, offsets,
field interpretation, and matching code.

Adding real constructors also affects default-constructor availability in other
descendants. The probe retains empty default constructors only to allow those
unchanged declarations; their native use and compatibility are not validated by
this small compilation. No claim of complete object lifetime recovery follows
from the six matching bodies.

The standing draft hold remains. The next integration needs a consistent client
contract across the word-valued callers and short-valued constructor chain,
complete field/default-construction qualification, compiler-emitted table ownership,
and full independent validation of the final linked head.
