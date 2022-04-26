#include "pieces.h"
#include <stdio.h>
#include "assert.h"

bool is_piece_null(Piece p){
    return is_loc_null(p.l);
}

bool is_loc_null(Location l){
    return (l.c == '\0' || l.n == 0);
}

bool is_locs_eq(Location l1, Location l2){
    return (l1.c == l2.c && l1.n == l2.n);
}

void push_movement(Moves* self, Location move){
    for(size_t i = 0; i < MAX_MOVEMENT_POSSIBLITIES; i++){
        if(is_loc_null(self->can_go[i])){
            self->can_go[i] = move;
            self->length++;
            return;
        }
    }
}

void draw_piece(Texture2D spritesheet, VTablePiece piece){
    SpriteSheetPosition ss_pos = piece_to_ss_position(*(CALL(piece, get_info)));
    DrawTexturePro(spritesheet, ss_pos.s, ss_pos.d, (Vector2){0, 0}, 0, WHITE);
}

void print_table(Piece table[8][8]){
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            Piece p = table[x][y];
            if(!is_piece_null(p))
                printf("piece -> %d:%c\n", p.l.n, p.l.c);
        }
    }
}

SpriteSheetPosition piece_to_ss_position(Piece piece){
    float s_x, s_y, d_x, d_y = 0.f;

    s_x = piece.t * (1884 / 6);
    s_y = piece.p * (604 / 2);

    d_x = (piece.l.c - 97) * 100;
    d_y = (8 - piece.l.n) * 100;

    return (SpriteSheetPosition){
        .s = (Rectangle){s_x, s_y, 314, 302},
        .d = (Rectangle){d_x, d_y, 100, 100},
    };
}

Rectangle loc_to_rect(Location l){
    float x = (l.c - 97) * 100;
    float y = (8 - l.n) * 100;

    return (Rectangle){x, y, 100, 100};
}

Location rectangle_to_piece(Rectangle rect){
    char c = 0;
    c = (rect.x / 100) + 97;

    int n = 0;
    n = -((rect.y / 100) - 8);

    return (Location){
        .c = c,
        .n = n,
    };
}

Location table_array_to_loc(int f_i, int s_i){
    int n = 0;
    char c = 0;

    c = s_i + 97;
    n = f_i + 1;

    return (Location){
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

    RESET_ARRAY(manager->table);
    setup_piece_manager(manager);

    print_table(manager->table);
    
    return manager;
}

void push_piece(PieceManager* self, Piece piece){
    self->table[piece.l.n - 1][piece.l.c - 97] = piece;

    RESET_ARRAY(piece.p_m.can_go);
    piece.p_m.length = 0;
    
    for(int i = 0; i < 32; i++){
        if(ISNULL(self->pieces[i])){
            VTablePiece vtable = { 0 };

            //TODO: add other pieces
            switch(piece.t){
            default: //Just for now
                vtable = create_pawn(piece, self->table)->vtable;
                break;
            }
            self->pieces[i] = vtable;
            break;
        }
    }
}

void add_to_table(Piece* table, Piece piece){

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
        Piece* p = CALL(self->clicked_piece, get_info);
        Location new_pos = rectangle_to_piece(vector_to_rect(mouse_pos));

        bool overlap = true;
        //self->table[piece.l.n - 1][piece.l.c - 97] = piece;

        //TODO: update table
        for(int i = 0; i < p->p_m.length; i++){
            Location loc = p->p_m.can_go[i];
            Piece m_p = self->table[loc.n - 1][loc.c - 97];
            if(is_piece_null(m_p) && is_locs_eq(loc, new_pos)){
                overlap = false;
            } else if(!is_piece_null(m_p)) {
                overlap = true;
                self->clicked_piece = (VTablePiece){ 0 };
                return;
            }
        }

        RESET_ARRAY(p->p_m.can_go);
        p->p_m.length = 0;

        if(!overlap){
            CALL(self->clicked_piece, get_info)->l = new_pos;
            CALL(self->clicked_piece, on_move);
        }
        self->clicked_piece = (VTablePiece){ 0 };
        return;
    }

    for(int i = 0; i < 32; i++){
        if(!ISNULL(self->pieces[i])){
            VTablePiece vtable = self->pieces[i];
            Piece* piece = CALL(vtable, get_info);
            SpriteSheetPosition ss_pos = piece_to_ss_position(*piece);
            if(CheckCollisionPointRec(mouse_pos, ss_pos.d)){
                self->clicked_piece = vtable;
                CALL(self->clicked_piece, on_click);
                printf("Clicked-> %c:%d\n", piece->l.c, piece->l.n);
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
    //TODO: check if the can_go[i] is not overlaping with any piece
    if(!ISNULL(self->clicked_piece)){
        Piece* piece = CALL(self->clicked_piece, get_info);

        for(int i = 0; i < piece->p_m.length; i++){
            Location loc = piece->p_m.can_go[i];
            Rectangle rec = loc_to_rect(loc);
            DrawRectangleRec(rec, (Color){0, 228, 48, 100});
        }
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


PawnPiece* create_pawn(Piece piece, Piece (*table)[8]){
    PawnPiece* pawn = malloc(sizeof(PawnPiece));
    *pawn = (PawnPiece){
        .vtable = (VTablePiece){
            .get_info = get_pawn_info,
            .on_move = on_pawn_move,
            .on_click = on_pawn_click,
            .impl = pawn,
        },
        .table = table,
        .piece = piece,
        .first_move = true,
    };

    return pawn;
}

Piece* get_pawn_info(PawnPiece* self){
    return &self->piece;
}

void set_pawn_pos(PawnPiece* self, char c, int n){
    self->piece.l.c = c;
    self->piece.l.n = n;
}

void on_pawn_move(PawnPiece* self){
    if(self->first_move) self->first_move = false;
}

void on_pawn_click(PawnPiece* self){
    if(self->first_move){
        Location cl = self->piece.l;
        Location ul1, ul2;
        int n1, n2;

        switch (self->piece.p){
        case White: {
            n1 = cl.n - 1;
            n2 = cl.n - 2;
        }
        break;
        
        case Black: {
            n1 = cl.n + 1;
            n2 = cl.n + 2;
        }
        break;

        default:
            assert(0 && "Unexpected player type");
        break;
        }
        
        ul1 = (Location){
            .c = cl.c,
            .n = n1,
        };
        ul2 = (Location){
            .c = cl.c,
            .n = n2,
        };

        push_movement(&self->piece.p_m, ul1);
        push_movement(&self->piece.p_m, ul2);
    } else{
        Location cl = self->piece.l;
        Location ul;
        int n1;

        switch (self->piece.p){
        case White: {
            n1 = cl.n - 1;
        }
        break;
        
        case Black: {
            n1 = cl.n + 1;
        }
        break;

        default:
            assert(0 && "Unexpected player type");
        break;
        }

        ul = (Location){
            .c = cl.c,
            .n = n1,
        };

        push_movement(&self->piece.p_m, ul);
    }
}