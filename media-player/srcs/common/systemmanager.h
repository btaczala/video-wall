#ifndef SYSTEMMANAGER_H_5VFOCN9H
#define SYSTEMMANAGER_H_5VFOCN9H

#include <string>
#include <vector>

namespace mars {
namespace common {

struct IPAddress {
    const std::string address;
    const std::string iface;
};

using IPAddressList = std::vector<IPAddress>;
struct SystemManager {
    IPAddressList getIP();
};
}
}

#endif /* end of include guard: SYSTEMMANAGER_H_5VFOCN9H */
