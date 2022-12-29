#include "search.h"

Value search_step(Game *game, uint8_t depth) {
    if (depth >= MAX_DEPTH || is_game_end(game)) {
        return get_game_value(game);
    }
    Bitboard bitboard = (Bitboard)0;
    Game child_game;
    Color turn = get_turn(game);
    Coordinate i = 0, j = 0;
    Index index = (turn == WHITE) ? 0 : 1;
    Value child_value = 0;
    Value best_child_value = (turn == WHITE) ? -INFINITY : INFINITY;
    for (; index < PIECES_NUM; index += 2) {
        get_bitboard(game, &bitboard, index);
        for (i = 0; i < BOARD_DIM; i++) {
            for (j = 0; j < BOARD_DIM; j++) {
                if (get_bitboard_bit_and_shift(&bitboard)) {
                    copy_game(&child_game, game);
                    move_piece(&child_game, index, i, j);
                    swap_turn(&child_game);
                    child_value = search_step(&child_game, depth + 1);
                    if ((turn == WHITE && child_value > best_child_value) ||
                        (turn == BLACK && child_value < best_child_value)) {
                        best_child_value = child_value;
                    }
                }
            }
        }
    }
    return best_child_value;
}

Value search(Game *game, Move *best_move) {
    if (is_game_end(game)) {
        best_move->piece_type = UNKNOWN;
        best_move->column_from = BOARD_DIM;
        best_move->row_from = BOARD_DIM;
        best_move->column_to = BOARD_DIM;
        best_move->row_to = BOARD_DIM;
        return get_game_value(game);
    }
    Bitboard bitboard = (Bitboard)0;
    Game child_game;
    Color turn = get_turn(game);
    Coordinate i = 0, j = 0;
    Index index = (turn == WHITE) ? 0 : 1;
    Value child_value = 0;
    Value best_child_value = (turn == WHITE) ? -INFINITY : INFINITY;
    for (; index < PIECES_NUM; index += 2) {
        get_bitboard(game, &bitboard, index);
        for (i = 0; i < BOARD_DIM; i++) {
            for (j = 0; j < BOARD_DIM; j++) {
                if (get_bitboard_bit_and_shift(&bitboard)) {
                    copy_game(&child_game, game);
                    move_piece(&child_game, index, i, j);
                    swap_turn(&child_game);
                    child_value = search_step(&child_game, 1);
                    if ((turn == WHITE && child_value > best_child_value) ||
                        (turn == BLACK && child_value < best_child_value)) {
                        best_move->piece_type = get_type(index);
                        best_move->column_from = get_y(game->pieces[index]);
                        best_move->row_from = get_x(game->pieces[index]);
                        best_move->column_to = j;
                        best_move->row_to = i;
                        best_child_value = child_value;
                    }
                }
            }
        }
    }
    return best_child_value;
}