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
#include "Shader.h"
#include "MsgBox.h"

list<float> gVertices = {
	-0.5f, -0.5f,
	 0.5f, -0.5f,
	 0.0f,  0.5f
};

int main(int argc, char** argv)
{
	Log::init();
	
	Display disp("Stick Jumper", 1280, 720);
	Shader basic("./assets/shaders/testVS.glsl", "./assets/shaders/testFS.glsl");

	BufferObject obj(gVertices);
	
	while(!disp.isClosed())
	{
		disp.clear(0.2f);

		basic.bind();
		//obj.bind();
		obj.draw();
		
		disp.swap();
	}

	LOG_INFO("Application exiting");

	MsgBox::show("Test MsgBox", "This is just a test", MsgBox::STYLE_INFO);
	return 0;
}