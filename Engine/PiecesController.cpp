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
        StopMovePieceDownInterval();
        curPieceController->SpawnNextPiece();
        StartMovePieceDownInterval();
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

void PiecesController::StartMovePieceDownInterval()
{
    move_piece_down_interval_is_on = true;

    std::thread th(&PiecesController::MovePieceDown, this);

    th.detach();
}

void PiecesController::StopMovePieceDownInterval()
{
    move_piece_down_interval_is_on = false;
}

void PiecesController::RotatePiece(bool rotate_clockwise)
{
    if (curPieceController->hasActivePiece())
    {
        curPieceController->RotatePiece(rotate_clockwise);
    }
}

void PiecesController::MovePieceDown()
{
    while (true) {
        std::lock_guard<std::mutex> guard(move_piece_down_mutex);
        if (!this->move_piece_down_interval_is_on) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        if (!this->move_piece_down_interval_is_on) return;
        MovePiece(MoveDirection::DOWN);
    }
}
