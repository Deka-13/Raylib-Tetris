#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "raylib.h"
#include <type_traits>
#include <algorithm>

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

// Canvas drawing function
void DrawCanvas(Canvas canvas);

// Position Offset Helper Functions
Rectangle offset_pos(Canvas c, Rectangle r);
Vector2 offset_pos(Canvas c, Vector2 v);

// Clipper Helper Functions
inline bool ClipRectangle(Canvas c, Rectangle target, Rectangle& clipped) {
    float left   = (std::max)(c.pos_x, target.x);
    float right  = (std::min)(c.pos_x + c.width, target.x + target.width);
    float top    = (std::max)(c.pos_y, target.y);
    float bottom = (std::min)(c.pos_y + c.height, target.y + target.height);

    if (left < right && top < bottom) {
        clipped = Rectangle{ left, top, right - left, bottom - top };
        return true;
    }
    return false;
}

inline bool IsInBounds(Canvas c, Vector2 v) {
    return (v.x >= c.pos_x && v.x <= c.pos_x + c.width &&
            v.y >= c.pos_y && v.y <= c.pos_y + c.height);
}

// Templates for functions drawing Rectangle or Vector2 or raw 2D coordinates
template <typename Func, typename... Args>
void DrawOnCanvas(Canvas canvas, Func drawFunc, Rectangle r, Args... args) 
{
    Rectangle offset_r = offset_pos(canvas, r);
    Rectangle clipped_r;
    
    if (ClipRectangle(canvas, offset_r, clipped_r)) {
        drawFunc(clipped_r, args...);
    }
}

template <typename Func, typename... Args>
void DrawOnCanvas(Canvas canvas, Func drawFunc, Vector2 v, Args... args) 
{
    Vector2 offset_v = offset_pos(canvas, v);
    
    if (IsInBounds(canvas, offset_v)) {
        drawFunc(offset_v, args...);
    }
}

template <typename Func, typename Coord, typename... Args>
auto DrawOnCanvas(Canvas canvas, Func drawFunc, Coord x, Coord y, Args... args) 
    -> std::enable_if_t<std::is_arithmetic_v<Coord>> 
{
    Vector2 offset_v = Vector2{ (float)canvas.pos_x + x, (float)canvas.pos_y + y };
    
    if (IsInBounds(canvas, offset_v)) {
        drawFunc(offset_v.x, offset_v.y, args...);
    }
}

#endif // CANVAS_HPP
