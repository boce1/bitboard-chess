#ifndef UCI_H
#define UCI_H

#include "board.h"
#include "bitboard.h"
#include "move_generator.h"

int parse_move(char* move_string, Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks);

#endif // UCI_H