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
#define PV_MOVE_SCORE 20000
#define MAX_PLY 64

#define FULL_DEPTH_MOVE 4
#define REDUCED_DEPTH_MOVE 3

// Trianglular PV table (principle variation)
// Principle variation is a move that lies along the best line of play found during the search
// The idea is storing the best moves and in the next negamax iteration first check them because they are good candidates for prunning
// they are stored in 2d matrix and they are indexed by [ply][ply]
/*
    ex.
    PV line: move1 move2 move3 ...
    ply/ply 
       0  1  2  3  4 ....
    0  m1 m2 m3 m4 
    1  0  m2 m3 m4
    2  0  0  m3 m4
    3  0  0  0  m4 
    4
    at the given ply pv moves are stored from the point it starts searching

    ply 0: e2e4
    ply 1: e7e5
    ply 2: g1f3
    ply 3: b8c6
    ply 4: f1b5
    when the ply is 2 negamax must be able to find g1f3, b8c6, f1b5
*/

typedef struct {
    int ply;
    int follow_pv; // if the current principle variation line is followed
    int score_pv;
    int pv_lenght[MAX_PLY]; // stores the ply where the PV nodes end
    int pv_table[MAX_PLY][MAX_PLY];
    int killer_moves[2][MAX_PLY];
    int history_moves[12][64]; // [piece][sqaure]
    long nodes;

} search_heuristics;

void init_search_heuristics(search_heuristics* search_data);

int quiescence(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, search_heuristics* search_data, int alpha, int beta);
int negamax(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, search_heuristics* search_data, int alpha, int beta, int depth);

int evaluate(Board* board);

// most valuable victim least valuable attacker
extern const int mvv_lva[12][12];

void enable_pv_scoring(Moves* move_list, search_heuristics* search_data);
int score_move(int move, Board* board, search_heuristics* search_data);
void merge(Moves* move_list, int* move_scores, int left, int mid, int right);
void merge_sort(Moves* move_list, int* move_scores, int left, int right);
void sort_moves(Moves* move_list, Board* board, search_heuristics* search_data);
void print_move_scores(Moves* move_list, Board* board, search_heuristics* search_data);

#endif