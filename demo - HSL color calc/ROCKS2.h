// rocks2.h
#ifndef ROCKS2_H
#define ROCKS2_H
#include "palette_config.h"

RgbPalette rgbPal = {
    { {26, 15, 133}, {32, 141, 143}, {20, 75, 136}, {57, 205, 142}, {52, 85, 208}, {53, 141, 209}, {170, 76, 209}, {164, 145, 206}, 
      {75, 203, 204}, {56, 18, 195}, {158, 112, 205}, {61, 174, 203}, {159, 19, 197}, {178, 210, 211}, {48, 113, 207}, {173, 179, 210}, 
      {180, 105, 236}, {72, 143, 233}, {172, 43, 207}, {74, 237, 198}, {167, 136, 245}, {72, 167, 229}, {68, 113, 232}, {157, 72, 234}, 
      {71, 83, 227}, {51, 51, 193}, {161, 235, 199}, {168, 167, 240}, {202, 116, 228}, {109, 135, 248}, {153, 55, 226}, {82, 202, 231}, 
      {105, 105, 245}, {110, 166, 245}, {205, 144, 229}, {158, 120, 246}, {60, 50, 229}, {198, 84, 227}, {240, 207, 139}, {102, 73, 234}, 
      {156, 88, 241}, {114, 186, 238}, {170, 152, 242}, {109, 153, 247}, {202, 169, 226}, {161, 202, 232}, {159, 183, 238}, {104, 121, 247}, 
      {206, 49, 198}, {174, 2, 122}, {99, 88, 239}, {175, 82, 147}, {120, 199, 232}, {123, 214, 231}, {168, 145, 166}, {223, 105, 204}, 
      {152, 105, 247}, {98, 44, 209}, {222, 120, 207}, {214, 204, 198}, {107, 213, 213}, {155, 18, 228}, {67, 242, 144}, {166, 240, 234}, 
      {163, 46, 161}, {32, 115, 148}, {45, 172, 145}, {21, 45, 131}, {152, 111, 169}, {169, 253, 146}, {166, 176, 170}, {160, 3, 165}, 
      {33, 79, 171}, {41, 47, 168}, {103, 20, 230}, {41, 143, 173}, {45, 17, 166}, {161, 83, 173}, {164, 212, 174}, {170, 244, 177}, 
      {62, 206, 172}, {245, 173, 147}, {114, 234, 237}, {239, 111, 147}, {79, 123, 142}, {53, 181, 171}, {102, 244, 172}, {243, 143, 151}, 
      {225, 45, 164}, {222, 9, 157}, {209, 15, 193}, {213, 49, 229}, {78, 75, 215}, {213, 78, 205}, {93, 78, 173}, {93, 3, 139}, 
      {92, 46, 166}, {100, 10, 164}, {239, 83, 171}, {105, 145, 205}, {219, 145, 210}, {214, 176, 207}, {235, 176, 173}, {214, 17, 225}, 
      {83, 149, 138}, {109, 76, 140}, {98, 180, 209}, {237, 246, 140}, {100, 112, 207}, {220, 238, 200}, {96, 145, 172}, {227, 208, 171}, 
      {222, 242, 171}, {125, 207, 148}, {107, 55, 226}, {237, 111, 179}, {110, 211, 173}, {248, 82, 146}, {109, 21, 196}, {101, 114, 176}, 
      {122, 236, 201}, {233, 6, 130}, {105, 178, 175}, {36, 116, 176}, {120, 254, 146}, {208, 236, 230}, {239, 144, 176} }
};

RgbPalette originalPal = {
    { {26, 15, 133}, {32, 141, 143}, {20, 75, 136}, {57, 205, 142}, {52, 85, 208}, {53, 141, 209}, {170, 76, 209}, {164, 145, 206}, 
      {75, 203, 204}, {56, 18, 195}, {158, 112, 205}, {61, 174, 203}, {159, 19, 197}, {178, 210, 211}, {48, 113, 207}, {173, 179, 210}, 
      {180, 105, 236}, {72, 143, 233}, {172, 43, 207}, {74, 237, 198}, {167, 136, 245}, {72, 167, 229}, {68, 113, 232}, {157, 72, 234}, 
      {71, 83, 227}, {51, 51, 193}, {161, 235, 199}, {168, 167, 240}, {202, 116, 228}, {109, 135, 248}, {153, 55, 226}, {82, 202, 231}, 
      {105, 105, 245}, {110, 166, 245}, {205, 144, 229}, {158, 120, 246}, {60, 50, 229}, {198, 84, 227}, {240, 207, 139}, {102, 73, 234}, 
      {156, 88, 241}, {114, 186, 238}, {170, 152, 242}, {109, 153, 247}, {202, 169, 226}, {161, 202, 232}, {159, 183, 238}, {104, 121, 247}, 
      {206, 49, 198}, {174, 2, 122}, {99, 88, 239}, {175, 82, 147}, {120, 199, 232}, {123, 214, 231}, {168, 145, 166}, {223, 105, 204}, 
      {152, 105, 247}, {98, 44, 209}, {222, 120, 207}, {214, 204, 198}, {107, 213, 213}, {155, 18, 228}, {67, 242, 144}, {166, 240, 234}, 
      {163, 46, 161}, {32, 115, 148}, {45, 172, 145}, {21, 45, 131}, {152, 111, 169}, {169, 253, 146}, {166, 176, 170}, {160, 3, 165}, 
      {33, 79, 171}, {41, 47, 168}, {103, 20, 230}, {41, 143, 173}, {45, 17, 166}, {161, 83, 173}, {164, 212, 174}, {170, 244, 177}, 
      {62, 206, 172}, {245, 173, 147}, {114, 234, 237}, {239, 111, 147}, {79, 123, 142}, {53, 181, 171}, {102, 244, 172}, {243, 143, 151}, 
      {225, 45, 164}, {222, 9, 157}, {209, 15, 193}, {213, 49, 229}, {78, 75, 215}, {213, 78, 205}, {93, 78, 173}, {93, 3, 139}, 
      {92, 46, 166}, {100, 10, 164}, {239, 83, 171}, {105, 145, 205}, {219, 145, 210}, {214, 176, 207}, {235, 176, 173}, {214, 17, 225}, 
      {83, 149, 138}, {109, 76, 140}, {98, 180, 209}, {237, 246, 140}, {100, 112, 207}, {220, 238, 200}, {96, 145, 172}, {227, 208, 171}, 
      {222, 242, 171}, {125, 207, 148}, {107, 55, 226}, {237, 111, 179}, {110, 211, 173}, {248, 82, 146}, {109, 21, 196}, {101, 114, 176}, 
      {122, 236, 201}, {233, 6, 130}, {105, 178, 175}, {36, 116, 176}, {120, 254, 146}, {208, 236, 230}, {239, 144, 176} }
};

HslPalette hslPal = {
    { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} }
};

PaletteGroupCollection p_collection = {
    {
        { 0,  0,  NUM_PALETTE_ENTRIES },
    }
};

const Bool normal_map_mode = true; // false = HSL background, true = Normal mapping

ImageConfig image = {
    188, 127, 0, 163, toFIXED(0.0), toFIXED(0.0), toFIXED(0.0)
};

static jo_palette bg_palette;

jo_palette	*my_bg_palette_handling(void)
{
    jo_create_palette(&bg_palette);
    return (&bg_palette);
}

void init_background(void) {
    jo_img_8bits    img;
    jo_set_tga_palette_handling(my_bg_palette_handling);
    img.data = JO_NULL;
    jo_tga_8bits_loader(&img, "TEX", "ROCKS2.TGA", 0);
    jo_vdp2_set_nbg1_8bits_image(&img, bg_palette.id, false);
    jo_free_img(&img);

    slScrPosNbg1(toFIXED(0.0), toFIXED(0.0));
    slZoomNbg1(toFIXED(1.0), toFIXED(1.0));
}

#endif // ROCKS2_H