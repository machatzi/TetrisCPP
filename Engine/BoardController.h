#pragma once
#include "Graphics.h"
#include "Common.h"
#include "Sound.h"
#include "Vec2.h"
#include "Board.h"

class BoardController : private Board
{
public:
    BoardController() = default;
    BoardController(Vec2i board_offset_location, const int board_width_in_rectangles, const int board_height_in_rectangles, const int board_square_length_in_pixels, BorderWidths_t borders_width);

    void ClearCompleteLines();
    void DrawBoard( Graphics& gfx );
    bool MoveIsPossible(int location_x, int location_y) const;
    void StoreTile(void* tile);
    void ClearBoard();
    int GetSquareLength() const;
    int GetBoardHeightInRectangles() const;
    int GetBoardWidthInRectangles() const;

    const Vec2i& GetPieceOffset(int indx) const;
private:
    const int boarder_width_top = 13;
    const int boarder_width_left = 7;
    const int boarder_width_right = 7;
    const int boarder_width_bottom = 20;

    const Vec2i boarder_offset_location;

    const int board_width_in_rectangles;
    const int board_height_in_rectangles;
    const int board_square_length_in_pixels;

    int board_width_in_pixels;
    int board_height_in_pixels;
    void*** TetrisTable = nullptr;
    Sound LineClear;
    Sound TetrisClear;
    
    const Vec2i board_offset_location;
    const Vec2i pieces_offset_location[3] = {
       board_offset_location,
        { 395, 80 },
        { 100, 300 }
    };

    //void DrawBoarder( Graphics& gfx );
    bool LocationIsOccupied(int location_x, int location_y) const;
    bool IsValidLocation(int location_x, int location_y) const;
    bool LineIsComplete(int line_indx) const;
    bool LineIsEmpty(int line_indx) const;
    void RemoveLine(int line_indx);
    void ShiftLinesDown(int line_indx);
};
