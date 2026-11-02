# Box-drop directive recovery

The prerequisite is fork `main` at
`909d120b21f7e875e71a5c1d0d3a7799a08078e9`. The unit
`pso/unk/text_8011A780.cpp` owns `.text` `8011A780..8011B010`
(2,192 bytes) and no data. Its missing 312-byte function is
`handle_box_drop_directive` at `8011A868..8011A9A0`.

The original routine reads the source index at request +6, consumes its claim
in `quest_object_entries`, converts the four specialization parameters, and
optionally regenerates an item while preserving its category/group bytes. It
assigns the generated item ID, validates/encodes the item, and sends a 6x5F floor
item packet. The -1 source and 0xFFFF claim sentinels, and invalid generated items,
take the original exit paths. The existing 6xA2 dispatcher is its sole direct caller and discards
the result; the recovered helper has a typed request and a void return.

The GC instructions use signed source and room halfwords and a sign-extended
area byte. Their shared wire declarations now reflect that behavior. The source
census finds these request types used only by this unit. The bounded set-data
view retains its unknown prefix: `unpack_from_item` at `8010C744` reads only
+0x30/+0x34/+0x38. The handler fills those fields and the +0x2C regeneration
control. Compile-time guards verify their offsets and the relevant wire layouts.

Packet initialization (`8011B130`), sending (`8011B0C8`), and item generation
(`8011C454`) retain their existing legacy symbols at typed C ABI boundaries.
Their bodies establish packet/item arguments; they do not establish TLobby or
TObjPlayer instance ownership. In particular, generation receives area in r3
and the item pointer in r4. The packet's trailing four bytes remain opaque.
The wire packet contains FloorItem, whose native constructor would introduce
an additional call; the local delivery record instead owns a trivial TItemData
payload and uses the existing explicit packet initializer.

Under pinned GC 2.6 settings, the item/parameter/delivery declaration order
reproduces the original stack layout. Scoped immutable category/group backups
reproduce the original saved registers. Moving the helper ahead of the destroy
handler preserves original function order. No assembly, physical register
bindings, fabricated uses, assets, or copied data are introduced.

Validation on the prerequisite and final linked candidate used fresh split
objects/configuration and pinned dtk v1.8.4, objdiff v3.6.1, GC 2.6 and Wibo.
The unchanged prerequisite passed its full build and retention check. The final
`ninja -j2 -d keeprsp` build and subsequent
`python3 tools/check_pr.py --no-build` passed. All 15 functions and the complete
unit layout match. Relative to the prerequisite: matched functions +1, matched
code +312 bytes, linked code +2,192 bytes, linked units +1, data unchanged;
no exact-function, code/data-address-coverage or linked-range losses.
An additional overall no-loss comparison against the original starting baseline
`61f58f1e22a7203459abc6e1f19a82a5b9c4089c` also passed.

The actual `psov3.elf.rsp` contains
`build/GPOE8P/src/pso/unk/text_8011A780.o` exactly once and contains no original
split object for this unit. The sole linkset addition is this unit. Its generated
retention additions are `handle_box_drop_directive`,
`drop_item_from_source__6TLobbyFsisiff`, and
`process_enemy_drop_request__FScsisiff`; there are no retention removals.
All 3,552 linked units pass `link_units.py check`, and all 16,637 retention
entries pass `force-active --check`.

`cmp` confirms the final DOL equals the original; both have SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.
The validation receipt fingerprints the 5,013 ordered linker inputs, tools,
original DOL, split/symbol/configuration metadata, report, baseline and source.
Selected SHA-256 fingerprints are recorded below for reproducibility.


- `build/tools/dtk`: `7c86b1994401bde0cad1d308e6c04cccb65e85453ccc5062ac12baab3b03d320`

- `build/tools/objdiff-cli`: `72688707d5a7f30daebf5a4f65f74c6dab17ee6e09a230a187e327900345eecf`

- `build/tools/wibo`: `7fdf620b151744296b9bb93318d8c4009d3d3e98e23718a6eda9fbec4cefbb2a`

- `build/compilers/GC/2.6/mwcceppc.exe`: `316e2a98236c23f3fc902243b157eaebf8ef2ad6edb88cfd632a15b6676fa9a8`

- `build/compilers/GC/2.6/mwldeppc.exe`: `37818faa6e510d3ab92629f0a6c4334cfca0ca943fba0a0d61626f7f9379077d`

- `build/GPOE8P/config.json`: `0f27c7c0ac5c6ded4ec803c0666b29ba28ec7f4e3a26932bb075c9c9275af509`

- `build/GPOE8P/psov3.elf.rsp`: `ae4cdf60c58a527fdcb2dd901cafe2d5cd03a704d5c4441dc527dc9fa4634e76`

- `build/GPOE8P/obj/pso/unk/text_8011A780.o`: `e6b3a0840bed8efbcdad036f5f8ef4f21cdd72de84c2453bc6fe99fc06dc0930`

- `build/GPOE8P/src/pso/unk/text_8011A780.o`: `e85e87256263959045ffddce3f9acbb6d63c79f805d2206de83bad3a2a9f2ec8`
