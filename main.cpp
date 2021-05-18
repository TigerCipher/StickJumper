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

list<Vertex> gVertices = {
	{ { 0.5f, 0.5f }, COLOR_RED, { 1, 1 } }, // top right 0
	{ { 0.5f, -0.5f }, COLOR_GREEN, { 1, 0 } }, // bottom right 1
	{ { -0.5f, -0.5f }, COLOR_BLUE, { 0, 0 } }, // bottom left 2
	{ { -0.5f, 0.5f }, COLOR_CYAN, { 0, 1 } } // top left 3
};

list<uint> gIndices = {
	0, 1, 3,
	1, 2, 3
};

void run()
{
	Display disp("Stick Jumper", 800, 600);
	Shader basic("./assets/shaders/testVS.glsl", "./assets/shaders/testFS.glsl");

	Mesh obj(gVertices, gIndices);
	Texture testImg("./assets/textures/test.png");
	Texture smileImg("./assets/textures/smile.png");

	Timer timer;

	mat4f modelTransform(1);
	modelTransform = glm::scale(modelTransform, vec3f(0.5f, 0.5f, 0));

	mat4f worldTransform(1);

	while (!disp.isClosed())
	{
		const float delta = timer.mark();
		disp.clear(0.2f);

		basic.bind();

		basic.setUniform("tex", 1);
		basic.setUniform("smileTex", 2);
		testImg.bind(1);
		smileImg.bind(2);


		if (Input::keyDown(KEY_A))
		{
			worldTransform = glm::translate(worldTransform, vec3f(-delta, 0, 0));
		}

		if(Input::keyDown(KEY_D))
		{
			worldTransform = glm::translate(worldTransform, vec3f(delta, 0, 0));
		}

		if (Input::keyDown(KEY_S))
		{
			worldTransform = glm::translate(worldTransform, vec3f(0, -delta, 0));
		}

		if (Input::keyDown(KEY_W))
		{
			worldTransform = glm::translate(worldTransform, vec3f(0, delta, 0));
		}
		
		modelTransform = glm::rotate(modelTransform, delta, vec3f(0, 0, 1));

		basic.setUniform("model", modelTransform);
		basic.setUniform("world", worldTransform);

		obj.draw();


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
