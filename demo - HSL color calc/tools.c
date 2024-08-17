#include <jo/jo.h>

typedef struct {
    Uint8 r;
    Uint8 g;
    Uint8 b;
} ObjectColor;

typedef struct {
    Sint32 h;
    Uint32 s;
    Uint32 l;
} ObjectHSL;

void clamp_hue_saturation_luminance(ObjectHSL *hsl)
{
    if (hsl->h >= 360)
        hsl->h = hsl->h - 360;
        
    if (hsl->h < 0)
        hsl->h = 360 + hsl->h;

    if (hsl->s > 255)
        hsl->s = 255;

    if (hsl->l > 255)
        hsl->l = 255;
}