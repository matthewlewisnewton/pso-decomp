#ifndef PSO_MISC_TUDPSOCKET_H
#define PSO_MISC_TUDPSOCKET_H

#include "types.h"

struct TUdpSocket
{
    static s32 handle_socket_event(s16 arg0, u8 *arg1);
    static void unlock_mutex(int _w0);
};

#endif
