#ifndef CONWAY_GAME_OF_LIFE
#define CONWAY_GAME_OF_LIFE

#include <array>
#include <vector>

namespace conway {
    enum class Cell
    {
        Black,
        White
    };

    /**
     * This class implements the logic of the Game of Life.
     */
    class Game_of_Life
    {
    public:
        /**
         * Initializes the game state with a grid of the specified width and
         * height, with all cells set to white.
         */
        Game_of_Life(int width, int height);

        int width() const { return m_width; }
        int height() const { return m_height; }

        /**
         * The API makes no guarantees about the behavior of out-of-bounds
         * indices. The implementation reserves the right to change the
         * behavior.
         */
        Cell& at(int x, int y) { return at(read_grid(), x, y); }
        const Cell& at(int x, int y) const { return at(read_grid(), x, y); }

        void tick();
    private:
        // Implementation notes:
        // This class uses a double buffer. It stores two grids in an array, a
        // read grid and write grid. It uses a Boolean as an index. After one
        // tick, it negates the Boolean so that the read and write grids switch.
        int m_width;
        int m_height;
        std::array<std::vector<Cell>, 2> m_grids;
        bool m_write_grid;

        std::vector<Cell>& write_grid() { return m_grids[m_write_grid]; }
        std::vector<Cell>& read_grid() { return m_grids[!m_write_grid]; }
        const std::vector<Cell>& read_grid() const
        {
            return m_grids[!m_write_grid];
        }
        void swap() { m_write_grid = !m_write_grid; };

        // Wraps around and allows negative indices.
        Cell& at(std::vector<Cell>&, int x, int y);
        const Cell& at(const std::vector<Cell>&, int x, int y) const;

        int count_neighbors(int x, int y) const;
    };
}

#endif
