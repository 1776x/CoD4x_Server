#pragma once
#include "Plugin.h"
#include "../qcommon_io.h"
#include <map>
#include <string>

class CPluginHandler
{
public:
    CPluginHandler();
    ~CPluginHandler();

    // No copy class.
    CPluginHandler(const CPluginHandler&) = delete;
    void operator =(const CPluginHandler&) = delete;

    ////////////////////////////////
    // Plugin handler management. //
    ////////////////////////////////

    //////////////////////////////
    // Initializes plugin handler.
    void Init();

    ////////////////////////
    // Plugin management. //
    ////////////////////////

    ///////////////////////////////////
    // Loads plugin by its LibName_.
    void LoadPlugin(const char* LibName_);

    ///////////////////////////////////
    // Unload plugin by name LibName_.
    void UnloadPlugin(const char* LibName_);

    ///////////////////////////////////////////////
    // Prints info about plugin with name LibName_.
    void PrintPluginInfo(const char* LibName_);

    //////////////////////////////////////////
    // Prints all plugins summary information.
    void PrintPluginsSummary();

    /////////////////////
    // Fire plugin event.
    template<class...TParms>
    void PluginEvent(EPluginEvent Event_, TParms...Params)
    {
        if (Event_ < PLUGINS_EVENTS_START || Event_ >= PLUGINS_EVENTS_COUNT)
        {
            Com_PrintError("Unknown plugin event");
            return;
        }

        for(auto& plugin : m_Plugins)
        {
            m_CurrentPlugin = &plugin.second;
            m_CurrentPlugin->Event(Event_, Params...);
        }
        m_CurrentPlugin = nullptr;
    }
    
    ///////////////////////////////////////////
    // Allocates RAM for CURRENT plugin.
    void* Malloc(size_t Size_);

    ///////////////////////////////
    // Frees RAM allocated earlier.
    void Free(const void* Ptr_);

    ////////////////////////////////////////////
    // Add console command with specified power.
    void AddConsoleCommand(const char* const Name_, xcommand_t fpCallback_, int Power_ = 0);

    ///////////////////////////////////////
    // Remove console command from plugins.
    void RemoveConsoleCommand(const char* const Name_);

    /////////////////////////
    // Plugin error happened.
    void PluginError(EPluginError_t Code_, const char* const Message_);

    ///////////////////////////////////////////////////////////////////////////////////////////
    // Open new TCP connection for current plugin.
    // ReceiveCallback_ is a pointer to a function which gets executed when new data available.
    // Returns connection index or SOCKET_ERROR.
    int TCP_Connect(const char* const Remote_, FPNetworkReceiveCallback ReceiveCallback_);

    /////////////////////////////////////////////////////////////
    // Send TCP data for current plugin for specified connection.
    // Returns count of sent bytes or SOCKET_ERROR.
    int TCP_Send(const int Connection_, const void* const Data_, unsigned int Size_);

    ///////////////////////////////////////////////////////////////
    // Receive TCP data from current plugin's specified connection.
    // Returns count of received bytes or SOCKET_ERROR.
    int TCP_Receive(const int Connection_, void* const Buffer_, unsigned int Size_);

    ////////////////////////////////////////////
    // Close TCP connections for current plugin.
    void TCP_Close(const int Connection_);

    ////////////////////////////
    // Print message to console.
    void Print(const char* const Msg_);

    //////////////////////////////////////////
    // Print warning-style message to console.
    void PrintWarning(const char* const Msg_);

    //////////////////////////////////
    // Print error message to console.
    void PrintError(const char* const Msg_);

    ////////////////////////////////////////
    // Print message in developer mode only.
    void PrintDeveloper(const char* const Msg_);

    ///////////////////////////////////////
    // Print message to administrative log.
    void PrintAdministrativeLog(const char* const Msg_);

    /////////////////////////////////
    // Fill buffer with random bytes.
    void FillWithRandomBytes(byte* Buffer_, const int Size_);

    ///////////////////////////
    // Returns real world time.
    time_t GetRealTime();

    ////////////////////////////////
    // Add player ban by IP address.
    void AddBanByIP(netadr_t* Remote_, const char* const Message_, int Expire_);

    ///////////////////////////////////
    // Remove player ban by IP address.
    void RemoveBanByIP(netadr_t* Remote_);

    //////////////////////////////////////////////////
    // Get player ban time limit and save into buffer.
    void GetBanTimeLimit(int MinutesLeft_, char* const Buffer_, const int Size_);

    ///////////////////////////////////////////////
    // Get player ban message and save into buffer.
    void GetBanMessage(int MinutesLeft_, char* const Buffer_, const int Size_, const char* const Reason_);

    /////////////////////////////////////
    // Convert numeric SteamID to string.
    void SteamIDToString(uint64_t SteamID_, char* const Buffer_, const int Size_);

    /////////////////////////////////////
    // Convert numeric SteamID to string.
    void SteamIDToString64(uint64_t SteamID_, char* const Buffer_, const int Size_);

    ////////////////////////////////////////////
    // Convert string representation to SteamID.
    uint64_t StringToSteamID(const char* const String_) const;

    ///////////////////////////////////////////////
    // Return true if passed SteamID is individual.
    bool IsSteamIDIndividual(uint64_t SteamID_) const;

    /////////////////////////
    // Return true if WHAAAT? TODO
    bool IsSteamIDIndividualSteamOnly(uint64_t SteamID_) const;

    ////////////////
    // WHAAAAAAAAAT? TODO
    void AddCommandForPlayerToWhitelist(const int ClientNum_, const char* const Command_) const;

    ///////
    // TODO
    bool CanPlayerUseCommand(const int ClientNum_, const char* const Command_) const;

private:
    ////////////////////////////////////////////////////////////////
    // Returns true if plugin with name LibName_ has known checksum.
    bool isLegacyPlugin(const std::string& LibPath_) const;

    /////////////////////////////////////////////////////
    // Returns major and minor version of plugin handler.
    void getVersion(int& Major_, int& Minor_) const;

    ////////////////////////////
    // Returns plugin file path.
    std::string getPluginFilePath(const char* LibName_) const;

    bool m_Initialized;
    std::map<const char*, CPlugin> m_Plugins;
    CPlugin* m_CurrentPlugin;
};

CPluginHandler* PluginHandler();
