/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "BoardController.h"
#include "PiecesController.h"
#include "Common.h"
#include "FrameTimer.h"
#include "Sound.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
    void DrawBorders();

	MainWindow& wnd;
	Graphics gfx;

	/********************************/
	/*  User Variables              */
    const VectorPosition_t board_offset_location = { 10, 10 };
    BoardController* boardController;
    PiecesController* piecesController = NULL;
    FrameTimer ft;

    int board_width_in_pixels;
    int board_height_in_pixels;
    int board_square_length_in_pixels = 30;

    /* Buttons flags */
    bool vkleft_was_released    = true;
    bool vkright_was_released   = true;
    bool vkspace_was_released   = true;
    bool vkdown_was_released    = true;
    bool vkup_was_released      = true;
    bool z_was_released         = true;
    bool x_was_released         = true;
    bool vkreturn_was_released  = true;
    /********************************/

    float move_down_speed = 1.6f;
    float time_passed = 0.0f;
    float move_down_speed_min = 0.3f;

    static constexpr float move_right_manual_speed = 0.1f;
    float move_right_manual_speed_time_passed = 0.0f;
    static constexpr float move_left_manual_speed = 0.1f;
    float move_left_manual_speed_time_passed = 0.0f;
    static constexpr float move_down_manual_speed = 0.18f;
    float move_down_manual_speed_time_passed = 0.0f;

    bool is_game_over = false;
    bool is_game_started = false;
	/********************************/
    Sound GameoverSnd;
    Sound TetrisThemeSnd;
};