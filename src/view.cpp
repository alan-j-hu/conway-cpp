#include "conway/view.h"

constexpr int CELL_SIDE_LENGTH = 16;

void conway::cycle(conway::Game_of_Life& game, conway::Renderer& renderer)
{
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

void conway::play(conway::Game_of_Life& game)
{
    conway::Init init(SDL_INIT_EVERYTHING);
    conway::Window window(
        "Conway's Game of Life",
        0,
        0,
        game.width() * CELL_SIDE_LENGTH,
        game.height() * CELL_SIDE_LENGTH,
        0
    );
    conway::Renderer renderer(
        window, -1, SDL_RENDERER_SOFTWARE
    );

    while(true) {
        while(auto event = conway::poll_event()) {
            switch(event->type) {
            case SDL_QUIT:
                return;
            }
        }
        conway::cycle(game, renderer);
        // If the user attempts to quit while SDL is delaying, the event simply
        // gets queued. The pause isn't noticeable.
        SDL_Delay(64);
    }
}
