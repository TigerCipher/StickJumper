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
// File Name: Common.h
// Date File Created: 05/11/2021 at 4:14 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#pragma once

#if defined(_WIN32) || defined(_WIN64)
	#define OS_WINDOWS
#elif defined(macintosh) || defined(Macintosh) || defined(__APPLE__) || defined(__MACH__)
	#define OS_APPLE
#elif defined(__unix__) || defined(__unix) || defined(__linux__) || defined(linux) || defined(__linux)
	#define OS_UNIX
#else
	#define OS_OTHER
#endif

#define STR(x) #x
#define STR_EXPANDED(x) STR(x)

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef unsigned char ubyte;

#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/common.hpp>

#include "Log.h"

using vec2f = glm::vec2;
using vec3f = glm::vec3;
using vec4f = glm::vec4;
using mat4f = glm::mat4;

template <typename T>
using list = std::vector<T>;


template <typename T>
using scope = std::unique_ptr<T>;


template <typename T>
using ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr scope<T> create_scope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
constexpr ref<T> create_ref(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}
