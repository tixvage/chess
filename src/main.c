#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <raylib.h>

#include "board.h"

int main(void){
    InitWindow(800, 800, "Chess");
    SetTargetFPS(120);

    Board board = create_board();
    
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(GRAY);
        draw_board(&board);
        EndDrawing();
    }

    destroy_board(&board);
    
    CloseWindow();
}

