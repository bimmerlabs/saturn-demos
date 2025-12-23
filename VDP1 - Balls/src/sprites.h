#pragma once

#include <srl.hpp>

// SGL doesn't have these by default
#define	    Pclpoff		(1 << 11)	/* No pre-clipping and no horizontal inversion */
#define	    Pclpon		(0 << 11)	/* Pre-clipping with horizontal inversion (default) */

#define maxBalls (1501)
    
#ifdef SRL_HIGH_RES
static const int16_t screenWidth  = 704;
static const int16_t screenHeight = 480;
#else
static const int16_t screenWidth  = 352;
static const int16_t screenHeight = 224;
#endif

using namespace SRL::Types;
using namespace SRL::Math::Types;
    
extern int spriteDrawCount;

typedef struct {
    Fxp x, y, z;
    Fxp r;
} Position;

typedef struct {
    Fxp x, y;
} Scale;

typedef struct {
    Angle x, y, z;
} Rotation;

typedef struct {
    Fxp x, y;
} Vector;

typedef struct {
    Fxp x, y, z;
} Velocity;

typedef struct _BoundingBox
{
    Fxp min_x, min_y;
    Fxp max_x, max_y;
    Fxp width, height;
} BoundingBox;

typedef struct {
    uint16_t asset; // initial sprite index
    uint8_t frame; // current frame
    uint8_t max; // might not be needed
} Animation;

typedef struct {
    Position pos;
    Scale    scl;
    Rotation rot;
    Vector   vec2;
    Velocity vel;
    BoundingBox bbox;
    Fxp mass;
    bool isColliding;
    uint8_t    id;
    uint8_t    frame;
    uint8_t    max;
    bool   visible;
    int    pal_id;
    int    flip;
    uint16_t    mesh;
    uint16_t    zmode;
    Animation anim[2];
} Sprite;

// characters
extern Sprite Ball[maxBalls];
extern uint16_t spritecount;

SRL::Math::Random<int16_t> rnd = SRL::Math::Random<int16_t>(1);

static inline void set_sprite_position(Sprite *sprite) {
    int16_t xPos = rnd.GetNumber(0, screenWidth) - screenWidth/2;
    int16_t yPos = rnd.GetNumber(0, screenHeight) - screenHeight/2;
    
    sprite->pos.x = Fxp(xPos);
    sprite->pos.y = Fxp(yPos);
}

static inline void	my_sprite_draw(Sprite *sprite) {
	FIXED pos[XYZS] = { sprite->pos.x.RawValue(), sprite->pos.y.RawValue(), sprite->pos.z.RawValue(), sprite->scl.x.RawValue() };
	SPR_ATTR attr = SPR_ATTRIBUTE( sprite->id, 0, No_Gouraud, sprite->mesh | Pclpon | HSSoff | ECenb | CL256Bnk, sprite->flip | sprite->zmode );
	slDispSprite(pos, &attr, 0); // faster because it doesn't do a degree-to-angle conversion, which uses floats
}

static inline void	my_sprite_draw_hv(Sprite *sprite) {
	FIXED pos[XYZSS] = { sprite->pos.x.RawValue(), sprite->pos.y.RawValue(), sprite->pos.z.RawValue(), sprite->scl.x.RawValue(), sprite->scl.y.RawValue() };
	SPR_ATTR attr = SPR_ATTRIBUTE( sprite->id, 0, No_Gouraud, sprite->mesh | Pclpon | HSSoff | ECenb | CL256Bnk, sprite->flip | sprite->zmode );
	slDispSpriteHV(pos, &attr, 0); // faster because it doesn't do a degree-to-angle conversion, which uses floats
}