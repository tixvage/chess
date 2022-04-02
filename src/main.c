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

    Texture2D test = LoadTexture("assets/spritesheet.png");

    printf("%d\n", test.width);
    printf("%d\n", test.height);
   
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        draw_board(&board);
        EndDrawing();
    }

    destroy_board(&board);
    
    CloseWindow();
}

