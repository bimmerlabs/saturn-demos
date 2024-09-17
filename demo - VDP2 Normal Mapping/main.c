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
#include <jo/vdp2.h>
#include "palettetools.h"
#include "lighting.h"
#include "font.h"
#include "ColorHelpers.h"
#include "background.h"
#include "input.h"

// GROUND
jo_pos3Df	pos1;
jo_rot3Df	rot;
// SKY
jo_pos3Df	pos2;
jo_rot3Df	rot2;

FIXED	scrollx;
static float 	windspeed = 5.0f;
static int	movement_speed = 2;

const FIXED HORIZON = toFIXED(151);
const FIXED LIGHT_SPEED = toFIXED(0.2);

// day / night cycle
static Uint8  sun_sprite;
static Uint8  moon_sprite;
static Uint8  curr_sprite;

jo_palette light_pal;

ImgAttributes ground_attr = {0, 0, 0, 0};

void                my_draw(void)	{
	// light - fake, needs to replaced with a 3D light
	if (draw_light && light.z > HORIZON && light.y < FIXED_127) { // draw the "light" only if it's above the horizon (depends on RGB0 plane angle)
            jo_3d_push_matrix();
            jo_3d_translate_matrix_fixed(-4*(light.x-FIXED_127), -2*(light.z-FIXED_127), FIXED_255);
            jo_3d_draw_sprite(curr_sprite);
            jo_3d_pop_matrix();
        }
	if (start_animation) {
                light.x -= LIGHT_SPEED;
                if (light.x < JO_FIXED_0)
                    light.x = FIXED_255;
                tile1_increment.h += 1;           
                move_light = true;
                do_update = true;
	}
	if (light.x == FIXED_255 && light.z == JO_FIXED_0 && curr_sprite == sun_sprite) {
	    curr_sprite = moon_sprite;
	}
	else if (light.x == FIXED_255 && light.z == JO_FIXED_0 && curr_sprite == moon_sprite) {
	    curr_sprite = sun_sprite;
	}

	// RBG0 position
	scrollx += jo_int2fixed(movement_speed);
	pos1.x -= movement_speed * jo_cos_radf(rot.rz) / 10.0;
	pos2.x -= movement_speed * jo_cos_radf(rot2.rz) / 100.0;
        if (pos1.x >=256.0) {
        	pos1.x = 0.0;
        }
        if (pos2.x >=256.0) {
        	pos2.x = 0.0;
        }
	if (pos1.y >=256.0) {
        	pos1.y = 0.0;
        }
        if (pos2.y >=256.0) {
        	pos2.y = 0.0;
        }

	// GROUND
	jo_3d_push_matrix();
	{
		jo_3d_rotate_matrix_rad(rot.rx, rot.ry, rot.rz);
		jo_3d_translate_matrixf(pos1.x, pos1.y, pos1.z);
		jo_background_3d_plane_a_draw(true);
	}
	jo_3d_pop_matrix();
	// SKY
	pos2.x -= windspeed / 1000;
	pos2.y -= windspeed / 500;
	jo_3d_push_matrix();
	{
		jo_3d_rotate_matrix_rad(rot.rx, rot.ry, rot2.rz);
		jo_3d_translate_matrixf(pos2.x, pos2.y, pos2.z);
		jo_background_3d_plane_b_draw(draw_plane_b);
	}
	jo_3d_pop_matrix();
}

void                title_text(void)	{
	jo_nbg2_clear();
	jo_nbg2_printf(4, 2, "VDP2 PLANE NORMAL MAP WITH LIGHTING");
}

void                debug_text(void)	{
        jo_nbg2_printf(3, 4, "LIGHT:  X=%3i, Y=%3i, Z=%3i", JO_FIXED_TO_INT(light.x), JO_FIXED_TO_INT(light.y), JO_FIXED_TO_INT(light.z));
        jo_nbg2_printf(3, 5, "TILE1:  H=%3i, S=%3i, L=%3i", hslGround.color[0].h, hslGround.color[0].s, hslGround.color[0].l);
        jo_nbg2_printf(3, 6, "TILE2:  H=%3i, S=%3i, L=%3i", hslGround.color[37].h, hslGround.color[37].s, hslGround.color[37].l);
}

void my_color_calc(void)
{
    if (move_light) {
        // not just for the sprite - this affects the actual lighting calculation
        light_position_ellipse_float(&light);
        move_light = false;
    }
    if (do_update) {
        NormalMapLighting2d(&hslGround, &rgbGround, &bufferPal, &light, &tile1_range, &tile1_increment);
        NormalMapLighting2d(&hslGround, &rgbGround, &bufferPal, &light, &tile2_range, &tile2_increment);
        update_palette = true;
        do_update = false;
    }
}

void my_palette_update(void)
{
    if (update_palette) {
        UpdatePaletteFromBuffer(&bufferPal, &ground_palette, &tile_range);
    }
    title_text();
    if (debugtxt) {
        debug_text();
    }
}

jo_palette      *my_light_palette_handling(void)
{
    jo_create_palette(&light_pal);
    return (&light_pal);
}

void                init_graphics(void)	{
    jo_enable_background_3d_plane(JO_COLOR_Black);
    
    // light
    jo_set_tga_palette_handling(my_light_palette_handling);
    sun_sprite = jo_sprite_add_tga(JO_ROOT_DIR, "SUN.TGA", 0);
    jo_sprite_set_palette(light_pal.id);
    moon_sprite = jo_sprite_add_tga(JO_ROOT_DIR, "MOON.TGA", 0);
    jo_sprite_set_palette(light_pal.id);
    curr_sprite = sun_sprite;

    jo_core_set_screens_order(JO_NBG2_SCREEN, JO_RBG0_SCREEN, JO_SPRITE_SCREEN);
    slColorCalc(CC_ADD | CC_TOP);
    slColorCalcOn(JO_RBG0_SCREEN);

    init_sky();
    MultiRgbToHsl(&hslSky, &rgbSky, &sky_range);

    init_ground();
    // tile1
    InitNormalImage(&hslGround, &tile1_range, &tile1_img);
    normal_init_2d(&hslGround, &rgbGround, &light, &tile1_range);
    // tile2
    InitNormalImage(&hslGround, &tile2_range, &tile2_img);
    normal_init_2d(&hslGround, &rgbGround, &light, &tile2_range);
    min_max_sl_id(&hslGround, &tile2_range, &ground_attr); // so you can adjust the saturation manually without overflowing
    
    // set initial image colors
    MultiPaletteUpdate(&ground_palette, &hslGround, &tile1_increment, &tile_range);
    MultiPaletteUpdate(&sky_palette, &hslSky, &sky_increment, &sky_range);

    // Set initial RBG0 position
    pos1.x = 110.0; // pos1 = ground
    pos2.x = 0.0; // pos2 = sky
    pos1.y = 0.0;
    pos2.y = 0.0;
    pos1.z = -60.0;
    pos2.z = 100.0;
    rot.rx = JO_DEG_TO_RAD(100); // horizon - 100 for 352x240, 110 for 704x448
    rot.ry = JO_DEG_TO_RAD(0.0);
    rot.rz = JO_DEG_TO_RAD(0);
    rot2.rz = JO_DEG_TO_RAD(0.0);
}

void my_input_callback(void) {
    my_input(&light, &tile2_increment, &hslGround, &ground_attr);
}

void                jo_main(void)	{
	jo_core_init(JO_COLOR_Black);
        jo_core_tv_off();
        init_font();
	init_graphics();
        jo_core_tv_on();
        
	jo_core_add_callback(my_input_callback);
	jo_core_add_callback(my_color_calc);
	jo_core_add_vblank_callback(my_palette_update);
	jo_core_add_callback(my_draw);
	jo_core_run();
}

/*
 ** END OF FILE
 */
