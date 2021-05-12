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
// File Name: BufferObject.cpp
// Date File Created: 05/11/2021 at 11:32 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#include "BufferObject.h"

#include <gl/glew.h>

BufferObject::BufferObject(list<float> verts):
	mVertices(std::move(verts))
{
	glGenBuffers(1, &mVbo);
	glGenVertexArrays(1, &mVao);

	glBindVertexArray(mVao);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);

	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(float), mVertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void BufferObject::bind()
{
	glBindVertexArray(mVao);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
}

void BufferObject::draw()
{
	glBindVertexArray(mVao);
	//glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}
