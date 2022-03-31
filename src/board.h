#ifndef BOARD_H
#define BOARD_H

#include "stdint.h"
#include "raylib.h"

typedef struct Board Board;

struct Board{
    int32_t x, y;
    RenderTexture2D texture;
};

Board create_board();
void draw_board(Board* self);
void destroy_board(Board* self);

bool is_color_equal(Color c1, Color c2);

#endif // BOARD_H
