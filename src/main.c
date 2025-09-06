#include "bitboard.h"
#include "magic_numbers.h"
#include "attack.h"
#include "board.h"
#include "move_generator.h"
#include "uci.h"
#include "negamax.h"
#include "time_control.h"
// #include "perft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    leaper_moves_masks* leaper_masks = create_leaper_moves_masks(); // pawn, knight, king masks
    slider_moves_masks* slider_masks = create_slider_moves_masks(); // rook, bishop, queen masks
    init_leaper_moves_masks(leaper_masks);
    init_slider_moves_masks(slider_masks);
    Board board[1];
    init_board(board);

    search_heuristics search_data[1];
    init_search_heuristics(search_data);

    time_controls time_info[1];
    init_time_controls(time_info); 

    int debug = 0; // set to 0 to run UCI loop
    if(debug) {

        parse_fen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ", board);
        print_board(board);
        
        //perft_test(2, board, leaper_masks, slider_masks);
        search_position(6, board, leaper_masks, slider_masks, search_data, time_info);
        //Moves mv[1];
        //init_move_list(mv);
        //generate_moves(board, leaper_masks, slider_masks, mv);
//
        //sort_moves(mv, board, search_data);
        //print_move_scores(mv, board, search_data);        
        //printf("score %d\n", evaluate(board));
    } else {
        uci_loop(board, leaper_masks, slider_masks, search_data, time_info);
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