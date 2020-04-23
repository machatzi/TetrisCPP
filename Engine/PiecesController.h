#pragma once
#include "BoardController.h"
#include "PieceController.h"
#include "Common.h"
#include "Graphics.h"

class PiecesController
{
public:
    PiecesController(Graphics& gfx, BoardController& boardController);

    void Init();
    bool SpawnNewPiece();
    void DrawPiece();
    void MovePiece(MoveDirection direction);
    void RootPiece(); //Send piece on the bottom
    void RotatePiece(bool rotate_clockwise);
private:
    Graphics& gfx;
    BoardController& boardController;
    PieceController* curPieceController;
};

