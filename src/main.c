#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <raylib.h>

int main(void){
    InitWindow(800, 800, "Chess");
    SetTargetFPS(120);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();
}

