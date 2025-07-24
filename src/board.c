#include "board.h"

const char ascii_pieces[12] = "PNBRQKpnbrqk";
const int char_to_piece[] = { 
    ['P'] = P, ['N'] = N, ['B'] = B, ['R'] = R, ['Q'] = Q, ['K'] = K,
    ['p'] = p, ['n'] = n, ['b'] = b, ['r'] = r, ['q'] = q, ['k'] = k
    // maps ASCII characters to piece types
};

Board* create_board() {
    Board* board = (Board*)malloc(sizeof(Board));
    if (!board) {
        fprintf(stderr, "Memory allocation failed for Board\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 12; i++) {
        board->pieces[i] = 0ULL;
    }
    for (int i = 0; i < 3; i++) {
        board->occupancies[i] = 0ULL;
    }

    board->side_to_move = white;
    board->en_passant_square = no_square;
    board->castling_rights = wk | wq | bk | bq;
    return board;
}

void print_board(Board* board) {
    int square, piece, i;
    for(int rank = 0; rank < 8; rank++) {
        for(int file = 0; file < 8; file++) {
            square = rank * 8 + file;
            if(!file) {
                printf(" %d ", 8 - rank); // print rank number
            }
            piece = -1; // default to empty square

            for(i = P; i <= k; i++) {
                if (board->pieces[i] & (1ULL << square)) {
                    piece = i;
                }
            }

            printf(" %c", (piece == -1) ? '.' : ascii_pieces[piece]);
        }
        printf("\n");
    }
    printf("\n    a b c d e f g h\n");
    printf("    Side: %s\n", (board->side_to_move == white) ? "White" : "Black");
    printf("    Enpassant: %s\n", square_to_cordinates[board->en_passant_square]);
    printf("    Castling: %c%c%c%c\n", board->castling_rights & wk ? 'K' : '-', 
                                        board->castling_rights & wq ? 'Q' : '-', 
                                        board->castling_rights & bk ? 'k' : '-', 
                                        board->castling_rights & bq ? 'q' : '-');
}
