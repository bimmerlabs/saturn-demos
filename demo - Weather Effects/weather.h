#ifndef WEATHER_H
#define WEATHER_H

#include <jo/jo.h>

extern int snow_color1;
extern int snow_color2;
extern int snow_color3;
extern int snow_color4;
extern int snow_color5;
extern int snow_color6;

void animate_palette(jo_palette *palette, int *frame, bool *direction, int *animation, int total_frames, int color, int pixels, int framerate);
void update_color(int *color, bool *color_direction, int framerate, int max, int min);
void initialize_snow(jo_palette *palette);
void draw_snow(jo_palette *palette, int scrollx);

#endif // WEATHER_H