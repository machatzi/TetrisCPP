#pragma once
#include "Common.h"

class BoardController
{
public:
    BoardController();

    void ClearCompleteLines();
    void DrawBoard();
    bool MoveIsPossible(int x, int y) const;
    void StoreTile(void* tile);
private:
    void* Board[BOARD_WIDTH_IN_RECTANGLES][BOARD_HEIGHT_IN_RECTANGLES] = { nullptr };
    
    bool LocationIsOccupied(int x, int y) const;
    bool IsValidLocation(int x, int y) const;
    bool LineIsComplete(int line_indx) const;
    bool LineIsEmpty(int line_indx) const;
    void RemoveLine(int line_indx);
    void ShiftLinesDown(int line_indx);
};
