#ifndef CONWAY_WINDOW_H
#define CONWAY_WINDOW_H

#include <memory>
#include <string>
#include <SDL2/SDL_video.h>

namespace conway {
    class Window
    {
    public:
        Window(std::string, int, int, int, int, Uint32);

        SDL_Window* get() { return m_window.get(); }
    private:
        struct Deleter
        {
            void operator()(SDL_Window*);
        };
        std::unique_ptr<SDL_Window, Deleter> m_window;
    };
}

#endif
