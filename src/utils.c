#include "utils.h"

int is_valid_coordinate(Coordinate coordinate) {
    return coordinate < BOARD_DIM;
}

Color swap_color(Color color) {
    return (color == WHITE) ? BLACK : WHITE;
}

char char_map[2][7] = {
    {'K', 'Q', 'R', 'N', 'B', 'P', '?'},
    {'k', 'q', 'r', 'n', 'b', 'p', '?'}
};

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

char get_piece_char(Index index) {
    if (index == EMPTY) return '.';
    return char_map[get_color(index)][get_type(index)];
}