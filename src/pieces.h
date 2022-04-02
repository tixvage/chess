#ifndef PIECES_H
#define PIECES_H

//for(int x = 0; x < 10; x++){
//    for(int y = 0; y < 2; y++){
//        DrawTexturePro(test, (Rectangle){x * (test.width / 6), y * (test.height / 2), 314.17, 302.5}, (Rectangle){(x * 100), (y * 100), test.width / 18, test.height / 6}, (Vector2){0, 0}, 0, WHITE);
//    }
//}

#include <stdlib.h>
#include <string.h>

#include "raylib.h"

#define POSITION(cc, nn) (Position) {.c = cc, .n = nn}

typedef struct Position Position;
typedef struct PieceManager PieceManager;
typedef struct PawnPiece PawnPiece;
typedef struct VTablePiece VTablePiece;

typedef enum PieceType PieceType;

struct Position{
    char c;
    int n;
};

struct PieceManager{
    const char* sprite_name;
    struct{
        VTablePiece* data;
        int length;
    } pieces;
    Texture2D spritesheet;
};

PieceManager* create_piece_manager();
void setup_piece_manager(PieceManager* self);
void draw_piece_manager(PieceManager* self);
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
    Position (*get_position)(void*);

    void* impl;
};

struct PawnPiece{
    VTablePiece vtable;
    Position pos;
};

PawnPiece* create_pawn(Position pos);

PieceType get_pawn();
Position get_pawn_pos(PawnPiece* self);

#endif // PIECES_H
