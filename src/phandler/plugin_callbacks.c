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

void *Plugin_Malloc(size_t size)
{
    volatile int pID;
    //Identify the calling plugin
    pID = PHandler_CallerID();
    if (pID < 0)
    {
        Com_Printf("Plugins: Error! Tried allocating memory for unknown plugin!\n");
        return NULL;
    }
    if (pluginFunctions.plugins[pID].enabled == qfalse)
    {
        Com_Printf("^1WARNING^7: Tried allocating memory for a disabled plugin!\n");
    }
    return PHandler_Malloc(pID, size);
}

void Plugin_Free(void *ptr)
{
    //Identify the calling plugin
    volatile int pID = PHandler_CallerID();
    if (pID < 0)
    {
        Com_Printf("Plugins: Error! Tried freeing memory for unknown plugin!\n");
        return;
    }
    PHandler_Free(pID, ptr);
}

void Plugin_Error(EPluginError_t code, const char *fmt, ...)
{
    va_list argptr;
    char msg[1024];

    volatile int pID = PHandler_CallerID();

    if (pID < 0)
    {
        Com_PrintError("Plugin Error called from unknown plugin!\n");
        return;
    }

    va_start(argptr, fmt);
    Q_vsnprintf(msg, sizeof(msg), fmt, argptr);
    va_end(argptr);

    PHandler_Error(pID, code, msg);
}
// TODO: main thread only.
void Plugin_Cmd_AddPCommand(const char *cmd_name, xcommand_t function, int power)
{
    volatile int pID;
    pID = PHandler_CallerID();
    if (pID >= MAX_PLUGINS)
    {
        Com_PrintError("Tried adding a command for a plugin with non existent pID. pID supplied: %d.\n", pID);
        return;
    }
    else if (pID < 0)
    {
        Com_PrintError("Plugin_AddCommand called from not within a plugin or from a disabled plugin!\n");
        return;
    }
    if (!pluginFunctions.plugins[pID].loaded)
    {
        Com_PrintError("Tried adding a command for not loaded plugin! PID: %d.\n", pID);
        return;
    }

    Com_DPrintf("Adding a plugin command for plugin %d, command name: %s.\n", pID, cmd_name);
    Cmd_AddCommand(cmd_name, PHandler_CmdExecute_f);
    Cmd_SetPower(cmd_name, power);
    pluginFunctions.plugins[pID].cmd[pluginFunctions.plugins[pID].cmds].xcommand = function;
    strcpy(pluginFunctions.plugins[pID].cmd[pluginFunctions.plugins[pID].cmds++].name, cmd_name);
    Com_DPrintf("Command added.\n");
}
// TODO: main thread only.
void Plugin_Cmd_RemoveCommand(const char *cmd_name)
{
    volatile int pID;
    pID = PHandler_CallerID();
    if (pID >= MAX_PLUGINS)
    {
        Com_PrintError("Tried removing a command for a plugin with non existent pID. pID supplied: %d.\n", pID);
        return;
    }
    else if (pID < 0)
    {
        Com_PrintError("Plugin_RemoveCommand called from not within a plugin or from a disabled plugin!\n");
        return;
    }

    if (!pluginFunctions.plugins[pID].loaded)
    {
        Com_PrintError("Tried removing a command for not loaded plugin! PID: %d.\n", pID);
        return;
    }
    
    Com_DPrintf("Remove a plugin command for plugin %d, command name: %s.\n", pID, cmd_name);
    Cmd_RemoveCommand(cmd_name);
    Com_DPrintf("Command removed.\n");
}

qboolean Plugin_TcpConnect(int connection, const char *remote)
{
    return PHandler_TcpConnectMT(PHandler_CallerID(), connection, remote);
}

int Plugin_TcpGetData(int connection, void *buf, int size)
{
    return PHandler_TcpGetDataMT(PHandler_CallerID(), connection, buf, size);
}

qboolean Plugin_TcpSendData(int connection, void *data, int len)
{
    return PHandler_TcpSendDataMT(PHandler_CallerID(), connection, data, len);
}

void Plugin_TcpCloseConnection(int connection)
{
    PHandler_TcpCloseConnectionMT(PHandler_CallerID(), connection);
}

qboolean Plugin_UdpSendData(netadr_t *to, void *data, int len)
{
    int pID;

    if (to == NULL)
    {
        pID = PHandler_CallerID();
        Com_PrintError("Plugin_UdpSendData: First argument can not be a NULL-Pointer for plugin ID: #%d\n", pID);
        return qfalse;
    }

    if (data == NULL)
    {
        pID = PHandler_CallerID();
        Com_PrintError("Plugin_UdpSendData: First argument can not be a NULL-Pointer for plugin ID: #%d\n", pID);
        return qfalse;
    }

    netadr_t *defif;
    defif = NET_GetDefaultCommunicationSocket(to->type);
    to->sock = defif ? defif->sock : 0;

    return Sys_SendPacket(len, data, to);
}

void Plugin_ServerPacketEvent(netadr_t *to, void *data, int len)
{
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
    client_t *cl;
    int PID = PHandler_CallerID();
    mvabuf;

    if (clientslot > sv_maxclients->integer)
    {
        PHandler_Error(PID, P_ERROR_DISABLE, va("Plugin tried to get SteamID for bad client: %d\n", clientslot));
    }
    cl = &svs.clients[clientslot];
    return cl->steamid;
}

uint64_t Plugin_GetPlayerID(unsigned int clientslot)
{
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

int Plugin_GetLevelTime(void)
{
    return level.time;
}

int Plugin_GetServerTime(void)
{
    return svs.time;
}

void Plugin_Scr_AddFunction(char *name, xfunction_t function)
{
    int PID = PHandler_CallerID();

    PHandler_Scr_AddFunction(name, function, qfalse, PID);
}

void Plugin_Scr_AddMethod(char *name, xfunction_t function)
{
    int PID = PHandler_CallerID();

    PHandler_Scr_AddMethod(name, function, qfalse, PID);
}

void Plugin_Scr_ReplaceFunction(char *name, xfunction_t function)
{
    int PID = PHandler_CallerID();

    PHandler_Scr_AddFunction(name, function, qtrue, PID);
}

void Plugin_Scr_ReplaceMethod(char *name, xfunction_t function)
{
    int PID = PHandler_CallerID();

    PHandler_Scr_AddMethod(name, function, qtrue, PID);
}

void Plugin_ChatPrintf(int slot, const char *fmt, ...)
{
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
    if (clientnum > sv_maxclients->integer)
        return;

    SV_DropClient(&svs.clients[clientnum], reason);
}

void Plugin_BanClient(unsigned int clientnum, int duration, int invokerid, char *banreason)
{

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
    return &g_entities[entnum];
}

client_t *Plugin_GetClientForClientNum(int clientnum)
{
    return &svs.clients[clientnum];
}

int Plugin_HTTP_SendReceiveData(ftRequest_t *request)
{
    return HTTP_SendReceiveData(request);
}

ftRequest_t *Plugin_HTTP_MakeHttpRequest(const char *url, const char *method, byte *requestpayload, int payloadlen, const char *additionalheaderlines)
{
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
    return Plugin_HTTP_Request(url, "GET", NULL, 0, NULL);
}

void Plugin_HTTP_FreeObj(ftRequest_t *request)
{
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

int Plugin_GetPluginID() //Only from mainthread callable
{
    int PID = PHandler_CallerID();
    return PID;
}
