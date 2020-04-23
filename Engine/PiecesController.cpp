#include "PiecesController.h"
#include "PieceController.h"


PiecesController::PiecesController(Graphics& gfx, BoardController& boardController)
    :
    gfx (gfx),
    boardController (boardController)
{
    curPieceController = new PieceController(gfx, boardController);
}

void PiecesController::Init()
{
    curPieceController->Init();
}

bool PiecesController::SpawnNewPiece()
{
    return curPieceController->SpawnNextPiece();
}

void PiecesController::DrawPiece()
{
     curPieceController->DrawPiece();
}

void PiecesController::MovePiece(MoveDirection direction)
{
    curPieceController->MovePiece(direction);
}

void PiecesController::RootPiece()
{
    curPieceController->RootPiece();
}

void PiecesController::RotatePiece(bool rotate_clockwise)
{
    curPieceController->RotatePiece(rotate_clockwise);
}
