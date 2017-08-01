#ifndef CONFIGURATION_H_OVFWETK7
#define CONFIGURATION_H_OVFWETK7

#include <string>
#include <vector>

namespace mars {
namespace core {
struct ConfigurationManager {
    ConfigurationManager();

    void debug();

    std::vector<std::string> fontPaths() const noexcept;

private:
    const std::string _configPath;
};
} // namespace core
} // namespace mars

#endif /* end of include guard: CONFIGURATION_H_OVFWETK7 */
