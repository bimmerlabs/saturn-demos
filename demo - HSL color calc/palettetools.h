#ifndef PALETTETOOLS_H
#define PALETTETOOLS_H

#include <jo/jo.h>

# define NUM_PALETTE_ENTRIES 16

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

typedef struct RgbPalette
{
    ObjectColor rgb0[NUM_PALETTE_ENTRIES];
} RgbPalette;

typedef struct HslPalette
{
    ObjectHSL hsl0[NUM_PALETTE_ENTRIES];
} HslPalette;

extern Bool do_update;
extern Bool l_update;
extern Uint8 min_lum_idx;
extern Uint8 max_lum_idx;

// Function prototypes
void clamp_hsl(ObjectHSL *hsl);
void update_colors(ObjectHSL *hsl, GlobalHSL *hsl_increment, ObjectColor *color);
void reset_palette(RgbPalette *dest, const RgbPalette *src);
void SinglePaletteUpdate(int index, ObjectColor color, jo_palette palette);

void MultiPaletteUpdate(jo_palette *palette, RgbPalette *rgbPal, HslPalette *hslPal, GlobalHSL *hsl_increment);
void MultiRgbToHsl(HslPalette *hslPal, RgbPalette *rgbPal);
void MultiHslTorRgb(HslPalette *hslPal, RgbPalette *rgbPal);

void min_max_lum_idx(HslPalette *hslPal);

#endif // PALETTETOOLS_H
