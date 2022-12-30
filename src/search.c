#include "search.h"

// auxiliary function that perform the depth-first search
Value search_step(Game *game, uint8_t depth) {
    // edge case return (leaf node)
    if (depth >= MAX_DEPTH || is_game_end(game)) {
        return get_game_value(game);
    }
    Bitboard bitboard = (Bitboard)0;
    Game child_game;
    Color turn = get_turn(game);
    Coordinate i = 0, j = 0;
    Value child_value = 0;
    Value best_child_value = (turn == WHITE) ? -INFINITY : INFINITY;
    // select only pieces of the right color, skipping the others
    Index index = (turn == WHITE) ? 0 : 1;
    for (; index < PIECES_NUM; index += 2) {
        get_bitboard(game, &bitboard, index);
        for (i = 0; i < BOARD_DIM; i++) {
            for (j = 0; j < BOARD_DIM; j++) {
                // for each legal move
                if (get_bitboard_bit_and_shift(&bitboard)) {
                    copy_game(&child_game, game);
                    move_piece(&child_game, index, i, j);
                    swap_turn(&child_game);
                    // execute the recursive search with additional depth
                    child_value = search_step(&child_game, depth + 1);
                    // evantually update the best value found so far
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
    // special case of game already ended
    if (is_game_end(game)) {
        best_move->piece_type = UNKNOWN;
        best_move->column_from = BOARD_DIM;
        best_move->row_from = BOARD_DIM;
        best_move->column_to = BOARD_DIM;
        best_move->row_to = BOARD_DIM;
        return get_game_value(game);
    }
    // similar algorithm of the former search_step, but with best_move memory
    Bitboard bitboard = (Bitboard)0;
    Game child_game;
    Color turn = get_turn(game);
    Coordinate i = 0, j = 0;
    Value child_value = 0;
    Value best_child_value = (turn == WHITE) ? -INFINITY : INFINITY;
    Index index = (turn == WHITE) ? 0 : 1;
    // select only pieces of the right color, skipping the others
    for (; index < PIECES_NUM; index += 2) {
        get_bitboard(game, &bitboard, index);
        for (i = 0; i < BOARD_DIM; i++) {
            for (j = 0; j < BOARD_DIM; j++) {
                if (get_bitboard_bit_and_shift(&bitboard)) {
                    copy_game(&child_game, game);
                    move_piece(&child_game, index, i, j);
                    swap_turn(&child_game);
                    // execute the recursive search with additional depth
                    child_value = search_step(&child_game, 1);
                    // evantually update the best value found so far
                    // and also best_move
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