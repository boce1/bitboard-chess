#ifndef ZOOBRIST_HASH_H
#define ZOOBRIST_HASH_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "magic_numbers.h"
#include "board.h"

typedef struct {
    uint64_t piece_keys[12][64]; // 12 pieces, 64 squares
    uint64_t en_passant_keys[64]; // 8 possible en passant files (a-h)
    uint64_t castle_keys[16]; // 16 possible castling rights combinations
    uint64_t side_keys; // side to move
} zoobrist_hash_keys;

zoobrist_hash_keys* create_zoobrist_hash_keys();
void init_zoobrist_random_keys(zoobrist_hash_keys* hash_data);

#endif // ZOOBRIST_HASH_H