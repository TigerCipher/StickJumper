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
// File Name: Log.h
// Date File Created: 05/11/2021 at 5:46 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#ifdef _DEBUG
	#define SPDLOG_DEBUG_ON
	#define SPDLOG_TRACE_ON
#endif


#include <spdlog/spdlog.h>

#include <memory>

class Log
{
public:
	static void init();
	static std::shared_ptr<spdlog::logger>& getLogger() { return sLogger; }
private:
	static std::shared_ptr<spdlog::logger> sLogger;
};

#define LOG_TRACE(...)       SPDLOG_LOGGER_TRACE(Log::getLogger(), __VA_ARGS__)
#define LOG_DEBUG(...)       SPDLOG_LOGGER_DEBUG(Log::getLogger(), __VA_ARGS__)
#define LOG_INFO(...)        SPDLOG_LOGGER_INFO(Log::getLogger(), __VA_ARGS__)
#define LOG_WARN(...)        SPDLOG_LOGGER_WARN(Log::getLogger(), __VA_ARGS__)
#define LOG_ERROR(...)       SPDLOG_LOGGER_ERROR(Log::getLogger(), __VA_ARGS__)
#define LOG_CRITICAL(...)    SPDLOG_LOGGER_CRITICAL(Log::getLogger(), __VA_ARGS__)
