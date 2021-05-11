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
// File Name: Log.cpp
// Date File Created: 05/11/2021 at 5:48 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#include "Log.h"
#include <vector>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Log::sLogger;

void Log::init()
{
	std::vector<spdlog::sink_ptr> logSinks;
	logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("info.log", true));
	logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

	logSinks[0]->set_pattern("[%m-%d-%Y %H:%M:%S] [%l] [%g:%#] [%!] %n: %v");
	logSinks[1]->set_pattern("%^[%T] [%l] %n: %v%$");

	sLogger = std::make_shared<spdlog::logger>("StickJumper", begin(logSinks), end(logSinks));
	spdlog::register_logger(sLogger);
	sLogger->set_level(spdlog::level::trace);
	sLogger->flush_on(spdlog::level::trace);
}
