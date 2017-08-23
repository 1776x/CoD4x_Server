#pragma once
//////////////////////////////////////////////////////////////////////
// This file contains types used in cmd.c/.h. Can be used anywhere. //
//////////////////////////////////////////////////////////////////////

// Paramters for command buffer stuffing
typedef enum {
    EXEC_NOW,    // don't return until completed, a VM should NEVER use this,
                 // because some commands might cause the VM to be unloaded...
    EXEC_INSERT, // insert at current position, but don't run yet
    EXEC_APPEND  // add to end of the command buffer (normal case)
} cbufExec_t;

typedef void (*xcommand_t)(void);
typedef void (*completionFunc_t)(char *args, int argNum);
