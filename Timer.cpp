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
// File Name: Timer.cpp
// Date File Created: 05/14/2021 at 3:02 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#include "Timer.h"


float Timer::mark()
{
	const auto prev = mLast;
	mLast = std::chrono::steady_clock::now();
	const std::chrono::duration<float> time = mLast - prev;
	return time.count();
}

float Timer::peek() const
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - mLast).count();
}

float Timer::elapsed() const
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - mStart).count();
}
