# Final raw composer predicate: direct receiver cohort

This follows 2b92dd446a. An all-original-object resolved-relocation census of
8024701C finds five zero-addend direct text calls across four units, and no
relocation-backed table references. The caller/producer pairs are:

- Ctrl wrapper 8024A314 and two Ctrl handlers load receiver +0x38. Original
  Ctrl construction allocates 0x3C, calls Chat constructor 80247C68 and stores
  its result at +0x38 (901f0038).
- SubLog task loads +0x28; its original constructor stores the result of the
  same 0x3C Chat construction at +0x28 (901d0028).
- TradeMain task loads +0x50; its original constructor stores the same Chat
  construction result at +0x50 (901d0050).

Four original references to the Chat constructor were found. The fourth is
SubShortCut, which also stores a 0x3C Chat result but is not a direct consumer
of this predicate. Four predicate consumers compare the full return word with
cmpwi r3,0; the wrapper forwards it unchanged. This census covers resolved
relocations, not arbitrary computed-call arithmetic or universal lifetime.

The helper retains its historical C export and bool implementation. Its local
receiver declaration is now TWindowChat*, replacing the synthetic Win_8024701C
view. It reads existing native composer/flags/hardKeyboard fields. The composer
call now uses the genuine integer member, removing the last raw composer query
alias. Reads, short-circuit order, raw hardware helper and return normalization
are unchanged. All captured 3,655 compiled objects and the original DOL remain
raw-byte-identical after the gated build; aggregate no-loss and inventories pass.
Independent scoped source review accepts the correction.

This proves the observed receiver identity, not the original function name or
member ownership. In particular the outer helper's bool definition versus s32
external declarations remains a separate ABI cleanup question; this checkpoint
neither changes nor claims to solve it. It also does not resolve raw hardware
query ownership, borrowed lifetime, Hard table extent or other family holds.
