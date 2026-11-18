# ChatSymbol and PartsSet native constructor chain

This follows PR #268 checkpoint
`c08c3577c09ec38f2a141534d5de375e077c10f2`. The existing Base-derived ChatSymbol
and ChatSymbol-derived PartsSet images now have native constructors. ChatSymbol's
empty descendant destructor uses automatic Base cleanup; PartsSet retains its
existing native destructor and opaque heading release before ChatSymbol cleanup.
No new raw constructor/destructor binding or compiler control is introduced.

## Four ChatSymbol constructor paths

Original-reference inspection finds four calls to the 116-byte ChatSymbol
constructor, all at its existing address 80248700:

- PartsSet now uses a native ChatSymbol initializer with its existing position
  and extent record.
- SubSymbolChat's 0x68-byte producer uses ordinary new.
- The separate selection controller's 0x68-byte child producer in text_80248840
  also uses ordinary new.
- The protected original 1,044-byte helper retains its original provider and
  bytes. Its relative relocation at 0x3DC remains REL24/addend zero to 80248700
  after the catalog rename. No source rewrite or compatibility wrapper is added.

ChatSymbol's constructor accepts position/size pointers, forwards client four
and the observed descriptor to Base, assigns its name and forwards the size
through the existing two-float helper boundary before clearing words at 0x60/0x64.
The helper's wider historical declarations and complete ownership remain
qualified; this does not claim that all surrounding UI APIs are portable.

The sole PartsSet producer allocates exactly 0x98 bytes. Its native constructor
retains the established s16 selection argument, two borrowed word-global
pointers, initialization order, depth adjustment and final selection update.
Fields at 0x7C/0x80 are borrowed pointers; neither is released by this recovery.
Fields at 0x8C/0x90/0x94 remain the observed floats. The existing 36-byte heading allocation,
message-34 initializer and release protocol remain opaque: no complete child
class or new delete policy is inferred. The entire 236-byte constructor matches.

## Virtual ownership and distinct controller receiver

ChatSymbol task and render references are its own table slots. The renderer
is now defined as the native member; direct members preserve original register
allocation. Its wider draw helper/implicit-register boundaries remain qualified.
The existing PartsSet render/task/destructor table is retained byte-for-byte.

The historical destroy__17TWindowChatSymbolFs export is not ChatSymbol cleanup.
The separate TObject-derived TUnk_804CE7D0 controller owns a menu pointer at 0x1C
and a ChatSymbol child at 0x20. Its cleanup now expresses that actual receiver
under the same legacy C export; the false ChatSymbol member declaration is
removed. The wrapper's operations and bytes are unchanged. Controller native
construction/destruction, historical export naming and wider child interfaces
remain separate holds. No new controller table or native lifetime is claimed.

## Data providers and original word preservation

The observed descriptor has extent 203/78, order 50100, the existing sprite-entry
reference and flags 11. It uses WindowLayoutDescriptor's provisional schema.
The 20-byte descriptor and compiler-owned 24-byte table form the natural 44-byte source
range [804CE7A0,804CE7CC), with five exact relocation targets. The table has
four function slots; the former 28-byte catalog extent is corrected to 24.

The trailing zero word at 804CE7CC remains an explicitly catalogued original
word, not a fifth function or source padding. The previously selected 1280-byte
original provider is refined into 1208 original prefix bytes, 44 source bytes and
28 original suffix bytes. That suffix consists of the zero word and the separate
controller table at 804CE7D0. Both original pieces are actual linker inputs once;
no gap is introduced. Fresh-main range comparisons use the appropriate slices
of its larger original provider, retaining unrelated earlier PR refinements.

## Validation and remaining work

Six complete text sections and every text relocation target match main originals:
ChatSymbol lifetime/controller 408, ChatSymbol task 64, PartsSet 2440, sprite/render
owner 1900, SubSymbolChat producers 8084 and selection producer 256 bytes. All six
compiled objects are selected once. Descriptor/table 44 and the existing PartsSet
table 24 have exact raw data and relocation targets. The protected helper and all
other protected prefixes/remainders remain unchanged and selected as before.

The serialized full build reproduces DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against c08c3577c0 passes
with 44 additional matched/linked data bytes and no function/code/unit/coverage
or linked-address loss. Totals remain 27,395 exact functions and 3,588 exact linked
units. Retention is clean at 17,840 names; port inventory passes unchanged.
This removes the ChatSymbol raw Base pair, leaving 32 calls across 16 source units
and the four shared Base/Addition ABI bindings. No source-link completion of the
protected helper, Parts or the separate controller is claimed. PR remains draft.

Before this family, one bounded WS_ScrollBar native probe was checked. Its
constructor grew from 112 to 116 bytes because the emitted compiler table no
longer shared the original data-base addressing. Keeping the original position/
descriptor array representations as a control produced the same difference.
The probe is not activated; its original matching source and providers remain.
No manual vptr, invented virtual slot or scheduling control was introduced.

Integrated main remains `12cc95ca737a3a8757c17f45df06a9af4821d872`. Combined PR
deltas versus its separately validated source baseline are +600 matched code,
+1220 linked code, +1400 matched data and +1356 linked data bytes. The fourteen
qualified four-byte alignment gaps are unchanged. Parts' constant blocker,
ChoiceSetting/global ownership, callback signatures and all wider interface
holds remain in force.
