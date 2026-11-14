# Keyboard Control text forwarding

This follows PR #268 checkpoint `9d18ddcacadaf30525a901fa38f4c8f41ebf38ef`.
The two historical text-getter declarations actually forward a borrowed byte
string through Control and its composer into embedded text-record storage.
The forwarding contract is now explicit; complete record identity, capacity,
storage aliasing and broader Soft keyboard interfaces remain qualified.

## Original call and receiver evidence

An all-section reference scan of the original objects finds nine direct,
zero-addend text calls to 80131BA0, one from there to 8025C5F4, and one from
there to 8008081C. There are no other-section or address-taking references.
Every outer caller supplies its text pointer in r4 and discards r3 afterward.
The serial and CMName integer-return declarations do not represent result use.
The wrappers' incidental preservation of r3 does not establish a getter result.

The nine calls are two MakeTeam, two SubComCard and one each from ShortMail,
InformationBoard, SymbolChat, serial input and CMName. Their existing producers
allocate 0x2C and initialize Control; field 0x20 holds the evidenced 0xB8 composer.
Original 80131BA0 loads that field and forwards r4 unchanged. Original 8025C5F4
adds 0x6C to its composer receiver and forwards r4 unchanged. The lower setter
accesses a text record's buffer at 0, cursor at 4 and length at 0x10.

Control::set_text(char*) and TWindowKeyBoardBase::set_text(char*) are native void
members at those two existing 36-byte addresses. The composer passes &m_6c into
the lower helper. All nine calls now supply their text argument explicitly;
the serial setter's incompatible function-pointer cast and obsolete local
prototypes are removed. Existing borrowed-text getters retain their own qualified
interfaces and emission-free pointer views.

The lower helper keeps its historical symbol through KeyboardTextAbi.h as an
ordinary C function taking void* record storage and char* text. Its definition
retains the exact existing Kb_8008081C prefix and body. It no longer claims to be
a complete Soft-window member. No nontrivial holder class or native embedded
lifetime is invented, and no ownership transfer is implied.

Cursor/length reset still precedes null handling. Language-prefix early returns,
Japanese byte decoding, buffer writes, termination, pointer advancement and
allocation/null assumptions are unchanged. No capacity check or speculative
initialization is added. The leaf's early returns and lack of an established
result, together with all observed callers, support the bounded void protocol.

## Exact-object qualification

The two wrappers are independently exact at 36 bytes each and the lower setter
at 224 bytes. Nine selected source objects retain complete original text and
resolved text relocation targets: Control wrapper owner288, composer helper
owner4788, text-record helper owner2196, serial1512, ShortMail5828,
SubComCard13404, MakeTeam1188, InformationBoard408 and SymbolChat8084.
All changed compiled objects retain their prior allocated headers, flags, sizes,
alignment, data/constants and resolved text/data relocation targets. No new table,
data ownership, split, compiler control or source activation is introduced.

CMName is checked separately. Its compiled15504 text, relocations and allocated
sections remain unchanged from 9d18; the original17988 provider remains selected
once and compiled source stays absent from executable inputs. Changed run_task556
bytes and every call target match original, while the same eight pre-existing
SDA21 constant-target differences and unrecovered code remain held. This is not
complete CMName object equivalence or source activation.

## Integration, validation and remaining work

Main `25b4001837b8bdc46666d2ad736a7148a411f978` is integrated by clean merge
`c2cc6767f159b3bff7899a23eefdad3756839c2c`. Its Moja source/data changes are
qualified against a separately built isolated baseline; they are not attributed
to this zero-metric text-forwarding family.

Both isolated full builds preserve DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr passes against published
9d18 and fresh main25b; retention remains clean at 17,882 and port inventory
passes unchanged. The first honest native probe matches all ten complete texts;
there are no failed scheduling variants or compiler/output controls.

Main contributes +688 matched code, +836 linked code and +736 matched/linked data
bytes, one exact function and a one-unit source inventory fold. This family adds
two catalog renames with no metric or source-link delta. Current totals are
27,404 exact functions, 3,585 exact linked units and 3,641 source-bearing units.
Combined PR deltas versus fresh main remain +600 matched code, +1220 linked code,
+1496 matched data and +1452 linked data bytes. The fourteen previously qualified
four-byte zero alignment ranges are unchanged.

Position/depth, Snapshot, WS_Word and protected-original provenance checks pass
again, including the original 1,044-byte helper and WS_Word's full original3,412
provider/missing916 renderer. No existing matched object or meaningful data range
is lost. Independent source review found no actionable issue; final publication
also requires review of this evidence and the exact candidate head.

This resolves the observed outer text-getter argument/return mismatch only.
Record capacity/storage aliasing, complete Soft-window recovery, CMName,
remaining native lifetimes, Parts constants, ChoiceSetting producer, task-global
word, callback/renderer/depth protocols and protected original remainders retain
their documented holds. Raw Base/Addition calls remain 22 across 12 units and
four shared bindings. The PR stays draft.
