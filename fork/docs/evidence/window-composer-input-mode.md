# Composer input-mode receiver recovery

This checkpoint follows `c844f432f4175f558e9547dc739e13dee3a3c7c8`.
A complete active-object relocation census finds two original direct calls to
`0x8024FBA8`: Hard process_key_input and the Soft key-selection handler. Both pass
their borrowed composer, followed by an input-mode value. No original table or
address-taking reference to this function was found in that census. This does
not exclude arbitrary runtime address arithmetic.

The eight-byte setter previously carried a false TWindowSubStatusDisp owner,
whose field at 0x64 is a word. The actual TWindowKeyBoardBase composer has a byte
there. It is now `m_input_mode`, written by a real composer member. Both callers
use that member; Hard also uses its typed composer for the following insertion
instead of rereading offset 0x70 through an integer pointer.

The reconstructed parameter is s32, preserving the full-width contract of both
existing call sites, with narrowing on assignment to the byte. This deliberately
does not add caller-side byte truncation or a new range check. It is a defensible
source signature, not a claim to know the original exact spelling. The function
returns void: its body only stores the byte and neither caller uses a result.

The capacity-gated native build reproduces the original DOL. Complete allocated
payloads, section headers, symbol metadata/order and resolved relocation targets
in all three affected source objects are unchanged after the single export
rename to `set_input_mode__19TWindowKeyBoardBaseFl`. Their relocation counts are
67 for the setter owner, 390 for Soft and 216 for Hard. All other 3,633 active
compiled objects remain raw-identical. The three units remain source-selected. Fresh checks against the preceding head
and pinned main pass, with no new loss or retention drift. All 346 tool tests
and portable behavior tests pass; independent source/documentation review found
no blocker in this scoped change.

The Soft child's legacy PMF façade is deliberately unchanged; the evidenced
composer view is used only at these ordinary direct calls. This does not settle
borrowed-composer lifetime, PMF/callback ownership, Hard destruction/table,
Word/ComCard or other window-family holds. No readiness or matching gain is claimed.
