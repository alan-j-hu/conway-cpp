#include "conway/events.h"

std::optional<SDL_Event> conway::poll_event()
{
    SDL_Event event;
    if(SDL_PollEvent(&event)) {
        return std::optional(event);
    }
    return std::nullopt;
}
