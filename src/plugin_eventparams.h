#if !defined _PLUGIN_EVENTPARAMS_H_
#define _PLUGIN_EVENTPARAMS_H_

#include "gentity.h" // gentity_t
#include "g_entity.h" // hitLocation_t

typedef struct ScriptEventParams_OnPlayerKilled_t 
{
    gentity_t *self;
    gentity_t *inflictor;
    gentity_t *attacker;
    int damage;
    unsigned int meansOfDeath;
    int iWeapon;
    float *vDir;
    hitLocation_t hitLoc;
    int psTimeOffset;
    int deathAnimDuration;
} ScriptEventParams_OnPlayerKilled_t;

typedef struct ScriptEventParams_OnPlayerDamage_t 
{
    gentity_t *self;
    gentity_t *inflictor;
    gentity_t *attacker;
    int damage;
    int dflags;
    unsigned int meansOfDeath;
    int iWeapon;
    float *vPoint;
    float *vDir;
    hitLocation_t hitLoc;
    int timeOffset;
} ScriptEventParams_OnPlayerDamage_t;

typedef struct ScriptEventParams_OnPlayerLastStand_t
{
    gentity_t *self;
    gentity_t *inflictor;
    gentity_t *attacker;
    int damage;
    unsigned int meansOfDeath;
    int iWeapon;
    float *vDir;
    hitLocation_t hitLoc;
    int psTimeOffset;
} ScriptEventParams_OnPlayerLastStand_t;

#endif
