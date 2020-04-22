#include "BoardController.h"
#include "Tile.h"

BoardController::BoardController()
{
}

void BoardController::ClearCompleteLines()
{
    for (int y = BOARD_HEIGHT_IN_RECTANGLES - 1; y >= 0; y--)
    {
        if (LineIsEmpty(y))
            break;

        if (LineIsComplete(y))
        {
            RemoveLine(y);
            ShiftLinesDown(y);
            y++; //Need to check again same line due to shifting down
        }
    }
}

bool BoardController::LineIsEmpty(int y_indx) const
{
    for (int x = 0; x < BOARD_WIDTH_IN_RECTANGLES; x++)
    {
        if (Board[x][y_indx] != nullptr)
        {
            return false;
        }
    }
    return true;
}

bool BoardController::LineIsComplete(int y_indx) const
{
    for (int x = 0; x < BOARD_WIDTH_IN_RECTANGLES; x++)
    {
        if (Board[x][y_indx] == nullptr)
        {
            return false;
        }
    }
    return true;
}

void BoardController::RemoveLine(int y_indx)
{
    for (int x = 0; x < BOARD_WIDTH_IN_RECTANGLES; x++)
    {
        delete Board[x][y_indx];
        Board[x][y_indx] = nullptr;
    }
}

void BoardController::ShiftLinesDown(int y_indx)
{
    for (int y = y_indx - 1; y >= 0 ; y--)
    {
        for (int x = 0; x < BOARD_WIDTH_IN_RECTANGLES; x++)
        {
            Board[x][y + 1] = Board[x][y];

            if (Board[x][y])
            {
                static_cast<Tile*>(Board[x][y])->UpdateLocation(x, y + 1);
                Board[x][y] = nullptr;
            }
        }
    }
}

void BoardController::DrawBoard()
{
    for (int x = 0; x < BOARD_WIDTH_IN_RECTANGLES; x++)
    {
        for (int y = 0; y < BOARD_HEIGHT_IN_RECTANGLES; y++)
        {
            if (Board[x][y] != nullptr)
                static_cast<Tile*>(Board[x][y])->DrawMe(false);
        }
    }
}

bool BoardController::MoveIsPossible(int x, int y) const
{
    return (IsValidLocation(x, y) && !LocationIsOccupied(x, y));
}

void BoardController::StoreTile(void* tile)
{
    VectorPosition_t* position = static_cast<Tile *>(tile)->GetCurrentLocationPtr();

    Board[position->x][position->y] = tile;
}

bool BoardController::LocationIsOccupied(int x, int y) const
{
    return (Board[x][y] != nullptr);
}

bool BoardController::IsValidLocation(int x, int y) const
{
    return ((x < BOARD_WIDTH_IN_RECTANGLES && x >= 0) &&
        (y < BOARD_HEIGHT_IN_RECTANGLES && y >= 0));
}
