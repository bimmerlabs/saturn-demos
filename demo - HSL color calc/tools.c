#include <jo/jo.h>
#include "ColorHelpers.h"

Bool do_update = false;

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

void update_colors(ObjectHSL *hsl, ObjectColor *color) {
        clamp_hue_saturation_luminance(hsl);
	ColorHelpers_HSLToRGB(hsl, color);
	do_update = false;
}