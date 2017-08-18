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
#if !defined _PLUGIN_EVENTS_H
#define _PLUGIN_EVENTS_H

// We want to execute event by unique ID and not by name so this enum is required.
// If you editing this enum, look inside plugin_handler.c - there are mapping available.
typedef enum PluginEvents
{
    PLUGINS_EVENTS_START = 0,

    PLUGINS_ONINIT = PLUGINS_EVENTS_START,
    PLUGINS_ONINFOREQUEST,
    PLUGINS_ONUNLOAD,
    PLUGINS_ONPLAYERDC,
    PLUGINS_ONPLAYERCONNECT,
    PLUGINS_ONEXITLEVEL,
    PLUGINS_ONMESSAGESENT,
    PLUGINS_ONFRAME,
    PLUGINS_ONONESECOND,
    PLUGINS_ONTENSECONDS,
    PLUGINS_ONCLIENTAUTHORIZED,
    PLUGINS_ONCLIENTSPAWN,
    PLUGINS_ONCLIENTENTERWORLD,
    PLUGINS_ONTCPSERVERPACKET,
    PLUGINS_ONUDPNETEVENT,
    PLUGINS_ONUDPNETSEND,
    PLUGINS_ONSPAWNSERVER,
    PLUGINS_ONPREFASTRESTART,
    PLUGINS_ONPOSTFASTRESTART,
    PLUGINS_ONCLIENTUSERINFOCHANGED,
    PLUGINS_ONCLIENTMOVECOMMAND,
    PLUGINS_ONPLAYERWANTRESERVEDSLOT,
    PLUGINS_ONFSSTARTED,
    PLUGINS_ONPLAYERGOTAUTHINFO,
    PLUGINS_ONPLAYERADDBAN,
    PLUGINS_ONPLAYERGETBANSTATUS,
    PLUGINS_ONPLAYERREMOVEBAN,
    PLUGINS_ONMODULELOADED,
    PLUGINS_ONSCREENSHOTARRIVED,
    PLUGINS_ONTERMINATE,
    PLUGINS_SCRIPT_ONGAMETYPELOADED,        // Gametype's main executed.
    PLUGINS_SCRIPT_ONLEVELLOADED,           // Level's main executed.
    PLUGINS_SCRIPT_ONGAMETYPESTARTED,       // CodeCallback_StartGametype executed.
    PLUGINS_SCRIPT_ONPLAYERCONNECTED,       // CodeCallback_PlayerConnect executed.
    PLUGINS_SCRIPT_ONPLAYERDISCONNECTED,    // CodeCallback_PlayerDisconnect executed.
    PLUGINS_SCRIPT_ONPLAYERDAMAGE,          // CodeCallback_PlayerDamage executed.
    PLUGINS_SCRIPT_ONPLAYERKILLED,          // CodeCallback_PlayerKilled executed.
    PLUGINS_SCRIPT_ONPLAYERLASTSTAND,       // CodeCallback_PlayerLastStand executed.

    PLUGINS_EVENTS_COUNT
} PluginEvents;

// Enum and string array are not bound to themselves so there may happen mismatches.
// So this function required to map event ID to its name.
const char* const GetEventName(PluginEvents EventIdx_);

#endif
