#include "Tile.h"
#include "Graphics.h"
#include "Common.h"

Tile::Tile(Graphics& gfx, BoardController& boardController, VectorPosition_t location, int len, Color clr)
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

void Tile::DrawMe(bool draw_landing_as_well) const
{
    for (int i = 0; i < len; i++)
    {
        for (int z = 0; z < len; z++)
        {
            gfx.PutPixel(len * current_location.x + i, len * current_location.y + z, SetColor(i, z));

            if (draw_landing_as_well) //Could make another function for drawing landing piece but wanted to save the extra for loop...
            {
                if (!((i == 0) || (z == 0) || (i == len - 1) || (z == len - 1))) continue;
                gfx.PutPixel(len * landing_location.x + i, len * landing_location.y + z, Colors::White);
            }
        }
    }
}

void Tile::UpdateLocation(int x, int y)
{
    this->current_location.x = x;
    this->current_location.y = y;
}

void Tile::UpdateLandingLocation(int y_offset)
{
    this->landing_location.y = this->current_location.y + y_offset;
    this->landing_location.x = this->current_location.x;
}

bool Tile::IsOffsetPossibleBy(int x_offset, int y_offset)
{
    new_location.x += x_offset;
    new_location.y += y_offset;

    return boardController.MoveIsPossible(new_location.x, new_location.y);
}

bool Tile::IsRotationPossibleBy(bool rotate_clock_wise, int center_x, int center_y, int offset_x, int offset_y)
{
    VectorPosition_t vr;
    VectorPosition_t vt;

    new_location.x = current_location.x;
    new_location.y = current_location.y;

    vr.x = new_location.x - center_x;
    vr.y = new_location.y - center_y;

    int rotation_multiplication = (rotate_clock_wise) ? 1 : -1;
    vt.x = (rotation_multiplication)*(-1)* vr.y;
    vt.y = (rotation_multiplication)*vr.x;

    new_location.x = center_x + vt.x + offset_x;
    new_location.y = center_y + vt.y + offset_y;

    return boardController.MoveIsPossible(new_location.x, new_location.y);
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

VectorPosition_t* Tile::GetCurrentLocationPtr()
{
    return &this->current_location;
}

const VectorPosition_t& Tile::GetLocation() const
{
    return current_location;
}
