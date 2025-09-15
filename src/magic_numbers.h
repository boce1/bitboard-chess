#ifndef MAGIC_NUMBERS_H
#define MAGIC_NUMBERS_H

#include <stdio.h>
#include <stdint.h>
// #include "bitboard.h"

extern const uint64_t rook_magic_numbers[64];
extern const uint64_t bishop_magic_numbers[64];

/*
    FUNCTIONS BELLOW ARE ONLY RAN ONCE, 
    FOR PURPOUSE BEING GENERATING MAGIC NUMBERS.
    The idia is not generating them every time the program starts.
*/
extern unsigned int random_state;

unsigned int get_random_uint_32();
uint64_t get_random_uint64_t();
uint64_t generate_magic_number();

/*
uint64_t find_magic_number(int square, int relevant_bits, int piece_type, leaper_moves_masks* masks);
void print_magic_numbers(int piece_type, leaper_moves_masks* masks);
*/
#endif // MAGIC_NUMBERS_H