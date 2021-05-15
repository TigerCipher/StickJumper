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
// File Name: Vertex.h
// Date File Created: 05/15/2021 at 12:20 AM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#pragma once


struct Position
{
	float x;
	float y;
};

struct TexCoords
{
	float u;
	float v;
};

struct ColorRGBA8
{
	float r;
	float g;
	float b;
	float a = 1.0f;
};

struct Vertex
{
	Position pos;
	ColorRGBA8 color;
};


constexpr ColorRGBA8 COLOR_WHITE = { 1, 1, 1 };
constexpr ColorRGBA8 COLOR_BLACK = { 0, 0, 0 };
constexpr ColorRGBA8 COLOR_RED = { 1, 0, 0 };
constexpr ColorRGBA8 COLOR_GREEN = { 0, 1, 0 };
constexpr ColorRGBA8 COLOR_BLUE = { 0, 0, 1 };
constexpr ColorRGBA8 COLOR_MAGENTA = { 1, 0, 1 };
constexpr ColorRGBA8 COLOR_CYAN = { 0, 1, 1 };
constexpr ColorRGBA8 COLOR_YELLOW = { 1, 1, 0 };
