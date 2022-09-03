#include "hzpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Hazel
{
	std::shared_ptr<spdlog::logger> Log::CoreLogger;
	std::shared_ptr<spdlog::logger> Log::ClientLogger;
	
	void Log::Init() 
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		CoreLogger = spdlog::stdout_color_mt("HAZEL");
		ClientLogger = spdlog::stdout_color_mt("APP");
	}
}