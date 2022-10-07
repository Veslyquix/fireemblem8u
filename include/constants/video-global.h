#pragma once

#include "gba/gba.h"

enum
{
    BGCHR_WINDOW_FRAME = 0,

    BGCHR_TEXT_DEFAULT = 0x80,

    BGCHR_0_TEXT_POPUP = 0x100,
    BGCHR_DEBUGTEXT_DEFAULT = 0x2C0,

    BGCHR_LIMITVIEW = 0x280,

    BGCHR_ICON_BEGIN = 0x280,
    BGCHR_ICON_END   = 0x300,

    BGCHR_STATUSHEAL = 0x280,

    BGCHR_TILESET_A = 0x400,
    BGCHR_TILESET_B = 0x600,

    BGCHR_PHASE_CHANGE_SQUARES = 0x100,
    BGCHR_PHASE_CHANGE_NAME = 0x140,

    BGCHR_CHAPTERINTRO_80 = 0x80,
    BGCHR_CHAPTERINTRO_100 = 0x100,
    BGCHR_CHAPTERINTRO_MOTIF = 0x400,
    BGCHR_CHAPTERINTRO_FOG = 0x500,

    BGCHR_GAMEOVER_TEXT = 0x80,

    BGCHR_BMFX_IMG = 0x100,

    BGCHR_STEALSELECT_FACE = 0x200,

    BGCHR_BATTLEPREVIEW_FRAME = 0x200,

    BGCHR_MANIM_1 = 1,
    BGCHR_MANIM_140 = 0x140,
    BGCHR_MANIM_200 = 0x200,
};

enum
{
    BGPAL_TEXT_DEFAULT    = 0,
    BGPAL_WINDOW_FRAME    = 1,
    BGPAL_TALK            = 2,
    BGPAL_TALK_BUBBLE     = 3,
    BGPAL_ICONS           = 4, // .. 5
    BGPAL_TILESET         = 6, // .. 15

    BGPAL_DEBUGTEXT       = 0,

    BGPAL_EQUIP_INFO_ICON = 3,

    BGPAL_STATUSHEAL = 3,

    BGPAL_BATTLEPREVIEW_ICONALT = 3,

    BGPAL_LIMITVIEW = 4, // .. 5

    BGPAL_PHASE_CHANGE = 5,

    BGPAL_CHAPTERINTRO_0 = 0,
    BGPAL_CHAPTERINTRO_1 = 1,
    BGPAL_CHAPTERINTRO_FOG = 4,
    BGPAL_CHAPTERINTRO_MOTIF = 5,

    BGPAL_GAMEOVER_TEXT = 0,
    BGPAL_GAMEOVER_4 = 4,

    BGPAL_LIGHTRUNE_IMG = 2,
    BGPAL_DANCERING_IMG = 2,
    BGPAL_EVENTWARP_IMG = 5,
    BGPAL_WHILTECIRCLE_FADE = 2,

    BGPAL_STEALSELECT_FACE = 5,

    BGPAL_BATTLEPREVIEW_FRAME = 1, // .. 2

    BGPAL_UI_STATBAR = 6,

    BGPAL_MANIM_1 = 1, // .. 2
    BGPAL_MANIM_4 = 4,
    BGPAL_MANIM_5 = 5,
};

enum
{
    OBJCHR_SYSTEM_OBJECTS = 0x000,

    OBJCHR_CLOUDS = 0x012,
    OBJCHR_SNOWSTORM_PARTICLE = 0x018,
    OBJCHR_SANDSTORM_PARTICLE = 0x01C,

    OBJCHR_MAPSPRITES = 0x80,

    OBJCHR_DEBUGTEXT_DEFAULT = 0x180,

    OBJCHR_MU_180 = 0x180,

    OBJCHR_MANIM_180 = 0x180,
    OBJCHR_MANIM_1C0 = 0x1C0,

    OBJCHR_TRAPFX = 0x240,

    OBJCHR_EMITSTARTS = 0x200,
    OBJCHR_MINEFX = 0x180,

    OBJCHR_TRADEMENU_240 = 0x240,

    OBJCHR_SUBTITLEHELP_TEXT = 0x240,

    OBJCHR_BATTLEPREVIEW_MULTIPLIERS = 0x2E8,

    OBJCHR_MOVEPATH = 0x2F0,

    OBJCHR_FACE_DEFAULT2 = 0x1E0,
    OBJCHR_FACE_DEFAULT1 = 0x268,
    OBJCHR_FACE_DEFAULT0 = 0x2F0,
    OBJCHR_FACE_DEFAULT3 = 0x378,

    OBJCHR_MU_BASE = 0x380,
};

enum
{
    OBJPAL_SYSTEM_OBJECTS = 0,

    OBJPAL_1 = 1,

    OBJPAL_TRAPFX = 2,
    OBJPAL_MINEFX = 0x15,

    OBJPAL_STATUSHEAL_UNITSPRITE = 2,

    OBJPAL_BATTLEPREVIEW_MULTIPLIERS = 2,

    OBJPAL_MOVEPATH = 3,

    OBJPAL_SUBTITLEHELP_TEXT = 4,

    OBJPAL_MU_FADE = 5,

    OBJPAL_FACE_DEFAULT0 = 6,
    OBJPAL_FACE_DEFAULT1 = 7,
    OBJPAL_FACE_DEFAULT2 = 8,
    OBJPAL_FACE_DEFAULT3 = 9,

    OBJPAL_TRADEMENU_8 = 8,

    OBJPAL_MANIM_3 = 3,
    OBJPAL_MANIM_4 = 4,
    OBJPAL_MANIM_SPECIALMU = 8, // .. 9

    OBJPAL_7 = 7,
    OBJPAL_10 = 10,

    OBJPAL_UNITSPRITE_PURPLE = 11,

    OBJPAL_MAPSPRITES = 12,
    OBJPAL_UNITSPRITE_BLUE = OBJPAL_MAPSPRITES + 0,
    OBJPAL_UNITSPRITE_RED = OBJPAL_MAPSPRITES + 1,
    OBJPAL_UNITSPRITE_GREEN = OBJPAL_MAPSPRITES + 2,
    OBJPAL_UNITSPRITE_GRAY = OBJPAL_MAPSPRITES + 3,
};
