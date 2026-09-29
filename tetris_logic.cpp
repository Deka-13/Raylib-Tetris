#include "tetris_logic.hpp"

TetrisGrid::TetrisGrid() : grid(GRID_SIZE, Cell{false, false}) {}

constexpr std::optional<int> TetrisGrid::get_index(int x, int y) const {
    return (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT + 1)
        ? std::optional<int>(y * GRID_WIDTH + x)
        : std::nullopt;
}

void TetrisGrid::create_block(int x, int y) {
    auto index = get_index(x, y);
    if (index.has_value()) {
        auto& cell = grid[*index];
        cell.is_block = true;
        cell.is_falling = true;
    }
}

void TetrisGrid::CreateTetromino() {
    int start_x = std::get<0>(grid_start);
    int start_y = std::get<1>(grid_start);

    TetrominoType tetromino = static_cast<TetrisGrid::TetrominoType>(GetRandomValue(0, 4));

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

void TetrisGrid::DoFallStep() {
    bool can_fall = true;
    
    // check if falling piece reaches floor or another block
    for (int y = 0; y < GRID_ROWS && can_fall; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            int index = y * GRID_WIDTH + x;
            if (!grid[index].is_falling) continue;

            if (y == GRID_ROWS - 1) { can_fall = false; break; }

            const Cell& below = grid[index + GRID_WIDTH];
            if (below.is_block && !below.is_falling) { can_fall = false; break; }
        }
    }
    
    // stop falling piece; check if block is in 0th row which means game over
    if (!can_fall) {
        for (int i = 0; i < GRID_WIDTH; ++i) {
            if (grid[i].is_falling) {
                game_over = true;
                return;
            }
        }
        for (auto& c : grid) c.is_falling = false; // locks piece
        TetrisGrid::CreateTetromino();
        return;
    }
    
    // move blocks to cell below from bottom to top
    for (int y = GRID_ROWS - 2; y >= 0; --y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            int index = y * GRID_WIDTH + x;
            if (grid[index].is_falling) {
                grid[index + GRID_WIDTH] = grid[index];
                grid[index] = Cell{false, false};
            }
        }
    }
}
