#include <srl.hpp>
#include <tmsf.hpp>
#include "sprites.h"
#include "physics.h"
#include "vdp2/balls.pal"

#define PaletteID (0)

// tmsf format loads in alphabetical order
enum
{
    BALLS_02X01 = 0, // ILLEGAL!!!!
    BALLS_02X02,     // ILLEGAL!!!!
    BALLS_03X03,     // ILLEGAL!!!!
    BALLS_04X04,     // ILLEGAL!!!!
    BALLS_08X08,
    BALLS_16X16,
    BALLS_24X24,
    BALLS_32X32,
    BALLS_48X48,
    BALLS_64X64,
} BALL_SPRITES;// tmsf format loads in alphabetical order

using namespace SRL::Types;
using namespace SRL::Math::Types;
using namespace SRL::Input;

static uint16_t currentBalls;
static uint8_t currentTilemap = 0;

Sprite Ball[maxBalls] = {};

SRL::CRAM::Palette LoadSpritePalette(uint16_t* palData)
{
    SRL::CRAM::TextureColorMode mode = SRL::CRAM::TextureColorMode::Paletted256;

    int32_t id = 0;

    SRL::CRAM::Palette cramPalette(mode, id);

    if (cramPalette.Load((SRL::Types::HighColor*)palData, 256) >= 0)
    {
        SRL::CRAM::SetBankUsedState(id, mode, true);
    }
    return cramPalette;
}

uint16_t* init_game_palette(void)
{
    SRL::CRAM::Palette gamePalette  = LoadSpritePalette(game_pal);
    return game_pal;
}

using Trig = SRL::Math::Trigonometry;

static bool EndCodeDisable = true;
static bool HSSEnable = true;
static bool PreClipDisable = true;
static bool ScaledSprite = false;
uint8_t DrawMode = SrlPolygonDraw; // use SRL draw routines, or SGL raw
bool PausePhysics = false;
static bool FilledPolygon = true;
static uint8_t spriteid = 0;

Fxp PolygonSize = 1;
bool DrawPolygon = false;

static SPRITE polygon[maxBalls];

static inline void getInputs(Digital &port0, TilemapObject* Balls) {
    switch (port0.IsHeld(Digital::Button::Up))
    {
        case true:
        {
            currentBalls++;
            if (currentBalls >= maxBalls)
                currentBalls = maxBalls - 1;
            SRL::Debug::Print(2, 2, "Sprites: %d  ", currentBalls);
            break;
        }
        default:
            break;
    }
    switch (port0.IsHeld(Digital::Button::Down))
    {
        case true:
        {
            currentBalls--;
            if (currentBalls < 1)
                currentBalls = 1;
            SRL::Debug::Print(2, 2, "Sprites: %d  ", currentBalls);
            break;
        }
        default:
            break;
    }

    if (port0.WasPressed(Digital::Button::Left))
    {
        spriteid = 0;
        if (currentTilemap > 0)
            currentTilemap--;

        switch (currentTilemap)
        {
            case BALLS_48X48:
            {
                SRL::Debug::Print(2, 3, "Size: 48x48");
                PolygonSize = 47;
                break;
            }
            case BALLS_32X32:
            {
                SRL::Debug::Print(2, 3, "Size: 32x32");
                PolygonSize = 31;
                break;
            }
            case BALLS_24X24:
            {
                SRL::Debug::Print(2, 3, "Size: 24x24");
                PolygonSize = 23;
                break;
            }
            case BALLS_16X16:
            {
                SRL::Debug::Print(2, 3, "Size: 16x16");
                PolygonSize = 15;
                break;
            }
            case BALLS_08X08:
            {
                SRL::Debug::Print(2, 3, "Size: 8x8  ");
                PolygonSize = 7;
                break;
            }
            case BALLS_04X04:
            {
                SRL::Debug::Print(2, 3, "Size: 4x4  ");
                PolygonSize = 3;
                break;
            }
            case BALLS_03X03:
            {
                SRL::Debug::Print(2, 3, "Size: 3x3  ");
                PolygonSize = 2;
                break;
            }
            case BALLS_02X02:
            {
                SRL::Debug::Print(2, 3, "Size: 2x2  ");
                PolygonSize = 1;
                DrawPolygon = true;
                break;
            }
            case BALLS_02X01:
            {
                SRL::Debug::Print(2, 3, "Size: 2x1  ");
                DrawPolygon = false;
                break;
            }
            default:
                break;
        }
        
        for (uint16_t i = 0; i < maxBalls; i++)
        {
            Ball[i].id = Balls->sprite[currentTilemap].SpriteIndex + spriteid;
            spriteid++;
            if (spriteid > 6)
                spriteid = 0;                
            if (DrawMode == SrlPolygonDraw && !DrawPolygon)
            {
                polygon[i] = SRL::Scene2D::GetSpriteCommand(SRL::Scene2D::CommandType::LineSegment, Ball[i].color);
            }
        }
    }

    if (port0.WasPressed(Digital::Button::Right))
    {
        spriteid = 0;
        if (currentTilemap < BALLS_64X64)
            currentTilemap++;

        uint16_t visibleBalls = 0;
        
        switch (currentTilemap)
        {
            case BALLS_64X64:
            {
                SRL::Debug::Print(2, 3, "Size: 64x64");
                PolygonSize = 63;
                visibleBalls = 90;
                break;
            }
            case BALLS_48X48:
            {
                SRL::Debug::Print(2, 3, "Size: 48x48");
                PolygonSize = 47;
                visibleBalls = 145;
                break;
            }
            case BALLS_32X32:
            {
                SRL::Debug::Print(2, 3, "Size: 32x32");
                PolygonSize = 31;
                visibleBalls = 285;
                break;
            }
            case BALLS_24X24:
            {
                SRL::Debug::Print(2, 3, "Size: 24x24");
                PolygonSize = 23;
                visibleBalls = 435;
                break;
            }
            case BALLS_16X16:
            {
                SRL::Debug::Print(2, 3, "Size: 16x16");
                PolygonSize = 15;
                visibleBalls = 680;
                break;
            }
            case BALLS_08X08:
            {
                SRL::Debug::Print(2, 3, "Size: 8x8  ");
                PolygonSize = 7;
                visibleBalls = maxBalls;
                break;
            }
            case BALLS_04X04:
            {
                SRL::Debug::Print(2, 3, "Size: 4x4  ");
                PolygonSize = 3;
                visibleBalls = maxBalls;
                break;
            }
            case BALLS_03X03:
            {
                SRL::Debug::Print(2, 3, "Size: 3x3  ");
                PolygonSize = 2;
                visibleBalls = maxBalls;
                break;
            }
            case BALLS_02X02:
            {
                SRL::Debug::Print(2, 3, "Size: 2x2  ");
                PolygonSize = 1;
                visibleBalls = maxBalls;
                DrawPolygon = true;
                break;
            }
            default:
                break;
        }
        
        if (currentBalls > visibleBalls)
        {
            currentBalls = visibleBalls;
            SRL::Debug::Print(2, 2, "Sprites: %d  ", currentBalls);
        }
        
        for (uint16_t i = 0; i < maxBalls; i++)
        {
            Ball[i].id = Balls->sprite[currentTilemap].SpriteIndex + spriteid;
            spriteid++;
            if (spriteid > 6)
                spriteid = 0;                
            if (DrawMode == SrlPolygonDraw)
            {                
                if (DrawPolygon)
                {
                    polygon[i] = SRL::Scene2D::GetSpriteCommand(FilledPolygon ? SRL::Scene2D::CommandType::Polygon : SRL::Scene2D::CommandType::PolyLine, Ball[i].color);
                }
            }
        }
    }

    if (port0.WasPressed(Digital::Button::START))
    {
        PausePhysics = !PausePhysics;
        if (!PausePhysics)
        {
            SRL::Debug::Print(2, 6, "                ");
        }
        else if (PausePhysics)
        {
            SRL::Debug::Print(2, 6, "Pause Physics...");
        }
    }

    // // Check triggers
    // if (port0.IsHeld(Digital::Button::L))
    // {
    // }

    // if (port0.IsHeld(Digital::Button::R))
    // {
    // }

    if (port0.WasPressed(Digital::Button::A))
    {
        DrawMode++;
        if (DrawMode > SrlPolygonDraw)
            DrawMode = DirectSpriteDraw;
        if (DrawMode == SrlPolygonDraw)
        {
            SRL::Debug::Print(2, 4, "Renderer: SRL (polygon)");
        }
        else if (DrawMode == SrlSpriteDraw)
        {
            SRL::Debug::Print(2, 4, "Renderer: SRL (default) ");
        }
        else if (DrawMode == DirectSpriteDraw)
        {
            SRL::Debug::Print(2, 4, "Renderer: SGL (direct)  ");
        }
    }

    // if (port0.WasPressed(Digital::Button::B))
    // {
    // }
    
    if (port0.WasPressed(Digital::Button::C))
    {
        ScaledSprite = !ScaledSprite;
        SRL::Debug::Print(2, 5, ScaledSprite ? "Scaled Sprite: Yes" : "Scaled Sprite: No ");
        if (ScaledSprite)
        {
            for (uint16_t i = 0; i < maxBalls; i++) {
                #ifdef SRL_HIGH_RES
                Ball[i].scl = {Fxp(2.0), Fxp(2.0)};
                #elif SRL_HIGH_RES_NON_INTERLACED 
                Ball[i].scl = {Fxp(2.0), Fxp(1.0)};
                #else
                Ball[i].scl = {Fxp(0.5), Fxp(0.5)};
                #endif
            }
        }
        else {
            for (uint16_t i = 0; i < maxBalls; i++) {
                #ifdef SRL_HIGH_RES
                Ball[i].scl = {Fxp(1.0), Fxp(1.0)};
                #elif SRL_HIGH_RES_NON_INTERLACED 
                Ball[i].scl = {Fxp(1.0), Fxp(0.5)};
                #else
                Ball[i].scl = {Fxp(1.0), Fxp(1.0)};
                #endif
            }            
        }
    }
    
    if (port0.WasPressed(Digital::Button::X) && DrawPolygon)
    {
        FilledPolygon = !FilledPolygon;
        for (uint16_t i = 0; i < maxBalls; i++)
        {
            polygon[i] = SRL::Scene2D::GetSpriteCommand(FilledPolygon ? SRL::Scene2D::CommandType::Polygon : SRL::Scene2D::CommandType::PolyLine, Ball[i].color);
        }
    }
    // these don't have any measurable effect in this test, so disabling
    // if (port0.WasPressed(Digital::Button::Y))
    // {
        // PreClipDisable = !PreClipDisable;
        // SRL::Scene2D::SetEffect(SRL::Scene2D::SpriteEffect::DisablePreClip, PreClipDisable);
        // SRL::Debug::Print(2, 5, PreClipDisable ? "Preclip: On " : "Preclip: Off");
    // }
    // if (port0.WasPressed(Digital::Button::Z))
    // {
        // HSSEnable = !HSSEnable;
        // SRL::Scene2D::SetEffect(SRL::Scene2D::SpriteEffect::EnableHSS, HSSEnable);
        // SRL::Debug::Print(2, 6, HSSEnable ? "HSS: On " : "HSS: Off");
    // }
}

int main()
{
	SRL::Core::Initialize(HighColor::Colors::Black);
	
	Digital port0(0);
	
    SRL::Scene2D::SetEffect(SRL::Scene2D::SpriteEffect::EnableECD, EndCodeDisable);
    
	// also need to make Nbg0 work in 704x240p
	#ifdef SRL_HIGH_RES
    slZoomNbg0(toFIXED(0.50), toFIXED(0.5));
    #endif
    
    Vector2D point = Vector2D(0, 0);
    auto defaultColor = 1;
    init_game_palette();
    
    TilemapObject* Balls;

    Balls = new TilemapObject("BALLS.TM", PaletteID, false);
        
    for (uint16_t i = 0; i < maxBalls; i++) {
        Ball[i].pos = {Fxp(0), Fxp(0), Fxp(100), Fxp(32), Fxp(0), Fxp(0)};
        #ifdef SRL_HIGH_RES_NON_INTERLACED 
        Ball[i].scl = {Fxp(1.0), Fxp(0.5)};
        #else
        Ball[i].scl = {Fxp(1.0), Fxp(1.0)};
        #endif
        Ball[i].rot = {0, 0, 0};
        Ball[i].vec2 = {Fxp(0), Fxp(0)};
        Ball[i].vel = {Fxp(0), Fxp(0), Fxp(0)};
        Ball[i].id = 0;
        Ball[i].visible = true;
        Ball[i].pal_id = 0;
        Ball[i].flip = sprNoflip;
        Ball[i].mesh = MESHoff;
        Ball[i].zmode = _ZmCC;
        Ball[i].id = Balls->sprite[0].SpriteIndex + spriteid;
        
        set_sprite_position(&Ball[i]);
        start_ball_movement(&Ball[i]);
        
        switch (spriteid)
        {
            case 0:
            {
                Ball[i].color = 6;
                break;
            }
            case 1:
            {
                Ball[i].color = 12;
                break;
            }
            case 2:
            {
                Ball[i].color = 18;
                break;
            }
            case 3:
            {
                Ball[i].color = 24;
                break;
            }
            case 4:
            {
                Ball[i].color = 30;
                break;
            }
            case 5:
            {
                Ball[i].color = 36;
                break;
            }
            case 6:
            {
                Ball[i].color = 46;
                break;
            }
            default:
                break;
        }
        
        polygon[i] = SRL::Scene2D::GetSpriteCommand(SRL::Scene2D::CommandType::LineSegment, Ball[i].color);
        
        spriteid++;
        if (spriteid > 6)
            spriteid = 0;
    }
    
    currentBalls = 750;
    
    SRL::Debug::Print(2, 1, "Resolution: %dx%d", screenWidth, screenHeight);
    SRL::Debug::Print(2, 2, "Sprites: %d  ", currentBalls);
    SRL::Debug::Print(2, 3, "Size: 2x1");
    SRL::Debug::Print(2, 4, "Renderer: SRL (polygon)");
    SRL::Debug::Print(2, 5, ScaledSprite ? "Scaled Sprite: Yes" : "Scaled Sprite: No ");
    
	while(1)
	{   
        for (uint16_t i = 0; i < currentBalls; i++) {
            update_ball(&Ball[i], polygon[i]);
            switch (DrawMode)
            {
                case SrlPolygonDraw:
                {
                    SRL::Scene2D::Draw(
                        &polygon[i],
                        500
                    );
                    break;
                }
                case SrlSpriteDraw:
                {
                    SRL::Scene2D::DrawSprite(
                        Ball[i].id, 
                        Vector3D(
                            Ball[i].pos.x,
                            Ball[i].pos.y,
                            Ball[i].pos.z),
                        Vector2D(
                            Ball[i].scl.x,
                            Ball[i].scl.y)
                    );
                    break;
                }
                default:                
                {
                    my_sprite_draw(&Ball[i]);
                    break;
                }
            }
        }
        
        getInputs(port0, Balls);      
          
        SRL::Core::Synchronize();
	}

	return 0;
}
