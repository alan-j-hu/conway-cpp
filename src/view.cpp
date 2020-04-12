#include "conway/view.h"
#include "conway/events.h"
#include "conway/init.h"
#include "conway/window.h"
#include "conway/render.h"
#include <iostream>

constexpr int CELL_SIDE_LENGTH = 50;

void conway::play(conway::Game_of_Life& game)
{
    conway::Init init(SDL_INIT_EVERYTHING);
    conway::Window window(
        "Conway's Game of Life",
        0,
        0,
        game.width() * CELL_SIDE_LENGTH,
        game.height() * CELL_SIDE_LENGTH,
        0 // SDL_WINDOW_OPENGL
    );
    conway::Renderer renderer(
        window, -1,
        SDL_RENDERER_SOFTWARE
    );
    // SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
    // SDL_RenderClear(renderer.get());
    // SDL_RenderPresent(renderer.get());

    while(true) {
        while(auto event = conway::poll_event()) {
            switch(event->type) {
            case SDL_QUIT:
                return;
            }
        }
        for(int y = 0; y < game.height(); ++y) {
            for(int x = 0; x < game.width(); ++x) {
                if(game.at(x, y) == conway::Cell::Black) {
                    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
                }
                const SDL_Rect rect {
                    x * CELL_SIDE_LENGTH,
                    y * CELL_SIDE_LENGTH,
                    CELL_SIDE_LENGTH,
                    CELL_SIDE_LENGTH
                };
                SDL_RenderFillRect(renderer.get(), &rect);
            }
        }
        SDL_RenderPresent(renderer.get());
        game.tick();
    }
}
