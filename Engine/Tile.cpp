#include "Tile.h"
#include "Graphics.h"
#include "Common.h"

Tile::Tile(Graphics& gfx, BoardController* boardController, Vec2 location, int len, Color clr)
    :
    gfx(gfx),
    boardController (boardController),
    current_location (location),
    len(len),
    clr(clr)
{
    landing_location = current_location;
    new_location = current_location;
}

inline Color Tile::SetColor(int i, int z) const
{
    return ((i == 0) || (z == 0) || (i == len - 1) || (z == len - 1))
        ? Colors::Gray : clr;
}

void Tile::DrawMe(bool draw_landing_as_well, Vec2 offset) const
{
    const Vec2 tile_current_location = (current_location * len) + offset;
    const Vec2 tile_landing_location = (landing_location * len) + offset;

    for (int i = 0; i < len; i++)
    {
        for (int z = 0; z < len; z++)
        {
            gfx.PutPixel(tile_current_location.x + i, tile_current_location.y + z, SetColor(i, z));

            if (draw_landing_as_well) //Could make another function for drawing landing piece but wanted to save the extra for loop...
            {
                if (!((i == 0) || (z == 0) || (i == len - 1) || (z == len - 1))) continue;
                gfx.PutPixel(tile_landing_location.x + i, tile_landing_location.y + z, Colors::White);
            }
        }
    }
}

void Tile::UpdateLocation(Vec2 new_location)
{
    this->current_location = new_location;
}

void Tile::UpdateLandingLocation(Vec2 offset_for_landing_tile)
{
    this->landing_location = current_location + offset_for_landing_tile;
}

bool Tile::IsOffsetPossibleBy(Vec2 offset_location)
{
    new_location += offset_location;

    return boardController->MoveIsPossible(new_location.x, new_location.y);
}

bool Tile::IsRotationPossibleBy(bool rotate_clock_wise, Vec2* center_location, Vec2 offset_location)
{
    Vec2 vr;
    Vec2 vt;

    new_location = current_location;

    vr = new_location - *center_location;

    int rotation_multiplication = (rotate_clock_wise) ? 1 : -1;

    vt.x = (rotation_multiplication)*(-1)* vr.y;
    vt.y = (rotation_multiplication)*vr.x;

    new_location = *center_location + vt + offset_location;

    return boardController->MoveIsPossible(new_location.x, new_location.y);
}

void Tile::ResetNewLocation()
{
    new_location = current_location;
}

void Tile::MoveToNewLocation()
{
    current_location = new_location;
}

void Tile::RootMe()
{
    current_location = landing_location;
}

Vec2 Tile::GetCurrentLocation()
{
    return this->current_location;
}

Vec2* Tile::GetCurrentLocationPtr()
{
    return &this->current_location;
}

const Vec2& Tile::GetLocation() const
{
    return current_location;
}
