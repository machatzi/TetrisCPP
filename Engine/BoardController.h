#pragma once
#include "Graphics.h"
#include "Common.h"
#include "Sound.h"

class BoardController
{
public:
    BoardController(VectorPosition_t board_offset_location, const int board_width_in_rectangles, const int board_height_in_rectangles, const int board_square_length_in_pixels);

    void ClearCompleteLines();
    void DrawBoard( Graphics& gfx );
    bool MoveIsPossible(int x, int y) const;
    void StoreTile(void* tile);
    void ClearBoard();
    const VectorPosition_t& GetPieceOffset(int indx) const;
private:    
    const VectorPosition_t pieces_offset_location[3] = {
        { 10, 10 },
        { 263, 80 },
        { 100, 300 }
    };
    VectorPosition_t board_offset_location;
    const int board_width_in_rectangles;
    const int board_height_in_rectangles;
    const int board_square_length_in_pixels;
    void*** Board = nullptr;
    Sound LineClear;
    Sound TetrisClear;
    
    bool LocationIsOccupied(int x, int y) const;
    bool IsValidLocation(int x, int y) const;
    bool LineIsComplete(int line_indx) const;
    bool LineIsEmpty(int line_indx) const;
    void RemoveLine(int line_indx);
    void ShiftLinesDown(int line_indx);
};
