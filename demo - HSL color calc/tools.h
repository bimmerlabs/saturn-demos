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
    Sint32 s;
    Sint32 l;
} ObjectHSL;

typedef struct {
    Sint32 h;
    Sint32 s;
    Sint32 l;
} GlobalHSL;

extern Bool do_update;

// Function prototypes
void clamp_hue_saturation_luminance(ObjectHSL *hsl);
void update_colors(ObjectHSL *hsl, GlobalHSL *hsl_increment, ObjectColor *color);

#endif // TOOLS_H
