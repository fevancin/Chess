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

// search and execute the best move in the current situation
void make_computer_move(Game *game);

void clear_console();

// game mechanics of a human-computer match
void play_game(Game *game);

void print_intro();

// menu mechanics
void play_menu(Game *game);