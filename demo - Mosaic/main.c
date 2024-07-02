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

# define MOZAIC_MAX  (16)
# define MOZAIC_MIN  (1)

jo_palette                  image_pal;
static unsigned short     mozaic_size_x = 16;
static unsigned short     mozaic_size_y = 12;
static unsigned short     scroll = 1;

void			            my_draw(void)
{
	if (jo_is_pad1_key_pressed(JO_KEY_UP))
	{
		if ((mozaic_size_y += 1) > MOZAIC_MAX)
			mozaic_size_y = MOZAIC_MAX;
	}
	else if (jo_is_pad1_key_pressed(JO_KEY_DOWN))
	{
		if ((mozaic_size_y -= 1) < MOZAIC_MIN)
			mozaic_size_y = MOZAIC_MIN;
	}
	if (jo_is_pad1_key_pressed(JO_KEY_RIGHT))
	{
		if ((mozaic_size_x += 1) > MOZAIC_MAX)
			mozaic_size_x = MOZAIC_MAX;
	}
	else if (jo_is_pad1_key_pressed(JO_KEY_LEFT))
	{
		if ((mozaic_size_x -= 1) < MOZAIC_MIN)
			mozaic_size_x = MOZAIC_MIN;
	}
	if (jo_is_pad1_key_down(JO_KEY_A))
	{
		if ((mozaic_size_y += 1) > MOZAIC_MAX)
			mozaic_size_y = MOZAIC_MAX;
		if ((mozaic_size_x += 1) > MOZAIC_MAX)
			mozaic_size_x = MOZAIC_MAX;
	}
	else if (jo_is_pad1_key_down(JO_KEY_B))
	{
		if ((mozaic_size_x -= 1) < MOZAIC_MIN)
			mozaic_size_x = MOZAIC_MIN;
		if ((mozaic_size_y -= 1) < MOZAIC_MIN)
			mozaic_size_y = MOZAIC_MIN;
	}
	if (jo_is_pad1_key_down(JO_KEY_X))
	{
		mozaic_size_y = 16;
		mozaic_size_x = 16;
	}
	else if (jo_is_pad1_key_down(JO_KEY_Y))
	{
		mozaic_size_y = 1;
		mozaic_size_x = 1;
	}
	jo_enable_screen_mozaic(JO_NBG1_SCREEN, mozaic_size_x, mozaic_size_y);
	scroll++;
	jo_vdp2_move_nbg1(-scroll, scroll);
	
	jo_clear_screen();
	jo_printf(2, 2, "mozaic_size_x: %i", mozaic_size_x);
	jo_printf(2, 3, "mozaic_size_y: %i", mozaic_size_y);
}

void                    load_background_image()
{
    jo_img_8bits        img;

    img.data = NULL;
    jo_tga_8bits_loader(&img, "BG", "BG.TGA", 0);
    jo_set_background_8bits_sprite(&img, image_pal.id, false);
    jo_free_img(&img);
}

jo_palette          *my_tga_palette_handling(void)
{
    jo_create_palette(&image_pal);
    return (&image_pal);
}

void			    jo_main(void)
{
    jo_core_init(JO_COLOR_Black);
    jo_core_tv_off();
    jo_set_tga_palette_handling(my_tga_palette_handling);
    load_background_image();
    jo_core_tv_on();
    jo_core_add_callback(my_draw);
    jo_core_run();
}

/*
** END OF FILE
*/
