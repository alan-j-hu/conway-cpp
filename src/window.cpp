#include "conway/window.h"
#include <stdexcept>

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
