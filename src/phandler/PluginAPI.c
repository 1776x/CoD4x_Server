// Any header files can be included.
#include "plugin_callbacks.h"
#include "phandler.h"
#include "../qcommon.h"
#include "../sapi.h"
#include "../sv_auth.h"
#include "../cmd.h"
#include "../sys_main.h"
#include "../scr_vm.h"
#include "../g_sv_shared.h"
#include "../zlib/unzip.h"
#include "../server.h"
#include "../httpftp.h"
#include "../misc.h"
#include "../sys_net_types.h"

///////////////////////////////////////////////////////////////////////////
// Exported functions definitions lower.                                 //
// If function thread safe - it contains no "THREAD_UNSAFE*(...)" macro. //
///////////////////////////////////////////////////////////////////////////
// Leaving any code without plugin handler attention will make it available to any user, not only to a plugin.
void Plugin_Com_Printf(const char *fmt, ...)
{
    char buffer[1024];
    va_list va;
    
    va_start(va, fmt);
    Q_vsnprintf(buffer, sizeof(buffer), fmt, va);
    va_end(va);

    PluginHandler()->Print(buffer);
}

void Plugin_Com_PrintWarning(const char *fmt, ...)
{
    char buffer[1024];
    va_list va;

    va_start(va, fmt);
    Q_vsnprintf(buffer, sizeof(buffer), fmt, va);    
    va_end(va);

    PluginHandler()->PrintWarning(buffer);
}

void Plugin_Com_PrintError(const char *fmt, ...)
{
    char buffer[1024];
    va_list va;

    va_start(va, fmt);
    Q_vsnprintf(buffer, sizeof(buffer), fmt, va);
    va_end(va);

    PluginHandler()->PrintError(buffer);
}

void Plugin_Com_DPrintf(const char *fmt, ...)
{
    char buffer[1024];
    va_list va;

    va_start(va, fmt);
    Q_vsnprintf(buffer, sizeof(buffer), fmt, va);
    va_end(va);

    PluginHandler()->PrintDeveloper(buffer);
}

void Plugin_Com_RandomBytes(void *ptr, int len)
{
    PluginHandler()->FillWithRandomBytes(static_cast<byte*>(ptr), len);
}

time_t Plugin_Com_GetRealtime()
{
    PluginHandler()->GetRealTime();
}

void Plugin_SV_PrintAdministrativeLog(const char *fmt, ...)
{
    char buffer[1024];
    va_list va;

    va_start(va, fmt);
    Q_vsnprintf(buffer, sizeof(buffer), fmt, va);
    va_end(va);

    PluginHandler()->PrintAdministrativeLog(buffer);
}

void Plugin_SV_PlayerAddBanByip(netadr_t *remote, char *message, int expire)
{
    PluginHandler()->AddBanByIP(remote, message, expire);
}

void Plugin_SV_RemoveBanByip(netadr_t *remote)
{
    PluginHandler()->RemoveBanByIP(remote);
}

const char* Plugin_SV_WriteBanTimelimit(int timeleftminutes, char *outbuffer, int outbufferlen)
{
    PluginHandler()->GetBanTimeLimit(timeleftminutes, outbuffer, outbufferlen);
    return outbuffer;
}

const char* Plugin_SV_FormatBanMessage(int timeleftminutes, char *outbuffer, int outbufferlen, const char* reasonfmt, ...)
{
    char buffer[1024];
    va_list va;

    va_start(va, reasonfmt);
    Q_vsnprintf(buffer, sizeof(buffer), reasonfmt, va);
    va_end(va);

    PluginHandler()->GetBanMessage(timeleftminutes, outbuffer, outbufferlen, buffer);
    return outbuffer;
}

void Plugin_SV_SApiSteamIDToString(uint64_t steamid, char* string, int length)
{
    PluginHandler()->SteamIDToString(steamid, string, length);
}

void Plugin_SV_SApiSteamIDTo64String(uint64_t steamid, char* string, int length)
{
    PluginHandler()->SteamIDToString64(steamid, string, length);
}

uint64_t Plugin_SV_SApiStringToID(const char* steamidstring)
{
    return PluginHandler()->StringToSteamID(steamidstring);
}

qboolean Plugin_SV_SApiSteamIDIndividual(uint64_t steamid)
{
    return PluginHandler()->IsSteamIDIndividual(steamid) ? qtrue : qfalse;
}

qboolean Plugin_SV_SApiSteamIDIndividualSteamOnly(uint64_t steamid)
{
    return PluginHandler()->IsSteamIDIndividualSteamOnly(steamid) ? qtrue : qfalse;
}

void Plugin_Auth_AddCommandForClientToWhitelist(int clnum, const char* cmd)
{
    PluginHandler()->AddCommandForPlayerToWhitelist(clnum, cmd);
}

qboolean Plugin_Auth_CanPlayerUseCommand(unsigned int clnum, const char* cmd)
{
    return PluginHandler()->CanPlayerUseCommand(clnum, cmd) ? qtrue : qfalse;
}

client_t* Plugin_SV_GetPlayerClByHandle(const char* handle)
{
    THREAD_UNSAFE_RET(nullptr);
    return SV_GetPlayerClByHandle(handle);
}

const char* Plugin_SV_GetPlayerNameByHandle(const char* handle)
{
    THREAD_UNSAFE_RET(nullptr);
    return SV_GetPlayerNameByHandle(handle);
}

uint64_t Plugin_SV_GetPlayerSteamIDByHandle(const char* handle)
{
    THREAD_UNSAFE_RET(0);
    return SV_GetPlayerSteamIDByHandle(handle);
}

void Plugin_SV_SetClientStat(int clientNum, int index, int value)
{
    THREAD_UNSAFE();
    SV_SetClientStat(clientNum, index, value);
}

int Plugin_SV_GetClientStat(int clientNum, int index)
{
    THREAD_UNSAFE_RET(0);
    return SV_GetClientStat(clientNum, index);
}

int Plugin_Cmd_GetInvokerClnum()
{
    THREAD_UNSAFE_RET(-1);
    return Cmd_GetInvokerClnum();
}

int Plugin_Cmd_GetInvokerPower()
{
    THREAD_UNSAFE_RET(0);
    return Cmd_GetInvokerPower();
}

uint64_t Plugin_Cmd_GetInvokerSteamID()
{
    THREAD_UNSAFE_RET(0);
    return Cmd_GetInvokerSteamID();
}

const char* Plugin_Cmd_GetInvokerName(char *buf, int len)
{
    THREAD_UNSAFE_RET(buf);
    return Cmd_GetInvokerName(buf, len);
}

char* Plugin_Cmd_Argv(int arg)
{
    THREAD_UNSAFE_RET(nullptr);
    return Cmd_Argv(arg);
}

int Plugin_Cmd_Argc()
{
    THREAD_UNSAFE_RET(0);
    return Cmd_Argc();
}

char* Plugin_Cmd_Args(char* buff, int bufsize)
{
    THREAD_UNSAFE_RET(buff);
    return Cmd_Args(buff, bufsize);
}

const char* Plugin_Cvar_VariableStringBuffer(const char *var_name, char *buffer, int bufsize)
{
    THREAD_UNSAFE_RET(buffer);
    return Cvar_VariableStringBuffer(var_name, buffer, bufsize);
}

float Plugin_Cvar_VariableValue(const char *var_name)
{
    THREAD_UNSAFE_RET(0.0f);
    return Cvar_VariableValue(var_name);
}

int Plugin_Cvar_VariableIntegerValue(const char *var_name)
{
    THREAD_UNSAFE_RET(0);
    return Cvar_VariableIntegerValue(var_name);
}

qboolean Plugin_Cvar_VariableBooleanValue(const char *var_name)
{
    THREAD_UNSAFE_RET(qfalse);
    return Cvar_VariableBooleanValue(var_name);
}

cvar_t* Plugin_Cvar_RegisterString(const char *var_name, const char *var_value, unsigned short flags, const char *var_description)
{
    THREAD_UNSAFE_RET(nullptr);
    return Cvar_RegisterString(var_name, var_value, flags, var_description);
}

cvar_t* Plugin_Cvar_RegisterBool(const char *var_name, qboolean var_value, unsigned short flags, const char *var_description)
{
    THREAD_UNSAFE_RET(nullptr);
    return Cvar_RegisterBool(var_name, var_value, flags, var_description);
}

cvar_t* Plugin_Cvar_RegisterInt(const char *var_name, int var_value, int min_value, int max_value, unsigned short flags, const char *var_description)
{
    THREAD_UNSAFE_RET(nullptr);
    return Cvar_RegisterInt(var_name, var_value, min_value, max_value, flags, var_description);
}

cvar_t* Plugin_Cvar_RegisterFloat(const char *var_name, float var_value, float min_value, float max_value, unsigned short flags, const char *var_description)
{
    THREAD_UNSAFE_RET(nullptr);
    return Cvar_RegisterFloat(var_name, var_value, min_value, max_value, flags, var_description);
}

void Plugin_Cvar_SetInt(cvar_t* var, int val)
{
    THREAD_UNSAFE();
    Cvar_SetInt(var, val);
}

void Plugin_Cvar_SetBool(cvar_t* var, qboolean val)
{
    THREAD_UNSAFE();
    Cvar_SetBool(var, val);
}

void Plugin_Cvar_SetString(cvar_t* var, char const* string)
{
    THREAD_UNSAFE();
    Cvar_SetString(var, string);
}

void Plugin_Cvar_SetFloat(cvar_t* var, float val)
{
    THREAD_UNSAFE();
    Cvar_SetFloat(var, val);
}

void Plugin_Cvar_Set(const char *var_name, const char *value)
{
    THREAD_UNSAFE();
    Cvar_Set(var_name, value);
}

fileHandle_t Plugin_FS_FOpenFileWrite(const char* filename)
{
    THREAD_UNSAFE_RET(-1);
    return FS_FOpenFileWrite(filename);
}

long Plugin_FS_FOpenFileRead(const char* filename, fileHandle_t* returnhandle)
{
    THREAD_UNSAFE_RET(0);
    return FS_FOpenFileRead(filename, returnhandle);
}

fileHandle_t Plugin_FS_FOpenFileAppend(const char* filename)
{
    THREAD_UNSAFE_RET(-1);
    return FS_FOpenFileAppend(filename);
}

long Plugin_FS_SV_FOpenFileRead(const char *filename, fileHandle_t *fp)
{
    THREAD_UNSAFE_RET(0);
    return FS_SV_FOpenFileRead(filename, fp);
}

fileHandle_t Plugin_FS_SV_FOpenFileWrite(const char *filename)
{
    THREAD_UNSAFE_RET(-1);
    return FS_SV_FOpenFileWrite(filename);
}

fileHandle_t Plugin_FS_SV_FOpenFileAppend(const char *filename)
{
    THREAD_UNSAFE_RET(-1);
    return FS_SV_FOpenFileAppend(filename);
}

int Plugin_FS_Read(void* data, int length, fileHandle_t fh)
{
    THREAD_UNSAFE_RET(0);
    return FS_Read(data, length, fh);
}

int Plugin_FS_ReadFile(const char *qpath, void **buffer)
{
    THREAD_UNSAFE_RET(0);
    return FS_ReadFile(qpath, buffer);
}

void Plugin_FS_FreeFile(void *buffer)
{
    THREAD_UNSAFE();
    FS_FreeFile(buffer);
}

int Plugin_FS_ReadLine(void *buffer, int len, fileHandle_t fh)
{
    THREAD_UNSAFE_RET(0);
    return FS_ReadLine(buffer, len, fh);
}

int Plugin_FS_Write(const void *buffer, int len, fileHandle_t fh)
{
    THREAD_UNSAFE_RET(0);
    return FS_Write(buffer, len, fh);
}

int Plugin_FS_WriteFile(const char *qpath, const void *buffer, int size)
{
    THREAD_UNSAFE_RET(0);
    return FS_WriteFile(qpath, buffer, size);
}

qboolean Plugin_FS_FCloseFile(fileHandle_t fh)
{
    THREAD_UNSAFE_RET(qfalse);
    return FS_FCloseFile(fh);
}

int Plugin_FS_SV_HomeWriteFile(const char *qpath, const void *buffer, int size)
{
    THREAD_UNSAFE_RET(0);
    return FS_SV_HomeWriteFile(qpath, buffer, size);
}

int Plugin_FS_SV_BaseWriteFile(const char *qpath, const void *buffer, int size)
{
    THREAD_UNSAFE_RET(0);
    return FS_SV_BaseWriteFile(qpath, buffer, size);
}

void Plugin_FS_SV_HomeCopyFile(char* from, char* to)
{
    THREAD_UNSAFE();
    FS_SV_HomeCopyFile(from, to);
}

int Plugin_NET_StringToAdr(const char *s, netadr_t *a, netadrtype_t family)
{
    THREAD_UNSAFE_RET(0);
    return NET_StringToAdr(s, a, family);
}
/*
const char* Plugin_NET_AdrToString(netadr_t *a)
{
    THREAD_UNSAFE_RET(nullptr);
    return NET_AdrToString(a);
}*/

const char* Plugin_NET_AdrToString(netadr_t *a, char *buf, int len)
{
    //THREAD_UNSAFE_RET(buf); // TODO: check safety
    return NET_AdrToStringMT(a, buf, len);
}
/*
const char* Plugin_NET_AdrToStringShort(netadr_t *a)
{
    THREAD_UNSAFE_RET(nullptr);
    return NET_AdrToStringShort(a);
}*/

const char* Plugin_NET_AdrToStringShort(netadr_t *a, char* buf, int len)
{
    //THREAD_UNSAFE_RET(buf); // TODO: check safety
    return NET_AdrToStringShortMT(a, buf, len);
}

const char* Plugin_NET_AdrMaskToString(netadr_t *a, char* buf, int len)
{
    //THREAD_UNSAFE_RET(buf); // TODO: check safety
    return NET_AdrMaskToStringMT(a, buf, len);
}

qboolean Plugin_NET_CompareBaseAdrMask(netadr_t *a, netadr_t *b, int netmask)
{
    THREAD_UNSAFE_RET(qfalse);
    return NET_CompareBaseAdrMask(a, b, netmask);
}

qboolean Plugin_NET_CompareBaseAdr(netadr_t *a, netadr_t *b)
{
    THREAD_UNSAFE_RET(qfalse);
    return NET_CompareBaseAdr(a, b);
}

qboolean Plugin_NET_CompareAdr(netadr_t *a, netadr_t *b)
{
    THREAD_UNSAFE_RET(qfalse);
    return NET_CompareAdr(a, b);
}

unsigned int Plugin_Sys_Milliseconds()
{
    THREAD_UNSAFE_RET(0);
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
    THREAD_UNSAFE();
    Scr_AddEntity(ent);
}

int Plugin_Scr_AllocArray()
{
    THREAD_UNSAFE_RET(0);
    return Scr_AllocArray();
}

int Plugin_Scr_GetNumParam()
{
    THREAD_UNSAFE_RET(0);
    return Scr_GetNumParam();
}

int Plugin_Scr_GetInt(unsigned int arg)
{
    THREAD_UNSAFE_RET(0);
    return Scr_GetInt(arg);
}

float Plugin_Scr_GetFloat(unsigned int arg)
{
    THREAD_UNSAFE_RET(0.0f);
    return Scr_GetFloat(arg);
}

char* Plugin_Scr_GetString(unsigned int arg)
{
    THREAD_UNSAFE_RET(nullptr);
    return Scr_GetString(arg);
}

gentity_t* Plugin_Scr_GetEntity(unsigned int arg)
{
    THREAD_UNSAFE_RET(nullptr);
    return Scr_GetEntity(arg);
}

short Plugin_Scr_GetConstString(unsigned int arg)
{
    THREAD_UNSAFE_RET(0);
    return Scr_GetConstString(arg);
}

unsigned int Plugin_Scr_GetType(unsigned int arg)
{
    THREAD_UNSAFE_RET(0);
    return Scr_GetType(arg);
}

void Plugin_Scr_GetVector(unsigned int arg, float* vec)
{
    THREAD_UNSAFE();
    Scr_GetVector(arg, vec);
}

void Plugin_Scr_Error(const char *string)
{
    THREAD_UNSAFE();
    Scr_Error(string);
}

void Plugin_Scr_ParamError(int paramNum, const char *string)
{
    THREAD_UNSAFE();
    Scr_ParamError(paramNum, string);
}

void Plugin_Scr_ObjectError(const char *string)
{
    THREAD_UNSAFE();
    Scr_ObjectError(string);
}

void Plugin_Scr_AddInt(int value)
{
    THREAD_UNSAFE();
    Scr_AddInt(value);
}

void Plugin_Scr_AddFloat(float value)
{
    THREAD_UNSAFE();
    Scr_AddFloat(value);
}

void Plugin_Scr_AddBool(qboolean value)
{
    THREAD_UNSAFE();
    Scr_AddBool(value);
}

void Plugin_Scr_AddString(const char *string)
{
    THREAD_UNSAFE();
    Scr_AddString(string);
}

void Plugin_Scr_AddUndefined()
{
    THREAD_UNSAFE();
    Scr_AddUndefined();
}

void Plugin_Scr_AddVector(vec3_t vec)
{
    THREAD_UNSAFE();
    Scr_AddVector(vec);
}

void Plugin_Scr_AddArray()
{
    THREAD_UNSAFE();
    Scr_AddArray();
}

void Plugin_Scr_MakeArray()
{
    THREAD_UNSAFE();
    Scr_MakeArray();
}

void Plugin_Scr_AddArrayKey(int strIdx)
{
    THREAD_UNSAFE();
    Scr_AddArrayKey(strIdx);
}

short Plugin_Scr_ExecEntThread(gentity_t *ent, int callbackHook, unsigned int numArgs)
{
    THREAD_UNSAFE_RET(0);
    return Scr_ExecEntThread(ent, callbackHook, numArgs);
}

short Plugin_Scr_ExecThread(int callbackHook, unsigned int numArgs)
{
    THREAD_UNSAFE_RET(0);
    return Scr_ExecThread(callbackHook, numArgs);
}

void Plugin_Scr_FreeThread(short threadId)
{
    THREAD_UNSAFE();
    Scr_FreeThread(threadId);
}

void Plugin_Scr_Notify(gentity_t *ent, unsigned short constString, unsigned int numArgs)
{
    THREAD_UNSAFE();
    Scr_Notify(ent, constString, numArgs);
}

void Plugin_Scr_NotifyNum(int entityNum, unsigned int entType, unsigned int constString, unsigned int numArgs)
{
    THREAD_UNSAFE();
    Scr_NotifyNum(entityNum, entType, constString, numArgs);
}

void Plugin_Scr_NotifyLevel(int constString, unsigned int numArgs)
{
    THREAD_UNSAFE();
    Scr_NotifyLevel(constString, numArgs);
}

int Plugin_Scr_AllocString(const char* string)
{
    THREAD_UNSAFE_RET(0);
    return Scr_AllocString(string);
}

void Plugin_G_LogPrintf(const char *fmt, ...)
{
    THREAD_UNSAFE();
    char buffer[1024];
    va_list va;

    va_start(va, fmt);
    Q_vsnprintf(buffer, sizeof(buffer), fmt, va);
    va_end(va);

    G_LogPrintf(buffer);
}

playerState_t* Plugin_SV_GameClientNum(int num)
{
    THREAD_UNSAFE_RET(nullptr);
    return SV_GameClientNum(num);
}

int Plugin_unzSetPassword(unzFile file, const char* password)
{
    THREAD_UNSAFE_RET(0);
    return unzSetPassword(file, password);
}

void Plugin_Cbuf_AddText(const char* text)
{
    Cbuf_AddText(text);
}

void Plugin_SV_GetConfigstring(int index, char *buffer, int bufferSize)
{
    THREAD_UNSAFE();
    SV_GetConfigstring(index, buffer, bufferSize);
}

void Plugin_SV_SetConfigstring(int index, const char *text)
{
    THREAD_UNSAFE();
    SV_SetConfigstring(index, text);
}

char* Plugin_SL_ConvertToString(unsigned int index)
{
    THREAD_UNSAFE_RET(nullptr);
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

void* Plugin_Malloc(size_t size)
{
    THREAD_UNSAFE_RET(nullptr);
    return PluginHandler()->Malloc(size);
}

void Plugin_Free(void *ptr)
{
    THREAD_UNSAFE();
    PluginHandler()->Free(ptr);
}

void Plugin_Error(EPluginError_t code, const char *fmt, ...)
{
    THREAD_UNSAFE();
    va_list argptr;
    char msg[1024];

    va_start(argptr, fmt);
    Q_vsnprintf(msg, sizeof(msg), fmt, argptr);
    va_end(argptr);

    PluginHandler()->PluginError(code, msg);
}

void Plugin_Cmd_AddPCommand(const char *cmd_name, xcommand_t function, int power)
{
    THREAD_UNSAFE();
    PluginHandler()->AddConsoleCommand(cmd_name, function, power);
}

void Plugin_Cmd_RemoveCommand(const char *cmd_name)
{
    THREAD_UNSAFE();
    PluginHandler()->RemoveConsoleCommand(cmd_name);
}

int Plugin_TcpConnect(const char* Remote_, FPNetworkReceiveCallback ReceiveCallback_)
{
    THREAD_UNSAFE_RET(-1);
    return PluginHandler()->TCP_Connect(Remote_, ReceiveCallback_);
}

int Plugin_TcpGetData(const int Connection_, void* const Buffer_, unsigned int Size_)
{
    THREAD_UNSAFE_RET(SOCKET_ERROR);
    return PluginHandler()->TCP_Receive(Connection_, Buffer_, Size_);
}

int Plugin_TcpSendData(const int Connection_, const void* const Data_, unsigned int Size_)
{
    THREAD_UNSAFE_RET(SOCKET_ERROR);
    return PluginHandler()->TCP_Send(Connection_, Data_, Size_);
}

void Plugin_TcpCloseConnection(const int Connection_)
{
    THREAD_UNSAFE();
    PluginHandler()->TCP_Close(Connection_);
}
// todo: move inside plugin and guard with event only, ...() const.
qboolean Plugin_UdpSendData(netadr_t *To_, void *Data_, int Size_)
{
    THREAD_UNSAFE_RET(qfalse);
    if (!To_)
    {
        Com_PrintError("Unknown destination\n");
        return false;
    }
    if (!Data_ || !Size_)
    {
        Com_PrintError("Attempt to send NULL buffer or send nothing\n");
        return false;
    }

    netadr_t *defif = NET_GetDefaultCommunicationSocket(to->type);
    To_->sock = defif ? defif->sock : 0;
    return Sys_SendPacket(Size_, Data_, To_);
}

void Plugin_ServerPacketEvent(netadr_t *to, void *data, int len)
{
    THREAD_UNSAFE();
    msg_t msg;
    msg.data = data;
    msg.cursize = len;
    msg.maxsize = len;
    msg.bit = 0;
    msg.overflowed = qfalse;
    msg.readonly = qtrue;

    SV_PacketEvent(to, &msg);
}

uint64_t Plugin_GetPlayerSteamID(unsigned int clientslot)
{
    THREAD_UNSAFE_RET(0);
    client_t *cl;
    int PID = PHandler_CallerID();
    mvabuf;

    if (clientslot >= sv_maxclients->integer)
    {
        PHandler_Error(PID, P_ERROR_DISABLE, va("Plugin tried to get SteamID for bad client: %d\n", clientslot));
    }
    cl = &svs.clients[clientslot];
    return cl->steamid;
}

uint64_t Plugin_GetPlayerID(unsigned int clientslot)
{
    THREAD_UNSAFE_RET(0);
    client_t *cl;
    int PID = PHandler_CallerID();
    mvabuf;

    if (clientslot > sv_maxclients->integer)
    {
        PHandler_Error(PID, P_ERROR_DISABLE, va("Plugin tried to get PlayerID for bad client: %d\n", clientslot));
    }
    cl = &svs.clients[clientslot];
    return cl->playerid;
}

int Plugin_GetLevelTime()
{
    THREAD_UNSAFE_RET(0);
    return level.time;
}

int Plugin_GetServerTime()
{
    THREAD_UNSAFE_RET(0);
    return svs.time;
}

void Plugin_Scr_AddFunction(char *name, xfunction_t function)
{
    THREAD_UNSAFE();
    int PID = PHandler_CallerID();

    PHandler_Scr_AddFunction(name, function, qfalse, PID);
}

void Plugin_Scr_AddMethod(char *name, xfunction_t function)
{
    THREAD_UNSAFE();
    int PID = PHandler_CallerID();

    PHandler_Scr_AddMethod(name, function, qfalse, PID);
}

void Plugin_Scr_ReplaceFunction(char *name, xfunction_t function)
{
    THREAD_UNSAFE();
    int PID = PHandler_CallerID();

    PHandler_Scr_AddFunction(name, function, qtrue, PID);
}

void Plugin_Scr_ReplaceMethod(char *name, xfunction_t function)
{
    THREAD_UNSAFE();
    int PID = PHandler_CallerID();

    PHandler_Scr_AddMethod(name, function, qtrue, PID);
}

void Plugin_ChatPrintf(int slot, const char *fmt, ...)
{
    THREAD_UNSAFE();
    char str[256];
    client_t *cl;
    va_list vl;

    if (slot < 0)
        cl = NULL;
    else if (slot < sv_maxclients->integer)
        cl = &svs.clients[slot];
    else
        return;

    va_start(vl, fmt);
    Q_vsnprintf(str, sizeof(str), fmt, vl);
    va_end(vl);
    SV_SendServerCommand(cl, "h \"%s\"", str);
}

void Plugin_BoldPrintf(int slot, const char *fmt, ...)
{
    THREAD_UNSAFE();
    char str[256];
    client_t *cl;
    va_list vl;

    if (slot < 0)
        cl = NULL;
    else if (slot < sv_maxclients->integer)
        cl = &svs.clients[slot];
    else
        return;

    va_start(vl, fmt);
    Q_vsnprintf(str, sizeof(str), fmt, vl);
    va_end(vl);
    SV_SendServerCommand(cl, "c \"%s\"", str);
}

int Plugin_Dvar_GetInteger(void *cvar)
{
    THREAD_UNSAFE_RET(0);
    cvar_t *var = cvar;
    int PID = PHandler_CallerID();
    int v;
    if (var == NULL)
    {
        PHandler_Error(PID, P_ERROR_DISABLE, "Plugin to get Cvar of NULL-Pointer\n");
        return 0;
    }
    Sys_EnterCriticalSection(CRIT_CVAR);
    if (var->type != CVAR_INT)
    {
        PHandler_Error(PID, P_ERROR_DISABLE, "Plugin tried to get Cvar of different type\n");
        Sys_LeaveCriticalSection(CRIT_CVAR);
        return 0;
    }
    v = var->integer;
    Sys_LeaveCriticalSection(CRIT_CVAR);

    return v;
}

qboolean Plugin_Dvar_GetBoolean(void *cvar)
{
    THREAD_UNSAFE_RET(qfalse);
    cvar_t *var = cvar;
    qboolean b;
    int PID = PHandler_CallerID();

    if (var == NULL)
    {
        PHandler_Error(PID, P_ERROR_DISABLE, "Plugin to get Cvar of NULL-Pointer\n");
        return 0;
    }

    Sys_EnterCriticalSection(CRIT_CVAR);
    if (var->type != CVAR_BOOL)
    {
        PHandler_Error(PID, P_ERROR_DISABLE, "Plugin tried to get Cvar of different type\n");
        Sys_LeaveCriticalSection(CRIT_CVAR);
        return 0;
    }
    b = var->boolean;
    Sys_LeaveCriticalSection(CRIT_CVAR);
    return b;
}

float Plugin_Dvar_GetValue(void *cvar)
{
    THREAD_UNSAFE_RET(0.0f);
    cvar_t *var = cvar;
    float v;
    int PID = PHandler_CallerID();

    if (var == NULL)
    {
        PHandler_Error(PID, P_ERROR_DISABLE, "Plugin to get Cvar of NULL-Pointer\n");
        return 0;
    }

    Sys_EnterCriticalSection(CRIT_CVAR);

    if (var->type != CVAR_FLOAT)
    {
        PHandler_Error(PID, P_ERROR_DISABLE, "Plugin tried to get Cvar of different type\n");
        Sys_LeaveCriticalSection(CRIT_CVAR);
        return 0;
    }
    v = var->value;
    Sys_LeaveCriticalSection(CRIT_CVAR);
    return v;
}

const char *Plugin_Dvar_GetString(void *cvar, char *buf, int sizebuf)
{
    THREAD_UNSAFE_RET(buf);
    cvar_t *var = cvar;
    int PID = PHandler_CallerID();

    if (var == NULL)
    {
        PHandler_Error(PID, P_ERROR_DISABLE, "Plugin to get Cvar of NULL-Pointer\n");
        return 0;
    }

    Sys_EnterCriticalSection(CRIT_CVAR);

    if (var->type != CVAR_STRING)
    {
        PHandler_Error(PID, P_ERROR_DISABLE, "Plugin tried to get Cvar of different type\n");
        Sys_LeaveCriticalSection(CRIT_CVAR);
        return 0;
    }
    Q_strncpyz(buf, var->string, sizebuf);
    Sys_LeaveCriticalSection(CRIT_CVAR);
    return buf;
}

void Plugin_SV_DropClient(unsigned int clientnum, const char *reason)
{
    THREAD_UNSAFE();
    if (clientnum > sv_maxclients->integer)
        return;

    SV_DropClient(&svs.clients[clientnum], reason);
}

void Plugin_BanClient(unsigned int clientnum, int duration, int invokerid, char *banreason)
{
    THREAD_UNSAFE();
    client_t *cl;
    time_t expire;
    char *temp;
    time_t aclock;
    char endtime[32];
    char dropmsg[MAX_STRING_CHARS];
    char banmsg[MAX_STRING_CHARS];
    char timelimitmsg[MAX_STRING_CHARS];
    baninfo_t baninfo;
    char playeridstring[128];

    if (clientnum > sv_maxclients->integer)
        return;

    cl = &svs.clients[clientnum];

    time(&aclock);

    if (duration == -1)
    {
        expire = duration;
        Q_strncpyz(endtime, "never", sizeof(endtime));
    }
    else
    {
        expire = (aclock + (time_t)(duration * 60));
        temp = ctime(&expire);
        temp[strlen(temp) - 1] = 0;
        Q_strncpyz(endtime, temp, sizeof(endtime));
    }

    if (banreason == NULL)
    {
        banreason = "N/A";
    }

    uint64_t invokersteamid = Cmd_GetInvokerSteamID();
    if (invokersteamid == 0)
    {
        Q_strncpyz(baninfo.adminname, "A Plugin", sizeof(baninfo.adminname));
        baninfo.adminsteamid = 0;
    }
    else
    {
        Cmd_GetInvokerName(baninfo.adminname, sizeof(baninfo.adminname));
        baninfo.adminsteamid = invokersteamid;
    }

    baninfo.expire = (time_t)expire;
    baninfo.duration = (time_t)duration;
    Q_strncpyz(baninfo.message, banreason, sizeof(baninfo.message));

    //Banning
    Q_strncpyz(baninfo.playername, cl->name, sizeof(baninfo.playername));
    baninfo.steamid = cl->steamid;
    baninfo.playerid = cl->playerid;
    baninfo.adr = cl->netchan.remoteAddress;

    SV_AddBan(&baninfo);
    SV_SApiSteamIDToString(cl->playerid, playeridstring, sizeof(playeridstring));
    Com_Printf("Banrecord added for player: %s id: %s\n", cl->name, playeridstring);
    SV_PrintAdministrativeLog("Banned player: %s id: %s until %s with the following reason: %s", cl->name, playeridstring, endtime, banreason);

    SV_WriteBanTimelimit(duration * 60, timelimitmsg, sizeof(timelimitmsg));
    SV_FormatBanMessage(duration * 60, banmsg, sizeof(banmsg), "%s\nYour ID is: %s\nBanning admin UID is: \n%i\n", banreason, playeridstring, invokerid);

    Com_sprintf(dropmsg, sizeof(dropmsg), "%s%s", banmsg, timelimitmsg);

    SV_PlayerAddBanByip(&cl->netchan.remoteAddress, banmsg, expire);

    SV_DropClient(cl, dropmsg);
}

gentity_t *Plugin_GetGentityForEntityNum(int entnum)
{
    THREAD_UNSAFE_RET(nullptr);
    return &g_entities[entnum];
}

client_t *Plugin_GetClientForClientNum(int clientnum)
{
    THREAD_UNSAFE_RET(nullptr);
    return &svs.clients[clientnum];
}

int Plugin_HTTP_SendReceiveData(ftRequest_t *request)
{
    THREAD_UNSAFE_RET(0);
    return HTTP_SendReceiveData(request);
}

ftRequest_t *Plugin_HTTP_MakeHttpRequest(const char *url, const char *method, byte *requestpayload, int payloadlen, const char *additionalheaderlines)
{
    THREAD_UNSAFE_RET(nullptr);
    ftRequest_t *curfileobj;
    msg_t msgdata;
    msg_t *msg;

    if (method == NULL)
    {
        method = "GET";
    }

    if (requestpayload == NULL || payloadlen < 1)
    {
        msg = NULL;
    }
    else
    {
        MSG_InitReadOnly(&msgdata, requestpayload, payloadlen);
        msg = &msgdata;
    }

    curfileobj = HTTPRequest(url, method, msg, additionalheaderlines);

    if (curfileobj == NULL)
    {
        Com_Printf("Couldn't connect to server.\n");
        return qfalse;
    }

    return curfileobj;
}

/* blocking */
ftRequest_t *Plugin_HTTP_Request(const char *url, const char *method, byte *requestpayload, int payloadlen, const char *additionalheaderlines)
{
    THREAD_UNSAFE_RET(nullptr);
    ftRequest_t *curfileobj;
    int transret;
    msg_t msgdata;
    msg_t *msg;

    if (method == NULL)
    {
        method = "GET";
    }

    if (requestpayload == NULL || payloadlen < 1)
    {
        msg = NULL;
    }
    else
    {
        MSG_InitReadOnly(&msgdata, requestpayload, payloadlen);
        msg = &msgdata;
    }

    curfileobj = HTTPRequest(url, method, msg, additionalheaderlines);

    if (curfileobj == NULL)
    {
        Com_Printf("Couldn't connect to server.\n");
        return qfalse;
    }

    do
    {
        transret = FileDownloadSendReceive(curfileobj);
        Sys_SleepUSec(20000);
    } while (transret == 0);

    if (transret < 0)
    {
        Com_Printf("Receiving data has failed\n");
        FileDownloadFreeRequest(curfileobj);
        return qfalse;
    }
    return curfileobj;
}

/* blocking */
ftRequest_t *Plugin_HTTP_GET(const char *url)
{
    THREAD_UNSAFE_RET(nullptr);
    return Plugin_HTTP_Request(url, "GET", NULL, 0, NULL);
}

void Plugin_HTTP_FreeObj(ftRequest_t *request)
{
    THREAD_UNSAFE();
    FileDownloadFreeRequest(request);
}
/*
int mutex_depth = 0;
qboolean enable_threaddebug = qfalse;

void Plugin_EnterCriticalSection()
{
    mvabuf;

    if (enable_threaddebug)
    {
        Sys_Print(va("^6Plugin_EnterCriticalSection for thread: %d Section: [PLUGIN] Depth: %d\n", Sys_GetCurrentThreadId(), mutex_depth));
    }
    mutex_depth++;

    Sys_EnterCriticalSectionInternal(CRIT_PLUGIN);

    if (enable_threaddebug)
    {
        Sys_Print(va("^6Section [PLUGIN] Locked for thread: %d\n", Sys_GetCurrentThreadId()));
    }
}

void Plugin_LeaveCriticalSection()
{
    mvabuf;

    if (enable_threaddebug)
    {
        Sys_Print(va("^6Plugin_LeaveCriticalSection for Thread: %d\n", Sys_GetCurrentThreadId()));
    }
    mutex_depth--;

    Sys_LeaveCriticalSectionInternal(CRIT_PLUGIN);
}

qboolean Plugin_CreateNewThread(void *(*ThreadMain)(void *), threadid_t *tid, void *arg)
{
    mvabuf;
    threadid_t threadId = -1;
    qboolean r;

    if (enable_threaddebug)
    {
        Sys_Print("^6Plugin_CreateNewThread: Creating a new thread\n");
    }

    r = Sys_CreateNewThread(ThreadMain, &threadId, arg);

    if (enable_threaddebug)
    {
        Sys_Print(va("^6Plugin_CreateNewThread: Created a new thread with thread id %d\n", threadId));
    }
    if (tid)
    {
        *tid = threadId;
    }
    return r;
}

void Plugin_ExitThread(int code)
{
    mvabuf;
    if (enable_threaddebug)
    {
        Sys_Print(va("^6Plugin_ExitThread: Exit thread %d\n", Sys_GetCurrentThreadId()));
    }
    Sys_ExitThread(code);
}

void Plugin_EnableThreadDebug()
{
    enable_threaddebug = qtrue;
}

void Plugin_DisableThreadDebug()
{
    enable_threaddebug = qfalse;
}

void Plugin_RunThreadCallbacks()
{
    int i, j;
    plugin_thread_callback_t *tcb;
    for (j = 0; j < MAX_PLUGINS; ++j)
    {
        if (pluginFunctions.plugins[j].loaded == qfalse || pluginFunctions.plugins[j].enabled == qfalse)
        {
            continue;
        }

        for (tcb = pluginFunctions.plugins[j].thread_callbacks, i = 0; i < MAX_PLUGINCALLBACKS; i++)
        {
            if (tcb->lock == qfalse || tcb->isActive == qfalse)
            {
                continue;
            }

            if (tcb->callbackMain != NULL)
                tcb->callbackMain(tcb->callback_args[0], tcb->callback_args[1], tcb->callback_args[2], tcb->callback_args[3],
                                  tcb->callback_args[4], tcb->callback_args[5], tcb->callback_args[6], tcb->callback_args[7]);

            Com_Memset(tcb, 0, sizeof(plugin_thread_callback_t));
        }
    }
}

void *Plugin_CbThreadStub(void *arg)
{
    mvabuf;

    if (enable_threaddebug)
    {
        Sys_Print(va("^6Created new Thread: %d\n", Sys_GetCurrentThreadId()));
    }

    plugin_thread_callback_t *tcb = arg;

    tcb->threadMain(tcb->thread_args[0], tcb->thread_args[1], tcb->thread_args[2], tcb->thread_args[3],
                    tcb->thread_args[4], tcb->thread_args[5], tcb->thread_args[6], tcb->thread_args[7]); //real main-thread
    tcb->isActive = qtrue;
    return NULL;
}

qboolean Plugin_SetupThreadCallback(void *callbackMain, ...)
{
    plugin_thread_callback_t *tcb;
    int i;
    va_list argptr;

    volatile int pID = PHandler_CallerID();

    if (Sys_IsMainThread() == qtrue)
    {
        Com_PrintError("Plugin_SetupThreadCallback: Can not call this function from the main-thread!\n");
        return qfalse;
    }

    if (pluginFunctions.plugins[pID].loaded == qfalse || pluginFunctions.plugins[pID].enabled == qfalse)
    {
        Com_PrintError("Plugin_SetupThreadCallback: called from disabled or unknown plugin!\n");
        return qfalse;
    }

    for (tcb = pluginFunctions.plugins[pID].thread_callbacks, i = 0; i < MAX_PLUGINCALLBACKS; i++, tcb++)
    {
        if (Sys_ThreadisSame(tcb->tid))
        {
            break;
        }
    }
    if (i == MAX_PLUGINCALLBACKS)
    {
        Com_PrintError("Couldn't find this thread\n");
        return qfalse;
    }

    va_start(argptr, callbackMain);

    for (i = 0; i < MAX_PLUGINCALLBACKARGS; i++)
        tcb->callback_args[i] = va_arg(argptr, void *);

    va_end(argptr);

    tcb->callbackMain = callbackMain;
    return qtrue;
}

qboolean Plugin_CreateCallbackThread(void *threadMain, ...)
{
    volatile int pID = PHandler_CallerID();
    plugin_thread_callback_t *tcb;

    int i;
    va_list argptr;
    qboolean success;

    if (Sys_IsMainThread() == qfalse)
    {
        Com_PrintError("Plugin_CreateCallbackThread: Can only call this function from the main-thread!\n");
        return qfalse;
    }

    if (pluginFunctions.plugins[pID].loaded == qfalse || pluginFunctions.plugins[pID].enabled == qfalse)
    {
        Com_PrintError("Plugin_CreateCallbackThread: called from disabled or unknown plugin!\n");
        return qfalse;
    }

    for (tcb = pluginFunctions.plugins[pID].thread_callbacks, i = 0; i < MAX_PLUGINCALLBACKS; i++, tcb++)
    {
        if (tcb->threadMain == NULL)
        {
            break;
        }
    }
    if (i == MAX_PLUGINCALLBACKS)
    {
        Com_PrintError("Couldn't create a callback-thread. Max handles exceeded\n");
        return qfalse;
    }

    va_start(argptr, threadMain);

    for (i = 0; i < MAX_PLUGINCALLBACKARGS; i++)
        tcb->thread_args[i] = va_arg(argptr, void *);

    va_end(argptr);

    tcb->lock = qtrue;
    tcb->isActive = qfalse;
    tcb->threadMain = threadMain;
    tcb->callbackMain = NULL;
    success = Sys_CreateNewThread(Plugin_CbThreadStub, &tcb->tid, tcb);
    if (success == qfalse)
        tcb->isActive = qtrue;
    return success;
}
*/
