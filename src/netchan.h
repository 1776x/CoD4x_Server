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


#ifndef __NETCHAN_H__
#define __NETCHAN_H__

#include "sys_net.h"
#include "msg.h"
#include "netchan_types.h"


//#define	MAC_STATIC			// be fragmented into multiple packets

//#define TRUNCATE_LENGTH	64

//#define CL_DECODE_START 0
//#define SV_DECODE_START 12
//#define SV_ENCODE_START 4
//#define CL_ENCODE_START 9


void Netchan_Init( int port );
void Netchan_Setup( netsrc_t sock, netchan_t *chan, netadr_t adr, unsigned int qport , byte* unsentBuffer, int unsentBufferSize, byte* fragmentBuffer, int fragmentBufferSize);
qboolean Netchan_Process( netchan_t *chan, msg_t *msg );
qboolean Netchan_TransmitNextFragment( netchan_t *chan );
qboolean Netchan_Transmit( netchan_t *chan, int length, const byte *data );
qboolean NET_GetLoopPacket (netsrc_t sock, netadr_t *net_from, msg_t *net_message);
void NET_SendLoopPacket (netsrc_t sock, int length, const void *data, netadr_t to);
qboolean NET_SendPacket( netsrc_t sock, int length, const void *data, netadr_t *to );
__cdecl void QDECL NET_OutOfBandPrint( netsrc_t sock, netadr_t *adr, const char *format, ... );
void NET_OutOfBandData( netsrc_t sock, netadr_t *adr, byte *format, int len );
void QDECL NET_PrintData( int sock, const char *format, ... );
qboolean NET_SendData( int sock, msg_t* msg);
int NET_TcpReceiveData( int sock, msg_t* msg);
void NET_CookieInit();
int NET_CookieHash(netadr_t*);

#endif