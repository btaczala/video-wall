#ifndef GLOBALCONFIGURATION_H_LNVOITNZ
#define GLOBALCONFIGURATION_H_LNVOITNZ

#include "iconfigurationmanager.h"
#include <json.hpp>

#include <string>
#include <vector>

namespace mars {
namespace core {
struct ConfigurationManager : public IConfigurationManager {
    ConfigurationManager();

    std::vector<std::string> fontsPaths() const override;

    std::string uuid() const override;

    void adjustLoggers();

private:
    const std::string _configPath;
    const nlohmann::json _jsonObject;
};

} // namespace core
} // namespace mars

#endif /* end of include guard: GLOBALCONFIGURATION_H_LNVOITNZ*/
