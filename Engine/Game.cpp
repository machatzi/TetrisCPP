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
	gfx( wnd ),
    boardController(board_offset_location, 10, 20, 30)
{
    piecesController = new PiecesController(gfx, boardController);
    board_width_in_pixels = 10 * board_square_length_in_pixels;
    board_height_in_pixels = 20 * board_square_length_in_pixels;
    GameoverSnd = Sound(L"Media\\gameover.wav");
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
    auto dt = ft.Mark();

    if (is_game_over)
    {
        if (wnd.kbd.KeyIsPressed(VK_SPACE)) //New Game
        {
            if (vkspace_was_released)
            {
                boardController.ClearBoard();
                piecesController->Init();
                is_game_over = false;
                vkspace_was_released = false;
            }
        }
        else
        {
            vkspace_was_released = true;
        }
        return;
    }

    boardController.ClearCompleteLines();

    if (!piecesController->SpawnNewPiece())
    {
        is_game_over = true;
        GameoverSnd.Play();
        return;
    }

    time_passed += dt;
    if (time_passed >= move_down_speed)
    {
        time_passed -= move_down_speed;
        piecesController->MovePiece(MoveDirection::DOWN);
        move_down_speed = std::max(move_down_speed - dt, move_down_speed_min);
    }

    if (wnd.kbd.KeyIsPressed(VK_DOWN))
    {
        move_down_manual_speed_time_passed += dt;
        if ((vkdown_was_released) || (move_down_manual_speed_time_passed >= move_down_manual_speed))
        {
            move_down_manual_speed_time_passed -= move_down_manual_speed;
            vkdown_was_released = false;
            piecesController->MovePiece(MoveDirection::DOWN);
        }
    }
    else
    {
        vkdown_was_released = true;
        move_down_manual_speed_time_passed = 0.0f;
    }

    if (wnd.kbd.KeyIsPressed(VK_RIGHT))
    {
        move_right_manual_speed_time_passed += dt;
        if ((vkright_was_released) || (move_right_manual_speed_time_passed >= move_right_manual_speed))
        {
            move_right_manual_speed_time_passed -= move_right_manual_speed;
            vkright_was_released = false;
            piecesController->MovePiece(MoveDirection::RIGHT);
        }
    }
    else
    {
        vkright_was_released = true;
        move_right_manual_speed_time_passed = 0.0f;
    }

    if (wnd.kbd.KeyIsPressed(VK_LEFT))
    {
        move_left_manual_speed_time_passed += dt;
        if ((vkleft_was_released) || (move_left_manual_speed_time_passed >= move_left_manual_speed))
        {
            move_left_manual_speed_time_passed -= move_left_manual_speed;
            vkleft_was_released = false;
            piecesController->MovePiece(MoveDirection::LEFT);
        }
    }
    else
    {
        vkleft_was_released = true;
        move_left_manual_speed_time_passed = 0.0f;
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

void Game::DrawBorders()
{
    for (int y = 0; y <= board_offset_location.y; y++)
    {
        for (int x = 0; x < board_width_in_pixels + 2 * board_offset_location.x; x++)
            gfx.PutPixel(x, y, Colors::DarkBlue);
    }

    for (int y = board_offset_location.y + board_height_in_pixels; y < 2 * board_offset_location.y + board_height_in_pixels; y++)
    {
        for (int x = 0; x < board_width_in_pixels + 2 * board_offset_location.x; x++)
            gfx.PutPixel(x, y, Colors::DarkBlue);
    }

    for (int y = board_offset_location.y; y < board_offset_location.y + board_height_in_pixels; y++)
    {
        for (int x = 0; x < board_offset_location.x; x++)
            gfx.PutPixel(x, y, Colors::DarkBlue);

        for (int x = board_offset_location.x + board_width_in_pixels; x < 2 * board_offset_location.x + board_width_in_pixels; x++)
            gfx.PutPixel(x, y, Colors::DarkBlue);
    }
}

void Game::ComposeFrame()
{
    boardController.DrawBoard(gfx);
    piecesController->DrawPiece();
    DrawBorders();
    if (is_game_over)
    {
        //to implement game over graphics
    }
}
