#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdio.h>
#include <stdint.h>
#include "magic_numbers.h"

// #define uint_64 unsigned long long

#define get_bit(bitboard, square) ((bitboard) & (1ULL << (square)))
#define set_bit(bitboard, square) ((bitboard) |= (1ULL << (square)))
#define pop_bit(bitboard, square) ((bitboard) &= ~(1ULL << (square)))

int count_bits(uint64_t bitboard);
int get_least_significant_bit_index(uint64_t bitboard);

void print_bitboard(uint64_t bitboard);

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

extern const char* square_to_cordinates[65];
extern const int bishop_relevant_bits[64];
extern const int rook_relevant_bits[64];

extern const uint64_t not_a_file; // bitboard where bits on 'a' file are 0
extern const uint64_t not_h_file; // bitboard where bits on 'h' file are 0
extern const uint64_t not_hg_file;
extern const uint64_t not_ab_file;

/*
    rook and bishop attack masks are the mask for blocker bitboards. they produce occupancy board that produce magic number
    queen is the combined rook and bishop

    for lepaer pieces (pawn, king, knight) the attack masks are the actual attack masks
    for slider pieces (rook, bishop, queen) the attack masks are made with
                the help of magic numbers and blocker bitboards
    magic number + blocker bitboards = attack masks
*/
typedef struct {
    uint64_t pawn_attacks[2][64]; // white, black
    uint64_t knight[64];
    uint64_t king[64];
} leaper_moves_masks;

typedef struct {
    uint64_t rook[64][4096]; // 4096 is the maximum number of rook moves from a square
    uint64_t bishop[64][512]; // 512 is the maximum number of bishop moves from a square
    uint64_t bishop_occupancy_rays[64]; // occupancy rays
    uint64_t rook_occupancy_rays[64]; // occupancy rays
} slider_moves_masks;

leaper_moves_masks* create_leaper_moves_masks();

void init_pawn_leaper_moves_masks(leaper_moves_masks* masks);
void init_king_leaper_moves_masks(leaper_moves_masks* masks);
void init_knight_leaper_moves_masks(leaper_moves_masks* masks);
void init_leaper_moves_masks(leaper_moves_masks* masks);

uint64_t get_occupancy_permutation(int index, int bits, uint64_t mask);
slider_moves_masks* create_slider_moves_masks();

uint64_t bishop_attacks_on_the_fly(int square, uint64_t block);
uint64_t rook_attacks_on_the_fly(int square, uint64_t block);

void init_rook_occupancy_rays_masks(slider_moves_masks* masks);
void init_bishop_occupancy_rays_masks(slider_moves_masks* masks);
void init_rook_slider_moves_masks(slider_moves_masks* slider_mask);
void init_bishop_slider_moves_masks(slider_moves_masks* slider_mask);

void init_slider_moves_masks(slider_moves_masks* masks);

#endif // BITBOARD_H