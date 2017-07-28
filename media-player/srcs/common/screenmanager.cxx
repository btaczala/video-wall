#include "screenmanager.h"
#include <X11/Xlib-xcb.h>
#include <Xrandr.h>

#include <iostream>

namespace mars {
namespace common {

ScreensInfo ScreenManager::availableScreens() const
{
    ScreensInfo screens;
    Display* dpy = XOpenDisplay(nullptr);

    auto window = DefaultRootWindow(dpy);
    auto screen = XRRGetScreenResources(dpy, window);

    for (int i = 0; i < screen->ncrtc; ++i) {
        auto crtc_info = XRRGetCrtcInfo(dpy, screen, screen->crtcs[i]);
        const auto info = XRRGetOutputInfo(dpy, screen, screen->outputs[i]);
        screens.push_back({ static_cast<std::uint16_t>(crtc_info->width), static_cast<std::uint16_t>(crtc_info->height),
            info->name });
    }

    return screens;
}
}
}
