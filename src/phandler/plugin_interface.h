#pragma once
#include "../server_types.h"
#include "phandler_events_params.h"

// Plugin's exports (aka events) forward declaration.
#ifndef PLUGINEXPORT // To make PLUGINEVENT works only for export.
#define PLUGINEVENT extern "C" __declspec(dllexport)

PLUGINEVENT int OnInit();
PLUGINEVENT void OnInfoRequest(pluginInfo_t *info);
PLUGINEVENT void OnUnload();
PLUGINEVENT void OnPlayerDC(client_t *client, const char *reason);
PLUGINEVENT void OnPlayerConnect(int clientnum, netadr_t *netaddress, char *pbguid, char *userinfo, int authstatus, char *deniedmsg, int deniedmsgbufmaxlen);
PLUGINEVENT void OnExitLevel();
PLUGINEVENT void OnMessageSent(char *message, int slot, qboolean *show, int mode);
PLUGINEVENT void OnFrame();
PLUGINEVENT void OnOneSecond();
PLUGINEVENT void OnTenSeconds();
PLUGINEVENT void OnClientAuthorized();
PLUGINEVENT void OnClientSpawn(gentity_t *ent);
PLUGINEVENT void OnClientEnterWorld(client_t *client);
PLUGINEVENT void OnTcpServerPacket();
PLUGINEVENT void OnUdpNetEvent(netadr_t *from, void *data, int size, qboolean *returnNow);
PLUGINEVENT void OnUdpNetSend(netadr_t *to, void *data, int len, qboolean *returnNow);
PLUGINEVENT void OnSpawnServer();
PLUGINEVENT void OnPreFastRestart();
PLUGINEVENT void OnPostFastRestart();
PLUGINEVENT void OnClientUserinfoChanged(client_t *client);
PLUGINEVENT void OnClientMoveCommand(client_t *client, usercmd_t *ucmd);
PLUGINEVENT void OnPlayerWantReservedSlot(netadr_t *from, char *pbguid, char *userinfo, int authstate, qboolean *isallowed);
PLUGINEVENT void OnFilesystemStarted();
//Following function gets called when the player has basic authentication completed. Here we got a pbguid, the uid which is a short steamid, rejectmsg can be written a text to but never exceed 1023 characters, returnNow will keep the client idle when set to true, client_t*
PLUGINEVENT void OnPlayerGotAuthInfo(netadr_t *from, uint64_t *playerid, uint64_t *steamid, char *rejectmsg /*never exceed a limit of 1023 chars*/, qboolean *returnNow, client_t *cl); //an unverified playerid, SteamID "steamIdPending" and "clanIdPending" is not getting verified yet at all - you can get this info from client_t* structure
PLUGINEVENT void OnPlayerAddBan(baninfo_t *baninfo);
PLUGINEVENT void OnPlayerGetBanStatus(baninfo_t *baninfo, char *message, int len);
PLUGINEVENT void OnPlayerRemoveBan(baninfo_t *baninfo);
PLUGINEVENT void OnModuleLoaded(client_t *client, char *fullpath, long checksum);
PLUGINEVENT void OnScreenshotArrived(client_t *client, const char *path);
PLUGINEVENT void OnTerminate(); //Plugins using threads have to listen to this and terminate all threads without keeping critical sections locked. Plugins are susposed not to return from this functions until all child threads are terminated
PLUGINEVENT void OnScript_GametypeLoaded();
PLUGINEVENT void OnScript_LevelLoaded();
PLUGINEVENT void OnScript_GametypeStarted();
PLUGINEVENT void OnScript_PlayerConnected(gentity_t* self);
PLUGINEVENT void OnScript_PlayerDisconnected(gentity_t* self);
PLUGINEVENT void OnScript_PlayerDamage(ScriptEventParams_OnPlayerDamage_t* params);
PLUGINEVENT void OnScript_PlayerKilled(ScriptEventParams_OnPlayerKilled_t* params);
PLUGINEVENT void OnScript_PlayerLastStand(ScriptEventParams_OnPlayerLastStand_t* params);

#undef PLUGINEVENT
#endif


