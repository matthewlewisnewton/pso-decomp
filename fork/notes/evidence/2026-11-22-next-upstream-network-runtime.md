# Recover native PPP, modem, and packet receive interfaces

The local review branch `great-merge/review/network-runtime` ends at `3dd55d81fcb82618a032de944c152d5aa842597b` and starts directly on upstream master `b2d2912058829d0f0c9260f6272dc2a303c90110`. The diff contains 55 source, header and configuration paths with 1,153 insertions and 1,131 deletions. All three commits use the configured fork author and committer.

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

Give the network stack the native types for transport and PPP setup, modem callbacks, and packet delivery. Callers share the SDK queue and callback declarations through the original C and C++ owners.

- Transport uses the three original SDK queue layouts and typed thread, alarm and mutex slots. The modem dispatch reads the original command and settings fields.
- LCP, IPCP, PAP, CHAP and IPv6CP share typed frame, configure and timer callbacks. The IPCP implementation uses its native compression state.
- Raw IPv4, raw IPv6 and UDP delivery share the leading receive record. TCP send uses native fragment fields, and DHCP uses typed messages for Discover, Request, Release and reply processing.

Start with `NetworkRuntimeSlots.h`, `PppFsm.h` and `NetworkReceiveCallback.h`. The four linker label changes follow the recovered callback signatures and modem status output.

### Validation

- GPOE8P builds at each commit with retail DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- `tools/check_pr.py` passes against upstream master with 27,572 exact functions, 2,446 exact linked units and zero code or data coverage losses.
- Eleven runtime suites pass. They exercise SDK queue and startup behavior, modem scripts, PPP framing and negotiation, IP receive dispatch, DHCP record handling and 4,926 TCP queue comparisons.
