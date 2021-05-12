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
// File Name: Shader.cpp
// Date File Created: 05/11/2021 at 7:47 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#include "Shader.h"

#include "Util.h"

#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(std::string vert, std::string frag) :
mVertPath(std::move(vert)),
mFragPath(std::move(frag))
{
	load();
}

void Shader::init(std::string vert, std::string frag)
{
	mVertPath = std::move(vert);
	mFragPath = std::move(frag);
	load();
}

void Shader::bind()
{
	glUseProgram(mProgram);
}

void Shader::setUniform(const std::string& name, const vec4f& value)
{
	glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::setUniform(const std::string& name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string& name, const mat4f& value)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniform(const std::string& name, const vec3f& value)
{
	glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setUniform(const std::string& name, const vec2f& value)
{
	glUniform2f(getUniformLocation(name), value.x, value.y);
}

void Shader::setUniform(const std::string& name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string& name, uint value)
{
	glUniform1ui(getUniformLocation(name), value);
}

void Shader::load()
{
	std::string vertSrcStr;
	std::string fragSrcStr;

	if(!read_file(mVertPath, vertSrcStr))
	{
		LOG_CRITICAL("Failed to load shader {}", mVertPath);
		exit(-1);
	}

	if (!read_file(mFragPath, fragSrcStr))
	{
		LOG_CRITICAL("Failed to load shader {}", mFragPath);
		exit(-1);
	}

	const auto* vertSrc = vertSrcStr.c_str();
	const auto* fragSrc = fragSrcStr.c_str();

	const auto vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertSrc, nullptr);
	glCompileShader(vertShader);

	int success;
	char info[512];
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertShader, 512, nullptr, info);
		const auto err = fmt::format("Vertex Shader Error [{}]: {}", mVertPath, info);
		LOG_CRITICAL(err);
		exit(-1);
	}

	const auto fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSrc, nullptr);
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, nullptr, info);
		const auto err = fmt::format("Fragment Shader Error [{}]: {}", mFragPath, info);
		LOG_CRITICAL(err);
		exit(-1);
	}

	mProgram = glCreateProgram();
	glAttachShader(mProgram, vertShader);
	glAttachShader(mProgram, fragShader);
	glLinkProgram(mProgram);

	glGetShaderiv(mProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(mProgram, 512, nullptr, info);
		const auto err = fmt::format("Shader Linkage Error [{} & {}]: {}", mVertPath, mFragPath, info);
		LOG_CRITICAL(err);
		exit(-1);
	}


	LOG_INFO("Shader [id={}] loaded from files [{}] and [{}]", mProgram, mVertPath, mFragPath);
}

int Shader::getUniformLocation(const std::string& name) const {}
int Shader::getAttributeLocation(const std::string& name) const {}
