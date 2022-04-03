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
        .d = (Rectangle){d_x, d_y, 1884 / 18, 604 / 6},
    };
}

PieceManager* create_piece_manager(const char* sprite_name){
    PieceManager* manager = malloc(sizeof(PieceManager));

    //TODO: an advanced container for pieces (null checks etc...)
    manager->pieces.data = malloc(32 * sizeof(VTablePiece));
    manager->pieces.length = 32;

    manager->sprite_name = sprite_name;
    manager->spritesheet = LoadTexture(manager->sprite_name);

    setup_piece_manager(manager);
    
    return manager;
}

void setup_piece_manager(PieceManager* self){
    PawnPiece* pawn1 = create_pawn(PIECE('a', 2, Black));
    self->pieces.data[0] = pawn1->vtable;
    PawnPiece* pawn2 = create_pawn(PIECE('b', 2, Black));
    self->pieces.data[1] = pawn2->vtable;
}

void draw_piece_manager(PieceManager* self){
    draw_piece(self->spritesheet, self->pieces.data[0]);
    draw_piece(self->spritesheet, self->pieces.data[1]);
}

void destroy_piece_manager(PieceManager* self){
    //TODO: memory leak on pieces[].impl
    free(self->pieces.data);
    free(self);
}


PawnPiece* create_pawn(Piece piece){
    piece.t = Pawn;
    PawnPiece* pawn = malloc(sizeof(PawnPiece));
    *pawn = (PawnPiece){
        .vtable = (VTablePiece){
            .get_info = get_pawn_info,
            .impl = pawn,
        },
        .piece = piece,
    };

    return pawn;
}

Piece get_pawn_info(PawnPiece* self){
    return self->piece;
}
