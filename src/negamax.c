#include "negamax.h"

int ply = 0; // half move counter
int best_move = 0;

const int material_score[12] = {
    100, // white pawn score
    300, // white knight score
    350, // white bishop
    500, // white rook
    1000, // white queen
    10000, // white king
    -100, // black pawn score
    -300, // black knight score
    -350, // black bishop
    -500, // black rook
    -1000, // black queen
    -10000 // black king
};

const int pawn_score[64] = {
    90,  90,  90,  90,  90,  90,  90,  90,
    30,  30,  30,  40,  40,  30,  30,  30,
    20,  20,  20,  30,  30,  30,  20,  20,
    10,  10,  10,  20,  20,  10,  10,  10,
     5,   5,  10,  20,  20,   5,   5,   5,
     0,   0,   0,   5,   5,   0,   0,   0,
     0,   0,   0, -10, -10,   0,   0,   0,
     0,   0,   0,   0,   0,   0,   0,   0
};

// knight positional score
const int knight_score[64] = {
    -5,   0,   0,   0,   0,   0,   0,  -5,
    -5,   0,   0,  10,  10,   0,   0,  -5,
    -5,   5,  20,  20,  20,  20,   5,  -5,
    -5,  10,  20,  30,  30,  20,  10,  -5,
    -5,  10,  20,  30,  30,  20,  10,  -5,
    -5,   5,  20,  10,  10,  20,   5,  -5,
    -5,   0,   0,   0,   0,   0,   0,  -5,
    -5, -10,   0,   0,   0,   0, -10,  -5
};

// bishop positional score
const int bishop_score[64] = {
     0,   0,   0,   0,   0,   0,   0,   0,
     0,   0,   0,   0,   0,   0,   0,   0,
     0,  20,   0,  10,  10,   0,  20,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,  10,   0,   0,   0,   0,  10,   0,
     0,  30,   0,   0,   0,   0,  30,   0,
     0,   0, -10,   0,   0, -10,   0,   0
};

const int rook_score[64] = {
    50,  50,  50,  50,  50,  50,  50,  50,
    50,  50,  50,  50,  50,  50,  50,  50,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,   0,  20,  20,   0,   0,   0

};

const int king_score[64] = {
     0,   0,   0,   0,   0,   0,   0,   0,
     0,   0,   5,   5,   5,   5,   0,   0,
     0,   5,   5,  10,  10,   5,   5,   0,
     0,   5,  10,  20,  20,  10,   5,   0,
     0,   5,  10,  20,  20,  10,   5,   0,
     0,   0,   5,  10,  10,   5,   0,   0,
     0,   5,   5,  -5,  -5,   0,   5,   0,
     0,   0,  10,   0, -15,   0,  15,   0
};

const int mirror_score[128] = {
	a1, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8
};

int evaluate(Board* board) {
    int score = 0;
    uint64_t bitboard;
    int square;

    for(int bb_piece = P; bb_piece <= k; bb_piece++) {
        bitboard = board->pieces[bb_piece];
        while(bitboard) {
            square = get_least_significant_bit_index(bitboard);
            score += material_score[bb_piece];

            // evaluate with positional score tables
            // early queen movement leads to loss
            switch(bb_piece) {
                // white
                case P:
                    score += pawn_score[square];
                    break;
                case N:
                    score += knight_score[square];
                    break;
                case B:
                    score += bishop_score[square];
                    break;
                case R:
                    score += rook_score[square];
                    break;
                case K:
                    score += king_score[square];
                    break;
                // black
                case p:
                    score -= pawn_score[mirror_score[square]];
                    break;
                case n:
                    score -= knight_score[mirror_score[square]];
                    break;
                case b:
                    score -= bishop_score[mirror_score[square]];
                    break;
                case r:
                    score -= rook_score[mirror_score[square]];
                    break;
                case k:
                    score -= king_score[mirror_score[square]];
                    break;
            }

            pop_bit(bitboard, square);
        }
    }

    if(board->side_to_move == white) {
        return score;
    } else if (board->side_to_move == black) {
        return -score;
    }
    return 0;
}

int quiescence(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, int alpha, int beta) {
    int eval = evaluate(board);
    if(eval >= beta) {
        return beta;
    }
    if(eval > alpha) {
        alpha = eval;
    }
    
    Moves move_list[1];
    init_move_list(move_list);
    generate_moves(board, leaper_masks, slider_masks, move_list);

    for(int count = 0; count < move_list->count; count++) {
        copy_board(board);
        ply++;
        if(make_move(board, move_list->moves[count], only_captures, leaper_masks, slider_masks) == 0) {
            ply--;
            continue;
        }

        int score = -quiescence(board, leaper_masks, slider_masks, -beta, -alpha);
        take_back(board);
        ply--;

        if(score >= beta){
            return beta;
        }

        if(score > alpha) {
            alpha = score;

        }
    }

    return alpha;
}

int negamax(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, int alpha, int beta, int depth) {
    if(depth == 0) {
        return quiescence(board, leaper_masks, slider_masks, alpha, beta);
        //return evaluate(board);
    }
    nodes++; // will be used later to reduced search space
    int legal_moves = 0;

    int in_check = 0;
    int king_pos;
    if(board->side_to_move == white) {
        king_pos = get_least_significant_bit_index(board->pieces[K]);
        if(is_square_attacked(king_pos, board, leaper_masks, slider_masks)) {
            in_check = 1;
        }
    } else if(board->side_to_move == black) {
        king_pos = get_least_significant_bit_index(board->pieces[k]);
        if(is_square_attacked(king_pos, board, leaper_masks, slider_masks)) {
            in_check = 1;
        }
    }


    Moves move_list[1];
    init_move_list(move_list);
    generate_moves(board, leaper_masks, slider_masks, move_list);

    int best_move_sofar = 0;
    int old_alpha = alpha;

    for(int count = 0; count < move_list->count; count++) {
        copy_board(board);
        ply++;
        if(make_move(board, move_list->moves[count], all_moves, leaper_masks, slider_masks) == 0) {
            ply--;
            continue;
        }

        legal_moves++;

        int score = -negamax(board, leaper_masks, slider_masks, -beta, -alpha, depth-1);
        take_back(board);
        ply--;

        if(score >= beta) {
            return beta;
        }

        if(score > alpha) {
            alpha = score;

            if(ply == 0) {
                best_move_sofar = move_list->moves[count];
            }
        }
    }

    if(legal_moves == 0) {
        if(in_check) { // mating score assuming closest distance to mating position
            return ALPHA + 1 + ply;
        } else {
            // stalemate
            return 0;
        }
    }

    if(old_alpha != alpha) {
        best_move = best_move_sofar;
    }

    return alpha;
}
