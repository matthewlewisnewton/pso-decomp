# Save-record flag queries preserve the client word

This follows continuation `dad479cec7a8dc1f121402c33965f400a7aa3edb` on main
`12a3368673103f37dfd3710886ce24a4e19c6783`. Four historical Hard keyboard
methods actually receive a client word. The source now expresses their observed
free-function contract and explicitly forwards the client through the shared
save-record lookup. This is source-quality progress with zero coverage gain.

## Original transport and consumers

The four 36-byte queries at 8025EB74, 8025EB98, 8025EBBC and 8025EBE0 pass masks
128, 64, 32 and 16 to the existing static test helper at 801A529C. They do not
load a hardware-keyboard field or dereference their first argument. An all-section
scan of the verified current-main original objects finds exactly one direct,
zero-addend call to each query, all in the language-derived flag helper at
8025CC48, with no address-taking or other-section reference.

That caller loads a signed halfword at offset 0x20 into r3 before each call.
The old source cast this number to `TWindowKeyBoardHard *` and called a member,
although no hardware-keyboard object exists at that address. The four queries
now take an explicit s32 client through `CharacterSaveFlagQueries.h`; the caller
passes the same signed halfword with its ordinary word promotion. The names'
numeric suffixes are decimal masks. Result types, mask values, calls, branches,
language selection and writes to the caller's flag word remain unchanged.

The 76-byte core test and 80-byte setter both call get_character_save_record
while preserving incoming r3. Their previous source declaration took no
arguments, depending on that register remaining live. The actual 88-byte lookup
at 80202990 consumes a u32 client: split-screen mode distinguishes 0xFFFF from
other full-word values and otherwise returns the active record. A no-argument
source declaration therefore omits a meaningful input; it is not an unused word.

The test now passes its explicit client as u32. The setter passes the same
transported word from its retained legacy pointer-shaped argument. Both use the
existing target-address-word result. No narrowing, sentinel normalization, new
null behavior, extra record access or reinterpretation as a complete record is
introduced. Negative sign-extended caller values retain their original full-word
representation rather than being silently changed to 0xFFFF.

## Bounded declaration sharing and remaining ABI holds

CharacterSaveRecordLookup.h matches the actual definition's existing u32 input
and s32 address-word output. The historical public declaration uses this header.
The actual definition includes it within its pre-existing P80202978 namespace.
An initial global include failed because the same large owner also contains an
older global u16/pointer-return view. That unrelated view is preserved; no caller
width is changed merely to make a shared declaration compile.

This scope checks the recovered definition without claiming that all declarations
of the same C symbol are compatible. Other legacy lookup views, the setter's
pointer-as-client-word interface, general flag-helper naming/receiver views and
the outer language helper remain qualified. The saved record's complete native
type and portable address representation are not recovered. The change removes
four false member receivers and two implicit-register lookup calls only.

## Exact validation and providers

The first ordinary free-query and explicit-forwarding candidate preserves the
complete original text of the query owner (156 bytes), language-helper owner
(416 bytes) and core flag owner (752 bytes), with all normalized relocation
targets. Every allocated section's bytes, flags, sizes and alignments and all
resolved text/data targets remain unchanged from the preceding source objects.
The lookup owner's complete 27412-byte-text ELF remains byte-identical to the
captured checkpoint; its 88-byte lookup is also independently original-exact.
All four objects remain selected from source once. The complete ordered linker
input list is unchanged. No table, split, extent, alignment, compiler control,
original provider, retention entry or protected remainder changes.

After qualifying the existing definition namespace, the capacity-gated full
rebuild passes and reproduces DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against dad479 passes with
four function renames and zero metric, code/data/function coverage or linked
address change. All 3597 linked units remain exact; retention stays at 18457
names with no drift. Comparison against refreshed focused #402 and the port
exception inventory also passes. Independent read-only review supports this
bounded repair and the explicit remaining ABI qualifications.

The previous rank-index, ComCard trailing-word/table, Parts export, Palette
owner/conversion, Word/DD/nameplate, lifetime and initialization holds remain.
The inherited eight-byte main coverage qualification is unchanged. Both PRs stay
draft. No active shortcut-preview or Word recovery is duplicated here.
