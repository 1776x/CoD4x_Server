#pragma once
#include "g_hud_types.h"
#include "q_shared_types.h"
#include "q_math_types.h"

//defines Cvarflags
#define CVAR_ARCHIVE 1 // set to cause it to be saved to vars.rc
// used for system variables, not for player
// specific configurations
#define CVAR_USERINFO 2   // sent to server on connect or change
#define CVAR_SERVERINFO 4 // sent in response to front end requests
#define CVAR_SYSTEMINFO 8 // these cvars will be duplicated on all clients
#define CVAR_INIT 16      // don't allow change from console at all,
// but can be set from the command line
#define CVAR_LATCH 32 // will only change when C code next does
// a Cvar_Get(), so it can't be changed
// without proper initialization.  modified
// will be set, even though the value hasn't
// changed yet
#define CVAR_ROM 64             // display only, cannot be set by user at all
#define CVAR_CHEAT 128          // can not be changed if cheats are disabled
#define CVAR_TEMP 256           // can be set even when cheats are disabled, but is not archived
#define CVAR_NORESTART 1024     // do not clear when a cvar_restart is issued
#define CVAR_USER_CREATED 16384 // created by a set command

// TODO: replace 8192 integer to this symbol in cvar.c
#define CVAR_STRING_SIZE 8192

typedef enum cvarType_t
{
    CVAR_BOOL,
    CVAR_FLOAT,
    CVAR_VEC2,
    CVAR_VEC3,
    CVAR_VEC4,
    CVAR_INT,
    CVAR_ENUM,
    CVAR_STRING,
    CVAR_COLOR
} cvarType_t;

typedef union value_t
{
    float floatval;
    float value;
    int integer;
    char *string;
    byte boolean;
    vec3_t vec3;
    vec4_t vec4;
} value_t;

typedef struct cvar_t
{
    char *name;
    char *description;
    short int flags;
    byte type;
    byte modified;
    union {
        float floatval;
        float value;
        int integer;
        char *string;
        byte boolean;
        vec2_t vec2;
        vec3_t vec3;
        vec4_t vec4;
        ucolor_t color;
    };
    union {
        float latchedFloatval;
        int latchedInteger;
        char *latchedString;
        byte latchedBoolean;
        vec2_t latchedVec2;
        vec3_t latchedVec3;
        vec4_t latchedVec4;
        ucolor_t latchedColor;
    };
    union {
        float resetFloatval;
        int resetInteger;
        char *resetString;
        byte resetBoolean;
        vec2_t resetVec2;
        vec3_t resetVec3;
        vec4_t resetVec4;
        ucolor_t resetColor;
    };
    union {
        int imin;
        float fmin;
    };
    union {
        int imax;
        float fmax;
        const char **enumStr;
    };
    struct cvar_t *next;
    struct cvar_t *hashNext;
} cvar_t;
