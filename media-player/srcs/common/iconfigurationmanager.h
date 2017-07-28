#ifndef ICONFIGURATIONMANAGER_H_I5QMEVOX
#define ICONFIGURATIONMANAGER_H_I5QMEVOX

#include "configuration.h"

namespace mars {
namespace common {

struct IConfigurationManager {
    virtual ~IConfigurationManager() = default;
    virtual Configuration parse() const = 0;
};
} // namespace common
} // namespace mars

#endif /* end of include guard: ICONFIGURATIONMANAGER_H_I5QMEVOX */
