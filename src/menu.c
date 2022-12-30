#include "header/menu.h"

int write_game_to_file(Game *game, char *file_name) {
    if (game == NULL || file_name == NULL) return -1;
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL) return -1;
    Index index = 0;
    Piece piece = 0;
    for (index = 0; index < PIECES_NUM; index++) {
        piece = game->pieces[index];
        fprintf(fp, "%c %c %d %d\n",
            to_column_char(get_y(piece)),
            to_row_char(get_x(piece)),
            is_alive(piece),
            is_promoted(piece)
        );
    }
    fclose(fp);
    return 0;
}

int read_game_from_file(Game *game, char *file_name) {
    if (game == NULL || file_name == NULL) return -1;
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) return -1;
    empty_game(game);
    Index index = 0;
    Piece *piece = NULL;
    char string[9];
    for (index = 0; index < PIECES_NUM; index++) {
        if (fgets(string, 9, fp) == NULL) {
            fclose(fp);
            return -1;
        }
        piece = &(game->pieces[index]);
        if (!is_column_char(string[0])) return -1;
        set_y(piece, decode_column_char(string[0]));
        if (string[1] != ' ') return -1;
        if (!is_row_char(string[2])) return -1;
        set_x(piece, decode_row_char(string[2]));
        if (string[3] != ' ') return -1;
        if (string[4] != '0' && string[4] != '1') return -1;
        if (string[4] == '0') kill(piece);
        else revive(piece);
        if (string[5] != ' ') return -1;
        if (string[6] != '0' && string[6] != '1') return -1;
        if (string[6] == '0') depromote(piece);
        else promote(piece);
        if (string[7] != '\n') return -1;
        game->board[get_x(*piece)][get_y(*piece)] = index;
    }
    fclose(fp);
    return 0;
}

void make_computer_move(Game *game) {
    Move move;
    search(game, &move);
    apply_move(game, &move);
}

void clear_console() {
    printf("\e[1;1H\e[2J\n");
}

void play_game(Game *game) {
    Move move;
    char string[PATH_MAX];
    empty_move(&move);
    printf("\n");
    do {
        print_game(game);
        printf("Insert a move for ");
        if (get_turn(game) == WHITE) printf("WHITE");
        else printf("BLACK");
        printf("\n(\"quit\" for exiting, \"save\" for saving the game)\n> ");
        if (fgets(string, 32, stdin) == NULL) {
            fprintf(stderr, "Error in input read\n");
            break;
        }
        else if (strcmp(string, "quit\n") == 0) {
            printf("Exiting the program...\n");
            break;
        }
        else if (strcmp(string, "save\n") == 0) {
            printf("Insert the path of the file:\n> ");
            if (fgets(string, PATH_MAX, stdin) == NULL) {
                fprintf(stderr, "Error in path read\n");
                continue;
            }
            clear_console();
            *strchr(string, '\n') = '\0';
            if (write_game_to_file(game, string) != 0) {
                fprintf(stderr, "Error in file write\n");
                continue;
            }
            printf("File \"%s\" written successfully\n", string);
            continue;
        }
        if (decode_move(string, &move) != 0 || apply_move(game, &move) != 0) {
            printf("Move not valid\n");
            continue;
        }
        make_computer_move(game);
        clear_console();
        printf("Executed %s", string);
    } while (!is_game_end(game));
    if (is_game_end(game)) {
        print_game(game);
        printf("Game ended by checkmate\n");
    }
}

void print_intro() {
    printf("      ___ ___  _,, __ ___ ___ ___ ___\n");
    printf("     /.  /   /\"-X\\~  / + /   /   /   /\n");
    printf("    /_()/___/___)(__/__()___/___/___/\n");
    printf("   /  )(   /   /XX\\/   )(  /   /   /\n");
    printf("  /___)(__/___/___/___/)(_/___/___/\n");
    printf(" /   /__\\/   /   /   //__\\   /   /\n");
    printf("/___/___/___/___/___/___/___/___/\n");
    printf("    o-----------------------o\n");
    printf("    |     Chess Engine      |\n");
    printf("    o-----------------------o\n");
}

void play_menu(Game *game) {
    int input_length = PATH_MAX;
    char string[input_length];
    int can_start_game = 0;
    clear_console();
    print_intro();
    do {
        printf("* play -> Play a game\n");
        printf("* load -> Load a save\n");
        printf("* quit -> Quit the program\n");
        printf("Choose an option:\n> ");
        if (fgets(string, input_length, stdin) == NULL) {
            fprintf(stderr, "Error in option read\n");
            exit(-1);
        } else if (strcmp(string, "quit\n") == 0) {
            printf("Exiting the program...\n");
            exit(0);
        } else if (strcmp(string, "load\n") == 0) {
            printf("Insert the path of the save file:\n> ");
            if (fgets(string, input_length, stdin) == NULL) {
                clear_console();
                print_intro();
                fprintf(stderr, "Error in path read\n");
                continue;
            }
            *strchr(string, '\n') = '\0';
            if (read_game_from_file(game, string) != 0) {
                clear_console();
                print_intro();
                fprintf(stderr, "Error in file read\n");
                continue;
            }
            can_start_game = 1;
            printf("File \"%s\" read successfully\n", string);
        } else if (strcmp(string, "play\n") == 0) {
            do {
                printf("Choose a color for a new game:\n");
                printf("* white\n");
                printf("* black\n");
                printf("* back\n> ");
                if (fgets(string, input_length, stdin) == NULL) {
                    fprintf(stderr, "Error in option read\n");
                    exit(-1);
                } else if (strcmp(string, "white\n") == 0) {
                    place_initial_configuration(game);
                    can_start_game = 1;
                    break;
                } else if (strcmp(string, "black\n") == 0) {
                    place_initial_configuration(game);
                    make_computer_move(game);
                    can_start_game = 1;
                    break;
                } else if (strcmp(string, "back\n") == 0) {
                    clear_console();
                    print_intro();
                    break;
                }
            } while (1);
        } else {
            clear_console();
            print_intro();
            fprintf(stderr, "Option not recognized\n");
        }
    } while (!can_start_game);
}