#include <jo/jo.h>#include "weather.h"

#define PALETTE_ENTRIES (28)
#define FRAMES1 14
#define FRAMES2 7
#define FRAMERATE 5 // lower number = higher frame rate

jo_fixed		    snowx;
jo_fixed		    snowy;
// probably could be cleaned up a bit, but it works...
static int snowspeed   = 1;
static int frame_counter = 0;
static int color_counter = 0;
static int snow_frame1 = 13;
static int snow_frame2 = 4;
static bool snow_direction1 = true;
static bool snow_direction2 = false;
static bool color_direction1 = true;
static bool color_direction2 = true;
int snow_color1 = 0;
int snow_color2 = 15;

// list of palette indexes read from .tga file
static int snow_animation1[FRAMES1] = {6, 12, 17, 1, 20, 16, 10, 8, 5, 9, 13, 21, 11, 14};
static int snow_animation2[FRAMES2] = {15, 19, 7, 4, 2, 3, 18};
// palette animation loopvoid    animate_palette(jo_palette *palette, int *frame, bool *direction, int *animation, int total_frames, int color, int pixels)	{
    if (frame_counter % FRAMERATE == 0) {
        for (int i = 0; i < total_frames; i++) {
        	palette->data[animation[i]] 		= JO_COLOR_RGB(0, 0, 0);
		if (i == *frame) {
			palette->data[animation[i]]	= JO_COLOR_RGB(color, color, color);
			if (*frame < total_frames && *frame > 0 && pixels > 1) {
				palette->data[animation[i - 1]]	= JO_COLOR_RGB(color, color, color);
			}
		}
        }
       // Update the frame based on direction
       if (*direction) { 
		(*frame)++;
		if (*frame >= total_frames - 1) {
		    *direction = false;
		}
       } 
       else { 
		(*frame)--;
		if (*frame <= 0) {
		    *direction = true;
		}
       }
    }
    frame_counter++;
    if (frame_counter % 60 == 0) {
        // Reset frame_counter to 0 after every 60 frames
        frame_counter = 0;
    }
}

// cycle colors to fade snow in/out
void    update_color(int *color, bool *color_direction, int framerate, int max, int min)	{
    if (color_counter % framerate == 0) {
       // Update the color based on direction
       if (*color_direction) { 
		(*color)++;
		if (*color > max) {
		    *color_direction = false;
		    *color = max;
		}
       } 
       else { 
		(*color)--;
		if (*color < min) {
		    *color_direction = true;
		    *color = min;
		}
       }
    }
    color_counter++;
    if (color_counter % 60 == 0) {
        // Reset frame_counter to 0 after every 60 frames
        color_counter = 0;
    }
}

// set snow to black (since we're using CC_ADD)
void    initialize_snow(jo_palette *palette)    {
    int i;
    for (i = 1; i < PALETTE_ENTRIES; i++) {
    		palette->data[i]  = JO_COLOR_RGB(0,  0,  0);
    }
}

// main snow drawing loop
void    draw_snow (jo_palette *palette, int scrollx) {
    snowx += jo_int2fixed(snowspeed);
    snowy -= jo_int2fixed(snowspeed);
    slScrPosNbg0((snowx) + (scrollx / 4), snowy);
    animate_palette(palette, &snow_frame1, &snow_direction1, snow_animation1, FRAMES1, snow_color1, 2);
    animate_palette(palette, &snow_frame2, &snow_direction2, snow_animation2, FRAMES2, snow_color2, 1);
    update_color(&snow_color1, &color_direction1, 8, 255, 0);
    update_color(&snow_color2, &color_direction2, 9, 255, 10);
}