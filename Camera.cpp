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
// File Name: Camera.cpp
// Date File Created: 05/18/2021 at 7:00 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#include "Camera.h"
#include "Math.h"

Camera::Camera(const Display& disp)
{
	mScreenWidth  = disp.getWidth();
	mScreenHeight = disp.getHeight();
	mProjection   = glm::ortho(0.0f, static_cast<float>(mScreenWidth),
	                           0.0f, static_cast<float>(mScreenHeight));
}

void Camera::update()
{
	if (mUpdateMatrix)
	{
		LOG_DEBUG("Camera pos: {} , {}", mPosition.x, mPosition.y);
		const vec3f translation(-mPosition.x + mScreenWidth / 2, -mPosition.y + mScreenHeight / 2, 0);
		LOG_DEBUG("Trans pos: {} , {}", translation.x, translation.y);
		mTransform    = glm::translate(mProjection, translation);
		//mTransform    = glm::translate(mTransform, vec3f(mPosition, 0));
		mTransform    = glm::scale(mat4f(1), vec3f(mScale, mScale, 0)) * mTransform;
		mUpdateMatrix = false;
	}
}

vec2f Camera::convertScreenToWorld(const vec2f& screenCoords) const
{
	vec2f worldCoords {};
	worldCoords.x = mScreenHeight - screenCoords.y;
	worldCoords -= vec2f(mScreenWidth / 2, mScreenHeight / 2);
	worldCoords /= mScale;
	worldCoords += mPosition;
	return worldCoords;
}
