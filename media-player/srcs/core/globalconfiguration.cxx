#include "globalconfiguration.h"
#include "log.hpp"

#include <algorithm>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

extern const size_t _resource_default_config_json_len;
extern const char _resource_default_config_json[];

namespace bfs = boost::filesystem;

namespace {
const std::vector<std::string> kDefaultSearchPaths{ "$HOME/.config/mars/config", "$INSTALL_PATH/conf/mars/config",
    "$OPT/mars/config" };

const std::string kDefaultJson{ static_cast<const char*>(_resource_default_config_json),
    _resource_default_config_json_len };

std::string configPath()
{
    auto it = std::find_if(
        std::begin(kDefaultSearchPaths), std::end(kDefaultSearchPaths), [](const auto& c) { return bfs::exists(c); });

    if (it == std::end(kDefaultSearchPaths)) {
        mars_warn("No path exists , using default json config");
        return "";
    }

    return *it;
}

nlohmann::json loadJson(const std::string& path)
{
    mars_debug("Loading json from path = {}", path);
    std::string data;
    if (path.empty()) {
        data = kDefaultJson;
    }

    try {
        nlohmann::json j;
        std::stringstream ss{ data };
        ss >> j;
        return j;
    } catch (const std::exception& ex) {
        mars_error("Excetion {} while parsing {}", ex.what(), data);
        throw;
    }
}

} // namespace

namespace mars {
namespace core {
ConfigurationManager::ConfigurationManager()
    : _configPath(configPath())
    , _jsonObject(loadJson(_configPath))
{
}

std::vector<std::string> ConfigurationManager::fontsPaths() const
{
    auto z = _jsonObject["fontPaths"];
    auto paths = z.get<std::vector<std::string>>();

    auto homePath = std::getenv("HOME");

    for (auto& p : paths) {
        if (boost::algorithm::contains(p, "$HOME") && homePath) {
            boost::algorithm::replace_all(p, "$HOME", std::string{ homePath });
        }
    }
    return paths;
}

std::string ConfigurationManager::uuid() const { return _jsonObject["uuid"].get<std::string>(); }

void ConfigurationManager::adjustLoggers()
{
    auto o = _jsonObject["logging"];

    for (nlohmann::json::iterator it = o.begin(); it != o.end(); ++it) {
        const std::string level = it.value().get<std::string>();
        for (int i = spdlog::level::trace; i <= spdlog::level::off; ++i) {
            if (std::string{ spdlog::level::level_names[i] } == level) {
                auto logger = spdlog::get(it.key());
                if (logger) {
                    logger->set_level(static_cast<spdlog::level::level_enum>(i));
                }
                break;
            }
        }
        spdlog::level::to_str(spdlog::level::debug);
    }
}

} // namespace core
} // namespace mars
