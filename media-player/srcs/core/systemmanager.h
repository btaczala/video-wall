#ifndef SYSTEMMANAGER_H_5VFOCN9H
#define SYSTEMMANAGER_H_5VFOCN9H

#include <string>
#include <vector>

namespace mars {
namespace core {
struct IConfigurationManager;

struct IPAddress {
    const std::string address;
    const std::string iface;
};

using IPAddressList = std::vector<IPAddress>;
struct SystemManager {
    SystemManager(IConfigurationManager& configurationManager)
        : _cfg(configurationManager)
    {
    }
    IPAddressList getIP();

    std::string uuid() const;

private:
    IConfigurationManager& _cfg;
};
} // namespace core
} // namespace mars

#endif /* end of include guard: SYSTEMMANAGER_H_5VFOCN9H */
