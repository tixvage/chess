#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <raylib.h>

#include "board.h"
#include "pieces.h"

int main(void){
    InitWindow(800, 800, "Chess");
    SetTargetFPS(120);

    Board board = create_board();
   
    while(!WindowShouldClose()){
        update_board(&board);
        BeginDrawing();
        ClearBackground(BLACK);
        draw_board(&board);
        EndDrawing();
    }

    destroy_board(&board);
    
    CloseWindow();
}

