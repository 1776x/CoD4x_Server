/*
===========================================================================
    Copyright (C) 2010-2013  Ninja and TheKelm

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

#include "phandler.h"
#include "../sys_main.h"
#include "phandler_shared_types.h"
/*==========================================*
 *                                          *
 *   Plugin Handler's internal functions    *
 *                                          *
 * Functions in this file might be not safe *
 *    for use outside of plugin handler.    *
 *                                          *
 *==========================================*/

/*
============
 TCP module
============
*/

qboolean PHandler_TcpConnect(int pID, const char *remote, int connection)
{
    if (pluginFunctions.plugins[pID].sockets[connection].sock < 1)
    {
        pluginFunctions.plugins[pID].sockets[connection].sock = NET_TcpClientConnect(remote);

        if (pluginFunctions.plugins[pID].sockets[connection].sock < 1)
        {
            Com_Printf("Plugins: Notice! Error connecting to server: %s for plugin #%d!\n", remote, pID);
            return qfalse;
        }
        Com_DPrintf("PHandler_TcpConnect: Received socket %d @ %d\n", pluginFunctions.plugins[pID].sockets[connection].sock, connection);
        NET_StringToAdr(remote, &pluginFunctions.plugins[pID].sockets[connection].remote, NA_UNSPEC);
        return qtrue;
    }
    Com_PrintError("Plugin_TcpConnect: Connection id %d is already in use for plugin #%d!\n", connection, pID);

    return qfalse;
}

int PHandler_TcpGetData(int pID, int connection, void *buf, int size)
{
    char errormsg[1024];
    errormsg[0] = 0;
    int len;
    pluginTcpClientSocket_t *ptcs = &pluginFunctions.plugins[pID].sockets[connection];

    if (ptcs->sock < 1)
    {
        Com_PrintWarning("Plugin_TcpGetData: called on a non open socket for plugin ID: #%d\n", pID);
        return -1;
    }
    len = NET_TcpClientGetData(ptcs->sock, buf, size, errormsg, sizeof(errormsg));
    //    Com_DPrintf("PHandler_TcpGetData: Retrived data from socket %d @ %d\n", ptcs->sock, connection);

    if (len > 0)
    {
        return len;
    }

    if (len == NET_WANT_READ)
    {
        return 0;
    }
    Com_DPrintf("PHandler_TcpGetData[%d]: NET_Receive returned %s\n", pID, errormsg);
    NET_TcpCloseSocket(ptcs->sock);
    ptcs->sock = -1;
    return -1;
}

int PHandler_TcpSendData(int pID, int connection, void *data, int len)
{
    int state;

    pluginTcpClientSocket_t *ptcs = &pluginFunctions.plugins[pID].sockets[connection];

    if (ptcs->sock < 1)
    {
        Com_PrintWarning("Plugin_TcpSendData: called on a non open socket for plugin ID: #%d\n", pID);
        return -1;
    }
    state = NET_TcpSendData(ptcs->sock, data, len, NULL, 0);
    //    Com_DPrintf("PHandler_TcpSendData: Sent data from socket %d @ %d\n", ptcs->sock, connection);

    if (state == NET_WANT_WRITE)
    {
        return 0;
    }

    if (state == -1)
    {
        NET_TcpCloseSocket(ptcs->sock);
        ptcs->sock = -1;
        return -1;
    }
    return state;
}

void PHandler_TcpCloseConnection(int pID, int connection)
{
    pluginTcpClientSocket_t *ptcs = &pluginFunctions.plugins[pID].sockets[connection];

    if (ptcs->sock < 1)
    {
        Com_PrintWarning("Plugin_TcpCloseConnection: Called on a non open socket for plugin ID: #%d\n", pID);
        return;
    }
    NET_TcpCloseSocket(ptcs->sock);
    Com_DPrintf("PHandler_TcpCloseConnection: Closed socket %d @ %d\n", ptcs->sock, connection);
    ptcs->sock = -1;
}

/*
=====================================
 Functionality providers for exports
=====================================
*/

void PHandler_ChatPrintf(int slot, char *fmt, ...)
{
    char str[256];
    client_t *cl;
    va_list vl;

    cl = slot >= 0 ? &(svs.clients[slot]) : NULL;
    va_start(vl, fmt);
    vsprintf(str, fmt, vl);
    va_end(vl);
    SV_SendServerCommand(cl, "h \"%s\"", str);
}
void PHandler_BoldPrintf(int slot, char *fmt, ...)
{
    char str[256];
    client_t *cl;
    va_list vl;
    cl = slot >= 0 ? &(svs.clients[slot]) : NULL;
    va_start(vl, fmt);
    vsprintf(str, fmt, vl);
    va_end(vl);
    SV_SendServerCommand(cl, "c \"%s\"", str);
}
/*
void PHandler_CmdExecute_f()
{
    Com_DPrintf("Attempting to execute a plugin command '%s'.\n", Cmd_Argv(0));
    if (!pluginFunctions.enabled)
    {
        Com_DPrintf("Error! Tried executing a plugin command with plugins being disabled! Command name: '%s'.\n", Cmd_Argv(1));
        return;
    }
    char name[128];
    int i, j;
    void (*func)();
    strcpy(name, Cmd_Argv(0));
    for (i = 0; i < MAX_PLUGINS; i++)
    {
        if (pluginFunctions.plugins[i].loaded && pluginFunctions.plugins[i].enabled)
        {
            for (j = 0; j < pluginFunctions.plugins[i].cmds; j++)
            {
                if (strcmp(name, pluginFunctions.plugins[i].cmd[j].name) == 0)
                {
                    Com_DPrintf("Executing plugin command '%s' for plugin '%s', plugin ID: %d.\n", name, pluginFunctions.plugins[i].name, i);
                    func = (void (*)())(pluginFunctions.plugins[i].cmd[j].xcommand);
                    pluginFunctions.hasControl = i;
                    func();
                    pluginFunctions.hasControl = PLUGIN_UNKNOWN;
                    return;
                }
            }
        }
    }
}*/

void PHandler_Error(int pID, EPluginError_t code, char *string)
{
    if (pluginFunctions.plugins[pID].enabled == qfalse)
    {
        Com_PrintWarning("An error of ID %d and string \"%s\" occured in a disabled plugin with ID %d!\n", code, string, pID);
        return;
    }
    switch (code)
    {
    case P_ERROR_WARNING:
        Com_Printf("Plugin #%d ('%s') issued a warning: \"%s\"\n", pID, pluginFunctions.plugins[pID].name, string);
        break;
    case P_ERROR_DISABLE:
        Com_Printf("Plugin #%d ('%s') returned an error and will be disabled! Error string: \"%s\".\n", pID, pluginFunctions.plugins[pID].name, string);
        pluginFunctions.plugins[pID].enabled = qfalse;
        break;
    case P_ERROR_TERMINATE:
        Com_Printf("Plugin #%d ('%s') reported a critical error, the server will be terminated. Error string: \"%s\".\n", pID, pluginFunctions.plugins[pID].name, string);
        Com_Error(ERR_FATAL, "%s", string);
        break;
    default:
        Com_DPrintf("Plugin #%d ('%s') reported an unknown error! Error string: \"%s\", error code: %d.\n", pID, pluginFunctions.plugins[pID].name, string, code);
        break;
    }
}
/*
======
 Misc
======
*/

// TODO: LAMBDA <3
void PHandler_InitDynCallStub(struct dyncallstub_s *d, xfunction_t func, int pID)
{
    //Static Opcodes
    d->mov_eax_esp4[0] = 0x8b;
    d->mov_eax_esp4[1] = 0x44;
    d->mov_eax_esp4[2] = 0x24;
    d->mov_eax_esp4[3] = 0x04;
    d->push_eax = 0x50;
    d->move_eax_ptr = 0xb8;
    d->move_edx_ptr = 0xba;
    d->move_eax_edx[0] = 0x89;
    d->move_eax_edx[1] = 0x10;
    d->move_ecx_ptr = 0xb9;
    d->call_ecx[0] = 0xff;
    d->call_ecx[1] = 0xd1;
    d->add_esp4[0] = 0x83;
    d->add_esp4[1] = 0xc4;
    d->add_esp4[2] = 0x04;
    d->move_eax2_ptr = 0xb8;
    d->move_edx2_ptr = 0xba;
    d->move_eax_edx2[0] = 0x89;
    d->move_eax_edx2[1] = 0x10;
    d->ret = 0xc3;

    //Dynamic addresses
    d->hasControlAdr = &pluginFunctions.hasControl;
    d->hasControlAdr2 = &pluginFunctions.hasControl;
    d->pluginId = pID;
    d->nullpluginId = PLUGIN_UNKNOWN;
    d->xfunction = func;
}

void PHandler_Scr_AddFunction(char *name, xfunction_t function, qboolean replace, int pID)
{
    int i;

    if (pID >= MAX_PLUGINS)
    {
        Com_Printf("Error: tried adding a script command for a plugin with non existent pID. pID supplied: %d.\n", pID);
        return;
    }
    else if (pID < 0)
    {
        Com_Printf("Plugin Handler error: Plugin_ScrAddFunction or Plugin_ScrReplaceFunction called from not within a plugin or from a disabled plugin!\n");
        return;
    }
    if (!pluginFunctions.plugins[pID].loaded)
    {
        Com_Printf("Error: Tried adding a command for not loaded plugin! PID: %d.\n", pID);
    }
    Com_Printf("Adding a plugin script function for plugin %d, command name: %s.\n", pID, name);
    for (i = 0; i < MAX_SCRIPTFUNCTIONS; i++)
    {
        if (pluginScriptCallStubs.s[pID * MAX_SCRIPTFUNCTIONS + i].name[0] == 0)
        {
            break;
        }
    }
    if (i == MAX_SCRIPTFUNCTIONS)
    {
        Com_PrintError("Exceeded maximum number of scrip-functions (%d) for plugin\n", MAX_SCRIPTFUNCTIONS);
        return;
    }
    if (strlen(name) >= sizeof(pluginScriptCallStubs.s[pID * MAX_SCRIPTFUNCTIONS + i].name))
    {
        Com_PrintError("Exceeded maximum length of name for scrip-method: %s (%d) for plugin.\n", name, sizeof(pluginScriptCallStubs.s[pID * MAX_SCRIPTFUNCTIONS + i].name));
        return;
    }
    if (replace == qtrue)
    {
        Scr_RemoveFunction(name);
    }
    if (Scr_AddFunction(name, (xfunction_t)&pluginScriptCallStubs.s[pID * MAX_SCRIPTFUNCTIONS + i].dyncallstub, qfalse) == qfalse)
    {
        Com_PrintError("Failed to add this script function: %s for plugin\n", name);
        return;
    }
    Sys_MemoryProtectWrite(pluginScriptCallStubs.s, sizeof(pluginScriptCallStubs.s));
    Q_strncpyz(pluginScriptCallStubs.s[pID * MAX_SCRIPTFUNCTIONS + i].name, name, sizeof(pluginScriptCallStubs.s[pID * MAX_SCRIPTFUNCTIONS + i].name));
    pluginScriptCallStubs.s[pID * MAX_SCRIPTFUNCTIONS + i].isMethod = qfalse;
    PHandler_InitDynCallStub(&pluginScriptCallStubs.s[pID * MAX_SCRIPTFUNCTIONS + i].dyncallstub, function, pID);
    Sys_MemoryProtectExec(pluginScriptCallStubs.s, sizeof(pluginScriptCallStubs.s));
    pluginFunctions.plugins[pID].scriptfunctions++;
}

void PHandler_Scr_AddMethod(char *name, xfunction_t function, qboolean replace, int pID)
{
    int i;

    if (pID >= MAX_PLUGINS)
    {
        Com_Printf("Error: tried adding a script command for a plugin with non existent pID. pID supplied: %d.\n", pID);
        return;
    }
    else if (pID < 0)
    {
        Com_Printf("Plugin Handler error: Plugin_Scr_AddMethod or Plugin_Scr_ReplaceMethod called from not within a plugin or from a disabled plugin!\n");
        return;
    }
    if (!pluginFunctions.plugins[pID].loaded)
    {
        Com_Printf("Error: Tried adding a command for not loaded plugin! PID: %d.\n", pID);
    }
    Com_Printf("Adding a plugin script method for plugin %d, command name: %s.\n", pID, name);
    for (i = 0; i < MAX_SCRIPTFUNCTIONS; i++)
    {
        if (pluginScriptCallStubs.s[pID * MAX_SCRIPTFUNCTIONS + i].name[0] == 0)
        {
            break;
        }
    }
    if (i == MAX_SCRIPTFUNCTIONS)
    {
        Com_PrintError("Exceeded maximum number of scrip-functions (%d) for plugin\n", MAX_SCRIPTFUNCTIONS);
        return;
    }
    if (strlen(name) >= sizeof(pluginScriptCallStubs.s[pID * MAX_SCRIPTFUNCTIONS + i].name))
    {
        Com_PrintError("Exceeded maximum length of name for scrip-method: %s (%d) for plugin.\n", name, sizeof(pluginScriptCallStubs.s[pID * MAX_SCRIPTFUNCTIONS + i].name));
        return;
    }
    if (replace == qtrue)
    {
        Scr_RemoveMethod(name);
    }
    if (Scr_AddMethod(name, (xfunction_t)&pluginScriptCallStubs.s[pID * MAX_SCRIPTFUNCTIONS + i].dyncallstub, qfalse) == qfalse)
    {
        Com_PrintError("Failed to add this script method: %s for plugin\n", name);
        return;
    }
    Sys_MemoryProtectWrite(pluginScriptCallStubs.s, sizeof(pluginScriptCallStubs.s));
    Q_strncpyz(pluginScriptCallStubs.s[pID * MAX_SCRIPTFUNCTIONS + i].name, name, sizeof(pluginScriptCallStubs.s[pID * MAX_SCRIPTFUNCTIONS + i].name));
    pluginScriptCallStubs.s[pID * MAX_SCRIPTFUNCTIONS + i].isMethod = qtrue;
    PHandler_InitDynCallStub(&pluginScriptCallStubs.s[pID * MAX_SCRIPTFUNCTIONS + i].dyncallstub, function, pID);
    Sys_MemoryProtectExec(pluginScriptCallStubs.s, sizeof(pluginScriptCallStubs.s));
    pluginFunctions.plugins[pID].scriptmethods++;
}

qboolean PHandler_TcpConnectMT(int pID, int connection, const char *remote)
{
    if (pID < 0)
    {
        Com_Printf("Plugins: Error! Tried open a TCP-Connection for unknown plugin!\n");
        return qfalse;
    }
    if (pluginFunctions.plugins[pID].enabled == qfalse)
    {
        Com_Printf("^1WARNING^7: Tried open a TCP-Connection for a disabled plugin!\n");
        return qfalse;
    }
    if (connection >= PLUGIN_MAX_SOCKETS || connection < 0)
    {
        Com_PrintError("Plugin_TcpConnect: Second argument can only be a value inside the range: 0...%d plugin ID: #%d\n", PLUGIN_MAX_SOCKETS);
        return qfalse;
    }
    return PHandler_TcpConnect(pID, remote, connection);
}

int PHandler_TcpGetDataMT(int pID, int connection, void *buf, int size)
{
    if (pID < 0 || pID >= MAX_PLUGINS)
    {
        Com_Printf("Plugin_TcpGetData: Error! Tried get TCP data for unknown plugin!\n");
        return -1;
    }
    if (pluginFunctions.plugins[pID].enabled == qfalse)
    {
        Com_Printf("^1WARNING^7: Plugin_TcpGetData: Tried get TCP data for a disabled plugin!\n");
        return -1;
    }
    if (connection >= PLUGIN_MAX_SOCKETS || connection < 0)
    {
        Com_PrintError("Plugin_TcpGetData: First argument can only be a value inside the range: 0...%d plugin ID: #%d\n", PLUGIN_MAX_SOCKETS, pID);
        return -1;
    }
    if (buf == NULL)
    {
        Com_PrintError("Plugin_TcpGetData: Third argument can not be a NULL-Pointer for plugin ID: #%d\n", pID);
        return -1;
    }

    return PHandler_TcpGetData(pID, connection, buf, size);
}

qboolean PHandler_TcpSendDataMT(int pID, int connection, void *data, int len)
{
    if (pID < 0 || pID >= MAX_PLUGINS)
    {
        Com_Printf("Plugin_TcpSendData: Error! Tried get TCP data for unknown plugin!\n");
        return qfalse;
    }
    if (pluginFunctions.plugins[pID].enabled == qfalse)
    {
        Com_Printf("^1WARNING^7: Plugin_TcpSendData: Tried get TCP data for a disabled plugin!\n");
        return qfalse;
    }
    if (connection >= PLUGIN_MAX_SOCKETS || connection < 0)
    {
        Com_PrintError("Plugin_TcpSendData: Second argument can only be a value inside the range: 0...%d plugin ID: #%d\n", PLUGIN_MAX_SOCKETS, pID);
        return qfalse;
    }
    if (data == NULL)
    {
        Com_PrintError("Plugin_TcpSendData: Second argument can not be a NULL-Pointer for plugin ID: #%d\n", pID);
        return qfalse;
    }

    return PHandler_TcpSendData(pID, connection, data, len);
}
// todo: move to callback + few upper
void PHandler_TcpCloseConnectionMT(int pID, int connection)
{
    //Identify the calling plugin
    if (pID < 0 || pID >= MAX_PLUGINS)
    {
        Com_Printf("Plugin_TcpCloseConnection: Error! Tried get close a connection for unknown plugin!\n");
        return;
    }
    if (pluginFunctions.plugins[pID].enabled == qfalse)
    {
        Com_Printf("^1WARNING^7: Plugin_TcpCloseConnection: Tried to close a connection for a disabled plugin!\n");
        return;
    }
    if (connection >= PLUGIN_MAX_SOCKETS || connection < 0)
    {
        Com_PrintError("Plugin_TcpCloseConnection: Second argument can only be a value inside the range: 0...%d plugin ID: #%d\n", PLUGIN_MAX_SOCKETS, pID);
        return;
    }
    PHandler_TcpCloseConnection(pID, connection);
}