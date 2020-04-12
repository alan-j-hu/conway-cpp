#include "conway/view.h"

void display(conway::Game_of_Life& game, conway::Renderer& renderer)
{
    for(int y = 0; y < game.height(); ++y) {
        for(int x = 0; x < game.width(); ++x) {
            if(game.at(x, y) == conway::Cell::Black) {
                SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
            } else {
                SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
            }
            const SDL_Rect rect {
                x * conway::CELL_SIDE_LENGTH,
                y * conway::CELL_SIDE_LENGTH,
                conway::CELL_SIDE_LENGTH,
                conway::CELL_SIDE_LENGTH
            };
            SDL_RenderFillRect(renderer.get(), &rect);
        }
    }
    SDL_RenderPresent(renderer.get());
}

void conway::play(conway::Game_of_Life& game)
{
    conway::Init init(SDL_INIT_EVERYTHING);
    conway::Window window(
        "Conway's Game of Life",
        0,
        0,
        game.width() * conway::CELL_SIDE_LENGTH,
        game.height() * conway::CELL_SIDE_LENGTH,
        0
    );
    conway::Renderer renderer(
        window, -1, SDL_RENDERER_SOFTWARE
    );
    bool is_playing = true;

    display(game, renderer);

    while(true) {
        int mouse_x = 0;
        int mouse_y = 0;
        bool mouse_clicked = false;

        while(auto event = conway::poll_event()) {
            switch(event->type) {
            case SDL_QUIT:
                return;
            case SDL_KEYDOWN:
                if(event->key.keysym.sym == SDLK_SPACE) {
                    is_playing = !is_playing;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                auto button = event->button.button;
                if(button == SDL_BUTTON_LEFT || button == SDL_TOUCH_MOUSEID) {
                    mouse_x = event->button.x;
                    mouse_y = event->button.y;
                    mouse_clicked = true;
                }
                break;
            }
        }

        if(is_playing) {
            game.tick();
            display(game, renderer);
            // If the user attempts to quit while SDL is delaying, the event
            // simply gets queued. The pause isn't noticeable.
            SDL_Delay(64);
        } else if(mouse_clicked) {
            int idx_x = mouse_x / conway::CELL_SIDE_LENGTH;
            int idx_y = mouse_y / conway::CELL_SIDE_LENGTH;
            conway::Cell& cell = game.at(idx_x, idx_y);
            if(cell == conway::Cell::Black) {
                cell = conway::Cell::White;
            } else {
                cell = conway::Cell::Black;
            }
            display(game, renderer);
        }
    }
}
