#pragma once
#include "Graphics.h"
#include "BoardController.h"
#include "Common.h"
#include "Vec2.h"

class Tile
{
public:
    Tile(Graphics& gfx, BoardController* boardController, Vec2i location, int len, Color clr);

    void DrawMe(bool draw_landing_as_well, Vec2i offset) const;
    void UpdateLocation(Vec2i new_location);
    void UpdateLandingLocation(Vec2i offset_for_landing_tile);
    bool IsOffsetPossibleBy(Vec2i offset_location);
    bool IsRotationPossibleBy(bool rotate_clock_wise, Vec2i* center_location, Vec2i offset_location);
    void ResetNewLocation();
    void MoveToNewLocation();
    void RootMe();
    Vec2i GetCurrentLocation();
    Vec2i* GetCurrentLocationPtr();
    const Vec2i& GetLocation() const;
private:
    Graphics& gfx;
    BoardController* boardController;
    int len;
    Vec2i current_location;
    Vec2i landing_location;
    Vec2i new_location;
    Color clr;

    Color SetColor(int x, int y) const;
};

