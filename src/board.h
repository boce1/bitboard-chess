#ifndef BOARD_H
#define BOARD_H

#include "bitboard.h"
#include "attack.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define empty_board "8/8/8/8/8/8/8/8 b - - "
#define start_position "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 "
#define tricky_position "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R b Kq e3 0 1 "
#define killer_position "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define cmk_position "r2q1rk1/ppp2ppp/2n1bn2/2b1p3/3pP3/3P1NPP/PPP1NPB1/R1BQ1RK1 b - - 0 9 "
#define repetitions "2r3k1/R7/8/1R6/8/8/P4KPP/8 w - - 0 40 "

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
void parse_fen(char *fen, Board* board);
int is_square_attacked(int square, Board* board, leaper_attack_masks* leaper_masks, slider_attack_masks* slider_masks);
void print_attacked_squares(Board* board, leaper_attack_masks* leaper_masks, slider_attack_masks* slider_masks);

#endif // BOARD_H