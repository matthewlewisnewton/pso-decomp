# Upstream matching and data synchronization

This integration imports upstream PRs [#168](https://github.com/zeroz41/pso-decomp/pull/168)
(`6e52d78f641e37d66845e683e8fc3f013f3c2662`) and
[#167](https://github.com/zeroz41/pso-decomp/pull/167)
(`137150833b5374a820782c6a3a3f510c11386c86`). The initial fork baseline is
`02a5ab8e2069f78c806438bcb6d1eb2a003976a1`; the final fork-main prerequisite is
`61f58f1e22a7203459abc6e1f19a82a5b9c4089c`.
The intermediate `9496b2b18974cb8b97cc0e64612574581eff6cd6` baseline also passed.
During publication, main incorporated the player hit-vector and status-gauge
recoveries. Their newer typed source and compiler profiles supersede the
corresponding upstream spellings and are preserved in the final integration.

## Reconciliation with the fork

Canadin, Merill Lia and Morfos already have complete exact native implementations
and source linkage on the fork. Their implementations are retained. New Gyaranzo
and model-capture storage uses the fork's existing typed declarations. The container,
ray and jukebox folds retain the fork's texture-list, BML lifetime, sound and receiver
contracts. Photon-blast attachment tables use `PhotonAttachmentSpec`; opening-effect
records use the existing 28-byte record type instead of an unrelated byte-array view.

The Slime implementation already defines its original constant pool explicitly.
The additional upstream constants extend that pool without replacing native bodies.
`SlimeTailPose` owns one attachment vector and four shadow vectors: 60 bytes at
`0x80501010..0x8050104C`. The original copy copies 12 bytes followed by six 8-byte
iterations. The node callback writes the attachment and four 12-byte shadows, ending
at offset `0x3C`. All six original split-object references to `lbl_80501010` are in
this unit with addend zero. The old 64-byte symbol extent included the four bytes
before the next object at `0x80501050`; these remain unclaimed alignment, rather
than becoming an invented field in the native pose. The last four bytes after the
extended constant pool, `0x805DA75C..0x805DA760`, are also alignment, not a constant.

## Keyboard prerequisite

Upstream #168 enables `TWindowKeyBoardSoft.cpp`, but the fork had deliberately held
back its `0x8025DBDC` implementation in PR #210. This integration reuses the owner's
frozen correction `e43c8acd43e0934f724d75041c2e3c1aa6756a84` (source SHA-256
`262ccdfd60810b964a0a8b5b3b08874a0e12dff368baedcf89500dbde37c7947`). The existing
GC/2.6 profile matches its 564-byte code and physical relocations.

The backwards scan uses a 32-bit unsigned address cursor. In the full-prefix case
it may subtract below the buffer numerically, but never constructs or dereferences
a pointer there; it restores a valid element address before reading. A target-size
assertion records the Gekko dependency. Both caller translation units declare the
routine `void`; all callers discard the result. Independent source review checked
this bounded repair, and the full unit must remain exact and link from source.

## Scope of previously held changes

Git ancestry does not establish that every earlier upstream implementation is on
the fork. PR #210 deliberately published progress maintenance while retaining
unresolved recovery history. Apart from the keyboard prerequisite above, its held
selection initializer, inventory/list recovery, Needle constructor and node banks,
Quest/window fold and coverage work, and `0x80104FCC` jump-table claim remain with
their existing owners. This synchronization does not declare those recoveries
complete or incorporate their unqualified source/profile changes.

## Validation

The initial fork baseline was built from source and reproduced original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Its retention check uses freshly generated
split objects from that exact baseline and passes with 16,265 entries and no drift.
The integrated retention list is regenerated from the integrated split inventory;
its changes are not a normalization of a broken baseline.

Validation compares original-address function, data and linked coverage, including
unit folds, rather than relying on unit counts. Actual retained linker response
inputs must equal the Ninja link edge, and every complete unit must select its
compiled source object. Alignment gaps are reported separately and the final DOL
must retain the original hash. No source-linked unit may be demoted to fallback.


## Source-review repairs and deferred buffer ownership

The Boss7 laser setup now keeps a live parameter record. Its source constant
initializes the `params` member of `Boss7AttackParameterCopy`; trivial whole-union
assignment copies that active member's representation, then the caller updates
its real float member. The representation array is never selected or accessed.
This preserves the original word-copy behavior without an unrelated aggregate
lvalue, a pointer before the object, or float writes into character-array storage.
The existing setup routine synchronously borrows that live record. Targeted
GC/2.6 comparisons preserve every function and allocated non-code byte, symbol,
alignment and relocation in the complete behavior object; this is separate from
final current-main build and linkage acceptance.

The newly introduced `QuestDownloadBuffers.cpp` and its single BSS split/link
claim are deferred. They defined ten shared objects as raw arrays despite
incompatible consumer record types and unresolved original source ownership.
Removing only this added unit restores original fallback storage for
`0x8058DE08..0x80596668`; it does not remove a source-linked unit from the PR base.
The ten symbol entries remain unchanged from the base and have no generated
force-active entries in this candidate. No other source recovery, symbol extent,
retention entry, compiler profile or existing linked unit is removed by this
bounded deferral. A fresh generated graph, retention check, original DOL and
address-based no-loss comparison remain final merge checks.

Task8 owns completion and integration of this deferred scope, coordinated with
existing Quest owner task48. The exact incoming definitions and evidence remain
preserved at `6afe7bb34e2862958ba8d3f048a723c02524a4c8` and in local frozen branch
`codex/fork-pr226-quest-buffers-frozen`. Task48's public #203 supplies the real
`QuestDownloadSlot[80]` contract; its private input-entry correction concerns a
different table and is not a fix for all ten buffers. Task48 is retaining the
shared record, text-buffer phase/lifetime and original-owner investigation. No
parallel whole-buffer recovery is introduced here.

The former candidate's reported 34,912-byte exact/linked gain for this buffer
unit is therefore not part of the repaired candidate. Earlier aggregate metrics
and full-build results apply to their named historical heads, not this repair.
The user's merge process owns fresh current-main coverage, build, original-DOL
and actual linker-input checks. The two upstream commit histories are retained,
but this explicit deferral means their complete source scope is not all adopted.
