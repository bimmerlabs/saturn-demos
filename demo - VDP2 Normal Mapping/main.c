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
#include "font.h"
#include "input.h"
#include "sprites.h"
// background images here
#include "BG_DEF/rocks.h"
#include "BG_DEF/tiles.h"
#include "BG_DEF/flower.h"

// GROUND
jo_pos3D_fixed	pos1;
jo_rot3D_fixed	rot1;
// SKY
jo_pos3D_fixed	pos2;
jo_rot3D_fixed	rot2;
// FLOWER
jo_pos3D_fixed	pos3;
jo_rot3D_fixed	rot3;

const FIXED rotation_speed = toFIXED(0.2);
const FIXED LIGHT_SPEEDX   = toFIXED(0.4);
const FIXED LIGHT_SPEEDY   = toFIXED(0.2);

void                my_draw(void)	{
        my_sprite_draw(&flower1_palette, &flower1_spr_id, &pos3, &rot3);
        if (sprite_scale_up) {
            sprite_scale_counter += 1;
        }
        else if (!sprite_scale_up) {
            sprite_scale_counter -= 1;
        }
        
        if (sprite_scale_counter > 254) {
            sprite_scale_up = false;
        }
        else if (sprite_scale_counter < -254)  {
            sprite_scale_up = true;
        }
            
        for (int i = 0; i < NUM_SPRITES; i++) {
            if (sprite_scale_up) {
                sprite_pos[i].z += JO_FIXED_1;
            }
            else {
                sprite_pos[i].z -= JO_FIXED_1;
            }
            my_sprite_draw(&sprite_pal[i], &sprite_id[i], &sprite_pos[i], &rot3);
        }
            
	if (start_animation) {
                light1.x += LIGHT_SPEEDX;
                light2.x += LIGHT_SPEEDX;
                if (light1.x > FIXED_255) {
                    light1.x = JO_FIXED_0;
                    light2.x = JO_FIXED_0;
                }
                light1.y -= LIGHT_SPEEDY;
                light2.y -= LIGHT_SPEEDY;
                if (light1.y < JO_FIXED_0) {
                    light1.y = FIXED_255;
                    light2.y = FIXED_255;
                }
                
                light3.x += LIGHT_SPEEDY;
                if (light3.x > FIXED_255) {
                    light3.x = JO_FIXED_0;
                    light3.y += FIXED_127;
                    if (light3.y > FIXED_255) {
                        light3.y = toFIXED(100);
                    }
                }

                hsl_incRocks0.h += 1;           
                hsl_incTiles0.h -= 1;           
                move_light = true;
                do_update = true;
                
                // RBG0 position
                rot1.rx += JO_DEG_TO_RAD(rotation_speed);
                rot1.rz += JO_DEG_TO_RAD(rotation_speed);
                rot2.rx += JO_DEG_TO_RAD(rotation_speed);
                rot2.rz += JO_DEG_TO_RAD(rotation_speed);
                
                // FLOWER
                rot3.rz += JO_DEG_TO_RAD(rotation_speed);

                // ROCKS
                jo_3d_push_matrix();
                {
                    my_fixed_3d_rotate_matrix_rad(&rot1);
                    my_fixed_3d_translate_matrix(&pos1);
                    jo_background_3d_plane_a_draw(true);
                }
                jo_3d_pop_matrix();
                
                // TILES
                jo_3d_push_matrix();
                {
                    my_fixed_3d_rotate_matrix_rad(&rot2);
                    my_fixed_3d_translate_matrix(&pos2);
                    jo_background_3d_plane_b_draw(draw_plane_b);
                }
                jo_3d_pop_matrix();
        }
}

void                title_text(void)	{
	jo_nbg0_clear();
        jo_nbg0_printf(14, 2, "NORMAL MAP DEMO");
}

void                debug_text(void)	{
        jo_nbg0_printf(3, 4, "LIGHT1:  X=%3i, Y=%3i, Z=%3i", JO_FIXED_TO_INT(light1.x), JO_FIXED_TO_INT(light1.y), JO_FIXED_TO_INT(light1.z));
        jo_nbg0_printf(3, 5, "LIGHT2:  X=%3i, Y=%3i, Z=%3i", JO_FIXED_TO_INT(light2.x), JO_FIXED_TO_INT(light2.y), JO_FIXED_TO_INT(light2.z));
        jo_nbg0_printf(3, 6, "LIGHT3:  X=%3i, Y=%3i, Z=%3i", JO_FIXED_TO_INT(light3.x), JO_FIXED_TO_INT(light3.y), JO_FIXED_TO_INT(light3.z));
        jo_nbg0_printf(3, 7, "TILE1:  H=%3i, S=%3i, L=%3i", hslRocks.color[0].h, hslRocks.color[0].s, hslRocks.color[0].l);
        jo_nbg0_printf(3, 8, "TILE2:  H=%3i, S=%3i, L=%3i", hslRocks.color[37].h, hslRocks.color[37].s, hslRocks.color[37].l);
}

void my_color_calc(void)
{
    if (move_light) {
        light_position_ellipse_float(&light1);
        light_position_ellipse_float(&light2);
        light_position_ellipse_float(&light3);
        move_light = false;
    }
    if (do_update) {
        update_flower_color();
        update_tiles_color();
        update_rocks_color();
        update_palette = true;
        do_update = false;
    }
}

void my_palette_update(void)
{
    if (update_palette) {        
        update_flower_palette();
        update_tiles_palette();
        update_rocks_palette();
    }
    title_text();
    if (debugtxt) {
        debug_text();
    }
}

void                init_graphics(void)	{
    jo_enable_background_3d_plane(JO_COLOR_Black);

    jo_core_set_screens_order(JO_NBG2_SCREEN, JO_SPRITE_SCREEN, JO_RBG0_SCREEN);
    init_flower_img();
    init_tiles_img();
    init_rocks_img();

    // Set initial RBG0 position
    // ROCKS
    pos1.x = toFIXED(176);
    pos1.y = toFIXED(224);
    pos1.z = toFIXED(100.0);
    rot1.rx = JO_DEG_TO_RAD(toFIXED(-90));
    rot1.ry = JO_DEG_TO_RAD(JO_FIXED_0);
    rot1.rz = JO_DEG_TO_RAD(JO_FIXED_0);
    // tiles
    pos2.x = toFIXED(176);
    pos2.y = toFIXED(224);
    pos2.z = toFIXED(-300.0);
    rot2.rx = JO_DEG_TO_RAD(toFIXED(-90));
    rot2.ry = JO_DEG_TO_RAD(JO_FIXED_0);
    rot2.rz = JO_DEG_TO_RAD(JO_FIXED_0);
    // flower initial position
    initialize_sprite_positions();
    pos3.x = JO_FIXED_0;
    pos3.y = JO_FIXED_0;
    pos3.z = FIXED_255;
}

void my_input_callback(void) {
    my_input(&light1, &light2, &hsl_incRocks0, &hslRocks, &attrRocks0);
}

void                jo_main(void)	{
    jo_core_tv_off();
    jo_core_init(JO_COLOR_Black);
    init_font();
    init_graphics();

    jo_core_add_callback(my_input_callback);
    jo_core_add_callback(my_color_calc);
    jo_core_add_vblank_callback(my_palette_update);
    jo_core_add_callback(my_draw);
    jo_core_tv_on();
    jo_core_run();
}

/*
 ** END OF FILE
 */
