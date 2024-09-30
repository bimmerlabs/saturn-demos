// tiles.h
#ifndef TILES_H
#define TILES_H

#include "../palettetools.h"
#include "../lighting.h"

// this file is autogenerated - see tga_tools.pl (modified for demo)
// modifications: added additional buffers and palettes to enable separate tile colors

// palette for normal map calculations
RgbPalette rgbTiles = {
    { {0, 127, 255}, {127, 127, 255}, {103, 95, 237}, {31, 201, 65}, {27, 63, 63}, {127, 0, 255}, {225, 205, 73}, {113, 9, 61}, 
      {255, 127, 255}, {101, 175, 231}, {67, 233, 63}, {149, 9, 67}, {127, 255, 255}, {159, 103, 241}, {237, 71, 61}, {75, 19, 55}, 
      {59, 217, 121}, {237, 185, 65}, {163, 155, 239}, {215, 43, 67}, {201, 227, 71}, {9, 139, 79}, {99, 149, 245}, {91, 107, 237}, 
      {49, 221, 63}, {9, 115, 75}, {53, 49, 117}, {213, 201, 125}, {189, 23, 61}, {249, 149, 71}, {105, 247, 77}, {155, 245, 89}, 
      {159, 105, 243}, {249, 111, 67}, {55, 33, 61}, {171, 159, 233}, {209, 51, 121}, {0, 127, 255}, {127, 127, 255}, {103, 95, 237}, 
      {31, 201, 65}, {27, 63, 63}, {127, 0, 255}, {225, 205, 73}, {113, 9, 61}, {255, 127, 255}, {101, 175, 231}, {67, 233, 63}, 
      {149, 9, 67}, {127, 255, 255}, {159, 103, 241}, {237, 71, 61}, {75, 19, 55}, {59, 217, 121}, {237, 185, 65}, {163, 155, 239}, 
      {215, 43, 67}, {201, 227, 71}, {9, 139, 79}, {99, 149, 245}, {91, 107, 237}, {49, 221, 63}, {9, 115, 75}, {53, 49, 117}, 
      {213, 201, 125}, {189, 23, 61}, {249, 149, 71}, {105, 247, 77}, {155, 245, 89}, {159, 105, 243}, {249, 111, 67}, {55, 33, 61}, 
      {171, 159, 233}, {209, 51, 121} }
};

// buffer palette for writing to CRAM (populated at runtime)
RgbBuff bufferTiles = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0 }
};

// palette for calculating color and lighting - hue, saturation, luminance (populated at runtime)
HslPalette hslTiles = {
    { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0} }
};

// palette ranges - used with the palette group collection.
PaletteRange p_rangeTiles0 = { 0, 73 }; // default range - includes all unique palette entries
PaletteRange p_rangeTiles1 = { 0, 36 };
PaletteRange p_rangeTiles2 = { 37, 73 };

// tracks the accumulation of changes for the HSL color model
GlobalHSL hsl_incTiles0 = {0, 0, 0};
GlobalHSL hsl_incTiles1 = {0, 0, 0};
GlobalHSL hsl_incTiles2 = {0, 0, 0};

// initial image setup: hue, saturation, luminance, x_pos, y_pos, x_scale, y_scale, x_scroll (rate), y_scroll (rate), min_sat_id, max_sat_id, min_lum_id, max_lum_id
ImageAttr attrTiles0 = { 0, 255, 127, toFIXED(0.0), toFIXED(0.0), toFIXED(0.0), toFIXED(0.0), 0, 0, 0, 0};
ImageAttr attrTiles1 = { 0, 255, 127, toFIXED(0.0), toFIXED(0.0), toFIXED(0.0), toFIXED(0.0), 0, 0, 0, 0};
ImageAttr attrTiles2 = { 90, 127, 127, toFIXED(0.0), toFIXED(0.0), toFIXED(0.0), toFIXED(0.0), 0, 0, 0, 0};

// Helper Functions

static jo_palette tiles_palette;

jo_palette	*my_tiles_palette_handling(void)
{
    jo_create_palette(&tiles_palette);
    return (&tiles_palette);
}

void init_tiles_img(void) {
    jo_img_8bits    img;
    jo_set_tga_palette_handling(my_tiles_palette_handling);
    img.data = JO_NULL;
    jo_tga_8bits_loader(&img, JO_ROOT_DIR, "TILES.TGA", 0);
    jo_background_3d_plane_b_img(&img, tiles_palette.id, true, true);
    jo_free_img(&img);
    
    InitNormal2d(&hslTiles, &rgbTiles, &light1, &p_rangeTiles1, &attrTiles1);
    InitNormal2d(&hslTiles, &rgbTiles, &light1, &p_rangeTiles2, &attrTiles2);
    MultiPaletteUpdate(&tiles_palette, &hslTiles, &hsl_incTiles0, &p_rangeTiles0);

}

void update_tiles_color(void) {
    NormalMapLighting2d(&hslTiles, &rgbTiles, &bufferTiles, &light1, &p_rangeTiles1, &hsl_incRocks0);
    NormalMapLighting2d(&hslTiles, &rgbTiles, &bufferTiles, &light1, &p_rangeTiles2, &hsl_incTiles0);
}

void update_tiles_palette(void) {
    UpdatePaletteFromBuffer(&bufferTiles, &tiles_palette, &p_rangeTiles0);
}

#endif // TILES_H
