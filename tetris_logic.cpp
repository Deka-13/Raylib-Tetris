#include "tetris_logic.hpp"

TetrisGrid::TetrisGrid() : grid(GRID_SIZE, grid_cell{false, false}) {}

constexpr std::optional<int> TetrisGrid::get_index(int x, int y) const {
    return (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT + 1)
        ? std::optional<int>(y * GRID_WIDTH + x)
        : std::nullopt;
}

void TetrisGrid::create_block(int x, int y) {
    auto index = get_index(x, y);
    if (index.has_value()) {
        std::get<0>(grid[*index]) = true;
        std::get<1>(grid[*index]) = true;
    }
}

void TetrisGrid::CreateTetromino(TetrominoType tetromino) {
    int start_x = std::get<0>(grid_start);
    int start_y = std::get<1>(grid_start);

    switch (tetromino) {
        case TetrominoType::I:
            for (int i = 0; i < 4; ++i) {
                create_block(start_x + i, start_y);
            }
            break;
        case TetrominoType::O:
            ++start_x;
            create_block(start_x, start_y);
            create_block(start_x + 1, start_y);
            create_block(start_x, start_y - 1);
            create_block(start_x + 1, start_y - 1);
            break;
        case TetrominoType::T:
            for (int i = 0; i < 3; ++i) {
                create_block(start_x + i, start_y);
            }
            create_block(start_x + 1, start_y - 1);
            break;
        case TetrominoType::L:
            for (int i = 0; i < 3; ++i) {
                create_block(start_x + i, start_y);
            }
            create_block(start_x + 2, start_y - 1);
            break;
        case TetrominoType::S:
            ++start_x;
            create_block(start_x, start_y);
            create_block(start_x + 1, start_y);
            create_block(start_x + 1, start_y - 1);
            create_block(start_x + 2, start_y - 1);
            break;
    }
}
