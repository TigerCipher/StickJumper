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
// File Name: Texture.cpp
// Date File Created: 05/15/2021 at 5:37 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#include "Texture.h"

#include <SOIL2/SOIL2.h>

#include <gl/glew.h>

std::unordered_map<std::string, TextureData> Texture::sTextureCache;


Texture::Texture(const std::string& filePath)
{
	auto it = sTextureCache.find(filePath);

	if (it == sTextureCache.end())
	{
		// Load
		mData = load(filePath);
		sTextureCache.insert(std::make_pair(filePath, mData));
	}
	else
	{
		mData = it->second;
	}
}

Texture::~Texture()
{
	if (mBound)
	{
		LOG_TRACE("Unbinding texture {}", mData.id);
		unbind(mData.id);
	}
}


void Texture::bind(uint slot)
{
	if(slot == 99)
	{
		slot = mData.id;
	}
	assert(slot < 31 && slot >= 0);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, mData.id);
	mBound = true;
}

void Texture::unbind(uint slot)
{
	if (slot == 99)
	{
		slot = mData.id;
	}
	assert(slot < 31 && slot >= 0);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, 0);
	mBound = false;
}


TextureData Texture::load(const std::string& path)
{
	LOG_INFO("Loading texture {}", path);

	TextureData data {};

	int w, h;

	ubyte* img = SOIL_load_image(path.c_str(), &w, &h,
	                             nullptr, SOIL_LOAD_RGBA);

	glGenTextures(1, &data.id);

	glBindTexture(GL_TEXTURE_2D, data.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
	             w, h, 0, GL_RGBA,
	             GL_UNSIGNED_BYTE, img);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(img);

	glBindTexture(GL_TEXTURE_2D, 0);

	data.width  = w;
	data.height = h;

	LOG_INFO("Texture loaded with ID: {}", data.id);
	return data;
}
