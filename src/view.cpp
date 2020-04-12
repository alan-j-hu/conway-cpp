#include "conway/view.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

conway::View::View(conway::Game_of_Life& game)
    : m_game(game),
      m_init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER),
      m_window(
          "Conway's Game of Life", 0, 0,
          game.width() * conway::CELL_SIDE_LENGTH,
          game.height() * conway::CELL_SIDE_LENGTH,
          0),
      m_renderer(m_window, -1, SDL_RENDERER_SOFTWARE),
      m_is_playing(true)
{
    display();
}

void conway::View::display()
{
    for(int y = 0; y < m_game.height(); ++y) {
        for(int x = 0; x < m_game.width(); ++x) {
            if(m_game.at(x, y) == conway::Cell::Black) {
                SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 255);
            } else {
                SDL_SetRenderDrawColor(m_renderer.get(), 255, 255, 255, 255);
            }
            const SDL_Rect rect {
                x * conway::CELL_SIDE_LENGTH,
                y * conway::CELL_SIDE_LENGTH,
                conway::CELL_SIDE_LENGTH,
                conway::CELL_SIDE_LENGTH
            };
            SDL_RenderFillRect(m_renderer.get(), &rect);
        }
    }
    SDL_RenderPresent(m_renderer.get());
}

bool conway::View::cycle()
{
    int mouse_x = 0;
    int mouse_y = 0;
    bool mouse_clicked = false;

    while(auto event = conway::poll_event()) {
        switch(event->type) {
        case SDL_QUIT:
            return false;
        case SDL_KEYDOWN:
            if(event->key.keysym.sym == SDLK_SPACE) {
                m_is_playing = !m_is_playing;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            auto button = event->button.button;
            if(button == SDL_BUTTON_LEFT) {
                mouse_x = event->button.x;
                mouse_y = event->button.y;
                mouse_clicked = true;
            }
            break;
        }
    }

    if(m_is_playing) {
        m_game.tick();
        display();
#ifndef __EMSCRIPTEN__
        // If the user attempts to quit while SDL is delaying, the event
        // simply gets queued. The pause isn't noticeable.
        SDL_Delay(64);
#endif
    } else if(mouse_clicked) {
        int idx_x = mouse_x / conway::CELL_SIDE_LENGTH;
        int idx_y = mouse_y / conway::CELL_SIDE_LENGTH;
        conway::Cell& cell = m_game.at(idx_x, idx_y);
        if(cell == conway::Cell::Black) {
            cell = conway::Cell::White;
        } else {
            cell = conway::Cell::Black;
        }
        display();
    }

    return true;
}

void main_loop(void* view)
{
    reinterpret_cast<conway::View*>(view)->cycle();
}

void conway::play(conway::Game_of_Life& game)
{
    conway::View view(game);
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(main_loop, &view, 0, true);
#else
    while(view.cycle());
#endif
}
