#include "Board.h"

Board::Board(Vec2i top_left_out, Vec2i top_left_out_boarder_width_offset, Vec2i bottom_right_in, Vec2i bottom_right_in_boarder_width_offset)
    :
    top_left_out (top_left_out),
    top_left_in (top_left_out + top_left_out_boarder_width_offset),
    bottom_right_in (bottom_right_in),
    bottom_right_out (bottom_right_in + bottom_right_in_boarder_width_offset)
{
}

void Board::DrawBoarder(Graphics& gfx)
{
    // Draw the TOP boarder
    for (int y = top_left_out.y; y <= top_left_in.y; y++)
    {
        for (int x = top_left_out.x; x < bottom_right_out.x; x++)
            gfx.PutPixel(x, y, Colors::DarkBlue);
    }

    // Draw the BOTTOM boarder
    for (int y = bottom_right_in.y; y <= bottom_right_out.y; y++)
    {
        for (int x = top_left_out.x; x < bottom_right_out.x; x++)
            gfx.PutPixel(x, y, Colors::DarkBlue);
    }

    //DRAW THE SIDE BOARDERS
    for (int y = top_left_in.y; y <= bottom_right_in.y; y++)
    {
        //LEFT
        for (int x = top_left_out.x; x < top_left_in.x; x++)
            gfx.PutPixel(x, y, Colors::DarkBlue);

        //RIGHT
        for (int x = bottom_right_in.x; x < bottom_right_out.x; x++)
            gfx.PutPixel(x, y, Colors::DarkBlue);
    }
}
