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



#ifndef __SERVER_H__
#define __SERVER_H__

#include "netchan.h"
#include "q_shared.h"
#include "qcommon.h"
#include "sys_net.h"
#include "gentity.h"
#include "player.h"
#include "filesystem.h"
#include "g_hud.h"
#include "sys_cod4defs.h"
#include "cvar.h"
#include "net_game_conf.h"
#include "cm_public.h"
#include "client.h"
#include "server_types.h"

#include "net_reliabletransport.h"

#include <time.h>

#define SERVER_STRUCT_ADDR 0x13e78d00
#define sv (*((server_t*)(SERVER_STRUCT_ADDR)))

#define SERVERSTATIC_STRUCT_ADDR 0x8c51780
#define svs (*((serverStatic_t*)(SERVERSTATIC_STRUCT_ADDR)))

#define SERVERHEADER_STRUCT_ADDR 0x13f18f80
#define svsHeader (*((svsHeader_t*)(SERVERHEADER_STRUCT_ADDR)))

#define CM_WORLD_STRUCT_ADDR 0x889efa0
#define cm_world (*((struct cm_world_t*)(CM_WORLD_STRUCT_ADDR)))


#define CLIENT_BASE_ADDR 0x90b4f8C


//*******************************************************************************


#define g_sv_skel_memory ((char*)(0x13F5A1C0))
#define g_sv_skel_memory_start (*(char**)(0x13F5A1A8))


int SV_NumForGentity( gentity_t *ent );
gentity_t *SV_GentityNum( int num );
playerState_t *SV_GameClientNum( int num );
svEntity_t  *SV_SvEntityForGentity( gentity_t *gEnt );
gentity_t *SV_GEntityForSvEntity( svEntity_t *svEnt );

//
// sv_client.c
//
void SV_ChallengeResponse( int );

void SV_PBAuthChallengeResponse( int );

void SV_Heartbeat_f( void );

void SV_ExecuteClientCommand( client_t *cl, const char *s, qboolean clientOK, qboolean inDl );

void SV_SendClientSnapshot( client_t *cl );

qboolean SV_Acceptclient(int);
client_t* SV_ReadPackets(netadr_t *from, unsigned short qport);
void SV_GetVoicePacket(netadr_t *from, msg_t* msg);
void SV_UserVoice(client_t* cl, msg_t* msg);
void SV_PreGameUserVoice(client_t* cl, msg_t* msg);
//void SV_BuildClientSnapshot(client_t* cl);
void SV_ArchiveSnapshot(msg_t* msg);

void QDECL SV_SendServerCommand_IW(client_t *cl, int type, const char *fmt, ...);
void QDECL SV_SendServerCommandNoLoss(client_t *cl, const char *fmt, ...);
void QDECL SV_SendServerCommand(client_t *cl, const char *fmt, ...);

__optimize3 __regparm2 void SV_PacketEvent( netadr_t *from, msg_t *msg );

void SV_AddServerCommand( client_t *cl, int type, const char *cmd );

void Scr_SpawnBot(void);

char*	SV_IsGUID(char* guid);

void SV_Shutdown( const char* finalmsg);

void SV_WriteGameState(msg_t*, client_t*);

void SV_GetServerStaticHeader(void);

void SV_ShowClientUnAckCommands( client_t *client );


void SV_WriteDemoMessageForClient( byte *msg, int dataLen, client_t *client );
void SV_StopRecord( client_t *cl );
void SV_RecordClient( client_t* cl, char* basename );
void SV_DemoSystemShutdown( void );
void SV_WriteDemoArchive(client_t *client);

void SV_SendClientVoiceData(client_t *client);

void SV_InitCvarsOnce( void );

void SV_Init( void );

__optimize2 __regparm1 qboolean SV_Frame( unsigned int usec );

unsigned int SV_FrameUsec( void );

void SV_RemoveAllBots( void );

const char* SV_GetMapRotation( void );

void SV_AddOperatorCommands(void);

__optimize3 __regparm1 void SV_GetChallenge(netadr_t *from);
__optimize3 __regparm1 void SV_AuthorizeIpPacket( netadr_t *from );
__optimize3 __regparm1 void SV_DirectConnect( netadr_t *from );
__optimize3 __regparm2 void SV_ReceiveStats(netadr_t *from, msg_t* msg);
void SV_SetClientStat(int clientNum, signed int index, int value);
int SV_GetClientStat(int clientNum, signed int index);
void SV_UserinfoChanged( client_t *cl );
void SV_DropClient( client_t *drop, const char *reason );
void SV_DropClientNoNotify( client_t *drop, const char *reason );
void SV_DelayDropClient(client_t *client, const char *dropmsg);
__optimize3 __regparm3 void SV_UserMove( client_t *cl, msg_t *msg, qboolean delta );
void SV_ClientEnterWorld( client_t *client, usercmd_t *cmd );
void SV_WriteDownloadToClient( client_t *cl );
void SV_SendClientGameState( client_t *client );

void SV_Netchan_Decode( client_t *client, byte *data, int remaining );
void SV_Netchan_Encode( client_t *client, byte *data, int cursize );
qboolean SV_Netchan_Transmit( client_t *client, byte *data, int cursize);
qboolean SV_Netchan_TransmitNextFragment( client_t *client );
void SV_SysAuthorize(char* s);
int SV_ClientAuthMode(void);
qboolean SV_FriendlyPlayerCanBlock(void);
qboolean SV_FFAPlayerCanBlock(void);
const char* SV_GetMessageOfTheDay(void);
const char* SV_GetNextMap(void);
void QDECL SV_EnterLeaveLog( const char *fmt, ... );


qboolean SV_ClientCommand( client_t *cl, msg_t *msg, qboolean inDl);

void SV_WriteRconStatus( msg_t *msg );

void G_PrintAdvertForPlayer(client_t*);
void G_PrintRuleForPlayer(client_t*);
void G_AddRule(const char* newtext);
void G_AddAdvert(const char* newtext);
void G_SetupHudMessagesForPlayer(client_t*);


void SV_SayToPlayers(int clnum, int team, char* text);


__optimize3 __regparm2 void SV_ExecuteClientMessage( client_t *cl, msg_t *msg );

void SV_GetUserinfo( int index, char *buffer, int bufferSize );

qboolean SV_Map(const char* levelname);
void SV_MapRestart( qboolean fastrestart );

void __cdecl SV_SetConfigstring(int index, const char *text);
//SV_SetConfigstring SV_SetConfigstring = (tSV_SetConfigstring)(0x8173fda);
const char* SV_GetGuid(unsigned int clnum, char* buf, int size);
qboolean SV_ExecuteRemoteCmd(int, const char*);
qboolean SV_UseUids();
int SV_GetUid(unsigned int);
void SV_SetUid(unsigned int clnum, unsigned int uid);
gentity_t* SV_AddBotClient();
gentity_t* SV_RemoveBot();
void SV_AddBan(baninfo_t* baninfo);

//sv_ingameadmin.c:
void SV_RemoteCmdInit();
void SV_RemoteCmdClearAdminList();
int SV_RemoteCmdGetClPower(client_t* cl);
int SV_RemoteCmdGetClPowerByUID(int uid);
void SV_ExecuteBroadcastedCmd(int uid, const char *msg);
qboolean SV_RemoteCmdAddAdmin(int uid, char* guid, int power);
qboolean SV_RemoteCmdInfoAddAdmin(const char* infostring);
void SV_RemoteCmdWriteAdminConfig(char* buffer, int size);
void SV_PrintAdministrativeLog( const char *fmt, ... );

void SV_RemoteCmdSetAdmin(int uid, char* guid, int power);
void SV_RemoteCmdUnsetAdmin(int uid, char* guid);
void SV_RemoteCmdSetPermission(char* command, int power);
void SV_RemoteCmdListAdmins( void );
__cdecl qboolean SV_GameCommand(void);

void SV_GetConfigstring( int index, char *buffer, int bufferSize );
int SV_GetConfigstringIndex(int num);
int SV_GetModelConfigstringIndex(int num);

extern cvar_t* sv_rconPassword;
extern cvar_t* sv_protocol;
extern cvar_t* sv_padPackets;
extern cvar_t* sv_demoCompletedCmd;
extern cvar_t* sv_screenshotArrivedCmd;
extern cvar_t* sv_mapDownloadCompletedCmd;
extern cvar_t* sv_wwwBaseURL;
extern cvar_t* sv_maxPing;
extern cvar_t* sv_minPing;
extern cvar_t* sv_authorizemode;
extern cvar_t* sv_privateClients;
extern cvar_t* sv_privatePassword;
extern cvar_t* sv_reconnectlimit;
extern cvar_t* sv_wwwDlDisconnected;
extern cvar_t* sv_allowDownload;
extern cvar_t* sv_wwwDownload;
extern cvar_t* sv_autodemorecord;
extern cvar_t* sv_modStats;
extern cvar_t* sv_password;
extern cvar_t* sv_mapRotation;
extern cvar_t* sv_mapRotationCurrent;
extern cvar_t* sv_randomMapRotation;
extern cvar_t* sv_cheats;
extern cvar_t* sv_consayname;
extern cvar_t* sv_contellname;
extern cvar_t* sv_maxclients;
extern cvar_t* sv_g_gametype;
extern cvar_t* sv_pure;
extern cvar_t* sv_fps;
extern cvar_t* sv_serverid;
extern cvar_t* sv_maxRate;
extern cvar_t* sv_mapname;
extern cvar_t* sv_floodProtect;
extern cvar_t* sv_showAverageBPS;
extern cvar_t* sv_hostname;
extern cvar_t* sv_shownet;
extern cvar_t* sv_legacymode;
extern cvar_t* sv_steamgroup;
extern cvar_t* sv_disableChat;

void __cdecl SV_StringUsage_f(void);
void __cdecl SV_ScriptUsage_f(void);
void __cdecl SV_BeginClientSnapshot( client_t *cl, msg_t* msg);
void __cdecl SV_EndClientSnapshot( client_t *cl, msg_t* msg);
void __cdecl SV_ClientThink( client_t *cl, usercmd_t * );
void SV_SpawnServer(const char* levelname);
void __cdecl SV_SetGametype( void );
void __cdecl SV_InitCvars( void );
void __cdecl SV_RestartGameProgs( int savepersist );
void __cdecl SV_ResetSekeletonCache(void);
void SV_BotInitBotLib( void );
int SV_BotLibSetup( void );
int SV_BotLoadMap(const char* levelname);
void __cdecl SV_PreFrame(void);
void __cdecl SV_SendClientMessages(void);
void __cdecl SV_SetServerStaticHeader(void);
void __cdecl SV_ShutdownGameProgs(void);
void __cdecl SV_FreeClients(void);
void __cdecl SV_GameSendServerCommand(int clientnum, int svscmd_type, const char *text);
void __cdecl SV_SetConfigstring(int index, const char *text);
void __cdecl SV_FreeClient(client_t* drop);
void __cdecl SV_FreeClientScriptId(client_t *cl);
void __cdecl SV_LinkEntity(gentity_t*);
void __cdecl SV_UnlinkEntity(gentity_t*);
void SV_SpawnServerResetPlayers();
void serverStatus_Write();

int SV_GetPlayerUIDByHandle(const char* handle);
client_t* SV_GetPlayerClByHandle(const char* handle);
const char* SV_GetPlayerNameByHandle(const char* handle);
uint64_t SV_GetPlayerSteamIDByHandle( const char* handle);
void SV_InitGameProgs(int a1);

//sv_banlist.c
void SV_InitBanlist( void );
void  SV_ReloadBanlist();
char* SV_PlayerIsBanned(uint64_t playerid, uint64_t steamid, netadr_t *addr, char* message, int len);
char* SV_PlayerBannedByip(netadr_t *netadr, char* message, int len);	//Gets called in SV_DirectConnect
void SV_PlayerAddBanByip(netadr_t *remote, char *message, int expire);
void SV_RemoveBanByip(netadr_t *remote);
void SV_RemoveBan(baninfo_t* baninfo);
void SV_DumpBanlist( void );
void SV_AddBanForPlayer(uint64_t steamid, uint64_t playerid, const char* name, int bantime, const char* banreason);
void SV_AddBanForClient(client_t* cl, int bantime, const char* banreason);
const char* SV_WriteBanTimelimit(int timeleftminutes, char *outbuffer, int outbufferlen);
const char* SV_FormatBanMessage(int timeleftminutes, char *outbuffer, int outbufferlen, const char* reasonfmt, ...);


void SV_AddSafeCommands();
extern	serverStaticExt_t	svse;	// persistant server info across maps
extern	permServerStatic_t	psvs;	// persistant even if server does shutdown

struct moveclip_s;
struct trace_s;

void SV_SetExpectedHunkUsage(const char* name);

__cdecl void SV_UpdateServerCommandsToClient( client_t *client, msg_t *msg );
__cdecl void SV_SendMessageToClient( msg_t *msg, client_t *client );
__cdecl void SV_WriteSnapshotToClient(client_t* client, msg_t* msg);
__cdecl cachedSnapshot_t* SV_GetCachedSnapshotInternal(int snapTime);
__cdecl void SV_ClipMoveToEntity(struct moveclip_s *clip, svEntity_t *entity, struct trace_s *trace);
void SV_Cmd_Init();
void SV_CopyCvars();
void SV_SteamData(client_t* cl, msg_t* msg);
void __cdecl SV_Trace(trace_t *results, const float *start, const float *mins, const float *maxs, const float *end, IgnoreEntParams *ignoreEntParams, int contentmask, int locational, char *priorityMap, int staticmodels); //0817D9F8
void SV_ClipToEntity( trace_t *trace, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int entityNum, int contentmask, int capsule );
void G_TraceCapsule(trace_t *results, const float *start, const float *mins, const float *maxs, const float *end, int passEntityNum, int contentmask);
int SV_PointContents( const vec3_t p, int passEntityNum, int contentmask );
qboolean SV_inPVSIgnorePortals( const vec3_t p1, const vec3_t p2 );

qboolean SV_SetupReliableMessageProtocol(client_t* client);
void SV_DisconnectReliableMessageProtocol(client_t* client);
void SV_ReceiveReliableMessages(client_t* client);
void SV_SendReliableServerCommand(client_t* client, msg_t *msg);
void SV_GenerateServerId( );
qboolean SV_RequestStats(client_t* client);
void SV_GetUsername(int clientNum, char* name, int maxlen);
void SV_CalculateChecksums();
void SV_WriteClientConfigInfo( msg_t* msg, client_t* cl, int messageNum );
void SV_UpdateClientConfigInfo(client_t* cl);
void SV_ScreenshotClient(client_t* cl, const char* name);
void SV_ScreenshotArrived(client_t* cl, const char* filename);
void SV_ModuleArrived(client_t* cl, const char* filename, long checksum);
void SV_AddBanForSteamIDGUID(uint64_t id, const char* guid, const char* name, int bantime, const char* banreason);
void SV_ClientCalcFramerate();
int SV_GetPredirectedOriginAndTimeForClientNum(int clientNum, float *origin);
void SV_SetMapCenterInSVSHeader(float* center);
void SV_GetMapCenterFromSVSHeader(float* center);

#ifdef COD4X18UPDATE
void SV_ConnectWithUpdateProxy(client_t *cl);
#endif
void SV_WriteChecksumInfo(msg_t* msg, const char* filename);
#endif

/*

typedef struct{
    vec3_t direction1;
    vec3_t direction2;
}spawnerrortest_t;


extern spawnerrortest_t e_spawns[64];
*/