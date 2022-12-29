#include "move.h"
#include "game.h"

char get_piece_char(Index index);

void print_game(Game *game);

Type decode_piece_type(char c);
Coordinate decode_row_char(char c);
Coordinate decode_column_char(char c);
int is_piece_type_char(char c);
int is_row_char(char c);
int is_column_char(char c);
int is_capture_char(char c);

int get_string_length(char *string, int max_length);

int decode_move(char *string, Move *move);

char to_row_char(Coordinate x);
char to_column_char(Coordinate y);
char to_piece_type_char(Type type);

void print_move(Move *move);

void print_debug_info(Game *game);