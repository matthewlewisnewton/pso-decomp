#ifndef PSO_NETWORK_NETWORK_RECORD_CONFIG_H
#define PSO_NETWORK_NETWORK_RECORD_CONFIG_H
#include "types.h"

/* Verified native configuration prefixes. The address-qualified opaque views
 * deliberately retain unresolved field ownership rather than invent a class. */
struct Obj_803F87E0;
struct Cfg_803F8868;
struct RecoveredFields_803F88E4_arg0;
struct NetConfig_803F895C;
struct NetConfig_803F8A28;
struct Desc_803F8AD8;
struct NetConfig_803F8B7C;
struct Cfg_803F86C0;
extern "C" {
void NetInitIpv6InterfaceConfig(Obj_803F87E0 *self);
void NetInitUdpSocketConfig(Cfg_803F8868 *self);
void NetInitBufferDescriptorB(RecoveredFields_803F88E4_arg0 *self);
void NetInitBufferDescriptorA(NetConfig_803F895C *self);
void NetInitNetworkBufferConfig(NetConfig_803F8A28 *self);
void NetInitFunctionTable(Desc_803F8AD8 *self);
void NetInitReceiveDescriptor(NetConfig_803F8B7C *self);
void NetInitNetworkConfig(Cfg_803F86C0 *self);
}
#endif
