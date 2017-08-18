/*
===========================================================================
    Copyright (C) 2010-2013  Ninja and TheKelm

    This file is part of CoD4X18-Server source code.

    CoD4X18-Server source code is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    CoD4X18-Server source code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
===========================================================================
*/


#ifndef __G_HUD_H__
#define __G_HUD_H__

#include "q_shared.h"
#include "gentity.h"
#include "g_hud_types.h"

extern game_hudelem_t* g_hudelems;

qboolean OnSameTeam( gentity_t *ent1, gentity_t *ent2 );
qboolean Cmd_FollowClient_f(gentity_t *ent, int clientnum);
game_hudelem_t* G_GetNewHudElem(unsigned int clnum);
void G_HudSetText(game_hudelem_t*, const char*);
void G_HudSetPosition(game_hudelem_t*, float x, float y, hudscrnalign_t, hudscrnalign_t, hudalign_t alignx, hudalign_t aligny);
void G_HudSetColor(game_hudelem_t*, ucolor_t, ucolor_t);
void G_HudSetMovingOverTime(game_hudelem_t*, int, float newx, float newy);
void G_HudSetFont(game_hudelem_t*, float fontscale, fonttype_t ft);
void G_HudSetFadingOverTime(game_hudelem_t* element ,int time, ucolor_t newcolor);
void G_HudDestroy(game_hudelem_t* element);


#endif


