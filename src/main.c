#include "bitboard.h"
#include "magic_numbers.h"
#include "attack.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    leaper_attack_masks* leaper_masks = create_leaper_attack_masks(); // pawn, knight, king masks
    slider_attack_masks* slider_masks = create_slider_attack_masks(); // rook, bishop, queen masks
    init_leaper_attack_masks(leaper_masks);
    init_slider_attack_masks(slider_masks);

    Board* board = create_board();
    parse_fen(start_position, board);
    //parse_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1 ", board);

    print_board(board);
    print_attacked_squares(board, leaper_masks, slider_masks);

    free(leaper_masks);
    free(slider_masks);
    return 0;
}