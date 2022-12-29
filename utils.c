#include "utils.h"

int is_valid_coordinate(Coordinate coordinate) {
    return coordinate < BOARD_DIM;
}

Color swap_color(Color color) {
    return (color == WHITE) ? BLACK : WHITE;
}

Type type_map[PIECES_NUM] = {
    KING, KING,
    QUEEN, QUEEN,
    ROOK, ROOK, ROOK, ROOK,
    KNIGHT, KNIGHT, KNIGHT, KNIGHT,
    BISHOP, BISHOP, BISHOP, BISHOP,
    PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN,
    PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN
};

Type get_type(Index index) {
    if (index >= PIECES_NUM) return UNKNOWN;
    return type_map[index];
}

Color get_color(Index index) {
    return ((Color)index) & ((Color)0x01);
}