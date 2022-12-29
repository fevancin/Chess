#include "utils.h"

typedef uint8_t Piece;

Coordinate get_x(Piece piece);
Coordinate get_y(Piece piece);
int is_alive(Piece piece);
int is_promoted(Piece piece);

void set_x(Piece *piece, Coordinate x);
void set_y(Piece *piece, Coordinate y);
void kill(Piece *piece);
void revive(Piece *piece);
void depromote(Piece *piece);
void promote(Piece *piece);