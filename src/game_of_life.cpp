#include "conway/game_of_life.h"
#include <utility>

conway::Game_of_Life::Game_of_Life(int width, int height)
  : m_width(width), m_height(height),
    m_grids({
        std::vector(width * height, Cell::White),
        std::vector(width * height, Cell::White)
    }),
    m_write_grid(false)
{
}

void conway::Game_of_Life::tick()
{
    for(int y = 0; y < m_height; ++y) {
        for(int x = 0; x < m_width; ++x) {
            const int count = count_neighbors(x, y);
            if(at(read_grid(), x, y) == Cell::Black) {
                if(count == 2 || count == 3) {
                    at(write_grid(), x, y) = Cell::Black;
                } else {
                    at(write_grid(), x, y) = Cell::White;
                }
            } else {
                if(count == 3) {
                    at(write_grid(), x, y) = Cell::Black;
                } else {
                    at(write_grid(), x, y) = Cell::White;
                }
            }
        }
    }
    swap();
}

inline int pos_modulo(int n, int d) {
    return (n % d + d) % d;
}

conway::Cell& conway::Game_of_Life::at(std::vector<Cell>& grid, int x, int y)
{
    return grid.at(pos_modulo(y, m_height) * m_width + pos_modulo(x, m_width));
}

const conway::Cell&
conway::Game_of_Life::at(const std::vector<Cell>& grid, int x, int y) const
{
    return grid.at(pos_modulo(y, m_height) * m_width + pos_modulo(x, m_width));
}

constexpr std::array<std::pair<int, int>, 8> neighbor_positions = {
    std::make_pair(-1, -1), std::make_pair(0, -1), std::make_pair(1, -1),
    std::make_pair(-1, 0),                         std::make_pair(1, 0),
    std::make_pair(-1, 1),  std::make_pair(0, 1),  std::make_pair(1, 1)
};

int conway::Game_of_Life::count_neighbors(int x, int y)
{
    auto& grid = read_grid();
    int count = 0;
    for(auto [x_off, y_off] : neighbor_positions) {
        if(at(grid, x + x_off, y + y_off) == Cell::Black) {
            ++count;
        }
    }
    return count;
}
