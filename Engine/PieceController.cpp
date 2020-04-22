#include "PieceController.h"

PieceController::PieceController(Graphics& gfx, BoardController& boardController)
    :
    gfx (gfx),
    boardController (boardController)
{
}

void PieceController::SpawnNextPiece()
{
    if (next_piece == NULL) //This can only happen in beginning of game
    {
        GenerateNextPiece();
    }
    active_piece = next_piece;
    next_piece = NULL;

    GenerateNextPiece();

    UpdateActivePieceLandingLocation();
    this->has_active_piece = true;
}

void PieceController::GenerateNextPiece()
{
    next_piece = new Piece_t();

    next_piece->piece_type = static_cast<PieceShape>(rand() % static_cast<int>(PieceShape::NUMBER_OF_SHAPES));
    
    next_piece->offset_data = getOffsetData(next_piece->piece_type);

    int shape_index = static_cast<int>(next_piece->piece_type);

    for (int i = 0; i < TETRAMINO_NUMBER_OF_TILES; i++)
    {
        next_piece->tiles[i] = new Tile(gfx, boardController, spawn_positions[shape_index][i].spawn_location, 30, ShapeInitColors[shape_index]);

        if (spawn_positions[shape_index][i].center_rotation_tile)
        {
            next_piece->centered_tile_location = next_piece->tiles[i]->GetCurrentLocationPtr();
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

void PieceController::DrawPiece() const
{
    for (int i = 0; i < TETRAMINO_NUMBER_OF_TILES; i++)
    {
        if (active_piece->tiles[i])
        {
            active_piece->tiles[i]->DrawMe(true);
        }
    }
}

void PieceController::MovePiece(MoveDirection direction)
{
    int x_offset = 0;
    int y_offset = 0;

    switch (direction)
    {
    case MoveDirection::RIGHT:
        x_offset = 1;
        break;
    case MoveDirection::LEFT:
        x_offset = -1;
        break;
    case MoveDirection::DOWN:
        y_offset = 1;
        break;
    default:
        break;
    }

    for (int i = 0; i < TETRAMINO_NUMBER_OF_TILES; i++)
    {
        if (!active_piece->tiles[i]->IsOffsetPossibleBy(x_offset,y_offset))
        {
            ResetPiece();

            if (direction == MoveDirection::DOWN)
            {
                StorePieceToBoard();
            }

            return;
        }
    }
    MovePieceToNewLocation();
}

void PieceController::RootPiece()
{
    for (int i = 0; i < TETRAMINO_NUMBER_OF_TILES; i++)
    {
        active_piece->tiles[i]->RootMe();
    }
    StorePieceToBoard();
}

bool PieceController::hasActivePiece()
{
    return has_active_piece;
}

void PieceController::RotatePiece(bool rotate_clockwise)
{
    for (int i = 1; i < NUMBER_OF_POSSIBLE_ROTATIONS; i++)
    {
        int next_rotation_indx = (((rotate_clockwise) ? (active_piece->current_rotation_indx + i) : (active_piece->current_rotation_indx - i)) + NUMBER_OF_POSSIBLE_ROTATIONS) % NUMBER_OF_POSSIBLE_ROTATIONS;

        VectorPosition_t offset_vector;

        for (int z = 0; z < active_piece->offset_data->number_of_offsets; z++)
        {
            offset_vector.x = active_piece->offset_data->offsets[z][active_piece->current_rotation_indx].x - active_piece->offset_data->offsets[z][next_rotation_indx].x;
            offset_vector.y = (-1)*active_piece->offset_data->offsets[z][active_piece->current_rotation_indx].y - (-1)*active_piece->offset_data->offsets[z][next_rotation_indx].y;

            bool piece_can_rotate = true;
            for (int k = 0; k < TETRAMINO_NUMBER_OF_TILES; k++)
            {
                if (!active_piece->tiles[k]->IsRotationPossibleBy(rotate_clockwise, active_piece->centered_tile_location->x, active_piece->centered_tile_location->y, offset_vector.x, offset_vector.y))
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
                return;
            }
        }
    }
}

void PieceController::UpdateActivePieceLandingLocation()
{
    int max_possible_y_offset = 20;
    VectorPosition_t* tile_current_location;
    for (int i = 0; i < TETRAMINO_NUMBER_OF_TILES; i++)
    {
        tile_current_location = active_piece->tiles[i]->GetCurrentLocationPtr();

        int possible_steps_so_far = 0;
        while (boardController.MoveIsPossible(tile_current_location->x, tile_current_location->y + possible_steps_so_far + 1))
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
        boardController.StoreTile(active_piece->tiles[i]);

        active_piece->tiles[i] = NULL;
    }

    active_piece->centered_tile_location = NULL;
    delete active_piece;
    active_piece = NULL;
    has_active_piece = false;
}
