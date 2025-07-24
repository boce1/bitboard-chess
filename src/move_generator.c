#include "move_generator.h"

void genenerate_moves(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks) {
    int source_square, target_square;
    uint64_t bitboard, attacks;

    for(int piece = P; piece <= k; piece++) {
        bitboard = board->pieces[piece];

        if(white == board->side_to_move) { // generate white pawn and white king castiling moves (they are not realing on precalculated attack tables)
            if(piece == P) {
                while(bitboard) {
                    source_square = get_least_significant_bit_index(bitboard);
                    target_square = source_square - 8; // move pawn one place forward

                    

                    pop_bit(bitboard, source_square);
                }   
            }
        } else { // generate black pawn and black king castiling moves

        }

        // generate moves for knignt, bishop, rook, queen and king

    }
}