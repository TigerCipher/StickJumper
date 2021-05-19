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

//const list<Vertex> G_VERTICES = {
//	{ { 0.5f, 0.5f }, { 1, 1 } }, // top right 0
//	{ { 0.5f, -0.5f }, { 1, 0 } }, // bottom right 1
//	{ { -0.5f, -0.5f }, { 0, 0 } }, // bottom left 2
//	{ { -0.5f, 0.5f }, { 0, 1 } } // top left 3
//};

// TODO: Make objects take x1, y1, x2, and y2 coords to fill the vertex data
// Will make life easier for tracking position - and making camera follow a player

const list<Vertex> G_VERTICES = {
	{ { 400, 300 }, { 1, 1 } }, // top right 0
	{ { 400, -300 }, { 1, 0 } }, // bottom right 1
	{ { -400, -300 }, { 0, 0 } }, // bottom left 2
	{ { -400, 300 }, { 0, 1 } } // top left 3
};

const list<uint> G_INDICES = {
	0, 1, 3,
	1, 2, 3
};

Sprite::Sprite(const std::string& tex, const float scale):
	mTexture(tex),
	mMesh(G_VERTICES, G_INDICES),
	mScale(scale)
{
	mTransform = glm::scale(mTransform, vec3f(scale, scale, 0));
}

void Sprite::setScale(const float scale)
{
	mScale     = scale;
	mTransform = glm::scale(mTransform, vec3f(scale, scale, 0));
}

void Sprite::setPosition(const vec2f& pos)
{
	mPosition  = pos;
	mTransform = glm::translate(mat4f(1), vec3f(pos.x, pos.y, 0));
}


void Sprite::translate(const float x, const float y)
{
	mTransform = glm::translate(mTransform, vec3f(x, y, 0));
}

void Sprite::rotate(const float angle, const Axis axis)
{
	mRotTransform = glm::rotate(mRotTransform, to_radians(angle), get_axis(axis));
}

void Sprite::render(const Shader& shader)
{
	shader.setVec4("colorOverlay", vec4f(mColor.r, mColor.g, mColor.b, mColor.a));

	shader.setInt("tex", mTexture.getId());
	mTexture.bind();

	//shader.setMat4("rotMatrix", mRotTransform);

	shader.setMat4("transform", mTransform);

	mMesh.draw();
	mTexture.unbind();
}
