#pragma once
#include "BoardController.h"
#include "Tile.h"
#include "Common.h"
#include "Sound.h"

#define TETRAMINO_NUMBER_OF_TILES 4
#define NUMBER_OF_POSSIBLE_ROTATIONS 4

enum class PieceShape {
    J,
    L,
    S,
    T,
    Z,
    I,
    O,
    NUMBER_OF_SHAPES
};

typedef struct OffsetData_s {
    const int number_of_offsets;
    Vec2i offsets[5][NUMBER_OF_POSSIBLE_ROTATIONS];
} OffsetData_t;

typedef struct SpawningProperties_s {
    Vec2i spawn_location;
    bool center_rotation_tile = false;
} SpawningProperties_t;

class PieceController
{
private:
    class Piece {
    public:
        ~Piece();
        PieceShape piece_type;
        int current_rotation_indx = 0;
        const OffsetData_t* offset_data;
        Tile* tiles[TETRAMINO_NUMBER_OF_TILES] = { 0 };
        Vec2i* centered_tile_location_ptr;
    };

public:
    PieceController(Graphics& gfx, BoardController* boardController);
    void Init();
    bool SpawnNextPiece();
    void DrawActivePiece();
    void DrawNextPieces();
    void DrawPiece(Piece* piece, Vec2i offset, bool draw_landing_piece_as_well) const;
    void MovePiece(MoveDirection direction);
    void RootPiece();
    void RotatePiece(bool rotate_clockwise);
private:
    Piece* active_piece = NULL;
    Piece* next_piece = NULL;

    Graphics& gfx;
    BoardController* boardController;
    Sound RotateSnd;
    Sound FallSnd;
    Sound BruteFall;
    ~PieceController();
    const OffsetData_t* getOffsetData(PieceShape piece_shape);

    void StorePieceToBoard();
    void UpdateActivePieceLandingLocation();
    void GenerateNextPiece();
    void ResetPiece();
    void MovePieceToNewLocation();
    bool PieceCanBePlacedOnBoard();

    const SpawningProperties_t spawn_positions[7][4] = {
        { { { 3, 1 } },
          { { 4, 1 }, true },
          { { 5, 1 } },
          { { 3, 0 } },
        }, //J end
        { { { 3, 1 } },
          { { 4, 1 }, true },
          { { 5, 1 } },
          { { 5, 0 } },
        }, //L end
        { { { 3, 1 } },
          { { 4, 1 }, true },
          { { 4, 0 } },
          { { 5, 0 } },
        }, //S end
        { { { 3, 1 } },
          { { 4, 1 }, true },
          { { 5, 1 } },
          { { 4, 0 } },
        }, //T end
        { { { 3, 0 } },
          { { 4, 1 }, true },
          { { 4, 0 } },
          { { 5, 1 } },
        }, //Z end
        { { { 3, 0 } },
          { { 4, 0 }, true },
          { { 5, 0 } },
          { { 6, 0 } },
        }, //I end
        { { { 4, 0 } },
          { { 4, 1 }, true },
          { { 5, 0 } },
          { { 5, 1 } },
        }//O end
    };

    const OffsetData_t OffsetTable[3] = {
         {
             5,
             {
                 { { 0, 0 },
                   { 0, 0 },
                   { 0, 0 },
                   { 0, 0 } }, //Offset 1
                 { { 0, 0 },
                   { 1, 0 },
                   { 0, 0 },
                   {-1, 0 } }, //Offset 2
                 { { 0, 0 },
                   { 1,-1 },
                   { 0, 0 },
                   {-1,-1 } }, //Offset 3
                 { { 0, 0 },
                   { 0, 2 },
                   { 0, 0 },
                   { 0, 2 } }, //Offset 4
                 { { 0, 0 },
                   { 1, 2 },
                   { 0, 0 },
                   {-1, 2 } } //Offset 5
             }
         }, //Pieces J, L, S, T, Z end
         {
             5,
             {
                 { { 0, 0 },
                   {-1, 0 },
                   {-1, 1 },
                   { 0, 1 } }, //Offset 1
                 { {-1, 0 },
                   { 0, 0 },
                   { 1, 1 },
                   { 0, 1 } }, //Offset 2
                 { { 2, 0 },
                   { 0, 0 },
                   {-2, 1 },
                   { 0, 1 } }, //Offset 3
                 { {-1, 0 },
                   { 0, 1 },
                   { 1, 0 },
                   { 0,-1 } }, //Offset 4
                 { { 2, 0 },
                   { 0,-2 },
                   {-2, 0 },
                   { 0, 2 } } //Offset 5
             }
         }, //Piece I end
         {
             1,
             {
                 { { 0, 0 },
                   { 0,-1 },
                   {-1,-1 },
                   {-1, 0 } } //Offset 0
             }
         } //Piece O end
    };

    const Color ShapeInitColors[7] = {
        Colors::Blue,
        Colors::Orange,
        Colors::Green,
        Colors::Magenta,
        Colors::Red,
        Colors::Cyan,
        Colors::Yellow
    };
};

