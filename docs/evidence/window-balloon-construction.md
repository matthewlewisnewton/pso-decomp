# Balloon construction checkpoint and retained destruction hold

This follows PR #268 checkpoint
`c57714e1d8d247edb5d52ed4a6c6a9995f3e4cdf`. The existing 0x98-byte
TUnk_804CF0B8 image now has a genuine word-valued constructor that initializes
Addition. Its sole source producer uses ordinary new. The task owner is corrected
to that same balloon class. Destruction, initializer ABI and full source linkage
remain held; this is a construction checkpoint.

## Supported construction and actual owners

Original-reference inspection finds one constructor producer, allocating 0x98,
and no subclass. The constructor receives player, text and client words plus a
float. It narrows the client explicitly for Addition and passes the existing
zero-position helper result. Compiler-generated derived-vptr initialization
reproduces the original 132-byte constructor. The producer's complete 2356-byte
text also matches. No raw replacement constructor binding is added.

The task table slot and its own switch destinations support TUnk_804CF0B8 as
the owner of the 456-byte task. The old TWindowFukidasi task declaration is
removed. Existing surrounding Fukidasi helper views remain qualified, including
approach and position synchronization; this change does not assign all mixed
receiver helpers to the balloon class.

Name storage at 0x78 is allocated by operator new[] in the existing initializer.
The retained deleting wrapper conditionally clears/releases slot 0x73, releases
and clears name storage, then invokes the existing Addition cleanup binding.
Its complete 144-byte text and operation order are unchanged. The actual class
virtual destructor remains declared as before; a native destructor definition
is not activated in this checkpoint.

## Initializer width boundary remains explicit

The constructor retains the pre-existing word-valued C view of the initializer
at 80251DF0. That view disagrees with the recovered method's short player/client
formals. Original instructions forward the full words to this entry; the
initializer stores halfwords and sends the player word to the color helper.
The color callee itself masks the low 16 bits. This establishes observed transport,
not a resolved portable C++ interface or canonical helper signature.

A coordinated word-typed initializer/color probe did not reproduce the original
functions. The 216-byte initializer changed register-selection words; word color
variants using a local or use-site u16 conversion produced 112 rather than 116
bytes. These variants are not activated. The actual short initializer/color
declarations and bodies are restored, byte-exact at 216/116 bytes. No wrapper,
function-pointer cast or new ABI binding is introduced. The native constructor
crosses the same unresolved legacy initializer view as its predecessor; that
interface hold remains explicit.

## Native destruction/table integration blocker

A native destructor probe reproduced all 144 text bytes, but claiming its
compiler-owned 24-byte table caused the build generator to report:

`Cyclic dependency encountered while resolving link order: pso/misc/TWindowFukidasi.cpp -> pso/misc/TWindowFukidasi_80252AE4.cpp`

The earlier held Fukidasi text unit owns 80 exact data bytes at 804CF0D0: the
render and task jump tables, 40 each. The later destructor text would emit the
class table before those jump tables at 804CF0B8. The resulting text/data order
constraints conflict. Dropping the 80 matched bytes, losing the existing source
linked destructor, or inventing a table/control is not justified. Native
construction does not require activating that destruction probe.

The original class table therefore remains selected as part of the unchanged
84-byte original provider at 804CF07C. Its 24-byte range at 804CF0B8 is canonically
named __vt__13TUnk_804CF0B8, with the same four slots and resolved targets.
This identifies the original table; it is not a compiler-owned table claim.
Neither constructor nor deleting-wrapper object emits competing data. No data
claim, new alignment gap or synthetic padding is introduced.

## Validation and remaining work

The serialized full build retains DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against c57714e1d8 passes
with zero metric delta: 27,395 exact functions and 3,588 exact linked units,
no code/data/function/coverage or linked-address loss. Retention remains clean
at 17,846 and ports pass unchanged.

Constructor 132, deleting wrapper 144 and producer 2356 complete text sections
and all resolved text relocation targets match main originals. All three source
objects are actual linker inputs once. The held Fukidasi object's 9912 compiled
text bytes, constants and resolved relocation targets are unchanged from fresh
main compiled source. Its executable provider remains the original 10712-byte
text and 80 jump-table bytes, each unchanged with matching resolved targets.
The456-byte task, 216-byte initializer and 116-byte color function are additionally
compared individually against original bytes. The original 84-byte provider and
all four table relocations are unchanged and selected once.

The raw constructor boundary is removed; deleting cleanup remains. There are
now 29 Base/Addition calls across 14 source units, with the same four shared
bindings. All protected ranges, including the original 1,044-byte helper, retain
their providers and prior validation. ScrollBar, Parts, callback, ChoiceSetting,
task-global and wider ownership/interface holds remain. PR stays draft.

Integrated main is `12cc95ca737a3a8757c17f45df06a9af4821d872`. Combined deltas
remain +600 matched code, +1220 linked code, +1448 matched data and +1404 linked
data bytes. The fourteen qualified four-byte alignment gaps are unchanged.
