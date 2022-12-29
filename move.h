#include "bitboard.h"

typedef struct move {
    Type piece_type;
    Coordinate row_from;
    Coordinate column_from;
    Coordinate row_to;
    Coordinate column_to;
} Move;

void empty_move(Move *move);

int is_valid_move(Move *move);

Index get_index_from_move(Game *game, Move *move);

int apply_move(Game *game, Move *move);

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