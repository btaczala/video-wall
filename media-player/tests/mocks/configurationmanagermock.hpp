#ifndef CONFIGURATIONMANAGERMOCK_HPP_NRMLSXAT
#define CONFIGURATIONMANAGERMOCK_HPP_NRMLSXAT

#include "iconfigurationmanager.h"
#include <trompeloeil.hpp>

struct ConfigurationManagerMock : public mars::core::IConfigurationManager {
    MAKE_CONST_MOCK0(uuid, std::string(), override);
    MAKE_CONST_MOCK0(fontsPaths, std::vector<std::string>(), override);
};

#endif /* end of include guard: CONFIGURATIONMANAGERMOCK_HPP_NRMLSXAT */
