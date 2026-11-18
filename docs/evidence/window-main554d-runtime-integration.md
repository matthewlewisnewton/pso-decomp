# Current-main runtime integration

This ordinary #403 refresh combines preceding continuation
`5bb474c6ef5a0d43d9af671267fb0a53b4b8bcd9` with accepted main
`554d21699c873ccf9be1b2268eba37cd3a32e48b`. Main contributes #458 EXI,
#459 ADX, #460 LaserLight constant-pool linkage and #461's explicit frame
receiver. Their evidence, attribution and native/portable qualifications remain
intact. The only merge conflict joins the exception register's incoming ADX
subsection and existing window-lifetime chapter; both are retained in full.
No new runtime implementation or compiler control is introduced here.

The runner-provided Ninja verification and every source-check gate remain
unchanged. The complete CMName provider and its five recovered keyboard calls,
both formatter providers, and the typed BML/heap/primitive interfaces are retained.
The EXI frame callback correction does not establish the window callback's ABI
or clear any borrowed-lifetime hold.

## Native validation

Fresh pinned-main and combined builds use the shared capacity gate and unchanged
local original inputs/tools. They complete in 89.88 and 88.69 seconds. Both DOLs
are byte-identical to the preceding continuation and reproduce original SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

Strict checks pass against both fresh main and the preceding continuation:
3,626 source-linked units are exact, with 19,114 retention names and zero drift.
Against fresh main, functions/code are unchanged and the continuation retains
1,604 matched/linked data bytes. The same fourteen qualified four-byte window
tails remain; no new raw, exact or linked loss is introduced by this refresh.
Main's separate 31-byte reported denominator change versus the preceding main
is inherited: three EXI string-tail bytes and seven four-byte ADX intervals.
It is not a new ownership assertion or a waived regression.

The twelve EXI/transport/LaserLight/ADX source objects are whole-ELF identical
to fresh main. Their 171 original functions, 41,836 owned text bytes and 1,506
original-owned relocation bindings are checked, including 966 actual linked
REL24 branch destinations. Stored data agrees with the explicit inherited
qualifications below. Each compiled provider is selected once; its original
fallback is absent.

LaserLight additionally emits a trailing 16-byte weak `queue_destruction`
helper, outside its original 976-byte text. Its two calls bind to the existing
strong function at `0x80019A50`, verified in the linked ELF and branch words;
the object's local weak offset is not used as the final target. Six ADX rodata
sections retain exact string prefixes with 25 original zero-tail bytes in total
outside emitted storage: Manager 3, Stream 5, Talk 7, Init 2, Server 6 and Start 2.
Those source extents and all section metadata are identical to accepted main;
the complete DOL retains the original bytes. These observations do not recover
portable padding ownership or original source/compiler provenance.

Of the common active source objects, 3,611 remain raw-identical. Five changed
objects either reproduce accepted-main allocated images/targets or preserve the
preceding runtime image/targets with metadata changes. Twenty protected complete
continuation objects, including CMName, six Message objects, Word, Parts,
ComCard and the preview owner, remain raw-identical. Seventeen original remainder
providers retain their bytes/targets and are selected once; the 1,044-byte preview
and explicit original-only CallBack word remain protected.

The two EXI receiver host tests and all five portable behavior/sanitizer targets
pass. LeakSanitizer first rejected the local ptrace sandbox; the unchanged
sanitizer command passed outside that sandbox, without disabling checks.
Independent frozen-head review and hosted source checks are separate publication
gates. This build evidence does not claim review readiness.

All substantive Word order/table/startup, ComCard trailing-word/conversion,
CustomSelect initialization/session, keyboard lifetime, Parts provenance,
callback, record-capacity and other documented holds remain. The previously
denied PR-description update is not part of this refresh.
