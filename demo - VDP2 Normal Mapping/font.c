#include <jo/jo.h>

jo_palette      text_pal;

jo_palette      *my_text_palette_handling(void)
{
    jo_create_palette(&text_pal);
    return (&text_pal);
}

void init_font(void) {
    jo_img_8bits    img;
    jo_set_tga_palette_handling(my_text_palette_handling);
    img.data = NULL;
    jo_tga_8bits_loader(&img, JO_ROOT_DIR, "FONT5.TGA", 2);
    jo_vdp2_set_nbg2_8bits_font(&img, " 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!?,.:;\"'&()=\%/\\*+-$<>", text_pal.id, false, true);
    jo_free_img(&img);
    for (int i = 2; i < 9; i++) {
            text_pal.data[i] = JO_COLOR_White;
    }
}