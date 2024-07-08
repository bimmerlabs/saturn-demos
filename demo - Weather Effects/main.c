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
#include "weather.h"

// GROUND
jo_pos3Df	pos1;
jo_rot3Df	rot;
// SKY
jo_pos3Df	pos2;
jo_rot3Df	rot2;

jo_fixed	scrollx;

jo_palette	snow_pal;
jo_palette 	image_pal;

static float 	windspeed = 5.0f;
static int 	scrollspeed = 20;    
static int	movement_speed = 0;


void                my_draw(void)	{
	// SNOW
	draw_snow(&snow_pal, scrollx);

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
		jo_background_3d_plane_b_draw(true);
	}
	jo_3d_pop_matrix();
	

}

void                debug_text(void)	{
	jo_nbg2_clear();
	jo_nbg2_printf(2, 2,  "LET IT SNOW!");
	jo_nbg2_printf(2, 4,  "SNOW_COLOR1: %i", snow_color1);
	jo_nbg2_printf(2, 5,  "SNOW_COLOR2: %i", snow_color2);
}

void                my_input(void)	{
	static bool	is_cd_playing = false;
	if (jo_is_pad1_key_pressed(JO_KEY_RIGHT))	{
		if ((movement_speed += 10) > scrollspeed)
		movement_speed = scrollspeed;
	}
	else if (jo_is_pad1_key_pressed(JO_KEY_LEFT))	{
		if ((movement_speed -= 10) < -scrollspeed)
		movement_speed = -scrollspeed;
	}
	else if (movement_speed > 5)
		movement_speed -= 1;
	else if (movement_speed < -5)
		movement_speed += 1;
	else
		movement_speed = 0;   

	// music
	if (jo_is_pad1_key_down(JO_KEY_C))	{
		if (!is_cd_playing)	{
			/* The first track in this demo is game data so the first audio track is 2.
			For more details you can open "game.cue" file with a notepad */
			jo_audio_play_cd_track(2, 2, true);
			is_cd_playing = true;
		}
		else	{
			jo_audio_stop_cd();
			is_cd_playing = false;
		}
	}
}

// keep the snow palette separate
jo_palette                *my_snow_palette_handling(void)	{
    jo_create_palette(&snow_pal);
    return (&snow_pal);
}

// all other images are loaded here
jo_palette                *my_bg_palette_handling(void)	{
    jo_create_palette(&image_pal);
    return (&image_pal);
}

void                init_vdp2(void)	{
    jo_core_set_screens_order(JO_NBG2_SCREEN, JO_NBG0_SCREEN, JO_RBG0_SCREEN);
    slColorCalc(CC_ADD | CC_2ND | JO_NBG0_SCREEN); // this is the magic line
    jo_img_8bits    img;
    jo_core_tv_off();
    jo_enable_background_3d_plane(JO_COLOR_Black);

	// SNOW
	jo_set_tga_palette_handling(my_snow_palette_handling);
	img.data = JO_NULL;
	jo_tga_8bits_loader(&img, JO_ROOT_DIR, "SNOWA3.TGA", 1);
	jo_vdp2_set_nbg0_8bits_image(&img, snow_pal.id, false, true);
	initialize_snow(&snow_pal);
	jo_free_img(&img);

	jo_set_tga_palette_handling(my_bg_palette_handling);
	// FONT
	img.data = NULL;
	jo_tga_8bits_loader(&img, JO_ROOT_DIR, "FONT4.TGA", 2);
	jo_vdp2_set_nbg2_8bits_font(&img, " 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!?,.:;\"'&()=%/\\*+-$<>", image_pal.id, false, true);
	jo_free_img(&img);
	for (int i = 2; i < 9; i++) {
	image_pal.data[i] = JO_COLOR_White;
	}
	// GROUND
	img.data = JO_NULL;
	jo_tga_8bits_loader(&img, JO_ROOT_DIR, "SNOWBG.TGA", 0);
	jo_background_3d_plane_a_img(&img, image_pal.id, true, true);
	jo_free_img(&img);
	// SKY
	img.data = JO_NULL;
	jo_tga_8bits_loader(&img, JO_ROOT_DIR, "SNOWSKY.TGA", 0);
	jo_background_3d_plane_b_img(&img, image_pal.id, true, true);
	jo_free_img(&img);

	// Set initial RBG0 position
	pos1.x = 110.0;
	pos2.x = 0.0;
	pos1.y = 0.0;
	pos2.y = 0.0;
	pos1.z = -20.0;
	pos2.z = 100.0;
	rot.rx = JO_DEG_TO_RAD(96.0);
	rot.ry = JO_DEG_TO_RAD(0.0);
	rot.rz = JO_DEG_TO_RAD(180.0);
	rot2.rz = JO_DEG_TO_RAD(0.0);
	
    jo_core_tv_on();
}

void                jo_main(void)	{
	jo_core_init(JO_COLOR_Black);
	init_vdp2();

	jo_core_add_callback(my_input);
	jo_core_add_callback(my_draw);
	jo_core_add_callback(debug_text);
	jo_core_run();
}

/*
 ** END OF FILE
 */
