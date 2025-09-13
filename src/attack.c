#include "attack.h"

uint64_t get_pawn_attacks(leaper_moves_masks* masks, int square, side side) {
    uint64_t attacks = 0ULL;
    if (side == white) {
        attacks |= masks->pawn_attacks[white][square];
    } else {
        attacks |= masks->pawn_attacks[black][square];
    }
    return attacks;
}

uint64_t get_knight_attacks(leaper_moves_masks* masks, int square) {
    return masks->knight[square];
}

uint64_t get_king_attacks(leaper_moves_masks* masks, int square) {
    return masks->king[square];
}

uint64_t get_rook_attacks(slider_moves_masks* masks, int square, uint64_t occupancy) {
    occupancy &= masks->rook_occupancy_rays[square];
    occupancy *= rook_magic_numbers[square];
    occupancy >>= (64 - rook_relevant_bits[square]);
    return masks->rook[square][occupancy];
}

uint64_t get_bishop_attacks(slider_moves_masks* masks, int square, uint64_t occupancy) {
    occupancy &= masks->bishop_occupancy_rays[square];
    occupancy *= bishop_magic_numbers[square];
    occupancy >>= (64 - bishop_relevant_bits[square]);
    return masks->bishop[square][occupancy];
}

uint64_t get_queen_attacks(slider_moves_masks* slider_masks, int square, uint64_t occupancy) {
    return get_rook_attacks(slider_masks, square, occupancy) | 
           get_bishop_attacks(slider_masks, square, occupancy);
}