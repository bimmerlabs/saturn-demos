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
#include "ColorHelpers.h"

static jo_palette palette;

// Example color (pure blue)
ObjectColor input_color;
ObjectHSL hsl;

void my_draw(void)
{
    jo_clear_screen();

    // update palette index with our new RGB values
    palette.data[4] = JO_COLOR_RGB(input_color.r, input_color.g, input_color.b);
    jo_sprite_set_palette(palette.id);
    jo_sprite_draw3D(0, 0, 0, 500);
    
    // Print result
    jo_printf(1, 1, "Color: r=%d, g=%d, b=%d", input_color.r, input_color.g, input_color.b);
    jo_printf(1, 2, "HSL:   h=%i, s=%i, l=%i" , hsl.h, hsl.s, hsl.l);
    jo_printf(1, 4, "Jo_Color = %i", JO_COLOR_RGB(input_color.r, input_color.g, input_color.b));
    jo_printf(1, 5, "Jo_Red   = %x", JO_COLOR_SATURN_GET_R(JO_COLOR_RGB(input_color.r, input_color.g, input_color.b)));
    jo_printf(1, 6, "Jo_Green = %x", JO_COLOR_SATURN_GET_G(JO_COLOR_RGB(input_color.r, input_color.g, input_color.b)));
    jo_printf(1, 7, "Jo_Blue  = %x", JO_COLOR_SATURN_GET_B(JO_COLOR_RGB(input_color.r, input_color.g, input_color.b)));
}

void clamp_hue_saturation_luminance(void)
{
    if (hsl.h >= 360)
        hsl.h = 0;
        
    if (hsl.h < 0)
        hsl.h = 360 + hsl.h;

    if (hsl.s > 255)
        hsl.s = 255;

    if (hsl.l > 255)
        hsl.l = 255;
}

void my_input(void)
{

// hue
    if (jo_is_pad1_key_pressed(JO_KEY_A)) {
        hsl.h += 1;
        clamp_hue_saturation_luminance();
	ColorHelpers_HSLToRGB(hsl, &input_color);
    }
    else if (jo_is_pad1_key_pressed(JO_KEY_X)) {
        hsl.h -= 1;
        clamp_hue_saturation_luminance();
	ColorHelpers_HSLToRGB(hsl, &input_color);
    }
    if (jo_is_pad1_key_down(JO_KEY_R)) {
        hsl.h += 10;
        clamp_hue_saturation_luminance();
	ColorHelpers_HSLToRGB(hsl, &input_color);
    }
    else if (jo_is_pad1_key_down(JO_KEY_L)) {
        hsl.h -= 10;
        clamp_hue_saturation_luminance();
	ColorHelpers_HSLToRGB(hsl, &input_color);
    }	

// saturation
    if (jo_is_pad1_key_pressed(JO_KEY_B)) {
        hsl.s += 1;
        clamp_hue_saturation_luminance();
	ColorHelpers_HSLToRGB(hsl, &input_color);
    }
    else if (jo_is_pad1_key_pressed(JO_KEY_Y) && hsl.s > 0) {
        hsl.s -= 1;
        clamp_hue_saturation_luminance();
	ColorHelpers_HSLToRGB(hsl, &input_color);
    }
    if (jo_is_pad1_key_down(JO_KEY_UP)) {
        hsl.s = 255;
	ColorHelpers_HSLToRGB(hsl, &input_color);
    }
    else if (jo_is_pad1_key_down(JO_KEY_DOWN) && hsl.s > 0) {
        hsl.s = 0;
	ColorHelpers_HSLToRGB(hsl, &input_color);
    }	

// luminance
    if (jo_is_pad1_key_pressed(JO_KEY_C)) {
        hsl.l += 1;
        clamp_hue_saturation_luminance();
	ColorHelpers_HSLToRGB(hsl, &input_color);
    }
    else if (jo_is_pad1_key_pressed(JO_KEY_Z) && hsl.l > 0) {
        hsl.l -= 1;
        clamp_hue_saturation_luminance();
	ColorHelpers_HSLToRGB(hsl, &input_color);
    }
    if (jo_is_pad1_key_down(JO_KEY_RIGHT)) {
        hsl.l = 255;
	ColorHelpers_HSLToRGB(hsl, &input_color);
    }
    else if (jo_is_pad1_key_down(JO_KEY_LEFT) && hsl.l > 0) {
        hsl.l = 0;
	ColorHelpers_HSLToRGB(hsl, &input_color);
    }

// reset
    if (jo_is_pad1_key_down(JO_KEY_START)) {
	input_color.r = 0;
        input_color.g = 0;
        input_color.b = 255;
	ColorHelpers_RGBToHSL(input_color, &hsl);
    }
}

jo_palette      *my_tga_palette_handling(void)
{
    jo_create_palette(&palette);
    return (&palette);
}

void			jo_main(void)
{
	jo_core_init(JO_COLOR_Blue);

	jo_set_tga_palette_handling(my_tga_palette_handling);
	jo_sprite_add_tga("TEX", "POPPY8.TGA", 0);
	// initialize HSL
	input_color.r = 0;
        input_color.g = 0;
        input_color.b = 255;
	ColorHelpers_RGBToHSL(input_color, &hsl);
	
	jo_core_add_callback(my_input);
	jo_core_add_callback(my_draw);
	jo_core_run();
}

/*
** END OF FILE
*/
