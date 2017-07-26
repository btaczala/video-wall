
#include "log.hpp"

std::shared_ptr<spdlog::logger> loggerSetup(const std::string& name)
{
    auto log = spdlog::stdout_color_mt(name);
    log->set_level(spdlog::level::debug);
    return log;
}

std::shared_ptr<spdlog::logger> uiLogger{ loggerSetup("mars-ui") };
std::shared_ptr<spdlog::logger> renderingLogger{ loggerSetup("mars-rendering") };
std::shared_ptr<spdlog::logger> ffmpegLogger{ loggerSetup("mars-ffmpeg") };
