#ifndef BOARD_H
#define BOARD_H

#include "bitboard.h"
#include <stdlib.h>
#include <stdint.h>

/*
    0001 white king can castle to the king side / 1
    0010 white king can castle to the queen side / 2
    0100 black king can castle to the king side / 4
    1000 black king can castle to the queen side / 8
*/
typedef enum {
    wk = 1, wq = 2, bk = 4, bq = 8
} castling_bits;

typedef enum {
    P, N, B, R, Q, K, p, n, b, r, q, k
} piece;

typedef struct {
    uint64_t pieces[12]; // 12 types of pieces (6 for each color)
    uint64_t occupancies[3]; // 3 occupancies: white, black, both
    int side_to_move; // white, black
    int en_passant_square;
    int castling_rights; // bitmask for castling rights (white kingside, white queenside, black kingside, black queenside)
} Board;

extern const char ascii_pieces[12];
extern const int char_to_piece[128]; // maps ASCII characters to piece types

Board* create_board();
void print_board(Board* board);

#endif // BOARD_H