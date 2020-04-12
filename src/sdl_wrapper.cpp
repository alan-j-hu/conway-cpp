#include "conway/sdl_wrapper.h"
#include <stdexcept>

conway::Init::Init(Uint32 flags)
{
    if(SDL_Init(flags) != 0) {
        throw std::runtime_error(SDL_GetError());
    }
}

conway::Init::~Init()
{
    SDL_Quit();
}

conway::Window::Window(
    std::string name,
    int x,
    int y,
    int w,
    int h,
    Uint32 flags)
    : m_window(SDL_CreateWindow(name.c_str(), x, y, w, h, flags))
{
    if(m_window.get() == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }
}

void conway::Window::Window::Deleter::operator()(SDL_Window* ptr)
{
    SDL_DestroyWindow(ptr);
}

conway::Renderer::Renderer(conway::Window& window, int index, Uint32 flags)
    : m_renderer(SDL_CreateRenderer(window.get(), index, flags))
{
    if(m_renderer.get() == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }
}

void conway::Renderer::Deleter::operator()(SDL_Renderer* ptr)
{
    SDL_DestroyRenderer(ptr);
}

std::optional<SDL_Event> conway::poll_event()
{
    SDL_Event event;
    if(SDL_PollEvent(&event)) {
        return std::optional(event);
    }
    return std::nullopt;
}
