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
// File Name: main.cpp
// Date File Created: 05/11/2021 at 3:59 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------


#include "Display.h"
#include "Mesh.h"
#include "Error.h"
#include "Shader.h"
#include "MsgBox.h"
#include "Timer.h"
#include "Vertex.h"
#include "Texture.h"
#include "Input.h"
#include "Math.h"
#include "Sprite.h"

#include "Camera.h"


bool gLimitFramerate = false;

void run()
{
	Display disp("Stick Jumper", 800, 600);

	const Shader basic("./assets/shaders/testVS.glsl", "./assets/shaders/testFS.glsl");

	Camera cam(disp);
	//cam.setScale(3.0f);

	Timer timer;

	const float size = 256.0f;
	Sprite spr("./assets/textures/test.png", -400, -300, size, size); // bottom left

	Sprite spr2("./assets/textures/test.png", 400 - size, -300, size, size); // bottom right
	Sprite spr3("./assets/textures/test.png", -400, 300 - size, size, size); // top left
	Sprite spr4("./assets/textures/test.png", 400 - size, 300 - size, size, size); // top right


	Sprite m1("./assets/textures/01.png", -32, -32, 64, 64);


	Sprite smile("./assets/textures/smile.png", -32, -32, 64, 64);


	smile.setPosition(-32, -150);
	smile.setScale(3.0f);

	spr.setColor(COLOR_CYAN);
	spr2.setColor(COLOR_BLUE);
	spr3.setColor(COLOR_RED);
	spr4.setColor(COLOR_GREEN);


	float lastTime     = Timer::now();
	float frameCounter = 0;
	float accumulated  = 0;
	int fps            = 0;

	float frameTime = 1.0f / 144.0f;

	while (!disp.isClosed())
	{
		bool allowRender = false;
		float startTime  = Timer::now();
		float passedTime = startTime - lastTime;
		lastTime         = startTime;

		accumulated += passedTime;
		frameCounter += passedTime;

		//const float delta2 = timer.mark();
		if (frameCounter >= 1.0f)
		{
			fmt::print("FPS: {}\n", fps);
			disp.setTitle(fmt::format("Stick Jumper    -    {} FPS", fps));
			fps          = 0;
			frameCounter = 0;
		}

		while (accumulated > frameTime)
		{
			allowRender       = true;
			const float delta = frameTime;

			cam.update();

			if (Input::buttonPressed(MOUSE_BUTTON_LEFT))
			{
				vec2f coords = Input::getMousePos();
				fmt::print("Screen coords: ({}, {})\n", coords.x, coords.y);
				coords = cam.convertScreenToWorld(coords);
				fmt::print("World coords: ({}, {})\n", coords.x, coords.y);
			}

			smile.rotate(delta * 45, AXIS_Z);

			static float movSpd = 500.0f * delta;
			//static float movSpd = 10.0f;
			if (Input::keyDown(KEY_D))
			{
				cam.move({ movSpd, 0 });
			}

			if (Input::keyDown(KEY_A))
			{
				cam.move({ -movSpd, 0 });
			}

			if (Input::keyDown(KEY_S))
			{
				cam.move({ 0, -movSpd });
			}

			if (Input::keyDown(KEY_W))
			{
				cam.move({ 0, movSpd });
			}

			if (Input::keyDown(KEY_E))
			{
				cam.setScale(cam.getScale() + delta);
			}

			if (Input::keyDown(KEY_Q))
			{
				cam.setScale(cam.getScale() - delta);
			}

			Input::update();

			accumulated -= frameTime;
		}


		// Render code
		if (!gLimitFramerate || allowRender)
		{
			Display::clear(0.2f);
			basic.bind();
			basic.setMat4("proj", cam.getTransform());
			spr.render(basic);
			spr2.render(basic);
			spr3.render(basic);
			spr4.render(basic);
			smile.render(basic);
			disp.swap();
			fps++;
		}
	}
}

int main(int argc, char** argv)
{
	Log::init();

	try
	{
		run();
	}
	catch (const Error& e)
	{
		LOG_CRITICAL(e.what());
		MsgBox::show(e.getType(), e.what(), MsgBox::STYLE_ERROR);
		return -1;
	}catch (const std::exception& e)
	{
		LOG_CRITICAL(e.what());
		MsgBox::show("STD Exception", e.what(), MsgBox::STYLE_ERROR);
		return -1;
	}catch (...)
	{
		LOG_CRITICAL("Encountered an unknown fatal exception");
		MsgBox::show("Unknown Exception", "No details available.", MsgBox::STYLE_ERROR);
		return -1;
	}

	LOG_INFO("Application exiting");

	return 0;
}
