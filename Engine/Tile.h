#pragma once
#include "Graphics.h"
#include "BoardController.h"
#include "Common.h"

class Tile
{
public:
    Tile(Graphics& gfx, BoardController& boardController, VectorPosition_t location, int len, Color clr);

    void DrawMe(bool draw_landing_as_well) const;
    void UpdateLocation(int x, int y);
    void UpdateLandingLocation(int y_offset);
    bool IsOffsetPossibleBy(int x_offset, int y_offset);
    bool IsRotationPossibleBy(bool rotate_clock_wise, int center_x, int center_y, int offset_x, int offset_y);
    void ResetNewLocation();
    void MoveToNewLocation();
    void RootMe();
    VectorPosition_t* GetCurrentLocationPtr();
    const VectorPosition_t& GetLocation() const;
private:
    Graphics& gfx;
    BoardController& boardController;
    int len;
    VectorPosition_t current_location;
    VectorPosition_t landing_location;
    VectorPosition_t new_location;
    Color clr;

    Color SetColor(int x, int y) const;
};

