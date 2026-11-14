# Zako renderer consolidation

This completes the remaining renderer work from fork PR #303 on main
`284fafb0b1df1955a8d03f8035f3484d99e76fc7`. Its DHCP, network, BML,
character-load and storage recoveries have already landed through separate PRs.
Those current implementations are retained, including the unsigned DHCP clock
subtraction and the genuine two-argument chunk-material helper.

## Unit and source contracts

Combine the adjacent `TBoss4ZakoDraw` class methods at `0x8030A884..0x8030A96C`
with its constructor, renderer, queue producer and clearer through `0x8030AD38`.
The combined unit owns the class vtable at `0x804E7650..0x804E7668` and the
existing two draw buffers at `0x80541E58..0x80542D60`. Definitions follow native
address order. This is a validated source consolidation, not proof of the
historical source filename. The separate clear wrapper and resource initializer
remain in their existing units.

The renderer uses the shared `Boss4ZakoDrawBuffer` representation recovered on
main. Each entry owns a `Vec` at offset zero. Copy-initializing a per-iteration
`Vec` preserves the native integer word transfers and subsequent Y replacement;
assignment to an outer local would introduce the out-of-line assignment helper.
The matrix translation call consumes the vector immediately and retains no
pointer. The shared matrix interface accepts its first float's address.

The tint is an actual `NJS_ARGB`, whose order is alpha, red, green, blue. The
falloff changes alpha. The previous temporary's misleading RGBA names and cast
are removed without changing channel stores. Shared matrix, distance, chunk-draw
and material headers replace the local incompatible declarations. The material
setup retains main's three saved state values, their original save/restore order,
and its two-input call. No dummy arguments or hand-built ABI declarations are
introduced.

`get_bml_model` already returns `NJS_OBJECT *`; use that pointer directly for
drawing and its `child->ang[1]` field for the rotation update. Native child and
angle offsets are `0x2C` and `0x18`. The model local is declared before the buffer
locals: reversing this declaration order changes their native register allocation.
No unused locals or compiler controls are added for that allocation.

The camera position comes from `TCameraCtrl::position` at `0x178`. One explicit
conversion remains at the shared camera slot's existing byte-pointer boundary;
this change does not retype that global across the repository. The viewport
storage is declared as the camera owner's actual `u32[18]`, and word 12 identifies
the existing rectangle at byte offset `0x30`. Its address stays live across
`is_split_screen`. This removes the dead pointer temporaries and fabricated
integer-to-pointer values without inventing a shared camera-storage structure.
Existing null, capacity and signed-angle behavior is preserved.

The class header no longer redeclares its virtual `render` as static. The obsolete
fragment header is removed. Texture-slot and viewport characterization tests
follow the consolidated source.

## Matching constraints and validation

The shadow function retains only its existing scoped `fp_contract on` for the
native fused falloff/alpha arithmetic. The inline pragmas and trailing function
redeclaration are removed; no per-unit compiler override is added.

The unchanged-main baseline and combined candidate are built from their own
source and split configurations with the pinned native tools and local original
inputs. Native builds use the repository's serialized exclusive mode. The
shared-mode graph checker does not yet accept the newer `mwcc_post` rule; these
runs do not claim shared-mode admission.

The combined renderer is **9/9 exact**, with **1,204 code bytes and 3,872 data
bytes** matched and linked from source. `check_pr.py` checks address-based
no-loss, source providers and generated retention. Consolidation reduces the
linked-unit count by one; it changes no matched or linked byte count. The scanner
adds three retention entries for references now internal to the combined unit,
removing none. The rebuilt DOL retains original SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

This does not claim to repair unrelated legacy network allocator, queue-adjacency,
private-creator or callback boundaries still present on main. No changes to those
interfaces are carried by the remaining PR diff.
