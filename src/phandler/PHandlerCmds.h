#pragma once

// Plugin handler server console commands.
// All functions must be __cdecl, so ...(void) required.

void OnCmd_LoadPlugin(void);
void OnCmd_UnloadPlugin(void);
void OnCmd_PluginList(void);
void OnCmd_PluginInfo(void);
