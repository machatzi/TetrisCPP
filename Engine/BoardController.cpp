#include "BoardController.h"
#include "Tile.h"

BoardController::BoardController(Vec2i board_offset_location, const int board_width_in_rectangles, const int board_height_in_rectangles, const int board_square_length_in_pixels, BorderWidths_t borders_width)
    :
    boarder_offset_location(board_offset_location),
    board_offset_location( board_offset_location + Vec2i(borders_width.left, borders_width.top) ),
    board_width_in_rectangles (board_width_in_rectangles),
    board_height_in_rectangles (board_height_in_rectangles),
    board_square_length_in_pixels (board_square_length_in_pixels),
    board_width_in_pixels (board_width_in_rectangles* board_square_length_in_pixels),
    board_height_in_pixels (board_height_in_rectangles* board_square_length_in_pixels),
    Board(board_offset_location, Vec2i(borders_width.left, borders_width.top), board_offset_location + Vec2i(board_width_in_rectangles, board_height_in_rectangles)* board_square_length_in_pixels, Vec2i(borders_width.right, borders_width.bottom))
{
    TetrisTable = new void** [board_width_in_rectangles];
    for (int i = 0; i < board_width_in_rectangles; ++i) {
        TetrisTable[i] = new void*[board_height_in_rectangles];
    }

    for (int i = 0; i < board_width_in_rectangles; i++)
        for (int z = 0; z < board_height_in_rectangles; z++)
            TetrisTable[i][z] = nullptr;

    LineClear = Sound(L"Media\\line.wav");
    TetrisClear = Sound(L"Media\\se_game_tetris.wav");
}

void BoardController::ClearCompleteLines()
{
    int lines_cleared = 0;
    for (int y = board_height_in_rectangles - 1; y >= 0; y--)
    {
        if (LineIsEmpty(y))
            break;

        if (LineIsComplete(y))
        {
            lines_cleared++;
            RemoveLine(y);
            ShiftLinesDown(y);
            y++; //Need to check again same line due to shifting down
        }
    }
    if (lines_cleared > 0)
    {
        if (lines_cleared == 4)
            TetrisClear.Play();
        else
            LineClear.Play();
    }
}

bool BoardController::LineIsEmpty(int y_indx) const
{
    for (int x = 0; x < board_width_in_rectangles; x++)
    {
        if (TetrisTable[x][y_indx] != nullptr)
        {
            return false;
        }
    }
    return true;
}

bool BoardController::LineIsComplete(int y_indx) const
{
    for (int x = 0; x < board_width_in_rectangles; x++)
    {
        if (TetrisTable[x][y_indx] == nullptr)
        {
            return false;
        }
    }
    return true;
}

void BoardController::RemoveLine(int y_indx)
{
    for (int x = 0; x < board_width_in_rectangles; x++)
    {
        delete TetrisTable[x][y_indx];
        TetrisTable[x][y_indx] = nullptr;
    }
}

void BoardController::ShiftLinesDown(int y_indx)
{
    for (int y = y_indx - 1; y >= 0 ; y--)
    {
        for (int x = 0; x < board_width_in_rectangles; x++)
        {
            TetrisTable[x][y + 1] = TetrisTable[x][y];

            if (TetrisTable[x][y])
            {
                static_cast<Tile*>(TetrisTable[x][y])->UpdateLocation(Vec2i(x, y + 1));
                TetrisTable[x][y] = nullptr;
            }
        }
    }
}

void BoardController::DrawBoard( Graphics& gfx )
{
    DrawBoarder(gfx);

    for (int x = 0; x < board_width_in_rectangles; x++)
    {
        for (int y = 0; y < board_height_in_rectangles; y++)
        {
            if (TetrisTable[x][y] != nullptr)
                static_cast<Tile*>(TetrisTable[x][y])->DrawMe(false, board_offset_location);
        }
    }
}

bool BoardController::MoveIsPossible(int location_x, int location_y) const
{
    return (IsValidLocation(location_x, location_y) && !LocationIsOccupied(location_x, location_y));
}

void BoardController::StoreTile(void* tile)
{
    Vec2i position = static_cast<Tile *>(tile)->GetCurrentLocation();

    TetrisTable[position.x][position.y] = tile;
}

void BoardController::ClearBoard()
{
    for (int x = 0; x < board_width_in_rectangles; x++)
    {
        for (int y = 0; y < board_height_in_rectangles; y++)
        {
            if (TetrisTable[x][y] != nullptr)
            {
                delete TetrisTable[x][y];
                TetrisTable[x][y] = nullptr;
            }
        }
    }
}

int BoardController::GetSquareLength() const
{
    return board_square_length_in_pixels;
}

int BoardController::GetBoardHeightInRectangles() const
{
    return board_height_in_rectangles;
}

int BoardController::GetBoardWidthInRectangles() const
{
    return board_width_in_rectangles;
}


const Vec2i& BoardController::GetPieceOffset(int indx) const
{
    // TODO: insert return statement here
    return pieces_offset_location[indx];
}

bool BoardController::LocationIsOccupied(int location_x, int location_y) const
{
    return (TetrisTable[location_x][location_y] != nullptr);
}

bool BoardController::IsValidLocation(int location_x, int location_y) const
{
    return ((location_x < board_width_in_rectangles && location_x >= 0) &&
        (location_y < board_height_in_rectangles && location_y >= 0));
}
