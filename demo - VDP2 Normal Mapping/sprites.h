#ifndef SPRITES_H
#define SPRITES_H

#include <jo/jo.h>  // Jo Engine headers
#include "math.h"
#include "lighting.h"

#define NUM_SPRITES 30

extern jo_pos3D_fixed sprite_pos[NUM_SPRITES];
extern jo_rot3D_fixed sprite_rot[NUM_SPRITES];
extern jo_palette     sprite_pal[NUM_SPRITES];
extern Uint8          sprite_id[NUM_SPRITES];
extern Bool           sprite_scale_up;
extern Sint16          sprite_scale_counter;

typedef struct {
	jo_pos3D_fixed p;
	jo_rot3D_fixed r;
} SpritePos;

// Function declaration for drawing sprites
static inline void my_sprite_draw(jo_palette *palette, Uint8 *spr_id, jo_pos3D_fixed *pos, jo_rot3D_fixed *rot) {
    // Set the sprite palette
    jo_sprite_set_palette(palette->id);

    // Push the matrix
    jo_3d_push_matrix();

    // Rotate the matrix based on the provided rotation values
    my_fixed_3d_rotate_matrix_rad(rot);

    // Translate the sprite to the provided coordinates
    jo_3d_translate_matrix_fixed(pos->x, pos->y, pos->z);

    // Draw the sprite with the provided sprite ID
    jo_3d_draw_sprite(*spr_id);

    // Pop the matrix
    jo_3d_pop_matrix();
}

void initialize_sprite_positions(void);

typedef struct {
    SpritePos spr[8];
} SpriteList;

#endif // SPRITES_H
