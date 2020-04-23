/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Tile.h"

using namespace std;

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
    piecesController = new PiecesController(gfx, boardController);
}

void Game::Go()
{
    piecesController->SpawnNewPiece();

	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
    boardController.ClearCompleteLines();

    frames_counter++;
    if (frames_counter == move_down_speed)
    {
        frames_counter = 0;
        piecesController->MovePiece(MoveDirection::DOWN);
    }

    if (wnd.kbd.KeyIsPressed(VK_DOWN))
    {
        if (vkdown_was_released)
        {
            vkdown_was_released = false;
            piecesController->MovePiece(MoveDirection::DOWN);
        }
    }
    else
    {
        vkdown_was_released = true;
    }

    if (wnd.kbd.KeyIsPressed(VK_RIGHT))
    {
        if (vkright_was_released)
        {
            vkright_was_released = false;
            piecesController->MovePiece(MoveDirection::RIGHT);
        }
    }
    else
    {
        vkright_was_released = true;
    }

    if (wnd.kbd.KeyIsPressed(VK_LEFT))
    {
        if (vkleft_was_released)
        {
            vkleft_was_released = false;
            piecesController->MovePiece(MoveDirection::LEFT);
        }
    }
    else
    {
        vkleft_was_released = true;
    }

    if (wnd.kbd.KeyIsPressed(VK_UP))
    {
        if (vkup_was_released)
        {
            vkup_was_released = false;
            piecesController->RootPiece();
        }
    }
    else
    {
        vkup_was_released = true;
    }

    if (GetKeyState('Z') & 0x8000)
    {
        if (z_was_released)
        {
            z_was_released = false;
            piecesController->RotatePiece(false);
        }
    }
    else
    {
        z_was_released = true;
    }

    if (GetKeyState('X') & 0x8000)
    {
        if (x_was_released)
        {
            x_was_released = false;
            piecesController->RotatePiece(true);;
        }
    }
    else
    {
        x_was_released = true;
    }
      
}

void Game::ComposeFrame()
{
    piecesController->DrawPiece();
    boardController.DrawBoard();
}
