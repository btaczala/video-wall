#ifndef LOG_HPP_LI7VTYUZ
#define LOG_HPP_LI7VTYUZ

#include <cstring>
#include <memory>
#include <utility>

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

extern std::shared_ptr<spdlog::logger> kDefaultLogger;
extern std::shared_ptr<spdlog::logger> uiLogger;
extern std::shared_ptr<spdlog::logger> renderingLogger;
extern std::shared_ptr<spdlog::logger> videoLogger;
extern std::shared_ptr<spdlog::logger> ffmpegLibLogger;
extern std::shared_ptr<spdlog::logger> htmlLogger;
extern std::shared_ptr<spdlog::logger> perfLogger;

template <typename F, typename S> std::ostream& operator<<(std::ostream& os, const std::pair<F, S>& p)
{
    os << "{" << p.first << " ," << p.second << "}";
    return os;
}

#define __FILENAME__ (std::strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define mars_trace(fmt, ...)                                                                                           \
    do {                                                                                                               \
        kDefaultLogger->trace("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                  \
    } while (false)
#define mars_debug(fmt, ...)                                                                                           \
    do {                                                                                                               \
        kDefaultLogger->debug("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                  \
    } while (false)
#define mars_warn(fmt, ...)                                                                                            \
    do {                                                                                                               \
        kDefaultLogger->warn("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                   \
    } while (false)
#define mars_error(fmt, ...)                                                                                           \
    do {                                                                                                               \
        kDefaultLogger->error("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                  \
    } while (false)
#define mars_info(fmt, ...)                                                                                            \
    do {                                                                                                               \
        kDefaultLogger->info("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                   \
    } while (false)

#define mars_trace_(logger, fmt, ...)                                                                                  \
    do {                                                                                                               \
        logger##Logger->trace("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                  \
    } while (false)
#define mars_debug_(logger, fmt, ...)                                                                                  \
    do {                                                                                                               \
        logger##Logger->debug("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                  \
    } while (false)
#define mars_info_(logger, fmt, ...)                                                                                   \
    do {                                                                                                               \
        logger##Logger->info("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                   \
    } while (false)
#define mars_warn_(logger, fmt, ...)                                                                                   \
    do {                                                                                                               \
        logger##Logger->warn("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                   \
    } while (false)
#define mars_error_(logger, fmt, ...)                                                                                  \
    do {                                                                                                               \
        logger##Logger->error("[{}@{}] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__);                                  \
    } while (false)

template <typename ex = std::runtime_error> void fatal_error(const std::string& e)
{
    mars_error("{}", e);
    throw ex(e.c_str());
}
#endif /* end of include guard: LOG_HPP_LI7VTYUZ */
