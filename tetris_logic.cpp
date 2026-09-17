#include "raylib.h"
#include "screen_config.hpp"

#include <vector>
#include <tuple>
#include <optional>

class TetrisGrid {
private:
    using is_falling = bool;
    using is_block = bool;
    using grid_cell = std::tuple<is_block, is_falling>;

    std::vector<grid_cell> grid;
    std::tuple<int, int> grid_start = {GRID_WIDTH / 2 - 2, 1};
    int score = 0;

    constexpr std::optional<int> get_index(int x, int y) const {
        return (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT + 1)
            ? std::optional<int>(y * GRID_WIDTH + x)
            : std::nullopt;
    }

public:
    TetrisGrid() : grid(GRID_SIZE, grid_cell{false, false}) {}
    enum class TetrominoType{I, O, T, L, S};

    void CreateTetromino(TetrominoType tetromino){
        int start_x = std::get<0>(grid_start);
        int start_y = std::get<1>(grid_start);
        switch (tetromino){
            case TetrominoType::I:
                for (int i = 0; i != 4; ++i){
                    int index = get_index(start_x + i, start_y);
                    std::get<0>(grid[index]) = true;
                    std::get<1>(grid[index]) = true;
                }
        }

    }
};
