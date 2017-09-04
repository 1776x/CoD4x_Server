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
