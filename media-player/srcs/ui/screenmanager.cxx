#include "screenmanager.h"
#include <X11/Xlib-xcb.h>
#include <Xrandr.h>

#include <iostream>

namespace mars {
namespace ui {

ScreenManager::ScreenManager() {}

void ScreenManager::availableScreens() const {
    Display* dpy = XOpenDisplay(nullptr);

    auto window = DefaultRootWindow(dpy);
    auto screen = XRRGetScreenResources(dpy, window);

    std::cout << screen->ncrtc << std::endl;

    for (int i = 0; i < screen->ncrtc; ++i) {
        auto crtc_info = XRRGetCrtcInfo(dpy, screen, screen->crtcs[i]);
        auto info = XRRGetOutputInfo(dpy, screen, screen->outputs[i]);
        std::cout << crtc_info->width <<  " x " << crtc_info->height << " " << info->name << std::endl;
    }
}
}
}
