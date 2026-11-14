# Shortcut preview and Word/String contracts across the native lifetime stack

This reconciles continuation `0092b8f67cec6e29e37ead4747bcca7fa09cc43b` with
focused `37ed8308f9df0e8ff4426bcc187f378f337a2cbc` and main
`e65f11ce6ec99c006909422f81da1c0a46ac062e`, including merged #415.
The earlier [Word timing/profile diagnostics](window-word-specific-context-control.md)
remain unactivated. This integration neither changes Word's constructor owner
nor its compiler profile; that complete ELF remains identical to its saved
published checkpoint.

## Protected preview bytes and native lifetime coexist

Main recovers `TWindowShortCut::initialize_preview` at `0x8026E1D4`, the
1,044-byte range previously kept as original input by this continuation.
The existing source owner contains a native 492-byte `TUnk_804D0948` lifetime
prefix and its 28-byte compiler table. They now share the full original text
interval `[8026DFE8,8026E5E8)` with the recovered preview. The split retains
that table and adds main's 52-byte constant pool `[805DD348,805DD37C)`.
There is no artificial source unit or second copy of the preview.

The combined object reproduces all 1,536 text bytes, 28 data bytes, 52 small-data
bytes and all 99 normalized original relocation records. Its six function bodies
and function-relative targets match. Source is selected once; the old original
1,044-byte fallback is absent only after this complete qualification. Its protected
bytes are preserved by the compiled source, not dropped from the program.
The four bytes immediately after the pool remain at the head of the original
188-byte remainder beginning `805DD37C`, selected once and byte-identical to
fresh main. No unknown tail is assigned to an invented field or constant.

The preview uses this continuation's genuine `new TWindowChatSymbol` path,
not the incoming legacy raw initializer alias. ShortCut keeps its existing
native constructor, destructor, Base cleanup, opaque heading at0x60 and borrowed
record at0x70. Its constructor calls the recovered member directly. The optional
symbol child at0x68 is typed as `TWindowChatSymbol*`, as established by its actual
producer; message child0x64 stays a Base pointer. Their close/null cleanup and the
0x74-byte parent layout are unchanged. ShortCut's complete 500-byte owner and
all targets reproduce the original. Native ChatSymbol construction and its
provider remain selected once, without a wrapper or default-constructor invention.

## Truthful common contracts carried into native Word/String

The shared `measure_text_entry(void*)` boundary receives actual text entries in
the native String constructor, Word render/list-loader, Room and other recovered
callers. It does not assign those entries a DD window identity or depend on an
unexpressed incoming argument. `WordSelectMessage` shares the actual compact
12-byte record and full-width dispatcher/player contracts. Caller-specific low
16-bit extraction follows the incoming recovery; incoming player words are not
narrowed speculatively. The new symbol-chat members retain the real ChatSymbol
receiver. Main's [contract evidence](twindowdd-member-standins.md) is preserved.

The complete native String constructor owner is 460 original bytes with matching
targets. Word remains 3,412 original bytes / 25 functions / 112 text relocations,
including its native task and fields. The 56-byte UV helper, its complete 844-byte
owner, existing 448-byte bank, both caller units and ordered window providers
retain their preceding byte/target qualifications. The independent DD source ELF
remains unchanged and its original provider stays selected. Raw reset, UV and
other held buffer interfaces acquire no new lifetime claim.

Twenty-five source units change in the merge. For the 23 units with complete
original text, the comparison verifies 235 original function bodies and their
function-relative normalized targets. The two original-provided units stay held:

- The incomplete localized formatter unit retains its missing 1,628-byte Spanish
  function and existing source-data/jump-table differences (432 compiled versus
  436 original data bytes). Its compiled text, data and all normalized targets
  equal fresh main's compiled counterpart. Its full original provider remains
  selected once; no source admission or new four-byte exception is claimed.
- Fukidasi retains the reconstructed nonexact 800-byte nameplate. Its entire
  compiled text/data and normalized targets equal the prior published native
  recovery. Its original provider remains selected once.

Parts' eighteen float-export ownership gap, the other original data remainders,
ComCard and Status qualifications, partial initialization, callback/opaque
ownership and all existing renderer/provider holds remain. Previous evidence and
the complete attribution archive are unchanged. Of 41 incoming paths, 35 retain
the exact upstream added/removed-line sequence; six native-integration differences
are explicitly accounted for in the private preservation receipt. The owner was
already in the continuation's linked list, so it is not admitted a second time.

## Source qualifications retained from the preview recovery

The MWCC path still reads `shortcut_kind_sprites[kind - 1]` for kind zero from
the preceding separator's trailing byte. This is an inherited language-level
bounds qualification, not proof that an independent four-byte array has a valid
negative subscript. The portable branch handles zero explicitly. The existing
scoped fused-float and propagation controls and `.sdata2` definitions retain
main's exception-register entry; this merge adds no compiler control.
Child allocation is followed by the original unguarded use; the recovery does
not establish allocation-failure safety. Kind, record, message and callback
bounds/ownership preconditions remain as before. No behavior repair or inferred
heap-zero guarantee is introduced to make the source appear safer.

## Integrated validation

A fresh isolated main build, focused build and reconciled continuation build use
the existing capacity gate and pinned tools. All reproduce DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Continuation acceptance has 3,601 exact
linked units and 18,584 retention names without drift; port inventory passes.
The source/provider/relocation proofs above and all remaining protected-original
range checks pass. Comparisons against preceding B, refreshed A and fresh main
pass, with no new strict raw, exact-data or linked-data range loss against B.
The same fourteen qualified four-byte window tails remain against A/main, and
all twelve inherited historical main coverage bytes retain their qualifications.

Against preceding B, upstream supplies one exact function, +1,044 matched/linked
code and +52 matched/linked data bytes. Its native 492-byte prefix was already
linked here. Main now links that prefix too, so B's previous +492 linked-code
advantage over A is superseded: current A/B matched and linked code totals agree.
B retains +1,604 matched / +1,560 linked data bytes against A. The new +1044/+52 change versus preceding B belongs to upstream #415;
the existing data contribution remains historical. No gain is credited to the
failed Word timing controls.

Independent read-only review checks the frozen combined source and proof limits
before publication. Both PRs stay draft. This qualifies only the recovered preview
provider and truthful combined boundaries; no global lifetime/profile, bounds or
ownership hold is lifted and no merge or formal approval is performed.
