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
// File Name: Shader.h
// Date File Created: 05/11/2021 at 7:43 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#pragma once

#include <string>

#include "Common.h"

class Shader
{
public:

	Shader() = default;
	Shader(std::string vert, std::string frag);

	void init(std::string vert, std::string frag);
	void bind() const;
	void unbind() const;
	
	void setMat4(const std::string& name, const mat4f& value) const;
	void setVec4(const std::string& name, const vec4f& value) const;
	void setVec3(const std::string& name, const vec3f& value) const;
	void setVec2(const std::string& name, const vec2f& value) const;
	void setFloat(const std::string& name, float value) const;
	void setInt(const std::string& name, int value) const;
	void setUnsignedInt(const std::string& name, uint value) const;

private:
	void load();
	int getUniformLocation(const std::string& name) const;
	int getAttributeLocation(const std::string& name) const;

	std::string mVertPath{};
	std::string mFragPath{};
	uint mProgram{};
};