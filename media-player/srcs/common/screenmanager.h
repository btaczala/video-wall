#ifndef SCREENMANAGER_H_3NQUV5JU
#define SCREENMANAGER_H_3NQUV5JU

#include <cstdint>
#include <string>
#include <vector>

namespace mars {
namespace common {

    struct ScreenInfo {
        const std::uint16_t width;
        const std::uint16_t height;
        const std::string name;
    };

    using ScreensInfo = std::vector<ScreenInfo>;
    struct ScreenManager {
        ScreenManager();

        ScreensInfo availableScreens() const;
    };
}
}

#endif /* end of include guard: SCREENMANAGER_H_3NQUV5JU */
