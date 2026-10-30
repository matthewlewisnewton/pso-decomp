# Player target-candidate evidence (work in progress)

The player collector at `0x800BB484` writes an eight-byte record for each
candidate: a 16-bit entity ID at offset `0`, followed by a squared horizontal
distance as a float at offset `4`. The copy routine at `0x800BB650` copies the
16-bit ID and float separately; it does not copy the two intervening bytes.
For a positive floating-point threshold, the collector includes only candidates
whose squared distance is strictly smaller. A zero or negative threshold disables
that filter. The resulting records are sorted by ascending distance.

This layout is distinct from `EnemyTargetCandidate`, used for Gyaranzo, which
has a **32-bit** ID at offset `0` and a float at offset `4`. Their equal sizes
do not make their ID fields interchangeable on big-endian PowerPC.

The `PlayerTargetCandidate` name is descriptive, not an established original
name. The ID is declared unsigned because `get_entity_id` returns `u16` and
callers including Recon consume it as `u16`; the collector's current local
structure uses `s16`, but only stores the 16-bit result. The collector definition
and copy routine still use their earlier local declarations. The collector receives its actor and output pointers in `r3` and `r4`, and
the squared-distance limit in `f1`. Reconciling its existing declarations
remains work for a later matching change. An earlier copy-routine conversion
changed its generated instructions. Existing callers and the collector wrapper
retain other pre-existing overlays and calling-convention questions.
