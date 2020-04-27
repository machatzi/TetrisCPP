#pragma once
#include "Graphics.h"
#include "Common.h"
#include "Sound.h"
#include "Vec2.h"

class BoardController
{
public:
    BoardController() = default;
    BoardController(Vec2 board_offset_location, const int board_width_in_rectangles, const int board_height_in_rectangles, const int board_square_length_in_pixels);

    void ClearCompleteLines();
    void DrawBoard( Graphics& gfx );
    bool MoveIsPossible(Vec2 location) const;
    void StoreTile(void* tile);
    void ClearBoard();
    int GetSquareLength() const;
    int GetBoardHeightInRectangles() const;
    int GetBoardWidthInRectangles() const;

    const Vec2& GetPieceOffset(int indx) const;
private:    
    const Vec2 board_offset_location;
    const Vec2 pieces_offset_location[3] = {
       board_offset_location,
        { 325, 80 },
        { 100, 300 }
    };
    const int board_width_in_rectangles;
    const int board_height_in_rectangles;
    const int board_square_length_in_pixels;
    void*** Board = nullptr;
    Sound LineClear;
    Sound TetrisClear;
    
    bool LocationIsOccupied(Vec2 location) const;
    bool IsValidLocation(Vec2 location) const;
    bool LineIsComplete(int line_indx) const;
    bool LineIsEmpty(int line_indx) const;
    void RemoveLine(int line_indx);
    void ShiftLinesDown(int line_indx);
};
