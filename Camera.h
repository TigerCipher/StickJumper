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
// File Name: Camera.h
// Date File Created: 05/18/2021 at 7:00 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#pragma once

#include "Common.h"
#include "Display.h"

class Camera
{
public:
	Camera(const Display& disp);

	~Camera() = default;

	void update();

	vec2f convertScreenToWorld(const vec2f& screenCoords) const;

	void setScale(const float scale)
	{
		mScale = scale;
		mUpdateMatrix = true;
	}

	void setPosition(const vec2f& pos)
	{
		mPosition = pos;
		mUpdateMatrix = true;
	}

	void move(const vec2f& offset)
	{
		mPosition += offset;
		mUpdateMatrix = true;
	}

	float getScale() const { return mScale; }
	vec2f getPosition() const { return mPosition; }
	mat4f getTransform() const { return mTransform; }
	mat4f getProjection() const { return mProjection; }

private:
	int mScreenWidth;
	int mScreenHeight;
	bool mUpdateMatrix = true;

	float mScale = 1;

	vec2f mPosition{};
	mat4f mProjection{1};
	mat4f mTransform{1};
};
