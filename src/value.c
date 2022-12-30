#include "header/value.h"

Value piece_values[6] = {10000.0, 90.0, 50.0, 30.0, 30.0, 10.0};

Value square_values[BOARD_DIM][BOARD_DIM] = {
    {1.0, 2.0, 3.0, 4.0, 4.0, 3.0, 2.0, 1.0},
    {2.0, 3.0, 4.0, 5.0, 5.0, 4.0, 3.0, 2.0},
    {3.0, 4.0, 5.0, 6.0, 6.0, 5.0, 4.0, 3.0},
    {4.0, 5.0, 6.0, 7.0, 7.0, 6.0, 5.0, 4.0},
    {4.0, 5.0, 6.0, 7.0, 7.0, 6.0, 5.0, 4.0},
    {3.0, 4.0, 5.0, 6.0, 6.0, 5.0, 4.0, 3.0},
    {2.0, 3.0, 4.0, 5.0, 5.0, 4.0, 3.0, 2.0},
    {1.0, 2.0, 3.0, 4.0, 4.0, 3.0, 2.0, 1.0}
};

Value get_game_value(Game *game) {
    // default values of a checkmate
    if (is_game_end(game)) return (get_turn(game) == WHITE) ? -10000.0 : 10000.0;
    Index index = 0;
    Value value = 0.0;
    Piece piece = 0;
    Bitboard bitboard = (Bitboard)0;
    Coordinate i = 0, j = 0;
    Value color_multiplier = 0.0;
    for (index = 0; index < PIECES_NUM; index++) {
        piece = game->pieces[index];
        if (is_alive(piece)) {
            // sum of piece values
            color_multiplier = (get_color(index) == WHITE) ? 1.0 : -1.0;
            value += piece_values[get_type(index)] * color_multiplier;
            // sum of values of the square occupied (central is better)
            value += square_values[get_x(piece)][get_y(piece)] * color_multiplier;
            get_bitboard(game, &bitboard, index);
            for (i = 0; i < BOARD_DIM * BOARD_DIM; i++) {
                // sum of all the possible moves of the pieces (more is better)
                if (get_bitboard_bit_and_shift(&bitboard)) value += color_multiplier;
            }
        }
    }
    return value;
}