#ifndef CONWAY_VIEW
#define CONWAY_VIEW

#include "conway/game_of_life.h"
#include "conway/sdl_wrapper.h"

namespace conway {
    void cycle(conway::Game_of_Life&, conway::Renderer&);
    void play(conway::Game_of_Life&);
}

#endif
