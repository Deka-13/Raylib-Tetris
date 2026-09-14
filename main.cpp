#include "raylib.h"

// Main Window Parameters
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 1200
#define SCREEN_TITLE "TETRIS"
#define SCREEN_BG_COLOR BEIGE

// Tetris Screen Parameters
#define TSCREEN_POSX 200
#define TSCREEN_POSY 100
#define TSCREEN_WIDTH 600
#define TSCREEN_HEIGHT 1000
#define TSCREEN_COLOR BLACK

#define T_BORDER_COLOR WHITE
#define T_BORDER_THICK 10

int main(void){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(SCREEN_BG_COLOR);
        
        Rectangle T_Screen = {TSCREEN_POSX, TSCREEN_POSY, TSCREEN_WIDTH, TSCREEN_HEIGHT};
        Rectangle T_Screen_Border = {TSCREEN_POSX - T_BORDER_THICK, TSCREEN_POSY - T_BORDER_THICK, 
            TSCREEN_WIDTH + T_BORDER_THICK, TSCREEN_HEIGHT + T_BORDER_THICK};
        DrawRectangleRec(T_Screen, TSCREEN_COLOR);
        DrawRectangleLinesEx(T_Screen_Border, (float) T_BORDER_THICK, T_BORDER_COLOR);

        EndDrawing();
    }

    CloseWindow();
    return 0;

}


