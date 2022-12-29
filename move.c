#include "move.h"

void empty_move(Move *move) {
    move->piece_type = UNKNOWN;
    move->row_from = BOARD_DIM;
    move->column_from = BOARD_DIM;
    move->row_to = BOARD_DIM;
    move->column_to = BOARD_DIM;
}

int is_valid_move(Move *move) {
    if (move->piece_type == UNKNOWN) return 0;
    if (!is_valid_coordinate(move->row_to) || !is_valid_coordinate(move->column_to)) return 0;
    return 1;
}