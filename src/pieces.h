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

#define PIECE(cc, nn, pp) (Piece) {.c = cc, .n = nn, .p = pp}

typedef enum PieceType PieceType;
typedef enum Player Player;

typedef struct SpriteSheetPosition SpriteSheetPosition;
typedef struct Piece Piece;
typedef struct PieceManager PieceManager;
typedef struct PawnPiece PawnPiece;
typedef struct VTablePiece VTablePiece;

enum PieceType{
    King = 0,
    Queen = 1,
    Bishop = 2,
    Knight = 3,
    Rook = 4,
    Pawn = 5,
};

enum Player{
    White = 0,
    Black = 1,
};

struct SpriteSheetPosition{
    Rectangle s;
    Rectangle d;
};

struct Piece{
    char c;
    int n;
    Player p;
    PieceType t;
};

SpriteSheetPosition piece_to_ss_position(Piece pos);

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

struct VTablePiece{
    Piece (*get_info)(void*);

    void* impl;
};

struct PawnPiece{
    VTablePiece vtable;
    Piece piece;
};

PawnPiece* create_pawn(Piece piece);

Piece get_pawn_info(PawnPiece* self);

#endif // PIECES_H
