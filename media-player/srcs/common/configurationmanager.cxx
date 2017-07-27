#include "configurationmanager.h"
#include "log.hpp"
#include "systemmanager.h"

#include <boost/filesystem/operations.hpp>
#include <spdlog/fmt/fmt.h>

namespace mars {
namespace common {
ConfigurationManager::ConfigurationManager(const std::string& inputFilename)
{
    namespace bfs = boost::filesystem;
    if (!bfs::exists(inputFilename)) {
        fatal_error(fmt::format("File {} does not exists", inputFilename));
    }
}
}
}
