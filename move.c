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

char decode_char_map[5] = {'K', 'Q', 'R', 'N', 'B'};

Type decode_piece_type(char c) {
    if (c == decode_char_map[0]) return KING;
    if (c == decode_char_map[1]) return QUEEN;
    if (c == decode_char_map[2]) return ROOK;
    if (c == decode_char_map[3]) return KNIGHT;
    if (c == decode_char_map[4]) return BISHOP;
    return UNKNOWN;
}
Coordinate decode_row_char(char c) {
    return (Coordinate)(BOARD_DIM - c - 1 + '1');
}
Coordinate decode_column_char(char c) {
    return (Coordinate)(c - 'a');
}
int is_piece_type_char(char c) {
    return
        (c == decode_char_map[0]) ||
        (c == decode_char_map[1]) ||
        (c == decode_char_map[2]) ||
        (c == decode_char_map[3]) ||
        (c == decode_char_map[4]);
}
int is_row_char(char c) {
    return (c >= '1') && (c <= '8');
}
int is_column_char(char c) {
    return (c >= 'a') && (c <= 'h');
}
int is_capture_char(char c) {
    return (c == 'x') || (c == 'X');
}

int get_string_length(char *string, int max_length) {
    if (string == NULL) return -1;
    int i = 0;
    for (i = 0; i <= max_length; i++) {
        if (string[i] == '\0' || string[i] == '\n') return i;
    }
    return -1;
}

//                 COL ROW
//       COL     X COL ROW
// PIECE           COL ROW
// PIECE COL       COL ROW
// PIECE     ROW   COL ROW
// PIECE COL ROW   COL ROW
// PIECE         X COL ROW
// PIECE COL     X COL ROW
// PIECE     ROW X COL ROW
// PIECE COL ROW X COL ROW
int decode_move(char *string, Move *move) {
    if (string == NULL || move == NULL) return -1;
    empty_move(move);
    int length = get_string_length(string, 7) - 1;
    if (length < 1) return -1;
    if (!is_row_char(string[length])) return -1;             // last char must be a row
    move->row_to = decode_row_char(string[length]);
    length--;
    if (!is_column_char(string[length])) return -1;          // second to last must be a column
    move->column_to = decode_column_char(string[length]);
    if (length == 0) {                                       // catch moves of the type 'f4'
        move->piece_type = PAWN;
        return 0;
    }
    length--;
    if (is_capture_char(string[length])) {                   // there may be a 'cXd4' or 'NXf4' move
        length--;
        if (length < 0) return -1;
        if (length == 0 && is_column_char(string[length])) { // special pawn move of type 'dxe5'
            move->column_from = decode_column_char(string[length]);
            move->piece_type = PAWN;
            return 0;
        }
    }
    if (is_row_char(string[length])) {                       // catch moves of the type 'N3f4' or 'N3xf4'
        move->row_from = decode_row_char(string[length]);
        length--;
        if (length < 0) return -1;
    }
    if (is_column_char(string[length])) {                    // catch moves of the type 'Ndf4' or 'Ndxf4'
        move->column_from = decode_column_char(string[length]);
        length--;
        if (length < 0) return -1;
    }
    if (!is_piece_type_char(string[length])) {               // the first char must be a piece type
        return -1;
    }
    move->piece_type = decode_piece_type(string[length]);
    if (length != 0) return -1;                              // no other chars must remain in the string
    return 0;
}

char to_row_char(Coordinate x) {
    return (char)(BOARD_DIM - x - 1 + '1');
}
char to_column_char(Coordinate y) {
    return (char)(y + 'a');
}
char to_piece_type_char(Type type) {
    if (type == KING) return decode_char_map[0];
    if (type == QUEEN) return decode_char_map[1];
    if (type == ROOK) return decode_char_map[2];
    if (type == KNIGHT) return decode_char_map[3];
    if (type == BISHOP) return decode_char_map[4];
    if (type == PAWN) return 'P';
    return '?';
}

void print_move(Move *move) {
    printf("Move (%c, %c) => (%c, %c) of %c\n",
        to_column_char(move->column_from), to_row_char(move->row_from),
        to_column_char(move->column_to), to_row_char(move->row_to),
        to_piece_type_char(move->piece_type)
    );
}