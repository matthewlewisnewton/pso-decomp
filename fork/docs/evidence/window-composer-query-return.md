# Composer full-width state predicate

At 24c7aa6c40 the composer predicate at 8025CB10 had a bool definition/header,
but its four direct original callers compared the full result word and the
reconstructed raw callers declared s32. A caller-only replacement with the
native bool declaration inserted byte normalization and failed the original DOL
check; that attempt was rejected, not used as an excuse to retain a false ABI.

An all-original-object relocation census finds four direct zero-addend calls:
three in TWindowChat and one in TWindowKeyBoardBase. Each call is immediately
followed by instruction 2c030000 (cmpwi r3,0). The genuine member reads m_7c and
m_94 and returns the integer predicate 0 or 1. Its declaration and definition
now agree on int, and its final conditional is expressed explicitly as 1 or 0.
Render can therefore call the actual member with this, instead of its raw alias,
without narrowing the result. Existing Chat raw declarations remain compatible
full-word returns; their separate receiver-view cleanup is not claimed here.

This recovers a consistent observed full-width interface, not the original
source spelling. The first nonzero m_7c still returns 1 immediately; otherwise
m_94 determines 0/1. Reads, guards and short-circuit order are unchanged. Every
captured compiled object and the original DOL remain raw-identical after this
change. The capacity-gated native build and aggregate no-loss checks pass.
No layout, data provider, compiler setting, symbol name or retention change is
introduced. The hardware-global query's distinct owner question and the wider
window-family lifetime/table holds remain.
