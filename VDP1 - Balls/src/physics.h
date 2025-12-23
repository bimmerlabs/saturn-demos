#pragma once
#include <srl.hpp>
#include "sprites.h"

#define MIN_VELOCITY_X Fxp(7)
#define MIN_VELOCITY_Y Fxp(3)
#define MAX_VELOCITY_Z Fxp(70) // originally 70
#define MEDIUM_MAX_VELOCITY Fxp(10.5) // 8 = easy, 10 = medium, 13 = hard?
#define BALL_FRICTION_Y Fxp(1.75)
#define BALL_FRICTION_X Fxp(1.15)
#define BALL_ROTATION Fxp(1.7) // IDEA:  PICK UP A BOOMERANG ITEM - MAKE THIS NUMBER HIGHER?
#define REBOUND Fxp(0.1) // the lower this is, the bigger the rebound?
#define FRICTION_COEFFICIENT Fxp(0.01) // Adjust this value to alter the ball curve
#define ITEM_RADIUS 32

#define Fxp_0 Fxp(0)
#define Fxp_1 Fxp(1)
#define Fxp_360 Fxp(360)

using namespace SRL::Types;
using namespace SRL::Math::Types;

static Fxp maxBallVelocity = 0.0;

#ifdef SRL_HIGH_RES
static const uint8_t maxspeed = 12;
static const Fxp screenLeft   = -352;
static const Fxp screenRight  = 352;
static const Fxp screenTop    = -240;
static const Fxp screenBottom = 240;
#else
static const uint16_t maxspeed = 3;
static const Fxp screenLeft   = -176;
static const Fxp screenRight  = 176;
static const Fxp screenTop    = -112;
static const Fxp screenBottom = 112;
#endif

// Function to initialize the ball's movement
static inline void start_ball_movement(Sprite *ball) {    
    maxBallVelocity = MEDIUM_MAX_VELOCITY;
    int16_t xVel = rnd.GetNumber(-maxspeed, maxspeed);
    int16_t yVel = rnd.GetNumber(-maxspeed, maxspeed);
    ball->vel.x = Fxp(xVel);
    ball->vel.y = Fxp(yVel);
}

// // Function to update the ball's position and check for collisions (ORIGINAL)
// static inline void update_ball(Sprite *ball) {
    // // Update position based on velocity
    // ball->pos.x += ball->vel.x;
    // ball->pos.y += ball->vel.y;
    
    // // Check for collisions with walls
    // if (ball->pos.x > screenRight) {
        // // ball->pos.x = screenRight;
        // ball->vel.x = -ball->vel.x; // Reverse X velocity  
    // }
    // if (ball->pos.x < screenLeft) {
        // // ball->pos.x = screenleft;
        // ball->vel.x = -ball->vel.x; // Reverse X velocity      
    // }
    // if (ball->pos.y > screenBottom) {
        // // ball->pos.y = screenBottom;
        // ball->vel.y = -ball->vel.y; // Reverse Y velocity
    // }
    // if (ball->pos.y < screenTop) {
        // // ball->pos.y = screenTop;
        // ball->vel.y = -ball->vel.y; // Reverse Y velocity
    // }
// }

// // slower with my draw call, faster with lines?
// static inline void update_ball(Sprite *ball)
// {
    // ball->pos.x += ball->vel.x;
    // ball->pos.y += ball->vel.y;

    // if (ball->pos.x > screenRight)
    // {
        // ball->vel.x = -ball->vel.x;
    // }
    // else if (ball->pos.x < screenLeft)
    // {
        // ball->vel.x = -ball->vel.x;
    // }

    // if (ball->pos.y > screenBottom)
    // {
        // ball->vel.y = -ball->vel.y;
    // }
    // else if (ball->pos.y < screenTop)
    // {
        // ball->vel.y = -ball->vel.y;
    // }
// }

// // this is waaaaay slower then my original loop
// static inline void update_ball(Sprite *ball)
// {
    // auto x = ball->pos.x + ball->vel.x;
    // auto y = ball->pos.y + ball->vel.y;

    // auto vx = ball->vel.x;
    // auto vy = ball->vel.y;

    // if (x > screenRight || x < screenLeft)
        // vx = -vx;

    // if (y > screenBottom || y < screenTop)
        // vy = -vy;

    // ball->pos.x = x;
    // ball->pos.y = y;
    // ball->vel.x = vx;
    // ball->vel.y = vy;
// }

// // about the same as my original method
// static inline void update_ball(Sprite *ball)
// {
    // ball->pos.x += ball->vel.x;
    // ball->pos.y += ball->vel.y;

    // const bool hitX =
        // (ball->pos.x > screenRight) |
        // (ball->pos.x < screenLeft);

    // const bool hitY =
        // (ball->pos.y > screenBottom) |
        // (ball->pos.y < screenTop);

    // if (hitX) ball->vel.x = -ball->vel.x;
    // if (hitY) ball->vel.y = -ball->vel.y;
// }

// fastest so far with linedraw
static inline void update_ball(Sprite* ball)
{
    ball->pos.x += ball->vel.x;
    ball->pos.y += ball->vel.y;

    if (ball->pos.x > screenRight || ball->pos.x < screenLeft)
    {
        ball->vel.x = -ball->vel.x;
    }

    if (ball->pos.y > screenBottom || ball->pos.y < screenTop)
    {
        ball->vel.y = -ball->vel.y;
    }
}

// // slightly faster than original, slower than the above
// static inline void update_ball(Sprite* ball)
// {
    // ball->pos.x += ball->vel.x;
    // ball->pos.y += ball->vel.y;

    // const bool flipX =
        // (ball->pos.x > screenRight) |
        // (ball->pos.x < screenLeft);

    // const bool flipY =
        // (ball->pos.y > screenBottom) |
        // (ball->pos.y < screenTop);

    // if (flipX) ball->vel.x = -ball->vel.x;
    // if (flipY) ball->vel.y = -ball->vel.y;
// }