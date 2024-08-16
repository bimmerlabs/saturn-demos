#ifndef OBJ_COLORHELPERS_H
#define OBJ_COLORHELPERS_H

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

// Extra Entity Functions
uint16 ColorHelpers_PackRGB(ObjectColor color);

void ColorHelpers_RGBToHSL(ObjectColor color, ObjectHSL *hsl);
void ColorHelpers_HSLToRGB(ObjectHSL hsl, ObjectColor *color);

#endif //! OBJ_COLORHELPERS_H
