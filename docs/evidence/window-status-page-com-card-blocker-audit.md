# Status page and ComCard bounded blocker audit

This follows PR #268 checkpoint `8b0f14037dda44ed23c7cf211df26926010ecd35`.
Both probes are retained privately and all implementation/configuration files
are restored to that published checkpoint. No source is activated, no table or
data range is reclassified, and no coverage gain is claimed.

## Missing status page initializer

The consumer at 8027FD88 lacks exactly one original function: the 1348-byte
TWindowSubStatusDisp::vt4 at 8027FF6C. The existing sixteen functions total
3788 bytes. The new borrowed four-pointer table supplies concrete evidence for
the missing rank/time page, rather than another renderer scheduling hypothesis.

One ordinary native-member reconstruction expresses the observed page setup,
five entry triplets, text messages, decoded name, rank strings and play times.
It retains the discarded get_type(m_68) call and explicit unsigned-short client
conversions. The local byte view of get_status_window's result is supported by
the lower helper's 12-byte decoded shared text buffer; its shared word-pointer
return declaration is unchanged. Entry flags and the text entry's 0x24 store
retain their original storage views, without inventing a complete entry class.

The original unchecked rank lookup is preserved. The lower rank helper clamps
negative decoded values to zero but does not establish an upper bound of three.
This audit therefore does not claim universal table-index safety or add a guard.

The new body compiles to 1344 bytes, four short of the original. All 53 direct
call targets and their order agree. All sixteen prior functions and their
function-relative resolved relocations remain original-exact; every prior
allocated data/constant section remains unchanged.

The first divergence is the initial slot selection: the original has distinct
carriers for the title branch and retained record slot, including a register
copy. The reconstruction uses one slot variable. Later register allocation also
differs. Machine registers alone do not establish two source variables or a
missing inline helper. No extra carrier, declaration permutation or scheduling
variant is tried to recreate that copy. The full original 5136-byte consumer
provider remains selected, with compiled source absent.

Further progress needs independent source/value-lifetime evidence for that
selection boundary, or a supported common page implementation that explains
it. The probe's matching calls and semantics are insufficient for activation.

## Basic ComCard key function and data partition

A separate coherent class boundary was examined at text 80249C10. The first
752 bytes contain the basic window's setters, three factories, rendering/task,
destructor and native constructor. The remaining 1092 bytes contain existing
accessors, entry/status helpers, the distinct follower and request helpers.
This is a proposed recovery organization, not an original-TU identity claim.

The basic native destructor reproduces all 88 bytes, including automatic Base
cleanup and the deleting protocol. The task and existing 104-byte constructor
also match. Its compiler vtable naturally follows the existing entry records,
descriptor and status-string pointers. Primary text/data are 752/244 bytes;
legacy suffix text/data are 1092/176 bytes with the same eight-byte conversion
pool. Every byte and resolved text/data relocation matches its corresponding
slice of the old complete 1844-byte text and 424-byte data image.

The initial native renderer conversion swaps two saved registers. Its existing
80-byte C-named implementation can instead be retained byte-for-byte as the
established target-ABI virtual entrypoint, with no new wrapper or pointer view.
That boundary remains qualified; the probe does not establish a complete native
C++ renderer definition or portable whole-class recovery.

The compiler table has four function relocations and is 24 bytes at
[804CE8FC,804CE914). The old manual table also spelled a zero word at
[804CE914,804CE918). The proposed partition preserves that exact word through
an explicit original-only input, followed by the unchanged follower data and
jump table. The full candidate build retains the original DOL hash. The suffix
source object is independently exact but was not added to the linked-unit list.

There is still a substantive stop: the former source-linked word becomes
original-only, losing four matched data bytes. Even after activating the exact
suffix, that word would remain a four-byte linked-data regression. The probe's
report check rejects the data loss; temporary suffix linkage differences are
separate from this ownership problem. Zero bytes and adjacent alignment do not
prove whether the word was padding or a distinct object. No source padding
object, fictitious slot, ownership claim, catalog deletion or regression waiver
is introduced to make the check pass.

Further progress needs independent ownership evidence for this word, or an
explicitly authorized change to the no-regression requirement. Until then the
published complete ComCard source and its 424-byte data provider are restored.
The follower constructor's conversion-pool hold remains unchanged.

## Restored validation and standing limits

Independent read-only review checked both routes and supported these stop
conditions. After restoration, the capacity-gated full build reproduces DOL
SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr against
8b0f passes with zero metric, provider or address-coverage change. Retention and
port inventories remain clean. Main remains 4bec40d6.

Raw Base/Addition calls remain sixteen across nine units, with three shared
bindings. DD/Word/nameplate original providers, incomplete status consumers,
protected remainders, and all lifetime/ownership/constant/initialization holds
remain. No exhausted renderer probe is repeated. The PR stays draft and the
proposed PR split remains pending its separate decision.

A later [standalone render-body recovery](window-com-card-render-member.md)
reproduces the entire ComCard object using the established explicit receiver
contract. It does not activate the held data partition or establish ownership
of the trailing word; the partition stop condition above remains unchanged.

The later [Status/PageIndicator integration](window-status-page-stack-integration.md)
records upstream #420's reviewed exact initializer and the combined current-main
build. That supersedes this historical missing-page probe/provider hold, while
the unchecked rank index and all ComCard word/table ownership holds remain.
