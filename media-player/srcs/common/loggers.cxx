
#include "log.hpp"

std::shared_ptr<spdlog::logger> loggerSetup(const std::string& name, spdlog::level::level_enum ll = spdlog::level::info)
{
    auto log = spdlog::stdout_color_mt(name);
    log->set_level(ll);
    return log;
}

std::shared_ptr<spdlog::logger> uiLogger{ loggerSetup("mars-ui") };
std::shared_ptr<spdlog::logger> renderingLogger{ loggerSetup("mars-rendering") };
std::shared_ptr<spdlog::logger> ffmpegLogger{ loggerSetup("mars-ffmpeg", spdlog::level::off) };
