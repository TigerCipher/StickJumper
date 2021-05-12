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
// File Name: Display.cpp
// Date File Created: 05/11/2021 at 4:22 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#include "Display.h"

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>

void glfw_error_callback(int error, const char* desc)
{
	fmt::print("Error {}: {}", error, desc);
}

Display::Display(const std::string& title, const int width, const int height) :
	mWidth(width),
	mHeight(height),
	mTitle(title)
{
	LOG_TRACE("Initializing glfw");
	if (!glfwInit())
	{
		LOG_CRITICAL("Failed to initialize glfw");
		exit(-1);
	}

	glfwSetErrorCallback(glfw_error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	LOG_TRACE("Creating window with resolution ({}, {})", width, height);
	mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	if (!mWindow)
	{
		LOG_CRITICAL("Failed to create window");
		exit(-1);
	}
	LOG_TRACE("Window has been created successfully");
	
	const auto centerX = (glfwGetVideoMode(glfwGetPrimaryMonitor())->width / 2) - (width / 2);
	const auto centerY = (glfwGetVideoMode(glfwGetPrimaryMonitor())->height / 2) - (height / 2);
	glfwSetWindowPos(mWindow, centerX, centerY);

	LOG_TRACE("Creating OpenGL context");
	glfwMakeContextCurrent(mWindow);

	glfwSwapInterval(VSYNC);

	int w, h;
	glfwGetFramebufferSize(mWindow, &w, &h);

	LOG_TRACE("Initializing GLEW");
	const auto init = glewInit();
	if (init)
	{
		LOG_CRITICAL("Failed to initialize glew - {}", glewGetErrorString(init));
		exit(-1);
	}
	
	//glViewport(0, 0, w, h);

	LOG_INFO("Display is initialized");
}

Display::~Display()
{
	LOG_INFO("Destroying display");
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

void Display::swap() const
{
	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}

void Display::clear(const float red, const float green, const float blue)
{
	glClearColor(red, green, blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool Display::isClosed() const
{
	return glfwWindowShouldClose(mWindow);
}

vec2f Display::getCenter() const
{
	return { static_cast<float>(mWidth) / 2.0f, static_cast<float>(mHeight) / 2.0f };
}

vec2f Display::getWhVector() const
{
	return { mWidth, mHeight };
}
