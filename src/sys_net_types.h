#pragma once
#include "q_shared_types.h"

#define NET_ENABLEV4 0x01
#define NET_ENABLEV6 0x02
// if this flag is set, always attempt ipv6 connections instead of ipv4 if a v6 address is found.
#define NET_PRIOV6 0x04
// disables ipv6 multicast support if set.
#define NET_DISABLEMCAST 0x08
#define PORT_ANY -1

#ifndef _WIN32
//#define SOCKET_DEBUG
#endif

typedef enum netadrtype_t
{
    NA_BAD = 0, // an address lookup failed
    NA_BOT = 0,
    NA_LOOPBACK = 2,
    NA_BROADCAST = 3,
    NA_IP = 4,
    NA_IP6 = 5,
    NA_TCP = 6,
    NA_TCP6 = 7,
    NA_MULTICAST6 = 8,
    NA_UNSPEC = 9,
    NA_DOWN = 10,
} netadrtype_t;

typedef enum netsrc_t
{
    NS_CLIENT,
    NS_SERVER
} netsrc_t;

#define NET_ADDRSTRMAXLEN 48 // maximum length of an IPv6 address string including trailing '\0'

typedef struct
{
    netadrtype_t type;
    int scope_id;
    unsigned short port;
    unsigned short pad;
    int sock; //Socket FD. 0 = any socket
    union {
        byte ip[4];
        byte ipx[10];
        byte ip6[16];
    };
} netadr_t;

typedef enum tcpclientstate_t
{
    TCP_AUTHWAIT,
    TCP_AUTHNOTME,
    TCP_AUTHBAD,
    TCP_AUTHAGAIN,
    TCP_AUTHSUCCESSFULL
} tcpclientstate_t;
