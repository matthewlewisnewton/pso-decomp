# Snapshot window and opaque capture storage

This follows PR #268 checkpoint `da05632f73d56ee8343a237cfac5dfbc518177cf`.
SnapshotCaptureAbi.h separates the 0x40-byte capture allocation from the existing
0x64-byte Base-derived window. The capture storage remains opaque and uses its
unchanged historical C exports. This checkpoint does not activate either native
capture lifetime or native window construction/destruction/table ownership.

## Distinct receiver domains

The load_player_motion_data producer allocates 0x40 bytes using operator new,
then calls the existing initializer and load sequence. Capture operations use
words at 0/4, an owned buffer at 8, its size at 0xC, status at 0x14/0x18,
filename bytes 0x1C..0x3B and a dispatch pointer at 0x3C. The initializer installs
the existing dispatch table at 804DD098 and resets the existing fields. Reset
does not clear offset 0x10; no additional store or heap-zero assumption is added.
The deleting function writes that same dispatch pointer and conditionally
releases the allocation. Native dynamic type and destructor ABI remain held.

OptionCtrl separately allocates a 0x64-byte window. It initializes Base, uses
Base's vptr at 0x18, and owns its byte flags at 0x60. It is the sole original
caller of the window constructor. The two images do not share a complete class
or object-lifetime claim merely because previous exports used the same name.

Capture operations and getters no longer use the window's TObject/Base fields
as aliases for capture storage. Their declarations, definitions and all known
source consumers use the opaque receiver. Historical mangled export names are
preserved as C names, with no replacement wrapper, new symbol or inferred native
capture class. Word-valued address/status returns are preserved: get_size is used
as an address by Lobby despite its historical name. Static capture setup helpers
also move out of the window declaration under their existing exports.

The filename truncation rule, mode values, allocation/failure paths and cleanup
order are unchanged. Global cleanup still calls buffer cleanup/reset before
dispatch deletion and clears the global afterward. Its existing null-order
behavior is preserved. ARAM transfer, aligned allocation and startup call order
are likewise unchanged. Wider archive, transfer, dispatch and word-address
interfaces remain qualified; this is not a portable capture implementation.

## Validation and retained ownership

All six whole compiled texts match captured da05 source and main originals,
including every resolved relocation: capture owner1364, transfer116, window/
shared helpers868, Lobby1312, Player startup200 and keyboard startup1520 bytes.
Allocated-section inventories, data/constants and relocations are unchanged.
Each source object is selected once in actual executable inputs, with its
original counterpart absent. No new compiler table or data section is emitted.

The original capture table16 remains selected once in auto_07_804DD098_data.
The window descriptor20 at 804DDEB4 and table24 at 804DDEC8 remain in the complete
original auto_07_804DDBF0_data provider, selected once. All provider bytes and
resolved data targets match main. No range, split, padding, retention entry or
compiler control changes. The raw0x40 producer/dispatch protocol and window's
160-byte constructor, 88-byte deleting wrapper, 176-byte render and 152-byte task
are unchanged at this checkpoint.

The shared-gate full build retains DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against da05 passes with
zero metric delta: 27,395 exact functions, 3,589 exact linked units and 3,653
source-bearing units. Retention is clean at 17,852 entries and port inventory
passes unchanged. Fork main remains `4e784e247d991f1fb25766fc80923242a9ba469a`.

Raw Base/Addition calls remain 24 across 13 units. All previous holds, including
WS_Word's 916-byte rendering body and native constructor difference, remain.
PR stays draft. Native window recovery requires its own complete code/data/link
proof; this boundary alone does not establish it.
