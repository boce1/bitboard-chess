#include "bitboard.h"
#include <inttypes.h>
#include <stdlib.h>

const char* square_to_cordinates[65] = {
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", 
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "No Square"
};

// relevant occupancy bit count for every square on board
const int bishop_relevant_bits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6, 
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6
};

const int rook_relevant_bits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12, 
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};

const uint64_t not_a_file = 18374403900871474942ULL; // bitboard where bits on 'a' file are 0
const uint64_t not_h_file = 9187201950435737471ULL; // bitboard where bits on 'h' file are 0
const uint64_t not_hg_file = 4557430888798830399ULL;
const uint64_t not_ab_file = 18229723555195321596ULL;


int count_bits(uint64_t bitboard) {
    int count = 0;
    while (bitboard) {
        count++;
        bitboard &= (bitboard - 1);
    }
    return count;
}

int get_least_significant_bit_index(uint64_t bitboard) { // get least significant 1st bit
    if(bitboard) {
        return count_bits((bitboard & -bitboard) - 1);
    } else {
        return -1;
    }
}

void print_bitboard(uint64_t bitboard) {
    printf("\n");
    for(int rank = 0; rank < 8; rank++) {
        for(int file = 0; file < 8; file++) {
            int square = rank * 8 + file;

            if(!file) {
                printf(" %d ", (8 - rank));
            }
            printf(" %d", get_bit(bitboard, square) ? 1 : 0);
        }
        printf("\n");
    }
    printf("\n    a b c d e f g h\n");
    printf("    Bitboard value: %" PRIu64, bitboard);
}

leaper_moves_masks* create_leaper_moves_masks() {
    leaper_moves_masks* masks = malloc(sizeof(leaper_moves_masks));
    if (!masks) {
        fprintf(stderr, "Memory allocation failed for leaper_moves_masks\n");
        exit(EXIT_FAILURE);
    }
    int i, j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 64; j++) {
            masks->pawn_attacks[i][j] = 0ULL;
        }
    }

    for (i = 0; i < 64; i++) {
        masks->king[i] = 0ULL;
        masks->knight[i] = 0ULL;
    }
    
    return masks;
}   

void init_pawn_leaper_moves_masks(leaper_moves_masks* masks) {
    uint64_t left_attack, right_attack;
    int square;
    for(int rank = 0; rank < 8; rank++) {
        for(int file = 0; file < 8; file++) {
            square = rank * 8 + file;

            left_attack = 0ULL;
            right_attack = 0ULL;
            set_bit(left_attack, square);
            set_bit(right_attack, square);
            left_attack >>= 9;
            right_attack >>= 7;
            masks->pawn_attacks[white][square] |= left_attack & not_h_file;
            masks->pawn_attacks[white][square] |= right_attack & not_a_file;

            left_attack = 0ULL;
            right_attack = 0ULL;
            set_bit(left_attack, square);
            set_bit(right_attack, square);
            right_attack <<= 9;
            left_attack <<= 7;
            masks->pawn_attacks[black][square] |= right_attack & not_a_file;
            masks->pawn_attacks[black][square] |= left_attack & not_h_file;
        }
    }
}

void init_king_leaper_moves_masks(leaper_moves_masks* masks) {
    int square;
    uint64_t king_pos = 0ULL;
    for(int rank = 0; rank < 8; rank++) {
        for(int file = 0; file < 8; file++) {
            square = rank * 8 + file;
            king_pos = 0ULL;
            set_bit(king_pos, square); 
            
            masks->king[square] |= (king_pos >> 8); // up
            masks->king[square] |= (king_pos << 8); // down
            masks->king[square] |= (king_pos >> 1) & not_h_file; // left
            masks->king[square] |= (king_pos << 1) & not_a_file; // right
            masks->king[square] |= (king_pos >> 9) & not_h_file; // up-left
            masks->king[square] |= (king_pos << 9) & not_a_file; // down-right
            masks->king[square] |= (king_pos >> 7) & not_a_file; // up-right
            masks->king[square] |= (king_pos << 7) & not_h_file; // down-left
        }           
    }
}

void init_knight_leaper_moves_masks(leaper_moves_masks* masks) {
    int square;
    uint64_t knight_pos = 0ULL;
    for(int rank = 0; rank < 8; rank++) {
        for(int file = 0; file < 8; file++) {
            square = rank * 8 + file;
            knight_pos = 0ULL;
            set_bit(knight_pos, square);

            masks->knight[square] |= ((knight_pos >> 10) & not_hg_file); 
            masks->knight[square] |= ((knight_pos << 10) & not_ab_file);
            masks->knight[square] |= ((knight_pos >> 6) & not_ab_file);
            masks->knight[square] |= ((knight_pos << 6) & not_hg_file);
            masks->knight[square] |= ((knight_pos >> 17) & not_h_file);
            masks->knight[square] |= ((knight_pos << 17) & not_a_file);
            masks->knight[square] |= ((knight_pos >> 15) & not_a_file);
            masks->knight[square] |= ((knight_pos << 15) & not_h_file);
        }
    }
}

void init_bishop_occupancy_rays_masks(slider_moves_masks* masks) {
    for(int square = 0; square < 64; square++) {
        uint64_t mask = 0ULL;
        int rank = square / 8;
        int file = square % 8;

        // Up-Right
        for(int r = rank + 1, f = file + 1; r <= 6 && f <= 6; r++, f++)
            mask |= (1ULL << (r * 8 + f));
        // Up-Left
        for(int r = rank + 1, f = file - 1; r <= 6 && f >= 1; r++, f--)
            mask |= (1ULL << (r * 8 + f));
        // Down-Right
        for(int r = rank - 1, f = file + 1; r >= 1 && f <= 6; r--, f++)
            mask |= (1ULL << (r * 8 + f));
        // Down-Left
        for(int r = rank - 1, f = file - 1; r >= 1 && f >= 1; r--, f--)
            mask |= (1ULL << (r * 8 + f));

        masks->bishop_occupancy_rays[square] = mask;
    }
}

void init_leaper_moves_masks(leaper_moves_masks* masks) {
    init_pawn_leaper_moves_masks(masks);
    init_king_leaper_moves_masks(masks);
    init_knight_leaper_moves_masks(masks);
}

void init_rook_occupancy_rays_masks(slider_moves_masks* masks){
    // Initialize all masks that can represent possitions for blocker pieces
    for (int square = 0; square < 64; square++) {
        uint64_t mask = 0ULL;
        int rank = square / 8;
        int file = square % 8;

        // Up
        for (int r = rank + 1; r <= 6; r++)
            mask |= (1ULL << (r * 8 + file));
        // Down
        for (int r = rank - 1; r >= 1; r--)
            mask |= (1ULL << (r * 8 + file));
        // Right
        for (int f = file + 1; f <= 6; f++)
            mask |= (1ULL << (rank * 8 + f));
        // Left
        for (int f = file - 1; f >= 1; f--)
            mask |= (1ULL << (rank * 8 + f));

        masks->rook_occupancy_rays[square] = mask;
    }
}

uint64_t get_occupancy_permutation(int index, int bits, uint64_t mask) { // for rook and bishop
    uint64_t occupancy = 0ULL;
    int square;

    for(int count = 0; count < bits; count++) {
        square = get_least_significant_bit_index(mask);
        pop_bit(mask, square);
        if (index & (1 << count)) {
            set_bit(occupancy, square);
        }  
    }

    return occupancy;
}

slider_moves_masks* create_slider_moves_masks() {
    slider_moves_masks* masks = malloc(sizeof(slider_moves_masks));
    if (!masks) {
        fprintf(stderr, "Memory allocation failed for slider_moves_masks\n");
        exit(EXIT_FAILURE);
    }
    int square, permutation;
    for (square = 0; square < 64; square++) {
        for (permutation = 0; permutation < 4096; permutation++) {
            masks->rook[square][permutation] = 0ULL;
        }

        for (permutation = 0; permutation < 512; permutation++) {
            masks->bishop[square][permutation] = 0ULL;
        }
        masks->bishop_occupancy_rays[square] = 0ULL;
        masks->rook_occupancy_rays[square] = 0ULL; 
    }
    
    return masks;
}

uint64_t bishop_attacks_on_the_fly(int square, uint64_t block) {
    uint64_t attacks = 0ULL;
    int r, f;
    int tr = square / 8;
    int tf = square % 8; 
    uint64_t attack;

    for(r = tr+1, f=tf+1; r<=7 && f<=7; r++, f++) {
        attack = (1ULL << (r*8 + f));
        attacks |= attack;
        if(attack & block) break;
    }

    for(r = tr-1, f=tf+1; r>=0 && f<=7; r--, f++) {
        attack = (1ULL << (r*8 + f));
        attacks |= attack;
        if(attack & block) break;
    }

    for(r = tr+1, f=tf-1; r<=7 && f>=0; r++, f--) {
        attack = (1ULL << (r*8 + f));
        attacks |= attack;
        if(attack & block) break;
    }

    for(r = tr-1, f=tf-1; r>=0 && f>=0; r--, f--) {
        attack = (1ULL << (r*8 + f));
        attacks |= attack;
        if(attack & block) break;
    }

    return attacks;
}

uint64_t rook_attacks_on_the_fly(int square, uint64_t block) {
    uint64_t attacks = 0ULL;
    int r, f;
    int tr = square / 8;
    int tf = square % 8; 
    uint64_t attack;

    for(r = tr+1; r<=7; r++) {
        attack = (1ULL << (r*8 + tf));
        attacks |= attack;
        if(attack & block) break;
    }

    for(r = tr-1; r>=0; r--) {
        attack = (1ULL << (r*8 + tf));
        attacks |= attack;
        if(attack & block) break;
    }

    for(f=tf-1; f>=0; f--) {
        attack = (1ULL << (tr*8 + f));
        attacks |= attack;
        if(attack & block) break;
    }

    for(f=tf+1; f<=7; f++) {
        attack = (1ULL << (tr* 8 + f));
        attacks |= attack;
        if(attack & block) break;
    }

    return attacks;
}

void init_rook_slider_moves_masks(slider_moves_masks* slider_mask) {
    uint64_t occupancy, magic_number;
    int square, bits, magic_index;

    for (square = 0; square < 64; square++) {
        bits = rook_relevant_bits[square];
        for (int index_rook = 0; index_rook < (1 << bits); index_rook++) {
            occupancy = get_occupancy_permutation(index_rook, bits, slider_mask->rook_occupancy_rays[square]);
            magic_number = rook_magic_numbers[square];
            magic_index = (int)((occupancy * magic_number) >> (64 - bits));
            slider_mask->rook[square][magic_index] = rook_attacks_on_the_fly(square, occupancy); 
        }
    }
}

void init_bishop_slider_moves_masks(slider_moves_masks* slider_mask) {
    uint64_t occupancy, magic_number;
    int square, bits, magic_index;

    for (square = 0; square < 64; square++) {
        bits = bishop_relevant_bits[square];
        for (int index_bishop = 0; index_bishop < (1 << bits); index_bishop++) {
            occupancy = get_occupancy_permutation(index_bishop, bits, slider_mask->bishop_occupancy_rays[square]);
            magic_number = bishop_magic_numbers[square];
            magic_index = (int)((occupancy * magic_number) >> (64 - bits));
            slider_mask->bishop[square][magic_index] = bishop_attacks_on_the_fly(square, occupancy); 
        }
    }
}

void init_slider_moves_masks(slider_moves_masks* slider_mask) {
    init_rook_occupancy_rays_masks(slider_mask);
    init_bishop_occupancy_rays_masks(slider_mask);
    init_rook_slider_moves_masks(slider_mask);
    init_bishop_slider_moves_masks(slider_mask);
}
