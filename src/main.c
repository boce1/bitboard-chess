#include "bitboard.h"
#include <stdlib.h>

int main() {
    attack_masks* masks = create_attack_masks();
    init_attack_masks(masks);

    for(int i = 0; i < 64; i++) {
        print_bitboard(masks->bishop[i]);
    }

    free(masks);
    return 0;
}