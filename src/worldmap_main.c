#include "global.h"

#include "bmlib.h"
#include "bmsave.h"
#include "bmudisp.h"
#include "face.h"
#include "fontgrp.h"
#include "hardware.h"
#include "mu.h"
#include "scene.h"
#include "uiutils.h"

#include "worldmap.h"

// TODO: Figure out what this is?

struct UnknownSub80B8BA4
{
    /* 00 */ u8 unk_00;
    /* 01 */ u8 unk_01;
    /* 02 */ u8 unk_02;
    /* 03 */ u8 unk_03;
    /* 04 */ u8 unk_04;
    /* 06 */ u16 unk_06;
    /* 08 */ u16 unk_08;
    /* 0A */ u16 unk_0a;
    /* 0C */ int unk_0c;
};

void sub_80BDEB4(ProcPtr, struct UnknownSub80B8BA4 *);

//! FE8U = 0x080B8A18
void WorldMap_Destruct(struct WorldMapMainProc * proc)
{
    Proc_End(proc->unk_50);
    Proc_End(proc->unk_44);
    Proc_End(proc->unk_48);

    SetSecondaryHBlankHandler(NULL);

    sub_80C1D70();

    SetPrimaryHBlankHandler(NULL);

    EndTalk();
    ClearTalkText();

    ResetUnitSprites();
    SetSpecialColorEffectsParameters(3, 0, 0, 0x10);

    sub_80BF15C();
    sub_80C3E94();

    gGMData.state.bits.state_6 = 0;
    gGMData.state.bits.state_7 = 0;
    gGMData.state.bits.state_0 = 0;

    return;
}

//! FE8U = 0x080B8A7C
void sub_80B8A7C(struct WorldMapMainProc * proc)
{
    int unk;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;

    proc->unk_40 = 0;
    proc->unk_41 = 0;

    proc->unk_29_1 = 1;

    gGMData.unk01 = 0;

    sub_80BE0A4(proc->unk_54, 0, &x1, &y1);
    GetWMCenteredCameraPosition(x1, y1 - 14, &x2, &y2);

    unk = sub_80C0834(gGMData.xCamera, gGMData.yCamera, x2, y2, 2);

    unk = unk >> 2;

    if (unk < 2)
    {
        gGMData.xCamera = x2;
        gGMData.yCamera = y2;
        Proc_Goto(proc, 7);
    }
    else
    {
        if (unk < 16)
        {
            unk = 16;
        }
        else if (unk > 75)
        {
            unk = 75;
        }
        sub_80BF404(-1, -1, x2, y2, unk, 0);
    }

    return;
}

s8 sub_80BF490(void);

//! FE8U = 0x080B8B3C
void sub_80B8B3C(struct WorldMapMainProc * proc)
{
    if (sub_80BF490() == 0)
    {
        proc->unk_41 = 20;
        Proc_Break(proc);
    }

    return;
}

//! FE8U = 0x080B8B60
s8 sub_80B8B60(int location)
{
    int i;

    if (!(gGMData.nodes[location].state & 2))
    {
        for (i = 4; i < 7; i++)
        {
            if (gGMData.units[i].id == 0)
            {
                continue;
            }

            if (gGMData.units[i].location != location)
            {
                continue;
            }

            return 1;
        }
    }

    return 0;
}

//! FE8U = 0x080B8BA4
void sub_80B8BA4(struct WorldMapMainProc * proc)
{
    struct UnknownSub80B8BA4 a;

    if (sub_80BE12C(proc->unk_54, 0) != 0)
    {
        return;
    }

    if (proc->unk_40 < sub_80BD29C() - 1)
    {
#ifdef NONMATCHING
        int var = sub_80BD29C() - proc->unk_40;
#else
        register int var asm("r0") = sub_80BD29C() - proc->unk_40;
#endif
        if (var == 2)
        {
            int location = sub_80BD28C(proc->unk_40 + 1);
            if (gGMData.nodes[location].state & 2 &&
                sub_80BD28C(proc->unk_40 + 1)[gWMNodeData].placementFlag != GMAP_NODE_PLACEMENT_DUNGEON)
            {
                proc->unk_3e = sub_80BD28C(proc->unk_40 + 1);
                Proc_Goto(proc, 14);
            }
        }
        else
        {
            if (sub_80BCA1C(sub_80BD28C(proc->unk_40 + 1)) >= 0)
            {
                Proc_Goto(proc, 17);
                return;
            }
        }

        if (proc->unk_41 < 1)
        {
            int b = sub_80BD28C(proc->unk_40);
            int c = sub_80BD28C(proc->unk_40 + 1);
            MapMU_80BE108(proc->unk_54, 0, 1);

            a.unk_00 = 0;
            a.unk_06 = b;
            a.unk_08 = c;
            a.unk_0c = -1;
            a.unk_01 = proc->unk_29_1;
            a.unk_0a = 0;
            a.unk_02 = 1;
            a.unk_03 = 0xff;
            a.unk_04 = 4;

            sub_80BDEB4(proc->unk_54, &a);
            proc->unk_41 = 8;
            proc->unk_40++;
        }
        else
        {
            if (proc->unk_29_1)
            {
                if (gKeyStatusPtr->heldKeys & A_BUTTON)
                {
                    proc->unk_41 -= 2;
                }
            }
            proc->unk_41--;
        }
    }
    else
    {
        int location;

        proc->unk_29_1 = 0;
        gGMData.units[0].location = sub_80BD28C(proc->unk_40);
        MapMU_80BE108(proc->unk_54, 0, 0);

        location = gGMData.units[0].location;
        if (location[gWMNodeData].placementFlag == GMAP_NODE_PLACEMENT_DUNGEON)
        {
            Proc_Goto(proc, 14);
        }
        else
        {
            if (sub_80B8B60(location) != 0)
            {
                Proc_Goto(proc, 16);
            }
            else
            {
                gGMData.unk01 = 1;
                Proc_Break(proc);
            }
        }
    }
    return;
}

extern struct FaceVramEntry gUnknown_08A3D728[];

//! FE8U: 0x080B8D5C
void SetupGraphicSystemsForWorldMap(void)
{
    SetupBackgrounds(NULL);

    SetDispEnable(0, 0, 0, 0, 0);

    BG_Fill(gBG0TilemapBuffer, 0);
    BG_Fill(gBG1TilemapBuffer, 0);
    BG_Fill(gBG2TilemapBuffer, 0);
    BG_Fill(gBG3TilemapBuffer, 0);

    gLCDControlBuffer.bg0cnt.priority = 0;
    gLCDControlBuffer.bg1cnt.priority = 1;
    gLCDControlBuffer.bg2cnt.priority = 3;
    gLCDControlBuffer.bg3cnt.priority = 3;

    GetSaveWriteAddr(SAVE_ID_XMAP);

    LoadLegacyUiFrameGraphics();
    ResetText();
    ResetFaces();
    SetupFaceGfxData(gUnknown_08A3D728);
    ResetUnitSprites();
    MU_Init();
    SetupMapSpritesPalettes();

    gBmSt.camera.x = 0;
    gBmSt.camera.y = 0;

    return;
}

//! FE8U = 0x080B8E14
void sub_80B8E14(void)
{
    ApplyPalettes(gUnknown_08A97A40, 0x13, 2);
    Decompress(gUnknown_08A96308, (void *)0x06011000);
    Decompress(gUnknown_08A97410, gGenericBuffer);
    Copy2dChr(gGenericBuffer, (void *)0x06010280, 0xc, 4);

    return;
}

//! FE8U = 0x080B8E60
void sub_80B8E60(struct WorldMapMainProc * proc)
{
    proc->unk_3a = 0;

    SetDefaultColorEffects();

    BG_Fill(gBG0TilemapBuffer, 0);
    BG_Fill(gBG1TilemapBuffer, 0);
    BG_Fill(gBG2TilemapBuffer, 0);
    BG_Fill(gBG3TilemapBuffer, 0);

    BG_EnableSyncByMask(BG0_SYNC_BIT | BG1_SYNC_BIT | BG2_SYNC_BIT | BG3_SYNC_BIT);

    ApplyPalettes(gPal_MiscUiGraphics, 0x10, 2);
    ApplyPalette(gPal_MiscUiGraphics, 0x1B);
    Decompress(gUnknown_08AA11D0, gGenericBuffer);
    Copy2dChr(gGenericBuffer, (void *)0x06015300, 8, 2);

    sub_80B8E14();

    ApplyPalette(gUnknown_08A97FA4, 0xE);
    Decompress(gUnknown_08A97ED8, (void *)0x06005000);

    LoadUiFrameGraphics();
    ResetText();
    ResetTextFont();

    SetWinEnable(0, 0, 0);
    SetWOutLayers(1, 1, 1, 1, 1);

    gLCDControlBuffer.wincnt.win0_enableBlend = 1;
    gLCDControlBuffer.wincnt.win1_enableBlend = 1;
    gLCDControlBuffer.wincnt.wout_enableBlend = 1;

    sub_80AE168(0, 0, 0);

    SetSpecialColorEffectsParameters(0, 0, 0, 0);
    SetBlendTargetA(0, 0, 0, 0, 0);
    SetBlendTargetB(0, 0, 0, 1, 1);

    sub_80C1D00();

    return;
}

//! FE8U = 0x080B8FA4
void DeployEveryUnit(struct WorldMapMainProc * unused)
{
    int i;

    for (i = FACTION_BLUE + 1; i < FACTION_GREEN; i++)
    {
        struct Unit * unit = GetUnit(i);

        if (!UNIT_IS_VALID(unit))
        {
            continue;
        }

        unit->state &= ~(US_NOT_DEPLOYED);
    }

    return;
}

//! FE8U = 0x080B8FD0
void nullsub_22(void)
{
    return;
}

//! FE8U = 0x080B8FD4
void sub_80B8FD4(void)
{
    gGMData.state.bits.state_0 = 1;
    gGMData.state.bits.state_3 = 0;
    return;
}

//! FE8U = 0x080B8FEC
void sub_80B8FEC(struct WorldMapMainProc * proc)
{
    int id = sub_80BD014(&gGMData);

    if (id >= 0)
    {
        proc->unk_48->nodeId = id;
        proc->unk_48->unk_32_1 = 1;
    }
    else
    {
        proc->unk_48->unk_32_1 = 0;
    }

    return;
}

//! FE8U = 0x080B9028
void sub_80B9028(struct WorldMapMainProc * proc)
{
    s16 unk[2];
    int i;
    s16 * a;
    s16 * b;

    for (i = 0; i < 7; i++)
    {
        if (gGMData.units[i].id == 0)
        {
            continue;
        }

        if (gGMData.units[i].state & 2)
        {
            MapMU_SetUnitClass(proc->unk_54, i, gGMData.units[i].id, -1, gGMData.units[i].location);
        }
        else
        {
            MapMU_SetUnitChar(proc->unk_54, i, gGMData.units[i].id, -1, gGMData.units[i].location);
        }

        // TODO: This matches but using a Vec2 does not
        a = &unk[0];
        *a = gGMData.units[i].location[gWMNodeData].x;
        b = &unk[1];
        *b = gGMData.units[i].location[gWMNodeData].y;

        sub_80BE35C(proc->unk_54, i, *a, *b);

        sub_80BDDC4(proc->unk_54, i);
    }

    return;
}

//! FE8U = 0x080B90CC
void sub_80B90CC(struct WorldMapMainProc * proc)
{
    int i;

    if (!gGMData.state.bits.state_1)
    {

        for (i = 4; i < 7; i++)
        {
            MapMU_RemoveUnit(proc->unk_54, i);
            gGMData.units[i].id = 0;
            gGMData.units[i].state &= ~2;
            gGMData.units[i].state &= ~1;
        }
    }

    sub_80B9028(proc);

    return;
}

//! FE8U = 0x080B9114
void sub_80B9114(struct WorldMapMainProc * proc)
{
    int i;

    for (i = 0; i <= 0x1c; i++)
    {
        if (gGMData.nodes[i].state & 2)
        {
            proc->unk_48->nodeId = i;
            proc->unk_48->unk_32_1 = 1;

            break;
        }
    }

    return;
}

//! FE8U = 0x080B9154
void sub_80B9154(struct WorldMapMainProc * proc)
{
    SetupGraphicSystemsForWorldMap();

    sub_80B8E60(proc);
    DeployEveryUnit(proc);

    proc->unk_44 = NewMapScreen(PROC_TREE_5);
    proc->unk_48 = sub_80BB9A4(PROC_TREE_5, 0, 3, 10, proc->unk_44);
    proc->unk_4c = NewGmapUnitContainer(proc->unk_44, 0x280, 0xc);
    proc->unk_50 = NewGmapCursor(PROC_TREE_5, 0x12c0, 4, proc->unk_44);
    proc->unk_54 = NewMapMU(proc);

    sub_80BCA0C(&gGMData);
    sub_80C368C(proc);
    sub_80B8FEC(proc);
    sub_80B90CC(proc);

    if (gGMData.state.bits.state_1)
    {
        sub_80B9114(proc);
    }

    proc->unk_44->unk_4c->flags |= 3;

    if (gPlaySt.chapterStateBits & PLAY_FLAG_POSTGAME)
    {
        sub_80BCFB4();
        proc->unk_48->unk_32_1 = 0;
    }

    proc->unk_2a = 0;

    return;
}

//! FE8U = 0x080B9218
void sub_80B9218(ProcPtr proc)
{
    s16 a, b, c, d;
    s16 cough;

    *&a = gGMData.unk08 >> 8;
    *&b = gGMData.unk0C >> 8;
    *&c = gGMData.xCamera;
    *&d = gGMData.yCamera;

    cough = a - c;
    if (cough < 0x20)
    {
        if (a >= 0x20)
            c = a - 0x20;
        else
            c = 0;
    }
    else if (cough > 0xd0)
    {
        if (a < 0x1c0)
            c = a - 0xd0;
        else
            c = 0xf0;
    }

    cough = b - d;
    if (cough < 0x20)
    {
        if (b >= 0x20)
            d = b - 0x20;
        else
            d = 0;
    }
    else if (cough > 0x80)
    {
        if (b < 0x120)
            d = b - 0x80;
        else
            d = 0xa0;
    }

    gGMData.xCamera = c;
    gGMData.yCamera = d;

    return;
}

#if NONMATCHING

/* https://decomp.me/scratch/RHZdA */

//! FE8U = 0x080B92D0
s8 sub_80B92D0(struct WorldMapMainProc * param_1, int param_2)
{

    int iVar4;
    int uVar5;

    if (gGMData.units[0].location == param_2)
    {
        if (((gGMData.nodes[param_2].state & 2) == 0) && (param_2[gWMNodeData].placementFlag != 3))
        {

            if (sub_80BCA1C(param_2) >= 0)
            {
                Proc_Goto(param_1, 16);
                return 1;
            }
            else
            {
                iVar4 = sub_80BD014(&gGMData);

                if ((((gPlaySt.chapterStateBits & 4) == 0) && (!gPlaySt.unk42_6)) && (iVar4 == 2))
                {
                    return 0;
                }

                Proc_Goto(param_1, 18);
                return 1;
            }
        }
        else
        {
        _74:
            param_1->unk_3e = param_2;
            Proc_Goto(param_1, 14);
        }
        return 1;
    }

    if (sub_80BCCFC(gGMData.units[0].location, param_2, 0) != 0)
    {
        if ((sub_80BD29C() == 2))
        {
            if ((gGMData.nodes[param_2].state & 2) != 0)
            {
                goto _74;
            }
            Proc_Goto(param_1, 6);
        }
        else
        {
            Proc_Goto(param_1, 6);
        }
    }
    else
    {
        uVar5 = gGMData.units[0].location;
        if (sub_80BCCFC(uVar5, param_2, 1) != 0)
        {
            if (sub_80BD29C() == 2)
            {
                if (param_2[gWMNodeData].placementFlag != 3)
                {
                    if ((gGMData.nodes[param_2].state & 2) != 0)
                    {
                        goto _74;
                    }
                }
                Proc_Goto(param_1, 6);
            }
            else
            {
                Proc_Goto(param_1, 6);
            }
            return 1;
        }
    }

    return 0;
}

#else

NAKEDFUNC
s8 sub_80B92D0(struct WorldMapMainProc * param_1, int param_2)
{
    asm("\n\
        .syntax unified\n\
        push {r4, r5, r6, r7, lr}\n\
        adds r5, r0, #0\n\
        adds r4, r1, #0\n\
        ldr r7, _080B930C  @ gGMData\n\
        ldrb r0, [r7, #0x11]\n\
        cmp r0, r4\n\
        bne _080B9356\n\
        lsls r0, r4, #2\n\
        adds r0, r0, r7\n\
        adds r0, #0x30\n\
        ldrb r1, [r0]\n\
        movs r0, #2\n\
        ands r0, r1\n\
        cmp r0, #0\n\
        bne _080B9344\n\
        lsls r0, r4, #5\n\
        ldr r1, _080B9310  @ gWMNodeData\n\
        adds r0, r0, r1\n\
        ldrb r0, [r0]\n\
        cmp r0, #3\n\
        beq _080B9344\n\
        adds r0, r4, #0\n\
        bl sub_80BCA1C\n\
        cmp r0, #0\n\
        blt _080B9314\n\
        adds r0, r5, #0\n\
        movs r1, #0x10\n\
        b _080B934E\n\
        .align 2, 0\n\
    _080B930C: .4byte gGMData\n\
    _080B9310: .4byte gWMNodeData\n\
    _080B9314:\n\
        adds r0, r7, #0\n\
        bl sub_80BD014\n\
        adds r3, r0, #0\n\
        ldr r2, _080B9340  @ gPlaySt\n\
        ldrb r1, [r2, #0x14]\n\
        movs r0, #4\n\
        ands r0, r1\n\
        cmp r0, #0\n\
        bne _080B9338\n\
        adds r0, r2, #0\n\
        adds r0, #0x42\n\
        ldrb r0, [r0]\n\
        lsls r0, r0, #0x1a\n\
        cmp r0, #0\n\
        blt _080B9338\n\
        cmp r3, #2\n\
        beq _080B93D6\n\
    _080B9338:\n\
        adds r0, r5, #0\n\
        movs r1, #0x12\n\
        b _080B934E\n\
        .align 2, 0\n\
    _080B9340: .4byte gPlaySt\n\
    _080B9344:\n\
        adds r0, r5, #0\n\
        adds r0, #0x3e\n\
        strb r4, [r0]\n\
        adds r0, r5, #0\n\
        movs r1, #0xe\n\
    _080B934E:\n\
        bl Proc_Goto\n\
    _080B9352:\n\
        movs r0, #1\n\
        b _080B93D8\n\
    _080B9356:\n\
        movs r0, #0x11\n\
        ldrsb r0, [r7, r0]\n\
        lsls r1, r4, #0x18\n\
        asrs r6, r1, #0x18\n\
        adds r1, r6, #0\n\
        movs r2, #0\n\
        bl sub_80BCCFC\n\
        lsls r0, r0, #0x18\n\
        cmp r0, #0\n\
        beq _080B938A\n\
        bl sub_80BD29C\n\
        adds r1, r0, #0\n\
        cmp r1, #2\n\
        bne _080B9384\n\
        lsls r0, r4, #2\n\
        adds r0, r0, r7\n\
        adds r0, #0x30\n\
        ldrb r0, [r0]\n\
        ands r1, r0\n\
        cmp r1, #0\n\
        bne _080B9344\n\
    _080B9384:\n\
        adds r0, r5, #0\n\
        movs r1, #6\n\
        b _080B934E\n\
    _080B938A:\n\
        movs r0, #0x11\n\
        ldrsb r0, [r7, r0]\n\
        adds r1, r6, #0\n\
        movs r2, #1\n\
        bl sub_80BCCFC\n\
        lsls r0, r0, #0x18\n\
        cmp r0, #0\n\
        beq _080B93D6\n\
        bl sub_80BD29C\n\
        adds r2, r0, #0\n\
        cmp r2, #2\n\
        bne _080B93CC\n\
        lsls r0, r4, #5\n\
        ldr r1, _080B93C8  @ gWMNodeData\n\
        adds r0, r0, r1\n\
        ldrb r0, [r0]\n\
        cmp r0, #3\n\
        beq _080B93C0\n\
        lsls r0, r4, #2\n\
        adds r0, r0, r7\n\
        adds r0, #0x30\n\
        ldrb r0, [r0]\n\
        ands r2, r0\n\
        cmp r2, #0\n\
        bne _080B9344\n\
    _080B93C0:\n\
        adds r0, r5, #0\n\
        movs r1, #6\n\
        b _080B934E\n\
        .align 2, 0\n\
    _080B93C8: .4byte gWMNodeData\n\
    _080B93CC:\n\
        adds r0, r5, #0\n\
        movs r1, #6\n\
        bl Proc_Goto\n\
        b _080B9352\n\
    _080B93D6:\n\
        movs r0, #0\n\
    _080B93D8:\n\
        pop {r4, r5, r6, r7}\n\
        pop {r1}\n\
        bx r1\n\
        .syntax divided\n\
    ");
}

#endif
