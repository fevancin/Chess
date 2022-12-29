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

Index get_index_from_move(Game *game, Move *move) {
    Coordinate i = 0, j = 0;
    Index index = 0;
    Bitboard bitboard = (Bitboard)0;
    Color turn = get_turn(game);
    if (is_valid_coordinate(move->row_from)) {
        if (is_valid_coordinate(move->column_from)) return game->board[move->row_from][move->column_from];
        for (j = 0; j < BOARD_DIM; j++) {
            index = game->board[move->row_from][j];
            if (index != EMPTY && get_color(index) == turn && get_type(index) == move->piece_type) {
                get_bitboard(game, &bitboard, index);
                if (is_bitboard_bit(&bitboard, move->row_to, j)) return index;
            }
        }
    }
    if (is_valid_coordinate(move->column_from)) {
        for (i = 0; i < BOARD_DIM; i++) {
            index = game->board[i][move->column_from];
            if (index != EMPTY && get_color(index) == turn && get_type(index) == move->piece_type) {
                get_bitboard(game, &bitboard, index);
                if (is_bitboard_bit(&bitboard, i, move->column_to)) return index;
            }
        }
    }
    for (index = 0; index < PIECES_NUM; index++) {
        if (get_color(index) != turn || !is_alive(game->pieces[index]) || get_type(index) != move->piece_type) continue;
        get_bitboard(game, &bitboard, index);
        if (is_bitboard_bit(&bitboard, move->row_to, move->column_to)) return index;
    }
    return PIECES_NUM;
}

int apply_move(Game *game, Move *move) {
    if (!is_valid_move(move)) return 0;
    Index index = get_index_from_move(game, move);
    if (index == PIECES_NUM) return -1;
    if (index == EMPTY) return -1;
    if (!is_alive(game->pieces[index])) return -1;
    if (get_type(index) != move->piece_type) return -1;
    if (get_color(index) != get_turn(game)) return -1;
    move_piece(game, index, move->row_to, move->column_to);
    swap_turn(game);
    return 0;
}