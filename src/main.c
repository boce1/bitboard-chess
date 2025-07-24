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
    set_bit(board->pieces[P], a2);
    set_bit(board->pieces[N], b2);
    set_bit(board->pieces[K], a6);
    set_bit(board->pieces[Q], g5);
    set_bit(board->pieces[n], b8);
    set_bit(board->pieces[k], a4);
    set_bit(board->pieces[q], c3);
    board->en_passant_square = b3;
    board->side_to_move = black;
    print_board(board);
    print_bitboard(board->pieces[n]);

    free(leaper_masks);
    free(slider_masks);
    return 0;
}