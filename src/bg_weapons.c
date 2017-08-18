#include "bg_weapons.h"

#define bg_weaponDefs ((WeaponDef_t**)0x0828DE40)

WeaponDef_t* __cdecl BG_GetWeaponDef(int Weapon_)
{
  return bg_weaponDefs[Weapon_];
}
