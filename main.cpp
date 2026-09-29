#include "raylib.h"
#include <ctime>

#include "canvas.hpp"
#include "screen_config.hpp"
#include "tetris_logic.hpp"

void DrawBlocksOnCanvas(const Canvas& canvas, const TetrisGrid &t_grid){
    for (int i = GRID_WIDTH; i != GRID_SIZE; ++i){
        if ((t_grid.get_cell(i)).is_block){
            int row = i / GRID_WIDTH;
            int col = i % GRID_WIDTH;
            Rectangle block = {
                static_cast<float>(col * BLOCK_SIZE), 
                static_cast<float>((row - 1) * BLOCK_SIZE), 
                static_cast<float>(BLOCK_SIZE), 
                static_cast<float>(BLOCK_SIZE)
            };
            DrawOnCanvas(canvas, DrawRectangleRec, block, BLOCK_COLOR);
        }
    }
}

int main(void){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(GAME_FPS);
    srand(time(NULL));
    TetrisGrid Tetris_Grid = TetrisGrid();
    int time_count = 1;
    int speed = INITIAL_SPEED;

    Tetris_Grid.CreateTetromino();

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(SCREEN_BG_COLOR);
        
        Canvas Tetris_Screen{
                            TSCREEN_POSX, TSCREEN_POSY, 
                            TSCREEN_WIDTH, TSCREEN_HEIGHT,
                            TSCREEN_COLOR, true, 
                            T_BORDER_THICK, T_BORDER_COLOR };
        DrawCanvas(Tetris_Screen);
        if (time_count == speed && !Tetris_Grid.IsGameOver()) {
            Tetris_Grid.DoFallStep();
            time_count = 1;
        }
        DrawBlocksOnCanvas(Tetris_Screen, Tetris_Grid);

        EndDrawing();
        ++time_count;
    }

    CloseWindow();
    return 0;

}


