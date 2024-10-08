// light.h
#ifndef LIGHT_H
#define LIGHT_H
#include "../palette_config.h"

// this file is autogenerated - see tga_tools.pl

RgbPalette rgbPal = {
    { {1, 1, 1}, {143, 143, 143}, {73, 73, 73}, {29, 29, 29}, {20, 20, 20}, {231, 231, 231}, {10, 10, 10}, {117, 117, 117}, 
      {91, 91, 91}, {247, 247, 247}, {165, 165, 165}, {49, 49, 49}, {83, 83, 83}, {151, 151, 151}, {37, 37, 37}, {255, 255, 255} }
};

HslPalette hslPal = {
    { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} }
};

PaletteGroupCollection p_collection = {
    {
        { 0,  0,  NUM_PALETTE_ENTRIES },
    }
};

ImageConfig image = {
    0, 0, 0, 0, toFIXED(0.0), toFIXED(0.0), toFIXED(0.0)
};

static jo_palette bg_palette;

jo_palette	*light_palette_handling(void)
{
    jo_create_palette(&bg_palette);
    return (&bg_palette);
}

void init_background(void) {
    jo_set_tga_palette_handling(light_palette_handling);
    jo_sprite_add_tga("TEX", "LIGHT.TGA", 1);
}

#endif // LIGHT_H
