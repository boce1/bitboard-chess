#include "bitboard.h"
#include "magic_numbers.h"
#include "attack.h"
#include "board.h"
#include "move_generator.h"
#include "uci.h"
#include "negamax.h"
//#include "perft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    leaper_moves_masks* leaper_masks = create_leaper_moves_masks(); // pawn, knight, king masks
    slider_moves_masks* slider_masks = create_slider_moves_masks(); // rook, bishop, queen masks
    init_leaper_moves_masks(leaper_masks);
    init_slider_moves_masks(slider_masks);
    //Board* board = create_board();
    Board board[1];
    init_board(board);

    int debug = 0;
    if(debug) {
        // debug code
        parse_fen("rnbqkbnr/ppppppp1/8/7p/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 1", board);
        print_board(board);
        search_position(6, board, leaper_masks, slider_masks);
        //Moves mv[1];
        //init_move_list(mv);
        //generate_moves(board, leaper_masks, slider_masks, mv);
//
        //for(int i = 0; i < mv->count; i++) {
        //    copy_board(board);
        //    if(make_move(board, mv->moves[i], all_moves, leaper_masks, slider_masks) != 0) {
        //        print_board(board);
        //        take_back(board);
        //        print_move(mv->moves[i]);
        //    }
        //}
        //printf("score %d\n", evaluate(board));
    } else {
        uci_loop(board, leaper_masks, slider_masks);
    }
    
    //free(board); 
    if(leaper_masks != NULL) {
        free(leaper_masks);  
    }
    if(slider_masks != NULL) {
        free(slider_masks);
    }
    
    return 0;
}