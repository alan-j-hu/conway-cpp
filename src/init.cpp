#include "conway/init.h"
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
