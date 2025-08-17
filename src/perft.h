// PERFT PASSED

#ifndef PERFT_H
#define PERFT_H

#ifdef WIN64
    #include <windows.h>
#else
    #include <sys/time.h>
#endif
#include "board.h"
#include "bitboard.h"
#include "move_generator.h"
#include "attack.h"
#include <stdio.h>

int get_time_ms();
void perft_driver(int depth, Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks);
void perft_test(int depth, Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks);

//left nodes (number of possitions reached during the test of the move generator at the given depth)
extern long nodes; // IT WAS FOR TESTING PURPOSES
// THE REAL NODES COUNT EXIST IN search_heuristics structure

#endif // PERFT_H