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

    // Creates a random block sequence starting from grid_start cell
    void CreateTetromino();
    
    struct Cell {
        bool is_block = false;
        bool is_falling = false;
    };

    // Function for reading cell values
    const Cell& get_cell(size_t index) const { 
        return grid[index]; 
    }

    // Function for blocks to fall to level below
    void DoFallStep();

    // check if game is over
    bool IsGameOver() const { return game_over; }

private:

    std::vector<Cell> grid = std::vector<Cell>(GRID_SIZE, {false, false});
    std::tuple<int, int> grid_start = {GRID_WIDTH / 2 - 2, 1};
    int score = 0;
    bool game_over = false;

    // Converts 2D coordinates into TetrisGrid linear array index
    constexpr std::optional<int> get_index(int x, int y) const;

    void create_block(int x, int y);
};

#endif // TETRIS_GRID_HPP
