#include "bitboard.h"
#include "magic_numbers.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    leaper_attack_masks* leaper_masks = create_leaper_attack_masks();
    slider_attack_masks* slider_masks = create_rook_bishop_occupancy_masks();
    init_leaper_attack_masks(leaper_masks);
    init_slider_attack_masks(slider_masks, leaper_masks);

    for(int i = 0; i < 4096; i++) {
        print_bitboard(slider_masks->rook[e4][i]);
    }

    //print_magic_numbers(bishop, masks);

    free(leaper_masks);
    free(slider_masks);
    return 0;
}