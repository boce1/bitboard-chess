#include "perft.h"

long nodes = 0;

void perft_driver(int depth, Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks) {
    if(depth == 0) {
        nodes++;
        return;
    }

    Moves move_list;
    init_move_list(&move_list);
    generate_moves(board, leaper_masks, slider_masks, &move_list);

    for (int i = 0; i < move_list.count; i++) {
        copy_board(board);
        if(!make_move(board, move_list.moves[i], all_moves, leaper_masks, slider_masks)) {
            continue;
        }

        perft_driver(depth - 1, board, leaper_masks, slider_masks);

        take_back(board); 
    }
}

void perft_test(int depth, Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks) {
    printf("\nPerformance test\n\n");

    Moves move_list;
    init_move_list(&move_list);
    generate_moves(board, leaper_masks, slider_masks, &move_list);


    int start_time = get_time_ms();
    for (int i = 0; i < move_list.count; i++) {
        copy_board(board);
        if(!make_move(board, move_list.moves[i], all_moves, leaper_masks, slider_masks)) {
            continue;
        }
        long acummulative_nodes = nodes;
        perft_driver(depth, board, leaper_masks, slider_masks);

        long old_nodes = nodes - acummulative_nodes; // how many new nodes this move has created
        take_back(board); 

        // printf("  move: ");
        // print_move(move_list.moves[i]);
        // printf("  nodes: %ld\n", old_nodes);
        // printf("-------------------------------------------------------------\n");
    }

    printf("\nDepth %d\n", depth);
    printf("Nodes %ld", nodes);
    printf("\nTime %d ms\n", get_time_ms() - start_time);
}