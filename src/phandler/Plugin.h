#pragma once
#include <string>
#include <list>
#include <map>
#include "../cmd_types.h"
#include "PluginEvents.h"

class CPlugin
{
public:
    CPlugin();
    ~CPlugin();

    // No copy class.
    CPlugin(const CPlugin&) = delete;
    void operator=(const CPlugin&) = delete;

    // ... but can be moved.
    CPlugin(CPlugin&& From_);

    ////////////////////////////////////////////////
    // Loads plugin from file specified by LibPath_.
    void LoadFromFile(const std::string& LibPath_);

    /////////////////////////////////////////
    // Unloads and frees all the plugin data.
    void Unload();

    //////////////////////
    // Prints plugin info.
    void PrintPluginInfo();

    //////////////////////////////////////////
    // Returns true if current plugin initialized.
    bool IsInitialized() const { return m_Initialized; }
    
    /////////////////////////////////////
    // Sets current plugin enabled state.
    void SetInitialized(bool State_) { m_Initialized = State_; }

    ///////////////////////////////////////////
    // Returns total plugin memory allocations.
    int GetMemAllocs() const { return m_MemAllocs; }

    //////////////////////////////////////////
    // Return total allocated memory in bytes.
    int GetMemAllocsSize() const { return m_AllocatedBytesCount; }

    /////////////////////
    // Fire plugin event.
    template <class...PTypes>
    bool Event(EPluginEvent Event_, PTypes...Params)
    {
        int idx = static_cast<int>(Event_);
        if (!m_Events[idx])
            return false;

        (reinterpret_cast<void(__cdecl *)(PTypes...)>(m_Events[idx]))(Params...);
        return true;
    }

    ////////////////////////
    // Allocates RAM.
    void* Malloc(size_t Size_);

    ///////////////////////////////
    // Frees RAM allocated earlier.
    void Free(const void* Ptr_);

    ///////////////////////
    // Add console command.
    void AddConsoleCommand(const char* const Name_, xcommand_t fpCallback_, int Power_ /*= 0*/);

    //////////////////////////
    // Remove console command.
    void RemoveConsoleCommand(const char* const Name_);

private:
    //////////////////////////////////
    // Frees all the allocated memory.
    void freeAllocatedMemory();

    ///////////////////////////////////////
    // Removes all custom console commands.
    void removeAllCustomConsoleCommands();

    void (*m_Events[PLUGINS_EVENTS_COUNT]);
    void* m_LibHandle;

    ////////////////////////////////////////////////////////////////////
    // If set to true, plugin successfully loaded and initialized.
    // Must not be set to "true" inside this class.
    // When unloading, if set to "true" - must fire "OnTerminate" first.
    bool m_Initialized;

    ////////////////////////////////
    // Plugin RAM memory management.
    int m_MemAllocs;
    int m_AllocatedBytesCount;
    std::list<void*> m_MemStorage;

    ///////////////////////////
    // Custom console commands.
    std::list<std::string> m_CustomCmds;
};
