#ifndef PIECES_H
#define PIECES_H

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "raylib.h"

#define PIECE(cc, nn, pp, tt) (Piece) {.c = cc, .n = nn, .p = pp, .t = tt}
#define CALL(i, f) i.f(i.impl)
#define ISNULL(i) (i.impl == NULL)

typedef enum PieceType PieceType;
typedef enum Player Player;

typedef struct SpriteSheetPosition SpriteSheetPosition;
typedef struct PawnPiece PawnPiece;
typedef struct Piece Piece;
typedef struct PieceManager PieceManager;
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
Piece rectangle_to_piece(Rectangle rect);
Rectangle vector_to_rect(Vector2 vec);

struct VTablePiece{
    Piece (*get_info)(void*);
    void (*set_pos)(void*, char, int);
    void (*on_click)(void*);
    void (*draw_possible_moves)(void*);

    void* impl;
};

struct PieceManager{
    const char* sprite_name;
    Texture2D spritesheet;

    VTablePiece clicked_piece;
    VTablePiece* pieces;
};

PieceManager* create_piece_manager(const char* sprite_name);
void push_piece(PieceManager* self, Piece piece);
void setup_piece_manager(PieceManager* self);
void on_mouse_click_piece_manager(PieceManager* self, Vector2 mouse_pos);
void draw_piece_manager(PieceManager* self);
void destroy_piece_manager(PieceManager* self);

struct PawnPiece{
    VTablePiece vtable;
    Piece piece;
};

PawnPiece* create_pawn(Piece piece);
Piece get_pawn_info(PawnPiece* self);
void set_pawn_pos(PawnPiece* self, char c, int n);
void on_pawn_click(PawnPiece* self);
void draw_possible_moves_pawn(PawnPiece* self);

#endif // PIECES_H
