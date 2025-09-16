#include "perft.h"

long nodes = 0;

void perft_driver(int depth, Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, zoobrist_hash_keys* hash_keys) {
    if(depth == 0) {
        nodes++;
        return;
    }

    Moves move_list;
    init_move_list(&move_list);
    generate_moves(board, leaper_masks, slider_masks, &move_list);

    for (int i = 0; i < move_list.count; i++) {
        copy_board(board);
        copy_board_hash_key(hash_keys);
        if(!make_move(board, move_list.moves[i], all_moves, leaper_masks, slider_masks, hash_keys)) {
            continue;
        }

        perft_driver(depth - 1, board, leaper_masks, slider_masks, hash_keys);

        take_back(board); 
        take_back_board_hash_key(hash_keys);

        // DEBUGGING HASH KEY
        // uint64_t current_hash_key = generate_board_hash_key(board, hash_keys);
        // if(hash_keys->board_hash_key != current_hash_key) {
        //     printf("Take back\n");
        //     print_board(board);
        //     printf("Board hash key: %" PRIu64 "\n", hash_keys->board_hash_key);
        //     printf("Current hash key: %" PRIu64 "\n", current_hash_key);
        //     getchar();
        // }
    }
}

void perft_test(int depth, Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, zoobrist_hash_keys* hash_keys) {
    printf("\nPerformance test\n\n");

    if(depth <= 0) {
        printf("\nDepth %d\n", 0);
        printf("Nodes %d", 1);
    }

    Moves move_list;
    init_move_list(&move_list);
    generate_moves(board, leaper_masks, slider_masks, &move_list);


    int start_time = get_time_ms();
    for (int i = 0; i < move_list.count; i++) {
        copy_board(board);
        copy_board_hash_key(hash_keys);
        if(!make_move(board, move_list.moves[i], all_moves, leaper_masks, slider_masks, hash_keys)) {
            continue;
        }
        long acummulative_nodes = nodes;
        perft_driver(depth-1, board, leaper_masks, slider_masks, hash_keys);

        long old_nodes = nodes - acummulative_nodes; // how many new nodes this move has created
        take_back(board); 
        take_back_board_hash_key(hash_keys);

        printf("  move: ");
        print_move(move_list.moves[i]);
        printf("  nodes: %ld\n", old_nodes);
        printf("-------------------------------------------------------------\n");
    }

    printf("\nDepth %d\n", depth);
    printf("Nodes %ld", nodes);
    printf("\nTime %d ms\n", get_time_ms() - start_time);
}