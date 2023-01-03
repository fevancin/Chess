#include "search.h"

// the file format of a game save is formed by PIECES_NUM rows
// expressed in index order (0 is always WHITE KING, etc..)
// of the form "COL ROW ALIVE PROMOTED\n" in witch:
// - COL is a char 'a'-'h',
// - ROW is '1'-'8',
// - ALIVE and PROMOTED are '0' or '1'.

// create or overwrite a file with game data.
// returns 0 on success
int write_game_to_file(Game *game, char *file_name);

// read and decode a file with game data.
// returns 0 on success
int read_game_from_file(Game *game, char *file_name);

typedef uint8_t MenuState;

#define MAIN_MENU_STATE 0
#define COLOR_CHOOSING_STATE 1
#define LOAD_GAME_STATE 2
#define EXITING_STATE 3
#define PLAYING_STATE 4
#define SAVE_GAME_STATE 5
#define HELP_STATE 6

void clear_console();

void print_menu_header();
void print_main_menu();
void print_color_choosing_menu();
void print_playing_menu();
void print_help_text();

// reads max_length - 1 chars from stdin in a safe manner
void read_string_from_stdin(char *string, int max_length);