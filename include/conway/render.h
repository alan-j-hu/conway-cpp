#ifndef CONWAY_RENDER_H
#define CONWAY_RENDER_H

#include <memory>
#include <SDL2/SDL_render.h>
#include "conway/window.h"

namespace conway {
    class Renderer
    {
    public:
        Renderer(conway::Window&, int, Uint32);

        SDL_Renderer* get() { return m_renderer.get(); };
    private:
        struct Deleter
        {
            void operator()(SDL_Renderer*);
        };
        std::unique_ptr<SDL_Renderer, Deleter> m_renderer;
    };
}

#endif
