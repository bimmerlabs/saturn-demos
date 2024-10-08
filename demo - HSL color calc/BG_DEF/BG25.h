// bg25.h
#ifndef BG25_H
#define BG25_H
#include "../palette_config.h"

// this file is autogenerated - see tga_tools.pl

RgbPalette rgbPal = {
    { {191, 3, 51}, {117, 23, 53}, {133, 57, 83}, {77, 3, 61}, {3, 7, 79}, {3, 57, 101}, {47, 115, 155}, {79, 153, 185}, 
      {3, 7, 41}, {3, 29, 49}, {3, 109, 111}, {3, 75, 73}, {3, 57, 49}, {3, 45, 37}, {5, 65, 45}, {255, 255, 255} }
};

HslPalette hslPal = {
    { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} }
};

PaletteGroupCollection p_collection = {
    {
        { 0,  0,  NUM_PALETTE_ENTRIES },
        { 0, 0, 3 },
        { 4, 4, 7 },
        { 8, 8, 14 },
        { 15, 15, 15 },
    }
};

ImageConfig image = {
    0, 0, 0, 0, toFIXED(0.0), toFIXED(0.0), toFIXED(0.5)
};

static jo_palette bg_palette;

jo_palette	*bg25_palette_handling(void)
{
    jo_create_palette(&bg_palette);
    return (&bg_palette);
}

void init_background(void) {
    jo_img_8bits    img;
    jo_set_tga_palette_handling(bg25_palette_handling);
    img.data = JO_NULL;
    jo_tga_8bits_loader(&img, "TEX", "BG25.TGA", 0);
    jo_vdp2_set_nbg1_8bits_image(&img, bg_palette.id, false);
    jo_free_img(&img);

    slScrPosNbg1(toFIXED(0.0), toFIXED(0.0));
    slZoomNbg1(toFIXED(1.0), toFIXED(1.0));
}

#endif // BG25_H
