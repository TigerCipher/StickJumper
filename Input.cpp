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
// File Name: Input.cpp
// Date File Created: 05/16/2021 at 2:00 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#include "Input.h"

bool Input::sKeys[ MAX_KEYS ]     = { false };
bool Input::sLastKeys[ MAX_KEYS ] = { false };

bool Input::sButtons[ MAX_BUTTONS ]     = { false };
bool Input::sLastButtons[ MAX_BUTTONS ] = { false };

vec2f Input::sMouse {};
vec2f Input::sLastMouse {};
vec2f Input::sScroll {};

void Input::update()
{
	for (int i = 0; i < MAX_KEYS; i++)
	{
		sLastKeys[ i ] = sKeys[ i ];
	}

	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		sLastButtons[ i ] = sButtons[ i ];
	}

	sLastMouse = sMouse;
}

void Input::onKeyCallback(int key, int scancode, int action, int mods)
{
	sKeys[ key ] = action != GLFW_RELEASE;
}

void Input::onButtonCallback(int button, int action, int mods)
{
	sButtons[ button ] = action != GLFW_RELEASE;
}

bool Input::keyDown(int key)
{
	return sKeys[ toupper(key) ];
}

bool Input::keyPressed(int key)
{
	return sKeys[ toupper(key) ] && !sLastKeys[ toupper(key) ];
}

bool Input::keyReleased(int key)
{
	return !sKeys[ toupper(key) ] && sLastKeys[ toupper(key) ];
}

bool Input::buttonDown(int button)
{
	return sButtons[ button ];
}

bool Input::buttonPressed(int button)
{
	return sButtons[ button ] && !sLastButtons[ button ];
}

bool Input::buttonReleased(int button)
{
	return !sButtons[ button ] && sLastButtons[ button ];
}
