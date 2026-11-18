#ifndef PSO_NETWORK_NETWORK_REQUEST_RUNTIME_H
#define PSO_NETWORK_NETWORK_REQUEST_RUNTIME_H
#include "types.h"
#include "pso/network/DnsQuery.h"

/* Shared native request/fragment interfaces. DNS layouts are checked in
 * DnsQuery.h; the fragment prefix remains in LobbyNetworkInternal.h. */
struct E_804196EC;
extern "C" {
s32 NetDnsBuildQueryAAAA(DnsQuery *query, u8 *name, s16 length);
s32 NetDnsBuildQueryA(DnsQuery *query, u8 *name, s16 length);
s32 NetConnectionCloseAndReset(DnsQuery *connection);
void NetDispatchRequestCallback(DnsQuery *connection, s16 status);
s32 NetResetOtherFragmentLists(E_804196EC *entry);
}
#endif
