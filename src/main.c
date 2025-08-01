#include "bitboard.h"
#include "magic_numbers.h"
#include "attack.h"
#include "board.h"
#include "move_generator.h"
#include "uci.h"
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

    // parse_position("position startpos moves e2e4 e7e5 g1f3 d7d6", board, leaper_masks, slider_masks);
    // print_board(board);
    // parse_go("go depth 5", board, leaper_masks, slider_masks);
    uci_loop(board, leaper_masks, slider_masks);
    
    //free(board); 
    if(leaper_masks != NULL) {
        free(leaper_masks);  
    }
    if(slider_masks != NULL) {
        free(slider_masks);
    }
    
    return 0;
}