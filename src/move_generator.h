#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include "board.h"
#include "attack.h"
#include "bitboard.h"
#include "zoobrist_hash.h"
#include <stdint.h>
#include <string.h>

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

// 0 in binary, other pieces are from the bitboard.h definitions (0 - 11)
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
extern const int castling_rights_vals[64];

void print_move(int move);
void print_move_list(Moves* moves);
void add_move(Moves* moves, int move);
void init_move_list(Moves* move_list);

/*
Board
    uint64_t pieces[12]; // 12 types of pieces (6 for each color)
    uint64_t occupancies[3]; // 3 occupancies: white, black, both
    int side_to_move; // white, black
    int en_passant_square;
    int castling_rights; // bitmask for castling rights (white kingside, white queenside, black kingside, black queenside)

board.pieces size 96
board.occupancies size 24
*/

#define copy_board(board) \
    uint64_t bitboards_copy[12], occupancies_copy[3]; \
    int side_copy, enpassant_copy, castle_copy; \
    memcpy(bitboards_copy, (board)->pieces, 96); \
    memcpy(occupancies_copy, (board)->occupancies,  24); \
    side_copy = (board)->side_to_move; enpassant_copy = (board)->en_passant_square; castle_copy = (board)->castling_rights; \

// take back must be called in the same scope as copy_board
// take_back must not be called before copy_board
#define take_back(board) \
    memcpy((board)->pieces, bitboards_copy, 96); \
    memcpy((board)->occupancies, occupancies_copy, 24); \
    (board)->side_to_move = side_copy; (board)->en_passant_square = enpassant_copy; (board)->castling_rights = castle_copy; \

typedef enum { all_moves, only_captures } move_flags;

int make_move(Board* board, int move, int move_flag, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, zoobrist_hash_keys* hash_keys); // move_flag can be all_moves or only_captures

/*
    ----------------encoding/deconding moves-------------------
    
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
    ----------------------------------------------------------------------

    -------------------------castling rights-----------------------------
    castiling bits
    wk = 1, wq = 2, bk = 4, bq = 8
  
    move update

    white king moved            1100    12
    white kings rook moved      1110    14
    white queens rook moved     1101    13

    black king moved            0011    3
    black kings rook moved      1011    11
    black queens rook moved     0111    7

    move update having all rights
    castling right & 1111

    new castiling rights = castling rights & move update
    ----------------------------------------------------------------------

*/

#endif // MOVE_GENERATOR_H