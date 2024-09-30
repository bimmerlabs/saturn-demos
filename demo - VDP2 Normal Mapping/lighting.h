#ifndef LIGHTING_H
#define LIGHTING_H

#include <jo/jo.h>
#include "palettetools.h"
#include "math.h"

#define ARC_CENTER_X 127
#define ARC_CENTER_Z 255
#define ARC_RADIUS_XY_SQ 16129
#define ARC_RADIUS_Z_SQ 65025

#define FIXED_SQ(x) ((x) * (x) / JO_FIXED_1)

typedef struct {
    FIXED  x; // east / west
    FIXED  y; // north / south
    FIXED  z; // up / down
    Uint8  ambient;
    Sint8  intensity;
    Uint16 hue;
} LightSource;

extern LightSource light1;
extern LightSource light2;
extern LightSource light3;

void light_position_arc_fixed(LightSource *_light); // experimental

void light_position_ellipse_fixed(LightSource *_light); // experimental
void light_position_ellipse_float(LightSource *_light);

void InitNormal2d(HslPalette *hslPal, RgbPalette *rgbPal, LightSource *_light, PaletteRange *range, ImageAttr *attr);
void NormalMapLighting2d(HslPalette *hslPal, RgbPalette *rgbPal, RgbBuff *bufferPal, LightSource *_light, PaletteRange *range, GlobalHSL *hsl_increment);
void InitNormal3d(HslPalette *hslPal, RgbPalette *rgbPal, LightSource *_light, PaletteRange *range, ImageAttr *attr);
void NormalMapLighting3d(HslPalette *hslPal, RgbPalette *rgbPal, RgbBuff *bufferPal, LightSource *_light, PaletteRange *range, GlobalHSL *hsl_increment);

#endif // LIGHTING_H