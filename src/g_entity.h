#if !defined _G_ENTITY_H_
#define _G_ENTITY_H_

#define g_entities ((gentity_t*)(0x841ffe0))

short G_GetMeansOfDeathString(int MODIdx_);
short G_GetHitLocationString(hitLocation_t HitLoc_);
gentity_t* G_Spawn();
void G_SpawnHelicopter( gentity_t* vehent, gentity_t* ownerent, const char* type, const char* model );
qboolean G_CallSpawnEntity( gentity_t* ent );

#endif // _G_ENTITY_H_