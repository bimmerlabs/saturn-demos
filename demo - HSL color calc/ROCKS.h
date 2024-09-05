// rocks.h
#ifndef ROCKS_H
#define ROCKS_H
#include "palette_config.h"

RgbPalette rgbPal = {
    { {63, 27, 56}, {30, 135, 136}, {52, 7, 164}, {31, 200, 143}, {23, 71, 168}, {158, 74, 168}, {28, 136, 206}, {157, 137, 203}, 
      {54, 200, 205}, {57, 72, 220}, {153, 10, 165}, {166, 76, 223}, {156, 167, 205}, {35, 168, 206}, {172, 201, 211}, {46, 104, 223}, 
      {162, 111, 220}, {109, 17, 209}, {61, 136, 235}, {97, 112, 217}, {144, 14, 206}, {164, 136, 236}, {72, 231, 199}, {214, 112, 218}, 
      {157, 231, 205}, {159, 169, 234}, {103, 136, 236}, {201, 136, 235}, {86, 104, 243}, {66, 173, 233}, {206, 80, 216}, {86, 120, 245}, 
      {94, 74, 223}, {142, 104, 241}, {141, 120, 241}, {161, 152, 234}, {101, 152, 236}, {77, 200, 227}, {198, 167, 233}, {143, 73, 240}, 
      {153, 41, 215}, {101, 169, 235}, {155, 200, 234}, {156, 185, 234}, {37, 39, 166}, {91, 73, 237}, {63, 54, 214}, {141, 87, 240}, 
      {154, 199, 147}, {188, 44, 211}, {105, 185, 234}, {90, 89, 241}, {168, 136, 141}, {105, 43, 219}, {20, 104, 167}, {160, 48, 165}, 
      {113, 119, 241}, {158, 104, 166}, {114, 104, 241}, {145, 44, 229}, {172, 120, 246}, {140, 132, 250}, {110, 57, 235}, {94, 136, 248}, 
      {103, 202, 214}, {172, 104, 244}, {140, 148, 250}, {211, 200, 205}, {100, 5, 167}, {114, 200, 231}, {94, 152, 247}, {169, 136, 249}, 
      {117, 132, 250}, {18, 72, 133}, {141, 167, 249}, {119, 230, 229}, {170, 89, 241}, {117, 214, 229}, {116, 89, 245}, {169, 152, 249}, 
      {105, 9, 188}, {113, 231, 204}, {156, 232, 227}, {94, 167, 247}, {118, 151, 250}, {116, 120, 250}, {163, 216, 210}, {148, 183, 247}, 
      {44, 232, 141}, {99, 56, 224}, {163, 232, 150}, {141, 116, 250}, {116, 247, 199}, {202, 236, 202}, {197, 198, 231}, {115, 105, 249}, 
      {24, 169, 140}, {141, 105, 250}, {170, 73, 237}, {200, 22, 165}, {169, 167, 248}, {156, 248, 201}, {155, 214, 230}, {156, 166, 142}, 
      {108, 217, 212}, {140, 140, 250}, {112, 183, 246}, {44, 120, 223}, {97, 105, 168}, {117, 167, 248}, {99, 47, 167}, {99, 137, 203}, 
      {227, 136, 205}, {222, 168, 206}, {54, 88, 224}, {236, 111, 168}, {116, 73, 240}, {97, 80, 167}, {102, 167, 204}, {141, 156, 250}, 
      {119, 198, 244}, {140, 124, 250}, {231, 80, 168}, {141, 89, 248}, {100, 23, 194}, {117, 140, 250}, {149, 58, 232}, {159, 56, 218}, 
      {154, 4, 137}, {161, 72, 134}, {36, 13, 120}, {14, 47, 115}, {32, 109, 120}, {161, 39, 139}, {157, 104, 137}, {160, 136, 170}, 
      {20, 135, 172}, {33, 201, 174}, {106, 168, 143}, {236, 168, 143}, {59, 232, 173}, {160, 234, 178}, {229, 199, 152}, {93, 40, 133}, 
      {92, 10, 119}, {93, 104, 135}, {221, 48, 164}, {100, 72, 134}, {221, 40, 135}, {231, 73, 138}, {95, 138, 139}, {238, 136, 173}, 
      {200, 8, 140}, {232, 143, 140}, {96, 136, 172}, {97, 200, 143}, {232, 104, 140}, {102, 200, 171}, {20, 169, 172}, {160, 169, 172}, 
      {99, 169, 175}, {234, 168, 173}, {100, 248, 148}, {214, 239, 147}, {211, 231, 172}, {158, 199, 175}, {99, 235, 179}, {223, 208, 178}, 
      {28, 80, 192}, {154, 80, 192}, {43, 49, 191}, {20, 112, 192}, {156, 113, 191}, {100, 112, 191}, {95, 44, 193}, {233, 112, 192}, 
      {100, 80, 190}, {225, 79, 192}, {27, 51, 141}, {200, 114, 237}, {57, 23, 186}, {95, 7, 141}, {163, 44, 190}, {40, 17, 142}, 
      {23, 112, 142}, {210, 50, 189}, {196, 84, 234}, {202, 233, 224}, {19, 88, 137}, {93, 55, 136}, {152, 17, 189}, {192, 25, 187}, 
      {156, 25, 138}, {230, 55, 139}, {155, 87, 138}, {162, 56, 138}, {94, 120, 137}, {212, 24, 140}, {24, 152, 135}, {30, 151, 205}, 
      {157, 152, 204}, {167, 185, 210}, {41, 184, 205}, {100, 152, 203}, {225, 152, 206}, {214, 184, 206}, {162, 152, 173}, {96, 88, 137}, 
      {241, 152, 174}, {193, 57, 215}, {155, 150, 136}, {96, 185, 209}, {105, 31, 212}, {236, 87, 140}, {150, 28, 210}, {163, 120, 136}, 
      {20, 151, 172}, {40, 216, 175}, {96, 152, 172}, {56, 248, 141}, {106, 216, 140}, {63, 215, 203}, {98, 215, 176}, {154, 185, 142}, 
      {93, 184, 144}, {232, 184, 146}, {24, 184, 171}, {162, 184, 173}, {201, 152, 234}, {211, 215, 202}, {197, 183, 232}, {100, 185, 173}, 
      {234, 184, 174}, {161, 252, 146}, {152, 250, 176}, {21, 216, 140}, {63, 246, 170}, {206, 249, 172}, {106, 249, 176}, {235, 215, 152}, 
      {162, 217, 178}, {62, 152, 234}, {203, 216, 232}, {94, 153, 139}, {232, 120, 139}, {153, 216, 148}, {18, 184, 142}, {45, 25, 166}, 
      {17, 88, 166}, {157, 89, 167}, {26, 57, 168}, {18, 121, 166}, {156, 120, 167}, {94, 23, 168}, {94, 119, 166}, {0, 0, 0} }
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
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
      {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} }
};

PaletteGroupCollection p_collection = {
    {
        { 0,  0,  NUM_PALETTE_ENTRIES },
    }
};

const Bool normal_map_mode = true; // false = HSL background, true = Normal mapping

ImageConfig image = {
    46, 127, 0, 127, toFIXED(0.0), toFIXED(0.0), toFIXED(0.0)
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
    jo_tga_8bits_loader(&img, "TEX", "ROCKS.TGA", 0);
    jo_vdp2_set_nbg1_8bits_image(&img, bg_palette.id, false);
    jo_free_img(&img);

    slScrPosNbg1(toFIXED(0.0), toFIXED(0.0));
    slZoomNbg1(toFIXED(1.0), toFIXED(1.0));
}

#endif // ROCKS_H
