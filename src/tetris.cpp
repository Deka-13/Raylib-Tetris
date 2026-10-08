#include "tetris.hpp"
#include "user_config.hpp"

// TetrisGrid Class Functions
void TetrisGrid::Rotate() {
    if (!is_tetromino) return;

    // 1. Clear current falling cells from the grid
    for (auto& cell : grid) {
        if (cell.state_cell == Cell::State::Falling) {
            cell.state_cell = Cell::State::Empty;
        }
    }

    // 2. Square pieces (O-tetromino) do not rotate
    bool is_square = true;
    const auto square_offsets = GetOffsets(TetrominoType::O);
    for (std::size_t i = 0; i < offsets.size(); ++i) {
        if (offsets[i].x != square_offsets[i].x || offsets[i].y != square_offsets[i].y) {
            is_square = false;
            break;
        }
    }
    if (is_square) {
        SetTetromino();
        return;
    }

    // 3. Backup old offsets and pivot
    auto old_offsets = offsets;
    Point old_pivot = pivot;

    // 4. Apply standard rotation transformation (90 degrees clockwise: (x, y) -> (-y, x))
    for (auto& offset : offsets) {
        int x = offset.x;
        int y = offset.y;
        offset.x = -y;
        offset.y = x;
    }

    // 5. Define potential kick adjustments (test normal first, then nudge left, right, or up)
    constexpr std::array<Point, 4> kick_tests = {{
        {0, 0},   // No shift (standard rotation check)
        {1, 0},   // Shift right
        {-1, 0},  // Shift left
        {0, -1}   // Shift up (crucial for floor rotations)
    }};

    bool successful_rotation = false;

    for (const auto& kick : kick_tests) {
        pivot.x = old_pivot.x + kick.x;
        pivot.y = old_pivot.y + kick.y;

        bool collision = false;
        for (const auto& offset : offsets) {
            Point cell_pos = GetOffsetCoordinates(offset.x, offset.y);
            auto index = GetIndex(cell_pos.x, cell_pos.y);

            // Check out of bounds or colliding with a locked block
            if (!index.has_value() || grid[static_cast<std::size_t>(index.value())].state_cell == Cell::State::Locked) {
                collision = true;
                break;
            }
        }

        if (!collision) {
            successful_rotation = true;
            break; // Found a valid spot, keep this kick
        }
    }

    // 6. If all kicks failed, completely revert offsets and pivot
    if (!successful_rotation) {
        offsets = old_offsets;
        pivot = old_pivot;
    }

    // 7. Redraw the tetromino on the grid
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

    // Check if any falling block will collide with the floor or a locked block below it.
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

    // Act based on collision status
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
        ++pivot.y;
        SetTetromino();
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
