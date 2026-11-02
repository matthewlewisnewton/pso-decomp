# Quest download workspace byte storage

This continuation supplies the existing `lbl_80595008` allocation as one
zero-initialized `u8[0x990]` object. Its boundary is
`0x80595008..0x80595998` (2,448 bytes); the separate slot array begins at its end.
The first 2,240 bytes remain uninterpreted. They are not asserted to be unused,
padding, slot records, or a dummy prefix in a fabricated query class.

The reference context is PR #262 at
`26d94367605e45aeb0364e0df6ecc09ff5d34a11`, whose production files match the
native-tested `140bc0ace7fcfe2deca0894ea09adb2c306f73e6`. This preserves #238's
upstream-attributed import and cache work and #262's separate slot definition.
This candidate does not change either published branch.

All interpretation of this workspace remains in original provider code. The
resolved references belong to A428 and A9E8. A428 passes the final 208-byte
region synchronously to query producers and the item-list builder. The inspected
producer path does not retain its output pointer; the builder copies values
into separate nodes. A9E8 uses the workspace-end address as a native anchor for
the separate slots. No C++ expression crossing that boundary is added here.
The reference tree has no source/header declaration of the workspace, so this
byte definition does not conflict with a selected typed declaration.

This is a bounded interface to original binary code, not a claim about a
historical translation unit, original query type, or typed C++ subobject
lifetime. Future source consumers require their own compatible access and
lifetime contracts. The symbol/reference inventory does not exclude arbitrary
computed aliases. A conditional original query path can write past the final
208-byte region; reachability remains unproved. This change preserves the
existing allocation and behavior rather than increasing capacity to conceal it.

Independent source review passed for the exact byte-storage proposal
(SHA-256 `298c5b49ecc1bf500066e7a9db1d6f3367db96a2086252b190c3b1f7f9a86665`).
Review SHA-256: `01864e681b9452be75a6daacc63ae4bb06860332b638bc3678b74e711231f04e`.
Native layout, full unchanged unit eligibility, explicit source selection, actual
link-input provenance, original DOL, full report, no-loss checks and independent
output review are pending. No new matched or source-linked bytes are claimed.
The 12-byte prefix is a separate continuation; scratch remains original and its
selected halfword contract is unchanged. Latest-main acceptance remains with
the separate merge process. Original artifacts and private evidence stay local.

The inactive split names exactly that existing allocation, with no alignment
override, added padding, symbol edits or linked-unit change. The generated
original partition and native object still require scheduled qualification.
