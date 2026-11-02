# Quest display-prefix source linkage

The inactive source checkpoint originated at
`0677283ae59d077cc40187e11db3ce3aa9207493` and passed independent source review.
This selected continuation carries that unchanged definition on the frozen
slot follow-up #262 at `26d94367605e45aeb0364e0df6ecc09ff5d34a11`. It preserves
the existing 29,184-byte cache and 2,240-byte slot selections. The attributed
upstream import remains in the dependency history; this definition retains the
original symbol and extent.

`QuestDownloadDisplayPrefix.cpp` defines the actual 12-byte encoded character
array at `80596258..80596264`. Both existing source consumers declare this symbol
as `u8[]`; the definition keeps that element type and C linkage. Static zero
initialization supplies the backing array before the frontend initializes it.
No structure overlay, union-member transition or node lifetime is needed for
this character storage. The remaining 1,028-byte scratch object is separate.

The original-reference census identifies four direct users. Frontend 5B94
initializes the prefix with `strcpy` from the constant at `8047E68C`. That constant
terminates at offset 10, so the copy uses 11 bytes within the 12-byte object.
Native B4D4 writes display-count bytes at offsets 5, 6 and 7, then passes the
prefix to C95C. BEFC and C460 use its address only as an anchor for the next
object at `+12`; they do not establish a larger prefix array.

C95C reads encoded characters until NUL, advancing by one or two bytes. Its
retained compiled body and symbolic relocations equal the original. A finite
read-only check of the retained prefix, all 256 possibilities for the first
count byte and the ten decimal possibilities for each remaining count byte
covered 25,600 cases: termination was at offset 5 or 10 and the maximum read
offset was 10. This is a bound for that prefix reader and the native count-write
domain, not a proof about arbitrary corruptions or other scratch writers.
No original string or asset bytes are included in this document or source.

The validated #238/#262 linker inputs select the frontend source object and
the original provider object. The frontend's prefix declaration is compatible
with this definition; its prefix-address relocations and copy call are unchanged.
The fallback provider retains the original BEFC/C460 `+12` address calculations.
Defining this separate data object therefore does not require changing the
provider source or recovering all sixteen missing provider functions. Recovering
those two consumers later still requires proper separate-object scratch access;
this definition does not bless their provisional source pointer arithmetic.

The combined candidate names exactly `80596258..80596264` and selects this
12-byte source object together with the independently reviewed 2,448-byte
workspace. It adds no alignment override, padding object, shared header or
consumer-body change. The original provider remains selected from fallback;
the separately released BEFC/C460 address repairs are outside this candidate.
The 1,028-byte scratch object remains original and unadopted.

## Combined native validation

The tested candidate is `08dde1b4dda051844878d755dd0c9dbb13c61b27`, compared
with retained native baseline `140bc0ace7fcfe2deca0894ea09adb2c306f73e6`.
The dependency #262 at `26d94367605e45aeb0364e0df6ecc09ff5d34a11` differs
from that baseline only in documentation. The publication follow-up updates
only these evidence documents after the tested candidate; production blobs
are unchanged. Neither published prerequisite branch is modified.

Both individual objects passed source, native-layout, genuine objdiff and full
unchanged unit-eligibility review. The combined graph then passed independent
selection, retention and runtime review. One normal candidate build produced
a genuine 5,017-unit report and selected 3,557 source objects. Its DOL is
byte-identical to the original (SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`). The baseline was not rebuilt.

Matched data increased from 1,435,551 to 1,438,011 bytes; source-linked data
increased from 1,041,335 to 1,043,795 bytes: **+2,460 bytes** in each measure.
Exact functions remain 27,288 and code measures are unchanged. The captured
actual linker response selects both new data objects once. All 5,014 unaffected
consumed objects remain byte-identical, and both new source objects equal their
previously reviewed diagnostic objects.

The final ELF preserves all allocated section payloads, flags, extents and
alignments, and every defined global/weak symbol's address, size, binding and
visibility. Prefix `80596258..80596264` and original scratch
`80596264..80596668` remain contiguous with no added padding. Existing cache
and slot storage and consumer objects are preserved. All 339 diagnostic blocks
and 313 warning lines match the baseline.

`check_pr.py --no-build`, all 3,557 linked-unit checks and retention passed;
retention has 16,678 entries with zero additions/removals. All nine unfiltered
code/data/function coverage, exactness and linkage loss classes are zero.
Independent final native review SHA-256:
`dbb33f3213408fb3c5fc4e1c2267c2e81d1dbcefd12dd4b8301f0179b1c73737`.

This evidence applies to the exact historical candidate and baseline above.
Latest-main applicability and final merge acceptance remain with the separate
merge process. Scratch representation, capacity, phase/reentry and tail-byte
questions are excluded. No original artifacts, private diagnostics or tools
are published, and no provider-function recovery is claimed.
