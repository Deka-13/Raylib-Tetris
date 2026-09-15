#include "raylib.h"

struct Canvas {    
    float pos_x = 0;
    float pos_y = 0;
    float width = 200;
    float height = 200;
    Color color = WHITE;

    bool has_border = false;
    float border_thick = 2;
    Color border_color = BLACK;
};

void DrawCanvas(Canvas canvas){

    Rectangle canvas_screen = {canvas.pos_x, canvas.pos_y, canvas.width, canvas.height};
    DrawRectangleRec(canvas_screen, canvas.color);
    
    if (canvas.has_border){
        Rectangle canvas_screen_border = {canvas.pos_x - canvas.border_thick, canvas.pos_y - canvas.border_thick, 
            canvas.width + canvas.border_thick * 2, canvas.height + canvas.border_thick * 2};
        DrawRectangleLinesEx(canvas_screen_border, canvas.border_thick, canvas.border_color);
    }

}
