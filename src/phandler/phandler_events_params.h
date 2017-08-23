#pragma once
////////////////////////////////////////////////////////////////////////////////
// This file contains types definitions for plugin handler events parameters. //
////////////////////////////////////////////////////////////////////////////////

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
