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
// File Name: Error.h
// Date File Created: 05/12/2021 at 9:52 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#pragma once

#include <exception>
#include <string>
#include <fmt/core.h>

class Error : public std::exception
{
public:
	Error(const char* file, const int line, std::string info) :
		mFile(file), mLine(line), mInfo(std::move(info)) {}

	char const* what() const override;

	virtual const char* getType() const;
	std::string getOrigin() const;

	int getLine() const { return mLine; }
	const std::string& getFile() const { return mFile; }

protected:

	virtual const char* getName() const;

	mutable std::string mWhat;
	mutable std::string mType;
	std::string mInfo;

private:
	std::string mFile;
	int mLine;
};


class ShaderError : public Error
{
public:
	ShaderError(const char* file, const int line, std::string info) :
		Error(file, line, std::move(info)) {}

	const char* getName() const override { return "Shader Error"; }
};

class DisplayError : public Error
{
public:
	DisplayError(const char* file, const int line, std::string info) :
		Error(file, line, std::move(info)) {}

	const char* getName() const override { return "Display Error"; }
};

class TextureError : public Error
{
public:
	TextureError(const char* file, const int line, std::string info) :
		Error(file, line, std::move(info)) {}

	const char* getName() const override { return "Texture Error"; }
};


#define SHADER_ERROR(x, ...) ShaderError(__FILE__, __LINE__, fmt::format(x, __VA_ARGS__))
#define DISPLAY_ERROR(x, ...) DisplayError(__FILE__, __LINE__, fmt::format(x, __VA_ARGS__))
#define TEXTURE_ERROR(x, ...) TextureError(__FILE__, __LINE__, fmt::format(x, __VA_ARGS__))