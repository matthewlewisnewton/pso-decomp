# w7-fork-a

No code changes; nothing matched or linked.

## 1. Boss7DeRolLeCBehavior, 802E7D70 (99.87%)
Only difference left: target computes the slot offset in place in the saved register
(`addi r30,r28,0xb; extsh r30,r30`), ours emits `addi r0,r28,0xb; extsh r30,r0`.
Tried: scalar `(s16)(slot+11)`, `offset = slot; offset += 11`, `slot += 11`, `s32` offset narrowed at use,
fork's `s16 &` / struct-member reference helper with `dont_inline off`, `auto_inline off`,
`inline_depth(4)` (the helper does inline once `auto_inline off` + `dont_inline off` are set; same code as scalar),
`opt_lifetimes off`, `opt_propagation off` (worse), computing the id in the other operand order,
reading `get_entity_id(self)` first. All 99.87% or worse. Remaining lfs differences are only
@N vs lbl_805DEA10 naming of the unit's own pool.

## 2. TQuestVmDownLoadServer 803EA428 (97.4%), 803EA9E8 (92.8%)
803EA428: register allocation cascade (one extra live register, slot address computed
`start*0x1c + work + 0x990` instead of target's `(work + start*0x1c) + 0x990`). The fork gets that order only
through `size_t` address arithmetic on a workspace object, which was not brought across. Adding the fork's
pragmas (`inline_depth(2)`, `opt_lifetimes off`, `opt_propagation off`, separately and together) gave 97.3 to 97.4.
803EA9E8: target hoists the slot/scratch address setup above the mode store; `opt_lifetimes off`,
`opt_propagation off`, `opt_common_subs off` and combinations all lowered the score (83 to 91%).
Left as found.

## 3. TBoss7DeRolLeC constructor 802EDE90 (97.4%): blocked on unit boundaries
Target addresses the vtable (0x804E3E54 = base 0x804E3BF0 + 0x264) and tables (0x804E3D1C, 0x804E3C8C) from one
base register, so they are one TU's .data. They sit in Boss7DeRolLeCBehavior (.data 0x804E3BF0..0x804E45C4).
The fork's split is the same as this tree's (text_802EDE90 is a separate unit), so it gives no boundary evidence.
A fold would have to merge 802ED928, 802EDCF0 and 802EDE90 into Boss7DeRolLeCBehavior, and the vtable is
not defined anywhere as C++ (only `extern s32 TBoss7DeRolLeC__vtable[]` in 802EDCF0), so it would need the
class's ~100 virtuals declared so the compiler emits it. The merged unit would also stay unlinked while 802E7D70
is open, unlinking the two currently linked fragments. Not attempted.
