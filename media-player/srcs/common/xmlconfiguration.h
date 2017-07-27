#ifndef XMLCONFIGURATION_H_3OQ6MZ4I
#define XMLCONFIGURATION_H_3OQ6MZ4I

#include "iconfigurationmanager.h"
#include <string>

namespace mars {
namespace common {
struct XmlConfigurationManager : public IConfigurationManager {
    XmlConfigurationManager(const std::string& inputFilename);

    Configuration parse() const override;

private:
    const std::string _file;
};
}
}

#endif /* end of include guard: XMLCONFIGURATION_H_3OQ6MZ4I */
