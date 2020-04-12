#include "conway/render.h"
#include <stdexcept>

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
