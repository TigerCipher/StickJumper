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
#include "BufferObject.h"
#include "Error.h"
#include "Shader.h"
#include "MsgBox.h"
#include "Timer.h"

list<float> gVertices = {
	0.5f, 0.5f, // top right 0
	0.5f, -0.5f, // bottom right 1
	-0.5f, -0.5f, // bottom left 2
	-0.5f,  0.5f // top left 3
};

list<uint> gIndices = {
	0, 1, 3,
	1, 2, 3
};

void run()
{
	Display disp("Stick Jumper", 800, 600);
	Shader basic("./assets/shaders/testVS.glsl", "./assets/shaders/testFS.glsl");

	BufferObject obj(gVertices, gIndices);

	Timer timer;
	
	while (!disp.isClosed())
	{
		float delta = timer.mark();
		disp.clear(0.2f);

		const auto time = timer.elapsed();
		const float green = (cos(time) / 2.0f) + 0.5f;
		const float blue = (sin(time) / 2.0f) + 0.5f;

		basic.bind();
		basic.setUniform("sinTime", blue);
		basic.setUniform("cosTime", green);
		
		obj.draw();

		disp.swap();
	}
}

int main(int argc, char** argv)
{
	Log::init();
	
	try
	{
		run();
	}catch(const Error& e)
	{
		LOG_CRITICAL(e.what());
		MsgBox::show(e.getType(), e.what(), MsgBox::STYLE_ERROR);
		return -1;
	}catch(const std::exception& e)
	{
		LOG_CRITICAL(e.what());
		MsgBox::show("STD Exception", e.what(), MsgBox::STYLE_ERROR);
		return -1;
	}catch(...)
	{
		LOG_CRITICAL("Encountered an unknown fatal exception");
		MsgBox::show("Unknown Exception", "No details available.", MsgBox::STYLE_ERROR);
		return -1;
	}

	LOG_INFO("Application exiting");

	return 0;
}