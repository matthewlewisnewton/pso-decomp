# Recover native positional and one-shot sound interfaces

The local review `great-merge/review/after-367/positional-and-one-shot-sound` is at `91b3288a4dc2a0b7f510f7799f2bd13627c9b8b8` above the actor foundation `630ba942768fd37899c560ef96dc43a9d1a02a8a`. The source change spans 197 paths. [Validation](2026-11-22-upstream-367-sound-and-spawn-validation.json)

## Proposed PR description

Recover the native sound request interfaces shared by the mixer, voice slots, actor effects, and options window.

- Persistent sounds retain the actual source identity and position while the mixer allocates and reuses slots. Floor-dependent dispatch passes through the original result.
- One-shot callers use one shared declaration and pass the original position.
- Sound balance draws with the shared window context and passes the actual labels to text measurement.

The five linker-label changes follow the corrected signatures. The GPOE8P binary matches retail and `tools/check_pr.py` reports zero coverage or linkage losses. Runtime checks cover all 36 floor choices, slot allocation and reuse, lobby gain, pitch, and sound balance. All 195 persistent and 1,198 one-shot call sites retain the same compiled addresses.
