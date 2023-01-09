#include <signal.h>
#include "header/menu.h"

// menu is treated as a finite-state machine
// with every window as a different state
// descripted by the following constants
typedef uint8_t MenuState;
#define MAIN_MENU_STATE ((MenuState)0)
#define COLOR_CHOOSING_STATE ((MenuState)1)
#define LOAD_GAME_STATE ((MenuState)2)
#define EXITING_STATE ((MenuState)3)
#define PLAYING_STATE ((MenuState)4)
#define SAVE_GAME_STATE ((MenuState)5)
#define HELP_STATE ((MenuState)6)

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
    char menu_message[100];
    memset(menu_message, '\0', 100);
    while (1) {
        switch (state) {
        case MAIN_MENU_STATE:
            print_menu_header();
            if (menu_message[0] != '\0') {
                printf("%s\n", menu_message);
                menu_message[0] = '\0';
            }
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
            printf("Insert a path to a save file (\"back\" to return)\n> ");
            read_string_from_stdin(string, PATH_MAX);
            if (strcmp(string, "back\n") == 0) {
                state = MAIN_MENU_STATE;
                continue;
            }
            *strchr(string, '\n') = '\0'; // replace first \n with \0
            if (read_game_from_file(&game, string) != 0) {
                strcpy(menu_message, "Error in file read\n");
                state = MAIN_MENU_STATE;
            } else {
                strcpy(menu_message, "File read successfully\n");
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
            if (menu_message[0] != '\0') {
                printf("%s\n", menu_message);
                menu_message[0] = '\0';
            }
            print_playing_menu();
            read_string_from_stdin(string, PATH_MAX);
            if (strcmp(string, "help\n") == 0) state = HELP_STATE;
            else if (strcmp(string, "save\n") == 0) state = SAVE_GAME_STATE;
            else if (strcmp(string, "exit\n") == 0) state = EXITING_STATE;
            else if (
                decode_move(string, &move) != 0 ||
                apply_move(&game, &move) != 0
            ) {
                strcpy(menu_message, "Move not valid\n");
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
            printf("Insert the path to the new save file (\"back\" to return)\n> ");
            read_string_from_stdin(string, PATH_MAX);
            if (strcmp(string, "back\n") == 0) {
                state = PLAYING_STATE;
                continue;
            }
            *strchr(string, '\n') = '\0'; // replace first \n with \0
            if (write_game_to_file(&game, string) != 0) {
                fprintf(stderr, "Error in file write\n");
            } else strcpy(menu_message, "File written successfully\n");
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