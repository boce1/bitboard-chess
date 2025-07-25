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
    //parse_fen(tricky_position, board);
    parse_fen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1P2P3/2N2Q1P/PPPBPPPP/R3K2R b KQkq e3 0 1 ", board);
    //parse_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1 ", board);
    //parse_fen("3n1b2/4P1p1/8/2pP4/8/1P6/5PpP/5N2 w - e6 ", board);

    //print_board(board);
    //generate_moves(board, leaper_masks, slider_masks);

    int move = encode_move(e7, e8, P, Q, capturing, double_push, not_enpassant, castiling);
    int source = get_move_source(move);
    int target = get_move_target(move);
    int piece = get_move_piece(move);
    int promoted = get_move_promoted(move);

    printf("source square: %s\n", square_to_cordinates[source]);
    printf("target square: %s\n", square_to_cordinates[target]);
    printf("piece: %c\n", ascii_pieces[piece]);
    printf("promoted piece: %c\n", ascii_pieces[promoted]);
    printf("capture: %d\n", get_move_capture(move));
    printf("double push: %d\n", get_move_double_push(move));
    printf("en passant: %d\n", get_move_enpassant(move));
    printf("castiling: %d\n", get_move_castiling(move));

    free(board); 
    free(leaper_masks);  
    free(slider_masks);
    return 0;
}