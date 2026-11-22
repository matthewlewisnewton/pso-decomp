# Recover native PPP, modem, and packet receive interfaces

The current 63-file standalone review is `great-merge/review/after-370/network-runtime` at `93e3933edb` on upstream master `d8c0a969d2`. It also builds cleanly above PR #371 at `6da1100681`. Both builds reproduce retail, preserve all 27,572 exact functions, and account for the original 1,147 data bytes. The benchmark reports 483 fewer findings and zero flagged symbol labels in both builds. The standalone revision passes 14 runtime suites. [Validation for both builds](2026-11-22-upstream-370-network-review-validation.json)

## Previous validations

The standalone network review is now `7f33369109` on upstream `6aee940eca`. It passes the full matching build, 11 network suites, and the list, packet copy, and UDP callback probes. The same source applies cleanly above the window review and matches retail at `c02dcaa95d`. [Current validation](2026-11-22-upstream-367-network-memory-validation.json)

The 60-path review `3d2429fcbd` on `2ea1c02d4c` also restores native game and lobby list assignment and copies the packet header as bytes. Its exact build, 15 protocol-list cases and 10 packet copy and collision checks pass. The next revision is being replayed onto upstream PR #367. [Assembled queue validation](2026-11-22-upstream-366-assembled-queue-validation.json)

The current standalone review is `great-merge/review/after-366/network-runtime` at `72703eff0b` on upstream `2ea1c02d4c`. Applying that same patch above the expanded window and combined actor reviews yields `8b22ee1626`. The stacked build matches retail, passes the coverage comparison, and passes all eleven network probes. [Current validation](2026-11-22-upstream-366-actor-and-network-review-validation.json)

The previous standalone review branch `great-merge/review/network-runtime` ends at `3dd55d81fcb82618a032de944c152d5aa842597b` and starts directly on upstream master `b2d2912058829d0f0c9260f6272dc2a303c90110`. The diff contains 55 source, header and configuration paths with 1,153 insertions and 1,131 deletions. All three commits use the configured fork author and committer.

The same patch applies cleanly after the local window and actor reviews. The queue application was checked against `5c9df48dbc73d4d930271b895172e983d42c1a70`. The build and runtime results below cover the branch on upstream master.

## Commit sequence

- `8ffff0369a` Native SDK queues, lobby allocation, modem callbacks and the modem command script.
- `5386be6b61` Thread, alarm and mutex slots, PPP startup, frames, configuration, authentication and compression.
- `3dd55d81fc` Shared raw IPv4, raw IPv6 and UDP receive records, typed TCP fragments and DHCP builders and reply handling.

All three commits reproduce the retail executable byte-for-byte. The final build matches 27,572 functions, links 2,446 exact source units, and preserves all 1,147 historical data bytes across 90 ranges. The range audit accounts for 980 linked bytes and 167 alignment bytes.

| Address | Function | Source change |
| --- | --- | --- |
| `0x80078378` | `TUdpSocket::handle_socket_event` | Takes the shared receive record prefix. |
| `0x8042BF48` | `TAdSinglePlyChrSelectGC::wake_load_thread` | Takes the EXI channel and OS context arguments. |
| `0x8042E768` | `copy_default_and_get_state` | Takes a typed modem status output as an ordinary C function. |
| `0x8042E84C` | `TAdSinglePlyChrSelectGC::send_modem_hangup` | Uses the SDK reset handler signature. |

## Evidence

| Artifact | SHA-256 |
| --- | --- |
| Upstream and review build comparison | `515b075f1142ba7ed8dc0f21fc2c886006e180cd71672e86d09d10990d6cf357` |
| Review build report | `eec6186c3dcfd28129c217b1a84ab505f48987d14acfbb637032bfbb64f02ca6` |
| Results for all 11 runtime suites | `0b44145a4a77a90cfb3c758ce359e995bdb857256e9ee9bb7504d735f74001b6` |
| Retail hashes for each commit | `2ec0eedf623a7e3bd879a51b3eb6fdc2df846ef3461d4080e13c03de354821d7` |

## Proposed PR description

### Summary

Recover the native network interfaces for dispatcher setup, transport, modem commands, PPP negotiation, and packet delivery. The existing C and C++ callers share typed SDK records and callback declarations.

- The dispatcher uses the SDK queue, mutex, alarm and thread records and posts the native 12-byte protocol message. Queue and thread handles use the original SDK types.
- LCP, IPCP, PAP, CHAP and IPv6CP share typed configuration, timer and frame callbacks. The IPCP path uses the original compression state.
- Raw IPv4, raw IPv6 and UDP delivery share the socket, length and buffer prefix. UDP retains its source, destination and port fields. TCP uses the original send fragments, and DHCP builders and reply paths use typed messages.
- The modem uses its real EXI wake and reset callbacks, editable command storage and typed status output.

Start with `NetworkDispatch.h`, `NetworkRuntimeSlots.h`, `PppFsm.h` and `NetworkReceiveCallback.h`. The four linker label changes follow the shared receive prefix, the EXI and SDK reset callback signatures, and the typed modem output. The recovered declarations retain existing address-named types and globals. PPP callback slots use their original offsets and typed members, and two context reads still use the corresponding byte offsets.

### Validation

- GPOE8P reproduces retail DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3` with 27,572 exact functions.
- `tools/check_pr.py` passes with zero code or data coverage loss. The standalone build links 2,416 exact units and retains all 1,147 original fork data bytes.
- The source-quality benchmark reports 483 fewer findings overall, zero flagged symbol labels and zero newly stale retention entries.
- Fourteen runtime suites pass. Coverage includes dispatcher startup failures and message layout, SDK queues, modem scripts, PPP frames and negotiation, UDP callbacks, DHCP and TCP queue behavior.
