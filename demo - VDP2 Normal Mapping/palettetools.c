#include <jo/jo.h>
#include "ColorHelpers.h"

Bool do_update = false;
Bool update_palette = false;

// palettes
void clamp_hue(ObjectHSL *hsl)
{
    if (hsl->h >= 360)
        hsl->h = hsl->h - 360;
        
    else if (hsl->h < 0)
        hsl->h = 360 + hsl->h;
}

void update_colors(ObjectHSL *hsl, GlobalHSL *hsl_increment, ObjectColor *color) {
    hsl->h += hsl_increment->h;
    hsl->s += hsl_increment->s;
    hsl->l += hsl_increment->l;
    clamp_hue(hsl);
    ColorHelpers_HSLToRGB(hsl, color);
}

void reset_palette(RgbPalette *dest, const RgbPalette *src, PaletteRange *range) {
    for (int i = range->lower; i <= range->upper; i++) {
        dest->color[i] = src->color[i];
    }
}

void SinglePaletteUpdate(int index, ObjectColor color, jo_palette palette)
{
    palette.data[index] = JO_COLOR_RGB(color.r, color.g, color.b);
}

void MultiPaletteUpdate(jo_palette *palette, HslPalette *hslPal, GlobalHSL *hsl_increment, PaletteRange *range) {
    for (int i = range->lower; i <= range->upper; i++) {
        ObjectColor color;
        update_colors(&hslPal->color[i], hsl_increment, &color);
        palette->data[i]  = JO_COLOR_RGB(color.r,  color.g,  color.b);
    }
    hsl_increment->h = 0;
    hsl_increment->s = 0;
    hsl_increment->l = 0;
}

void UpdatePaletteFromBuffer(RgbBuff *bufferPal, jo_palette *palette, PaletteRange *range) {
    for (int i = range->lower; i <= range->upper; i++) {
        palette->data[i]  = bufferPal->color[i];
        update_palette = false;
    }
}

// transformations
void MultiRgbToHsl(HslPalette *hslPal, RgbPalette *rgbPal, PaletteRange *range) {
    for (int i = range->lower; i <= range->upper; i++) {
        ColorHelpers_RGBToHSL(&rgbPal->color[i], &hslPal->color[i]);
    }
}

void MultiHslTorRgb(HslPalette *hslPal, RgbPalette *rgbPal, PaletteRange *range) {
    for (int i = range->lower; i <= range->upper; i++) {
        ColorHelpers_RGBToHSL(&rgbPal->color[i], &hslPal->color[i]);
    }
}

// tools
void min_max_sl_id(HslPalette *hslPal, PaletteRange *range, ImgAttributes *img_attr) {
    img_attr->min_sat_id = range->lower;
    img_attr->max_sat_id = range->upper;
    for (int i = range->lower; i <= range->upper; i++) {
        if (hslPal->color[i].s < hslPal->color[img_attr->min_sat_id].s) {
            img_attr->min_sat_id = i;
        }
        if (hslPal->color[i].s > hslPal->color[img_attr->max_sat_id].s) {
            img_attr->max_sat_id = i;
        }
    }
    img_attr->min_lum_id = range->lower;
    img_attr->max_lum_id = range->upper;
    for (int i = range->lower; i <= range->upper; i++) {
        if (hslPal->color[i].l < hslPal->color[img_attr->min_lum_id].l) {
            img_attr->min_lum_id = i;
        }
        if (hslPal->color[i].l > hslPal->color[img_attr->max_lum_id].l) {
            img_attr->max_lum_id = i;
        }
    }
}

void InitNormalImage(HslPalette *hslPal, PaletteRange *range, ImageConfig *image) {
    for (int i = range->lower; i <= range->upper; i++) {
        hslPal->color[i].h = image->hue;
        hslPal->color[i].s = image->sat;
        hslPal->color[i].l = image->lum;
    }
}
