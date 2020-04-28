#include "PieceController.h"


PieceController::PieceController(Graphics& gfx, BoardController* boardController)
    :
    gfx(gfx),
    boardController(boardController)
{
    RotateSnd = Sound(L"Media\\se_game_rotate.wav");
    FallSnd = Sound(L"Media\\fall.wav");
    BruteFall = Sound(L"Media\\se_game_bfall.wav");
}

void PieceController::Init()
{
    if (next_piece)
    {
        delete next_piece;
        next_piece = NULL;
    }
    if (active_piece)
    {
        delete active_piece;
        active_piece = NULL;
    }
}

bool PieceController::SpawnNextPiece()
{
    if (active_piece)
        return true;

    if (next_piece == NULL) //This can only happen in beginning of game
    {
        GenerateNextPiece();
    }
    active_piece = next_piece;
    next_piece = NULL;

    if (!PieceCanBePlacedOnBoard())
    {
        return false;
    }

    GenerateNextPiece();

    UpdateActivePieceLandingLocation();
    return true;
}

void PieceController::DrawActivePiece()
{
    const static Vec2& active_piece_offset = boardController->GetPieceOffset(0);

    if (active_piece)
    {
        DrawPiece(active_piece, active_piece_offset.x, active_piece_offset.y, true);
    }
}

void PieceController::DrawNextPieces()
{
    const static Vec2& next_piece_offset = boardController->GetPieceOffset(1);

    if (next_piece)
    {
        DrawPiece(next_piece, next_piece_offset.x, next_piece_offset.y, false);
    }
}

void PieceController::GenerateNextPiece()
{
    const int sqr_length = boardController->GetSquareLength();

    next_piece = new Piece();

    next_piece->piece_type = static_cast<PieceShape>(rand() % static_cast<int>(PieceShape::NUMBER_OF_SHAPES));
    
    next_piece->offset_data = getOffsetData(next_piece->piece_type);

    int shape_index = static_cast<int>(next_piece->piece_type);

    for (int i = 0; i < TETRAMINO_NUMBER_OF_TILES; i++)
    {
        next_piece->tiles[i] = new Tile(gfx, boardController, spawn_positions[shape_index][i].spawn_location, sqr_length, ShapeInitColors[shape_index]);

        if (spawn_positions[shape_index][i].center_rotation_tile)
        {
            next_piece->centered_tile_location_ptr = next_piece->tiles[i]->GetCurrentLocationPtr();
        }
    }
}

void PieceController::ResetPiece()
{
    for (int i = 0; i < TETRAMINO_NUMBER_OF_TILES; i++)
    {
        if (active_piece->tiles[i])
        {
            active_piece->tiles[i]->ResetNewLocation();
        }
    }
}

void PieceController::MovePieceToNewLocation()
{
    for (int i = 0; i < TETRAMINO_NUMBER_OF_TILES; i++)
    {
        if (active_piece->tiles[i])
        {
            active_piece->tiles[i]->MoveToNewLocation();
        }
    }
    UpdateActivePieceLandingLocation();
}

bool PieceController::PieceCanBePlacedOnBoard()
{
    for (int i = 0; i < TETRAMINO_NUMBER_OF_TILES; i++)
    {
        if (active_piece->tiles[i])
        {
            const Vec2& tile_location = active_piece->tiles[i]->GetLocation();
            if (!boardController->MoveIsPossible(tile_location))
                return false;
        }
    }

    return true;
}

void PieceController::DrawPiece(Piece * piece, int x_offset, int y_offset, bool draw_landing_piece_as_well) const
{
    if (piece == NULL)
        return;

    for (int i = 0; i < TETRAMINO_NUMBER_OF_TILES; i++)
    {
        if (piece->tiles[i])
        {
            piece->tiles[i]->DrawMe(draw_landing_piece_as_well, x_offset, y_offset);
        }
    }
}

void PieceController::MovePiece(MoveDirection direction)
{
    if (active_piece == NULL)
        return;

    Vec2 offset_location(1, 0);

    switch (direction)
    {
    case MoveDirection::RIGHT:
        offset_location = Vec2(1, 0);
        break;
    case MoveDirection::LEFT:
        offset_location = Vec2(-1, 0);
        break;
    case MoveDirection::DOWN:
        offset_location = Vec2(0, 1);
        break;
    default:
        break;
    }

    for (int i = 0; i < TETRAMINO_NUMBER_OF_TILES; i++)
    {
        if (!active_piece->tiles[i]->IsOffsetPossibleBy(offset_location))
        {
            ResetPiece();

            if (direction == MoveDirection::DOWN)
            {
                FallSnd.Play();
                StorePieceToBoard();
            }

            return;
        }
    }
    MovePieceToNewLocation();
}

void PieceController::RootPiece()
{
    if (active_piece == NULL)
        return;

    for (int i = 0; i < TETRAMINO_NUMBER_OF_TILES; i++)
    {
        active_piece->tiles[i]->RootMe();
    }
    BruteFall.Play();
    StorePieceToBoard();
}

void PieceController::RotatePiece(bool rotate_clockwise)
{
    if (active_piece == NULL)
        return;

    for (int i = 1; i < NUMBER_OF_POSSIBLE_ROTATIONS; i++)
    {
        int next_rotation_indx = (((rotate_clockwise) ? (active_piece->current_rotation_indx + i) : (active_piece->current_rotation_indx - i)) + NUMBER_OF_POSSIBLE_ROTATIONS) % NUMBER_OF_POSSIBLE_ROTATIONS;

        Vec2 offset_vector;

        for (int z = 0; z < active_piece->offset_data->number_of_offsets; z++)
        {
            offset_vector.x = active_piece->offset_data->offsets[z][active_piece->current_rotation_indx].x - active_piece->offset_data->offsets[z][next_rotation_indx].x;
            offset_vector.y = (-1)*active_piece->offset_data->offsets[z][active_piece->current_rotation_indx].y - (-1)*active_piece->offset_data->offsets[z][next_rotation_indx].y;

            bool piece_can_rotate = true;
            for (int k = 0; k < TETRAMINO_NUMBER_OF_TILES; k++)
            {
                if (!active_piece->tiles[k]->IsRotationPossibleBy(rotate_clockwise, active_piece->centered_tile_location_ptr, offset_vector))
                {
                    ResetPiece();
                    piece_can_rotate = false;
                    break;
                }
            }
            if (piece_can_rotate)
            {
                active_piece->current_rotation_indx = next_rotation_indx;
                MovePieceToNewLocation();
                RotateSnd.Play();
                return;
            }
        }
    }
}

void PieceController::UpdateActivePieceLandingLocation()
{   
    int max_possible_y_offset = boardController->GetBoardHeightInRectangles();

    Vec2 tile_current_location;
    
    for (int i = 0; i < TETRAMINO_NUMBER_OF_TILES; i++)
    {
        tile_current_location = active_piece->tiles[i]->GetCurrentLocation();

        int possible_steps_so_far = 0;
        while (boardController->MoveIsPossible(Vec2(tile_current_location.x, tile_current_location.y + possible_steps_so_far + 1)))
        {
            possible_steps_so_far++;
        }

        if (max_possible_y_offset > possible_steps_so_far)
        {
            max_possible_y_offset = possible_steps_so_far;
        }
    }
    for (int i = 0; i < TETRAMINO_NUMBER_OF_TILES; i++)
    {
        active_piece->tiles[i]->UpdateLandingLocation(max_possible_y_offset);
    }
}

PieceController::~PieceController()
{
}

const OffsetData_t* PieceController::getOffsetData(PieceShape piece_shape)
{
    switch (piece_shape)
    {
    case PieceShape::J:
    case PieceShape::L:
    case PieceShape::S:
    case PieceShape::T:
    case PieceShape::Z:
        return &OffsetTable[0];
        break;
    case PieceShape::I:
        return &OffsetTable[1];
        break;
    case PieceShape::O:
        return &OffsetTable[2];
    default:
        return &OffsetTable[0];
        break;
    }
    return nullptr;
}

void PieceController::StorePieceToBoard()
{
    for (int i = 0; i < TETRAMINO_NUMBER_OF_TILES; i++)
    {
        boardController->StoreTile(active_piece->tiles[i]);

        active_piece->tiles[i] = NULL;
    }
    
    active_piece->centered_tile_location_ptr = NULL;
    delete active_piece;
    active_piece = NULL;
}

PieceController::Piece::~Piece()
{
    for (int i = 0; i < TETRAMINO_NUMBER_OF_TILES; i++)
    {
        if (tiles[i])
            delete tiles[i];
    }
}
