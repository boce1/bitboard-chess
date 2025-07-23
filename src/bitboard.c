#include "bitboard.h"
#include <inttypes.h>
#include <stdlib.h>

const char* square_to_cordinates[64] = {
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", 
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
};

const uint_64 not_a_file = 18374403900871474942ULL; // bitboard where bits on 'a' file are 0
const uint_64 not_h_file = 9187201950435737471ULL; // bitboard where bits on 'h' file are 0
const uint_64 not_hg_file = 4557430888798830399ULL;
const uint_64 not_ab_file = 18229723555195321596ULL;


int count_bits(uint_64 bitboard) {
    int count = 0;
    while (bitboard) {
        count++;
        bitboard &= (bitboard - 1);
    }
    return count;
}

int get_least_significant_bit(uint_64 bitboard) { // get least significant 1st bit
    if(bitboard) {
        return count_bits((bitboard & -bitboard) - 1);

    } else {
        return -1;
    }
}

void print_bitboard(uint_64 bitboard) {
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

attack_masks* create_attack_masks() {
    attack_masks* masks = malloc(sizeof(attack_masks));
    if (!masks) {
        fprintf(stderr, "Memory allocation failed for attack_masks\n");
        exit(EXIT_FAILURE);
    }
    int i, j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 64; j++) {
            masks->pawn[i][j] = 0ULL;
        }
    }

    for (i = 0; i < 64; i++) {
        masks->king[i] = 0ULL;
        masks->knight[i] = 0ULL;
        masks->bishop[i] = 0ULL;
        masks->rook[i] = 0ULL; 
    }
    
    return masks;
}   

void init_pawn_attack_masks(attack_masks* masks) {
    uint_64 left_attack, right_attack;
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
            masks->pawn[white][square] |= left_attack & not_h_file;
            masks->pawn[white][square] |= right_attack & not_a_file;

            left_attack = 0ULL;
            right_attack = 0ULL;
            set_bit(left_attack, square);
            set_bit(right_attack, square);
            right_attack <<= 9;
            left_attack <<= 7;
            masks->pawn[black][square] |= right_attack & not_a_file;
            masks->pawn[black][square] |= left_attack & not_h_file;
        }
    }
}

void init_king_attack_masks(attack_masks* masks) {
    int square;
    uint_64 king_pos = 0ULL;
    for(int rank = 0; rank < 8; rank++) {
        for(int file = 0; file < 8; file++) {
            square = rank * 8 + file;
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

void init_knight_attack_masks(attack_masks* masks) {
    int square;
    uint_64 knight_pos = 0ULL;
    for(int rank = 0; rank < 8; rank++) {
        for(int file = 0; file < 8; file++) {
            square = rank * 8 + file;
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

void init_rook_occupancy_rays_masks(attack_masks* masks){
    // Initialize all masks that can represent possitions for blocker pieces
    for (int square = 0; square < 64; square++) {
        uint_64 mask = 0ULL;
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

        masks->rook[square] = mask;
    }
}

void init_bishop_occupancy_rays_masks(attack_masks* masks) {
    for(int square = 0; square < 64; square++) {
        uint_64 mask = 0ULL;
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

        masks->bishop[square] = mask;
    }
}

void init_attack_masks(attack_masks* masks) {
    init_pawn_attack_masks(masks);
    init_king_attack_masks(masks);
    init_knight_attack_masks(masks);
    init_rook_occupancy_rays_masks(masks);
    init_bishop_occupancy_rays_masks(masks);
}
