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

Sprite::Sprite(const std::string& tex, const float scale):
	mTexture(tex),
	mMesh(gVertices, gIndices),
	mScale(scale)
{
	mTransform = glm::scale(mTransform, vec3f(scale, scale, 0));
	LOG_DEBUG("Texture ID is {}", mTexture.getId());
}

void Sprite::setPosition(const vec2f& pos)
{
	mPosition = pos;
	mWorld = glm::translate(mat4f(1), vec3f(pos.x, pos.y, 0));
}

void Sprite::move(float delta, float x, float y)
{
	mWorld = glm::translate(mWorld, vec3f(x * delta, y * delta, 0));
}

void Sprite::render(const Shader& shader)
{
	shader.bind();

	shader.setInt("tex", mTexture.getId());
	mTexture.bind();
	
	shader.setMat4("model", mTransform);

	shader.setMat4("world", mWorld);

	mMesh.draw();

	shader.unbind();
	mTexture.unbind();
}
