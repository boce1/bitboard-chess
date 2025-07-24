#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include "board.h"
#include "attack.h"
#include "bitboard.h"
#include <stdint.h>

// TODO: later add move list
// first implement logic
void genenerate_moves(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks);

#endif // MOVE_GENERATOR_H