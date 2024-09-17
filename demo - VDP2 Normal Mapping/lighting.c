#include "lighting.h"

LightSource light = {toFIXED(221), toFIXED(84), toFIXED(148), 0, 0, 0};  // scene light

void light_position_ellipse_fixed(LightSource *_light) {
    // Calculate the deltas from the center of the arc
    Sint16 deltaX = _light->x - ARC_CENTER_X;
    Sint16 deltaY = _light->y - ARC_CENTER_X;
 
    Uint16 deltaX_sq = deltaX * deltaX;
    Uint16 deltaY_sq = deltaY * deltaY;
    
    // Calculate the squared ratios for X and Y
    FIXED x_ratio_squared = (FIXED)(deltaX_sq << 16) / ARC_RADIUS_XY_SQ;
    FIXED y_ratio_squared = (FIXED)(deltaY_sq << 16) / ARC_RADIUS_XY_SQ;
    
    _light->z = (Uint8)jo_sqrt(toFIXED(ARC_RADIUS_Z_SQ) * (JO_FIXED_1 - x_ratio_squared -y_ratio_squared));
}

void light_position_ellipse_float(LightSource *_light) {
    // Calculate the deltas from the center of the arc
    Sint16 deltaX = JO_FIXED_TO_INT(_light->x) - ARC_CENTER_X;
    Sint16 deltaY = JO_FIXED_TO_INT(_light->y) - ARC_CENTER_X;
 
    Uint16 deltaX_sq = deltaX * deltaX;
    Uint16 deltaY_sq = deltaY * deltaY;
    
    // Calculate the squared ratios for X and Y
    Float32 x_ratio_squared = (Float32)(deltaX_sq) / (ARC_RADIUS_XY_SQ);
    Float32 y_ratio_squared = (Float32)(deltaY_sq) / (ARC_RADIUS_XY_SQ);
    
    // Check if the point is within the ellipse
    if (x_ratio_squared + y_ratio_squared <= 1.0f) {
        // Calculate the Z value based on the ellipsoid equation
        _light->z = toFIXED(jo_sqrt(ARC_RADIUS_Z_SQ * (1.0f - x_ratio_squared - y_ratio_squared)));
    } else {
        // If the point lies outside the ellipse, set Z to 0
        _light->z = JO_FIXED_0;
    }
}

// since VDP2 is basically 2d, there is no need to use the b channel or z distance in the calculation (the normal is always 1)
// only use for initial setup
void normal_init_2d(HslPalette *hslPal, RgbPalette *rgbPal, LightSource *_light, PaletteRange *range) {
    for (int i = range->lower; i <= range->upper; i++) {
        
        // Calculate the difference between the light source XYZ and the palette RGB values
        int diff_r = JO_FIXED_TO_INT(_light->x) - rgbPal->color[i].r;
        int diff_g = JO_FIXED_TO_INT(_light->y) - rgbPal->color[i].g;

        // Calculate the luminance adjustment based on the closeness of the light source to the color
        // For simplicity, let's assume we adjust it based on the Euclidean distance
        Uint32 value = diff_r * diff_r + diff_g * diff_g;
        Sint16 distance = ApproximateIntegerSqrt(value);
        
        hslPal->color[i].l = MAX(0, (255 - distance) + (JO_FIXED_TO_INT(_light->z) - 255)); // this could probably be more efficient
    }
}

// use for real-time adjustments, then update the palette from bufferPal
void NormalMapLighting2d(
    HslPalette *hslPal, RgbPalette *rgbPal, RgbBuff *bufferPal, LightSource *_light, 
    PaletteRange *range, GlobalHSL *hsl_increment) {
    ObjectColor color;
    for (int i = range->lower; i <= range->upper; i++) {
        // Calculate the difference between the light source XYZ and the palette RGB values
        int diff_r = JO_FIXED_TO_INT(_light->x) - rgbPal->color[i].r;
        int diff_g = JO_FIXED_TO_INT(_light->y) - rgbPal->color[i].g;

        // Calculate the luminance adjustment based on the closeness of the light source to the color
        // For simplicity, let's assume we adjust it based on the Euclidean distance
        Uint32 value = diff_r * diff_r + diff_g * diff_g;
        Sint16 distance = ApproximateIntegerSqrt(value);

        hslPal->color[i].l = MAX(0, (255 - distance) + (JO_FIXED_TO_INT(_light->z) - 255));
        
        update_colors(&hslPal->color[i], hsl_increment, &color);
        bufferPal->color[i]  = JO_COLOR_RGB(color.r,  color.g,  color.b);
    }
    hsl_increment->h = 0;
    hsl_increment->s = 0;
    hsl_increment->l = 0;
}

// it is currently unknown if the 3d method is required, since the Saturn doesn't have UV mapping anyway.
// results are the same as the 2d method
// only use for initial setup
void normal_init_3d(HslPalette *hslPal, RgbPalette *rgbPal, LightSource *_light, PaletteRange *range) { 
    for (int i = range->lower; i <= range->upper; i++) {
        
        // Calculate the difference between the light source XYZ and the palette RGB values
        int diff_r = JO_FIXED_TO_INT(_light->x) - rgbPal->color[i].r;
        int diff_g = JO_FIXED_TO_INT(_light->y) - rgbPal->color[i].g;
        int diff_b = JO_FIXED_TO_INT(_light->z) - rgbPal->color[i].b;

        // Calculate the luminance adjustment based on the closeness of the light source to the color
        // For simplicity, let's assume we adjust it based on the Euclidean distance
        Uint32 value = diff_r * diff_r + diff_g * diff_g + diff_b * diff_b;
        Sint16 distance = ApproximateIntegerSqrt(value);

        // Adjust the luminance by the inverse of the distance
        Sint16 luminance = MAX(0, 255 - distance);

        hslPal->color[i].l = luminance;
    }
}
// use for real-time adjustments, then update the palette from bufferPal
void NormalMapLighting3d(
    HslPalette *hslPal, RgbPalette *rgbPal, RgbBuff *bufferPal, LightSource *_light, 
    PaletteRange *range, GlobalHSL *hsl_increment) { 
    ObjectColor color;
    for (int i = range->lower; i <= range->upper; i++) {
        // Calculate the difference between the light source XYZ and the palette RGB values
        int diff_r = JO_FIXED_TO_INT(_light->x) - rgbPal->color[i].r;
        int diff_g = JO_FIXED_TO_INT(_light->y) - rgbPal->color[i].g;
        int diff_b = JO_FIXED_TO_INT(_light->z) - rgbPal->color[i].b;

        // Calculate the luminance adjustment based on the closeness of the light source to the color
        // For simplicity, let's assume we adjust it based on the Euclidean distance
        Uint32 value = diff_r * diff_r + diff_g * diff_g + diff_b * diff_b;
        Sint16 distance = ApproximateIntegerSqrt(value); // @dannyduarte

        // Adjust the luminance by the inverse of the distance
        Sint16 luminance = MAX(0, 255 - distance);

        hslPal->color[i].l = luminance;
        update_colors(&hslPal->color[i], hsl_increment, &color);
        bufferPal->color[i]  = JO_COLOR_RGB(color.r,  color.g,  color.b);
    }
    hsl_increment->h = 0;
    hsl_increment->s = 0;
    hsl_increment->l = 0;
}

