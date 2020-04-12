#ifndef CONWAY_VIEW
#define CONWAY_VIEW

#include "conway/game_of_life.h"
#include "conway/sdl_wrapper.h"

namespace conway {
    inline constexpr int CELL_SIDE_LENGTH = 16;
    void play(conway::Game_of_Life&);
}

#endif
