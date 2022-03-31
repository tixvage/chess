#include "board.h"

Board create_board(){
    RenderTexture2D texture = LoadRenderTexture(800, 800);

    Color current_color = BLACK;
    
    BeginTextureMode(texture);
    for(int32_t x = 0; x < 8; x++){
        current_color = is_color_equal(current_color, BLACK) ? WHITE : BLACK;
        for(int32_t y = 0; y < 8; y++){
            current_color = is_color_equal(current_color, BLACK) ? WHITE : BLACK;
            DrawRectangle(x * 100, y * 100, 100, 100, current_color);
        }
    }
    EndTextureMode();
    
    return (Board){
        .x = 8,
        .y = 8,
        .texture = texture,
    };
}

void destroy_board(Board* self){
    UnloadRenderTexture(self->texture);
}

void draw_board(Board* self){
    DrawTextureRec(self->texture.texture, (Rectangle){ 0, 0, self->texture.texture.width, -self->texture.texture.height }, (Vector2){ 0, 0 }, WHITE);
}

bool is_color_equal(Color c1, Color c2){
    return (c1.r == c2.r && c1.g == c2.g &&
            c1.b == c2.b && c1.a == c2.a);
}
