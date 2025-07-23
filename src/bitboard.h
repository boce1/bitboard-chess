#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdio.h>

#define uint_64 unsigned long long

#define get_bit(bitboard, square) ((bitboard) & (1ULL << (square)))
#define set_bit(bitboard, square) ((bitboard) |= (1ULL << (square)))
#define pop_bit(bitboard, square) ((bitboard) &= ~(1ULL << (square)))

int count_bits(uint_64 bitboard);
int get_least_significant_bit(uint_64 bitboard);

void print_bitboard(uint_64 bitboard);

typedef enum {
    a8, b8, c8, d8, e8, f8, g8, h8, 
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1, no_square
} square;

typedef enum {
    white, black, both
} side;

typedef enum {
    rook, bishop
} rook_bishop;

extern const char* square_to_cordinates[64];

const uint_64 not_a_file; // bitboard where bits on 'a' file are 0
const uint_64 not_h_file; // bitboard where bits on 'h' file are 0
const uint_64 not_hg_file;
const uint_64 not_ab_file;

/*
    rook and bishop attack masks are the mask for blocker bitboards. they produce occupancy board that produce magic number
    queen is the combined rook and bishop

    for lepaer pieces (pawn, king, knight) the attack masks are the actual attack masks
    for slider pieces (rook, bishop, queen) the attack masks are made with
                the help of magic numbers and blocker bitboards
    magic number + blocker bitboards = attack masks
*/
typedef struct {
    uint_64 pawn[2][64]; // 
    uint_64 knight[64];
    uint_64 bishop[64];
    uint_64 rook[64];
    uint_64 king[64];
} attack_masks;

typedef struct {
    uint_64 rook[64][4096]; // 4096 is the maximum number of rook moves from a square
    uint_64 bishop[64][512]; // 512 is the maximum number of bishop moves from a square
} rook_bishop_occupancies;

attack_masks* create_attack_masks();

void init_pawn_attack_masks(attack_masks* masks);
void init_king_attack_masks(attack_masks* masks);
void init_knight_attack_masks(attack_masks* masks);

void init_rook_occupancy_rays_masks(attack_masks* masks);
void init_bishop_occupancy_rays_masks(attack_masks* masks);

void init_attack_masks(attack_masks* masks);

#endif // BITBOARD_H