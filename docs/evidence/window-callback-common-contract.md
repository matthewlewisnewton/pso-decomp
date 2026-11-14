# Shared callback contract for the inspected producer graph

This follows production checkpoint `8602ea2b7f8cf4b5a1d87be620716761645c0fdd`
and the [bounded seven-target census](window-callback-closure-gates.md). The
source change is atomic across all named producer/consumer edges in that graph.

## Recovered contract

`WindowCallback` is a function pointer taking two borrowed `void*` arguments:
the callback window and frame context. Factory, forwarding wrapper, constructor,
genuine member setter, stored field and invocation now use this same type.
All five frame-drawing targets already accept these arguments explicitly. The
two singleton-mediated targets now accept and ignore both arguments; their
original global reload/null test and target operations remain unchanged.

The previous integer/object-pointer function-address transports, zero-argument
target mismatch, incompatible typed invocation and raw hand-mangled setter /
factory / wrapper declarations are removed from this graph. The setter remains
a separate real member, preserving original operation order and symbol address;
no hand-written alias, shim, extra callback or special compiler control is added.
Native compiler symbols confirm the six catalog/retention renames for the setter,
constructor, factory, wrapper and two singleton targets. The stored callback
remains one word on the target, with the original 0x64-byte class extent.

The original render dispatch provides its own Base-derived window and the result
of draw_default_entry. The latter's existing public word-valued interface remains
an explicit `s32`-to-context-pointer conversion. Outer returned window handles
still cross historical integer/opaque views. Those boundaries are not hidden by
this change and remain separate pointer-width/portability work. Free C-linkage
targets coexist with C++ static members under the validated target compiler;
this result is not a claim of universal C/C++ language-linkage interchangeability
or ARM portability.

## Which hold this retires

For the inspected relocation-backed graph, the incompatible explicit callback
parameter lists and function-address word/object-pointer transport hold is
resolved. There are now real, consistently typed callable targets at every
observed registration and dispatch edge. This is more than matching a callback
body: the address producers, field setter and indirect invocation change together.

The census does not exclude raw/computed address access, runtime replacement or
external aliases. Deferred-window retirement, replacement singleton generation,
borrowed frame lifetime, capture and unrelated window families retain their
holds. `close()` remains a close-phase request, not an immediate destruction or
render-suppression guarantee. No ownership, guard, reset, shutdown or rendering
order is changed to make the new source contract appear safe.

## Validation

Independent source review passes for the atomic graph and its stated limits.
The capacity-gated native full rebuild passes with original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

Against the captured production baseline, 3,644 of 3,655 compiled-source object
files are raw-identical. The eleven affected objects preserve every non-string
section, raw relocation record and ordered symbol entry after normalizing only
the six native symbol renames. Symbol-name/string offsets and serialization are
not claimed byte-identical. Addresses, payloads, allocation/cleanup order, tables,
original-provider selection and compiler profiles remain unchanged.
Address-based check_pr against the captured baseline passes with zero metric loss
and six catalog renames; retention and all 3,618 linked units pass. All 347
repository tests pass. No readiness or general portability claim follows.
