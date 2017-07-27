#ifndef CONFIGURATION_H_AYME0F2K
#define CONFIGURATION_H_AYME0F2K

#include <vector>

namespace mars {
namespace common {

enum class ZoneType { Video = 1, Html, Audio, Image, Text, RSS, Ticker };

struct ZoneConfiguration {
    const ZoneType _type;
};

struct DisplayUnitConfiguration {
    const std::vector<ZoneConfiguration> _zones;
};

struct Configuration {
    const std::vector<DisplayUnitConfiguration> _displays;
};
}
}

#endif /* end of include guard: CONFIGURATION_H_AYME0F2K */
