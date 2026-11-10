# Hard keyboard construction

This follows PR #268 checkpoint `b996f557e59c6b968b154c57b4ef2012fb290da7`.
The existing 0x74-byte Base-derived hardware keyboard now has a genuine native
constructor and two ordinary-new producer paths. Destruction, compiler-table
integration and the wider mixed keyboard/card interfaces remain qualified.

## Constructor and borrowed composer

Original object references identify exactly two calls to the old constructor:
TKeyBoardControl's constructor and TWindowChat's constructor. Each first allocates
and initializes a 0xB8-byte TWindowKeyBoardBase composer, then passes that pointer
to the hardware keyboard. There is no descendant constructor reference.

The constructor's parameter is therefore a borrowed TWindowKeyBoardBase pointer.
It initializes Base with the existing descriptor, client 4 and layout position
0xB9, assigns the name, clears state at 0x60/0x64/0x68, stores the composer at
0x70 and sets 0x6C to seven. The existing release_keyboard helper then forwards
that composer to the historical reset helper. Despite its name, this path resets
composer state at 0xB4; it does not release its allocation. The original deleting
wrapper only performs Base cleanup. The encompassing Control/Chat owns and closes
its composer separately. No composer ownership is transferred to Hard.

Both producers now use ordinary new with the same composer pointer. The native
constructor is 136 bytes; its complete 440-byte owner and the 3284/3808-byte
producer units retain identical instructions and resolved relocation targets.
The source keeps field 0x70's existing word representation: unrelated mixed
receiver views are not silently normalized by this bounded constructor recovery.

## Original table and wider interfaces remain held

The 88-byte C deleting wrapper is unchanged. Its table is the selected original
28-byte provider at 804CFDC4, including its four original function relocations
and trailing zero word. It is not naturally aligned for an independently emitted
compiler table, and no table extraction, extra virtual slot, artificial padding
or alignment override is attempted. The preceding 756-byte descriptor/controller
data owner is unchanged. The new native constructor references the existing table
without emitting a competing definition.

release_keyboard, task/render and other helpers still contain historical mixed
Hard/Control/composer/card receiver views. The no-argument key query and card-ID
casts are not claimed as recovered interfaces. The reset helper's original calls
and all state updates remain exact. Soft keyboard lifetime/class separation,
deleting cleanup and native table ownership are separate work.

## Validation

The shared-gate full build reproduces DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against b996 passes with
zero metric delta: 27,395 exact functions, 3,589 exact linked units and 3,653
source-bearing units. Retention is clean at 17,852 entries and the port inventory
passes unchanged. Integrated fork main remains
`4e784e247d991f1fb25766fc80923242a9ba469a`.

All three whole source text sections match original objects and captured b996
source objects. All resolved text/data relocation targets and allocated
data/constants match the prior source. Each source object is selected once in
the actual executable inputs and its original text counterpart is absent. The
constructor owner emits only its unchanged four-byte name-pointer sdata, with no
new data/table. Original table bytes and all four resolved slot targets agree;
the provider remains selected once. No split, range, gap, retention name or
compiler control changes. Composer, ComCard and protected-original provenance
checks pass, including the original 1044-byte setup helper.

The combined PR deltas versus fresh main remain +600 matched code, +1220 linked
code, +1472 matched data and +1428 linked data bytes. There are now 24 raw
Base/Addition calls across 13 source units and the same four shared bindings.
All earlier ownership/interface/constant/destruction holds remain; PR stays draft.
