#include "canvas.hpp"

void DrawCanvas(Canvas canvas) {
    Rectangle canvas_screen = { canvas.pos_x, canvas.pos_y, canvas.width, canvas.height };
    DrawRectangleRec(canvas_screen, canvas.color);

    if (canvas.has_border) {
        Rectangle canvas_screen_border = {
            canvas.pos_x - canvas.border_thick, 
            canvas.pos_y - canvas.border_thick, 
            canvas.width + canvas.border_thick * 2, 
            canvas.height + canvas.border_thick * 2
        };
        DrawRectangleLinesEx(canvas_screen_border, canvas.border_thick, canvas.border_color);
    }
}

// Position Offset Helper Functions
Rectangle offset_pos(Canvas c, Rectangle r) {
    return Rectangle{ c.pos_x + r.x, c.pos_y + r.y, r.width, r.height };
}

Vector2 offset_pos(Canvas c, Vector2 v) {
    return Vector2{ c.pos_x + v.x, c.pos_y + v.y };
}
