#include <jo/jo.h>
#include "ColorHelpers.h"

Bool do_update = false;
Bool l_update  = true;
Uint8 min_lum_idx = 0;
Uint8 max_lum_idx = 0;

void clamp_hsl(ObjectHSL *hsl)
{
    if (hsl->h >= 360)
        hsl->h = hsl->h - 360;
        
    if (hsl->h < 0)
        hsl->h = 360 + hsl->h;

    if (hsl->s > 255)
        hsl->s = 255;

    if (hsl->s < 0)
        hsl->s = 0;

    if (hsl->l > 255)
        hsl->l = 255;

    if (hsl->l < 0)
        hsl->l = 0;
}

void update_colors(ObjectHSL *hsl, GlobalHSL *hsl_increment, ObjectColor *color) {
    hsl->h += hsl_increment->h;
    hsl->s += hsl_increment->s;
    if (l_update) {
        hsl->l += hsl_increment->l;
    }
    clamp_hsl(hsl);
    ColorHelpers_HSLToRGB(hsl, color);
    do_update = false;
}

void reset_palette(RgbPalette *dest, const RgbPalette *src) {
    for (int i = 0; i < NUM_PALETTE_ENTRIES; i++) { // NUM_PALETTE_ENTRIES input needs to be a range of 0-maximum.  so multiple palette index groups can be adjusted independently
        dest->rgb0[i] = src->rgb0[i];
    }
}

void SinglePaletteUpdate(int index, ObjectColor color, jo_palette palette)
{
    palette.data[index] = JO_COLOR_RGB(color.r, color.g, color.b);
}

void MultiPaletteUpdate(jo_palette *palette, RgbPalette *rgbPal, HslPalette *hslPal, GlobalHSL *hsl_increment) {
    if ((hslPal->hsl0[min_lum_idx].l == 0 && hsl_increment->l > 0) || 
        (hslPal->hsl0[max_lum_idx].l == 255 && hsl_increment->l < 0) ||
        (hslPal->hsl0[min_lum_idx].l > 0 && hslPal->hsl0[max_lum_idx].l < 255)) {
        l_update = true;
    }
    else {
        l_update = false;
    }
    int i;
    for (i = 0; i < NUM_PALETTE_ENTRIES; i++) {
        update_colors(&hslPal->hsl0[i], hsl_increment, &rgbPal->rgb0[i]);
        palette->data[i]  = JO_COLOR_RGB(rgbPal->rgb0[i].r,  rgbPal->rgb0[i].g,  rgbPal->rgb0[i].b);
    }
}

// transformations
void MultiRgbToHsl(HslPalette *hslPal, RgbPalette *rgbPal) {
    int i;
    for (i = 0; i < NUM_PALETTE_ENTRIES; i++) {
        ColorHelpers_RGBToHSL(&rgbPal->rgb0[i], &hslPal->hsl0[i]);
    }
}

void MultiHslTorRgb(HslPalette *hslPal, RgbPalette *rgbPal) {
    int i;
    for (i = 0; i < NUM_PALETTE_ENTRIES; i++) {
        ColorHelpers_RGBToHSL(&rgbPal->rgb0[i], &hslPal->hsl0[i]);
    }
}

void min_max_lum_idx(HslPalette *hslPal) {
    for (int i = 1; i < NUM_PALETTE_ENTRIES; i++) {
        if (hslPal->hsl0[i].l < hslPal->hsl0[min_lum_idx].l) {
            min_lum_idx = i;
        }
        if (hslPal->hsl0[i].l > hslPal->hsl0[max_lum_idx].l) {
            max_lum_idx = i;
        }
    }
}