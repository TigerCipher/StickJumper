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
// File Name: Error.cpp
// Date File Created: 05/12/2021 at 9:59 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#include "Error.h"

char const* Error::what() const
{
	mWhat = fmt::format("{}\n{}\n[Info]\n{}", getType(), getOrigin(), mInfo);
	return mWhat.c_str();
}

const char* Error::getType() const
{
	mType = fmt::format("STICK#{}", getName());
	return mType.c_str();
}

std::string Error::getOrigin() const
{
	return fmt::format("[File] {}\n[Line] {}", mFile, mLine);
}

const char* Error::getName() const
{
	return "StickJumper Error";
}
