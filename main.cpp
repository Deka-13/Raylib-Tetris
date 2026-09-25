#include "raylib.h"
#include <ctime>

#include "canvas.hpp"
#include "screen_config.hpp"
#include "tetris_logic.hpp"

void DrawBlocksOnCanvas(Canvas canvas, TetrisGrid t_grid){
    for (int i = GRID_WIDTH; i != GRID_SIZE; ++i){
        if (std::get<0>(t_grid.get_cell(i))){
            int row = i / GRID_HEIGHT;
            int col = i % GRID_WIDTH;
            Rectangle block = {
                static_cast<float>(col * BLOCK_SIZE), 
                static_cast<float>(row * BLOCK_SIZE), 
                static_cast<float>(BLOCK_SIZE), 
                static_cast<float>(BLOCK_SIZE)
            };
            DrawOnCanvas(canvas, DrawRectangleRec, block, BLOCK_COLOR);
        }
    }
}

int main(void){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(60);
    srand(time(NULL));
    TetrisGrid Tetris_Grid = TetrisGrid();

    TetrisGrid::TetrominoType tetromino = static_cast<TetrisGrid::TetrominoType>(GetRandomValue(0, 4));
    Tetris_Grid.CreateTetromino(tetromino);

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(SCREEN_BG_COLOR);
        
        Canvas Tetris_Screen{TSCREEN_POSX, TSCREEN_POSY, TSCREEN_WIDTH, TSCREEN_HEIGHT, TSCREEN_COLOR, true, T_BORDER_THICK, T_BORDER_COLOR};
        DrawCanvas(Tetris_Screen);
        DrawBlocksOnCanvas(Tetris_Screen, Tetris_Grid);

        EndDrawing();
    }

    CloseWindow();
    return 0;

}


