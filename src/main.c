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

    Texture2D test = LoadTexture("assets/spritesheet.png");

    printf("%d\n", test.width);
    printf("%d\n", test.height);
    
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        draw_board(&board);
        for(int x = 0; x < 10; x++){
            for(int y = 0; y < 2; y++){
                DrawTexturePro(test, (Rectangle){x * (test.width / 6), y * (test.height / 2), 314.17, 302.5}, (Rectangle){(x * 100), (y * 100), test.width / 18, test.height / 6}, (Vector2){0, 0}, 0, WHITE);
            }
        }
        EndDrawing();
    }

    destroy_board(&board);
    
    CloseWindow();
}

