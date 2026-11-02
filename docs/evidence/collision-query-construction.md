# Collision query construction at 0x8007A6C8

The static initializer constructs 32 records at 0x804FF9C0 with a 0x1C
stride, then initializes the 8-byte object at 0x80500140 and the 16-byte object
at 0x80500148. The reset at 0x8007A7A0 stores the pool address in the second
word of each result. The polygon-query loop accesses each pool entry as a
point, normal and flags, matching `CsnContact`. The second result adds the
selected index and distance to those first two words.

These three globals have actual constructors. CodeWarrior emits their single
initializer and passes the contact constructor to `__construct_array` through
its own constructor ABI. This avoids calling an ordinary function through an
incompatible constructor callback. The initializer, both result constructors
and the contact constructor keep their instruction bytes and relocation
positions. Their placeholder symbols are renamed to the compiler-generated
constructor names; the initializer becomes the local compiler-generated
`__sinit` symbol. The `.ctors` entry references it, so the former global
force-active entry is unnecessary. A scan of the pre-change split and compiled
objects found no other references to these four former names except the
initializer's references to the three constructors.

Although the 8-byte result resides in `.bss`, its external declaration uses
CodeWarrior's `.data` section attribute. This preserves the original full
address relocations in consumers; without it, the compiler selects small-data
addressing because the corrected type is eight bytes. The initializer object
retains the original global sizes and offsets and emits `.bss` for the result.
The clearing routine keeps its existing export name but takes a contact
pointer, matching its definition and callers rather than claiming a live
`TObjPlayer` receiver.
