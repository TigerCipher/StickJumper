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
#include "Error.h"

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>

#include "Input.h"

// GLFW Callbacks

void glfw_error_callback(int error, const char* desc)
{
	fmt::print("Error {}: {}", error, desc);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Input::onKeyCallback(key, scancode, action, mods);
}

void button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Input::onButtonCallback(button, action, mods);
}

void mouse_pos_callback(GLFWwindow* window, double xPos, double yPos)
{
	Input::setMousePos(static_cast<float>(xPos), static_cast<float>(yPos));
}

void mouse_scroll_callback(GLFWwindow* window, double xOff, double yOff)
{
	Input::setMouseScroll(static_cast<float>(xOff), static_cast<float>(yOff));
}


void window_resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	auto disp = static_cast<Display*>(glfwGetWindowUserPointer(window));
	disp->setWidth(width);
	disp->setHeight(height);
	//TODO: Resize camera ortho projection?
}

// END GLFW Callbacks

Display::Display(const std::string& title, const int width, const int height) :
	mWidth(width),
	mHeight(height),
	mTitle(title)
{
	LOG_TRACE("Initializing glfw");
	if (!glfwInit())
	{
		throw DISPLAY_ERROR("Failed to initialize glfw");
	}

	glfwSetErrorCallback(glfw_error_callback);

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	LOG_TRACE("Creating window with resolution ({}, {})", width, height);
	mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	if (!mWindow)
	{
		throw DISPLAY_ERROR("Failed to create window");
	}
	LOG_TRACE("Window has been created successfully");

	
	const auto centerX = (glfwGetVideoMode(glfwGetPrimaryMonitor())->width / 2) - (width / 2);
	const auto centerY = (glfwGetVideoMode(glfwGetPrimaryMonitor())->height / 2) - (height / 2);
	glfwSetWindowPos(mWindow, centerX, centerY);

	LOG_TRACE("Creating OpenGL context");
	glfwMakeContextCurrent(mWindow);

	glfwSetKeyCallback(mWindow, key_callback);
	glfwSetMouseButtonCallback(mWindow, button_callback);
	glfwSetCursorPosCallback(mWindow, mouse_pos_callback);
	glfwSetScrollCallback(mWindow, mouse_scroll_callback);

	glfwSetWindowSizeCallback(mWindow, window_resize_callback);

	glfwSwapInterval(VSYNC);

	int w, h;
	glfwGetFramebufferSize(mWindow, &w, &h);

	LOG_TRACE("Initializing GLEW");
	if (const auto init = glewInit(); init)
	{
		throw DISPLAY_ERROR("Failed to initialize glew - {}", glewGetErrorString(init));
	}
	
	glViewport(0, 0, w, h);

	// Enable OpenGL features
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	LOG_TRACE("OpenGL Vendor: {}", glGetString(GL_VENDOR));
	LOG_TRACE("OpenGL Renderer: {}", glGetString(GL_RENDERER));
	int major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	LOG_TRACE("OpenGL Version {}.{}", major, minor);
	LOG_TRACE("GLSL Version {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
	LOG_DEBUG("GLSL Extensions: {}", glGetString(GL_EXTENSIONS));
	LOG_INFO("Display is initialized");


	
	glfwSetWindowUserPointer(mWindow, this);
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

void Display::setTitle(const std::string& title)
{
	mTitle = title;
	glfwSetWindowTitle(mWindow, mTitle.c_str());
}

vec2f Display::getCenter() const
{
	return { static_cast<float>(mWidth) / 2.0f, static_cast<float>(mHeight) / 2.0f };
}

vec2f Display::getWhVector() const
{
	return { mWidth, mHeight };
}
