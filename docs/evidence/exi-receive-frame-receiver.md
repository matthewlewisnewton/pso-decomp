# Receive frame receiver at 80426A70

This receiver-only correction starts from main
`37eab6e173f40350e82c51ea91babc0507fe0317`, including the complete EXI
Ethernet driver recovery in #458. It does not recover the allocation callback's
full type or change the dispatcher's pointer-encoded length boundary.

## Registration and dataflow

At 80426190, the transport registers allocation target 80426AAC and delivery
target 80426A70 through 8042B58C. The registrar stores the two address words in
805D7C4C and 805D7C50. Initialization clears those slots; delivery does not clear
them. The callbacks persist across receives, without an exclusive lifetime claim.

The recovered receive routine 80429648 invokes the allocation slot with packet
type, descriptor length, and flags, then stores the returned buffer in 805D7C74.
The known allocation target ignores the third input word. Its mode 1 path obtains
a receive buffer from 804089A8; mode 2 uses unlocked allocator 80425640. Both paths
yield a buffer pointer or null. This does not establish a third source parameter,
canonical callback width, or a contract for locked allocator 8042558C.

DMA completion at 80429AC8 copies data into that buffer and calls the delivery
slot with the buffer in r3 and the zero-extended descriptor length in r4. The
60-byte target at 80426A70 tests incoming r3 for null and forwards it as the frame
to 80425DC8, alongside the channel table and unchanged second argument. It never
accesses a TLobby member.

The authenticated original-object reference inventory finds one direct registrar
call, one address-forming HA/LO pair for each registered target, and one direct
call from the delivery wrapper to the dispatcher. All named slot references are
the initialization, registration, and receive/completion accesses above. This is
a bounded static inventory, not a proof excluding arbitrary dynamic aliases or
external consumers.

## Bounded correction

Declare `void forward_to_channel(void *frame, void *b)` in the shared network
header and remove the fictitious class member and duplicate alias declaration.
Keep the null guard, table local, dispatch call, second opaque argument, and
existing registration cast. Map the export spelling at the same address and
size; preserve provider selection and native behavior, including bugs.

The allocation callback arity and widths, downstream length representation,
raw-IP callbacks, private creator/reset ABI, locked allocator, and queue
adjacency remain unresolved. No bounds check, callback adapter, compiler control,
or source-provider change is introduced.

## Validation

The focused host test extracts the actual wrapper body and checks null handling
and unchanged forwarding of the frame and opaque argument to a synthetic
dispatcher. It is not an ingress, EXI, ABI, or packet-lifetime test. Native
validation uses independently built baseline and candidate worktrees, authenticated
local tools and inputs, and the shared serialized build gate:

- Both DOLs reproduce original SHA-1
  `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- Of 3,633 compiled objects, 3,632 are byte-identical. The complete transport
  object agrees after the single export-name mapping, including code, data,
  section and symbol order, and relocations. Of 4,946 original split objects,
  4,945 are byte-identical; the same transport object agrees after the name
  mapping and regenerated string-table ordering.
- The full 60-byte wrapper resolves to the original instructions. Its unit
  remains source-linked with all 26 functions exact; passing the DOL does not
  depend on selecting an original fallback for this source change.
- Ordered providers remain 3,619 source objects and 1,327 fallbacks. Strict
  address-based no-loss checks pass; all 18,847 retention entries have zero
  drift. Matched functions/code/data remain 27,470 / 4,266,936 bytes /
  1,479,980 bytes. This is an interface correction, with no coverage gain.
- All 346 tool tests, including the two wrapper characterization tests, pass.
  The five portable behavior and sanitizer targets, Python syntax, generated
  exception inventory, and whitespace checks also pass.

No split range, provider choice, native compiler option, or existing hold changes.
