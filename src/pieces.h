#ifndef PIECES_H
#define PIECES_H

#include <stdlib.h>
#include <string.h>

#include "raylib.h"

#define PIECE(cc, nn, pp, tt) (Piece) {.c = cc, .n = nn, .p = pp, .t = tt}
#define CALL(i, f) i.f(i.impl)

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

void draw_piece(Texture2D spritesheet, VTablePiece piece);
SpriteSheetPosition piece_to_ss_position(Piece pos);

struct PieceManager{
    const char* sprite_name;
    VTablePiece* pieces;
    Texture2D spritesheet;
};

PieceManager* create_piece_manager(const char* sprite_name);
void push_piece(PieceManager* self, Piece piece);
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
