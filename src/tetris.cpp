#include "tetris.hpp"
#include "user_config.hpp"

// TetrisGrid Class Functions
void TetrisGrid::Rotate() {
    if (!is_tetromino) return;
    for (auto& cell : grid) {
        if (cell.state_cell == Cell::State::Falling) {
            cell.state_cell = Cell::State::Empty; // Fixed: used '=' instead of '=='
        }
    }

    for (auto& offset : offsets) {
        int x = offset.x;
        int y = offset.y;

        offset.x = -y;
        offset.y = x;
    }

    SetTetromino();
}

void TetrisGrid::SetTetromino(){    
    for (auto& offset : offsets) {
        Point cell_pos = GetOffsetCoordinates(offset.x, offset.y);
        // Fixed: Unwrapped std::optional<int> using .value() and cast to std::size_t
        auto index = GetIndex(cell_pos.x, cell_pos.y);
        if (index.has_value()) {
            GetCell(static_cast<std::size_t>(index.value())).state_cell = Cell::State::Falling;
        }
    }
}

// Fixed: Removed 'static' keyword out-of-line definition
std::array<Point, 4> TetrisGrid::GetOffsets(TetrominoType type) {
    switch (type) {
        case TetrominoType::I: return {{{-1, 0}, {0, 0}, {1, 0}, {2, 0}}};
        case TetrominoType::O: return {{{0, 0}, {1, 0}, {0, -1}, {1, -1}}};
        case TetrominoType::T: return {{{-1, 0}, {0, 0}, {1, 0}, {0, -1}}};
        case TetrominoType::L: return {{{-1, 0}, {0, 0}, {1, 0}, {1, -1}}};
        case TetrominoType::S: return {{{-1, 0}, {0, 0}, {0, -1}, {1, -1}}};
        case TetrominoType::J: return {{{-1, 0}, {0, 0}, {1, 0}, {-1, -1}}};
        case TetrominoType::Z: return {{{-1, -1}, {0, -1}, {0, 0}, {1, 0}}};
    }
    return {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}};
}

// Random Tetromino Creation Logic Function
void TetrisGrid::SetRandomTetromino() {
    static std::array<TetrominoType, 7> bag = {
        TetrominoType::I,
        TetrominoType::O,
        TetrominoType::T,
        TetrominoType::L,
        TetrominoType::J,
        TetrominoType::S,
        TetrominoType::Z
    };

    static std::size_t index = bag.size();

    // Refill and shuffle the bag when empty
    if (index >= bag.size()) {
        // Fisher-Yates shuffle
        for (std::size_t i = bag.size() - 1; i > 0; --i) {
            int j = GetRandomValue(0, static_cast<int>(i));
            std::swap(bag[i], bag[j]);
        }

        index = 0;
    }

    offsets = GetOffsets(bag[index++]); // assign offsets according to shuffled type
    pivot = start;
    is_tetromino = true;
    SetTetromino();
}

void TetrisGrid::DoFallStep() {
    bool all_locked = true;
    for (auto& cell : grid) {
        if (cell.state_cell == Cell::State::Falling) {
            all_locked = false;
        }
    }
    
    if (all_locked) {
        SetRandomTetromino();
        return;
    }

    // Phase 1: Check if any falling block will collide with the floor or a locked block below it.
    bool will_collide = false;
    for (std::size_t i = grid.size(); i > 0; --i) {
        std::size_t t = i - 1;
        if (grid[t].state_cell == Cell::State::Falling) {
            // Check if it's on the bottom row or if the cell directly below is locked
            if (((grid.size() - GRID_WIDTH) <= t) || (grid[t + GRID_WIDTH].state_cell == Cell::State::Locked)) {
                will_collide = true;
                break;
            }
        }
    }

    // Phase 2: Act based on collision status
    if (will_collide) {
        // Lock all falling blocks simultaneously so they stop immediately together
        for (auto& cell : grid) {
            if (cell.state_cell == Cell::State::Falling) {
                cell.state_cell = Cell::State::Locked;
            }
        }
        is_tetromino = false;
        CheckIfFullRow();
    } else {
        // Safe to move all falling blocks down by one row.
        // Must iterate backwards (bottom to top) to prevent overwriting falling cells below.
        for (std::size_t i = grid.size(); i > 0; --i) {
            std::size_t t = i - 1;
            if (grid[t].state_cell == Cell::State::Falling) {
                grid[t].state_cell = Cell::State::Empty;
                grid[t + GRID_WIDTH].state_cell = Cell::State::Falling;
            }
        }
    }
}

void TetrisGrid::CheckIfFullRow() {
    for (std::size_t row = 0; row < grid.size(); row += GRID_WIDTH) { // Fixed: increment loop properly with '+= GRID_WIDTH'
        bool is_full_row = true;
        for (std::size_t t = 0; t < GRID_WIDTH; ++t) {
            if (grid[row + t].state_cell == Cell::State::Empty) { // Fixed: use 'row + t' instead of undefined 'i + t'
                is_full_row = false;
            }
        }
        if (is_full_row) {
            for (std::size_t t = 0; t < GRID_WIDTH; ++t) {
                grid[row + t].state_cell = Cell::State::Empty; // Fixed: clear specific row slots
                score = score + GRID_WIDTH * 10;
            }
        }
    }
}
