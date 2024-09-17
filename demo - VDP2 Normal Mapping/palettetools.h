#ifndef PALETTETOOLS_H
#define PALETTETOOLS_H

#include <jo/jo.h>
#include "palette_config.h"

// Struct definitions
typedef struct {
    Uint8 r;
    Uint8 g;
    Uint8 b;
} ObjectColor;

typedef struct {
    Sint16 h;
    Sint16 s;
    Sint16 l;
} ObjectHSL;

typedef struct {
    Sint16 h;
    Sint16 s;
    Sint16 l;
} GlobalHSL;

typedef struct {
    Uint8 lower;
    Uint8 upper;
} PaletteRange;

typedef struct {
    Uint8 lower;
    Uint8 upper;
} PaletteGroup;

typedef struct
{
    PaletteGroup group[NUM_PALETTE_GROUPS]; // need to replace with variable length arrays I think..
} PaletteGroupList;

typedef struct
{
    ObjectColor color[NUM_PALETTE_ENTRIES+1];
} RgbPalette;

typedef struct
{
    FIXED color[NUM_PALETTE_ENTRIES+1];
} RgbBuff;

typedef struct
{
    ObjectHSL color[NUM_PALETTE_ENTRIES+1];
} HslPalette;

extern Bool do_update;
extern Bool update_palette;

typedef struct {
    Uint8 min_sat_id;
    Uint8 max_sat_id;
    Uint8 min_lum_id;
    Uint8 max_lum_id;
} ImgAttributes;    

// Function prototypes
void clamp_hue(ObjectHSL *hsl);
void update_colors(ObjectHSL *hsl, GlobalHSL *hsl_increment, ObjectColor *color);
void reset_palette(RgbPalette *dest, const RgbPalette *src, PaletteRange *range);  // might not be needed
void SinglePaletteUpdate(int index, ObjectColor color, jo_palette palette);

void MultiPaletteUpdate(jo_palette *palette, HslPalette *hslPal, GlobalHSL *hsl_increment, PaletteRange *range);
void UpdatePaletteFromBuffer(RgbBuff *bufferPal, jo_palette *palette, PaletteRange *range);

void MultiRgbToHsl(HslPalette *hslPal, RgbPalette *rgbPal, PaletteRange *range);
void MultiHslTorRgb(HslPalette *hslPal, RgbPalette *rgbPal, PaletteRange *range);

void min_max_sl_id(HslPalette *hslPal, PaletteRange *range, ImgAttributes *img_attr);

void InitNormalImage(HslPalette *hslPal, PaletteRange *range, ImageConfig *image);

#endif // PALETTETOOLS_H
