#include "utils.h"

// pieces are bytes with fixed fields:
// bits 012 are the y coordinate (column)
// bit 3 is the promoted flag
// bit 4 is the alive flag
// bits 567 are the x coordinate (row)
typedef uint8_t Piece;

// returns the row coordinate of the piece
Coordinate get_x(Piece piece);

// returns the column coordinate of the piece
Coordinate get_y(Piece piece);

// true if the piece is alive
int is_alive(Piece piece);

// true if the piece is promoted
int is_promoted(Piece piece);

// sets 00000XXX bits
void set_x(Piece *piece, Coordinate x);

// sets XXX00000 bits
void set_y(Piece *piece, Coordinate y);

// sets 000X0000 bit at 0
void kill(Piece *piece);

// sets 000X0000 bit at 1
void revive(Piece *piece);

// sets 0000X000 bit at 0
void depromote(Piece *piece);

// sets 0000X000 bit at 1
void promote(Piece *piece);