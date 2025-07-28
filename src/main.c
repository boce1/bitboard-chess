#include "bitboard.h"
#include "magic_numbers.h"
#include "attack.h"
#include "board.h"
#include "move_generator.h"
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
    //parse_fen(tricky_position, board);
    parse_fen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R b KQkq - 0 1 ", board);
    
    Moves move_list;
    init_move_list(&move_list);
    generate_moves(board, leaper_masks, slider_masks, &move_list);
    
    print_board(board);
    for (int i = 0; i < move_list.count; i++) {
        int move = move_list.moves[i];

        copy_board(board);
        make_move(board, move, all_moves);
        //print_board(board);
        print_bitboard(board->occupancies[both]);
        take_back(board);
        // print_board(board);
        
        // getchar();
    }

    //free(board); 
    free(leaper_masks);  
    free(slider_masks);
    return 0;
}