#include "xmlconfiguration.h"
#include "log.hpp"
#include "systemmanager.h"

#include <boost/filesystem/operations.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <spdlog/fmt/fmt.h>

namespace bpt = boost::property_tree;

namespace mars {
namespace common {
XmlConfigurationManager::XmlConfigurationManager(const std::string& inputFilename)
    : _file(inputFilename)
{
    namespace bfs = boost::filesystem;
    if (!bfs::exists(inputFilename)) {
        fatal_error(fmt::format("File {} does not exists", inputFilename));
    }
}

Configuration XmlConfigurationManager::parse() const
{
    fatal_error("Not implemented");
    Configuration cfg;
    bpt::ptree tree;

    bpt::xml_parser::read_xml(_file, tree);

    return cfg;
}
} // namespace common
} // namespace mars
