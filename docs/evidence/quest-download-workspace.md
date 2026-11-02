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
Native layout, genuine objdiff and the full unchanged unit-eligibility checks
subsequently passed. The combined prefix/workspace candidate selects this
2,448-byte owner and the separate 12-byte prefix. It names the exact original
workspace boundary without an alignment override, added padding, symbol
edit or consumer change. Scratch remains original and its selected halfword
contract is unchanged.

Native validation compared `08dde1b4dda051844878d755dd0c9dbb13c61b27` with
retained baseline `140bc0ace7fcfe2deca0894ea09adb2c306f73e6`. It proves
+2,460 matched and source-linked bytes in total, original-DOL equality, actual
source linker inputs, unchanged final ELF boundaries and all nine raw loss
classes zero. The final workspace symbol remains at `80595008`, size 2,448;
the existing slots begin at `80595998`. Both new compiled objects equal the
independently reviewed diagnostic objects. The baseline was not rebuilt.

See [the combined validation summary](quest-download-display-prefix.md#combined-native-validation)
for exact metrics, retained consumers, diagnostics and final independent review.
This source-only publication follow-up changes documentation only after the
tested candidate. Latest-main acceptance remains with the separate merge
process. The original-only interpretation and bounded-interface uncertainties
above remain in force; this result does not recover a historical query type
or certify original producer bounds. Original artifacts and private evidence
stay local.
