#pragma once
#include "Graphics.h"
#include "BoardController.h"
#include "Common.h"
#include "Vec2.h"

class Tile
{
public:
    Tile(Graphics& gfx, BoardController* boardController, Vec2 location, int len, Color clr);

    void DrawMe(bool draw_landing_as_well, Vec2 offset) const;
    void UpdateLocation(Vec2 new_location);
    void UpdateLandingLocation(Vec2 offset_for_landing_tile);
    bool IsOffsetPossibleBy(Vec2 offset_location);
    bool IsRotationPossibleBy(bool rotate_clock_wise, Vec2* center_location, Vec2 offset_location);
    void ResetNewLocation();
    void MoveToNewLocation();
    void RootMe();
    Vec2 GetCurrentLocation();
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

