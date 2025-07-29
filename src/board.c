#include "board.h"

const char ascii_pieces[12] = "PNBRQKpnbrqk";
const int char_to_piece[] = { 
    ['P'] = P, ['N'] = N, ['B'] = B, ['R'] = R, ['Q'] = Q, ['K'] = K,
    ['p'] = p, ['n'] = n, ['b'] = b, ['r'] = r, ['q'] = q, ['k'] = k
    // maps ASCII characters to piece types
};

void init_board(Board* board) {
    for (int i = 0; i < 12; i++) {
        board->pieces[i] = 0ULL;
    }
    for (int i = 0; i < 3; i++) {
        board->occupancies[i] = 0ULL;
    }

    board->side_to_move = white;
    board->en_passant_square = no_square;
    board->castling_rights = wk | wq | bk | bq;
}

Board* create_board() {
    Board* board = (Board*)malloc(sizeof(Board));
    if (!board) {
        fprintf(stderr, "Memory allocation failed for Board\n");
        exit(EXIT_FAILURE);
    }

    init_board(board);
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
    printf("    Castling: %c%c%c%c\n\n", board->castling_rights & wk ? 'K' : '-', 
                                        board->castling_rights & wq ? 'Q' : '-', 
                                        board->castling_rights & bk ? 'k' : '-', 
                                        board->castling_rights & bq ? 'q' : '-');
}


void parse_fen(char *fen, Board* board) {
    memset(board->pieces, 0ULL, sizeof(board->pieces));
    memset(board->occupancies, 0ULL, sizeof(board->occupancies));
    board->side_to_move = 0;
    board->en_passant_square = no_square;
    board->castling_rights = 0;

    for(int rank=0; rank<8; rank++) {
        for(int file=0; file<8; file++) {
            int square = rank * 8 + file;

            if((*fen >= 'a' && *fen <= 'z') || (*fen >= 'A' && *fen <= 'Z')) {
                int piece = char_to_piece[(unsigned char)*fen];

                set_bit(board->pieces[piece], square);
                fen++;
            }
            if(*fen >= '0' && *fen <= '9') {
                int offset = *fen - '0';

                int piece = -1;
                for(int bb_piece=P; bb_piece <= k; bb_piece++) {
                    if(get_bit(board->pieces[bb_piece], square))
                        piece = bb_piece;
                }
                if(piece == -1) {
                    file--;
                }
                file += offset;
                fen++;
            }
            if(*fen == '/') fen++;
        } 
    }
    fen++;
    (*fen == 'w') ? (board->side_to_move = white) : (board->side_to_move = black);
    fen += 2;
    while(*fen != ' ') {
        switch(*fen) {
            case 'K': board->castling_rights |= wk; break;
            case 'Q': board->castling_rights |= wq; break;
            case 'k': board->castling_rights |= bk; break;
            case 'q': board->castling_rights |= bq; break;
            case '-': break;
        }
        fen++;
    }
    fen++;
    if(*fen != '-') {
        int file = fen[0] - 'a';
        int rank = 8 - (fen[1] - '0');
        board->en_passant_square = 8 * rank + file;
    } else {
        board->en_passant_square = no_square;
    }
    
    // white pieces bitboards
    for(int piece = P; piece<= K; piece++) {
        board->occupancies[white] |= board->pieces[piece];
    }
    // black pieces bitboards
    for(int piece = p; piece<= k; piece++) {
        board->occupancies[black] |= board->pieces[piece];
    }

    board->occupancies[both] |= board->occupancies[white];
    board->occupancies[both] |= board->occupancies[black];
}

int is_square_attacked(int square, Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks) {
    // returns if the square is attacked by any piece of the opposite side
    // pawns
    int side;
    if(board->side_to_move == black) {
        side = white;
    } else {
        side = black;
    }

    if((side == white) && (get_pawn_attacks(leaper_masks, square, black) & board->pieces[P])) return 1;
    if((side == black) && (get_pawn_attacks(leaper_masks, square, white) & board->pieces[p])) return 1;
    // knight
    if(get_knight_attacks(leaper_masks, square) & 
    ((side == white) ? board->pieces[N] : board->pieces[n])) return 1;
    // king
    if(get_king_attacks(leaper_masks, square) & 
    ((side == white) ? board->pieces[K] : board->pieces[k])) return 1;
    // rook
    if(get_rook_attacks(slider_masks, square, board->occupancies[both]) & 
    ((side == white) ? board->pieces[R] : board->pieces[r])) return 1;
    // bishop
    if(get_bishop_attacks(slider_masks, square, board->occupancies[both]) & 
    ((side == white) ? board->pieces[B] : board->pieces[b])) return 1;
    // queen
    if(get_queen_attacks(slider_masks, square, board->occupancies[both]) & 
    ((side == white) ? board->pieces[Q] : board->pieces[q])) return 1;
    return 0;
}

void print_attacked_squares(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks) {
    int square;
    for(int rank = 0; rank < 8; rank++) {
        for(int file = 0; file < 8; file++) {
            square = rank * 8 + file;
            if(!file) {
                printf(" %d ", 8 - rank); // print rank number
            }
            printf(" %d", is_square_attacked(square, board, leaper_masks, slider_masks) ? 1 : 0);            
        }
        printf("\n");
    }
    printf("\n    a b c d e f g h\n\n");
}
