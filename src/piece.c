#include "piece.h"

#define X_MASK ((Piece)0x07)
#define Y_MASK ((Piece)0xE0)
#define ALIVE_MASK ((Piece)0x10)
#define PROMOTED_MASK ((Piece)0x08)
#define Y_SHIFT ((Piece)5)
#define NEGATED_X_MASK ((Piece)0xF8)
#define NEGATED_Y_MASK ((Piece)0x1F)
#define NEGATED_ALIVE_MASK ((Piece)0xEF)
#define NEGATED_PROMOTED_MASK ((Piece)0xF7)

Coordinate get_x(Piece piece) {
    return piece & X_MASK;
}
Coordinate get_y(Piece piece) {
    return piece >> Y_SHIFT;
}
int is_alive(Piece piece) {
    return (piece & ALIVE_MASK) == ALIVE_MASK;
}
int is_promoted(Piece piece) {
    return (piece & PROMOTED_MASK) == PROMOTED_MASK;
}

void set_x(Piece *piece, Coordinate x) {
    *piece = ((*piece) & NEGATED_X_MASK) | x;
}
void set_y(Piece *piece, Coordinate y) {
    *piece = ((*piece) & NEGATED_Y_MASK) | (y << Y_SHIFT);
}
void kill(Piece *piece) {
    *piece &= NEGATED_ALIVE_MASK;
}
void revive(Piece *piece) {
    *piece |= ALIVE_MASK;
}
void depromote(Piece *piece) {
    *piece &= NEGATED_PROMOTED_MASK;
}
void promote(Piece *piece) {
    *piece |= PROMOTED_MASK;
}