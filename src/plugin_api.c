// Any header files can be included.
#include "plugin_api.h"
#include "qcommon.h"
#include "sapi.h"
#include "sv_auth.h"
#include "cmd.h"
#include "sys_main.h"
#include "scr_vm.h"
#include "g_sv_shared.h"
#include "zlib/unzip.h"
#include "server.h"
#include "httpftp.h"
#include "misc.h"

void Plugin_Com_Printf(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), fmt, va);
    
    va_end(va);

    Com_Printf(buffer);
}

void Plugin_Com_PrintWarning(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), fmt, va);
    
    va_end(va);

    Com_PrintWarning(buffer);
}

void Plugin_Com_PrintError(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), fmt, va);
    
    va_end(va);

    Com_PrintError(buffer);
}

void Plugin_Com_DPrintf(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), fmt, va);
    
    va_end(va);

    Com_DPrintf(buffer);
}

void Plugin_Com_RandomBytes(void *ptr, int len)
{
    Com_RandomBytes(ptr, len);
}

time_t Plugin_Com_GetRealtime()
{
    return Com_GetRealtime();
}

void Plugin_SV_PrintAdministrativeLog( const char *fmt, ... )
{
    va_list va;
    va_start(va, fmt);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), fmt, va);
    
    va_end(va);

    SV_PrintAdministrativeLog(buffer);
}

void Plugin_SV_PlayerAddBanByip(netadr_t *remote, char *message, int expire)
{
    SV_PlayerAddBanByip(remote, message, expire);
}

void Plugin_SV_RemoveBanByip(netadr_t *remote)
{
    SV_RemoveBanByip(remote);
}

const char* Plugin_SV_WriteBanTimelimit(int timeleftminutes, char *outbuffer, int outbufferlen)
{
    return SV_WriteBanTimelimit(timeleftminutes, outbuffer, outbufferlen);
}

const char* Plugin_SV_FormatBanMessage(int timeleftminutes, char *outbuffer, int outbufferlen, const char* reasonfmt, ...)
{
    va_list va;
    va_start(va, reasonfmt);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), reasonfmt, va);
    
    va_end(va);
    return SV_FormatBanMessage(timeleftminutes, outbuffer, outbufferlen, buffer);
}

void Plugin_SV_SApiSteamIDToString(uint64_t steamid, char* string, int length)
{
    SV_SApiSteamIDToString(steamid, string, length);
}

void Plugin_SV_SApiSteamIDTo64String(uint64_t steamid, char* string, int length)
{
    SV_SApiSteamIDTo64String(steamid, string, length);
}

uint64_t Plugin_SV_SApiStringToID(const char* steamidstring)
{
    return SV_SApiStringToID(steamidstring);
}

qboolean Plugin_SV_SApiSteamIDIndividual(uint64_t steamid)
{
    return SV_SApiSteamIDIndividual(steamid);
}

qboolean Plugin_SV_SApiSteamIDIndividualSteamOnly(uint64_t steamid)
{
    return SV_SApiSteamIDIndividualSteamOnly(steamid);
}

void Plugin_Auth_AddCommandForClientToWhitelist(int clnum, const char* cmd)
{
    Auth_AddCommandForClientToWhitelist(clnum, cmd);
}

qboolean Plugin_Auth_CanPlayerUseCommand(unsigned int clnum, const char* cmd)
{
    return Auth_CanPlayerUseCommand(clnum, cmd);
}

client_t* Plugin_SV_GetPlayerClByHandle(const char* handle)
{
    return SV_GetPlayerClByHandle(handle);
}

const char* Plugin_SV_GetPlayerNameByHandle(const char* handle)
{
    return SV_GetPlayerNameByHandle(handle);
}

uint64_t Plugin_SV_GetPlayerSteamIDByHandle(const char* handle)
{
    return SV_GetPlayerSteamIDByHandle(handle);
}

void Plugin_SV_SetClientStat(int clientNum, int index, int value)
{
    SV_SetClientStat(clientNum, index, value);
}

int Plugin_SV_GetClientStat(int clientNum, int index)
{
    return SV_GetClientStat(clientNum, index);
}

int Plugin_Cmd_GetInvokerClnum()
{
    return Cmd_GetInvokerClnum();
}

int Plugin_Cmd_GetInvokerPower()
{
    return Cmd_GetInvokerPower();
}

uint64_t Plugin_Cmd_GetInvokerSteamID()
{
    return Cmd_GetInvokerSteamID();
}

const char* Plugin_Cmd_GetInvokerName(char *buf, int len)
{
    return Cmd_GetInvokerName(buf, len);
}

char* Plugin_Cmd_Argv(int arg)
{
    return Cmd_Argv(arg);
}

int Plugin_Cmd_Argc()
{
    return Cmd_Argc();
}

char* Plugin_Cmd_Args(char* buff, int bufsize)
{
    return Cmd_Args(buff, bufsize);
}

const char* Plugin_Cvar_VariableStringBuffer(const char *var_name, char *buffer, int bufsize)
{
    return Cvar_VariableStringBuffer(var_name, buffer, bufsize);
}

float Plugin_Cvar_VariableValue(const char *var_name)
{
    return Cvar_VariableValue(var_name);
}

int Plugin_Cvar_VariableIntegerValue(const char *var_name)
{
    return Cvar_VariableIntegerValue(var_name);
}

qboolean Plugin_Cvar_VariableBooleanValue(const char *var_name)
{
    return Cvar_VariableBooleanValue(var_name);
}

cvar_t* Plugin_Cvar_RegisterString(const char *var_name, const char *var_value, unsigned short flags, const char *var_description)
{
    return Cvar_RegisterString(var_name, var_value, flags, var_description);
}

cvar_t* Plugin_Cvar_RegisterBool(const char *var_name, qboolean var_value, unsigned short flags, const char *var_description)
{
    return Cvar_RegisterBool(var_name, var_value, flags, var_description);
}

cvar_t* Plugin_Cvar_RegisterInt(const char *var_name, int var_value, int min_value, int max_value, unsigned short flags, const char *var_description)
{
    return Cvar_RegisterInt(var_name, var_value, min_value, max_value, flags, var_description);
}

cvar_t* Plugin_Cvar_RegisterFloat(const char *var_name, float var_value, float min_value, float max_value, unsigned short flags, const char *var_description)
{
    return Cvar_RegisterFloat(var_name, var_value, min_value, max_value, flags, var_description);
}

void Plugin_Cvar_SetInt(cvar_t* var, int val)
{
    Cvar_SetInt(var, val);
}

void Plugin_Cvar_SetBool(cvar_t* var, qboolean val)
{
    Cvar_SetBool(var, val);
}

void Plugin_Cvar_SetString(cvar_t* var, char const* string)
{
    Cvar_SetString(var, string);
}

void Plugin_Cvar_SetFloat(cvar_t* var, float val)
{
    Cvar_SetFloat(var, val);
}

void Plugin_Cvar_Set(const char *var_name, const char *value)
{
    Cvar_Set(var_name, value);
}

fileHandle_t Plugin_FS_FOpenFileWrite(const char* filename)
{
    return FS_FOpenFileWrite(filename);
}

long Plugin_FS_FOpenFileRead(const char* filename, fileHandle_t* returnhandle)
{
    return FS_FOpenFileRead(filename, returnhandle);
}

fileHandle_t Plugin_FS_FOpenFileAppend(const char* filename)
{
    return FS_FOpenFileAppend(filename);
}

long Plugin_FS_SV_FOpenFileRead(const char *filename, fileHandle_t *fp)
{
    return FS_SV_FOpenFileRead(filename, fp);
}

fileHandle_t Plugin_FS_SV_FOpenFileWrite(const char *filename)
{
    return FS_SV_FOpenFileWrite(filename);
}

fileHandle_t Plugin_FS_SV_FOpenFileAppend(const char *filename)
{
    return FS_SV_FOpenFileAppend(filename);
}

int Plugin_FS_Read(void* data, int length, fileHandle_t fh)
{
    return FS_Read(data, length, fh);
}

int Plugin_FS_ReadFile(const char *qpath, void **buffer)
{
    return FS_ReadFile(qpath, buffer);
}

void Plugin_FS_FreeFile(void *buffer)
{
    FS_FreeFile(buffer);
}

int Plugin_FS_ReadLine(void *buffer, int len, fileHandle_t fh)
{
    return FS_ReadLine(buffer, len, fh);
}

int Plugin_FS_Write(const void *buffer, int len, fileHandle_t fh)
{
    return FS_Write(buffer, len, fh);
}

int Plugin_FS_WriteFile(const char *qpath, const void *buffer, int size)
{
    return FS_WriteFile(qpath, buffer, size);
}

qboolean Plugin_FS_FCloseFile(fileHandle_t fh)
{
    return FS_FCloseFile(fh);
}

int Plugin_FS_SV_HomeWriteFile(const char *qpath, const void *buffer, int size)
{
    return FS_SV_HomeWriteFile(qpath, buffer, size);
}

int Plugin_FS_SV_BaseWriteFile(const char *qpath, const void *buffer, int size)
{
    return FS_SV_BaseWriteFile(qpath, buffer, size);
}

void Plugin_FS_SV_HomeCopyFile(char* from, char* to)
{
    FS_SV_HomeCopyFile(from, to);
}

int Plugin_NET_StringToAdr(const char *s, netadr_t *a, netadrtype_t family)
{
    return NET_StringToAdr(s, a, family);
}

const char* Plugin_NET_AdrToString(netadr_t *a)
{
    return NET_AdrToString(a);
}

const char* Plugin_NET_AdrToStringMT(netadr_t *a, char *buf, int len)
{
    return NET_AdrToStringMT(a, buf, len);
}

const char* Plugin_NET_AdrToStringShort(netadr_t *a)
{
    return NET_AdrToStringShort(a);
}

const char* Plugin_NET_AdrToStringShortMT(netadr_t *a, char* buf, int len)
{
    return NET_AdrToStringShortMT(a, buf, len);
}

const char* Plugin_NET_AdrMaskToStringMT(netadr_t *a, char* buf, int len)
{
    return NET_AdrMaskToStringMT(a, buf, len);
}

qboolean Plugin_NET_CompareBaseAdrMask(netadr_t *a, netadr_t *b, int netmask)
{
    return NET_CompareBaseAdrMask(a, b, netmask);
}

qboolean Plugin_NET_CompareBaseAdr(netadr_t *a, netadr_t *b)
{
    return NET_CompareBaseAdr(a, b);
}

qboolean Plugin_NET_CompareAdr(netadr_t *a, netadr_t *b)
{
    return NET_CompareAdr(a, b);
}

unsigned int Plugin_Sys_Milliseconds()
{
    return Sys_Milliseconds();
}

void Plugin_Sys_SleepSec(int seconds)
{
    Sys_SleepSec(seconds);
}

void Plugin_Sys_SleepMSec(int msec)
{
    Sys_SleepMSec(msec);
}

void Plugin_Scr_AddEntity(gentity_t* ent)
{
    Scr_AddEntity(ent);
}

int Plugin_Scr_AllocArray()
{
    return Scr_AllocArray();
}

int Plugin_Scr_GetNumParam()
{
    return Scr_GetNumParam();
}

int Plugin_Scr_GetInt(unsigned int arg)
{
    return Scr_GetInt(arg);
}

float Plugin_Scr_GetFloat(unsigned int arg)
{
    return Scr_GetFloat(arg);
}

char* Plugin_Scr_GetString(unsigned int arg)
{
    return Scr_GetString(arg);
}

gentity_t* Plugin_Scr_GetEntity(unsigned int arg)
{
    return Scr_GetEntity(arg);
}

short Plugin_Scr_GetConstString(unsigned int arg)
{
    return Scr_GetConstString(arg);
}

unsigned int Plugin_Scr_GetType(unsigned int arg)
{
    return Scr_GetType(arg);
}

void Plugin_Scr_GetVector(unsigned int arg, float* vec)
{
    Scr_GetVector(arg, vec);
}

void Plugin_Scr_Error(const char *string)
{
    Scr_Error(string);
}

void Plugin_Scr_ParamError(int paramNum, const char *string)
{
    Scr_ParamError(paramNum, string);
}

void Plugin_Scr_ObjectError(const char *string)
{
    Scr_ObjectError(string);
}

void Plugin_Scr_AddInt(int value)
{
    Scr_AddInt(value);
}

void Plugin_Scr_AddFloat(float value)
{
    Scr_AddFloat(value);
}

void Plugin_Scr_AddBool(qboolean value)
{
    Scr_AddBool(value);
}

void Plugin_Scr_AddString(const char *string)
{
    Scr_AddString(string);
}

void Plugin_Scr_AddUndefined()
{
    Scr_AddUndefined();
}

void Plugin_Scr_AddVector(vec3_t vec)
{
    Scr_AddVector(vec);
}

void Plugin_Scr_AddArray()
{
    Scr_AddArray();
}

void Plugin_Scr_MakeArray()
{
    Scr_MakeArray();
}

void Plugin_Scr_AddArrayKey(int strIdx)
{
    Scr_AddArrayKey(strIdx);
}

short Plugin_Scr_ExecEntThread(gentity_t *ent, int callbackHook, unsigned int numArgs)
{
    return Scr_ExecEntThread(ent, callbackHook, numArgs);
}

short Plugin_Scr_ExecThread(int callbackHook, unsigned int numArgs)
{
    return Scr_ExecThread(callbackHook, numArgs);
}

void Plugin_Scr_FreeThread(short threadId)
{
    Scr_FreeThread(threadId);
}

void Plugin_Scr_Notify(gentity_t *ent, unsigned short constString, unsigned int numArgs)
{
    Scr_Notify(ent, constString, numArgs);
}

void Plugin_Scr_NotifyNum(int entityNum, unsigned int entType, unsigned int constString, unsigned int numArgs)
{
    Scr_NotifyNum(entityNum, entType, constString, numArgs);
}

void Plugin_Scr_NotifyLevel(int constString, unsigned int numArgs)
{
    Scr_NotifyLevel(constString, numArgs);
}

int Plugin_Scr_AllocString(const char* string)
{
    return Scr_AllocString(string);
}

void Plugin_G_LogPrintf(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), fmt, va);
    
    va_end(va);

    G_LogPrintf(buffer);
}

playerState_t* Plugin_SV_GameClientNum(int num)
{
    return SV_GameClientNum(num);
}

int Plugin_unzSetPassword(unzFile file, const char* password)
{
    return unzSetPassword(file, password);
}

void Plugin_Cbuf_AddText(const char* text)
{
    Cbuf_AddText(text);
}

void Plugin_SV_GetConfigstring(int index, char *buffer, int bufferSize)
{
    SV_GetConfigstring(index, buffer, bufferSize);
}

void Plugin_SV_SetConfigstring(int index, const char *text)
{
    SV_SetConfigstring(index, text);
}

char* Plugin_SL_ConvertToString(unsigned int index)
{
    return SL_ConvertToString(index);
}

void Plugin_HTTP_CreateString_x_www_form_urlencoded(char* outencodedstring, int len, const char* key, const char *value)
{
    HTTP_CreateString_x_www_form_urlencoded(outencodedstring, len, key, value);
}

void Plugin_HTTP_ParseFormDataBody(char* body, httpPostVals_t* values)
{
    HTTP_ParseFormDataBody(body, values);
}

const char* Plugin_HTTP_GetFormDataItem(httpPostVals_t* values, const char* search)
{
    return HTTP_GetFormDataItem(values, search);
}

