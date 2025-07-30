#include "bitboard.h"
#include "magic_numbers.h"
#include "attack.h"
#include "board.h"
#include "move_generator.h"
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
    parse_fen(start_position, board);
    
    
    //free(board); 
    free(leaper_masks);  
    free(slider_masks);

    
    return 0;
}