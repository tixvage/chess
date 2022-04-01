#ifndef PIECES_H
#define PIECES_H

//for(int x = 0; x < 10; x++){
//    for(int y = 0; y < 2; y++){
//        DrawTexturePro(test, (Rectangle){x * (test.width / 6), y * (test.height / 2), 314.17, 302.5}, (Rectangle){(x * 100), (y * 100), test.width / 18, test.height / 6}, (Vector2){0, 0}, 0, WHITE);
//    }
//}

#include "raylib.h"
#include "stdlib.h"

typedef struct PieceManager PieceManager;
typedef struct PawnPiece PawnPiece;
typedef struct VTablePiece VTablePiece;

typedef enum PieceType PieceType;

struct PieceManager{
    const char* sprite_name;
    VTablePiece* pieces;
};

PieceManager* create_piece_manager();
void destroy_piece_manager(PieceManager* self);

enum PieceType{
    King = 0,
    Rook = 1,
    Bishop = 2,
    Queen = 3,
    Knight = 4,
    Pawn = 5,
};

struct VTablePiece{
    PieceType (*get_type)();
};

struct PawnPiece{
    
};

#endif // PIECES_H
