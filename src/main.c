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

    Board* board = create_board();
    parse_fen(start_position, board);
    //parse_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1 ", board);

    // print_bitboard(get_queen_attacks(slider_masks, d1, board->occupancies[both]));
    // print_attacked_squares(board, leaper_masks, slider_masks);

    for(int i = 0; i < 64; i++) {
        print_bitboard(leaper_masks->pawn_one_step[white][i]);
    }

    free(leaper_masks);
    free(slider_masks);
    return 0;
}