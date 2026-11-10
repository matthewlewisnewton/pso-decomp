# Chat close/reopen receiver contract

This follows PR #268 checkpoint `b42f850c1b98e3609a888b5d052e9fc54b0027cd`.
The two remaining historical SubShortCut helper views have their evidenced Chat
owner, and the close/reopen wrapper uses the actual native void member calls.
The child-lifetime and wider interface qualifications inside those callees remain.

## Receivers, calls and state ordering

All-section inspection of original objects finds exactly one direct zero-addend
call to each helper, with no address-taking or other-section references. Both
calls pass the same field 0x38 immediately after ordinary new TWindowChat in the
SubShortCut task. The object has the established 0x3C Chat image and halfword
flags at 0x1E. Neither call targets a SubShortCut object or consumes a result.

The 64-byte helper at 80246FB0 now defines TWindowChat::close_and_clear_flag().
It calls the existing native void close_all_children(), clears mask 0x0002 in
Chat's flags, then calls the existing native void open_next_input_window().
This preserves the exact close/clear/open order and supplies the actual Chat
receiver explicitly through the C++ member calls. The old no-argument/s32 close
alias and void*/s32 open alias are removed; no replacement ABI binding or cast
is introduced to conceal that forwarding boundary.

The 16-byte helper at 8027E268 now defines TWindowChat::set_flag1e_bit80() and
sets mask 0x0080 in the same halfword. Both task call sites name TWindowChat,
and the false SubShortCut member declarations are removed. The preceding
composer-flag call recovered in the prior checkpoint remains unchanged.

This does not change allocation-failure handling, add a guard or initialize
other flags. Existing word-valued task storage and ownership remain unchanged.
No new meaning is assigned to the masks beyond the observed state operations.
Both recovered methods are nonvirtual; no class layout or table slot changes.

## Callee and lifetime qualifications

The existing close_all_children body remains 144 bytes and the existing
open_next_input_window body remains 384 bytes, each byte-exact to original.
Their code and source declarations are unchanged. The open method can enter the
held Soft-window construction path. Correcting this wrapper does not establish
a complete Soft class, native child lifetime or portability of that boundary.
All other callback, record, capacity, initialization and ownership holds persist.

## Exact objects and validation

The first ordinary native probe preserves complete helper108 and task1880 text.
Both recovered bodies independently match original at 64 and 16 bytes. The full
build also preserves Chat3808. All three complete texts and every resolved text
relocation target match original; every source object is selected once.
Allocated section headers, flags, sizes, alignment, data/constants and resolved
text/data relocations remain unchanged from b42f. No source activation, data
provider, original remainder, compiler control or synthetic table is introduced.

The existing retention entry follows the 16-byte helper's native symbol rename;
retention remains clean at 17,882 and port inventory passes unchanged. The
capacity-gated full build preserves DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr passes against published
b42f with zero metric/coverage/address delta and two catalog renames, and against
separately built main `25b4001837b8bdc46666d2ad736a7148a411f978`.

Earlier composer flags, copy/text, Snapshot, WS_Word and protected-original
checks pass again. CMName retains its original provider and existing differences.
The original 1,044-byte helper and WS_Word's full original3,412 provider/missing916
renderer remain intact. Totals remain 27,404 exact functions, 3,585 exact linked
units and 3,641 source-bearing units; combined PR deltas and the fourteen
qualified four-byte alignment ranges remain unchanged.

Raw Base/Addition calls remain 22 across 12 units and four shared bindings.
The remaining record, capacity, CMName, constructor ABI, lifetime, constant,
table-order and ownership holds are not closed by this source-fidelity step.
The PR stays draft.
