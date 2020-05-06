#pragma once
#include "Graphics.h"
#include "Vec2.h"

class Board
{
public:
    Board() = default;
    Board(Vec2i top_left_out, Vec2i top_left_out_boarder_width_offset, Vec2i bottom_right_in, Vec2i bottom_right_in_boarder_width_offset);
    Board(Vec2i top_left_out, Vec2i bottom_right_in)
    {
        Board(top_left_out, Vec2i(0,0), bottom_right_in, Vec2i(0, 0));
    }

    void DrawBoarder(Graphics& gfx);
private:
    Vec2i top_left_out;
    Vec2i top_left_in;
    Vec2i bottom_right_in;
    Vec2i bottom_right_out;
};

