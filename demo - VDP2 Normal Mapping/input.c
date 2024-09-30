#include "input.h"

Bool start_animation = true;
Bool move_light = false;
Bool draw_light = false;
Bool debugtxt = false;
Bool draw_plane_b = true;

void    my_input(LightSource *_light1, LightSource *_light2, GlobalHSL *_increment, HslPalette *_hslPal, ImageAttr *_attr)	{
        // move light
        if (jo_is_pad1_key_pressed(JO_KEY_UP) && _light1->y > JO_FIXED_0) {
            _light1->y -= JO_FIXED_1;
            _light2->y -= JO_FIXED_1;
            move_light = true;
            do_update = true;
        }
        else if (jo_is_pad1_key_pressed(JO_KEY_DOWN) && _light1->y < FIXED_255) {
            _light1->y += JO_FIXED_1;
            _light2->y += JO_FIXED_1;
            move_light = true;
            do_update = true;
        }	
        if (jo_is_pad1_key_pressed(JO_KEY_RIGHT) && _light1->x > JO_FIXED_0) {
            _light1->x -= JO_FIXED_1;
            _light2->x -= JO_FIXED_1;
            move_light = true;
            do_update = true;
        }
        else if (jo_is_pad1_key_pressed(JO_KEY_LEFT)&& _light1->x < FIXED_255) {
            _light1->x += JO_FIXED_1;
            _light2->x += JO_FIXED_1;
            move_light = true;
            do_update = true;
        }
        if (jo_is_pad1_key_down(JO_KEY_START)) {
            start_animation = !start_animation;
        }
        // hue
        if (jo_is_pad1_key_pressed(JO_KEY_A)) {
            _increment->h -= 1;
            do_update = true;
        }
        else if (jo_is_pad1_key_pressed(JO_KEY_X)) {
            _increment->h += 1;
            do_update = true;
        }
        // saturation
        if (jo_is_pad1_key_pressed(JO_KEY_B) && _hslPal->color[_attr->max_sat_id].s > 0) {
            _increment->s -= 1;
            do_update = true;
        }
        else if (jo_is_pad1_key_pressed(JO_KEY_Y) && _hslPal->color[_attr->min_sat_id].s < 255) {
            _increment->s += 1;
            do_update = true;
        }
        // other
        if (jo_is_pad1_key_down(JO_KEY_C)) {
            draw_plane_b = !draw_plane_b;
        }
        if (jo_is_pad1_key_down(JO_KEY_Z)) {
            debugtxt = !debugtxt;
        }
}