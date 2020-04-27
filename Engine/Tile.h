#pragma once
#include "Graphics.h"
#include "BoardController.h"
#include "Common.h"
#include "Vec2.h"

class Tile
{
public:
    Tile(Graphics& gfx, BoardController* boardController, Vec2 location, int len, Color clr);

    void DrawMe(bool draw_landing_as_well, int x_offset, int y_offset) const;
    void UpdateLocation(int x, int y);
    void UpdateLandingLocation(int y_offset);
    bool IsOffsetPossibleBy(int x_offset, int y_offset);
    bool IsRotationPossibleBy(bool rotate_clock_wise, int center_x, int center_y, int offset_x, int offset_y);
    void ResetNewLocation();
    void MoveToNewLocation();
    void RootMe();
    Vec2* GetCurrentLocationPtr();
    const Vec2& GetLocation() const;
private:
    Graphics& gfx;
    BoardController* boardController;
    int len;
    Vec2 current_location;
    Vec2 landing_location;
    Vec2 new_location;
    Color clr;

    Color SetColor(int x, int y) const;
};

