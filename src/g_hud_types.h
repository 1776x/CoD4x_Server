#pragma once
#include "q_shared_types.h"
#define HUDELEM_ADDR 0x8335620
#define MAX_HUDELEMS 1024

typedef enum fonttype_t
{
    HUDFONT_DEFAULT,
    HUDFONT_BIGFIXED,
    HUDFONT_SMALLFIXED,
    HUDFONT_OBJECTIVE
} fonttype_t;

typedef enum hudalign_t
{
    HUDALIGN_TOP = 0,
    HUDALIGN_LEFT = 0,
    HUDALIGN_MIDDLE = 1,
    HUDALIGN_BOTTOM = 2,
    HUDALIGN_CENTER = 4,
    HUDALIGN_RIGHT = 8
} hudalign_t;

typedef enum hudscrnalign_t
{
    HUDSCRNALIGN_TOP = 0,
    HUDSCRNALIGN_MIDDLE = 1,
    HUDSCRNALIGN_BOTTOM = 2,
    HUDSCRNALIGN_LEFT = 9,
    HUDSCRNALIGN_CENTER = 17,
    HUDSCRNALIGN_RIGHT = 25
} hudscrnalign_t;

typedef enum huddisplayoptions_t
{
    HUDDISPLAY_FOREGROUND = 1,
    HUDDISPLAY_HIDEINMENU = 4
} huddisplayoptions_t;

typedef union ucolor_t
{
    int i;
    byte rgba[4];
} ucolor_t;

typedef struct game_hudelem_t
{
    int type;
    float x;
    float y;
    int var_03;
    int targetEnt;
    float fontScale;
    fonttype_t fontType;
    hudalign_t align;
    hudscrnalign_t screenAlign;
    ucolor_t color;
    ucolor_t fadeColor;
    int fadeStartTime;
    int fadeTime;
    int var_13;
    int shaderWidth;
    int shaderHeight;
    int materialIndex;
    int waypointMaterialIndex;
    int shaderOldWidth;
    int shaderOldHeight;
    int scaleStartTime;
    int scaleTime;
    float moveX;
    float moveY;
    int moveAlign;
    int moveScreenAlign;
    int moveStartTime;
    int movingTime;
    int timeValue;
    int duration;
    float value;
    int hudTextConfigStringIndex;
    float sort;
    ucolor_t glowColor;
    int pulseStartTime;
    int pulseSpeed;
    int pulseDecayStart;
    int pulseDecayDuration;
    int var_38;
    huddisplayoptions_t displayOption;
    int entityNum;
    int teamNum;
    int archived;
} game_hudelem_t; //Size: 0xac
