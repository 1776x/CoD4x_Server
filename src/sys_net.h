/*
===========================================================================
    Copyright (C) 2010-2013  Ninja and TheKelm
    Copyright (C) 1999-2005 Id Software, Inc.

    This file is part of CoD4X18-Server source code.

    CoD4X18-Server source code is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    CoD4X18-Server source code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
===========================================================================
*/

#ifndef __SYS_NET_H__
#define __SYS_NET_H__

#include "q_shared.h"
#include "cvar.h"
#include "sys_net_types.h"

/*
==============================================================

NET

==============================================================
*/

void		NET_Init( void );
void		NET_Shutdown( void );
void		NET_Restart_f( void );
void		NET_Config( qboolean enableNetworking );
void		NET_FlushPacketQueue(void);
qboolean	NET_SendPacket (netsrc_t sock, int length, const void *data, netadr_t *to);
void		QDECL NET_OutOfBandPrint( netsrc_t net_socket, netadr_t *adr, const char *format, ...) __attribute__ ((format (printf, 3, 4)));
void		QDECL NET_OutOfBandData( netsrc_t sock, netadr_t *adr, byte *format, int len );
void		NET_RegisterDefaultCommunicationSocket(netadr_t *adr);
netadr_t*	NET_GetDefaultCommunicationSocket(netadrtype_t family);
qboolean	NET_CompareAdr (netadr_t *a, netadr_t *b);
qboolean	NET_CompareBaseAdrMask(netadr_t *a, netadr_t *b, int netmask);
qboolean	NET_CompareBaseAdr (netadr_t *a, netadr_t *b);
qboolean	NET_IsLocalAddress (netadr_t adr);
const char	*NET_AdrToString (netadr_t *a);
const char	*NET_AdrToStringMT (netadr_t *a, char*, int);
const char	*NET_AdrToStringShort (netadr_t *a);
const char	*NET_AdrToStringwPort (netadr_t *a);
netadr_t	*NET_SockToAdr(int socket);
const char	*NET_AdrToConnectionString(netadr_t *a);
const char	*NET_AdrToConnectionStringShort(netadr_t *a);
const char	*NET_AdrToConnectionStringMask(netadr_t *a);
int		NET_StringToAdr ( const char *s, netadr_t *a, netadrtype_t family);
//qboolean	NET_GetLoopPacket (netsrc_t sock, netadr_t *net_from, msg_t *net_message);
void		NET_JoinMulticast6(void);
void		NET_LeaveMulticast6(void);
__optimize3 __regparm1 qboolean	NET_Sleep(unsigned int usec);
void NET_Clear(void);
const char*	NET_AdrMaskToString(netadr_t *adr);
const char *NET_AdrMaskToStringMT(netadr_t *a, char* buf, int len);
int NET_GetStaticIPv6Address(netadr_t* adr, unsigned int startindex);
__cdecl const char	*NET_AdrToStringShortMT(netadr_t *a, char* buf, int len);

qboolean	Sys_SendPacket( int length, const void *data, netadr_t *to );
qboolean	Sys_StringToAdr( const char *s, netadr_t *a, netadrtype_t family );
int 		Sys_StringToAdrNonBlock( const char *s, netadr_t *a, netadrtype_t family );
int NET_StringToAdrNonBlocking( const char *s, netadr_t *a, netadrtype_t family );


//Does NOT parse port numbers, only base addresses.
qboolean	Sys_IsLANAddress (netadr_t *adr);
void		Sys_ShowIP(void);

int NET_TcpSendData( int sock, const void *data, int length, char* errormsg, int maxerrorlen );
void NET_TcpServerPacketEventLoop();
void NET_TcpServerRebuildFDList(void);
void NET_TcpServerInit(void);
int NET_TcpClientConnect( const char *remoteAdr );
int NET_TcpClientConnectToAdr( netadr_t* adr );
int NET_TcpClientConnectFromAdrToAdr( netadr_t* destination, netadr_t* source );
int NET_TcpClientConnectFromAdrToAdrSilent( netadr_t* destination, netadr_t* source );
int NET_TcpClientConnectNonBlockingToAdr( netadr_t* adr );
int NET_TcpClientGetData(int sock, void* buf, int buflen, char* errormsg, int maxerrorlen);
void NET_TcpCloseSocket(int socket);
int NET_TcpIsSocketReady(int socket); //return: 1 ready, 0 not ready, -1 select error, -2 other error
const char* NET_GetHostAddress(char* adrstrbuf, int len);
int NET_GetHostPort();
netadr_t* NET_GetLocalAddressList(int* count);
qboolean Sys_IsReservedAddress( netadr_t *adr );

extern cvar_t* net_enabled;

#endif
