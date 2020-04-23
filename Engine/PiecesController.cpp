#include "PiecesController.h"
#include "PieceController.h"


PiecesController::PiecesController(Graphics& gfx, BoardController& boardController)
    :
    gfx (gfx),
    boardController (boardController)
{
    curPieceController = new PieceController(gfx, boardController);
}

void PiecesController::SpawnNewPiece()
{
    if (!curPieceController->hasActivePiece())
    {
        curPieceController->SpawnNextPiece();
    }
}

void PiecesController::DrawPiece()
{
    if (curPieceController->hasActivePiece())
        curPieceController->DrawPiece();
}

void PiecesController::MovePiece(MoveDirection direction)
{
    if (curPieceController->hasActivePiece())
    {
        curPieceController->MovePiece(direction);
    }
}

void PiecesController::RootPiece()
{
    if (curPieceController->hasActivePiece())
    {
        curPieceController->RootPiece();
    }
}

void PiecesController::RotatePiece(bool rotate_clockwise)
{
    if (curPieceController->hasActivePiece())
    {
        curPieceController->RotatePiece(rotate_clockwise);
    }
}
