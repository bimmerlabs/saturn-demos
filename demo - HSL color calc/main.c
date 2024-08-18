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
#include "bg8.h"

static jo_palette palette1;
static jo_palette palette2;
static int index = 0;
GlobalHSL hsl_increment = {0, 0, 0};
void my_draw(void)
{
    jo_clear_screen();
    jo_sprite_draw3D(0, 0, 0, 500);
    
    jo_printf(1, 1, "Palette Index: %i", index);
    jo_printf(1, 2, "Color: r=%d, g=%d, b=%d", rgbPal.rgb0[index].r, rgbPal.rgb0[index].g, rgbPal.rgb0[index].b);
    jo_printf(1, 3, "HSL:   h=%i, s=%i, l=%i", hslPal.hsl0[index].h, hslPal.hsl0[index].s, hslPal.hsl0[index].l);
    jo_printf(1, 4, "Jo_Color = %i", JO_COLOR_RGB(rgbPal.rgb0[index].r, rgbPal.rgb0[index].g, rgbPal.rgb0[index].b));
    jo_printf(1, 5, "Jo_Red   = %x", JO_COLOR_SATURN_GET_R(JO_COLOR_RGB(rgbPal.rgb0[index].r, rgbPal.rgb0[index].g, rgbPal.rgb0[index].b)));
    jo_printf(1, 6, "Jo_Green = %x", JO_COLOR_SATURN_GET_G(JO_COLOR_RGB(rgbPal.rgb0[index].r, rgbPal.rgb0[index].g, rgbPal.rgb0[index].b)));
    jo_printf(1, 7, "Jo_Blue  = %x", JO_COLOR_SATURN_GET_B(JO_COLOR_RGB(rgbPal.rgb0[index].r, rgbPal.rgb0[index].g, rgbPal.rgb0[index].b)));
    jo_printf(1, 8, "Min L Index: %i", min_lum_idx);
    jo_printf(1, 9, "Max L Index: %i", max_lum_idx);
}

void my_input(void)
{

// hue
    if (jo_is_pad1_key_pressed(JO_KEY_A)) {
        hsl_increment.h += 1;
        do_update = true;
    }
    else if (jo_is_pad1_key_pressed(JO_KEY_X)) {
        hsl_increment.h -= 1;
        do_update = true;
    }
    if (jo_is_pad1_key_down(JO_KEY_R) && index < 15) {
        index++;
        // hsl_increment.h += 90;
        // do_update = true;
    }
    else if (jo_is_pad1_key_down(JO_KEY_L) && index > 0) {
        index--;
        // hsl_increment.h -= 90;
        // do_update = true;
    }	

// saturation
    if (jo_is_pad1_key_pressed(JO_KEY_B)) {
        hsl_increment.s += 1;
        do_update = true;
    }
    else if (jo_is_pad1_key_pressed(JO_KEY_Y)) {
        hsl_increment.s -= 1;
        do_update = true;
    }
    if (jo_is_pad1_key_pressed(JO_KEY_UP)) {
        hsl_increment.s += 5;
        do_update = true;
    }
    else if (jo_is_pad1_key_pressed(JO_KEY_DOWN)) {
        hsl_increment.s -= 5;
        do_update = true;
    }	

// luminance
    if (jo_is_pad1_key_pressed(JO_KEY_C)) {
        hsl_increment.l += 1;
        do_update = true;
    }
    else if (jo_is_pad1_key_pressed(JO_KEY_Z)) {
        hsl_increment.l -= 1;
        do_update = true;
    }
    if (jo_is_pad1_key_pressed(JO_KEY_RIGHT)) {
        hsl_increment.l += 5;
        do_update = true;
    }
    else if (jo_is_pad1_key_pressed(JO_KEY_LEFT)) {
        hsl_increment.l -= 5;
        do_update = true;
    }
    
// update RGB
    if (do_update) {
        MultiPaletteUpdate(&palette2, &rgbPal, &hslPal, &hsl_increment);
	hsl_increment.h = 0;
	hsl_increment.s = 0;
	hsl_increment.l = 0;
    }

// reset
    if (jo_is_pad1_key_down(JO_KEY_START)) {
	reset_palette(&rgbPal, &originalPal);
	MultiHslTorRgb(&hslPal, &rgbPal);
	MultiPaletteUpdate(&palette2, &rgbPal, &hslPal, &hsl_increment);
    }
}

jo_palette      *my_sprite_palette_handling(void)
{
    jo_create_palette(&palette1);
    return (&palette1);
}

jo_palette	*my_bg_palette_handling(void)
{
    jo_create_palette(&palette2);
    return (&palette2);
}

void                init_graphics(void) {
    // SPRITE
    jo_set_tga_palette_handling(my_sprite_palette_handling);
    jo_sprite_add_tga("TEX", "POPPY8.TGA", 5); // use 5 for transparent background color
    jo_sprite_set_palette(palette1.id);

    // BACKGROUND
    jo_img_8bits    img;
    jo_set_tga_palette_handling(my_bg_palette_handling);
    img.data = JO_NULL;
    jo_tga_8bits_loader(&img, "TEX", "BG8.TGA", 0);
    jo_vdp2_set_nbg1_8bits_image(&img, palette2.id, false);
    jo_free_img(&img);

    // init palette array
    MultiRgbToHsl(&hslPal, &rgbPal);
    min_max_lum_idx(&hslPal);
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
