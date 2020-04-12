#ifndef CONWAY_VIEW
#define CONWAY_VIEW

#include "conway/game_of_life.h"
#include "conway/sdl_wrapper.h"

namespace conway {
    inline constexpr int CELL_SIDE_LENGTH = 16;

    /**
     * This class displays the game to the user and accepts inputs.
     */
    class View
    {
    public:
        View(conway::Game_of_Life&);

        /**
         * Returns true if the simulation should continue.
         * Returns false if the user has fired a quit event.
         */
        bool cycle();
    private:
        conway::Game_of_Life& m_game;
        conway::Init m_init;
        conway::Window m_window;
        conway::Renderer m_renderer;
        bool m_is_playing;

        void display();
    };

    void play(conway::Game_of_Life&);
}

#endif
