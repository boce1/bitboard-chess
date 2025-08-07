#include "uci.h"

int parse_move(char* move_string, Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks) {
    Moves move_list[1];
    init_move_list(move_list);
    generate_moves(board, leaper_masks, slider_masks, move_list);

    int source_square = (move_string[0] - 'a') + (8 - (move_string[1] - '0')) * 8;
    int target_square = (move_string[2] - 'a') + (8 - (move_string[3] - '0')) * 8;
    int promoted_piece = no_piece;

    int move;
    for(int move_count = 0; move_count < move_list->count; move_count++) {
        move = move_list->moves[move_count];

        if(source_square == get_move_source(move) && target_square == get_move_target(move)) {
            promoted_piece = get_move_promoted(move);

            if(promoted_piece) {
                if((promoted_piece == Q || promoted_piece == q) && move_string[4] == 'q') {
                return move;
                }
                else if((promoted_piece == R || promoted_piece == r) && move_string[4] == 'r') {
                    return move;
                }
                else if((promoted_piece == B || promoted_piece == b) && move_string[4] == 'b') {
                    return move;
                }
                else if((promoted_piece == N || promoted_piece == n) && move_string[4] == 'n') {
                    return move;
                }
                continue;
            } 

            return move; // legal move
        }
    }

    return 0; // illegal move
}

/*
for UCI commands are being executed in terminal
each command starts with "position"

to command user can pas FEN string
or FEN string + moves to make
*/

void parse_position(char* command, Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks) {
    command += 9;
    char* current_char = command;

    // parse UCI startpos command
    if(strncmp(command, "startpos", 8) == 0) {
        parse_fen(start_position, board);
    } else { // parse UCI FEN command
        // make sure FEN is available within command string
        current_char = strstr(command, "fen");
        if(current_char == NULL) {
            parse_fen(start_position, board);
        } else {
            current_char += 4; // "fen" + " "
            parse_fen(current_char, board);
        }
    }

    current_char = strstr(command, "moves");
    if(current_char != NULL) {
        current_char += 6; // "moves" + " "
        while(*current_char) {
            int move = parse_move(current_char, board, leaper_masks, slider_masks);

            if(move == 0) {
                break;
            }

            make_move(board, move, all_moves, leaper_masks, slider_masks);

            while(*current_char && *current_char != ' ') {
                current_char++;
            }
            current_char++;
        }
    }
    print_board(board);
}


void parse_go(char* command, Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks) {
    // go depth n
    int depth = 3;
    char* current_char = NULL;
    if((current_char = strstr(command, "depth"))) {
        depth = atoi(current_char + 6); // "depth "
    } 
    search_position(depth, board, leaper_masks, slider_masks);
}

/*
start
GUI - isready
Engine - readyok
GUI - ucinewgame
*/
void uci_loop(Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks) {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    char input[2000];

    printf("id name Engine\n");
    printf("id name Boyan\n");
    printf("uciok\n");

    while(1) {
        memset(input, 0, sizeof(input));

        fflush(stdout);
        if(!fgets(input, 2000, stdin)) {
            continue;
        }
        if(input[0] == '\n') {
            continue;
        }

        if(strncmp(input, "isready", 7) == 0) {
            printf("readyok\n");
            continue;
        }
        else if(strncmp(input, "position", 8) == 0) {
            parse_position(input, board, leaper_masks, slider_masks);
        }
        else if(strncmp(input, "ucinewgame", 10) == 0) {
            parse_position("position startpos", board, leaper_masks, slider_masks);
        }
        else if(strncmp(input, "go", 2) == 0) {
            parse_go(input, board, leaper_masks, slider_masks);
        }
        else if(strncmp(input, "quit", 4) == 0) {
            break;
        }
        else if(strncmp(input, "uci", 3) == 0) {
            // testing if the engine supports uci protocol
            printf("id name Engine\n");
            printf("id name Boyan\n");
            printf("uciok\n");
        }
    }

}

void search_position(int depth, Board* board, leaper_moves_masks* leaper_masks, slider_moves_masks* slider_masks) {
    int score = negamax(board, leaper_masks, slider_masks, ALPHA, BETA, depth);
    int source_square = get_move_source(best_move);
    int target_square = get_move_target(best_move);
    printf("info score cp %d depth %d nodes %ld\n", score, depth, nodes);
    printf("bestmove %s%s\n", square_to_cordinates[source_square], square_to_cordinates[target_square]);    
}