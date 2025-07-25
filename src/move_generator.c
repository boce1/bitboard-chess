#include "move_generator.h"

void generate_pawn_moves(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, int piece) {
    int source_square, target_square;
    uint64_t bitboard, attacks;

    bitboard = board->pieces[piece];
    if(white == board->side_to_move) { // generate white pawn and white king castiling moves (they are not realing on precalculated attack tables)
        if(piece == P) {
            while(bitboard) {
                source_square = get_least_significant_bit_index(bitboard);
                target_square = source_square - 8; // move pawn one place forward
                if(!(target_square < a8) && !get_bit(board->occupancies[both], target_square) ) {
                    // pawn promotion
                    if(source_square >= a7 && source_square <= h7) {
                        // generate all promotion moves
                        printf("pawn promotion: %s%sQ\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                        printf("pawn promotion: %s%sR\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                        printf("pawn promotion: %s%sB\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                        printf("pawn promotion: %s%sN\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                    } else {
                        // one square forward
                        printf("pawn push: %s%s\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                        // two squares forward
                        if((source_square >= a2 && source_square <= h2) && !get_bit(board->occupancies[both], target_square - 8)) {
                            target_square -= 8; // move pawn two places forward
                            printf("double pawn push: %s%s\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);

                        }
                    }
                }
                attacks = get_pawn_attacks(leaper_masks, source_square, white) & board->occupancies[black];
                while(attacks) {
                    target_square = get_least_significant_bit_index(attacks);

                        // pawn promotion
                    if(source_square >= a7 && source_square <= h7) {
                        // generate all promotion moves
                        printf("pawn capture promotion: %s%sQ\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                        printf("pawn capture promotion: %s%sR\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                        printf("pawn capture promotion: %s%sB\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                        printf("pawn capture promotion: %s%sN\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                    } else {
                        printf("pawn capture: %s%s\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                    }

                    pop_bit(attacks, target_square);
                }

                // en passant
                if(board->en_passant_square != no_square) {
                    uint64_t enpassant_mask = get_pawn_attacks(leaper_masks, source_square, white) & (1ULL << board->en_passant_square);
                    if(enpassant_mask) {
                        int target_enpassant = get_least_significant_bit_index(enpassant_mask);
                        printf("en passant capture: %s%s\n", square_to_cordinates[source_square], square_to_cordinates[target_enpassant]);
                    }   
                }

                pop_bit(bitboard, source_square);
            }   
        }
    } else { // generate black pawn
        if(piece == p) {
            while(bitboard) {
                source_square = get_least_significant_bit_index(bitboard);
                target_square = source_square + 8; // move pawn one place down
                if(!(target_square > h1) && !get_bit(board->occupancies[both], target_square) ) {
                    // pawn promotion
                    if(source_square >= a2 && source_square <= h2) {
                        // generate all promotion moves
                        printf("pawn promotion: %s%sq\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                        printf("pawn promotion: %s%sr\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                        printf("pawn promotion: %s%sb\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                        printf("pawn promotion: %s%sn\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                    } else {
                        // one square forward
                        printf("pawn push: %s%s\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                        // two squares forward
                        if((source_square >= a7 && source_square <= h7) && !get_bit(board->occupancies[both], target_square + 8)) {
                            target_square += 8; // move pawn two places dows
                            printf("double pawn push: %s%s\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);

                        }
                    }
                }

                attacks = get_pawn_attacks(leaper_masks, source_square, black) & board->occupancies[white];
                while(attacks) {
                    target_square = get_least_significant_bit_index(attacks);

                    // pawn promotion
                    if(source_square >= a2 && source_square <= h2) {
                        // generate all promotion moves
                        printf("pawn capture promotion: %s%sq\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                        printf("pawn capture promotion: %s%se\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                        printf("pawn capture promotion: %s%sb\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                        printf("pawn capture promotion: %s%sn\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                    } else {
                        printf("pawn capture: %s%s\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                    }

                    pop_bit(attacks, target_square);
                }

                // en passant
                if(board->en_passant_square != no_square) {
                    uint64_t enpassant_mask = get_pawn_attacks(leaper_masks, source_square, black) & (1ULL << board->en_passant_square);
                    if(enpassant_mask) {
                        int target_enpassant = get_least_significant_bit_index(enpassant_mask);
                        printf("en passant capture: %s%s\n", square_to_cordinates[source_square], square_to_cordinates[target_enpassant]);
                    }   
                }

                pop_bit(bitboard, source_square);
            }   
        }
    }
}

void generate_king_castle(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, int piece) {
    int source_square, target_square;
    uint64_t bitboard, attacks;

    bitboard = board->pieces[piece];
    if(white == board->side_to_move) {
        if(piece == K) {
            if(board->castling_rights & wk) {
                if(!get_bit(board->occupancies[both], f1) && !get_bit(board->occupancies[both], g1)) { // check if f1 and g1 are empty
                    if(!is_square_attacked(e1, board, leaper_masks, slider_masks) && !is_square_attacked(f1, board, leaper_masks, slider_masks) && !is_square_attacked(g1, board, leaper_masks, slider_masks)) {
                        printf("white king castle: e1g1\n");
                    }
                }
            }

            if(board->castling_rights & wq) {   
                if(!get_bit(board->occupancies[both], d1) && !get_bit(board->occupancies[both], c1) && !get_bit(board->occupancies[both], b1)) { // check if d1, c1 and b1 are empty
                    if(!is_square_attacked(e1, board, leaper_masks, slider_masks) && !is_square_attacked(d1, board, leaper_masks, slider_masks) && !is_square_attacked(c1, board, leaper_masks, slider_masks)) {
                        printf("white king castle: e1c1\n");
                    }
                }
            }
        }
    } else {
        if(piece == k) {
            if(board->castling_rights & bk) {
                if(!get_bit(board->occupancies[both], f8) && !get_bit(board->occupancies[both], g8)) { // check if f8 and g8 are empty
                    if(!is_square_attacked(e8, board, leaper_masks, slider_masks) && !is_square_attacked(f8, board, leaper_masks, slider_masks) && !is_square_attacked(g8, board, leaper_masks, slider_masks)) {
                        printf("black king castle: e8g8\n");
                    }
                }
            } 

            if (board->castling_rights & bq) {   
                if(!get_bit(board->occupancies[both], d8) && !get_bit(board->occupancies[both], c8) && !get_bit(board->occupancies[both], b8)) { // check if d8, c8 and b8 are empty
                    if(!is_square_attacked(e8, board, leaper_masks, slider_masks) && !is_square_attacked(d8, board, leaper_masks, slider_masks) && !is_square_attacked(c8, board, leaper_masks, slider_masks)) {
                        printf("black king castle: e8c8\n");
                    }
                }
            }
        }
    }
}

void genenrate_knight_moves(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, int piece) {
    int source_square, target_square;
    uint64_t bitboard, attacks;

    int opp_side = (board->side_to_move == white) ? black : white;

    bitboard = board->pieces[piece];
    if((board->side_to_move == white && piece == N) || (board->side_to_move == black && piece == n)) {
        while(bitboard) {
            source_square = get_least_significant_bit_index(bitboard);
            attacks = get_knight_attacks(leaper_masks, source_square) & ~board->occupancies[board->side_to_move]; // get knight attacks by remove capturing own pieces

            while(attacks) {
                target_square = get_least_significant_bit_index(attacks);
                
                // quite moves
                if(!get_bit(board->occupancies[opp_side], target_square)) {
                    printf("knight move: %s%s\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                } else { // capture moves
                    printf("knight capture: %s%s\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);
                }
                
                pop_bit(attacks, target_square);
            }

            pop_bit(bitboard, source_square);
        }
    }
    
}

void generate_moves(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks) {
    for(int piece = P; piece <= k; piece++) {
        generate_pawn_moves(board, leaper_masks, slider_masks, piece); // generate only when pawn
        generate_king_castle(board, leaper_masks, slider_masks, piece); // generate only when king
        genenrate_knight_moves(board, leaper_masks, slider_masks, piece); // generate only when knight

        // generate moves for knignt, bishop, rook, queen and king

    }
}