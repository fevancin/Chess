#include <signal.h>
#include "header/menu.h"

void handler() {
    clear_console();
    printf("Exiting the program..\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, handler);
    Game game;
    Move move;
    MenuState state = MAIN_MENU_STATE;
    char string[PATH_MAX];
    while (1) {
        switch (state) {
        case MAIN_MENU_STATE:
            print_menu_header();
            print_main_menu();
            read_string_from_stdin(string, PATH_MAX);
            if (strcmp(string, "play\n") == 0) state = COLOR_CHOOSING_STATE;
            else if (strcmp(string, "load\n") == 0) state = LOAD_GAME_STATE;
            else if (strcmp(string, "exit\n") == 0) state = EXITING_STATE;
            break;
        case COLOR_CHOOSING_STATE:
            print_menu_header();
            print_color_choosing_menu();
            read_string_from_stdin(string, PATH_MAX);
            if (strcmp(string, "white\n") == 0) {
                place_initial_configuration(&game);
                state = PLAYING_STATE;
            } else if (strcmp(string, "black\n") == 0) {
                place_initial_configuration(&game);
                search(&game, &move); // computer do the first move
                apply_move(&game, &move);
                state = PLAYING_STATE;
            } else if (strcmp(string, "back\n") == 0) state = MAIN_MENU_STATE;
            break;
        case LOAD_GAME_STATE:
            print_menu_header();
            printf("Insert a path to a save file\n> ");
            read_string_from_stdin(string, PATH_MAX);
            *strchr(string, '\n') = '\0'; // replace first \n with \0
            if (read_game_from_file(&game, string) != 0) {
                fprintf(stderr, "Error in file read\n");
                state = MAIN_MENU_STATE;
            } else {
                printf("File \"%s\" read successfully\n", string);
                state = PLAYING_STATE;
            }
            break;
        case EXITING_STATE:
            clear_console();
            printf("Exiting the program..\n");
            exit(EXIT_SUCCESS);
            break;
        case PLAYING_STATE:
            clear_console();
            print_game(&game);
            print_playing_menu();
            read_string_from_stdin(string, PATH_MAX);
            if (strcmp(string, "help\n") == 0) state = HELP_STATE;
            else if (strcmp(string, "save\n") == 0) state = SAVE_GAME_STATE;
            else if (strcmp(string, "exit\n") == 0) state = EXITING_STATE;
            else if (
                decode_move(string, &move) != 0 ||
                apply_move(&game, &move) != 0
            ) {
                printf("Move not valid\n");
                continue;
            }
            if (state == PLAYING_STATE) {
                search(&game, &move); // computer move
                apply_move(&game, &move);
            }
            break;
        case SAVE_GAME_STATE:
            clear_console();
            print_game(&game);
            printf("Insert the path to the new save file\n> ");
            read_string_from_stdin(string, PATH_MAX);
            *strchr(string, '\n') = '\0'; // replace first \n with \0
            if (write_game_to_file(&game, string) != 0) {
                fprintf(stderr, "Error in file write\n");
            } else printf("File \"%s\" written successfully\n", string);
            state = PLAYING_STATE;
            break;
        case HELP_STATE:
            clear_console();
            print_help_text();
            read_string_from_stdin(string, PATH_MAX);
            if (strcmp(string, "back\n") == 0) state = PLAYING_STATE;
            break;
        }
    }
}