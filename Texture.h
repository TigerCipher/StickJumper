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
// File Name: Texture.h
// Date File Created: 05/15/2021 at 5:31 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#pragma once

#include "Common.h"

#include <string>

struct TextureData
{
	uint id;
	int width;
	int height;
};

class Texture
{
public:
	Texture(const std::string& filePath);
	~Texture();

	void bind(uint slot = 0);
	void unbind(uint slot = 0);

	uint getId() const { return mData.id; }

	int getWidth() const { return mData.width; }
	int getHeight() const { return mData.height; }


private:
	static TextureData load(const std::string& path);
	
	static std::unordered_map<std::string, TextureData> sTextureCache;
	
	TextureData mData {};
	bool mBound = false;
};
