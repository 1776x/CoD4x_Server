#include "PluginHandler.h"
#include "KnownPlugins.h"
#include "PHandlerCmds.h"
#include "../cmd.h"
#include "../qcommon.h"
#include "../sec_crypto.h"
#include "../sys_net_types.h"
#include "phandler_shared_types.h"

using namespace std;

#ifndef FUNCTION_NAME
#ifdef WIN32   //WINDOWS
#define FUNCTION_NAME (__FUNCTION__)
#else          //*NIX
#define FUNCTION_NAME (__func__)
#endif
#endif

#define THREAD_UNSAFE() \
do { \
    if (Sys_IsMainThread() == qfalse) \
    { \
        Com_PrintError("Attempting to execute non thread safe function '%s'\n", FUNCTION_NAME); \
        return; \
    } \
} while(0)

#define THREAD_UNSAFE_RET(retVal) \
do { \
    if (Sys_IsMainThread() == qfalse) \
    { \
        Com_PrintError("Attempting to execute non thread safe function '%s'\n", FUNCTION_NAME); \
        return retVal; \
    } \
} while(0)

#define DURING_EVENT_ONLY() \
    do { \
        if (!m_CurrentPlugin) \
        { \
            Com_PrintError("Attempt to call function '%s' outside of plugin event\n", FUNCTION_NAME); \
            return; \
        } \
    } while(0)

#define DURING_EVENT_ONLY_RET(retVal) \
    do { \
        if (!m_CurrentPlugin) \
        { \
            Com_PrintError("Attempt to call function '%s' outside of plugin event\n", FUNCTION_NAME); \
            return retVal; \
        } \
    } while(0)

static CPluginHandler g_Instance;

CPluginHandler* PluginHandler()
{
    return &g_Instance;
}

CPluginHandler::CPluginHandler() :
    m_Initialized(false),
    m_CurrentPlugin(nullptr)
{
}

CPluginHandler::~CPluginHandler()
{
    // TODO: cleanup required?
    // I meant Cmd_RemoveCommand etc.
}

void CPluginHandler::Init()
{
    if (m_Initialized)
    {
        Com_Printf("Error: you are trying to initialize plugin handler more than once. Stop it!\n");
        return;
    }

    Cmd_AddCommand("loadplugin", OnCmd_LoadPlugin);
    Cmd_AddCommand("unloadplugin", OnCmd_UnloadPlugin);
    Cmd_AddCommand("plugins", OnCmd_PluginList);
    Cmd_AddCommand("plugininfo", OnCmd_PluginInfo);

    m_Initialized = true;
    Com_Printf("-------- Plugin handler initialization completed --------\n");
}

void CPluginHandler::LoadPlugin(const char* LibName_)
{
    // Checking if the plugin is not already loaded.
    if (m_Plugins.find(LibName_) != m_Plugins.end())
    {
        Com_Printf("This plugin already loaded\n");
        return;
    }


    string pluginPath = getPluginFilePath(LibName_);
    // Checking if we can load this plugin.
    if (!isLegacyPlugin(pluginPath))
    {
        Com_Printf("This plugin can not be loaded in secure mode\n");
        return;
    }


    // Begin loading new plugin.
    m_Plugins.emplace(make_pair(LibName_, CPlugin()));
    //CPlugin plugin;
    CPlugin& plugin = m_Plugins[LibName_];
    plugin.LoadFromFile(pluginPath);


    Com_DPrintf("Fetching plugin information...");
    SPluginInfo_t info;
    m_CurrentPlugin = &plugin;
    if (!plugin.Event(PLUGINS_ONINFOREQUEST, &info))
    {
        Com_PrintError("Plugin function '%s' not found\n", GetEventName(PLUGINS_ONINFOREQUEST));
        plugin.Unload();
        m_CurrentPlugin = nullptr;
        m_Plugins.erase(LibName_);
        return;
    }

    if (info.handlerVersion.major != PLUGIN_HANDLER_VERSION_MAJOR || (info.handlerVersion.minor - info.handlerVersion.minor % 100) != (PLUGIN_HANDLER_VERSION_MINOR - PLUGIN_HANDLER_VERSION_MINOR % 100))
    {
        Com_PrintError("This plugin might not be compatible with this server version! Requested plugin handler version: %d.%d, server's plugin handler version: %d.%d. Unloading the plugin...\n", info.handlerVersion.major, info.handlerVersion.minor, PLUGIN_HANDLER_VERSION_MAJOR, PLUGIN_HANDLER_VERSION_MINOR);
        plugin.Unload();
        m_Plugins.erase(LibName_);
        return;
    }
    Com_DPrintf("done\n");


    Com_DPrintf("Executing plugin's OnInit...");
    // plugin version mismatch.
    int success = 0;
    if (!plugin.Event(PLUGINS_ONINIT, &success))
    {
        Com_PrintError("Plugin function '%s' not found\n", GetEventName(PLUGINS_ONINIT));
        plugin.Unload();
        m_CurrentPlugin = nullptr;
        m_Plugins.erase(LibName_);
        return;
    }
    m_CurrentPlugin = nullptr;

    if (success < 0)
    {
        Com_PrintError("Plugin initialization failed: %d\n", success);
        plugin.Unload();
        m_Plugins.erase(LibName_);
        return;
    }
    Com_DPrintf("done\n");


    plugin.SetInitialized(true);
    // At this point plugin successfully initialized and when at unloading it will fire "OnTerminate" event.
    // Keep passed name as key instead of file path.
    Com_Printf("Plugin loaded successfully. Server is currently running %d plugins\n", m_Plugins.size());
}

void CPluginHandler::UnloadPlugin(const char* LibName_)
{
    auto plugin = m_Plugins.find(LibName_);
    if (plugin == m_Plugins.end())
    {
        Com_Printf("Plugin '%s' is not loaded\n", LibName_);
        return;
    }
    m_CurrentPlugin = &plugin->second;
    plugin->second.Unload(); // May execute event.
    m_CurrentPlugin = nullptr;

    m_Plugins.erase(plugin);
    Com_Printf("Plugin '%s' has been unloaded\n", LibName_);
}

void CPluginHandler::PrintPluginInfo(const char* LibName_)
{
    auto plugin = m_Plugins.find(LibName_);
    if (plugin == m_Plugins.end())
    {
        Com_Printf("Plugin '%s' is not loaded\n", LibName_);
        return;
    }
    m_CurrentPlugin = &plugin->second;
    plugin->second.PrintPluginInfo();
    m_CurrentPlugin = nullptr;
}

void CPluginHandler::PrintPluginsSummary()
{
    int maj, min;
    getVersion(maj, min);
    Com_Printf("Plugin handler version: %d.%d\n\n", maj, min);

    if (!m_Plugins.size())
    {
        Com_Printf("No plugins are loaded\n");
        return;
    }

    Com_Printf("Loaded plugins:\n\n");
    Com_Printf("+----------------------+----------+--------------------+----------------------+\n");
    Com_Printf("|         name         | enabled? | memory allocations | total all. mem. in B |\n");
    Com_Printf("+----------------------+----------+--------------------+----------------------+\n");
    for (auto& itPlugin : m_Plugins)
    {
        const CPlugin& plugin = itPlugin.second;
        Com_Printf("| %-21s| %-9s| %-19d| %-21d|\n", itPlugin.first, "yes", plugin.GetMemAllocs(), plugin.GetMemAllocsSize());
    }
    Com_Printf("+----------------------+----------+--------------------+----------------------+\n");
}

void* CPluginHandler::Malloc(size_t Size_)
{
    DURING_EVENT_ONLY_RET(nullptr);
    return m_CurrentPlugin->Malloc(Size_);
}

void CPluginHandler::Free(const void* Ptr_)
{
    DURING_EVENT_ONLY();
    m_CurrentPlugin->Free(Ptr_);
}

void CPluginHandler::AddConsoleCommand(const char* const Name_, xcommand_t fpCallback_, int Power_ /*= 0*/)
{
    DURING_EVENT_ONLY();
    m_CurrentPlugin->AddConsoleCommand(Name_, fpCallback_, Power_);
}

void CPluginHandler::RemoveConsoleCommand(const char* const Name_)
{
    DURING_EVENT_ONLY();
    m_CurrentPlugin->RemoveConsoleCommand(Name_);
}

void CPluginHandler::PluginError(EPluginError_t Code_, const char* const Message_)
{
    DURING_EVENT_ONLY();

    switch (Code_)
    {
    case P_ERROR_WARNING:
        Com_Printf("Plugin issued a warning: \"%s\"\n", Message_);
        break;
    case P_ERROR_DISABLE:
        Com_Printf("Plugin returned an error and will be disabled! Error string: \"%s\".\n", Message_);
        // TODO: disable current plugin.
        //pluginFunctions.plugins[pID].enabled = qfalse;
        break;
    case P_ERROR_TERMINATE:
        Com_Printf("Plugin reported a critical error, the server will be terminated. Error string: \"%s\".\n", Message_);
        Com_Error(ERR_FATAL, "%s", Message_);
        break;
    default:
        Com_DPrintf("Plugin reported an unknown error! Error string: \"%s\", error code: %d.\n", Message_, Code_);
        break;
    }
}

int CPluginHandler::TCP_Connect(const char *const Remote_, FPNetworkReceiveCallback ReceiveCallback_)
{
    DURING_EVENT_ONLY_RET(SOCKET_ERROR);
    return m_CurrentPlugin->TCP_Connect(Remote_, ReceiveCallback_);
}

int CPluginHandler::TCP_Send(const int Connection_, const void *const Data_, unsigned int Size_)
{
    DURING_EVENT_ONLY_RET(SOCKET_ERROR);
    return m_CurrentPlugin->TCP_Send(Connection_, Data_, Size_);
}

int CPluginHandler::TCP_Receive(const int Connection_, const void *const Buffer_, unsigned int Size_)
{
    DURING_EVENT_ONLY_RET(SOCKET_ERROR);
    return m_CurrentPlugin->TCP_Receive(Connection_, Buffer_, Size_);
}

void CPluginHandler::TCP_Close(const int Connection_)
{
    DURING_EVENT_ONLY();
    m_CurrentPlugin->TCP_Close(Connection_);
}

void CPluginHandler::Print(const char* const Msg_)
{
    DURING_EVENT_ONLY();
    Com_Printf(Msg_);
}

void CPluginHandler::PrintWarning(const char* const Msg_)
{
    DURING_EVENT_ONLY();
    Com_PrintWarning(Msg_);
}

void CPluginHandler::PrintError(const char* const Msg_)
{
    DURING_EVENT_ONLY();
    Com_PrintError(Msg_);
}

void CPluginHandler::PrintDeveloper(const char* const Msg_)
{
    DURING_EVENT_ONLY();
    Com_DPrintf(Msg_);
}

void CPluginHandler::PrintAdministrativeLog(const char* const Msg_)
{
    THREAD_UNSAFE();
    DURING_EVENT_ONLY();
    SV_PrintAdministrativeLog(Msg_);
}

void CPluginHandler::FillWithRandomBytes(byte* Buffer_, const int Size_)
{
    THREAD_UNSAFE();
    DURING_EVENT_ONLY();
    Com_RandomBytes(Buffer_, Size_);
}

time_t CPluginHandler::GetRealTime()
{
    THREAD_UNSAFE_RET(0);
    DURING_EVENT_ONLY(0);
    return Com_GetRealtime();
}

void CPluginHandler::AddBanByIP(netadr_t* Remote_, const char* const Message_, int Expire_)
{
    THREAD_UNSAFE();
    DURING_EVENT_ONLY();
    SV_PlayerAddBanByIp(Remote_, Message_, Expire_);
}

void CPluginHandler::RemoveBanByIP(netadr_t* Remote_)
{
    THREAD_UNSAFE();
    DURING_EVENT_ONLY();
    SV_RemoveBanByIP(Remote_);
}

void CPluginHandler::GetBanTimeLimit(int MinutesLeft_, char* const Buffer_, const int Size_)
{
    THREAD_UNSAFE();
    DURING_EVENT_ONLY();
    SV_WriteBanTimelimit(MinutesLeft_, Buffer_, Size_);
}

void CPluginHandler::GetBanMessage(int MinutesLeft_, char* const Buffer_, const int Size_, const char* const Reason_)
{
    THREAD_UNSAFE();
    DURING_EVENT_ONLY();
    SV_FormatBanMessage(MinutesLeft_, Buffer_, Size_, Reason_);
}

void CPluginHandler::SteamIDToString(uint64_t SteamID_, char* const Buffer_, const int Size_)
{
    DURING_EVENT_ONLY();
    SV_SApiSteamIDToString(SteamID_, Buffer_, Size_);
}

void CPluginHandler::SteamIDToString64(uint64_t SteamID_, char* const Buffer_, const int Size_)
{
    DURING_EVENT_ONLY();
    SV_SApiSteamIDTo64String(SteamID_, Buffer_, Size_);
}

uint64_t CPluginHandler::StringToSteamID(const char* const String_) const
{
    DURING_EVENT_ONLY_RET(0);
    return SV_SApiStringToID(String_);
}

bool CPluginHandler::IsSteamIDIndividual(uint64_t SteamID_) const
{
    DURING_EVENT_ONLY_RET(false);
    return SV_SApiSteamIDIndividual(SteamID_) == qtrue ? true : false;
}

void CPluginHandler::AddCommandForPlayerToWhitelist(const int ClientNum_, const char* const Command_) const
{
    THREAD_UNSAFE();
    DURING_EVENT_ONLY();
    Auth_AddCommandForClientToWhitelist(ClientNum_, Command_);
}

bool CPluginHandler::CanPlayerUseCommand(const int ClientNum_, const char* const Command_) const
{
    THREAD_UNSAFE_RET(false);
    DURING_EVENT_ONLY_RET(false);
    return Auth_CanPlayerUseCommand(ClientNum_, Command_) == qtrue ? true : false;
}

bool CPluginEvent::IsSteamIDIndividualSteamOnly(uint64_t SteamID_) const
{
    DURING_EVENT_ONLY_RET(false);
    return SV_SApiSteamIDIndividualSteamOnly(SteamID_) == qtrue ? true : false;
}



bool CPluginHandler::isLegacyPlugin(const string& LibPath_) const
{
    // Do not test against name.
    // If plugin's checksum known - we know this plugin and we can load it no matter what name is.
    if (!com_securemode)
        return true;

    // Get hash of this file.
    char pluginHash[128] = {'\0'};
    unsigned long sizeOfHash = sizeof(pluginHash);
    Sec_HashFile(SEC_HASH_TIGER, LibPath_.c_str(), pluginHash, &sizeOfHash, qfalse);

    // Compare find file hash in the list of known plugins.
    for (int i = 0; i < GetKnownPluginsCount(); ++i)
    {
        if (!memcmp(pluginHash, GetKnownPluginHash(i), sizeof(pluginHash)))
            return true;
    }

    Com_PrintError("This plugin can not be loaded in secure mode\n");
    return false;
}

void CPluginHandler::getVersion(int& Major_, int& Minor_) const
{
    Major_ = 4;
    Minor_ = 0;
}

string CPluginHandler::getPluginFilePath(const char* LibName_) const
{
    Com_DPrintf("Checking if the plugin file exists and is of correct format...\n");
    // TODO
    #if 0
    //Additional test if a file is there
        realpath = (char *)PHandler_OpenTempFile(name, filepathbuf, sizeof(filepathbuf)); // Load a plugin, safe for use
        if (realpath == NULL)
        {
            return;
        }
    #endif
    return string(LibName_);
}
