#ifndef LIGHTING_H
#define LIGHTING_H

#include <jo/jo.h>
#include "palettetools.h"
#include "math.h"

#define ARC_CENTER_X 127
#define ARC_RADIUS_XY_SQ 16129
#define ARC_RADIUS_Z_SQ 65025

typedef struct {
    FIXED  x; // east / west
    FIXED  y; // north / south
    FIXED  z; // up / down
    Uint8  ambient;
    Sint8  intensity;
    Uint16 hue;
} LightSource;

extern LightSource light;

void light_position_ellipse_fixed(LightSource *_light);
void light_position_ellipse_float(LightSource *_light);

void normal_init_2d(HslPalette *hslPal, RgbPalette *rgbPal, LightSource *_light, PaletteRange *range);
void NormalMapLighting2d(HslPalette *hslPal, RgbPalette *rgbPal, RgbBuff *bufferPal, LightSource *_light, PaletteRange *range, GlobalHSL *hsl_increment);
void normal_init_3d(HslPalette *hslPal, RgbPalette *rgbPal, LightSource *_light, PaletteRange *range);
void NormalMapLighting3d(HslPalette *hslPal, RgbPalette *rgbPal, RgbBuff *bufferPal, LightSource *_light, PaletteRange *range, GlobalHSL *hsl_increment);

#endif // LIGHTING_H