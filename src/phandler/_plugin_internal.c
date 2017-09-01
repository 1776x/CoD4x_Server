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
#include "../q_platform.h"
#include "../sys_main.h"
#include "../objfile_parser.h"
#include "../sec_crypto.h"
 
/*=========================================*
 *                                         *
 *       Plugin Handler's main file        *
 *                                         *
 *   Functions in this file are the most   *
 *     important for Plugin Handler.       *
 *    Those functions are safe for use     *
 *  anywhere in the server's source code.  *
 *                                         *
 *=========================================*/

pluginWrapper_t pluginFunctions;
pluginScriptCallStubBase_t __attribute__((section(".text#"))) pluginScriptCallStubs;

const char *PHandler_OpenTempFile(char *name, char *fullfilepath, int fplen)
{ // Load a plugin, safe for use

    void *buf;
    int len;
    int wlen;
    char *file;
    char tmpfile[MAX_QPATH];
    char filepath[MAX_QPATH];

    Com_sprintf(filepath, sizeof(filepath), "plugins/%s" DLL_EXT, name);

    len = FS_SV_ReadFile(filepath, &buf);

    if (len < 100)
        len = FS_ReadFile(filepath, &buf);

    if (len < 100)
    {
        Com_Printf("No such file found: %s. Can not load this plugin.\n", filepath);
        return NULL;
    }

    if (PHandler_VerifyPlugin(buf, len) == qfalse)
    {
        Com_Printf("%s is not a plugin file or is corrupt or contains disallowed functions.\n", filepath);
        FS_FreeFile(buf);
        return NULL;
    }
    Com_sprintf(tmpfile, sizeof(tmpfile), "plugin.%s.tmp", name);
    /* If there is already such a file remove it now */
    file = FS_SV_GetFilepath(tmpfile, fullfilepath, fplen);
    if (file)
    {
        FS_RemoveOSPath(file);
        file = FS_SV_GetFilepath(tmpfile, fullfilepath, fplen);
        if (file)
        {
            FS_RemoveOSPath(file);
        }
    }
    wlen = FS_SV_HomeWriteFile(tmpfile, buf, len);
    if (wlen != len)
    {
        Com_PrintError("fs_homepath is readonly. Can not load this plugin.\n");
        FS_FreeFile(buf);
        return NULL;
    }
    //Additional test if a file is there and creation of full filepath
    FS_FreeFile(buf);
    return FS_SV_GetFilepath(tmpfile, fullfilepath, fplen);
}

void PHandler_CloseTempFile(char *filepath)
{
    if (!com_developer || com_developer->integer == 0)
        FS_RemoveOSPath(filepath);
}

#define PLUGINCENSOR_HASH "bfb496df0acc1bd01a0789b8d35d8081143db883297206aa"
#define PLUGINANTISPAM_HASH "7fc95f3902bd809a1e50a783fbb482044f67ad8927259a36"
#define PLUGINGAMERANGER_HASH "6609a69715a41b486611fa1c461f90acfed836eac0e699d8"

int PHandler_GetID(const char *name) // Get ID of a plugin by name, safe for use
{
    for (int i = 0; i < MAX_PLUGINS; ++i)
        if (!Q_stricmp(name, pluginFunctions.plugins[i].name))
            return i;

    return PLUGIN_UNKNOWN;
}

void PHandler_Event(PluginEvents Event_, ...) // Fire a plugin event, safe for use
{
    if (!pluginFunctions.enabled)
        return;

    if (Event_ < PLUGINS_EVENTS_START || Event_ >= PLUGINS_EVENTS_COUNT)
    {
        Com_DPrintf("Plugins: unknown event occured! Event ID: %d.\n", Event_);
        return;
    }

    va_list argptr;

    va_start(argptr, Event_);
    void *arg_0 = va_arg(argptr, void *);
    void *arg_1 = va_arg(argptr, void *);
    void *arg_2 = va_arg(argptr, void *);
    void *arg_3 = va_arg(argptr, void *);
    void *arg_4 = va_arg(argptr, void *);
    void *arg_5 = va_arg(argptr, void *);

    va_end(argptr);

    for (int i = 0; i < MAX_PLUGINS; i++)
    {
        if (!pluginFunctions.plugins[i].loaded || !pluginFunctions.plugins[i].enabled)
            continue;

        if (pluginFunctions.plugins[i].OnEvent[Event_])
        {
            pluginFunctions.hasControl = i;
            (*pluginFunctions.plugins[i].OnEvent[Event_])(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5);
            pluginFunctions.hasControl = PLUGIN_UNKNOWN;
        }
    }
}
