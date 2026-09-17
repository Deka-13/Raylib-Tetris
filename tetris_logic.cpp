#include "raylib.h"
#include "screen_config.h"

#include <vector>
#include <tuple>

class TetrisGrid {
private:
    using is_falling = bool;
    using is_block = bool;
    using grid_cell = std::tuple<is_block, is_falling>;

    std::vector<grid_cell> grid(GRID_SIZE, {false, false});
    std::tuple<int, int> grid_start = {GRID_WIDTH / 2 - 2, 1};
    int score = 0;

    constexpr int get_index(int x, int y) const {
        return (y * GRID_WIDTH + x);
    }

public:
    TetrisGrid() = default;

    enum class TetrominoType = {I, O, T, L, S};

    void CreateTetromino(TetrominoType tetromino){
        int start_x = std::get<0>(grid_start);
        int start_y = std::get<1>(grid_start);
        switch (tetromino){
            case I:
                for (int i = 0; i != 4; ++i){
                    int index = get_index(start_x + i, start_y);
                    std::get<0>(grid[index]) = true;
                    std::get<1>(grid[index]) = true;
                }
        }

    }


    
}
