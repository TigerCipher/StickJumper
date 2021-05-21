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
// File Name: Display.h
// Date File Created: 05/11/2021 at 4:19 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#pragma once

#include <string>
#include "Common.h"


class Display
{

public:
	Display(const std::string& title, int width, int height);
	~Display();

	void swap() const;
	static void clear(float red = 0, float green = 0, float blue = 0);

	bool isClosed() const;

	std::string getTitle() const { return mTitle; }
	void setTitle(const std::string& title);

	int getWidth() const { return mWidth; }
	int getHeight() const { return mHeight; }

	void setWidth(const int width) { mWidth = width; }
	void setHeight(const int height) { mHeight = height; }
	
	vec2f getCenter() const;
	vec2f getWhVector() const;

	static constexpr int VSYNC = 0;

private:
	struct GLFWwindow* mWindow;

	
	int mWidth;
	int mHeight;
	std::string mTitle{};


};