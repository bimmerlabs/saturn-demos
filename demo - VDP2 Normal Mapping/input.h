#ifndef INPUT_H
#define INPUT_H

#include <jo/jo.h>
#include "lighting.h"

extern Bool start_animation;
extern Bool move_light;
extern Bool draw_light;
extern Bool debugtxt;
extern Bool draw_plane_b;

void	my_input(LightSource *_light, GlobalHSL *_increment, HslPalette *_hslGround, ImgAttributes *_ground_attr);

#endif // INPUT_H