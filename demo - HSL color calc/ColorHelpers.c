// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: ColorHelpers Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// Modified for Saturn by: Hassmaschine
// ---------------------------------------------------------------------

#define COLOR_MIN(a, b)                      ((a) < (b) ? (a) : (b))
#define COLOR_MAX(a, b)                      ((a) > (b) ? (a) : (b))

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed int int32;

typedef struct {
    uint8 r;
    uint8 g;
    uint8 b;
} ObjectColor;

typedef struct {
    int32 h; // Hue
    uint32 s; // Saturation
    uint32 l; // Luminance
} ObjectHSL;

uint16 ColorHelpers_PackRGB(ObjectColor color)
{
    return (color.b >> 3) | ((color.g >> 2) << 5) | ((color.r >> 3) << 11);
}

void ColorHelpers_RGBToHSL(ObjectColor color, ObjectHSL *hsl)
{
    if (!color.r && !color.g && !color.b) {
        if (hsl) {
            hsl->h = 0;
            hsl->s = 0;
            hsl->l = 0;
        }
        return;
    }

    uint8 min = COLOR_MIN(COLOR_MIN(color.r, color.g), color.b);
    uint8 max = COLOR_MAX(COLOR_MAX(color.r, color.g), color.b);

    int32 chroma = max - min;
    if (max) {
        if (max == min) {
            if (hsl) {
                hsl->h = 0;
                hsl->s = 0;
                hsl->l = min;
            }
        } else {
            if (hsl) {
                int32 h = 0;

                if (color.r == max)
                    h = 60 * (int32)(color.g - color.b) / chroma;
                else if (color.g == max)
                    h = 60 * (int32)(color.b - color.r) / chroma + 120;
                else
                    h = 60 * (int32)(color.r - color.g) / chroma + 240;

                if (h < 0)
                    h += 360;

                hsl->h = h;
                hsl->s = 255 * chroma / max;
                hsl->l = max;
            }
        }
    }
}


void ColorHelpers_HSLToRGB(ObjectHSL hsl, ObjectColor *color)
{
    uint32 green = 0, red = 0, blue = 0;

    if (hsl.s) {
        int32 s = hsl.l * hsl.s / 255;

        int32 p = hsl.l - s;
        int32 q = hsl.l - (s * (hsl.h % 60)) / 60;
        int32 t = hsl.l - (s * (60 - hsl.h % 60)) / 60;

        switch (hsl.h / 60) {
            case 0:
                red   = hsl.l;
                green = t;
                blue  = p;
                break;

            case 1:
                red   = q;
                green = hsl.l;
                blue  = p;
                break;

            case 2:
                red   = p;
                green = hsl.l;
                blue  = t;
                break;

            case 3:
                red   = p;
                green = q;
                blue  = hsl.l;
                break;

            case 4:
                red   = t;
                green = p;
                blue  = hsl.l;
                break;

            case 5:
            default:
                red   = hsl.l;
                green = p;
                blue  = q;
                break;
        }
    } else {
        red   = hsl.l;
        green = hsl.l;
        blue  = hsl.l;
    }

    if (color) {
        color->r = red;
        color->g = green;
        color->b = blue;
    }
}


