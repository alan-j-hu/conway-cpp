#include "conway/game_of_life.h"
#include "conway/view.h"
#include <stdexcept>
#include <iostream>

void debug(const conway::Game_of_Life& game)
{
    for(int y = 0; y < game.height(); ++y) {
        for(int x = 0; x < game.width(); ++x) {
            if(game.at(x, y) == conway::Cell::Black) {
                std::cerr << "1";
            } else {
                std::cerr << "0";
            }
        }
        std::cerr << '\n';
    }
}

int main()
{
    try {
        conway::Game_of_Life game(50, 50);
        game.at(0, 0) = conway::Cell::Black;
        game.at(1, 0) = conway::Cell::Black;
        game.at(2, 0) = conway::Cell::Black;
        conway::play(game);
    } catch(const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        return -1;
    }
    return 0;
}
