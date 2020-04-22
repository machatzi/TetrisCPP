#pragma once
#include "BoardController.h"
#include "PieceController.h"
#include "Common.h"
#include "Graphics.h"
#include <mutex>

class PiecesController
{
public:
    PiecesController(Graphics& gfx, BoardController& boardController);

    void SpawnNewPiece();
    void DrawPiece();
    void MovePiece(MoveDirection direction);
    void RootPiece(); //Send piece on the bottom
    void StartMovePieceDownInterval();
    void StopMovePieceDownInterval();
    void RotatePiece(bool rotate_clockwise);
private:
    Graphics& gfx;
    BoardController& boardController;
    PieceController* curPieceController;

    void MovePieceDown();
    bool move_piece_down_interval_is_on = false;
    std::mutex move_piece_down_mutex;
};

