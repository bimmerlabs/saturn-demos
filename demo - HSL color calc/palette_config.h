// palette_config.h
#ifndef PALETTE_CONFIG_H
#define PALETTE_CONFIG_H

#define NUM_PALETTE_ENTRIES 254
#define NUM_PALETTE_GROUPS 1

typedef struct {
    Uint8 hue;
    Uint8 sat;
    Uint8 lum;
    Uint8 darkness;
    FIXED x_pos;
    FIXED y_pos;
    FIXED scroll_rate;
} ImageConfig;

#endif // PALETTE_CONFIG_H
