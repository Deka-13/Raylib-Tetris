#ifndef CANVAS_H
#define CANVAS_H

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

void DrawCanvas(Canvas canvas);

#endif // CANVAS_H
