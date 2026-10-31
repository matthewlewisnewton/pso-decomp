# Fresh main coverage — 2026-10-31

Main: `8b2bed362369acac93353019a3ef57870eaf4e70`. Starting fork baseline: `623d9415a5edb3e27c686135385dcf98b5fa36bc`.

Fresh report regenerated from the exact successful PR114 pilot build; all 8,776 object files were rehashed unchanged. Original DOL verification and current original-address/source-link checks pass. No extra clean build was needed.

| Metric | Starting baseline | Current main | Absolute delta |
|---|---:|---:|---:|
| Matched functions | 27,223 / 27,572 (98.7342%) | 27,248 / 27,572 (98.8249%) | +25 |
| Matched code bytes | 4,101,056 / 4,353,092 (94.2102%) | 4,116,324 / 4,353,092 (94.5609%) | +15,268 |
| Matched data bytes | 1,276,059 / 1,761,407 (72.4454%) | 1,288,019 / 1,761,375 (73.1258%) | +11,960 |
| Source-linked code bytes | 3,196,360 / 4,353,092 (73.4273%) | 3,330,428 / 4,353,092 (76.5072%) | +134,068 |
| Source-linked data bytes | 920,643 / 1,761,407 (52.2675%) | 938,775 / 1,761,375 (53.2978%) | +18,132 |
| Source-linked units | 3,539 / 5,087 (69.5695%) | 3,538 / 5,067 (69.8244%) | -1 |

Actual link inputs: **3,538 source + 1,529 original-object fallbacks = 5,067**. Original-object fallbacks are not counted as newly recovered source.

Matched coverage includes exact compiled functions/data in units that may still use original-object fallback. Source-linked coverage separately measures selected source objects.
Unit counts change with translation-unit consolidation; the net linked-unit count decrease from 3539 to 3538 is not source coverage loss. Address-based preservation passes.
Current data denominator is 32 bytes smaller: eight 4-byte padding ranges are no longer counted. Both original and current denominators are supplied.
Starting baseline is a retained verified report, not regenerated today. Its source config pins objdiff v3.6.1 and schema matches; its historical executable SHA256 was not recorded. Both reports were compared today by the same current address-check tooling.
Detailed reports, object hashes, build logs and original inputs remain local. This published summary contains aggregate metrics, source addresses and tool hashes only.

Current generator: `objdiff-cli 3.6.1`, report schema 2. Commands, exact tool/report hashes, denominators and padding addresses are in [coverage-summary.json](coverage-summary.json).

[Passing post-main source CI](https://github.com/matthewlewisnewton/pso-decomp/actions/runs/41241180024). Full binary validation ran locally; this source CI result is not a hosted binary-build claim.
