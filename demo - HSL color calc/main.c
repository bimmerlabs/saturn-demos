/*
** Jo Sega Saturn Engine
** Copyright (c) 2012-2020, Johannes Fetz (johannesfetz@gmail.com)
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of the Johannes Fetz nor the
**       names of its contributors may be used to endorse or promote products
**       derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL Johannes Fetz BE LIABLE FOR ANY
** DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <jo/jo.h>
#include "palettetools.h"
#include "ColorHelpers.h"
#include "background.h"

#define LWRAM 0x00200000 // start of LWRAM memory. Doesn't appear to be used
#define LWRAM_HEAP_SIZE 0x100000 // number of bytes to extend heap by
static jo_palette light_source;
FIXED scroll = toFIXED(0.0);

static Bool by_index_group = true;
static Uint8 group_id = 0;
static Uint8 index = 0;
PaletteRange range = {0, NUM_PALETTE_ENTRIES};

GlobalHSL hsl_increment = {0, 0, 0};
ImgAttributes img_attr = {0, 0, 0, 0};

LightSource light = {186, 87, 255};
void my_draw(void)
{    
    jo_clear_screen();
    
    ObjectColor rgb_color;
    ColorHelpers_HSLToRGB(&hslPal.hsl0[index], &rgb_color);
        if (NORMAL_MAP_MODE) {
        // this isn't really correct - yet
        // the light position actually doesn't have anything to do with the lighting model
        // it's also affected by the scale of the image
        // also it can be backwards (and the inputs reversed) depending on the orientation of the normal map (updated to be more 'normal' orientation)
        jo_sprite_draw3D(0, 2*(light.x-127), -2*(light.y-127)-16, 500);
        jo_printf(1, 1, "NORMAL MAP DEMO");
        jo_printf(1, 2, "Color: r=%3i, g=%3i, b=%3i", rgb_color.r, rgb_color.g, rgb_color.b);
        jo_printf(1, 3, "HSL:   h=%3i, s=%3i, l=%3i", hslPal.hsl0[index].h, hslPal.hsl0[index].s, hslPal.hsl0[index].l);
        jo_printf(1, 4, "light: x=%3i, y=%3i, z=%3i", light.x, light.y, light.z);
    }
    else {
        jo_printf(1, 1, "HSL COLOR CALC DEMO");
        jo_printf(1, 2, "by Index or Group: %i", by_index_group);
        jo_printf(1, 3, "Palette Group: %i", group_id);
        if (by_index_group)
            jo_printf(1, 4, "Palette Index: %i - %i", range.lower, range.upper);
        else
            jo_printf(1, 4, "Palette Index: %i / %i", range.lower+1, NUM_PALETTE_ENTRIES+1);
        jo_printf(1, 5, "min/max saturation: %3i %3i", hslPal.hsl0[img_attr.min_sat_id].s, hslPal.hsl0[img_attr.max_sat_id].s);
        jo_printf(1, 6, "min/max luminance:  %3i %3i", hslPal.hsl0[img_attr.min_lum_id].l, hslPal.hsl0[img_attr.max_lum_id].l);
        jo_printf(1, 7, "Color: r=%3i, g=%3i, b=%3i", rgb_color.r, rgb_color.g, rgb_color.b);
        jo_printf(1, 8, "HSL:   h=%3i, s=%3i, l=%3i", hslPal.hsl0[index].h, hslPal.hsl0[index].s, hslPal.hsl0[index].l);
    }
    if (image.scroll_rate > toFIXED(0)) {
        slScrPosNbg1(scroll, image.y_pos);
        scroll += image.scroll_rate;
        if (scroll > toFIXED(512.0))
            scroll = toFIXED(0);
    }
    
}

void my_input(void)
{
    if (NORMAL_MAP_MODE) {
        // light intensity
        if (jo_is_pad1_key_pressed(JO_KEY_R) && light.z < 255) {
            light.z += 1;
            do_update = true;
        }
        if (jo_is_pad1_key_pressed(JO_KEY_L) && light.z > 0) {
            light.z -= 1;
            do_update = true;
        }
        // light hue
        if (jo_is_pad1_key_pressed(JO_KEY_A)) {
            hsl_increment.h -= 1;
            do_update = true;
        }
        else if (jo_is_pad1_key_pressed(JO_KEY_X)) {
            hsl_increment.h += 1;
            do_update = true;
        }
        // saturation
        if (jo_is_pad1_key_pressed(JO_KEY_B) && hslPal.hsl0[img_attr.max_sat_id].s > 0) {
            hsl_increment.s -= 1;
            do_update = true;
        }
        else if (jo_is_pad1_key_pressed(JO_KEY_Y) && hslPal.hsl0[img_attr.min_sat_id].s < 255) {
            hsl_increment.s += 1;
            do_update = true;
        }
        // move light
        // up / down are reversed on the coin demo because the Y axis of the normal map is upside down
        // on a normal map where the X/Y axis is starts at the lower left, this should be switched around
        if (jo_is_pad1_key_pressed(JO_KEY_UP) && light.y < 255) {
            light.y += 1;
            do_update = true;
        }
        else if (jo_is_pad1_key_pressed(JO_KEY_DOWN) && light.y > 0) {
            light.y -= 1;
            do_update = true;
        }	
        if (jo_is_pad1_key_pressed(JO_KEY_RIGHT)&& light.x < 255) {
            light.x += 1;
            do_update = true;
        }
        else if (jo_is_pad1_key_pressed(JO_KEY_LEFT)&& light.x > 0) {
            light.x -= 1;
            do_update = true;
        }
        // darkness
        if (jo_is_pad1_key_pressed(JO_KEY_C) && image.darkness > 0) {
            image.darkness -= 1;
            do_update = true;
        }
        else if (jo_is_pad1_key_pressed(JO_KEY_Z) && image.darkness < 255) {
            image.darkness += 1;
            do_update = true;
        }
        // reset
        if (jo_is_pad1_key_down(JO_KEY_START)) {
            MultiHslTorRgb(&hslPal, &rgbPal, &range);
            InitNormalImage(&hslPal, &range, &image);
            light.z = 255;
            normal_lighting(&hslPal, &rgbPal, &light, &range, &image);
            MultiPaletteUpdate(&bg_palette, &hslPal, &hsl_increment, &range);
            do_update = false;
        }
    }
    else {
        // palette index / group
        if (jo_is_pad1_key_down(JO_KEY_R)) {
            if (by_index_group) {
                group_id++;
                if (group_id > NUM_PALETTE_GROUPS-1) {
                    group_id = 0;
                }           
                range.lower = p_collection.group[group_id].lower;
                range.upper = p_collection.group[group_id].upper;
                index = p_collection.group[group_id].index;
                min_max_sl_id(&hslPal, &range, &img_attr);
            }
            else {
                index++;
                if (index > NUM_PALETTE_ENTRIES) {
                    index = 0;
                }
                range.lower = index;
                range.upper = index;
                min_max_sl_id(&hslPal, &range, &img_attr);
            }
        }
        if (jo_is_pad1_key_down(JO_KEY_L)) {
            if (by_index_group) {
                by_index_group = false;
                group_id = 0;
                range.lower = 0;
                range.upper = 0;
                min_max_sl_id(&hslPal, &range, &img_attr);
            }
            else {
                by_index_group = true;
                index = 0;
                group_id = 0;
                range.lower = 0;
                range.upper = NUM_PALETTE_ENTRIES;
                min_max_sl_id(&hslPal, &range, &img_attr);
            }
        }
        // hue
        if (jo_is_pad1_key_pressed(JO_KEY_A)) {
            hsl_increment.h -= 1;
            do_update = true;
        }
        else if (jo_is_pad1_key_pressed(JO_KEY_X)) {
            hsl_increment.h += 1;
            do_update = true;
        }
        // saturation
        if (jo_is_pad1_key_pressed(JO_KEY_B) && hslPal.hsl0[img_attr.max_sat_id].s > 0) {
            hsl_increment.s -= 1;
            do_update = true;
        }
        else if (jo_is_pad1_key_pressed(JO_KEY_Y) && hslPal.hsl0[img_attr.min_sat_id].s < 255) {
            hsl_increment.s += 1;
            do_update = true;
        }
        if (jo_is_pad1_key_pressed(JO_KEY_UP) && hslPal.hsl0[img_attr.min_sat_id].s < 255) {
            hsl_increment.s += 5;
            do_update = true;
        }
        else if (jo_is_pad1_key_pressed(JO_KEY_DOWN) && hslPal.hsl0[img_attr.max_sat_id].s > 0) {
            hsl_increment.s -= 5;
            do_update = true;
        }	
        // luminance
        if (jo_is_pad1_key_pressed(JO_KEY_C) && hslPal.hsl0[img_attr.max_lum_id].l > 0) {
            hsl_increment.l -= 1;
            do_update = true;
        }
        else if (jo_is_pad1_key_pressed(JO_KEY_Z) && hslPal.hsl0[img_attr.min_lum_id].l < 255) {
            hsl_increment.l += 1;
            do_update = true;
        }
        if (jo_is_pad1_key_pressed(JO_KEY_RIGHT) && hslPal.hsl0[img_attr.min_lum_id].l < 255) {
            hsl_increment.l += 5;
            do_update = true;
        }
        else if (jo_is_pad1_key_pressed(JO_KEY_LEFT) && hslPal.hsl0[img_attr.max_lum_id].l > 0) {
            hsl_increment.l -= 5;
            do_update = true;
        }
        // reset demo
        if (jo_is_pad1_key_down(JO_KEY_START)) {
            MultiHslTorRgb(&hslPal, &rgbPal, &range);
            min_max_sl_id(&hslPal, &range, &img_attr);
            MultiPaletteUpdate(&bg_palette, &hslPal, &hsl_increment, &range);
            do_update = false;
        }
    }
}

void my_color_calc(void)
{
    if (do_update) {
        if (NORMAL_MAP_MODE) {
            MultiLuminanceSet(&hslPal, &range, &image);
            normal_lighting(&hslPal, &rgbPal, &light, &range, &image);
        }
        MultiPaletteUpdate(&bg_palette, &hslPal, &hsl_increment, &range);
	hsl_increment.h = 0;
	hsl_increment.s = 0;
	hsl_increment.l = 0;
    }}

jo_palette      *my_sprite_palette_handling(void)
{
    jo_create_palette(&light_source);
    return (&light_source);
}
void                init_graphics(void) {
    init_background();
    // load palettes into data structures
    MultiRgbToHsl(&hslPal, &rgbPal, &range);
    if (NORMAL_MAP_MODE) {
        // light (completely fake, it's only here for visual effect)
        jo_set_tga_palette_handling(my_sprite_palette_handling);
        jo_sprite_add_tga("TEX", "LIGHT.TGA", 1); // use 5 for transparent background color
        jo_sprite_set_palette(light_source.id);
        
        jo_core_set_screens_order(JO_NBG1_SCREEN, JO_SPRITE_SCREEN);
        slColorCalc(CC_ADD | CC_TOP| JO_NBG1_SCREEN);
        slColorCalcOn(JO_NBG1_SCREEN);

        // normal lighting
        InitNormalImage(&hslPal, &range, &image);
        normal_lighting(&hslPal, &rgbPal, &light, &range, &image);
    }
    // set initial image colors
    MultiPaletteUpdate(&bg_palette, &hslPal, &hsl_increment, &range);
}

void			jo_main(void)
{
        // increase the default heap size. LWRAM is not being used (not really needed for this demo, I did use it for some larger backgrounds)
        jo_add_memory_zone((unsigned char *)LWRAM, LWRAM_HEAP_SIZE);
        
	jo_core_init(JO_COLOR_Black);
        jo_core_tv_off();
	init_graphics();
        jo_core_tv_on();
	jo_core_add_callback(my_input);
	jo_core_add_callback(my_color_calc);
	jo_core_add_callback(my_draw);
	jo_core_run();
}

/*
** END OF FILE
*/
