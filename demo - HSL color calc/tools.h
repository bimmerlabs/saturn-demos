#ifndef TOOLS_H
#define TOOLS_H

#include <jo/jo.h>

// Struct definitions
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

// Function prototypes
void clamp_hue_saturation_luminance(ObjectHSL *hsl);

#endif // TOOLS_H
