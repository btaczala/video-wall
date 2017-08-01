#ifndef GLOBALCONFIGURATION_H_LNVOITNZ
#define GLOBALCONFIGURATION_H_LNVOITNZ

#include <string>
#include <vector>

#include "json.hpp"

namespace mars {
namespace core {
struct ConfigurationManager {
    ConfigurationManager();

    std::vector<std::string> fontPaths() const;

    std::string uuid() const;

private:
    const std::string _configPath;
    const nlohmann::json _jsonObject;
};
} // namespace core
} // namespace mars

#endif /* end of include guard: GLOBALCONFIGURATION_H_LNVOITNZ*/
