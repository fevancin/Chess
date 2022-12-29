#include "bitboard.h"

typedef struct move_vector {
    int8_t dx;
    int8_t dy;
    uint8_t times;
} MoveVector;

MoveVector move_vector[5][8] = {
    {{-1, -1, 1}, {-1, 0, 1}, {-1,  1, 1}, { 0, -1, 1}, {0,  1, 1}, {1, -1, 1}, {1,  0, 1}, {1, 1, 1}},
    {{-1, -1, 8}, {-1, 0, 8}, {-1,  1, 8}, { 0, -1, 8}, {0,  1, 8}, {1, -1, 8}, {1,  0, 8}, {1, 1, 8}},
    {{ 0,  0, 0}, {-1, 0, 1}, { 0,  0, 0}, { 0, -1, 1}, {0,  1, 1}, {0,  0, 0}, {1,  0, 1}, {0, 0, 0}},
    {{-2, -1, 1}, {-2, 1, 1}, {-1, -2, 1}, {-1,  2, 1}, {1, -2, 1}, {1,  2, 1}, {2, -1, 1}, {2, 1, 1}},
    {{-1, -1, 1}, { 0, 0, 0}, {-1,  1, 1}, { 0,  0, 0}, {0,  0, 0}, {1, -1, 1}, {0,  0, 0}, {1, 1, 1}}
};

void set_bitboard_bit(Bitboard *bitboard, Coordinate x, Coordinate y) {
    *bitboard |= ((Bitboard)1) << (x * BOARD_DIM + y);
}

int is_bitboard_bit(Bitboard *bitboard, Coordinate x, Coordinate y) {
    return (*bitboard & ((Bitboard)1) << (x * BOARD_DIM + y)) != 0;
}

int get_bitboard_bit_and_shift(Bitboard *bitboard) {
    int bit = *bitboard & ((Bitboard)1);
    *bitboard >>= 1;
    return bit;
}

void get_pawn_bitboard(Game *game, Bitboard *bitboard, Index index) {
    *bitboard = (Bitboard)0;
    Color color = get_color(index);
    Piece piece = game->pieces[index];
    Coordinate start_x = get_x(piece);
    Coordinate start_y = get_y(piece);
    int8_t dx = (color == WHITE) ? -1 : 1;
    int8_t new_x = start_x + dx;
    Index landing_square;
    if (new_x < 0 || new_x >= BOARD_DIM) return;
    if (start_y > 0) {
        landing_square = game->board[new_x][start_y - 1];
        if (landing_square != EMPTY && get_color(landing_square) != color) {
            set_bitboard_bit(bitboard, new_x, start_y - 1);
        }
    }
    if (start_y < BOARD_DIM - 1) {
        landing_square = game->board[new_x][start_y + 1];
        if (landing_square != EMPTY && get_color(landing_square) != color) {
            set_bitboard_bit(bitboard, new_x, start_y + 1);
        }
    }
    if (game->board[new_x][start_y] == EMPTY) {
        set_bitboard_bit(bitboard, new_x, start_y);
        if ((color == WHITE && start_x == 6) || (color == BLACK && start_x == 1)) {
            new_x += dx;
            if (game->board[new_x][start_y] == EMPTY) {
                set_bitboard_bit(bitboard, new_x, start_y);
            }
        }
    }
}

void get_piece_bitboard(Game *game, Bitboard *bitboard, Index index, Type type) {
    Color color = get_color(index);
    Coordinate start_x = get_x(game->pieces[index]);
    Coordinate start_y = get_y(game->pieces[index]);
    int8_t new_x = 0, new_y = 0;
    uint8_t times = 0;
    MoveVector *vector = NULL;
    Index landing_square = 0;
    int i = 0;
    *bitboard = (Bitboard)0;
    for (i = 0; i < 8; i++) {
        vector = &(move_vector[type][i]);
        new_x = start_x;
        new_y = start_y;
        times = vector->times;
        for (; times > 0; times--) {
            new_x += vector->dx;
            if (new_x < 0 || new_x >= BOARD_DIM) break;
            new_y += vector->dy;
            if (new_y < 0 || new_y >= BOARD_DIM) break;
            landing_square = game->board[new_x][new_y];
            if (landing_square != EMPTY) {
                if (get_color(landing_square) != color) {
                    set_bitboard_bit(bitboard, new_x, new_y);
                }
                break;
            }
            set_bitboard_bit(bitboard, new_x, new_y);
        }
    }
}

void get_bitboard(Game *game, Bitboard *bitboard, Index index) {
    Piece piece = game->pieces[index];
    if (!is_alive(piece)) return;
    Type type = get_type(index);
    if (type != PAWN) {
        get_piece_bitboard(game, bitboard, index, type);
        return;
    }
    if (!is_promoted(piece)) {
        get_pawn_bitboard(game, bitboard, index);
        return;
    }
    get_piece_bitboard(game, bitboard, index, QUEEN);
}

void print_bitboard(Bitboard *bitboard) {
    int i = 0, j = 0;
    for (i = 0; i < BOARD_DIM; i++) {
        for (j = 0; j < BOARD_DIM; j++) {
            if (get_bitboard_bit_and_shift(bitboard)) printf("1 ");
            else printf("0 ");
        }
        printf("\n");
    }
    printf("\n");
}