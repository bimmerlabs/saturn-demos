// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: ColorHelpers Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// Modified for Saturn by: Hassmaschine
// ---------------------------------------------------------------------
#include "ColorHelpers.h"

// can probably use the ones in SGL instead
#define COLOR_MIN(a, b)                      ((a) < (b) ? (a) : (b))
#define COLOR_MAX(a, b)                      ((a) > (b) ? (a) : (b))

Uint16 ColorHelpers_PackRGB(ObjectColor *color)
{
    return (color->b >> 3) | ((color->g >> 2) << 5) | ((color->r >> 3) << 11);
}

void ColorHelpers_RGBToHSL(ObjectColor *color, ObjectHSL *hsl)
{
    if (!color->r && !color->g && !color->b) {
        if (hsl) {
            hsl->h = 0;
            hsl->s = 0;
            hsl->l = 0;
        }
        return;
    }

    Uint8 min = COLOR_MIN(COLOR_MIN(color->r, color->g), color->b);
    Uint8 max = COLOR_MAX(COLOR_MAX(color->r, color->g), color->b);

    Sint16 chroma = max - min;
    if (max) {
        if (max == min) {
            if (hsl) {
                hsl->h = 0;
                hsl->s = 0;
                hsl->l = min;
            }
        } else {
            if (hsl) {
                Sint16 h = 0;

                if (color->r == max)
                    h = 60 * (Sint16)(color->g - color->b) / chroma;
                else if (color->g == max)
                    h = 60 * (Sint16)(color->b - color->r) / chroma + 120;
                else
                    h = 60 * (Sint16)(color->r - color->g) / chroma + 240;

                if (h < 0)
                    h += 360;

                hsl->h = h;
                hsl->s = 255 * chroma / max;
                hsl->l = max;
            }
        }
    }
}

void ColorHelpers_HSLToRGB(ObjectHSL *hsl, ObjectColor *color)
{
    Uint32 green = 0, red = 0, blue = 0;

    // Clamp saturation and luminance to the 0-255 range for calculation - 8/24/2024
    Sint16 s_clamped = hsl->s < 0 ? 0 : (hsl->s > 255 ? 255 : hsl->s);
    Sint16 l_clamped = hsl->l < 0 ? 0 : (hsl->l > 255 ? 255 : hsl->l);

    if (s_clamped) {
        Sint16 s = l_clamped * s_clamped / 255;
        Sint16 h_mod = hsl->h % 60;  // Compute modulus once
        Sint16 s_times_mod = s * h_mod / 60;  // Precompute this part
        
        Sint16 p = l_clamped - s;
        Sint16 q = l_clamped - s_times_mod;
        Sint16 t = p + s_times_mod;  // Use the precomputed term for `t`

        switch (hsl->h / 60) {
            case 0:
                red   = l_clamped;
                green = t;
                blue  = p;
                break;

            case 1:
                red   = q;
                green = l_clamped;
                blue  = p;
                break;

            case 2:
                red   = p;
                green = l_clamped;
                blue  = t;
                break;

            case 3:
                red   = p;
                green = q;
                blue  = l_clamped;
                break;

            case 4:
                red   = t;
                green = p;
                blue  = l_clamped;
                break;

            case 5:
            default:
                red   = l_clamped;
                green = p;
                blue  = q;
                break;
        }
    } else {
        red   = l_clamped;
        green = l_clamped;
        blue  = l_clamped;
    }
        color->r = red;  // we never pass a null pointer here, so get rid of condition check
        color->g = green;
        color->b = blue;
}


