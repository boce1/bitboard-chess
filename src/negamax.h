#ifndef NEGAMAX_H
#define NEGAMAX_H

#include "board.h"
#include "move_generator.h"
#include "perft.h"
#include "bitboard.h"
#include <stdint.h>

extern const int material_score[12];
extern const int pawn_score[64];
extern const int pawn_score[64];
extern const int knight_score[64];
extern const int bishop_score[64];
extern const int rook_score[64];
extern const int king_score[64];
extern const int mirror_score[128];

#define ALPHA -50000
#define BETA 50000

#define KILLER_MOVE_SCORE_1 9000
#define KILLER_MOVE_SCORE_2 8000
#define CAPTURE_MOVE_SCORE 10000


extern int ply; // half move counter
extern int best_move; // placeholder, remove later
extern int killer_moves[2][64];
extern int history_moves[12][64];

int quiescence(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, int alpha, int beta);
int negamax(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, int alpha, int beta, int depth);

int evaluate(Board* board);

// move ordering

// most valuable victim least valuable attacker
extern int mvv_lva[12][12];

int score_move(int move, Board* board);
void sort_moves(Moves* move_list, Board* board);
void print_move_scores(Moves* move_list, Board* board);

#endif