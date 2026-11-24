# Status page and PageIndicator stack integration

The continuation integrates main `12a3368673103f37dfd3710886ce24a4e19c6783`
through focused GuildWarning head `d2b34bd26795df47f3d119d563cb523d0585ec6f`.
PR #420's reviewed source recovery is now upstream. Its page initializer at
8027FF6C replaces the historical 1344-byte probe with the exact 1348-byte body.
The complete Pages object has 5136 text bytes, seventeen functions, 271 text
relocations and an eight-byte conversion pool. Its complete compiled ELF is
identical to the separately verified fresh-main object and selected once.
Upstream receives the recovery credit; this refresh adds no new page algorithm.

## One observed page object

The continuation's address-suffixed page declaration and main's `PageIndicator`
are unified in `pso/misc/PageIndicator.h`. There is no parallel type or alias.
The existing native constructor moves to this declaration; it stores two signed
bytes, the input-port word at offset four, and zero arrow offset at eight in a
twelve-byte allocation. Dynamic page/count producers already sign-extend their
observed byte values. These observations support the recovered contract, not an
original class-name or inheritance claim. No TObject base or virtual destructor
is inferred. The ordinary-storage release protocol is unchanged.

All six allocation sites are migrated: DuelResult, HelpItem, ShortCutList,
StatusDisp and both ComCardList constructors. All fifteen getter calls use the
same page object; none casts its twelve-byte allocation to a status window.
Status owns a typed pointer, while the other retained storage views remain
qualified by their existing caller evidence. Draw/input/decay helpers keep the
continuation's typed draw context and use the canonical field names. The getter,
constructor and retention catalog use the same native symbols throughout.
One stale Control setter retention name is removed after fresh-input generation;
the actual Base setter and current player flag helpers remain retained.

Thirteen affected complete caller/helper objects preserve all their prior
allocated section bytes and normalized relocation targets. Their complete text
and text targets also match the original objects. This includes the 1272-byte
page-helper unit, the eight-byte getter, and the 1660-byte Status unit. Status's
native constructor/destructor and borrowed four-pointer rank array plus native
vtable (forty recovered data bytes) remain intact. The original thirty-two-byte
suffix remains selected once with identical bytes and relocation destinations.
No new compiler control, wrapper, fabricated ownership or padding object is used.

The rank index remains unchecked. The lower decoder's negative clamp does not
establish an upper bound of three. This integration resolves the missing-body
and false PageIndicator receiver findings; it does not claim universal index
safety, alter the original behavior or clear unrelated lifetime/ownership holds.

## Validation and inherited coverage

The capacity-gated full build passes, followed by the retention rebuild. The
DOL remains SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
`check_pr --no-build` against refreshed GuildWarning passes: 3597 linked units
are exact, with no function or linked-address regression. The continuation adds
492 linked code bytes and 1604 matched / 1560 linked data bytes versus that
focused base. Its fourteen previously documented four-byte window gaps remain
qualified; they are not new refresh losses. Retention has 18457 names and no
missing/stale entries. Port exception inventory and scope checks pass.

The historical comparison with published continuation `34db766ce` also passes
the current reporting tool, which classifies two upstream four-byte gaps as
padding. A separate strict interval audit, without that exemption, explicitly
retains the inherited eight-byte coverage loss: BSS [8051857C,80518580) and
sdata2 [805DAA54,805DAA58). The BSS interval also leaves exact-data coverage;
linked-data coverage does not regress. These are exactly the same strict ranges
lost by main relative to its prior baseline. The TLobby BSS shortening comes
from upstream `fd739a51600b995813343f3c18eb07befa1cf5c6`; observed 0xBC records
support the declared array extent but do not independently prove the trailing
word is padding. The sdata2 gap is separately inherited, without a speculative
ownership attribution. No strict historical no-loss pass is claimed, no reporting
code or gate is weakened, and no invented source word conceals either gap.
The [focused qualification](guildwarning-focused-split.md) records the baseline.

All prior evidence and attribution remain. The thirteen affected object checks,
original-provider checks, protected 1044-byte helper and refined data remainders
pass against fresh main. Parts still selects its original provider, including
its exported constants. ComCard's trailing word, Palette UV/table ownership,
Word/DD/nameplate, callback, initialization and other recorded holds remain.
The stack stays draft; neither branch is merged or formally approved here.
