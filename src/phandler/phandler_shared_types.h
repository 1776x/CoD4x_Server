#pragma once

///////////////////////////////////////////////////////////////////
// This file contains types for both plugins and plugin handler. //
///////////////////////////////////////////////////////////////////

#include "../version.h"

typedef enum EPluginError_t
{                             // To be used as the code argument for Plugin_Error()
    P_ERROR_WARNING,          // Save the error string to serverlog - for minor errors
    P_ERROR_DISABLE,          // Save the error string to serverlog and disable the plugin - for serious errors
    P_ERROR_TERMINATE         // Save the error string to serverlog and close the server - for critical errors
} EPluginError_t;

#define PLUGIN_HANDLER_VERSION_MAJOR 3
#define PLUGIN_HANDLER_VERSION_MINOR 200

typedef struct SPluginInfo_t
{                               // To be used in OnInfoRequest
    version_t handlerVersion;   // Requested plugin handler version - mandatory field
    version_t pluginVersion;    // Version of your plugin - optional
    char fullName[64];          // Full plugin name, short name is the filename without extension - optional
    char shortDescription[128]; // Describe in a few words what this plugin does - optional
    char longDescription[1024]; // Full description - optional
} SPluginInfo_t;