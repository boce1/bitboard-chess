#ifndef UCI_H
#define UCI_H

#include "board.h"
#include "bitboard.h"
#include "move_generator.h"
#include "negamax.h"
#include <string.h>
#include <stdio.h>

int parse_move(char* move_string, Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks);
void parse_position(char* command, Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks);
void parse_go(char* command, Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, search_heuristics* search_data); // called when GUI tells engine to calculate moves
void uci_loop(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, search_heuristics* search_data);
void search_position(int depth, Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks, search_heuristics* search_data);

#endif // UCI_H