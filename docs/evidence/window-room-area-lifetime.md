# Native Room and Area window lifetimes

This follows PR #268 checkpoint
`6346f39876e0e723e9182be14674f0e05cc7e5f3`, including current main
`224eb99838471c243b20c305eddac75e7ff76c8f`.

## Evidenced inheritance and object layout

The original Room constructor calls Base with its existing descriptor,
client 4 and position lookup 0xAF. Its destructor only installs the Room
table, cleans up Base and conditionally releases the object. Room is 0x64:
the 0x60-byte Base image plus the float tab parameter at 0x60. The old flat
class-name, vptr and float views now use actual inheritance and Base fields
m_30, m_38 and m_48. The allocator adapter is removed; ordinary new inherits
TObject's allocator through Base.

Area's original constructor calls Room with a null title, then replaces the
name, copies the position pair at 0x40/0x44 and sets the inherited tab float.
Its destructor calls Room cleanup. Area therefore derives from Room and adds
no fields. Both sizes are checked as 0x64, with Room's own float checked at
0x60. No additional descendant or own child release was found.

Room and Area use genuine constructor initializers and native empty
destructors with automatic cleanup. No default Base lifetime is introduced.
The old raw Area constructor and raw destructor declarations leave the
headers. Room's previously flat native constructor keeps its actual char*
argument and emitted symbol; it now initializes its real Base subobject.

## Virtual render and actual allocation producers

Both original tables point at 8026D594 in the render slot. The formerly
named draw_status is Room's render override, inherited by Area. Declaration,
definition and catalog now agree with render__11TWindowRoomFv. Native tasks
retain their existing behavior. Rendering explicitly forwards the receiver
through the shared draw-context entry point and uses pointer-valued window
and entry-container parameters for the drawing boundary.

Original reference inspection found two Room-constructor calls: lobby
allocation and Area base construction. The Area constructor has two calls
from the two area-window allocation producers. All are direct zero-addend
REL24 references; no additional address-taken constructor reference was found.

The lobby producer now uses new TWindowRoom and assigns it directly to the
existing TObject* global. Actual inheritance makes that conversion valid.
The two area producers use new TWindowArea and the shared inherited title-entry
method, retaining their established word-valued result boundary. Unrelated
text-entry and title-widget protocols are not silently reassigned.

The lobby's existing queue-destruction ABI entry is used with the actual
TObject* receiver. Calling the inline member at that site after introducing
the native derived type emitted an additional unowned 16-byte inline body,
although the original function bytes stayed exact. Reusing the already
present explicit entry avoids that duplicate without a wrapper, new symbol,
pragma or change to the original call bytes.

## Qualified position-copy boundary

Area uses the existing exported two-float copy entry with explicit
`(f32 *destination, const void *source)` arguments. Its implementation copies
only offsets 0 and 4, without mutating source, and an existing non-window
caller already uses that declaration. Area supplies the real Base float pair
at 0x40/0x44. No complete PartsSet object is asserted at that address.

The historical mangled export remains unchanged and its class attribution
remains unresolved. This is reuse of an evidenced legacy transport boundary,
not recovery of a canonical portable free-function owner. The lookup is
explicitly evaluated before that copy; this expresses the observed dataflow
and reproduces the complete 104-byte constructor. The direct nested expression
emits 100 bytes, while retaining a destination across the lookup emits 108.
No dummy operation or compiler control is added to force an instruction.

The shared entry setter is also used by Addition and stays qualified under
its existing interface. The Room/Area recovery does not assign its complete
widget ownership or claim a SubStatusDisp object is present in either window.

## Compiler tables and original descriptor

Each native key function emits a four-function table of exactly 24 bytes:

| Owner | Source claim |
| --- | --- |
| Room | [804D08F0,804D0908) |
| Area | [804CE000,804CE018) |

Both data sections naturally align to eight and equal the original
unrelocated data. The full link validates their targets. Area inherits
Room's render slot; no new virtual slot or manual table is introduced.
No descriptor recovery, alignment override or padding definition is needed.

Room's 20-byte descriptor and preceding opaque entry table remain original
input. The selected auto_07_804D08B8_data.o has 56 bytes, equal to the original
prefix of main's 80-byte object. It is selected exactly once and its resolved
DOL bytes are unchanged. Descriptor ownership is not fabricated.

## Verification and remaining holds

All four changed source units have identical complete original/compiled
unrelocated text and are actual source link inputs exactly once:

| Unit | Bytes |
| --- | ---: |
| TWindowRoom | 652 |
| TWindowArea | 248 |
| TPlyJoinLobbyEntry | 23,052 |
| text_8024450C | 368 |

The full DOL reproduces SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr passes:
all 27,387 exact functions and 3,588 exact linked units retained, no code,
function, data or coverage loss, and 48 additional matched/linked data bytes.
Retention is clean at 17,741 names (+5, no removals); the porting inventory
passes. Relative to fresh main 224eb9983, the combined PR retains +600
matched code, +1,220 linked code and +824 matched/linked data bytes. The ten
previously qualified alignment gaps are unchanged.

One more Base construction/cleanup pair leaves the raw interface. It now
has 56 calls across 29 source units: 24 Base pairs and four Addition pairs.
The four Base/Addition bindings remain. Other raw-storage lifetime families
still need their own owner and interface evidence.

The original Help data suffix of 204 bytes, including its trailing zero word,
and the separate 1,044-byte text remainder [8026E1D4,8026E5E8) remain original
inputs exactly once, with unchanged unrelocated and resolved bytes.
ChoiceSetting's unknown 0x7C producer, task-global word 805D5D94, Snapshot
window/capture separation and broader interface/ownership holds remain.
The PR stays draft and must not be marked ready or merged.
