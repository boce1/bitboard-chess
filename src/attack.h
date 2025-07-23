#ifndef ATTACK_H
#define ATTACK_H

#include <stdint.h>
#include "bitboard.h"
#include "magic_numbers.h"

uint64_t get_pawn_attacks(leaper_attack_masks* masks, int square, side side);
uint64_t get_knight_attacks(leaper_attack_masks* masks, int square);
uint64_t get_king_attacks(leaper_attack_masks* masks, int square);
uint64_t get_rook_attacks(slider_attack_masks* masks, int square, uint64_t occupancy);
uint64_t get_bishop_attacks(slider_attack_masks* slider_masks, int square, uint64_t occupancy);
uint64_t get_queen_attacks(slider_attack_masks* slider_masks, int square, uint64_t occupancy);

#endif // ATTACK_H