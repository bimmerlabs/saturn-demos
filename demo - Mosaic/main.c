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

#define MOSAIC_MIN  1
#define MOSAIC_X_MAX  16
#define MOSAIC_X_RATE  2
#ifdef MY_TV_704x240 // high res non-interlaced gets doubled internally
	#define MOSAIC_Y_MAX  8
	#define MOSAIC_Y_RATE  4
#else
	#define MOSAIC_Y_MAX 16
	#define MOSAIC_Y_RATE  2
#endif
// NOTE: blur doesn't work in high res mode.  Instead, transparency is enabled (CC_RATE)
#define BLUR_MIN    CLRate31_1
#define BLUR_MAX    CLRate0_32
#define BLUR_RATE   1

#define BG_SCROLL toFIXED(0.5);
static FIXED pos_x = toFIXED(0);
static FIXED pos_y = toFIXED(0);

jo_palette                  image_pal;
static unsigned short     mosaic_size_x = 1;
static unsigned short     mosaic_size_y = 1;
static int		    blur = BLUR_MIN;
static Uint8		    frame = 0;
static Uint8		    current_background = 1;

void                    load_background_image(Uint8 background)
{
    jo_img_8bits        img;

    img.data = NULL;
    switch (background) {
    	case 1: {
		jo_tga_8bits_loader(&img, "BG", "WAVES1.TGA", 0);
		break;
	}
    	case 2: {
		jo_tga_8bits_loader(&img, "BG", "WAVES2.TGA", 0);
		break;
	}
    	case 3: {
		jo_tga_8bits_loader(&img, "BG", "WAVES4.TGA", 0);
		break;
	}
    	case 4: {
		jo_tga_8bits_loader(&img, "BG", "BG.TGA", 0);
		break;
	}
    	case 5: {
		jo_tga_8bits_loader(&img, "BG", "BG1.TGA", 0);
		break;
	}
    	case 6: {
		jo_tga_8bits_loader(&img, "BG", "BG28.TGA", 0);
		break;
	}
    	case 7: {
		jo_tga_8bits_loader(&img, "BG", "BG29.TGA", 0);
		break;
	}
    	case 8: {
		jo_tga_8bits_loader(&img, "BG", "BG27.TGA", 0);
		break;
	}
    	case 9: {
		jo_tga_8bits_loader(&img, "BG", "BG26.TGA", 0);
		break;
	}
    }
    jo_vdp2_set_nbg1_8bits_image(&img, image_pal.id, false);
    jo_free_img(&img);
}

void			            my_draw(void)
{
	if (jo_is_pad1_key_pressed(JO_KEY_UP))
	{
		// pos_y -= BG_SCROLL;
		if ((mosaic_size_y += 1) > MOSAIC_Y_MAX)
			mosaic_size_y = MOSAIC_Y_MAX;
	}
	else if (jo_is_pad1_key_pressed(JO_KEY_DOWN))
	{		
		// pos_y += BG_SCROLL;
		if ((mosaic_size_y -= 1) < MOSAIC_MIN)
			mosaic_size_y = MOSAIC_MIN;
	}
	if (jo_is_pad1_key_pressed(JO_KEY_RIGHT))
	{
		// pos_x -= BG_SCROLL;
		if ((mosaic_size_x += 1) > MOSAIC_X_MAX)
			mosaic_size_x = MOSAIC_X_MAX;
	}
	else if (jo_is_pad1_key_pressed(JO_KEY_LEFT))
	{	
		// pos_x += BG_SCROLL;
		if ((mosaic_size_x -= 1) < MOSAIC_MIN)
			mosaic_size_x = MOSAIC_MIN;
	}
	
	if (jo_is_pad1_key_pressed(JO_KEY_A))
	{
		if (frame % MOSAIC_X_RATE == 0) {
			if ((mosaic_size_x += 1) > MOSAIC_X_MAX)
				mosaic_size_x = MOSAIC_X_MAX;
		}
		if (frame % MOSAIC_Y_RATE == 0) {
			if ((mosaic_size_y += 1) > MOSAIC_Y_MAX)
				mosaic_size_y = MOSAIC_Y_MAX;
		}
	}
	else if (jo_is_pad1_key_pressed(JO_KEY_X))
	{
		if (frame % MOSAIC_X_RATE == 0) {
			if ((mosaic_size_x -= 1) < MOSAIC_MIN)
				mosaic_size_x = MOSAIC_MIN;
		}
		if (frame % MOSAIC_Y_RATE == 0) {
			if ((mosaic_size_y -= 1) < MOSAIC_MIN)
				mosaic_size_y = MOSAIC_MIN;
		}
	}
	
	if (jo_is_pad1_key_pressed(JO_KEY_B))
	{
		if (frame % BLUR_RATE == 0) {
			if ((blur += 1) > BLUR_MAX)
				blur = BLUR_MAX;
			slColRateNbg1 ( blur );
		}
	}
	else if (jo_is_pad1_key_pressed(JO_KEY_Y))
	{
		if (frame % BLUR_RATE == 0) {
			if ((blur -= 1) < BLUR_MIN)
				blur = BLUR_MIN;
			slColRateNbg1 ( blur );
		}
	}
	
	if (jo_is_pad1_key_down(JO_KEY_C))
	{
		mosaic_size_y = MOSAIC_Y_MAX;
		mosaic_size_x = MOSAIC_X_MAX;
		blur = BLUR_MAX;
		slColRateNbg1 ( blur );
	}
	else if (jo_is_pad1_key_down(JO_KEY_Z))
	{
		mosaic_size_y = MOSAIC_MIN;
		mosaic_size_x = MOSAIC_MIN;
		blur = BLUR_MIN;
		slColRateNbg1 ( blur );
	}
	if (jo_is_pad1_key_down(JO_KEY_START))
	{
		mosaic_size_y = MOSAIC_MIN;
		mosaic_size_x = MOSAIC_MIN;
		blur = BLUR_MIN;
		slColRateNbg1 ( blur );
	}
	
	if (jo_is_pad1_key_down(JO_KEY_R))
	{
		jo_core_tv_off();
		current_background += 1;
		if (current_background > 9) {
			current_background = 1;
		}
		load_background_image(current_background);
		jo_core_tv_on();		
	}
	if (jo_is_pad1_key_down(JO_KEY_L))
	{
		jo_core_tv_off();
		current_background -= 1;
		if (current_background < 1) {
			current_background = 9;
		}
		load_background_image(current_background);
		jo_core_tv_on();		
	}
	
	// the same as:
	// jo_enable_screen_mozaic(JO_NBG1_SCREEN, mosaic_size_x, mosaic_size_y);
	slScrMosSize ( mosaic_size_x, mosaic_size_y );
	
	jo_printf(2, 4, "mosaic_size_x: %i", mosaic_size_x);
	jo_printf(2, 5, "mosaic_size_y: %i", mosaic_size_y);
	jo_printf(2, 6, "blur: %i", blur);
	jo_printf(2, 7, "background: %i", current_background);
	jo_printf(20, 4, "A/X: INC/DEC MOSAIC");
	jo_printf(20, 5, "B/Y: INC/DEC BLUR");
	jo_printf(20, 6, "C/Z: MAX/MIN SETTINGS");
	jo_printf(20, 7, "L/R TRIGGER: NEXT BG");
	
        if (pos_x > toFIXED(512.0) || pos_x < toFIXED(-512.0))
            pos_x = toFIXED(0);
        if (pos_y > toFIXED(512.0) || pos_y < toFIXED(-512.0))
            pos_y = toFIXED(0);
	slScrPosNbg1(pos_x, pos_y);
        pos_x += BG_SCROLL;
}

void my_text_clear(void) {
	jo_clear_screen();
	frame++;
	if (frame == 240)
		frame = 0;
}

// jo_palette          *my_tga_palette_handling(void)
// {
    // jo_create_palette(&image_pal);
    // return (&image_pal);
// }

void			    jo_main(void)
{
    jo_core_init(JO_COLOR_Black);
    
    slColRAMMode ( CRM16_1024 ); // CRAM mode 0
    slGradationOn ( grdNBG1 ); // if used with CC_ADD, blur will always be on (rate is fixed at 100%)
    slColorCalc ( CC_RATE | CC_TOP | NBG1ON );
    slColRateNbg1 ( blur );
    slScrMosaicOn ( NBG1ON );
    
    jo_core_tv_off();
    jo_create_palette(&image_pal);
    jo_set_tga_default_palette(&image_pal);
    // jo_set_tga_palette_handling(my_tga_palette_handling);
    load_background_image(current_background);
    jo_core_tv_on();
    jo_core_add_callback(my_draw);
    jo_core_add_vblank_callback(my_text_clear);
    jo_core_run();
}

/*
** END OF FILE
*/
