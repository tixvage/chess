#include "pieces.h"

PieceManager* create_piece_manager(const char* sprite_name){
    PieceManager* manager = malloc(sizeof(PieceManager));
    manager->pieces.data = malloc(32 * sizeof(VTablePiece));
    memset(manager->pieces.data, 0, 32);
    manager->pieces.length = 32;
    manager->sprite_name = sprite_name;
    manager->spritesheet = LoadTexture(manager->sprite_name);

    setup_piece_manager(manager);
    
    return manager;
}

void setup_piece_manager(PieceManager* self){
    PawnPiece* pawn1 = create_pawn(POSITION('a', 2));
    self->pieces.data[0] = pawn1->vtable;
}

void draw_piece_manager(PieceManager* self){
    DrawText(TextFormat("%d:%c", self->pieces.data[0].get_position(self->pieces.data[0].impl).n, self->pieces.data[0].get_position(self->pieces.data[0].impl).c), 300, 300, 50, BLUE);
}

void destroy_piece_manager(PieceManager* self){
    free(self->pieces.data);
    free(self);
}


PawnPiece* create_pawn(Position pos){
    PawnPiece* pawn = malloc(sizeof(PawnPiece));
    *pawn = (PawnPiece){
        .vtable = (VTablePiece){
            .get_type = get_pawn,
            .get_position = get_pawn_pos,
            .impl = pawn,
        },
        .pos = pos,
    };

    return pawn;
}

PieceType get_pawn(){
    return Pawn;
}

Position get_pawn_pos(PawnPiece* self){
    return self->pos;
}
