# Audio header parsing and ADX block transfer

Unit: `pso/misc/TLobby_803C1A58.cpp`, `.text` `0x803C1A58..0x803C45E4`
(end exclusive), 11,148 bytes; `.bss` 2,944 bytes (the existing 16-entry,
0xB8-byte channel-record pool). Initial recovery baseline:
`e9b77fcfdcc2335c9a5a92886826022c80505e67` on the fork's `main`.
The publication branch is rebased onto the immutable fork base
`1b43a2deec8837c23c889e9c859855cc1fd455df`;
validation compares both this base and the initial recovery baseline.

The remaining three functions are now exact C++:

| Address | Function | Bytes | Evidence |
|---|---|---:|---|
| `803C2388` | `TLobby__sub_803C2388` | 624 | FORM/AIFF tags, COMM channel/frame/sample-width/rate fields, SSND offset |
| `803C32EC` | `fn_803C32EC` | 520 | `.snd` magic and big-endian offset, byte count, encoding, rate and channel count |
| `803C3570` | `TLobby__sub_803C3570` | 1,028 | ADX decoder submission/completion and planar PCM ring-buffer wrap copies |

The SND routine previously carried the unrelated name `GXSetCopyFilter`. Its
only source caller is the format-header dispatcher at `803C30E8`; the real
`Dolphin_GXSetCopyFilter` is unchanged. The two remaining address names and the
unit's legacy TLobby attribution are not claims of recovered original ownership.

## Source provenance and experiments

The SND implementation and initial AIFF body were adapted from this project's
upstream commit [13186af0b243af1f12abb9f4a1b333bbab93adc7](https://github.com/zeroz41/pso-decomp/commit/13186af0b243af1f12abb9f4a1b333bbab93adc7),
by zeroz, originally in `src/pso/unk/TLobby_803C1A58.cpp` (matchpass 16).
The ADX transfer was recovered from the original instruction/control-flow and
callee evidence. No asset data, generated assembly, compiler patch or external
implementation is added.

The [WAVE parser investigation](wave-header-parser-evidence.md) motivated
unsigned high-byte shifts and checking the native expression type rather than
casting every operand unsigned. The latter changed both parser instruction
sequences. The final macros avoid signed high-byte left shifts while preserving
the native `int` result of the byte assembly. AIFF reuses its tag and chunk-size
locals across the FORM header and chunk loop. Its scoped propagation/CSE controls
preserve the original load, byte-swap and pointer-update sequence.

The [cast-technique investigation](cast-technique-6x47-register-allocation.md)
and [Moja compiler trace](moja-compiler-tracing.md) guided the remaining ADX
register-allocation work. A local unmodified-MWCC debugger trace exposed the
allocation order: the three completion values must precede the submission-phase
locals to obtain the original saved-register reuse. The rounded block limit is
kept separate from the adjustable wrap limit; a named space value is calculated
before subtracting the final-block tail. Passing the stereo right destination
as an expression avoids extending a redundant pointer's lifetime. The ordinary
forward sample-copy loops are automatically unrolled by the native compiler.

Trials with other compiler versions and processor settings did not solve the
remaining allocation difference. The final unit uses the repository's existing
GC/2.6 Gekko configuration, with function-local propagation/CSE controls and
lifetime control for the ADX transfer. No per-unit flag override is added.
These observations explain emitted code, not the unknown original source.

## Record and callback boundary

`AdxBlockTransferView` is a local, bounded 0xA8-byte prefix. Native offset and
size assertions cover every accessed member. Unknown bytes remain reserved.
The dispatcher reads its format at 0xA8 through the existing shared view.

| Offset | Meaning / evidence |
|---|---|
| `04`, `08` | transfer state and decoder pointer |
| `40`, `44` | wrap length and right-channel offset in 16-bit samples |
| `50`, `54` | encoded source and available encoded block count; initializer `803C3A24` divides input bytes by the encoded block size |
| `58`, `5C`, `60` | channel count, encoded bytes per block, decoded samples per block |
| `64..78` | PCM buffer, capacity, channel stride, position, available samples and remaining samples |
| `88`, `8C` | reader callback and context; writes position/available/remaining through three pointers |
| `90`, `94` | completion callback and context; receives encoded bytes consumed and decoded sample count |
| `A0`, `A4` | completed samples and encoded bytes consumed |

The decoder's shared interface still has legacy `TLobby` member names.
`AdxStreamRuntime.cpp` shows that `post_request`/`try_post_command` store the
encoded input, block count and PCM destinations; `update_receive_check` calls
the mono/stereo ADX block decoders; `get_size` returns completed blocks and
`get_client_count` returns decoder state. This recovery uses those existing
shared declarations without fabricating a new class or changing their ABI.
The pointer-to-`s32` arguments reflect that pre-existing 32-bit native boundary;
a port should replace it with typed decoder pointers and fixed-width state.

The parsers retain the original validation order and malformed-input behavior;
this is not parser hardening. In particular the AIFF COMM/SSND traversal and
sample-rate shifts, and SND channel division, retain the original assumptions.
The transfer likewise assumes valid channel counts, block sizes and buffers
provided by the existing initializer and callbacks.

## Validation

The complete native object has 46/46 exact functions, 11,148/11,148 exact code
bytes and 2,944/2,944 exact data bytes. Baseline was 43/46 functions and
8,976/11,148 code bytes, with the same exact data. Linking this unit adds all
46 functions, 11,148 code bytes and 2,944 data bytes to source-linked coverage.

Validation uses fresh split objects from the checked-in symbol configuration,
original inputs copied independently into this worktree, and the pinned native
tools. Whole-object section/layout/global/relocation checks, generated retention,
the full native build and address-based `tools/check_pr.py` cover the final
source and linkset. The 91 normalized relocations and both allocated sections compare identically
between the original split and compiled object. The link command selects
`build/GPOE8P/src/pso/misc/TLobby_803C1A58.o`. Generated retention adds 22 names
and removes none. The full source-linked build and `check_pr.py --no-build`
pass with no coverage losses. The original DOL SHA-1 is
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.
