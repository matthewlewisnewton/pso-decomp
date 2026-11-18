#ifndef PSO_NETWORK_NETWORK_REQUEST_RUNTIME_H
#define PSO_NETWORK_NETWORK_REQUEST_RUNTIME_H
#include "types.h"

/* Shared native request/fragment records. Their checked layouts remain in
 * LobbyNetworkInternal.h; these interfaces do not imply TLobby ownership. */
struct F_8040A45C;
struct Conn_8040C540;
struct E_804196EC;
extern "C" {
s32 NetDnsBuildQueryAAAA(F_8040A45C *query, u8 *name, s16 length);
s32 NetDnsBuildQueryA(F_8040A45C *query, u8 *name, s16 length);
s32 NetConnectionCloseAndReset(Conn_8040C540 *connection);
void NetDispatchRequestCallback(Conn_8040C540 *connection, s16 status);
s32 NetResetOtherFragmentLists(E_804196EC *entry);
}
#endif
