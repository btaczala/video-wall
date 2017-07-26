#include "log.hpp"

std::shared_ptr<spdlog::logger> grab(const std::string& name) {
    auto logger = spdlog::stdout_color_mt("mars");
    logger->set_level(spdlog::level::warn);

    return logger;
}

std::shared_ptr<spdlog::logger> kDefaultLogger{grab("mars")};
