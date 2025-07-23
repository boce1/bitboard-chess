#include "bitboard.h"
#include "magic_numbers.h"
#include "attack.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    leaper_attack_masks* leaper_masks = create_leaper_attack_masks();
    slider_attack_masks* slider_masks = create_slider_attack_masks();
    init_leaper_attack_masks(leaper_masks);
    init_slider_attack_masks(slider_masks);

    
    uint64_t bitboard = 0ULL;
    set_bit(bitboard, e4);
    set_bit(bitboard, a1); 
    set_bit(bitboard, g7); 
    set_bit(bitboard, c3); 
    set_bit(bitboard, d8); 


    for(int square = 0; square < 64; square++) {
        print_bitboard(get_queen_attacks(slider_masks, square, bitboard));
    }

    free(leaper_masks);
    free(slider_masks);
    return 0;
}