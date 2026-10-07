#include "raylib.h"

#include "canvas.hpp"
#include "user_config.hpp"
#include "game_config.hpp"
#include "tetris.hpp"

void DrawBlocksOnCanvas(const Canvas& canvas, const TetrisGrid &tetris){
    BeginCanvasMode(canvas);
    for (int i = GRID_WIDTH; i != GRID_SIZE; ++i){
        if (tetris.IsCellEmpty(i)){
            int row = i / GRID_WIDTH;
            int col = i % GRID_WIDTH;
            Rectangle block = {
                static_cast<float>(col * BLOCK_SIZE), 
                static_cast<float>((row - 1) * BLOCK_SIZE), 
                static_cast<float>(BLOCK_SIZE), 
                static_cast<float>(BLOCK_SIZE)
            };
            DrawRectangleRec(block, BLOCK_COLOR);
        }
    }
    EndCanvasMode();
}

int main(void){
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(GAME_FPS);
    TetrisGrid Tetris = TetrisGrid();
    int time_count = 1;
    int speed = INITIAL_SPEED;

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WINDOW_COLOR);
        
        Canvas Tetris_Screen{
            { TETRIS_WINDOW_POSX, TETRIS_WINDOW_POSY, TETRIS_WINDOW_WIDTH, TETRIS_WINDOW_HEIGHT }, // Rectangle area
            TETRIS_WINDOW_COLOR, // Color color
            TETRIS_BORDER_THICK, // float border_thick
            TETRIS_BORDER_COLOR  // Color border_color
        };
        DrawCanvas(Tetris_Screen);
        if (time_count == speed && !Tetris.IsGameOver()) {
            Tetris.DoFallStep();
            time_count = 1;
        }
        DrawBlocksOnCanvas(Tetris_Screen, Tetris);

        EndDrawing();
        ++time_count;
    }

    CloseWindow();
    return 0;

}


