#include "pieces.h"

PieceManager* create_piece_manager(const char* sprite_name){
    PieceManager* manager = malloc(sizeof(PieceManager));
    manager->pieces = malloc(32 * sizeof(VTablePiece));
    manager->sprite_name = sprite_name;
    
    return manager;
}

void destroy_piece_manager(PieceManager* self){
    free(self->pieces);
    free(self);
}
