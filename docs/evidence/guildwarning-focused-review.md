# Focused GuildWarning review assessment and settings-helper repair

Assessment starts from focused head
`be9e024f26698be013626a8591bd25150228825f` on current main
`f8a71fae8a52f0bde1b956af4519061fe306cb30`. Live refs, clean worktrees and the
targeted owner/PR check showed no competing update. The continuation is assessed
separately; its unresolved native-lifetime work is not silently imported here.

## Focused review conclusion

No new blocking defect was found in the introduced GuildWarning scope. Its
observed 0x34 image, instance lifecycle, native methods and 600-byte renderer
agree with the original-byte/target evidence. The shared two-float layout lookup
and Message factory size-pointer input are supported by their actual consumers.
The focused partial change can receive technical review on those terms.

That conclusion is not universal safety or native-construction clearance.
Message's existing layout-word and result-pointer transports, three-argument
size-word delegation, raw Message/Base/Addition lifetime graph and layout lookup's
byte-storage view remain bounded inherited debt. Player-ID indexing and allocation
assumptions reproduce original behavior; no new guard or proof of every runtime
precondition is claimed. These qualifications remain explicit. The PR stays draft;
no ready marking, formal approval or merge follows from this assessment.

## Concrete repair within that scope

The factory's size-copy helper at 80269DA4 still had incompatible declarations:
its definition took a by-value float pair and pointer-shaped second argument,
callers used pointer/word views, and the factory used a function-pointer cast.
The nonvoid definition had no return statement. These were inherited boundaries,
not new GuildWarning behavior, but can be repaired without importing the wider
continuation graph.

`MessageWindowSettingsAbi.h` now gives the historical C export one shared
`void(const void*, u32)` declaration. The definition reads the same two floats
through its existing raw pair view and stores the same second argument word.
The word is not assigned an unproved semantic enum or receiver role. Six caller
units use the shared declaration with explicit pointer/word transport; the
factory's incompatible function-pointer call and const-discarding casts are gone.
No wrapper, symbol rename, constructor, data layout or compiler setting changes.
Raw source/destination storage views remain qualified; this does not identify the
unique original aggregate type or recover global-storage ownership.

An active original census examines 4947 objects and 249768 relocations. There are
exactly six zero-addend direct calls and no address-taking/interior reference.
At every call, the immediately following instruction overwrites r3 with the next
allocation size without reading its former value. This supports the observed
unused-result contract independently of the source calls. The original helper
performs only the two float copies and unchanged word store.

## Validation

One isolated coherent candidate reproduces all six complete compiler ELFs
byte for byte: Message, MessagePage, Lobby8026B06C, Lobby8035D540, text8026A93C
and text80269FE8. The production rebuild reproduces those same identities,
including the 36-byte helper, all callers, section headers, symbols and relocations.
The complete Ninja graph and report are byte-identical to the prior focused build.

The capacity-gated full build passes in 4.10 seconds with original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Address-based acceptance, 3600 exact
linked units, 18427-name retention and port inventory pass with zero metric change.
The prior fresh-main comparison and strict data-range qualifications remain
unchanged. A new standalone main build is not claimed. The focused contribution
remains one exact function, 600 matched/728 linked code and no additional data loss.

Private original-reference census, fixed source/commands, six whole-object
identities, build and acceptance receipts are in
`pr402-message-settings-contract/`. Original binaries/objects/disassembly are not
published. Independent source and frozen-head review remain publication gates.

The repair resolves only the helper's incompatible call/return views. Remaining
factory storage/lifetime assumptions are retained; unrelated continuation holds
do not become newly introduced defects in this focused partial PR.
