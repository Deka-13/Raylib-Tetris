#ifndef TETRIS_GRID_HPP
#define TETRIS_GRID_HPP

#include "raylib.h"
#include "screen_config.hpp"

#include <vector>
#include <tuple>
#include <optional>

class TetrisGrid {
public:
    enum class TetrominoType { I, O, T, L, S };

    TetrisGrid();

    // Creates a block sequence starting from grid_start cell
    void CreateTetromino(TetrominoType tetromino);
    
    using is_falling = bool;
    using is_block = bool;
    using grid_cell = std::tuple<is_block, is_falling>;

    // Function for reading cell values
    const grid_cell& get_cell(size_t index) const { 
        return grid[index]; 
    }

private:

    std::vector<grid_cell> grid = std::vector<grid_cell>(GRID_SIZE, {false, false});
    std::tuple<int, int> grid_start = {GRID_WIDTH / 2 - 2, 1};
    int score = 0;

    // Converts 2D coordinates into TetrisGrid linear array index
    constexpr std::optional<int> get_index(int x, int y) const;

    void create_block(int x, int y);
};

#endif // TETRIS_GRID_HPP
