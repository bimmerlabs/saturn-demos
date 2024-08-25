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

static jo_palette palette1;
static float scroll = 0.0;

static Bool by_index_group = true;
static Uint8 group_id = 0;
static Uint8 index = 0;
PaletteRange range = {0, NUM_PALETTE_ENTRIES};

GlobalHSL hsl_increment = {0, 0, 0};
ImgAttributes img_attr = {0, 0, 0, 0};
DemoOptions options = {false, true, true, false, true, false, false};
void my_draw(void)
{
    jo_clear_screen();
    // jo_sprite_draw3D(0, 0, 0, 500);
    jo_printf(1, 1, "Palette Group: %i", group_id);
    jo_printf(1, 2, "Palette Index: %i - %i", range.lower, range.upper);
    jo_printf(1, 3, "Color: r=%d, g=%d, b=%d", rgbPal.rgb0[index].r, rgbPal.rgb0[index].g, rgbPal.rgb0[index].b);
    jo_printf(1, 4, "HSL:   h=%i, s=%i, l=%i", hslPal.hsl0[index].h, hslPal.hsl0[index].s, hslPal.hsl0[index].l);
    jo_printf(1, 5, "Jo_Color: %i", JO_COLOR_RGB(rgbPal.rgb0[index].r, rgbPal.rgb0[index].g, rgbPal.rgb0[index].b));
    jo_printf(1, 6, "Jo_Red:   %x", JO_COLOR_SATURN_GET_R(JO_COLOR_RGB(rgbPal.rgb0[index].r, rgbPal.rgb0[index].g, rgbPal.rgb0[index].b)));
    jo_printf(1, 7, "Jo_Green: %x", JO_COLOR_SATURN_GET_G(JO_COLOR_RGB(rgbPal.rgb0[index].r, rgbPal.rgb0[index].g, rgbPal.rgb0[index].b)));
    jo_printf(1, 8, "Jo_Blue:  %x", JO_COLOR_SATURN_GET_B(JO_COLOR_RGB(rgbPal.rgb0[index].r, rgbPal.rgb0[index].g, rgbPal.rgb0[index].b)));
    jo_printf(1, 9, "min_sat_id: %i %i", img_attr.min_sat_id, hslPal.hsl0[img_attr.min_sat_id].s);
    jo_printf(1, 10, "max_sat_id: %i %i", img_attr.max_sat_id, hslPal.hsl0[img_attr.max_sat_id].s);
    jo_printf(1, 11, "min_lum_id: %i %i", img_attr.min_lum_id, hslPal.hsl0[img_attr.min_lum_id].l);
    jo_printf(1, 12, "max_lum_id: %i %i", img_attr.max_lum_id, hslPal.hsl0[img_attr.max_lum_id].l);
    jo_printf(1, 13, "by_index_group: %i", by_index_group);
    
    slScrPosNbg1(toFIXED(scroll), toFIXED(0.0));
    scroll += 0.5;
    if (scroll == 512.0)
        scroll = 0;
}

void my_input(void)
{

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
        hsl_increment.h += 1;
        do_update = true;
    }
    else if (jo_is_pad1_key_pressed(JO_KEY_X)) {
        hsl_increment.h -= 1;
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

// reset
    if (jo_is_pad1_key_down(JO_KEY_START)) {
	MultiHslTorRgb(&hslPal, &originalPal, &range);
        min_max_sl_id(&hslPal, &range, &img_attr);
	MultiPaletteUpdate(&bg_palette, &rgbPal, &hslPal, &hsl_increment, &range);
        do_update = false;
    }

// update RGB
    if (do_update) {
        MultiPaletteUpdate(&bg_palette, &rgbPal, &hslPal, &hsl_increment, &range);
	hsl_increment.h = 0;
	hsl_increment.s = 0;
	hsl_increment.l = 0;
    }}

jo_palette      *my_sprite_palette_handling(void)
{
    jo_create_palette(&palette1);
    return (&palette1);
}
void                init_graphics(void) {
    // SPRITE
    // jo_set_tga_palette_handling(my_sprite_palette_handling);
    // jo_sprite_add_tga("TEX", "POPPY8.TGA", 5); // use 5 for transparent background color
    // jo_sprite_set_palette(palette1.id);
    
    init_background();
    jo_move_background(80, 0);
        // init palette array
    MultiRgbToHsl(&hslPal, &rgbPal, &range);
    min_max_sl_id(&hslPal, &range, &img_attr);
}

void			jo_main(void)
{
	jo_core_init(JO_COLOR_Black);

	init_graphics();
	
	jo_core_add_callback(my_input);
	jo_core_add_callback(my_draw);
	jo_core_run();
}

/*
** END OF FILE
*/
