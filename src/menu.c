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

void clear_console() {
    printf("\e[1;1H\e[2J\n");
}

void print_menu_header() {
    clear_console();
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

void print_main_menu() {
    printf("\"play\" to play a new game\n");
    printf("\"load\" to load a game from file\n");
    printf("\"exit\" to exit the program\n");
    printf("Choose an option:\n> ");
}

void print_color_choosing_menu() {
    printf("\"white\" to play as white\n");
    printf("\"black\" to play as black\n");
    printf("\"back\" to return to the main menu\n");
    printf("Choose an option:\n> ");
}

void print_playing_menu() {
    printf("Enter a move for playing, or\n");
    printf("\"help\" for a summary of chess notation\n");
    printf("\"save\" for saving the game\n");
    printf("\"exit\" for exiting the program\n");
    printf("Choose an option:\n> ");
}

void print_help_text() {
    printf("help text...");
    printf("\"back\" for returning to the game\n> ");
}

void read_string_from_stdin(char *string, int max_length) {
    if (fgets(string, max_length, stdin) == NULL) {
        fprintf(stderr, "Error in string read\n");
        exit(EXIT_FAILURE);
    }
}