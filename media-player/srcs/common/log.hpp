#ifndef LOG_HPP_LI7VTYUZ
#define LOG_HPP_LI7VTYUZ

#include <cstring>
#include <memory>

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

extern std::shared_ptr<spdlog::logger> kDefaultLogger;
extern std::shared_ptr<spdlog::logger> uiLogger;
extern std::shared_ptr<spdlog::logger> ffmpegLogger;

#define __FILENAME__ (std::strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define mars_debug(fmt, ...)                                                                                           \
    do {                                                                                                               \
        kDefaultLogger->debug("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                  \
    } while (0)
#define mars_warn(fmt, ...)                                                                                            \
    do {                                                                                                               \
        kDefaultLogger->warn("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                   \
    } while (0)
#define mars_error(fmt, ...)                                                                                           \
    do {                                                                                                               \
        kDefaultLogger->error("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                  \
    } while (0)
#define mars_info(fmt, ...)                                                                                            \
    do {                                                                                                               \
        kDefaultLogger->info("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                   \
    } while (0)

#define mars_trace_(logger, fmt, ...)                                                                                  \
    do {                                                                                                               \
        logger##Logger->trace("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                  \
    } while (0)
#define mars_debug_(logger, fmt, ...)                                                                                  \
    do {                                                                                                               \
        logger##Logger->debug("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                  \
    } while (0)
#define mars_warn_(logger, fmt, ...)                                                                                   \
    do {                                                                                                               \
        logger##Logger->warn("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                   \
    } while (0)

#endif /* end of include guard: LOG_HPP_LI7VTYUZ */
