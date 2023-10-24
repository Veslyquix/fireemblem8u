#include "global.h"
#include "proc.h"
#include "anime.h"
#include "ekrbattle.h"
#include "efxbattle.h"
#include "ekrlevelup.h"
#include "hardware.h"
#include "mapanim.h"
#include "ctc.h"
#include "bmlib.h"

EWRAM_DATA int gEkrBg2ScrollFlip = 0;
EWRAM_DATA u16 * gpEkrLvupBg2ScrollOffsetStart = NULL;
EWRAM_DATA u16 * gpEkrLvupBg2ScrollOffset = NULL;
EWRAM_DATA u16 gpEkrLvupBg2ScrollOffsetTable1[160] = {0};
EWRAM_DATA u16 gpEkrLvupBg2ScrollOffsetTable2[160] = {0};

EWRAM_DATA int gEkrBg1ScrollFlip = 0;
EWRAM_DATA u16 * gpEkrLvupBg1ScrollOffsetStart = NULL;
EWRAM_DATA u16 * gpEkrLvupBg1ScrollOffset = NULL;
EWRAM_DATA u16 gpEkrLvupBg1ScrollOffsetList1[160] = {0};
EWRAM_DATA u16 gpEkrLvupBg1ScrollOffsetList2[160] = {0};

EWRAM_DATA int gUnknown_02020044 = 0;

CONST_DATA struct ProcCmd ProcScr_EfxPartsofScroll[] = {
    PROC_NAME("efxPartsofScroll"),
    PROC_SET_END_CB(EfxPartsofScrollCallBack),
    PROC_REPEAT(EfxPartsofScrollMain),
    PROC_END
};

ProcPtr NewEfxPartsofScroll(void)
{
    struct ProcEfx * proc =
        Proc_Start(ProcScr_EfxPartsofScroll, PROC_TREE_3);

    proc->timer = 0;
    proc->unk2E = 0;
    return proc;
}

void EfxUpdatePartsofScroll(void)
{
    u32 i;

    u16 * buf1 = (gEkrBg1ScrollFlip == 0)
               ? gpEkrLvupBg2ScrollOffsetTable2
               : gpEkrLvupBg2ScrollOffsetTable1;

    u16 * buf2 = (gEkrBg1ScrollFlip == 0)
               ? gpEkrLvupBg1ScrollOffsetList2
               : gpEkrLvupBg1ScrollOffsetList1;

    for (i = 0; i < 0xA0; i++)
    {
        if (i < 0x28)
        {
            *buf1++ = 0;
            *buf2++ = 0;
            continue;
        }

        if (i <= 0x47)
        {
            *buf1++ = gEkrLvupScrollPos1;
            *buf2++ = gEkrLvupScrollPos1;
            continue;
        }

        if (i <= 0x9F)
        {
            *buf1++ = gEkrLvupScrollPos2;
            *buf2++ = gEkrLvupScrollPos2;
            continue;
        }
    }
}

void EfxPartsofScrollCallBack(ProcPtr proc)
{
    return;
}

void EfxPartsofScrollMain(ProcPtr proc)
{
    EfxUpdatePartsofScroll();
}

CONST_DATA struct ProcCmd ProcScr_EfxPartsofScroll2[] = {
    PROC_NAME("efxPartsofScroll2"),
    PROC_SET_END_CB(EfxPartsofScroll2CallBack),
    PROC_REPEAT(EfxPartsofScroll2Main),
    PROC_END
};

ProcPtr NewEfxPartsofScroll2(void)
{
    struct ProcEfx * proc =
        Proc_Start(ProcScr_EfxPartsofScroll2, PROC_TREE_3);

    proc->timer = 0;
    proc->unk2E = 0;
    return proc;
}

void EfxPartsofScroll2CallBack(ProcPtr proc)
{
    return;
}

CONST_DATA s16 gUnknown_0875941C[] = {
    -0x100, -0xEE, -0xDD, -0xCC, -0xBB, -0xAA, -0x99, -0x88,
     -0x77, -0x66, -0x55, -0x44, -0x33, -0x22, -0x22, -0x11,
      0x11,  0x22,  0x22,  0x33,  0x44,  0x55,  0x66,  0x77,
      0x88,  0x99,  0xAA,  0xBB,  0xCC,  0xDD,  0xEE, 0x100
};

void EfxPartsofScroll2Main(ProcPtr proc)
{
    u16 * buf1 = (gEkrBg1ScrollFlip == 0)
               ? gpEkrLvupBg2ScrollOffsetTable2
               : gpEkrLvupBg2ScrollOffsetTable1;

    u16 * buf2 = (gEkrBg1ScrollFlip == 0)
               ? gpEkrLvupBg1ScrollOffsetList2
               : gpEkrLvupBg1ScrollOffsetList1;

    u32 i = 0;

    for (; i < 0xA0; i++)
    {
        s16 * src = gUnknown_0875941C;
        src = src - 0x28;

        if (i < 0x28)
        {
            *buf1++ = 0;
            *buf2++ = 0;
            continue;
        }

        if (i <= 0x47)
        {
            s16 val2 = (src[i] * gEkrLvupScrollPos1) >> 0xC;

            if (i + val2 < 0x2F)
                val2 = -0x20;
            else if (i + val2 >= 0x52)
                val2 = -0x20;

            *buf1++ = val2;
            *buf2++ = val2;
            continue;
        }

        if (i <= 0x9F)
        {
            *buf1++ = 0;
            *buf2++ = 0;
            continue;
        }
    }
}

CONST_DATA struct ProcCmd ProcScr_Efxleveluphb[] = {
    PROC_NAME("efxLevelupHB"),
    PROC_SET_END_CB(EfxleveluphbCallBack),
    PROC_REPEAT(EfxleveluphbNop),
    PROC_REPEAT(EfxleveluphbMain),
    PROC_END
};

ProcPtr NewEfxleveluphb(void)
{
    u32 i;
    struct ProcEfx * proc;
    u16 * buf;
    struct ProcCmd * v;

    gEfxBgSemaphore++;

    buf = gpEkrLvupBg2ScrollOffsetTable1;
    for (i = 0; i < 0xA0; i++)
        *buf++ = 0;

    buf = gpEkrLvupBg2ScrollOffsetTable2;
    for (i = 0; i < 0xA0; i++)
        *buf++ = 0;

    buf = gpEkrLvupBg1ScrollOffsetList1;
    for (i = 0; i < 0xA0; i++)
        *buf++ = 0;

    buf = gpEkrLvupBg1ScrollOffsetList2;
    for (i = 0; i < 0xA0; i++)
        *buf++ = 0;

    gEkrBg2ScrollFlip = 0;
    v = ProcScr_Efxleveluphb; // by permuter

    gEkrBg1ScrollFlip = 0;
#ifndef NONMATCHING
    asm("":::"v7"); // by me
#endif
    buf = gpEkrLvupBg2ScrollOffsetTable1;
    gpEkrLvupBg2ScrollOffsetStart = buf;
    buf = gpEkrLvupBg1ScrollOffsetList1;
    gpEkrLvupBg1ScrollOffsetStart = buf;
    buf = gpEkrLvupBg2ScrollOffsetStart;
    gpEkrLvupBg2ScrollOffset = buf;
    buf = gpEkrLvupBg1ScrollOffsetStart;
    gpEkrLvupBg1ScrollOffset = buf;

    proc = Proc_Start(v, PROC_TREE_VSYNC);
    proc->timer = 0;
    return proc;
}

void EfxleveluphbCallBack(ProcPtr proc)
{
    SetPrimaryHBlankHandler(NULL);
}

void EfxleveluphbNop(ProcPtr proc)
{
    Proc_Break(proc);
}

void EfxleveluphbMain(ProcPtr proc)
{
    if (gBmSt.sync_hardware != false)
    {
        if (gEkrBg2ScrollFlip == 1)
        {
            gEkrBg2ScrollFlip = 0;
            gpEkrLvupBg2ScrollOffsetStart = gpEkrLvupBg2ScrollOffsetTable1;
        }
        else
        {
            gEkrBg2ScrollFlip = 1;
            gpEkrLvupBg2ScrollOffsetStart = gpEkrLvupBg2ScrollOffsetTable2;
        }
    
        if (gEkrBg1ScrollFlip == 1)
        {
            gEkrBg1ScrollFlip = 0;
            gpEkrLvupBg1ScrollOffsetStart = gpEkrLvupBg1ScrollOffsetList1;
        }
        else
        {
            gEkrBg1ScrollFlip = 1;
            gpEkrLvupBg1ScrollOffsetStart = gpEkrLvupBg1ScrollOffsetList2;
        }
    }
    gpEkrLvupBg2ScrollOffset = gpEkrLvupBg2ScrollOffsetStart;
    gpEkrLvupBg1ScrollOffset = gpEkrLvupBg1ScrollOffsetStart;
}

void EkrLvupHBlank(void)
{
    /* line 160..226 */
    if (REG_DISPSTAT & DISPSTAT_VBLANK)
        return;

    REG_BG2HOFS = *gpEkrLvupBg2ScrollOffset++;
    REG_BG1HOFS = *gpEkrLvupBg1ScrollOffset++;
}

void EfxPartsofScroll2HBlank(void)
{
    /* line 160..226 */
    if (REG_DISPSTAT & DISPSTAT_VBLANK)
        return;

    REG_BG2VOFS = gLCDControlBuffer.bgoffset[2].y + *gpEkrLvupBg2ScrollOffset++;
    REG_BG1VOFS = gLCDControlBuffer.bgoffset[1].y + *gpEkrLvupBg1ScrollOffset++;
}

CONST_DATA struct ProcCmd ProcScr_Efxlvupbg[] = {
    PROC_NAME("efxLvupBG"),
    PROC_REPEAT(EfxlvupbgMain),
    PROC_END
};

const u16 FrameConfig_EfxLvupBG[] = {
    0, 1,
    1, 1,
    2, 1,
    3, 1,
    4, 1,
    5, 1,
    6, 1,
    7, 1,
    8, 1,
    9, 1,
    10, 1,
    -1
};

CONST_DATA u16 * TsaLut_EfxLvupBG[] = {
    Tsa1_EfxLvupBG,
    Tsa2_EfxLvupBG,
    Tsa3_EfxLvupBG,
    Tsa4_EfxLvupBG,
    Tsa5_EfxLvupBG,
    Tsa6_EfxLvupBG,
    Tsa7_EfxLvupBG,
    Tsa8_EfxLvupBG,
    Tsa9_EfxLvupBG,
    Tsa10_EfxLvupBG,
    Tsa11_EfxLvupBG
};

CONST_DATA u16 * ImgLut_EfxLvupBG[] = {
    Img1_EfxLvupBG,
    Img1_EfxLvupBG,
    Img2_EfxLvupBG,
    Img2_EfxLvupBG,
    Img3_EfxLvupBG,
    Img4_EfxLvupBG,
    Img5_EfxLvupBG,
    Img6_EfxLvupBG,
    Img7_EfxLvupBG,
    Img7_EfxLvupBG,
    Img7_EfxLvupBG
};

void NewEfxlvupbg(struct Anim * anim)
{
    struct ProcEfxBG * proc =
        Proc_Start(ProcScr_Efxlvupbg, PROC_TREE_3);

    proc->anim = anim;
    proc->timer = 0;
    proc->frame = 0;
    proc->frame_config = FrameConfig_EfxLvupBG;
    proc->tsal = TsaLut_EfxLvupBG;
    proc->tsar = TsaLut_EfxLvupBG;
    proc->img = ImgLut_EfxLvupBG;

    SpellFx_RegisterBgPal(Pal_EfxLvupBG, 0x20);
    SpellFx_SetSomeColorEffect();
}

void EfxlvupbgMain(struct ProcEfxBG * proc)
{
    int ret;
    ret = EfxAdvanceFrameLut((s16 *)&proc->timer, (s16 *)&proc->frame, proc->frame_config);
    if (ret >= 0) {
        u16 ** tsa1 = proc->tsal;
        u16 ** tsa2 = proc->tsar;
        u16 ** img = proc->img;

        SpellFx_WriteBgMap(proc->anim, tsa1[ret], tsa2[ret]);
        SpellFx_RegisterBgGfx(img[ret], 0x2000);
        return;
    }

    if (ret == -1)
    {
        SpellFx_ClearBG1();
        SetDefaultColorEffects_();
        Proc_Break(proc);
    }
}

CONST_DATA struct ProcCmd ProcScr_efxLvupBG2[] = {
    PROC_NAME("efxLvupBG2"),
    PROC_REPEAT(EfxLvupBg2Main),
    PROC_END
};

CONST_DATA u16 * TsaLut_EfxLvupBG2[] = {
    Tsa1_EfxLvupBG2,
    Tsa2_EfxLvupBG2,
    Tsa3_EfxLvupBG2,
    Tsa4_EfxLvupBG2,
    Tsa5_EfxLvupBG2,
    Tsa6_EfxLvupBG2
};

const u16 FrameConfig_EfxLvupBG2[] = {
    0, 1,
    1, 1,
    2, 1,
    3, 1,
    4, 1,
    5, 0x1C,
    -1
};

void NewEfxLvupBG2(struct Anim * anim)
{
    struct ProcEfxBG * proc =
        Proc_Start(ProcScr_efxLvupBG2, PROC_TREE_3);

    proc->anim = anim;
    proc->timer = 0;
    proc->frame = 0;
    proc->frame_config = FrameConfig_EfxLvupBG2;
    proc->tsal = TsaLut_EfxLvupBG2;
    proc->tsar = TsaLut_EfxLvupBG2;

    SpellFx_RegisterBgGfx(Img_EfxLvupBG2, 0x2000);
    SpellFx_RegisterBgPal(Pal_EfxLvupBG2, 0x20);
}

void EfxLvupBg2Main(struct ProcEfxBG * proc)
{
    int ret;
    ret = EfxAdvanceFrameLut((s16 *)&proc->timer, (s16 *)&proc->frame, proc->frame_config);
    if (ret >= 0) {
        u16 ** tsa1 = proc->tsal;
        u16 ** tsa2 = proc->tsar;

        SpellFx_WriteBgMap(proc->anim, tsa1[ret], tsa2[ret]);
        return;
    }

    if (ret == -1)
        Proc_Break(proc);
}

CONST_DATA struct ProcCmd ProcScr_efxLvupOBJ2[] = {
    PROC_NAME("efxLvupOBJ2"),
    PROC_SET_END_CB(EfxLvupOBJ2CallBack),
    PROC_SLEEP(0x18),
    PROC_END
};

void NewEfxLvupOBJ2(struct Anim * anim, int x, int y)
{
    struct Anim * anim3;
    struct ProcEfxOBJ * proc =
        Proc_Start(ProcScr_efxLvupOBJ2, PROC_TREE_3);

    proc->anim = anim;
    anim3 = EfxCreateFrontAnim(anim, AnimScr_EfxLvupOBJ2, AnimScr_EfxLvupOBJ2, AnimScr_EfxLvupOBJ2, AnimScr_EfxLvupOBJ2);
    proc->anim3 = anim3;
    anim3->xPosition = x;
    anim3->yPosition = y;

    SpellFx_RegisterObjGfx(Img_EfxLvupOBJ2, 0x1000);
    SpellFx_RegisterObjPal(Pal_EfxLvupBG2, 0x20);
}

void EfxLvupOBJ2CallBack(struct ProcEfxOBJ * proc)
{
    AnimDelete(proc->anim3);
}

CONST_DATA struct ProcCmd ProcScr_efxLvupBGCOL[] = {
    PROC_NAME("efxLvupBGCOL"),
    PROC_REPEAT(Loop6C1_EfxLvupBGCOL),
    PROC_REPEAT(Loop6C2_EfxLvupBGCOL),
    PROC_END
};

const u16 FrameLut_EfxLvupBGCOL[] = {
    0, 2,
    1, 2,
    2, 2,
    3, 2,
    4, 2,
    5, 2,
    6, 2,
    7, 2,
    8, 2,
    9, 2,
    10, 2,
    11, 2,
    12, 2,
    13, 2,
    14, 2,
    15, 2,
    -2
};

void NewEfxLvupBGCOL(struct Anim * anim)
{
    struct ProcEfxBGCOL * proc =
        Proc_Start(ProcScr_efxLvupBGCOL, PROC_TREE_3);

    proc->anim = anim;
    proc->timer = 0;
    proc->timer2 = 0;
    proc->terminator = 0x19;
    proc->frame = 0;
    proc->frame_config = FrameLut_EfxLvupBGCOL;
    proc->pal = Pal_EfxLvupBGCOL;
}

const u16 FrameLut2_EfxLvupBGCOL[] = {
    0, 2,
    1, 2,
    2, 2,
    3, 2,
    -1
};

void Loop6C1_EfxLvupBGCOL(struct ProcEfxBGCOL * proc)
{
    int ret;
    ret = EfxAdvanceFrameLut((s16 *)&proc->timer, (s16 *)&proc->frame, proc->frame_config);
    if (ret >= 0)
        sub_805588C(proc->pal, gPaletteBuffer + 1, ret, 0xF, 8);

    if (++proc->timer2 > proc->terminator)
    {
        proc->timer = 0;
        proc->timer2 = 0;
        proc->frame = 0;
        proc->frame_config = FrameLut2_EfxLvupBGCOL;
        proc->pal = Pal_EfxLvupBG2;
        Proc_Break(proc);
    }
}

void Loop6C2_EfxLvupBGCOL(struct ProcEfxBGCOL * proc)
{
    int ret;
    ret = EfxAdvanceFrameLut((s16 *)&proc->timer, (s16 *)&proc->frame, proc->frame_config);
    if (ret >= 0)
    {
        u16 * pal = proc->pal;
        SpellFx_RegisterBgPal(&PAL_BUF_COLOR(pal, ret, 0), 0x20);
        return;
    }

    if (ret == -1)
        Proc_Break(proc);
}

void EkrLvupApfxInit(struct ProcEkrLvupApfx * proc)
{
    proc->clock = 0;
}

void EkrLvupApfxMain(struct ProcEkrLvupApfx * proc)
{
    int new_color_offset;
    u16 * colors = Pal_ManimLevelUpStatGainCycling;

    ++proc->clock;

    if (proc->clock & 3)
        return;

    new_color_offset = (proc->clock >> 2) & 0xF;

    // TODO: constants
    CopyToPaletteBuffer(colors + new_color_offset + 0x00, (0x10 + proc->pal + 0) * 0x20 + 0x12, 0x20 - 0x12);
    CopyToPaletteBuffer(colors + new_color_offset + 0x20, (0x10 + proc->pal + 1) * 0x20 + 0x12, 0x20 - 0x12);
}

CONST_DATA struct ProcCmd ProcScr_EkrLvupApfx[] = {
    PROC_CALL(EkrLvupApfxInit),
    PROC_REPEAT(EkrLvupApfxMain),
    PROC_END
};

void NewEkrLvupApfx(int chr, int pal)
{
    int pal_bank;
    const u16 * pal_src;
    struct ProcEkrLvupApfx * proc;

    Decompress(Img_ManimLevelUpStatGain, OBJ_VRAM0 + OAM2_CHR(chr) * CHR_SIZE);

    pal_src = Pal_ManimLevelUp;
    pal_bank = pal + 0x10;
    ApplyPalette(pal_src, pal + 0x10);

    pal_bank = pal + 0x11;
    ApplyPalette(pal_src, pal_bank);

    proc = Proc_Start(ProcScr_EkrLvupApfx, PROC_TREE_3);
    proc->pal = pal;
    gEkrLvupApfxUnexist = false;
}

void EkrLvupApfxEndEach(void)
{
    Proc_EndEach(ProcScr_EkrLvupApfx);
    gEkrLvupApfxUnexist = true;
}

void PutEkrLvupStatGainLabelGfx1(int stat_num, int stat_gain)
{
    u8 * img = Img_EkrLvupNumBig;
    register int chr asm("r4");
    int chr_this_stat;

    chr = (stat_num - 1) * 2;

    chr_this_stat = chr;
    if (chr < 0)
        chr_this_stat = -chr;

    VramCopy(img + OAM2_CHR(chr_this_stat) * CHR_SIZE,
        OBJ_VRAM0 + (OAM2_CHR(stat_gain + 0x2C) << 5), 2 * CHR_SIZE);

    chr_this_stat = chr >= 0 ? chr : -chr;
    VramCopy(img + OAM2_CHR((chr_this_stat) + 0x20) * CHR_SIZE,
        OBJ_VRAM0 + (OAM2_CHR(stat_gain + 0x4C) << 5), 2 * CHR_SIZE);
}

void PutEkrLvupStatGainLabelGfx2(int chr, int stat_gain)
{
    int chr_this_stat;
    int chr_this_stat_2;
    u8 * img1;
    u8 * img2;

    img1 = Img_ManimLevelUpStatGainDigits;
    img2 = Img_EkrLvupNumBig;

    if (chr >= 0)
    {
        VramCopy(img2 + 0x18 * CHR_SIZE,
            OBJ_VRAM0 + (OAM2_CHR(stat_gain + 0x2C) << 5), 2 * CHR_SIZE);

        VramCopy(img2 + 0x38 * CHR_SIZE,
            OBJ_VRAM0 + (OAM2_CHR(stat_gain + 0x4C) << 5), 2 * CHR_SIZE);
    }
    else
    {
        VramCopy(img2 + 0x1A * CHR_SIZE,
            OBJ_VRAM0 + (OAM2_CHR(stat_gain + 0x2C) << 5), 2 * CHR_SIZE);

        VramCopy(img2 + 0x3A * CHR_SIZE,
            OBJ_VRAM0 + (OAM2_CHR(stat_gain + 0x4C) << 5), 2 * CHR_SIZE);
    }

    chr_this_stat = chr >= 0 ? chr : -chr;
    VramCopy(img1 + OAM2_CHR(chr_this_stat) * CHR_SIZE,
        OBJ_VRAM0 + (OAM2_CHR(stat_gain + 0x2D) << 5), CHR_SIZE);

    chr_this_stat_2 = chr >= 0 ? chr : -chr;
    VramCopy(img1 + OAM2_CHR((chr_this_stat_2) + 0x20) * CHR_SIZE,
        OBJ_VRAM0 + (OAM2_CHR(stat_gain + 0x4D) << 5), CHR_SIZE);
}

CONST_DATA struct ProcCmd ProcScr_eobjLvup[] = {
    PROC_NAME("eobjLvup"),
    PROC_REPEAT(sub_8074E6C),
    PROC_REPEAT(sub_8074EDC),
    PROC_REPEAT(sub_8074F14),
    PROC_END
};

/**
 * https://decomp.me/scratch/XQtZJ
 * Quite in process LOL
 */
#if NONMATCHING

void BanimDrawStatupAp(int chr, int pal, int x, int y, int index, int gain)
{
    struct ProcEobjLvup * proc;
    int chr2 = chr + 2 * (index - 1);
    int _pal = pal << 12;
    int _chr = chr | 0x400;
    int __oam = _chr | _pal;

    NewEkrsubAnimeEmulator(x - 0x12, y - 0x04, gUnknown_085C9270, 0, __oam, 0, PROC_TREE_5);
    if (index == 0)
        return;

    proc = Proc_Start(ProcScr_eobjLvup, PROC_TREE_3);

    if (gain >= 0)
    {
        proc->child2 = NewEkrsubAnimeEmulator(x, y, gUnknown_085C92A0, 2, __oam, 0, PROC_TREE_5);
    }
    else
    {
        int _oam = chr2 | 0x400 | _pal;
        proc->child1 = NewEkrsubAnimeEmulator(x - 3, y, gUnknown_085C92EC, 2, _oam, 0, PROC_TREE_5);

        _oam = _chr | _pal;
        proc->child1 = NewEkrsubAnimeEmulator(x, y, gUnknown_085C92D0, 2, _oam, 0, PROC_TREE_5);
        PutEkrLvupStatGainLabelGfx2(gain, _pal);
    }
    proc->x = x;
    proc->y = y;
    proc->timer = 0;
    proc->chr1 = chr;
    proc->chr2 = chr2;
    proc->chr = chr;
    proc->pal = pal;
    proc->index = index;
    proc->diff = gain;
}

#else

NAKEDFUNC
void BanimDrawStatupAp(int chr, int pal, int x, int y, int index, int gain)
{
    asm("\
        .syntax unified\n\
        push {r4, r5, r6, r7, lr}\n\
        mov r7, sl\n\
        mov r6, r9\n\
        mov r5, r8\n\
        push {r5, r6, r7}\n\
        sub sp, #0x1c\n\
        str r0, [sp, #0xc]\n\
        str r1, [sp, #0x10]\n\
        mov r8, r2\n\
        mov r9, r3\n\
        str r0, [sp, #0x14]\n\
        ldr r0, [sp, #0x3c]\n\
        subs r0, #1\n\
        lsls r0, r0, #1\n\
        ldr r1, [sp, #0xc]\n\
        adds r0, r1, r0\n\
        str r0, [sp, #0x18]\n\
        ldr r3, [sp, #0x10]\n\
        lsls r6, r3, #0xc\n\
        adds r7, r1, #0\n\
        movs r0, #0x80\n\
        lsls r0, r0, #3\n\
        orrs r7, r0\n\
        adds r5, r6, #0\n\
        orrs r5, r7\n\
        mov r0, r8\n\
        subs r0, #0x12\n\
        mov r1, r9\n\
        subs r1, #4\n\
        ldr r2, _08074DD8  @ gUnknown_085C9270\n\
        str r5, [sp]\n\
        movs r3, #0\n\
        mov sl, r3\n\
        str r3, [sp, #4]\n\
        movs r3, #5\n\
        str r3, [sp, #8]\n\
        movs r3, #0\n\
        bl NewEkrsubAnimeEmulator\n\
        ldr r0, [sp, #0x3c]\n\
        cmp r0, #0\n\
        beq _08074E52\n\
        ldr r0, _08074DDC  @ ProcScr_eobjLvup\n\
        movs r1, #3\n\
        bl Proc_Start\n\
        adds r4, r0, #0\n\
        ldr r1, [sp, #0x40]\n\
        cmp r1, #0\n\
        blt _08074DE4\n\
        ldr r2, _08074DE0  @ gUnknown_085C92A0\n\
        str r5, [sp]\n\
        mov r3, sl\n\
        str r3, [sp, #4]\n\
        movs r0, #5\n\
        str r0, [sp, #8]\n\
        mov r0, r8\n\
        mov r1, r9\n\
        movs r3, #2\n\
        bl NewEkrsubAnimeEmulator\n\
        str r0, [r4, #0x64]\n\
        b _08074E2A\n\
        .align 2, 0\n\
    _08074DD8: .4byte gUnknown_085C9270\n\
    _08074DDC: .4byte ProcScr_eobjLvup\n\
    _08074DE0: .4byte gUnknown_085C92A0\n\
    _08074DE4:\n\
        ldr r1, [sp, #0x18]\n\
        movs r3, #0x80\n\
        lsls r3, r3, #3\n\
        orrs r1, r3\n\
        orrs r1, r6\n\
        mov r0, r8\n\
        subs r0, #3\n\
        ldr r2, _08074E64  @ gUnknown_085C92EC\n\
        str r1, [sp]\n\
        mov r1, sl\n\
        str r1, [sp, #4]\n\
        movs r3, #5\n\
        str r3, [sp, #8]\n\
        mov r1, r9\n\
        movs r3, #2\n\
        bl NewEkrsubAnimeEmulator\n\
        str r0, [r4, #0x60]\n\
        orrs r6, r7\n\
        ldr r2, _08074E68  @ gUnknown_085C92D0\n\
        str r6, [sp]\n\
        mov r0, sl\n\
        str r0, [sp, #4]\n\
        movs r1, #5\n\
        str r1, [sp, #8]\n\
        mov r0, r8\n\
        mov r1, r9\n\
        movs r3, #2\n\
        bl NewEkrsubAnimeEmulator\n\
        str r0, [r4, #0x64]\n\
        ldr r0, [sp, #0x40]\n\
        ldr r1, [sp, #0x18]\n\
        bl PutEkrLvupStatGainLabelGfx2\n\
    _08074E2A:\n\
        movs r0, #0\n\
        mov r3, r8\n\
        strh r3, [r4, #0x32]\n\
        mov r1, r9\n\
        strh r1, [r4, #0x3a]\n\
        strh r0, [r4, #0x2c]\n\
        mov r3, sp\n\
        ldrh r3, [r3, #0x14]\n\
        strh r3, [r4, #0x2e]\n\
        mov r0, sp\n\
        ldrh r0, [r0, #0x18]\n\
        strh r0, [r4, #0x30]\n\
        ldr r1, [sp, #0xc]\n\
        str r1, [r4, #0x44]\n\
        ldr r3, [sp, #0x10]\n\
        str r3, [r4, #0x48]\n\
        ldr r0, [sp, #0x3c]\n\
        str r0, [r4, #0x4c]\n\
        ldr r1, [sp, #0x40]\n\
        str r1, [r4, #0x50]\n\
    _08074E52:\n\
        add sp, #0x1c\n\
        pop {r3, r4, r5}\n\
        mov r8, r3\n\
        mov r9, r4\n\
        mov sl, r5\n\
        pop {r4, r5, r6, r7}\n\
        pop {r0}\n\
        bx r0\n\
        .align 2, 0\n\
    _08074E64: .4byte gUnknown_085C92EC\n\
    _08074E68: .4byte gUnknown_085C92D0\n\
        .syntax divided\n\
    ");
}

#endif

void sub_8074E6C(struct ProcEobjLvup * proc)
{
    int oam2;
    if (proc->diff < 0)
    {
        Proc_Break(proc);
        return;
    }

    if (++proc->timer == 0xF)
    {
        proc->timer = 0;

        {
            int _pal = proc->pal << 12;
            int _chr = proc->chr2;
            int _lay = 0x400;
            oam2 = _pal | (_chr | _lay);
        }

        proc->child1 = NewEkrsubAnimeEmulator(
            proc->x - 3,
            proc->y,
            gUnknown_085C9328,
            2,
            oam2,
            0,
            PROC_TREE_3
        );
        PutEkrLvupStatGainLabelGfx1(proc->diff, proc->chr2);
        Proc_Break(proc);
    }
}

void sub_8074EDC(struct ProcEobjLvup * proc)
{
    int oam2;
    if (proc->diff < 0)
    {
        Proc_Break(proc);
        return;
    }

    if (++proc->timer == 0xF)
    {
        proc->timer = 0;
        PutEkrLvupStatGainLabelGfx2(proc->diff, proc->chr2);
        Proc_Break(proc);
    }
}

void sub_8074F14(struct ProcEobjLvup * proc)
{
    if (gEkrLvupApfxUnexist == true)
    {
        Proc_End(proc->child1);
        Proc_End(proc->child2);
        Proc_Break(proc);
    }
}
