# w2-particles

Ported ParticleBallistic, ParticleOrbit and ParticleRadial from the fork.

- Radial: already 100% matching here. It was blocked only by a duplicate
  `clear_active_flag__13TParticleCtrlFv` definition (0x80088000 is owned by
  TParticleCtrl_800874F4). Removing it from Radial, Orbit and Ballistic fixed
  the symbol and the .text size (4220 vs 4236, 6144 vs 6160, etc.).
- Ballistic/Orbit `run_task`: the fork's bodies matched here after bringing in
  how the fork wrote them: `f32 t[2]` / `f32 ch[3]` (Ballistic) and
  `envelope[2]` / `channels[3]` (Orbit) arrays declared in that order preserve
  FPR allocation; the packed ARGB colour is written byte by byte through a
  local u32 (`reinterpret_cast<u8 *>`); `fade_in`/`fade_out` initialised after
  the first statements; fp_contract on for the colour interpolation.
  Orbit's `orbit`/`rise` vectors are written x, z, y.
- Orbit/Ballistic `.sdata2`: the 8-byte `{360.0f, 0.0f}` object
  (lbl_805D9520 / lbl_805D9550) must be defined in the unit with
  `__declspec(section ".sdata2")` and the 360.0f in the random-angle code read
  from element 0, otherwise .sdata2 was 95.65%.
- Fork's `-pool off` entry for Ballistic was already present in configure.py.
- Not needed: cw_align, symbol_mappings.
