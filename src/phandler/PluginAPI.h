// This file must be included in each plugin.
// It declares plugin handler API.
// Used both to export and import functions.
#pragma once

////////////////////////////////////////////////////////////
// Do not include files with functions declarations here! //
// These one will declare but not define functions.       //
////////////////////////////////////////////////////////////
#include <time.h>
#include <stdint.h>
#include "../sys_net_types.h"
#include "../cvar_types.h"
#include "../client.h"
#include "../q_shared_types.h"
#include "../httpftp_types.h"
#include "phandler_shared_types.h"
#include "../cmd_types.h"
#include "../scr_vm_types.h"

// Import/export functions macro.
#ifdef PLUGINEXPORT
    #ifdef __cplusplus
        #define PLUGINAPI extern "C" __declspec(dllexport)
    #else
        #define PLUGINAPI __declspec(dllexport)
    #endif
#else
    #ifdef __cplusplus
        #define PLUGINAPI extern "C" __declspec(dllimport)
    #else
        #define PLUGINAPI __declspec(dllimport)
    #endif
#endif

// Function name aliases section.
// I'm tired of using 'Plugin_*()' calls.
// Purpose: export function called "Plugin_<funcName>()", but in code you can use "<funcName>()"
//   inside plugin code which transforms into "Plugin_<funcName>()" call using these definitions.
// You have to "#define USE_LEGACY_NAMES" before including this file in plugin source code.
#ifndef PLUGINEXPORT
#ifdef USE_LEGACY_NAMES
#define Com_Printf Plugin_Com_Printf
#define Com_PrintWarning Plugin_Com_PrintWarning
#define Com_PrintError Plugin_Com_PrintError
#define Com_DPrintf Plugin_Com_DPrintf
#define Com_RandomBytes Plugin_Com_RandomBytes
#define Com_GetRealtime Plugin_Com_GetRealtime
#define SV_PrintAdministrativeLog Plugin_SV_PrintAdministrativeLog
#define SV_PlayerAddBanByip Plugin_SV_PlayerAddBanByip
#define SV_RemoveBanByip Plugin_SV_RemoveBanByip
#define SV_WriteBanTimelimit Plugin_SV_WriteBanTimelimit
#define SV_FormatBanMessage Plugin_SV_FormatBanMessage
#define SV_SApiSteamIDToString Plugin_SV_SApiSteamIDToString
#define SV_SApiSteamIDTo64String Plugin_SV_SApiSteamIDTo64String
#define SV_SApiStringToID Plugin_SV_SApiStringToID
#define SV_SApiSteamIDIndividual Plugin_SV_SApiSteamIDIndividual
#define SV_SApiSteamIDIndividualSteamOnly Plugin_SV_SApiSteamIDIndividualSteamOnly
#define Auth_AddCommandForClientToWhitelist Plugin_Auth_AddCommandForClientToWhitelist
#define Auth_CanPlayerUseCommand Plugin_Auth_CanPlayerUseCommand
#define SV_GetPlayerClByHandle Plugin_SV_GetPlayerClByHandle
#define SV_GetPlayerNameByHandle Plugin_SV_GetPlayerNameByHandle
#define SV_GetPlayerSteamIDByHandle Plugin_SV_GetPlayerSteamIDByHandle
#define SV_SetClientStat Plugin_SV_SetClientStat
#define SV_GetClientStat Plugin_SV_GetClientStat
#define Cmd_GetInvokerClnum Plugin_Cmd_GetInvokerClnum
#define Cmd_GetInvokerPower Plugin_Cmd_GetInvokerPower
#define Cmd_GetInvokerSteamID Plugin_Cmd_GetInvokerSteamID
#define Cmd_GetInvokerName Plugin_Cmd_GetInvokerName
#define Cmd_Argv Plugin_Cmd_Argv
#define Cmd_Argc Plugin_Cmd_Argc
#define Cmd_Args Plugin_Cmd_Args
#define Cvar_VariableStringBuffer Plugin_Cvar_VariableStringBuffer
#define Cvar_VariableValue Plugin_Cvar_VariableValue
#define Cvar_VariableIntegerValue Plugin_Cvar_VariableIntegerValue
#define Cvar_VariableBooleanValue Plugin_Cvar_VariableBooleanValue
#define Cvar_RegisterString Plugin_Cvar_RegisterString
#define Cvar_RegisterBool Plugin_Cvar_RegisterBool
#define Cvar_RegisterInt Plugin_Cvar_RegisterInt
#define Cvar_RegisterFloat Plugin_Cvar_RegisterFloat
#define Cvar_SetInt Plugin_Cvar_SetInt
#define Cvar_SetBool Plugin_Cvar_SetBool
#define Cvar_SetString Plugin_Cvar_SetString
#define Cvar_SetFloat Plugin_Cvar_SetFloat
#define Cvar_Set Plugin_Cvar_Set
#define FS_FOpenFileWrite Plugin_FS_FOpenFileWrite
#define FS_FOpenFileRead Plugin_FS_FOpenFileRead
#define FS_FOpenFileAppend Plugin_FS_FOpenFileAppend
#define FS_SV_FOpenFileRead Plugin_FS_SV_FOpenFileRead
#define FS_SV_FOpenFileWrite Plugin_FS_SV_FOpenFileWrite
#define FS_SV_FOpenFileAppend Plugin_FS_SV_FOpenFileAppend
#define FS_Read Plugin_FS_Read
#define FS_ReadFile Plugin_FS_ReadFile
#define FS_FreeFile Plugin_FS_FreeFile
#define FS_ReadLine Plugin_FS_ReadLine
#define FS_Write Plugin_FS_Write
#define FS_WriteFile Plugin_FS_WriteFile
#define FS_FCloseFile Plugin_FS_FCloseFile
#define FS_SV_HomeWriteFile Plugin_FS_SV_HomeWriteFile
#define FS_SV_BaseWriteFile Plugin_FS_SV_BaseWriteFile
#define FS_SV_HomeCopyFile Plugin_FS_SV_HomeCopyFile
#define NET_StringToAdr Plugin_NET_StringToAdr
#define NET_AdrToString Plugin_NET_AdrToString
#define NET_AdrToStringMT Plugin_NET_AdrToStringMT
#define NET_AdrToStringShort Plugin_NET_AdrToStringShort
#define NET_AdrToStringShortMT Plugin_NET_AdrToStringShortMT
#define NET_AdrMaskToStringMT Plugin_NET_AdrMaskToStringMT
#define NET_CompareBaseAdrMask Plugin_NET_CompareBaseAdrMask
#define NET_CompareBaseAdr Plugin_NET_CompareBaseAdr
#define NET_CompareAdr Plugin_NET_CompareAdr
#define Sys_Milliseconds Plugin_Sys_Milliseconds
#define Sys_SleepSec Plugin_Sys_SleepSec
#define Sys_SleepMSec Plugin_Sys_SleepMSec
#define Scr_AddEntity Plugin_Scr_AddEntity
#define Scr_AllocArray Plugin_Scr_AllocArray
#define Scr_GetNumParam Plugin_Scr_GetNumParam
#define Scr_GetInt Plugin_Scr_GetInt
#define Scr_GetFloat Plugin_Scr_GetFloat
#define Scr_GetString Plugin_Scr_GetString
#define Scr_GetEntity Plugin_Scr_GetEntity
#define Scr_GetConstString Plugin_Scr_GetConstString
#define Scr_GetType Plugin_Scr_GetType
#define Scr_GetVector Plugin_Scr_GetVector
#define Scr_Error Plugin_Scr_Error
#define Scr_ParamError Plugin_Scr_ParamError
#define Scr_ObjectError Plugin_Scr_ObjectError
#define Scr_AddInt Plugin_Scr_AddInt
#define Scr_AddFloat Plugin_Scr_AddFloat
#define Scr_AddBool Plugin_Scr_AddBool
#define Scr_AddString Plugin_Scr_AddString
#define Scr_AddUndefined Plugin_Scr_AddUndefined
#define Scr_AddVector Plugin_Scr_AddVector
#define Scr_AddArray Plugin_Scr_AddArray
#define Scr_MakeArray Plugin_Scr_MakeArray
#define Scr_AddArrayKey Plugin_Scr_AddArrayKey
#define Scr_ExecEntThread Plugin_Scr_ExecEntThread
#define Scr_ExecThread Plugin_Scr_ExecThread
#define Scr_FreeThread Plugin_Scr_FreeThread
#define Scr_Notify Plugin_Scr_Notify
#define Scr_NotifyNum Plugin_Scr_NotifyNum
#define Scr_NotifyLevel Plugin_Scr_NotifyLevel
#define Scr_AllocString Plugin_Scr_AllocString
#define G_LogPrintf Plugin_G_LogPrintf
#define SV_GameClientNum Plugin_SV_GameClientNum
#define unzSetPassword Plugin_unzSetPassword
#define Cbuf_AddText Plugin_Cbuf_AddText
#define SV_GetConfigstring Plugin_SV_GetConfigstring
#define SV_SetConfigstring Plugin_SV_SetConfigstring
#define SL_ConvertToString Plugin_SL_ConvertToString
#define HTTP_CreateString_x_www_form_urlencoded Plugin_HTTP_CreateString_x_www_form_urlencoded
#define HTTP_ParseFormDataBody Plugin_HTTP_ParseFormDataBody
#define HTTP_GetFormDataItem Plugin_HTTP_GetFormDataItem
#define Malloc Plugin_Malloc
#define Free Plugin_Free
#define Error Plugin_Error
#define Cmd_AddPCommand Plugin_Cmd_AddPCommand
#define Cmd_RemoveCommand Plugin_Cmd_RemoveCommand
#define TcpConnect Plugin_TcpConnect
#define TcpGetData Plugin_TcpGetData
#define TcpSendData Plugin_TcpSendData
#define TcpCloseConnection Plugin_TcpCloseConnection
#define UdpSendData Plugin_UdpSendData
#define ServerPacketEvent Plugin_ServerPacketEvent
#define GetPlayerSteamID Plugin_GetPlayerSteamID
#define GetPlayerID Plugin_GetPlayerID
#define GetLevelTime Plugin_GetLevelTime
#define GetServerTime Plugin_GetServerTime
#define Scr_AddFunction Plugin_Scr_AddFunction
#define Scr_AddMethod Plugin_Scr_AddMethod
#define Scr_ReplaceFunction Plugin_Scr_ReplaceFunction
#define Scr_ReplaceMethod Plugin_Scr_ReplaceMethod
#define ChatPrintf Plugin_ChatPrintf
#define BoldPrintf Plugin_BoldPrintf
#define Dvar_GetInteger Plugin_Dvar_GetInteger
#define Dvar_GetBoolean Plugin_Dvar_GetBoolean
#define Dvar_GetValue Plugin_Dvar_GetValue
#define Dvar_GetString Plugin_Dvar_GetString
#define SV_DropClient Plugin_SV_DropClient
#define BanClient Plugin_BanClient
#define GetGentityForEntityNum Plugin_GetGentityForEntityNum
#define GetClientForClientNum Plugin_GetClientForClientNum
#define HTTP_SendReceiveData Plugin_HTTP_SendReceiveData
#define HTTP_MakeHttpRequest Plugin_HTTP_MakeHttpRequest
#define HTTP_Request Plugin_HTTP_Request
#define HTTP_GET Plugin_HTTP_GET
#define HTTP_FreeObj Plugin_HTTP_FreeObj
/*
#define EnterCriticalSection Plugin_EnterCriticalSection
#define LeaveCriticalSection Plugin_LeaveCriticalSection
#define CreateNewThread Plugin_CreateNewThread
#define ExitThread Plugin_ExitThread
#define EnableThreadDebug Plugin_EnableThreadDebug
#define DisableThreadDebug Plugin_DisableThreadDebug
#define RunThreadCallbacks Plugin_RunThreadCallbacks
#define SetupThreadCallback Plugin_SetupThreadCallback
#define CreateCallbackThread Plugin_CreateCallbackThread
*/
#endif //USE_LEGACY_NAMES
#endif //notdef PLUGINEXPORT

// Import/export functions section.
PLUGINAPI void Plugin_Com_Printf(const char *fmt, ...);
PLUGINAPI void Plugin_Com_PrintWarning(const char *fmt, ...);
PLUGINAPI void Plugin_Com_PrintError(const char *fmt, ...);
PLUGINAPI void Plugin_Com_DPrintf(const char *fmt, ...);
PLUGINAPI void Plugin_Com_RandomBytes(void *ptr, int len);
PLUGINAPI time_t Plugin_Com_GetRealtime();
PLUGINAPI void Plugin_SV_PrintAdministrativeLog( const char *fmt, ... );
PLUGINAPI void Plugin_SV_PlayerAddBanByip(netadr_t *remote, char *message, int expire);
PLUGINAPI void Plugin_SV_RemoveBanByip(netadr_t *remote);
PLUGINAPI const char* Plugin_SV_WriteBanTimelimit(int timeleftminutes, char *outbuffer, int outbufferlen);
PLUGINAPI const char* Plugin_SV_FormatBanMessage(int timeleftminutes, char *outbuffer, int outbufferlen, const char* reasonfmt, ...);
PLUGINAPI void Plugin_SV_SApiSteamIDToString(uint64_t steamid, char* string, int length);
PLUGINAPI void Plugin_SV_SApiSteamIDTo64String(uint64_t steamid, char* string, int length);
PLUGINAPI uint64_t Plugin_SV_SApiStringToID(const char* steamidstring);
PLUGINAPI qboolean Plugin_SV_SApiSteamIDIndividual(uint64_t steamid);
PLUGINAPI qboolean Plugin_SV_SApiSteamIDIndividualSteamOnly(uint64_t steamid);
PLUGINAPI void Plugin_Auth_AddCommandForClientToWhitelist(int clnum, const char* cmd);
PLUGINAPI qboolean Plugin_Auth_CanPlayerUseCommand(unsigned int clnum, const char* cmd);
PLUGINAPI client_t* Plugin_SV_GetPlayerClByHandle(const char* handle);
PLUGINAPI const char* Plugin_SV_GetPlayerNameByHandle(const char* handle);
PLUGINAPI uint64_t Plugin_SV_GetPlayerSteamIDByHandle(const char* handle);
PLUGINAPI void Plugin_SV_SetClientStat(int clientNum, int index, int value);
PLUGINAPI int Plugin_SV_GetClientStat(int clientNum, int index);
PLUGINAPI int Plugin_Cmd_GetInvokerClnum();
PLUGINAPI int Plugin_Cmd_GetInvokerPower();
PLUGINAPI uint64_t Plugin_Cmd_GetInvokerSteamID();
PLUGINAPI const char* Plugin_Cmd_GetInvokerName(char *buf, int len);
PLUGINAPI char* Plugin_Cmd_Argv(int arg);
PLUGINAPI int Plugin_Cmd_Argc();
PLUGINAPI char* Plugin_Cmd_Args(char* buff, int bufsize);
PLUGINAPI const char* Plugin_Cvar_VariableStringBuffer(const char *var_name, char *buffer, int bufsize);
PLUGINAPI float Plugin_Cvar_VariableValue(const char *var_name);
PLUGINAPI int Plugin_Cvar_VariableIntegerValue(const char *var_name);
PLUGINAPI qboolean Plugin_Cvar_VariableBooleanValue(const char *var_name);
PLUGINAPI cvar_t* Plugin_Cvar_RegisterString(const char *var_name, const char *var_value, unsigned short flags, const char *var_description);
PLUGINAPI cvar_t* Plugin_Cvar_RegisterBool(const char *var_name, qboolean var_value, unsigned short flags, const char *var_description);
PLUGINAPI cvar_t* Plugin_Cvar_RegisterInt(const char *var_name, int var_value, int min_value, int max_value, unsigned short flags, const char *var_description);
PLUGINAPI cvar_t* Plugin_Cvar_RegisterFloat(const char *var_name, float var_value, float min_value, float max_value, unsigned short flags, const char *var_description);
PLUGINAPI void Plugin_Cvar_SetInt(cvar_t* var, int val);
PLUGINAPI void Plugin_Cvar_SetBool(cvar_t* var, qboolean val);
PLUGINAPI void Plugin_Cvar_SetString(cvar_t* var, char const* string);
PLUGINAPI void Plugin_Cvar_SetFloat(cvar_t* var, float val);
PLUGINAPI void Plugin_Cvar_Set(const char *var_name, const char *value);
PLUGINAPI fileHandle_t Plugin_FS_FOpenFileWrite(const char* filename);
PLUGINAPI long Plugin_FS_FOpenFileRead(const char* filename, fileHandle_t* returnhandle);
PLUGINAPI fileHandle_t Plugin_FS_FOpenFileAppend(const char* filename);
PLUGINAPI long Plugin_FS_SV_FOpenFileRead(const char *filename, fileHandle_t *fp);
PLUGINAPI fileHandle_t Plugin_FS_SV_FOpenFileWrite(const char *filename);
PLUGINAPI fileHandle_t Plugin_FS_SV_FOpenFileAppend(const char *filename);
PLUGINAPI int Plugin_FS_Read(void* data, int length, fileHandle_t fh);
PLUGINAPI int Plugin_FS_ReadFile(const char *qpath, void **buffer);
PLUGINAPI void Plugin_FS_FreeFile(void *buffer);
PLUGINAPI int Plugin_FS_ReadLine(void *buffer, int len, fileHandle_t fh);
PLUGINAPI int Plugin_FS_Write(const void *buffer, int len, fileHandle_t fh);
PLUGINAPI int Plugin_FS_WriteFile(const char *qpath, const void *buffer, int size);
PLUGINAPI qboolean Plugin_FS_FCloseFile(fileHandle_t fh);
PLUGINAPI int Plugin_FS_SV_HomeWriteFile(const char *qpath, const void *buffer, int size);
PLUGINAPI int Plugin_FS_SV_BaseWriteFile(const char *qpath, const void *buffer, int size);
PLUGINAPI void Plugin_FS_SV_HomeCopyFile(char* from, char* to);
PLUGINAPI int Plugin_NET_StringToAdr(const char *s, netadr_t *a, netadrtype_t family);
PLUGINAPI const char* Plugin_NET_AdrToString(netadr_t *a);
PLUGINAPI const char* Plugin_NET_AdrToStringMT(netadr_t *a, char *buf, int len);
PLUGINAPI const char* Plugin_NET_AdrToStringShort(netadr_t *a);
PLUGINAPI const char* Plugin_NET_AdrToStringShortMT(netadr_t *a, char* buf, int len);
PLUGINAPI const char* Plugin_NET_AdrMaskToStringMT(netadr_t *a, char* buf, int len);
PLUGINAPI qboolean Plugin_NET_CompareBaseAdrMask(netadr_t *a, netadr_t *b, int netmask);
PLUGINAPI qboolean Plugin_NET_CompareBaseAdr(netadr_t *a, netadr_t *b);
PLUGINAPI qboolean Plugin_NET_CompareAdr(netadr_t *a, netadr_t *b);
PLUGINAPI unsigned int Plugin_Sys_Milliseconds();
PLUGINAPI void Plugin_Sys_SleepSec(int seconds);
PLUGINAPI void Plugin_Sys_SleepMSec(int msec);
PLUGINAPI void Plugin_Scr_AddEntity(gentity_t* ent);
PLUGINAPI int Plugin_Scr_AllocArray();
PLUGINAPI int Plugin_Scr_GetNumParam();
PLUGINAPI int Plugin_Scr_GetInt(unsigned int arg);
PLUGINAPI float Plugin_Scr_GetFloat(unsigned int arg);
PLUGINAPI char* Plugin_Scr_GetString(unsigned int arg);
PLUGINAPI gentity_t* Plugin_Scr_GetEntity(unsigned int arg);
PLUGINAPI short Plugin_Scr_GetConstString(unsigned int arg);
PLUGINAPI unsigned int Plugin_Scr_GetType(unsigned int arg);
PLUGINAPI void Plugin_Scr_GetVector(unsigned int arg, float* vec);
PLUGINAPI void Plugin_Scr_Error(const char *string);
PLUGINAPI void Plugin_Scr_ParamError(int paramNum, const char *string);
PLUGINAPI void Plugin_Scr_ObjectError(const char *string);
PLUGINAPI void Plugin_Scr_AddInt(int value);
PLUGINAPI void Plugin_Scr_AddFloat(float value);
PLUGINAPI void Plugin_Scr_AddBool(qboolean value);
PLUGINAPI void Plugin_Scr_AddString(const char *string);
PLUGINAPI void Plugin_Scr_AddUndefined();
PLUGINAPI void Plugin_Scr_AddVector(vec3_t vec);
PLUGINAPI void Plugin_Scr_AddArray();
PLUGINAPI void Plugin_Scr_MakeArray();
PLUGINAPI void Plugin_Scr_AddArrayKey(int strIdx);
PLUGINAPI short Plugin_Scr_ExecEntThread(gentity_t *ent, int callbackHook, unsigned int numArgs);
PLUGINAPI short Plugin_Scr_ExecThread(int callbackHook, unsigned int numArgs);
PLUGINAPI void Plugin_Scr_FreeThread(short threadId);
PLUGINAPI void Plugin_Scr_Notify(gentity_t *ent, unsigned short constString, unsigned int numArgs);
PLUGINAPI void Plugin_Scr_NotifyNum(int entityNum, unsigned int entType, unsigned int constString, unsigned int numArgs);
PLUGINAPI void Plugin_Scr_NotifyLevel(int constString, unsigned int numArgs);
PLUGINAPI int Plugin_Scr_AllocString(const char* string);
PLUGINAPI void Plugin_G_LogPrintf(const char *fmt, ...);
PLUGINAPI playerState_t* Plugin_SV_GameClientNum(int num);
PLUGINAPI int Plugin_unzSetPassword(unzFile file, const char* password);
PLUGINAPI void Plugin_Cbuf_AddText(const char* text);
PLUGINAPI void Plugin_SV_GetConfigstring(int index, char *buffer, int bufferSize);
PLUGINAPI void Plugin_SV_SetConfigstring(int index, const char *text);
PLUGINAPI char* Plugin_SL_ConvertToString(unsigned int index);
PLUGINAPI void Plugin_HTTP_CreateString_x_www_form_urlencoded(char* outencodedstring, int len, const char* key, const char *value);
PLUGINAPI void Plugin_HTTP_ParseFormDataBody(char* body, httpPostVals_t* values);
PLUGINAPI const char* Plugin_HTTP_GetFormDataItem(httpPostVals_t* values, const char* search);
PLUGINAPI void *Plugin_Malloc(size_t size);
PLUGINAPI void Plugin_Free(void *ptr);
PLUGINAPI void Plugin_Error(EPluginError_t code, const char *fmt, ...);
PLUGINAPI void Plugin_Cmd_AddPCommand(const char *cmd_name, xcommand_t function, int power);
PLUGINAPI void Plugin_Cmd_RemoveCommand(const char *cmd_name);

// Networking: TCP
PLUGINAPI qboolean Plugin_TcpConnect(int connection, const char *remote);
PLUGINAPI int Plugin_TcpGetData(int connection, void *buf, int size);
PLUGINAPI qboolean Plugin_TcpSendData(int connection, void *data, int len);
PLUGINAPI void Plugin_TcpCloseConnection(int connection);

// Networking: UDP
PLUGINAPI qboolean Plugin_UdpSendData(netadr_t *to, void *data, int len);
PLUGINAPI void Plugin_ServerPacketEvent(netadr_t *to, void *data, int len);

PLUGINAPI uint64_t Plugin_GetPlayerSteamID(unsigned int clientslot);
PLUGINAPI uint64_t Plugin_GetPlayerID(unsigned int clientslot);
PLUGINAPI int Plugin_GetLevelTime();
PLUGINAPI int Plugin_GetServerTime();
PLUGINAPI void Plugin_Scr_AddFunction(char *name, xfunction_t function);
PLUGINAPI void Plugin_Scr_AddMethod(char *name, xfunction_t function);
PLUGINAPI void Plugin_Scr_ReplaceFunction(char *name, xfunction_t function);
PLUGINAPI void Plugin_Scr_ReplaceMethod(char *name, xfunction_t function);

// Chat messaging.
PLUGINAPI void Plugin_ChatPrintf(int slot, const char *fmt, ...);
PLUGINAPI void Plugin_BoldPrintf(int slot, const char *fmt, ...);

// Dvars
PLUGINAPI int Plugin_Dvar_GetInteger(void *cvar);
PLUGINAPI qboolean Plugin_Dvar_GetBoolean(void *cvar);
PLUGINAPI float Plugin_Dvar_GetValue(void *cvar);
PLUGINAPI const char *Plugin_Dvar_GetString(void *cvar, char *buf, int sizebuf);

// Clients management.
PLUGINAPI void Plugin_SV_DropClient(unsigned int clientnum, const char *reason);
PLUGINAPI void Plugin_BanClient(unsigned int clientnum, int duration, int invokerid, char *banreason);

PLUGINAPI gentity_t *Plugin_GetGentityForEntityNum(int entnum);
PLUGINAPI client_t *Plugin_GetClientForClientNum(int clientnum);

// HTTP
PLUGINAPI int Plugin_HTTP_SendReceiveData(ftRequest_t *request);
PLUGINAPI ftRequest_t *Plugin_HTTP_MakeHttpRequest(const char *url, const char *method, byte *requestpayload, int payloadlen, const char *additionalheaderlines);
    // Blocking.
PLUGINAPI ftRequest_t *Plugin_HTTP_Request(const char *url, const char *method, byte *requestpayload, int payloadlen, const char *additionalheaderlines);
    // Blocking.
PLUGINAPI ftRequest_t *Plugin_HTTP_GET(const char *url);
PLUGINAPI void Plugin_HTTP_FreeObj(ftRequest_t *request);

// Multithreading
//PLUGINAPI void Plugin_EnterCriticalSection();
//PLUGINAPI void Plugin_LeaveCriticalSection();
//PLUGINAPI qboolean Plugin_CreateNewThread(void *(*ThreadMain)(void *), threadid_t *tid, void *arg);
//PLUGINAPI void Plugin_ExitThread(int code);
//PLUGINAPI void Plugin_EnableThreadDebug();
//PLUGINAPI void Plugin_DisableThreadDebug();
//PLUGINAPI void Plugin_RunThreadCallbacks();
//PLUGINAPI qboolean Plugin_SetupThreadCallback(void *callbackMain, ...);
//PLUGINAPI qboolean Plugin_CreateCallbackThread(void *threadMain, ...);
