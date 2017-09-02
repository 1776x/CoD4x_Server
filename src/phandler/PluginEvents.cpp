#include "PluginEvents.h"

static struct PluginEventsInfo_t
{
    EPluginEvent EventIdx;
    const char* CallbackName;
} g_PluginEventsInfo[PLUGINS_EVENTS_COUNT] = {
    {PLUGINS_ONINIT, "OnInit"},
    {PLUGINS_ONINFOREQUEST, "OnInfoRequest"},
    {PLUGINS_ONUNLOAD, "OnUnload"},
    {PLUGINS_ONPLAYERDC, "OnPlayerDC"},
    {PLUGINS_ONPLAYERCONNECT, "OnPlayerConnect"},
    {PLUGINS_ONEXITLEVEL, "OnExitLevel"},
    {PLUGINS_ONMESSAGESENT, "OnMessageSent"},
    {PLUGINS_ONFRAME, "OnFrame"},
    {PLUGINS_ONONESECOND, "OnOneSecond"},
    {PLUGINS_ONTENSECONDS, "OnTenSeconds"},
    {PLUGINS_ONCLIENTAUTHORIZED, "OnClientAuthorized"},
    {PLUGINS_ONCLIENTSPAWN, "OnClientSpawn"},
    {PLUGINS_ONCLIENTENTERWORLD, "OnClientEnterWorld"},
    {PLUGINS_ONTCPSERVERPACKET, "OnTcpServerPacket"},
    {PLUGINS_ONUDPNETEVENT, "OnUdpNetEvent"},
    {PLUGINS_ONUDPNETSEND, "OnUdpNetSend"},
    {PLUGINS_ONSPAWNSERVER, "OnSpawnServer"},
    {PLUGINS_ONPREFASTRESTART, "OnPreFastRestart"},
    {PLUGINS_ONPOSTFASTRESTART, "OnPostFastRestart"},
    {PLUGINS_ONCLIENTUSERINFOCHANGED, "OnClientUserinfoChanged"},
    {PLUGINS_ONCLIENTMOVECOMMAND, "OnClientMoveCommand"},
    {PLUGINS_ONPLAYERWANTRESERVEDSLOT, "OnPlayerWantReservedSlot"},
    {PLUGINS_ONFSSTARTED, "OnFilesystemStarted"},
    {PLUGINS_ONPLAYERGOTAUTHINFO, "OnPlayerGotAuthInfo"},
    {PLUGINS_ONPLAYERADDBAN, "OnPlayerAddBan"},
    {PLUGINS_ONPLAYERGETBANSTATUS, "OnPlayerGetBanStatus"},
    {PLUGINS_ONPLAYERREMOVEBAN, "OnPlayerRemoveBan"},
    {PLUGINS_ONMODULELOADED, "OnModuleLoaded"},
    {PLUGINS_ONSCREENSHOTARRIVED, "OnScreenshotArrived"},
    {PLUGINS_ONTERMINATE, "OnTerminate"},
    {PLUGINS_SCRIPT_ONGAMETYPELOADED, "OnScript_GametypeLoaded"},
    {PLUGINS_SCRIPT_ONLEVELLOADED, "OnScript_LevelLoaded"},
    {PLUGINS_SCRIPT_ONGAMETYPESTARTED, "OnScript_GametypeStarted"},
    {PLUGINS_SCRIPT_ONPLAYERCONNECTED, "OnScript_PlayerConnected"},
    {PLUGINS_SCRIPT_ONPLAYERDISCONNECTED, "OnScript_PlayerDisconnected"},
    {PLUGINS_SCRIPT_ONPLAYERDAMAGE, "OnScript_PlayerDamage"},
    {PLUGINS_SCRIPT_ONPLAYERKILLED, "OnScript_PlayerKilled"},
    {PLUGINS_SCRIPT_ONPLAYERLASTSTAND, "OnScript_PlayerLastStand"}
};

const char* const GetEventName(EPluginEvent EventIdx_)
{
    if (EventIdx_ < PLUGINS_EVENTS_START || EventIdx_ >= PLUGINS_EVENTS_COUNT)
        return nullptr;
    return g_PluginEventsInfo[EventIdx_].CallbackName;
}