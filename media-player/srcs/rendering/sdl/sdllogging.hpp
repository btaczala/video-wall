#ifndef SDLLOGGING_HPP_SHIC2UJZ
#define SDLLOGGING_HPP_SHIC2UJZ

#include <SDL2/SDL.h>
#include <spdlog/fmt/ostr.h>

std::ostream& operator<<(std::ostream& os, const SDL_Rect& c)
{
    return os << "Rect {" << c.x << "," << "," << c.y << "," << c.w << ","<< c.h << "}";
}

#endif /* end of include guard: SDLLOGGING_HPP_SHIC2UJZ */
