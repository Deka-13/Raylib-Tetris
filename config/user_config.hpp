#ifndef USER_CONFIG_HPP
#define USER_CONFIG_HPP

#include "raylib.h"

// Main Window Parameters
constexpr int WINDOW_WIDTH = 1600;
constexpr int WINDOW_HEIGHT = 1200;

constexpr Color WINDOW_COLOR = BLACK;

// Tetris Window Parameters
constexpr int TETRIS_WINDOW_POSX = 200;
constexpr int TETRIS_WINDOW_POSY = 100;

constexpr int BLOCK_SIZE = 50;

constexpr Color TETRIS_WINDOW_COLOR = BLACK;

constexpr Color TETRIS_BORDER_COLOR = WHITE;
constexpr int TETRIS_BORDER_THICK = 6;

// Tetris Grid Parameters
constexpr int GRID_WIDTH = 10;
constexpr int GRID_HEIGHT = 20;

constexpr Color BLOCK_COLOR = WHITE;

// Gameplay Parameters
constexpr int GAME_FPS = 60;
constexpr int INITIAL_SPEED = GAME_FPS / 2.5;

#endif // USER_CONFIG_HPP
