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

void run()
{
	Display disp("Stick Jumper", 800, 600);

	const Shader basic("./assets/shaders/testVS.glsl", "./assets/shaders/testFS.glsl");

	Camera cam(disp);
	cam.setScale(0.15f);

	Timer timer;

	Sprite spr("./assets/textures/smile.png", 0.5f);

	//spr.setPosition(-0.5f, 0);
	spr.setScale(0.35f);
	//spr.rotate(45.0f, AXIS_Z);
	spr.setColor(COLOR_CYAN);

	while (!disp.isClosed())
	{
		const float delta = timer.mark();
		Display::clear(0.2f);

		cam.update();

		if (Input::buttonPressed(MOUSE_BUTTON_LEFT))
		{
			vec2f mCoords = Input::getMousePos();
			fmt::print("Screen coords: ({}, {})\n", mCoords.x, mCoords.y);
			mCoords = cam.convertScreenToWorld(mCoords);
			fmt::print("World coords: ({}, {})\n", mCoords.x, mCoords.y);
		}

		static float movSpd = 5.0f;
		if (Input::keyDown(KEY_D))
		{
			cam.move({movSpd, 0});
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

		basic.bind();
		basic.setMat4("proj", cam.getTransform());
		spr.render(basic);

		

		Input::update();
		disp.swap();
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
