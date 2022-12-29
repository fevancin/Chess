#include "search.h"

int write_game_to_file(Game *game, char *file_name);
int read_game_from_file(Game *game, char *file_name);

void make_computer_move(Game *game);

void clear_console();

void play_game(Game *game);

void print_intro();

void play_menu(Game *game);