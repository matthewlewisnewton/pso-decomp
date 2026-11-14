# Native-table compilation context: an independent project control

This follows continuation `bf01124ee44b6eaf08ddab4ba90395fdd2b0683f` and
[Word's compiler observation](window-word-data-pool-observation.md). It tests an
already-recovered genuine class, rather than another Word layout or initializer.
The live focused/continuation heads and main `baa0b4e482` were unchanged at the
start; no competing branch update was observed. Word and all production profiles
remain untouched by this investigation.

## Independently recorded precedent

`pso/object/TObjFish_8033CCC8.cpp` owns the native
`TBoss6Demo11_TYPE1_DEAD` constructor/destructor and compiler-generated table.
Its local motion indices occupy eight data bytes, its origin twelve bytes, and
its four-function table twenty-four bytes. These are separate source objects in
one original data interval `[804EF9D8,804EFA04)`, not an invented aggregate.

The accepted recovery
[`3dbac85f07fd6384955af17b0c9a1f1aed5dca2d`](https://github.com/matthewlewisnewton/pso-decomp/commit/3dbac85f07fd6384955af17b0c9a1f1aed5dca2d)
already records `-inline off,deferred` and reverse definition order for this
specific unit. Its configure comment and the Falz death-cutscene entries in
[the exception register](../porting-exceptions.md) explicitly describe sharing
the motion/origin/table base and the separate conversion-constant ordering.
The later typed-caller change `21978410de` preserves that context. This precedent
therefore predates the Word observation; the investigation does not add a
compiler exception or infer a common original translation unit.

Word's corresponding original data contains its 36-byte entry record, eight-byte
position, twenty-byte descriptor and twenty-four-byte table in `[804EFC50,804EFCA8)`.
Its initializer references the latter three; the descriptor in turn refers to
the entry record. Similar address sharing is a relevant structural comparison,
not proof that the two units had the same original source order or options.

## Discriminating same-source control

Both lanes compile exactly the current accepted Fish source, SHA-256
`7cb6a4a7853697933075ec2c4db487c1b41324372cc3228b5cda13315f5bbeef`.
They keep its existing section annotations, weak capture/camera declarations,
ordinary native lifetime, constants and definition order. No new helper or
reference is introduced. Those existing linkage/section exceptions remain
qualified; this experiment does not remove or generalize them.

The production lane uses its recorded `-inline off,deferred`; the counterfactual
changes only that argument to `-inline off`. The remaining code-generation flags
are identical, including GC/2.6, `-O4,s` and `-sdata2 4`. The compiler and wibo
hashes are those recorded in the preceding Word observation.

Execution-only hardware breakpoints observe data declaration, function-generation
start, data-pool eligibility and anchor-reference addition. Runs hold the existing
legacy capacity gate and common debugger lock. Compiler code/data are not patched,
compiler helpers are not invoked, and neither source nor production configuration
is changed. Each lane has its own identical-options normal control. Both complete
traced ELF objects equal their normal controls byte for byte.

The production control additionally equals the currently selected compiled Fish
ELF byte for byte. Independent comparison against the original split object gives:

| Original owned section | Exact bytes |
| --- | ---: |
| .text, six functions | 1628 |
| .rodata | 200 |
| .data | 44 |
| .sdata | 8 |
| .sdata2 | 20 |

All 80 normalized original relocation records also match in offset, type and
resolved target including its addend. Generated local symbols resolve through their actual section offsets;
global catalog symbols resolve through original addresses. This is a whole-unit
original-byte/target comparison, not a percentage or merely matching constructor.
The production object is already selected once by the validated game build.

## Observed distinction

| Observation | Recorded production context | Immediate counterfactual |
| --- | --- | --- |
| Actual 24-byte native table declaration | Before all six function-generation starts | After all six starts |
| Table during constructor generation | Defined .data object with a pool root | Undefined symbol, size zero, no pool root |
| Eligible constructor objects in that data group | Table, origin, motion indices | Origin and motion indices |
| Group completion in this constructor | Count three, full | Count two, incomplete |
| Complete traced/control ELF identity | Pass | Pass |

The production trace observes the compiler's real table object entering the same
pool as the two local metadata objects, and the completed group's virtual register
41. The immediate control never gives the table a defined section root while the
constructor is being generated. This independently reproduces the mechanism found
in Word with a genuine compiler-managed lifetime and table.

The counterfactual also reverses the emitted function order and changes the
conversion pool order. Its constructor is 300 rather than 296 bytes and total
text is 1632 rather than 1628. These whole-output differences are not all
attributed to pooling. The timing and eligibility snapshots discriminate the
pooling cause directly. This counterfactual is not a proposed source/profile
change and receives no whole-game activation or DOL qualification.

## Reproduction and remaining boundary

Capture this unit's production command with the pinned Ninja `-t commands`
operation. Freeze the current accepted source and replay it in two scratch output
directories, varying only the `off,deferred`/`off` argument. Preserve its other
options and annotations. With the exact compiler pinned by the Word note, use
these four read-only hardware execution breakpoints in each run:

- `0x0050A460`: actual data declaration.
- `0x00433492`: function-generation start.
- `0x004D1247`: resolved symbol/section and data-pool eligibility.
- `0x004E09E0`: distinct anchor-reference addition.

Validate each complete traced/control ELF pair first, then production identity
against the selected compiled object and all original sections/normalized targets.
Private receipts, traces, objects and replay/verification scripts are in
`pr403-word-context-fish/`; no original-game binary, object or disassembly is
published with this note. Independent read-only review checks the control and its
bounded interpretation.

The result establishes an existing native-class mechanism and original-byte
precedent for early table availability. It does **not** establish Word's original
source organization, unit boundary or compiler profile. Applying this flag or
reversing Word definitions merely to obtain a match is not justified by the
analogy. Word would need its own independent provenance or a fully explained,
reviewed compilation-context reconstruction that preserves the entire owner,
all data/ctors, callers, original providers and complete linked validation.
No Word source/profile variant is attempted here. Native Word lifetime/table,
raw-storage and all other holds remain; there is no new coverage claim.
