#pragma once

// We want to execute event by unique ID and not by name so this enum is required.
// If you editing this enum, look inside plugin_handler.c - there are mapping available.
enum EPluginEvent
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
};

// Enum and string array are not bound to themselves so there may happen mismatches.
// So this function required to map event ID to its name.
const char* const GetEventName(EPluginEvent EventIdx_);
