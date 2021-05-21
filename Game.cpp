// ------------------------------------------------------------------------------
// 
// StickJumper
// Copyright (C) 2021 Blue Moon Development. All rights reserved.
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// 
// Contact: team@bluemoondev.org
// 
// File Name: Game.cpp
// Date File Created: 05/21/2021 at 12:44 AM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#include "Game.h"
#include "Input.h"

Game::Game(const Display& display):
	mCamera(display)
{
	mBasicShader.init("./assets/shaders/testVS.glsl", "./assets/shaders/testFS.glsl");
	mSprites.push_back(create_scope<Sprite>("./assets/textures/smile.png", -32, -32, 64, 64));

	mSprites.push_back(create_scope<Sprite>("./assets/textures/test.png", -400, -300, 256, 256));
	mSprites.back()->setColor(COLOR_CYAN);
	mSprites.push_back(create_scope<Sprite>("./assets/textures/test.png", 400 - 256, -300, 256, 256));
	mSprites.back()->setColor(COLOR_BLUE);
	mSprites.push_back(create_scope<Sprite>("./assets/textures/test.png", -400, 300 - 256, 256, 256));
	mSprites.back()->setColor(COLOR_RED);
	mSprites.push_back(create_scope<Sprite>("./assets/textures/test.png", 400 - 256, 300 - 256, 256, 256));
	mSprites.back()->setColor(COLOR_GREEN);
}

void Game::update(const float delta)
{
	mCamera.update();

	if (Input::buttonPressed(MOUSE_BUTTON_LEFT))
	{
		vec2f coords = Input::getMousePos();
		fmt::print("Screen coords: ({}, {})\n", coords.x, coords.y);
		coords = mCamera.convertScreenToWorld(coords);
		fmt::print("World coords: ({}, {})\n", coords.x, coords.y);
	}

	static float movSpd = 500.0f * delta;
	//static float movSpd = 10.0f;
	if (Input::keyDown(KEY_D))
	{
		mCamera.move({ movSpd, 0 });
	}

	if (Input::keyDown(KEY_A))
	{
		mCamera.move({ -movSpd, 0 });
	}

	if (Input::keyDown(KEY_S))
	{
		mCamera.move({ 0, -movSpd });
	}

	if (Input::keyDown(KEY_W))
	{
		mCamera.move({ 0, movSpd });
	}

	if (Input::keyDown(KEY_E))
	{
		mCamera.setScale(mCamera.getScale() + delta);
	}

	if (Input::keyDown(KEY_Q))
	{
		mCamera.setScale(mCamera.getScale() - delta);
	}
}

void Game::render()
{
	mBasicShader.bind();
	mBasicShader.setMat4("proj", mCamera.getTransform());

	for(int i = 0; i < mSprites.size(); i++)
	{
		mSprites[i]->render(mBasicShader);
	}
}
