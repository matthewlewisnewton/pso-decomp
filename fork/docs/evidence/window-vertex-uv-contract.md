# Raw vertex UV table helper

This follows continuation `3388a4604a69d31a5eb27d0eaf662c9bbb5b1b94`, after
integrating merged Word recovery on main `59dfc7117a`. The helper at 80348A9C
now has the shared free-function contract
`copy_vertex_uv_table(void *storage, s32 index)`, instead of a TWindowDD method
invoked on raw vertex buffers. This removes three false window receivers with
zero match or source-link gain.

## Storage and original references

The original 56-byte helper copies eight pairs from the existing seven banks,
with an eight-byte source stride and 24-byte destination stride. Its two stores
are at destination offsets 12 and 16. The lower textured-vertex consumer at
803E2810 loads those fields as the two GX texture coordinates; the integrated
WordRowVertex declaration likewise has u/v there. This supports UV pairs rather
than a new window image or a new table owner.

A complete original-object scan on freshly rebuilt main finds six direct,
zero-addend calls and no address-taking or other-section reference: three in
DD's retained original object, two in Word and one in WS_String. The destinations
are stack vertex buffers. The three implemented source calls now pass that raw
storage directly. Original DD calls continue to resolve to the same address
through the regenerated catalog; DD's incomplete source is not activated.

WindowVertexBufferAbi.h shares the definition and source caller declaration.
The false nonvirtual member declaration is removed, and the catalog names the
actual free definition. No old-name alias, wrapper, replacement binding or extra
call is added. The index retains its existing signed-word transport, with no
narrowing, range check or sentinel change. The source still copies eight pairs.

Private source/destination views name u/v and have explicit size/offset guards:
source pair eight bytes, destination stride 24, u at 12 and v at 16. The existing
7x8 table and its 448-byte BSS definition are unchanged. Its initialization,
index bounds, selected bank contents and ownership are not reinterpreted.
The raw destination view retains the existing target storage/aliasing boundary;
this does not establish portable C++ lifetime for every caller's character buffer
or a complete native vertex class. Other draw/transform helper views remain
separately qualified.

## First-candidate qualification

The first ordinary free-function candidate preserves all 56 helper bytes. The
complete 844-byte String helper and 3412-byte Word texts, including all resolved
text/data relocation targets, remain original-exact. All allocated section
bytes, flags, sizes and alignments match the preceding source objects. DD's
incomplete 1244-byte compiled ELF is byte-identical to its preceding object.

The complete ordered executable input list is identical. Word and String remain
selected from source exactly once, while DD retains its original provider. No
split, extent, compiler control, table, padding range or provider changes. The
retention list is unchanged at 18465 entries, with no missing or stale names.

The capacity-gated full build passes with DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against 3388a4604a passes
with one function rename and zero change to any metric or code/data/function
coverage. All 3599 linked units remain exact. Comparison against refreshed
focused #402 and the port inventory also pass. Independent read-only review
supports this bounded contract recovery and its remaining qualifications.

The complete Word renderer activation remains qualified by the preceding
[integration proof](window-word-main-stack-integration.md). Native Word lifetime,
DD's missing renderer, raw draw submission, ComCard trailing-word/table, Parts
exports, Palette ownership/conversion, callback and initialization holds remain.
The historical eight-byte main coverage qualification is unchanged. Both drafts
remain open; this source-quality repair does not claim review readiness.
