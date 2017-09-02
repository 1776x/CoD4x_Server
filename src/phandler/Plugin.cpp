#include "Plugin.h"
#include "phandler_shared_types.h"
#include "../qcommon_io.h"
#include "../sys_main.h"
#include "../cmd.h"
#include <algorithm>

using namespace std;

CPlugin::CPlugin() :
    m_LibHandle(nullptr),
    m_Initialized(false),
    m_MemAllocs(0),
    m_AllocatedBytesCount(0)
{

}

CPlugin::~CPlugin()
{
    Unload();
}

void CPlugin::LoadFromFile(const std::string &LibPath_)
{
    // We can't rely on filename, only it's hash.
    // That's why CPlugin not holds plugin name.
    // Plugin handler does that.
    Com_DPrintf("Loading plugin from file '%s'...", LibPath_.c_str());
    m_LibHandle = Sys_LoadLibrary(LibPath_.c_str());
    if (!m_LibHandle)
    {
        Com_PrintError("Failed to load the plugin\n");
        return;
    }
    Com_DPrintf("done\n");


    Com_DPrintf("Loading events callbacks...");
    for (int ev = PLUGINS_EVENTS_START; ev < PLUGINS_EVENTS_COUNT; ++ev)
        m_Events[ev] = Sys_GetProcedure(GetEventName((EPluginEvent)ev));
    Com_DPrintf("done\n");
}

void CPlugin::Unload()
{
    /*
    if (pluginFunctions.plugins[id].exports != 0)
    { // Library-plugins cannot be unloaded, see plugins/readme.txt
        Com_PrintError("PHandler_Unload: Cannot unload a library plugin!\n");
        return;
    }
    */

    /* TODO: yes, we will be able ;D
    if (pluginFunctions.plugins[id].scriptfunctions != 0 || pluginFunctions.plugins[id].scriptmethods != 0)
    {
        // Script-library plugins cannot be unloaded, see plugins/readme.txt
        Com_PrintError("PHandler_Unload: Cannot unload a script-library plugin!\n");
        return;
    }
    */
    // Let plugin free its stuff.
    if (m_Initialized)
    {
        Event(PLUGINS_ONTERMINATE);
        m_Initialized = false;
    }
    freeAllocatedMemory();
    removeAllCustomConsoleCommands();
    Event(PLUGINS_ONUNLOAD);

    /*
    // Remove all server commands of the plugin
    for (i = 0; i < pluginFunctions.plugins[id].cmds; i++)
    {
        if (pluginFunctions.plugins[id].cmd[i].xcommand != NULL)
        {
            Com_DPrintf("Removing command \"%s\"...\n", pluginFunctions.plugins[id].cmd[i].name);
            Cmd_RemoveCommand(pluginFunctions.plugins[id].cmd[i].name);
        }
    }
    */
    // at end
    Sys_CloseLibrary(m_LibHandle);
    m_LibHandle = nullptr; // Prevent unloading from destructor.
}

void CPlugin::PrintPluginInfo() // const impossible because of "Event" call
{
    // We know, plugin has required events.
    SPluginInfo_t info;
    Event(PLUGINS_ONINFOREQUEST, &info);
    int vMajor = info.pluginVersion.major;
    int vMinor = info.pluginVersion.minor;
    if (vMinor > 100)
        while (vMinor >= 1000)
            vMinor /= 10;

    Com_Printf("^2Plugin version:^7\n%d.%d\n\n", vMajor, vMinor);
    Com_Printf("^2Full plugin name:^7\n%s\n\n", info.fullName);
    Com_Printf("^2Short plugin description:^7\n%s\n\n", info.shortDescription);
    Com_Printf("^2Full plugin description:^7\n%s\n\n", info.longDescription);
    Com_Printf("^2Commands:^7 (total %d)\n\n", /*pluginFunctions.plugins[id].cmds*/ 0); // TODO
    /*
    for (i = 0; i < pluginFunctions.plugins[id].cmds; ++i)
        Com_Printf(" -%s\n", pluginFunctions.plugins[id].cmd[i].name);
    */
    Com_Printf("^2Script Functions:^7 (total %d)\n\n", /*pluginFunctions.plugins[id].scriptfunctions*/0);
    /*
    for (i = 0; i < pluginFunctions.plugins[id].scriptfunctions; ++i)
    {
        if (!pluginScriptCallStubs.s[id * MAX_SCRIPTFUNCTIONS + i].isMethod)
        {
            Com_Printf(" -%s\n", pluginScriptCallStubs.s[id * MAX_SCRIPTFUNCTIONS + i].name);
        }
    }
    */
    Com_Printf("^2Script Methods:^7 (total %d)\n\n", /*pluginFunctions.plugins[id].scriptmethods*/0); // TODO
    /*
    for (i = 0; i < pluginFunctions.plugins[id].scriptmethods; ++i)
    {
        if (pluginScriptCallStubs.s[id * MAX_SCRIPTFUNCTIONS + i].isMethod)
        {
            Com_Printf(" -%s\n", pluginScriptCallStubs.s[id * MAX_SCRIPTFUNCTIONS + i].name);
        }
    }
    */
}

void* CPlugin::Malloc(size_t Size_)
{
    if (!Size_) // Not an error, but worth mention.
    {
        Com_DPrintf("Attempt to allocate 0 bytes for plugin\n");
        return nullptr;
    }

    Com_DPrintf("Allocating %dB of memory for plugin...", Size_);
    void* mem = reinterpret_cast<void*>(malloc(Size_));
    if (!mem)
    {
        Com_DPrintf("failed: not enough memory\n");
        return nullptr;
    }
    m_MemStorage.push_back(mem);
    ++m_MemAllocs;
    m_AllocatedBytesCount += Size_;
    Com_DPrintf("done\n");
    return mem;
}

void CPlugin::Free(const void* Ptr_)
{
    if (!Ptr_)
    {
        Com_DPrintf("Attempt to free nullptr for plugin\n");
        return;
    }

    Com_DPrintf("Freeing plugin memory...");
    for (auto pMem : m_MemStorage) // pMem is void ptr so may use auto instead of auto&.
        if (pMem == Ptr_)
        {
            m_MemStorage.remove(pMem);
            free(pMem);
            Com_DPrintf("done\n");
            return;
        }
    Com_DPrintf("failed: unknown pointer");
}

void CPlugin::AddConsoleCommand(const char* const Name_, xcommand_t fpCallback_, int Power_ /*= 0*/)
{
    Com_DPrintf("Adding custom console command '%s' for plugin...", Name_);
    Cmd_AddPCommand(Name_, fpCallback_, Power_);
    m_CustomCmds.push_back(string(Name_));
    Com_DPrintf("done\n");
}

void CPlugin::RemoveConsoleCommand(const char* const Name_)
{
    Com_DPrintf("Removing custom console command '%s' from plugin...", Name_);
    string sName = Name_;
    // std::find issue.
    /*auto& itCmdName = std::find(m_CustomCmds.begin(), m_CustomCmds.end(), sName);
    if (itCmdName == m_CustomCmds.end())
    {
        Com_PrintError("Custom command '%s' not belongs to this plugin\n", Name_);
        return;
    }
    Cmd_RemoveCommand(Name_);
    m_CustomCmds.remove(itCmdName);
    */
    Com_DPrintf("done\n");
}

void CPlugin::freeAllocatedMemory()
{
    for (auto pMem : m_MemStorage)
        delete[] pMem;

    m_MemStorage.clear();
    m_MemAllocs = 0;
    m_AllocatedBytesCount = 0;
}

void CPlugin::removeAllCustomConsoleCommands()
{
    for (auto& conCmd : m_CustomCmds)
        RemoveConsoleCommand(conCmd.c_str());
    m_CustomCmds.clear();
}
