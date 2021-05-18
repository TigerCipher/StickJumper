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

void run()
{
	Display disp("Stick Jumper", 800, 600);
	const Shader basic("./assets/shaders/testVS.glsl", "./assets/shaders/testFS.glsl");


	Timer timer;


	Sprite spr("./assets/textures/test.png", 0.5f);

	spr.setPosition(-0.5f, 0);
	spr.setScale(0.2f);
	spr.rotate(45.0f, AXIS_Z);

	while (!disp.isClosed())
	{
		const float delta = timer.mark();
		disp.clear(0.2f);


		if(Input::keyDown(KEY_D))
		{
			spr.translate(delta * 5, 0);
		}

		if (Input::keyDown(KEY_A))
		{
			spr.translate(delta * -5, 0);
		}

		if (Input::keyDown(KEY_S))
		{
			spr.translate(0, delta * -5);
		}

		if (Input::keyDown(KEY_W))
		{
			spr.translate(0, delta * 5);
		}
		
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
