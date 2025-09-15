#include "zoobrist_hash.h"

zoobrist_hash_keys* create_zoobrist_hash_keys() {
    zoobrist_hash_keys* hash_data = (zoobrist_hash_keys*)malloc(sizeof(zoobrist_hash_keys));
    if (!hash_data) {
        fprintf(stderr, "Memory allocation failed for zoobrist_hash_keys\n");
        exit(EXIT_FAILURE);
    }
    return hash_data;
}

void init_zoobrist_random_keys(zoobrist_hash_keys* hash_data) {
    // The seed is the random_state variable from magic_numbers.c
    // function for getting the random u64 ints are also from magic_numbers.c

    for (int piece = P; piece <= k; piece++) {
        for (int square = 0; square < 64; square++) {
            hash_data->piece_keys[piece][square] = get_random_uint64_t();
        }
    }

    for (int square = 0; square < 64; square++) {
        hash_data->en_passant_keys[square] = get_random_uint64_t();
    }

    for (int i = 0; i < 16; i++) {
        hash_data->castle_keys[i] = get_random_uint64_t();
    }

    hash_data->side_keys = get_random_uint64_t();
}