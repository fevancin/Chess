#include "bitboard.h"

// contains the informations of a move inserted by the human player:
// type of piece moved, source and destination of the move.
typedef struct move {
    Type piece_type;
    Coordinate row_from;
    Coordinate column_from;
    Coordinate row_to;
    Coordinate column_to;
} Move;

// sets default empty values
void empty_move(Move *move);

// check for validity (valid type, valid destination)
int is_valid_move(Move *move);

// safe apply of the given move to the game, returning 0 if successfull.
// swaps the turn.
int apply_move(Game *game, Move *move);

// returns the row coordinate of a char '1' to '8'
Coordinate decode_row_char(char c);

// returns the column coordinate of a char 'a' to 'h'
Coordinate decode_column_char(char c);

// translate a string to a move, returning 0 on success
int decode_move(char *string, Move *move);

// prints a well formatted move to console
void print_move(Move *move);