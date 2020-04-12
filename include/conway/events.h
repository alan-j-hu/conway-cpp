#ifndef CONWAY_SDL_EVENT
#define CONWAY_SDL_EVENT

#include <optional>
#include <SDL2/SDL_events.h>

namespace conway {
    std::optional<SDL_Event> poll_event();
}

#endif
