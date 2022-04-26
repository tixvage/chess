#ifndef PIECES_H
#define PIECES_H

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "raylib.h"

#define PIECE(cc, nn, pp, tt) (Piece) {.l = (Location){ .c = cc, .n = nn}, .p = pp, .t = tt}
#define CALL(i, f, args...) i.f(i.impl, ##args)
#define ISNULL(i) (i.impl == NULL)
#define RESET_ARRAY(array) memset(array, 0, sizeof(array))

#define MAX_MOVEMENT_POSSIBLITIES 25

typedef struct SpriteSheetPosition SpriteSheetPosition;
typedef struct PawnPiece PawnPiece;
typedef struct Location Location;
typedef struct Piece Piece;
typedef struct Moves Moves;
typedef struct PieceManager PieceManager;
typedef struct VTablePiece VTablePiece;

typedef enum{
    King = 0,
    Queen = 1,
    Bishop = 2,
    Knight = 3,
    Rook = 4,
    Pawn = 5,
    NoneT = 6,
} PieceType;

typedef enum{
    White = 0,
    Black = 1,
    NoneP = 2,
} Player;

struct SpriteSheetPosition{
    Rectangle s;
    Rectangle d;
};

struct Location{
    char c;
    int n;
};

struct Moves{
    Location can_go[MAX_MOVEMENT_POSSIBLITIES];
    int length;
};

struct Piece{
    Location l;
    Player p;
    PieceType t;
    Moves p_m;
};

bool is_piece_null(Piece p);
bool is_loc_null(Location l);
bool is_locs_eq(Location l1, Location l2);
void push_movement(Moves* self, Location move);
void draw_piece(Texture2D spritesheet, VTablePiece piece);
SpriteSheetPosition piece_to_ss_position(Piece pos);
Rectangle loc_to_rect(Location l);
Location rectangle_to_piece(Rectangle rect);
Location table_array_to_loc(int f_i, int s_i);
Rectangle vector_to_rect(Vector2 vec);

struct VTablePiece{
    Piece* (*get_info)(void*);
    void (*set_pos)(void*, char, int);
    void (*on_click)(void*);
    void (*on_move)(void*);

    void* impl;
};

struct PieceManager{
    const char* sprite_name;
    Texture2D spritesheet;

    Piece table[8][8];
    VTablePiece clicked_piece;
    VTablePiece* pieces;
};

PieceManager* create_piece_manager(const char* sprite_name);
void push_piece(PieceManager* self, Piece piece);
void add_to_table(Piece* table, Piece piece);
void setup_piece_manager(PieceManager* self);
void on_mouse_click_piece_manager(PieceManager* self, Vector2 mouse_pos);
void draw_piece_manager(PieceManager* self);
void destroy_piece_manager(PieceManager* self);

//all pieces

struct PawnPiece{
    VTablePiece vtable;
    Piece piece;
    bool first_move;
    Piece (*table)[8];
};

PawnPiece* create_pawn(Piece piece, Piece (*table)[8]);
Piece* get_pawn_info(PawnPiece* self);
void set_pawn_pos(PawnPiece* self, char c, int n);
void on_pawn_move(PawnPiece* self);
void on_pawn_click(PawnPiece* self);

#endif // PIECES_H
