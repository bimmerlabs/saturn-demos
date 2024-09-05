#include <jo/jo.h>
#include "ColorHelpers.h"

Bool do_update = false;

void clamp_hue(ObjectHSL *hsl)
{
    if (hsl->h >= 360)
        hsl->h = hsl->h - 360;
        
    if (hsl->h < 0)
        hsl->h = 360 + hsl->h;
}

void update_colors(ObjectHSL *hsl, GlobalHSL *hsl_increment, ObjectColor *color) {
    hsl->h += hsl_increment->h;
    hsl->s += hsl_increment->s;
    hsl->l += hsl_increment->l;
    clamp_hue(hsl);
    ColorHelpers_HSLToRGB(hsl, color);
    do_update = false;
}

void reset_palette(RgbPalette *dest, const RgbPalette *src, PaletteRange *range) {
    for (int i = range->lower; i <= range->upper; i++) {
        dest->rgb0[i] = src->rgb0[i];
    }
}

void SinglePaletteUpdate(int index, ObjectColor color, jo_palette palette)
{
    palette.data[index] = JO_COLOR_RGB(color.r, color.g, color.b);
}

void MultiPaletteUpdate(jo_palette *palette, HslPalette *hslPal, GlobalHSL *hsl_increment, PaletteRange *range) {
    for (int i = range->lower; i <= range->upper; i++) {
        ObjectColor color;
        update_colors(&hslPal->hsl0[i], hsl_increment, &color);
        palette->data[i]  = JO_COLOR_RGB(color.r,  color.g,  color.b);
    }
}

// transformations
void MultiRgbToHsl(HslPalette *hslPal, RgbPalette *rgbPal, PaletteRange *range) {
    for (int i = range->lower; i <= range->upper; i++) {
        ColorHelpers_RGBToHSL(&rgbPal->rgb0[i], &hslPal->hsl0[i]);
    }
}

void MultiHslTorRgb(HslPalette *hslPal, RgbPalette *rgbPal, PaletteRange *range) {
    for (int i = range->lower; i <= range->upper; i++) {
        ColorHelpers_RGBToHSL(&rgbPal->rgb0[i], &hslPal->hsl0[i]);
    }
}

void min_max_sl_id(HslPalette *hslPal, PaletteRange *range, ImgAttributes *img_attr) {
    img_attr->min_sat_id = range->lower;
    img_attr->max_sat_id = range->upper;
    for (int i = range->lower; i <= range->upper; i++) {
        if (hslPal->hsl0[i].s < hslPal->hsl0[img_attr->min_sat_id].s) {
            img_attr->min_sat_id = i;
        }
        if (hslPal->hsl0[i].s > hslPal->hsl0[img_attr->max_sat_id].s) {
            img_attr->max_sat_id = i;
        }
    }
    img_attr->min_lum_id = range->lower;
    img_attr->max_lum_id = range->upper;
    for (int i = range->lower; i <= range->upper; i++) {
        if (hslPal->hsl0[i].l < hslPal->hsl0[img_attr->min_lum_id].l) {
            img_attr->min_lum_id = i;
        }
        if (hslPal->hsl0[i].l > hslPal->hsl0[img_attr->max_lum_id].l) {
            img_attr->max_lum_id = i;
        }
    }
}


void InitNormalImage(HslPalette *hslPal, PaletteRange *range, ImageConfig *image) {
    for (int i = range->lower; i <= range->upper; i++) {
        hslPal->hsl0[i].h = image->hue;
        hslPal->hsl0[i].s = image->sat; // subtracting gives a cool metalic effect / deeper colors
        hslPal->hsl0[i].l = image->lum; // increasing this reduces contrast
    }
}

void MultiLuminanceSet(HslPalette *hslPal, PaletteRange *range, ImageConfig *image) {
    for (int i = range->lower; i <= range->upper; i++) {
        hslPal->hsl0[i].l = image->lum; // increasing this reduces contrast
    }
}

void normal_lighting(HslPalette *hslPal, RgbPalette *rgbPal, LightSource *light, PaletteRange *range, ImageConfig *image) {
    for (int i = range->lower; i <= range->upper; i++) {
        // Calculate the difference between the light source XYZ and the palette RGB values
        int diff_r = light->x - rgbPal->rgb0[i].r;
        int diff_g = light->y - rgbPal->rgb0[i].g;
        int diff_b = light->z - rgbPal->rgb0[i].b;

        // Calculate the luminance adjustment based on the closeness of the light source to the color
        // For simplicity, let's assume we adjust it based on the Euclidean distance
        Sint16 distance = jo_sqrt(diff_r * diff_r + diff_g * diff_g + diff_b * diff_b);

        // Adjust the luminance by the inverse of the distance
        Sint16 luminance_adjustment = MAX(0, 255 - distance) - image->darkness;

        hslPal->hsl0[i].l += luminance_adjustment;
    }
}
