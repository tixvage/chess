#include "pieces.h"
#include <stdio.h>

void draw_piece(Texture2D spritesheet, VTablePiece piece){
    SpriteSheetPosition ss_pos = piece_to_ss_position(CALL(piece, get_info));
    DrawTexturePro(spritesheet, ss_pos.s, ss_pos.d, (Vector2){0, 0}, 0, WHITE);
}

SpriteSheetPosition piece_to_ss_position(Piece piece){
    float s_x, s_y, d_x, d_y = 0.f;

    s_x = piece.t * (1884 / 6);
    s_y = piece.p * (604 / 2);

    d_x = (piece.c - 97) * 100;
    d_y = (8 - piece.n) * 100;

    return (SpriteSheetPosition){
        .s = (Rectangle){s_x, s_y, 314, 302},
        .d = (Rectangle){d_x, d_y, 100, 100},
    };
}

Piece rectangle_to_piece(Rectangle rect){
    //100 = (x - 97) * 100
    //100/100 = x - 97
    //(100/100) + 97 = x

    char c = 0;
    c = (rect.x / 100) + 97;

    int n = 0;
    n = -((rect.y / 100) - 8);

    return (Piece){
        .c = c,
        .n = n,
    };
}

Rectangle vector_to_rect(Vector2 vec){
    int len_x = log10(vec.x);
    float div_x = pow(10, len_x);
    int x = vec.x < 100 ? 0 : (ceil((int)vec.x / div_x) * div_x) - 100;

    int len = log10(vec.y);
    float div = pow(10, len);
    int y = vec.y < 100 ? 0 : (ceil((int)vec.y / div) * div) - 100;

    return (Rectangle){
        .x = x,
        .y = y,
        .width = 100,
        .height = 100,
    };
}

PieceManager* create_piece_manager(const char* sprite_name){
    PieceManager* manager = malloc(sizeof(PieceManager));

    manager->pieces = calloc(32, sizeof(VTablePiece));
    manager->clicked_piece = (VTablePiece){ 0 };

    manager->sprite_name = sprite_name;
    manager->spritesheet = LoadTexture(manager->sprite_name);

    setup_piece_manager(manager);
    
    return manager;
}

void push_piece(PieceManager* self, Piece piece){
    for(int i = 0; i < 32; i++){
        if(ISNULL(self->pieces[i])){
            VTablePiece vtable = { 0 };

            //TODO: add other pieces
            switch(piece.t){
            default: //Just for now
                vtable = create_pawn(piece)->vtable;
                break;
            }
            self->pieces[i] = vtable;
            break;
        }
    }
}

void setup_piece_manager(PieceManager* self){
    for(int i = 0; i < 8; i++){
        push_piece(self, PIECE('a' + i, 2, Black, Pawn));
        push_piece(self, PIECE('a' + i, 7, White, Pawn));
    }

    push_piece(self, PIECE('a', 1, Black, Rook));
    push_piece(self, PIECE('h', 1, Black, Rook));

    push_piece(self, PIECE('a', 8, White, Rook));
    push_piece(self, PIECE('h', 8, White, Rook));

    push_piece(self, PIECE('b', 1, Black, Knight));
    push_piece(self, PIECE('g', 1, Black, Knight));

    push_piece(self, PIECE('b', 8, White, Knight));
    push_piece(self, PIECE('g', 8, White, Knight));

    push_piece(self, PIECE('c', 1, Black, Bishop));
    push_piece(self, PIECE('f', 1, Black, Bishop));

    push_piece(self, PIECE('c', 8, White, Bishop));
    push_piece(self, PIECE('f', 8, White, Bishop));

    push_piece(self, PIECE('d', 1, Black, King));
    push_piece(self, PIECE('d', 8, White, King));

    push_piece(self, PIECE('e', 1, Black, Queen));
    push_piece(self, PIECE('e', 8, White, Queen));
}

void on_mouse_click_piece_manager(PieceManager* self, Vector2 mouse_pos){
    if(!ISNULL(self->clicked_piece)){
        Piece new_pos = rectangle_to_piece(vector_to_rect(mouse_pos));
        self->clicked_piece.set_pos(self->clicked_piece.impl, new_pos.c, new_pos.n);
        self->clicked_piece = (VTablePiece){ 0 };
        return;
    }

    for(int i = 0; i < 32; i++){
        if(!ISNULL(self->pieces[i])){
            VTablePiece vtable = self->pieces[i];
            Piece piece = CALL(vtable, get_info);
            SpriteSheetPosition ss_pos = piece_to_ss_position(piece);
            if(CheckCollisionPointRec(mouse_pos, ss_pos.d)){
                self->clicked_piece = vtable;
                printf("Clicked-> %c:%d\n", piece.c, piece.n);
                break;
            }
            self->clicked_piece = (VTablePiece){ 0 };
        }
    }
}

void draw_piece_manager(PieceManager* self){
    for(int i = 0; i < 32; i++){
        if(!ISNULL(self->pieces[i])){
            draw_piece(self->spritesheet, self->pieces[i]);
        }
    }
    if(!ISNULL(self->clicked_piece)){
        CALL(self->clicked_piece, draw_possible_moves);
    }
}

void destroy_piece_manager(PieceManager* self){
    for(int i = 0; i < 32; i++){
        void* impl = self->pieces[i].impl;
        if(impl != NULL){
            free(impl);
        }
    }

    free(self->pieces);
    free(self);
}


PawnPiece* create_pawn(Piece piece){
    PawnPiece* pawn = malloc(sizeof(PawnPiece));
    *pawn = (PawnPiece){
        .vtable = (VTablePiece){
            .get_info = get_pawn_info,
            .set_pos = set_pawn_pos,
            .on_click = on_pawn_click,
            .draw_possible_moves = draw_possible_moves_pawn,
            .impl = pawn,
        },
        .piece = piece,
    };

    return pawn;
}

Piece get_pawn_info(PawnPiece* self){
    return self->piece;
}

void set_pawn_pos(PawnPiece* self, char c, int n){
    self->piece.c = c;
    self->piece.n = n;
}

void on_pawn_click(PawnPiece* self){

}

void draw_possible_moves_pawn(PawnPiece* self){
    Piece position = self->piece;
    Piece move1 = (Piece){
        .c = position.c,
        .n = position.n + 1,
    };
    Piece move2 = (Piece){
        .c = position.c,
        .n = position.n + 2,
    };

    Rectangle r1 = piece_to_ss_position(move1).d;
    Rectangle r2 = piece_to_ss_position(move2).d;

    DrawRectangleRec(r1, (Color){0, 228, 48, 100});
    DrawRectangleRec(r2, (Color){0, 228, 48, 100});
}
