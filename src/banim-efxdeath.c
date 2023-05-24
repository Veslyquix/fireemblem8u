#include "global.h"
#include "proc.h"
#include "hardware.h"
#include "event.h"
#include "bmlib.h"
#include "ekrbattle.h"
#include "efxbattle.h"
#include "ekrdragon.h"
#include "ev_triggercheck.h"

CONST_DATA struct ProcCmd ProcScr_efxDeadEvent[] = {
    PROC_NAME("efxDeadEVTENT"),
    PROC_REPEAT(sub_8052DFC),
    PROC_REPEAT(sub_8052E7C),
    PROC_REPEAT(sub_8052EAC),
    PROC_REPEAT(sub_8052F24),
    PROC_REPEAT(sub_8052F84),
    PROC_END
};

void NewEfxDeadEvent(struct Anim *anim1, struct Anim *anim2)
{
    struct ProcEfxDead *proc;
    proc = Proc_Start(ProcScr_efxDeadEvent, PROC_TREE_3);
    proc->anim1 = anim1;
    proc->anim2 = anim2;

    gEkrDeadEventExist = true;
}

void sub_8052DFC(struct ProcEfxDead *proc)
{
    struct Anim *ais_core1 = GetCoreAIStruct(proc->anim1);
    int ret = false;

    if (gUnknown_0201774C == 0 && gUnknown_0201772C == 0) {
        if (gBanimDoneMaybe[GetAISSubjectId(ais_core1)] == true)
            ret = true;
    }

    if (ret != true)
        return;

    proc->timer = 7;

    if (gEkrDistanceType != EKR_DISTANCE_CLOSE && GetAISSubjectId(proc->anim1) != gEkrPos2Maybe) {
        NewEfxFarAttackWithDistance(ais_core1, -1);
        proc->timer = 0;
    }

    Proc_Break(proc);
}

void sub_8052E7C(struct ProcEfxDead *proc)
{
    if (++proc->timer == 8) {
        NewEkrWindowAppear(1, 7);
        NewEkrNamewinAppear(1, 7, 0);
        Proc_Break(proc);
    }
}

void sub_8052EAC(struct ProcEfxDead *proc)
{
    if (DoesEkrWindowAppearExist() == true) {
        EkrGauge_Set2A();
        sub_8051B90();

        CpuFastFill(0, gBG0TilemapBuffer, 0x800);
        BG_SetPosition(BG_0, gEkrBg0QuakeVec.x, gEkrBg0QuakeVec.y);
        BG_SetPosition(BG_1, 0, 0);
        BG_EnableSyncByMask(BG0_SYNC_BIT);

        EkrGauge_Set4C50();
        
        /* Maybe triger death event */
        sub_80835DC(gEkrPids[GetAISSubjectId(proc->anim1)]);
        Proc_Break(proc);
    }
}

void sub_8052F24(struct ProcEfxDead *proc)
{
    if (BattleEventEngineExists() == false) {
        PlaySound8FForArenaMaybe();
        NewEfxDead(proc->anim1, proc->anim2);
        EfxPrepareScreenFx();
        gEkrPairSideVaild[GetAISSubjectId(proc->anim1)] = false;
        BG_EnableSyncByMask(BG0_SYNC_BIT);
        NewEkrWindowAppear(0, 7);
        NewEkrNamewinAppear(0, 7, 0);

        EkrGauge_Clr2A();
        sub_8051BA0();
        EkrGauge_Clr4C50();
        Proc_Break(proc);
    }
}

void sub_8052F84(struct ProcEfxDead *proc)
{
    if (DoesEkrWindowAppearExist() == true) {
        gEkrDeadEventExist = false;
        Proc_Break(proc);
    }
}

CONST_DATA struct ProcCmd ProcScr_efxDead[] = {
    PROC_NAME("efxDead"),
    PROC_REPEAT(sub_8052FEC),
    PROC_REPEAT(sub_8053080),
    PROC_END
};

void NewEfxDead(struct Anim *anim1, struct Anim *anim2)
{
    struct ProcEfxDead *proc;
    gEkrHPBarCount++;
    gUnknown_02017734 = 1;

    proc = Proc_Start(ProcScr_efxDead, PROC_TREE_3);
    proc->anim1 = anim1;
    proc->anim2 = anim2;
    proc->timer = 0;
    proc->unk2E = 0;
    DisableEfxStatusUnits(anim1);
}

void sub_8052FEC(struct ProcEfxDead *proc)
{
    int hp;

    if (GetBanimDragonStatusType() == EKRDRGON_TYPE_DRACO_ZOMBIE && GetAISSubjectId(proc->anim1) == EKR_POS_L) {
        hp = GetEfxHp(gEfxPairHpBufOffset[GetAISSubjectId(proc->anim1)] * 2 + GetAISSubjectId(proc->anim1));
    } else
        hp = 1;

    if (gUnknown_0201774C == false && gUnknown_0201772C == false) {
        if (GetBanimDragonStatusType() == EKRDRGON_TYPE_DEMON_KING)
            SetEkrDragonStatusAttrBit12(proc->anim1);
        else if (hp == 0)
            SetEkrDragonStatusAttrBit13(proc->anim1);
        else
            NewEfxDeadPika(proc->anim1, proc->anim2);

        proc->unk2E = 0x32;
        Proc_Break(proc);
    }
}

void sub_8053080(struct ProcEfxDead *proc)
{
    struct Anim *anim = proc->anim1;
    s16 time = ++proc->timer;

    if (time == 0x1E) {
        if (CheckEkrDragonDeadEffectMaybe(anim) == true)
            return;
        
        if (CheckEkrDragonStatusAttrBit13(proc->anim1) != false) {
            NewEfxDeadDragonAlpha(proc->anim1, proc->anim2);
            EfxPlaySE(0xD6, 0x100);
            M4aPlayWithPostionCtrl(0xD6, anim->xPosition, 1);
            proc->unk2E = 0x64;
            return;
        }

        NewEfxDeadAlpha(proc->anim1, proc->anim2);
        EfxPlaySE(0xD6, 0x100);
        M4aPlayWithPostionCtrl(0xD6, anim->xPosition, 1);
        proc->unk2E = 0x32;
        return;
    }

    if (time == proc->unk2E) {
        gEkrHPBarCount--;
        gUnknown_02017734 = 0;
        Proc_Break(proc);
    }
}

CONST_DATA struct ProcCmd ProcScr_efxDeadPika[] = {
    PROC_NAME("efxDeadPika"),
    PROC_REPEAT(EfxDeadPikaMain),
    PROC_END
};

void NewEfxDeadPika(struct Anim *anim1, struct Anim *anim2)
{
    struct ProcEfxDead *proc;
    proc = Proc_Start(ProcScr_efxDeadPika, PROC_TREE_3);
    
    proc->anim1 = anim1;
    proc->anim2 = anim2;
    proc->timer = 0;
    proc->unk2E = 0;
}

void EfxDeadPikaMain(struct ProcEfxDead *proc)
{
    struct Anim *anim1 = proc->anim1;
    struct Anim *anim2 = proc->anim2;

    if (++proc->timer > 0x6) {
        anim1->state &= ~0x2;
        anim2->state &= ~0x2;

        proc->timer = 0;
        proc->unk2E++;
    } else {
        anim1->state |= 0x2;
        anim2->state |= 0x2;
    }

    if (proc->unk2E > 0x5) {
        proc->timer = 0;
        proc->unk2E = 0;
        Proc_Break(proc);
    }
}

CONST_DATA struct ProcCmd ProcScr_efxDeadAlpha[] = {
    PROC_NAME("efxDeadAlpha"),
    PROC_REPEAT(EfxDeadAlphaMain),
    PROC_END
};

void NewEfxDeadAlpha(struct Anim *anim1, struct Anim *anim2)
{
    struct ProcEfxDead *proc;
    proc = Proc_Start(ProcScr_efxDeadAlpha, PROC_TREE_3);
    
    proc->anim1 = anim1;
    proc->anim2 = anim2;
    proc->timer = 0;
    proc->unk2E = 0;

    anim1->drawLayerPriority = 0xA;
    anim2->drawLayerPriority = 0xA;
    AnimSort();

    SetSpecialColorEffectsParameters(0, 0x10, 0x10, 0x0);
    SetBlendTargetA(0, 0, 0, 0, 0);
    SetBlendTargetB(0, 0, 1, 1, 0);

    gLCDControlBuffer.bldcnt.target2_bd_on = true;
}

void EfxDeadAlphaMain(struct ProcEfxDead *proc)
{
    struct Anim *anim1 = proc->anim1;
    struct Anim *anim2 = proc->anim2;

    anim1->oamBase |= 0x400;
    anim2->oamBase |= 0x400;

    if (++proc->timer > 0x3C) {
        anim1->state |= 0x2;
        anim2->state |= 0x2;

        anim1->oamBase &= ~0x400;
        anim2->oamBase &= ~0x400;

        SetDefaultColorEffects();
        Proc_Break(proc);
        return;
    }

    SetSpecialColorEffectsParameters(
        0,
        Interpolate(INTERPOLATE_LINEAR, 0x10, 0, proc->timer, 0x3C),
        0x10, 0
    );
}

CONST_DATA struct ProcCmd ProcScr_efxDeadDragonAlpha[] = {
    PROC_NAME("efxDeadDragonAlpha"),
    PROC_REPEAT(EfxDeadDragonAlphaMain),
    PROC_END
};

void NewEfxDeadDragonAlpha(struct Anim *anim1, struct Anim *anim2)
{
    struct ProcEfxDead *proc;
    proc = Proc_Start(ProcScr_efxDeadDragonAlpha, PROC_TREE_3);

    proc->anim1 = anim1;
    proc->anim2 = anim2;

    anim1->state |= 0x2;
    anim2->state |= 0x2;

    EfxDracoZombiePrepareTSA(0, 0, EKR_POS_R);

    proc->timer = 0;
    proc->unk2E = 0;

    SetSpecialColorEffectsParameters(1, 0x10, 0x10, 0x0);
    SetBlendTargetA(0, 0, 0, 1, 0);
    SetBlendTargetB(0, 0, 1, 0, 0);

    SetWinEnable(1, 0, 0);
    SetWin0Box(0, 0, 0xF0, 0xA0);
    SetWin0Layers(1, 1, 1, 1, 1);
    gLCDControlBuffer.wincnt.win0_enableBlend = 1;
    gLCDControlBuffer.bldcnt.target2_bd_on = 1;
}

void EfxDeadDragonAlphaMain(struct ProcEfxDead *proc)
{
    if (++proc->timer > 0x3C) {
        sub_80559D0(0);
        BG_Fill(gBG3TilemapBuffer, 0xF000);
        BG_EnableSyncByMask(BG3_SYNC_BIT);
        SetDefaultColorEffects();
        Proc_Break(proc);
        return;
    }
        
    SetSpecialColorEffectsParameters(
        1,
        Interpolate(INTERPOLATE_LINEAR, 0x10, 0, proc->timer, 0x3C),
        0x10, 0
    );
}
