#ifndef ICONFIGURATIONMANAGER_H_BWWQPAIT
#define ICONFIGURATIONMANAGER_H_BWWQPAIT

#include <string>
#include <vector>

namespace mars {
namespace core {
struct IConfigurationManager {
    virtual ~IConfigurationManager() = default;

    virtual std::string uuid() const = 0;
    virtual std::vector<std::string> fontsPaths() const = 0;
};

} // namespace core
} // namespace mars

#endif /* end of include guard: ICONFIGURATIONMANAGER_H_BWWQPAIT */
