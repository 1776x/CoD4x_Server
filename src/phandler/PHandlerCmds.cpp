#include "PHandlerCmds.h"
#include "PluginHandler.h"

// Return from console command callback if args count not equal (num).
#define ASSERT_ARGS_COUNT(num) \
    do { \
        if (Cmd_Argc() != (num)) \
        { \
            Com_Printf("Usage: %s <plugin file name without extension>\n", Cmd_Argv(0)); \
            return; \
        } \
    } while(0)

void OnCmd_LoadPlugin(void)
{
    ASSERT_ARGS_COUNT(2);

    PluginHandler()->LoadPlugin(Cmd_Argv(1));
}

void OnCmd_UnloadPlugin(void)
{
    ASSERT_ARGS_COUNT(2);

    PluginHandler()->UnloadPlugin(Cmd_Argv(1));
}

void OnCmd_PluginInfo(void)
{
    ASSERT_ARGS_COUNT(2);

    PluginHandler()->PrintPluginInfo(Cmd_Argv(1));
}

void OnCmd_PluginList(void)
{
    PluginHandler()->PrintPluginsSummary();
}

// No need to keep this preprocessor symbols.
#undef ASSERT_ARGS_COUNT
