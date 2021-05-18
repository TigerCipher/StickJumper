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
// File Name: Math.h
// Date File Created: 05/18/2021 at 12:00 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include "Common.h"

constexpr float PI    = 3.14159265358979323846f;
constexpr double PI_D = 3.1415926535897932384626433832795;

constexpr float to_radians(const float degs)
{
	return degs * PI / 180.0f;
}

constexpr float to_degrees(const float rads)
{
	return rads * 180.0f / PI;
}

enum Axis
{
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	AXIS_XY,
	AXIS_XZ,
	AXIS_YZ,
	AXIS_XYZ
};

constexpr vec3f get_axis(const Axis axis)
{
	return axis == AXIS_X
		       ? vec3f(1, 0, 0)
		       : axis == AXIS_Y
		       ? vec3f(0, 1, 0)
		       : axis == AXIS_Z
		       ? vec3f(0, 0, 1)
		       : axis == AXIS_XY
		       ? vec3f(1, 1, 0)
		       : axis == AXIS_XZ
		       ? vec3f(1, 0, 1)
		       : axis == AXIS_YZ
		       ? vec3f(0, 1, 1)
		       : vec3f(1, 1, 1);
}
