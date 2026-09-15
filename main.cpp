#include "raylib.h"
#include "canvas.hpp"
#include "screen_config.hpp"

int main(void){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(SCREEN_BG_COLOR);
        
        Canvas Tetris_Screen{TSCREEN_POSX, TSCREEN_POSY, TSCREEN_WIDTH, TSCREEN_HEIGHT, TSCREEN_COLOR, true, T_BORDER_THICK, T_BORDER_COLOR};
        DrawCanvas(Tetris_Screen);

        EndDrawing();
    }

    CloseWindow();
    return 0;

}


