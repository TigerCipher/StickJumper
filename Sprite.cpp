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
// File Name: Sprite.cpp
// Date File Created: 05/18/2021 at 2:25 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#include "Sprite.h"

#include "Vertex.h"


Sprite::Sprite(const std::string& tex, const float x, const float y, const float w, const float h):
	mTexture(tex)
{
	const list<Vertex> verts = {
		{ { x + w, y + h }, { 1, 1 } },
		{ { x + w, y }, { 1, 0 } },
		{ { x, y }, { 0, 0 } },
		{ { x, y + h }, { 0, 1 } }
	};

	const list<uint> ints = {
		0, 1, 3,
		1, 2, 3
	};

	mMesh = create_scope<Mesh>(verts, ints);
}

void Sprite::setScale(const float scale)
{
	mScale     = scale;
	mTransform = glm::scale(mTransform, vec3f(scale, scale, 0));
}

void Sprite::setPosition(const vec2f& pos)
{
	mPosition  = pos;
	mTransform = glm::translate(mTransform, vec3f(pos.x, pos.y, 0));
}


void Sprite::translate(const float x, const float y)
{
	mTransform = glm::translate(mTransform, vec3f(x, y, 0));
}

void Sprite::rotate(const float angle, const Axis axis)
{
	mTransform = glm::rotate(mTransform, to_radians(angle), get_axis(axis));
}

void Sprite::render(const Shader& shader)
{
	shader.setVec4("colorOverlay", vec4f(mColor.r, mColor.g, mColor.b, mColor.a));

	shader.setInt("tex", mTexture.getId());
	mTexture.bind();

	shader.setMat4("transform", mTransform);

	mMesh->draw();
	mTexture.unbind();
}
