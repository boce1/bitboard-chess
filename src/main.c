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
    // parse_fen(tricky_position, board);
    parse_fen("rnbqkbnr/ppp1pppp/8/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 1", board);
    print_board(board);
    
    int move = parse_move("e5d6", board, leaper_masks, slider_masks);
    if(move) {
        make_move(board, move, all_moves, leaper_masks, slider_masks);
        print_board(board);
    } else {
        printf("illegal move!\n");
    }

    
    //free(board); 
    free(leaper_masks);  
    free(slider_masks);

    
    return 0;
}