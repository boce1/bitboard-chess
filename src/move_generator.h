#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include "board.h"
#include "attack.h"
#include "bitboard.h"
#include <stdint.h>

typedef enum {
    not_promoting, promoting
} promoted_flag;

typedef enum {
    not_capturing, capturing 
} capture_flag;

typedef enum {
    not_double_push, double_push
} double_push_flag;

typedef enum {
    not_enpassant, enpassant
} enpassant_flag;

typedef enum {
    not_castiling, castiling
} castiling_flag;

// 1111 in binary, other pieces are from the bitboard.h definitions (0 - 11)
#define no_piece 0

#define encode_move(source, target, piece, promoted, capture, double_push, enpassant, castiling) \
    (source) | (target << 6) | (piece << 12) | \
    (promoted << 16) | (capture << 20) | (double_push << 21) | \
    (enpassant << 22) | (castiling << 23)
#define get_move_source(move) ((move) & 0x3f)
#define get_move_target(move) (((move) & 0xfc0) >> 6)
#define get_move_piece(move) (((move) & 0xf000) >> 12)
#define get_move_promoted(move) (((move) & 0xf0000) >> 16)
#define get_move_capture(move) ((move) & 0x100000)
#define get_move_double_push(move) ((move) & 0x200000)
#define get_move_enpassant(move) ((move) & 0x400000)
#define get_move_castiling(move) ((move) & 0x800000)


typedef struct {
    int moves[256]; // array to store moves, max 256 moves per position
    int count; // number of moves in the array
} Moves;

// first implement logic
void generate_moves(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, Moves* move_list);
void generate_pawn_moves(Board* board, leaper_moves_masks* leaper_masks, int piece, Moves* move_list);
void generate_king_castle(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, int piece, Moves* move_list);
void generate_king_moves(Board* board, leaper_moves_masks* leaper_masks, int piece, Moves* move_list);
void generate_knight_moves(Board* board, leaper_moves_masks* leaper_masks, int piece, Moves* move_list);
void generate_bishop_moves(Board* board, slider_moves_masks* slider_masks, int piece, Moves* move_list);
void generate_rook_moves(Board* board, slider_moves_masks* slider_masks, int piece, Moves* move_list);
void generate_queen_moves(Board* board, slider_moves_masks* slider_masks, int piece, Moves* move_list);

extern const char promoted_pieces[128];

void print_move(int move);
void print_move_list(Moves* moves);
void add_move(Moves* moves, int move);

/*
    encoding/deconding moves
    
    source square
    target square
    piece
    promotion piece (pawn is gonna get promoted to bishop, rook, queen or knight)
    capture flag
    double push flag
    enpassant flag
    castiling flag

    - target and source square are encoded as 6 bits each, representing the 64 (2^6) squares on the board
    - piece and promotion piece are encoded as 4 bits each, representing the 12 pieces ()
    - capture flag, double push flag, enpassant flag, castling flag are encoded as 1 bit each
    - total size of the move is 6 + 6 + 4 + 4 + 1 + 1 + 1 + 1 = 24 bits (3 bytes)

    0000 0000 0000 0000 0011 1111  source square mask      0x3f  
    0000 0000 0000 1111 1100 0000  target square mask      0xfc0
    0000 0000 1111 0000 0000 0000  piece mask              0xf000
    0000 1111 0000 0000 0000 0000  promotion piece mask    0xf0000
    0001 0000 0000 0000 0000 0000  capture flag mask       0x100000
    0010 0000 0000 0000 0000 0000  double push flag mask   0x200000
    0100 0000 0000 0000 0000 0000  enpassant flag mask     0x400000
    1000 0000 0000 0000 0000 0000  castling flag mask      0x800000
*/

#endif // MOVE_GENERATOR_H