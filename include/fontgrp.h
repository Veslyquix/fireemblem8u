#ifndef GUARD_FONTGRP_H
#define GUARD_FONTGRP_H

struct TextHandle
{
    u16 unk0;
    u8 x;
    u8 colorId;
    u8 unk4;
    s8 unk5;
    u8 unk6;
    u8 unk7;
};


struct Glyph
{
    struct Glyph *sjisNext;  // (only used in Shift-JIS fonts) next element in linked list
    u8 sjisByte1;            // (only used in Shift-JIS fonts) second byte of character
    u8 width;                // width of the glyph in pixels
    u32 bitmap[16];          // image data of the glyph (16x16 pixels, 2 bits per pixel)
};

struct Font
{
    /*0x00*/ u8 *vramDest;
             // pointer to table of glyph structs
             // In ASCII fonts, there is just one byte per character, so the glyph
             // for a given character is obtained by indexing this array.
             // In Shift-JIS fonts, each character is 2 bytes. Each element in
             // this array is a linked list. byte2 - 0x40 is the index of the head
             // of the list, and the list is traversed until a matching byte1 is found.
    /*0x04*/ struct Glyph **glyphs;
    /*0x08*/ void (*drawGlyph)(struct TextHandle *, struct Glyph *);
    /*0x0C*/ void *(*getVramTileOffset)(struct TextHandle *);
    /*0x10*/ u16 unk10;
    /*0x12*/ u16 unk12;
    /*0x14*/ u16 paletteNum;
    /*0x16*/ u8 isAscii;
};

struct TextBatch
{
    struct TextHandle *unk0;
    u8 unk4;
};


extern char gUnknown_02028E44[9];

// ??? SetupDebugFontForBG(???);
void PrintDebugStringToBG(u16 *bg, const char *asciiStr);
// ??? sub_800384C(???);
// ??? sub_8003870(???);
// ??? sub_80038B4(???);
// ??? ClearSmallStringBuffer(???);
// ??? StoreNumberStringToSmallBuffer(???);
// ??? StoreNumberStringOrDashesToSmallBuffer(???);
// ??? sub_800394C(???);
// ??? StoreNumberHexStringToSmallBuffer(???);
// ??? sub_80039B4(???);
void PrintStringToDBG(const char *str);
// ??? FlushDBGToBG2(???);
// ??? sub_8003ABC(???);
// ??? SetupDebugFontForOBJ(???);
// ??? PrintDebugStringAsOBJ(???);
// ??? sub_8003BFC(???);
// ??? sub_8003C20(???);
// ??? sub_8003C44(???);
// ??? GetSomeByte(???);
void SetSomeByte(int);
void Font_InitForUIDefault(void);
void Font_InitForUI(struct Font *a, void *b, int c, int d);
// ??? SetFontGlyphSet(???);
// ??? sub_8003D20(???);
void SetFont(struct Font *a);
void Text_Init(struct TextHandle *a, int b);
// ??? Text_Allocate(???);
// ??? InitTextBatch(???);
void Text_Clear(struct TextHandle *a);
// ??? sub_8003E00(???);
// ??? sub_8003E40(???);
// ??? Text_GetXCursor(???);
// ??? Text_SetXCursor(???);
// ??? Text_Advance(???);
// ??? Text_SetColorId(???);
// ??? Text_GetColorId(???);
void Text_SetParameters(struct TextHandle* th, int x, int colorId);
void Text_Draw(struct TextHandle* th, u16* dest);
// ??? Text_DrawBlank(???);
// ??? GetStringTextWidth(???);
// ??? GetCharTextWidth(???);
// ??? GetStringTextCenteredPos(???);
// ??? sub_8003FAC(???);
char *String_GetEnd(char *);
void Text_AppendString(struct TextHandle *th, char* str);
// ??? Text_AppendDecNumber(???);
// ??? sub_80040C0(???);
// ??? Text_AppendNumberOr2Dashes(???);
const char *Text_AppendChar(struct TextHandle *a, const char *b);
void *GetVRAMPointerForTextMaybe(struct TextHandle *a);
// ??? GetGlyphColorLUT(???);
// ??? Font_StandardGlyphDrawer(???);
// ??? Font_SpecializedGlyphDrawer(???);
void Font_LoadForUI(void);
// ??? Font_LoadForDialogue(???);
// ??? Font_SetSomeSpecialDrawingRoutine(???);
// ??? DrawTextInline(???);
// ??? Text_InsertString(???);
// ??? Text_InsertNumberOr2Dashes(???);
void Text_AppendStringASCII(struct TextHandle *text, const char *str);
const char *Text_AppendCharASCII(struct TextHandle *text, const char *str);
char *GetCharTextWidthASCII(char *str, u32 *width);
int GetStringTextWidthASCII(const char *str);
// ??? sub_8004598(???);
// ??? InitSomeOtherGraphicsRelatedStruct(???);
// ??? Text_Init3(???);
// ??? sub_80045FC(???);
// ??? sub_800465C(???);
// ??? Text_80046B4(???);
void *sub_80046E0(struct TextHandle *);
void sub_8004700(struct TextHandle *, struct Glyph *);
// ??? sub_80048B0(???);
// ??? sub_8004924(???);
// ??? sub_800496C(???);
// ??? sub_8004974(???);
// ??? sub_8004984(???);
// ??? NewGreenTextColorManager(???);
// ??? EndGreenTextColorManager(???);
// ??? sub_80049E0(???);
// ??? sub_8004A34(???);
// ??? sub_8004A90(???);
// ??? sub_8004ACC(???);
// ??? sub_8004B0C(???);
// ??? sub_8004B48(???);
// ??? sub_8004B88(???);
void DrawDecNumber(u16* a, int b, int c);
// ??? sub_8004BB4(???);
// ??? sub_8004BE4(???);
// ??? sub_8004BF0(???);
// ??? sub_8004C1C(???);
// ??? sub_8004C68(???);
void sub_8004D5C();
// ??? sub_8004D7C(???);
// ??? sub_8004DB8(???);
// ??? sub_8004DF8(???);

#endif  // GUARD_FONTGRP_H
