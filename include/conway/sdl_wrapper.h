#ifndef CONWAY_SDL_WRAPPER
#define CONWAY_SDL_WRAPPER

#include <memory>
#include <optional>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

namespace conway {
    struct Init
    {
        Init(Uint32);
        ~Init();
    };

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

    std::optional<SDL_Event> poll_event();
}

#endif
