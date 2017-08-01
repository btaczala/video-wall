#include "configuration.h"

#include <algorithm>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>

#include "log.hpp"

namespace bfs = boost::filesystem;

namespace {
const std::vector<std::string> kDefaultSearchPaths{ "$HOME/.config/mars/config", "$INSTALL_PATH/conf/mars/config",
    "$OPT/mars/config" };

std::string configPath()
{
    auto it = std::find_if(
        std::begin(kDefaultSearchPaths), std::end(kDefaultSearchPaths), [](const auto& c) { return bfs::exists(c); });

    if (it == std::end(kDefaultSearchPaths)) {
        throw std::runtime_error("");
    }

    return *it;
}

} // namespace

namespace mars {
namespace core {
ConfigurationManager::ConfigurationManager()
    : _configPath(configPath())
{
}

void ConfigurationManager::debug()
{
    spdlog::apply_all([](auto l) { l->set_level(spdlog::level::debug); });
}

} // namespace core
} // namespace mars
