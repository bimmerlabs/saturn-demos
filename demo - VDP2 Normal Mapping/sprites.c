#include "sprites.h"  // Include your new sprites.h

jo_pos3D_fixed sprite_pos[NUM_SPRITES];
jo_rot3D_fixed sprite_rot[NUM_SPRITES];
jo_palette     sprite_pal[NUM_SPRITES];
Uint8          sprite_id[NUM_SPRITES];
Bool           sprite_scale_up = false;
Sint16         sprite_scale_counter = 0;

void initialize_sprite_positions(void) {
    Uint8 pal_id = 2;
    Uint8 spr_id = 0;
    for (int i = 0; i < NUM_SPRITES; i++) {
        // Initialize the palette ID to 2 for each sprite
        sprite_pal[i].id = pal_id;
        sprite_id[i] = spr_id;
    }
    for (int i = 0; i < NUM_SPRITES; i++) {
        // Randomize the initial position within the defined ranges
        sprite_pos[i].x = jo_random(toFIXED(704)) - toFIXED(352);
        sprite_pos[i].y = jo_random(toFIXED(480)) - toFIXED(240);
        sprite_pos[i].z = jo_random(toFIXED(510)) + toFIXED(255);
        if (pal_id > 5)
            pal_id = 2;
        sprite_pal[i].id = pal_id;
        pal_id += 1;
        if (spr_id > 3)
            spr_id = 0;
        sprite_id[i] = spr_id;
        spr_id += 1;
        // Randomize the rotation angles
        sprite_rot[i].rz = JO_INT_TO_FIXED(jo_random(360));  // Rotation around Z-axis (0-359)
    }
}