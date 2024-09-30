// palette_config.h
#ifndef PALETTE_CONFIG_H
#define PALETTE_CONFIG_H

// this file is autogenerated - see tga_tools.pl

#define NUM_PALETTE_ENTRIES 254
#define NUM_PALETTE_GROUPS 2
#define NORMAL_MAP_MODE 1

typedef struct {
    Uint16 hue;
    Uint8 sat;
    Uint8 lum;
    FIXED x_pos;
    FIXED y_pos;
    FIXED scroll_rate;
} ImageConfig;

#endif // PALETTE_CONFIG_H