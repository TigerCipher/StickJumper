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
// File Name: MsgBox.h
// Date File Created: 05/12/2021 at 12:27 AM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#pragma once

class MsgBox
{
public:
	enum Styles
	{
		STYLE_INFO,
		STYLE_WARNING,
		STYLE_ERROR,
		STYLE_QUESTION
	};

	enum Buttons
	{
		BUTTON_OK,
		BUTTON_OK_CANCEL,
		BUTTON_YES_NO,
		BUTTON_QUIT
	};

	enum Response
	{
		RESP_OK,
		RESP_CANCEL,
		RESP_YES,
		RESP_NO,
		RESP_QUIT,
		RESP_NONE
	};

	static Response show(const char* title, const char* msg,
		Styles style = STYLE_INFO, Buttons button = BUTTON_OK);
};