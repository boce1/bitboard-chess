#include "bitboard.h"
#include "magic_numbers.h"
#include "attack.h"
#include "board.h"
#include "move_generator.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    leaper_moves_masks* leaper_masks = create_leaper_moves_masks(); // pawn, knight, king masks
    slider_moves_masks* slider_masks = create_slider_moves_masks(); // rook, bishop, queen masks
    init_leaper_moves_masks(leaper_masks);
    init_slider_moves_masks(slider_masks);

    //Board* board = create_board();
    Board board[1];
    init_board(board);
    parse_fen(tricky_position, board);
    parse_fen("r3k2r/pPppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/R3K2R b KQkq a3 0 1 ", board);
    //parse_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1 ", board);
    //parse_fen("3n1b2/4P1p1/8/2pP4/8/1P6/5PpP/5N2 w - e6 ", board);

    
    //print_move(move);
    Moves move_list;
    init_move_list(&move_list);
    generate_moves(board, leaper_masks, slider_masks, &move_list);
    //add_move(move_list, encode_move(e7, e8, B, B, not_capturing, double_push, enpassant, castiling));
    print_move_list(&move_list);
    print_board(board);

    //free(board); 
    free(leaper_masks);  
    free(slider_masks);
    return 0;
}