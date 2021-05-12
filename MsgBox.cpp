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
// File Name: MsgBox.cpp
// Date File Created: 05/12/2021 at 12:28 AM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#include "MsgBox.h"
#include "Common.h"

#ifdef OS_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>

UINT getIcon(MsgBox::Styles style)
{
	switch (style)
	{
	case MsgBox::STYLE_INFO: return MB_ICONINFORMATION;
	case MsgBox::STYLE_WARNING: return MB_ICONWARNING;
	case MsgBox::STYLE_ERROR: return MB_ICONERROR;
	case MsgBox::STYLE_QUESTION: return MB_ICONQUESTION;
	default: return MB_ICONINFORMATION;
	}
}

UINT getButtons(MsgBox::Buttons button)
{
	switch (button)
	{
	case MsgBox::BUTTON_OK:
	case MsgBox::BUTTON_QUIT: return MB_OK;
	case MsgBox::BUTTON_OK_CANCEL: return MB_OKCANCEL;
	case MsgBox::BUTTON_YES_NO: return MB_YESNO;
	default: return MB_OK;
	}
}

MsgBox::Response getResponse(int response, MsgBox::Buttons button)
{
	switch (response)
	{
	case IDOK: return button == MsgBox::BUTTON_QUIT ? MsgBox::RESP_QUIT : MsgBox::RESP_OK;
	case IDCANCEL: return MsgBox::RESP_CANCEL;
	case IDYES: return MsgBox::RESP_YES;
	case IDNO: return MsgBox::RESP_NO;
	default: return MsgBox::RESP_NONE;
	}
}

#endif


MsgBox::Response MsgBox::show(const char* title, const char* msg, Styles style, Buttons button)
{
#ifdef OS_WINDOWS
	UINT flags = MB_TASKMODAL;
	flags |= getIcon(style);
	flags |= getButtons(button);
	return getResponse(MessageBox(nullptr, msg, title, flags), button);
#else
	return RESP_NONE;
#endif
}
