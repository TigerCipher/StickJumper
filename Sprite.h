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
// File Name: Sprite.h
// Date File Created: 05/18/2021 at 2:25 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#pragma once

#include <string>

#include "Common.h"
#include "Common.h"
#include "Texture.h"
#include "Math.h"
#include "Shader.h"
#include "Mesh.h"
#include "Vertex.h"

class Sprite
{
public:
	Sprite(const std::string& tex, float x, float y, float w, float h);
	~Sprite() = default;

	void setScale(float scale);

	void setPosition(const vec2f& pos);
	void setPosition(const float x, const float y) { setPosition({x, y}); }

	vec2f getPosition() const { return mPosition; }

	void setColor(const ColorRGBA8 col) { mColor = col; }

	void translate(float x, float y);
	void rotate(float angle, Axis axis);

	void render(const Shader& shader);

private:
	Texture mTexture;
	scope<Mesh> mMesh;
	float mScale = 1.0f;

	vec2f mPosition {};
	mat4f mTransform { 1 };
	ColorRGBA8 mColor{};
	
};
