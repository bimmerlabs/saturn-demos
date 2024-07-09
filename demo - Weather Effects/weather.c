#include <jo/jo.h>#include "weather.h"

#define PALETTE_ENTRIES (66)
#define FRAMES1 14
#define FRAMES2 7
#define FRAMES3 2
#define FRAMERATE 5 // lower number = higher frame rate

jo_fixed		    snowx;
jo_fixed		    snowy;
// probably could be cleaned up a bit, but it works...
static int snowspeed   = 1;
static int frame_counter = 0;
static int snow_frame1 = 13;
static int snow_frame2 = 13;
static int snow_frame3 = 13;
static int snow_frame4 = 13;
static int snow_frame5 = 4;
static int snow_frame6 = 0;
static bool snow_direction1 = true;
static bool snow_direction2 = false;
static bool snow_direction3 = false;
static bool snow_direction4 = false;
static bool snow_direction5 = false;
static bool snow_direction6 = false;
static bool color_direction1 = true;
static bool color_direction2 = true;
static bool color_direction3 = true;
static bool color_direction4 = true;
static bool color_direction5 = true;
static bool color_direction6 = true;
int snow_color1 = 0;
int snow_color2 = 0;
int snow_color3 = 15;
int snow_color4 = 0;
int snow_color5 = 0;
int snow_color6 = 0;

// list of palette indexes read from .tga file
static int snow_2x2px[FRAMES1] = {20, 46, 36, 23, 53, 9, 17, 50, 5, 35, 18, 27, 28, 26};
static int snow_2x2_curved[FRAMES1] = {65, 11, 47, 31, 49, 61, 29, 66, 63, 55, 1, 58, 37, 51};
static int snow_1x1px[FRAMES1] = {12, 19, 52, 44, 62, 34, 16, 14, 15, 10, 32, 60, 39, 41};
static int snow_1x1_curved[FRAMES1] = {8, 30, 43, 59, 56, 6, 48, 4, 24, 25, 38, 42, 21, 57};
static int snow_invert[FRAMES2] = {22, 40, 33, 45, 13, 3, 54};
static int snow_3x3px[FRAMES3] = {2, 7};
// static int snow_animation1[FRAMES1] = {6, 12, 17, 1, 20, 16, 10, 8, 5, 9, 13, 21, 11, 14};
// static int snow_animation2[FRAMES2] = {15, 19, 7, 4, 2, 3, 18};
// palette animation loopvoid    animate_palette(jo_palette *palette, int *frame, bool *direction, int *animation, int total_frames, int color, int pixels, int framerate) {
    if (frame_counter % framerate == 0) {
        for (int i = 0; i < total_frames; i++) {
        	palette->data[animation[i]] 		= JO_COLOR_RGB(0, 0, 0);
		if (i == *frame) {
			palette->data[animation[i]]	= JO_COLOR_RGB(color, color, color);
			if (*frame < total_frames && *frame > 0 && pixels == 2) {
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
}

// cycle colors to fade snow in/out
void    update_color(int *color, bool *color_direction, int framerate, int max, int min)	{
    if (frame_counter % framerate == 0) {
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
    slScrPosNbg0((snowx) + (scrollx / 4), snowy * 1.3);
    animate_palette(palette, &snow_frame1, &snow_direction1, snow_2x2px, FRAMES1, snow_color1, 2, FRAMERATE);
    animate_palette(palette, &snow_frame2, &snow_direction2, snow_2x2_curved, FRAMES1, snow_color2, 2, 7);
    animate_palette(palette, &snow_frame3, &snow_direction3, snow_1x1px, FRAMES1, snow_color3, 1, FRAMERATE);
    animate_palette(palette, &snow_frame4, &snow_direction4, snow_1x1_curved, FRAMES1, snow_color4, 1, FRAMERATE);
    animate_palette(palette, &snow_frame5, &snow_direction5, snow_invert, FRAMES2, snow_color5, 1, FRAMERATE);
    // animate_palette(palette, &snow_frame6, &snow_direction6, snow_3x3px, FRAMES3, snow_color6, 1, 8);
    update_color(&snow_color1, &color_direction1, 10, 200, 0);
    update_color(&snow_color2, &color_direction2, 15, 200, 0);
    update_color(&snow_color3, &color_direction3, 6, 255, 10);
    update_color(&snow_color4, &color_direction4, 7, 127, 10);
    update_color(&snow_color5, &color_direction5, 12, 200, 10);
    // update_color(&snow_color6, &color_direction6, 30, 64, 0);
    
    frame_counter++;
    if (frame_counter % 60 == 0) {
        // Reset frame_counter to 0 after every 60 frames
        frame_counter = 0;
    }
}