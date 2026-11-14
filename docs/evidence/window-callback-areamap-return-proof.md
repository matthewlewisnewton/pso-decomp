# Area-map return: one concrete indirect callback-owner gate

Checkpoint based on `e7acba06c854b22c8662e5ce267ab79309c78c24`, whose hosted
source checks passed. Literal live main was `1712bd56c8bc24956dc6279019c0dda0fc577f8c`
at the start of this pass. No integration, native rebuild or readiness change.

## Receiver and original-code anchors

The 1P table at 804D3078 places vfunc_9 at +0x24 (two initial words, destructor,
run_task, render, shadows, then slots 6–9). This is not inferred from the name of
a placeholder C++ virtual method.

For menu selections 12/13, create_submenu passes the menu itself as constructor
argument r4 at 80264320 and calls AreaMap's constructor at 80264324. The constructor
calls TObject at 8027159C with that parent and saves it in AreaMap +0x20 at
802715B8. On its tested input condition, AreaMap::run_task loads that same field
at 802714E4, loads the receiver table +0x18, then table slot +0x24 at 802714EC and
calls it at 802714F4. For a MainMenu1P parent, this resolves to vfunc_9 at 802883EC.
The source's placeholder `m7()` name is therefore not the target's actual menu
method number. MainMenu4P parents have a different slot target and are outside
this 1P transition proof.

## Bounded ordinary-path proof

Assume: (1) a normal parent-task terminal selection creates the AreaMap while the
old transition is a child of the same menu; (2) both remain in that list without
reparenting or other intervening mutation; (3) the normal parent task is followed
by its child traversal; (4) the queued old transition is destruction-enabled at
that visit; (5) destructor/constructor side effects do not reentrantly replace the
menu generation. This is a path-specific proof, not proof these assumptions hold
for every call in the program.

TObject construction appends to the parent's child-list tail, not its head. The
old transition therefore precedes the new AreaMap. create_submenu queues that old
transition before constructing AreaMap. When the parent returns, its child
traversal reaches and deletes the queued transition before it can run AreaMap's
task. Only later can AreaMap invoke the parent's return gate and cause a new
transition publication. For this path the old transition destructor's global
clear precedes new publication; the hypothesized old-transition-clear-after-new-
publication overlap is excluded under the assumptions above.

A second ordering detail is useful: run_tasks caches the next pointer before
running a task. AreaMap's return gate queues AreaMap itself and appends the new
transition. If AreaMap was last when entered, the cached next pointer remains
null: the appended transition is not run in that same traversal. AreaMap is not
synchronously deleted by that gate or rechecked after its task. If other siblings
follow it, later traversal can differ; no universal one-frame delay is claimed.

## Explicit exceptions and remaining work

This does not cover direct/reentrant gate calls outside this normal child walk,
reopen via vfunc_6, other submenu implementations, removed/reparented nodes,
mutation during teardown, or destruction-disabled transitions. In particular,
the original queued-node branch clears its queue flag before checking destruction
disablement; a disabled case must not be represented as a guaranteed future
retirement. Existing callback windows on separate roots, deferred-render reachability
and singleton use after another publication remain separate obligations.

Next cheapest discriminator is the corresponding receiver trace for the reopen
slot and the other +0x24 submenu return callers. An opcode-offset candidate search
is not a complete receiver census and must not be presented as one. No source
fix is justified by this bounded exclusion; preserve original behavior.

## Validation

Original and retained compiled complete .text sections are equal for AreaMap
(828 bytes), MainMenu (1468), and TObject (6096). This checks those retained text
artifacts, not fresh compilation, relocations or a current-main integrated build.
`window-callback-areamap-order-model.py` passes the supported-order case plus two
assumption-sensitivity cases (head insertion and disabled retirement). It models
only the described traversal fragment, not game execution or complete TObject
semantics. No proprietary artifacts are included. Production source is untouched.

Independent read-only review passed the original receiver/slot, tail-insertion,
conditional ordering proof and all three model cases. No global hold was lifted.
