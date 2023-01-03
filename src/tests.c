#include "header/menu.h"
#include <assert.h>

void test_utils() {
    Coordinate c = 0;
    Index index = 0;
    for (c = 0; c < BOARD_DIM; c++) assert(is_valid_coordinate(c));
    assert(!is_valid_coordinate(BOARD_DIM));
    assert(swap_color(WHITE) == BLACK);
    assert(swap_color(BLACK) == WHITE);
    assert(get_type(0) == KING); assert(get_type(1) == KING);
    assert(get_type(2) == QUEEN); assert(get_type(3) == QUEEN);
    assert(get_type(4) == ROOK); assert(get_type(5) == ROOK);
    assert(get_type(6) == ROOK); assert(get_type(7) == ROOK);
    assert(get_type(8) == KNIGHT); assert(get_type(9) == KNIGHT);
    assert(get_type(10) == KNIGHT); assert(get_type(11) == KNIGHT);
    assert(get_type(12) == BISHOP); assert(get_type(13) == BISHOP);
    assert(get_type(14) == BISHOP); assert(get_type(15) == BISHOP);
    assert(get_type(16) == PAWN); assert(get_type(17) == PAWN);
    assert(get_type(18) == PAWN); assert(get_type(19) == PAWN);
    assert(get_type(20) == PAWN); assert(get_type(21) == PAWN);
    assert(get_type(22) == PAWN); assert(get_type(23) == PAWN);
    assert(get_type(24) == PAWN); assert(get_type(25) == PAWN);
    assert(get_type(26) == PAWN); assert(get_type(27) == PAWN);
    assert(get_type(28) == PAWN); assert(get_type(29) == PAWN);
    assert(get_type(30) == PAWN); assert(get_type(31) == PAWN);
    assert(get_type(PIECES_NUM) == UNKNOWN);
    for (index = 0; index < PIECES_NUM; index += 2) {
        assert(get_color(index) == WHITE);
        assert(get_color(index + 1) == BLACK);
    }
    assert(get_piece_char(0) == 'K'); assert(get_piece_char(1) == 'k');
    assert(get_piece_char(2) == 'Q'); assert(get_piece_char(3) == 'q');
    assert(get_piece_char(4) == 'R'); assert(get_piece_char(5) == 'r');
    assert(get_piece_char(6) == 'R'); assert(get_piece_char(7) == 'r');
    assert(get_piece_char(8) == 'N'); assert(get_piece_char(9) == 'n');
    assert(get_piece_char(10) == 'N'); assert(get_piece_char(11) == 'n');
    assert(get_piece_char(12) == 'B'); assert(get_piece_char(13) == 'b');
    assert(get_piece_char(14) == 'B'); assert(get_piece_char(15) == 'b');
    assert(get_piece_char(16) == 'P'); assert(get_piece_char(17) == 'p');
    assert(get_piece_char(18) == 'P'); assert(get_piece_char(19) == 'p');
    assert(get_piece_char(20) == 'P'); assert(get_piece_char(21) == 'p');
    assert(get_piece_char(22) == 'P'); assert(get_piece_char(23) == 'p');
    assert(get_piece_char(24) == 'P'); assert(get_piece_char(25) == 'p');
    assert(get_piece_char(26) == 'P'); assert(get_piece_char(27) == 'p');
    assert(get_piece_char(28) == 'P'); assert(get_piece_char(29) == 'p');
    assert(get_piece_char(30) == 'P'); assert(get_piece_char(31) == 'p');
    assert(get_piece_char(EMPTY) == '.');
}

void test_piece() {
    Piece piece = (Piece)0;
    Coordinate c = 0;
    for (c = 0; c < BOARD_DIM; c++) {
        set_x(&piece, c);
        assert(get_x(piece) == c);
    }
    for (c = 0; c < BOARD_DIM; c++) {
        set_y(&piece, c);
        assert(get_y(piece) == c);
    }
    kill(&piece);
    assert(!is_alive(piece));
    revive(&piece);
    assert(is_alive(piece));
    depromote(&piece);
    assert(!is_promoted(piece));
    promote(&piece);
    assert(is_promoted(piece));
}

void test_game() {
    Game game, game2;
    Index index = 0;
    Coordinate x = 0, y = 0;
    empty_game(&game);
    for (index = 0; index < PIECES_NUM; index++) {
        assert(get_x(game.pieces[index]) == 0);
        assert(get_y(game.pieces[index]) == 0);
        assert(!is_alive(game.pieces[index]));
        assert(!is_promoted(game.pieces[index]));
    }
    for (x = 0; x < BOARD_DIM; x++) {
        for (y = 0; y < BOARD_DIM; y++) {
            assert(game.board[x][y] == EMPTY);
            assert(!is_piece(&game, x, y));
        }
    }
    assert(get_turn(&game) == WHITE);
    set_turn(&game, BLACK);
    assert(get_turn(&game) == BLACK);
    set_turn(&game, WHITE);
    assert(get_turn(&game) == WHITE);
    swap_turn(&game);
    assert(get_turn(&game) == BLACK);
    swap_turn(&game);
    assert(get_turn(&game) == WHITE);
    place_piece(&game, 0, 3, 5); // WHITE KING in (3,5)
    assert(is_piece(&game, 3, 5));
    place_piece(&game, 1, 3, 7); // BLACK KING in (3,7)
    assert(!is_game_end(&game));
    move_piece(&game, 0, 3, 7); // eat BLACK KING with WHITE KING
    assert(is_game_end(&game));
    assert(!is_piece(&game, 3, 5)); // no piece in (3,5)
    assert(game.board[3][7] == 0); // WHITE KING in (3,7)
    remove_piece(&game, 0);
    assert(!is_piece(&game, 3, 7));
    assert(!is_alive(game.pieces[0]));
    place_initial_configuration(&game);
    assert(get_turn(&game) == WHITE);
    assert(get_x(game.pieces[0]) == 7); assert(get_y(game.pieces[0]) == 4);
    assert(get_x(game.pieces[1]) == 0); assert(get_y(game.pieces[1]) == 4);
    assert(get_x(game.pieces[2]) == 7); assert(get_y(game.pieces[2]) == 3);
    assert(get_x(game.pieces[3]) == 0); assert(get_y(game.pieces[3]) == 3);
    assert(get_x(game.pieces[4]) == 7); assert(get_y(game.pieces[4]) == 0);
    assert(get_x(game.pieces[5]) == 0); assert(get_y(game.pieces[5]) == 0);
    assert(get_x(game.pieces[6]) == 7); assert(get_y(game.pieces[6]) == 7);
    assert(get_x(game.pieces[7]) == 0); assert(get_y(game.pieces[7]) == 7);
    assert(get_x(game.pieces[8]) == 7); assert(get_y(game.pieces[8]) == 1);
    assert(get_x(game.pieces[9]) == 0); assert(get_y(game.pieces[9]) == 1);
    assert(get_x(game.pieces[10]) == 7); assert(get_y(game.pieces[10]) == 6);
    assert(get_x(game.pieces[11]) == 0); assert(get_y(game.pieces[11]) == 6);
    assert(get_x(game.pieces[12]) == 7); assert(get_y(game.pieces[12]) == 2);
    assert(get_x(game.pieces[13]) == 0); assert(get_y(game.pieces[13]) == 2);
    assert(get_x(game.pieces[14]) == 7); assert(get_y(game.pieces[14]) == 5);
    assert(get_x(game.pieces[15]) == 0); assert(get_y(game.pieces[15]) == 5);
    assert(get_x(game.pieces[16]) == 6); assert(get_y(game.pieces[16]) == 0);
    assert(get_x(game.pieces[17]) == 1); assert(get_y(game.pieces[17]) == 0);
    assert(get_x(game.pieces[18]) == 6); assert(get_y(game.pieces[18]) == 1);
    assert(get_x(game.pieces[19]) == 1); assert(get_y(game.pieces[19]) == 1);
    assert(get_x(game.pieces[20]) == 6); assert(get_y(game.pieces[20]) == 2);
    assert(get_x(game.pieces[21]) == 1); assert(get_y(game.pieces[21]) == 2);
    assert(get_x(game.pieces[22]) == 6); assert(get_y(game.pieces[22]) == 3);
    assert(get_x(game.pieces[23]) == 1); assert(get_y(game.pieces[23]) == 3);
    assert(get_x(game.pieces[24]) == 6); assert(get_y(game.pieces[24]) == 4);
    assert(get_x(game.pieces[25]) == 1); assert(get_y(game.pieces[25]) == 4);
    assert(get_x(game.pieces[26]) == 6); assert(get_y(game.pieces[26]) == 5);
    assert(get_x(game.pieces[27]) == 1); assert(get_y(game.pieces[27]) == 5);
    assert(get_x(game.pieces[28]) == 6); assert(get_y(game.pieces[28]) == 6);
    assert(get_x(game.pieces[29]) == 1); assert(get_y(game.pieces[29]) == 6);
    assert(get_x(game.pieces[30]) == 6); assert(get_y(game.pieces[30]) == 7);
    assert(get_x(game.pieces[31]) == 1); assert(get_y(game.pieces[31]) == 7);
    for (index = 0; index < PIECES_NUM; index++) {
        assert(is_alive(game.pieces[index]));
        assert(!is_promoted(game.pieces[index]));
    }
    copy_game(&game2, &game);
    for (index = 0; index < PIECES_NUM; index++) {
        assert(game.pieces[index] == game2.pieces[index]);
    }
    for (x = 0; x < BOARD_DIM; x++) {
        for (y = 0; y < BOARD_DIM; y++) {
            assert(game.board[x][y] == game2.board[x][y]);
        }
    }
    assert(get_turn(&game) == get_turn(&game2));
}

void test_bitboard() {
    Bitboard bitboard = (Bitboard)0;
    Game game;
    assert(!is_bitboard_bit(&bitboard, 3, 5));
    set_bitboard_bit(&bitboard, 3, 5);
    assert(is_bitboard_bit(&bitboard, 3, 5));
    assert(bitboard == 0x0000000020000000);
    assert(!is_bitboard_bit(&bitboard, 2, 2));
    set_bitboard_bit(&bitboard, 2, 2);
    assert(is_bitboard_bit(&bitboard, 2, 2));
    assert(bitboard == 0x0000000020040000);
    get_bitboard_bit_and_shift(&bitboard);
    assert(bitboard == 0x0000000010020000);
    empty_game(&game);
    place_piece(&game, 2, 3, 5); // WHITE QUEEN in (3,5)
    place_piece(&game, 12, 3, 7); // WHITE BISHOP in (3,7)
    place_piece(&game, 9, 0, 2); // BLACK KNIGHT in (0,2)
    get_bitboard(&game, &bitboard, 2);
    assert(!is_bitboard_bit(&bitboard, 3, 7));
    assert(is_bitboard_bit(&bitboard, 0, 2));
    place_piece(&game, 16, 6, 0); // WHITE PAWN in (6,0)
    get_bitboard(&game, &bitboard, 16);
    assert(is_bitboard_bit(&bitboard, 5, 0));
    assert(is_bitboard_bit(&bitboard, 4, 0));
    place_piece(&game, 17, 2, 6); // BLACK PAWN in (2,6)
    get_bitboard(&game, &bitboard, 17);
    assert(is_bitboard_bit(&bitboard, 3, 5));
    assert(is_bitboard_bit(&bitboard, 3, 6));
    assert(is_bitboard_bit(&bitboard, 3, 7));
    assert(!is_bitboard_bit(&bitboard, 4, 6));
    assert(bitboard == 0x00000000e0000000);
}

void test_move() {
    Move move;
    empty_move(&move);
    assert(move.piece_type == UNKNOWN);
    assert(move.row_from == BOARD_DIM);
    assert(move.column_from == BOARD_DIM);
    assert(move.row_to == BOARD_DIM);
    assert(move.column_to == BOARD_DIM);
    assert(!is_valid_move(&move));
    move.piece_type = KING;
    assert(!is_valid_move(&move));
    move.row_to = 0;
    move.column_to = 0;
    assert(is_valid_move(&move));
    move.row_to = 7;
    move.column_to = 7;
    assert(is_valid_move(&move));
    move.row_to = BOARD_DIM;
    assert(!is_valid_move(&move));
    // get_index_from_move(&game, &move);
    // apply_move(&game, &move);
    assert(decode_row_char('1') == 7);
    assert(decode_row_char('2') == 6);
    assert(decode_row_char('3') == 5);
    assert(decode_row_char('4') == 4);
    assert(decode_row_char('5') == 3);
    assert(decode_row_char('6') == 2);
    assert(decode_row_char('7') == 1);
    assert(decode_row_char('8') == 0);
    assert(decode_column_char('a') == 0);
    assert(decode_column_char('b') == 1);
    assert(decode_column_char('c') == 2);
    assert(decode_column_char('d') == 3);
    assert(decode_column_char('e') == 4);
    assert(decode_column_char('f') == 5);
    assert(decode_column_char('g') == 6);
    assert(decode_column_char('h') == 7);
    assert(!is_row_char('0'));
    assert(is_row_char('1'));
    assert(is_row_char('2'));
    assert(is_row_char('3'));
    assert(is_row_char('4'));
    assert(is_row_char('5'));
    assert(is_row_char('6'));
    assert(is_row_char('7'));
    assert(is_row_char('8'));
    assert(!is_row_char('9'));
    assert(is_column_char('a'));
    assert(is_column_char('b'));
    assert(is_column_char('c'));
    assert(is_column_char('d'));
    assert(is_column_char('e'));
    assert(is_column_char('f'));
    assert(is_column_char('g'));
    assert(is_column_char('h'));
    assert(decode_move("", &move) != 0);
    assert(decode_move("", NULL) != 0);
    assert(decode_move(NULL, &move) != 0);
    assert(decode_move("e4", &move) == 0);
    assert(move.piece_type == PAWN);
    assert(move.row_to == 4);
    assert(move.column_to == 4);
    assert(move.row_from == BOARD_DIM);
    assert(move.column_from == BOARD_DIM);
    assert(decode_move("dxe4", &move) == 0);
    assert(move.piece_type == PAWN);
    assert(move.row_to == 4);
    assert(move.column_to == 4);
    assert(move.row_from == BOARD_DIM);
    assert(move.column_from == 3);
    assert(decode_move("Ne4", &move) == 0);
    assert(move.piece_type == KNIGHT);
    assert(move.row_to == 4);
    assert(move.column_to == 4);
    assert(move.row_from == BOARD_DIM);
    assert(move.column_from == BOARD_DIM);
    assert(decode_move("Kde4", &move) == 0);
    assert(move.piece_type == KING);
    assert(move.row_to == 4);
    assert(move.column_to == 4);
    assert(move.row_from == BOARD_DIM);
    assert(move.column_from == 3);
    assert(decode_move("B2e4", &move) == 0);
    assert(move.piece_type == BISHOP);
    assert(move.row_to == 4);
    assert(move.column_to == 4);
    assert(move.row_from == 6);
    assert(move.column_from == BOARD_DIM);
    assert(decode_move("Qdxe4", &move) == 0);
    assert(move.piece_type == QUEEN);
    assert(move.row_to == 4);
    assert(move.column_to == 4);
    assert(move.row_from == BOARD_DIM);
    assert(move.column_from == 3);
    assert(decode_move("Rd4xe4", &move) == 0);
    assert(move.piece_type == ROOK);
    assert(move.row_to == 4);
    assert(move.column_to == 4);
    assert(move.row_from == 4);
    assert(move.column_from == 3);
}

void test_value() {
    Game game;
    place_initial_configuration(&game);
    assert(get_game_value(&game) == 0.0);
    move_piece(&game, 24, 4, 4); // e4
    assert(get_game_value(&game) == 8.0);
}

int main(int argc, char *argv[]) {
    test_utils();
    printf("Test of utils: SUCCESS\n");
    test_piece();
    printf("Test of piece: SUCCESS\n");
    test_game();
    printf("Test of game: SUCCESS\n");
    test_bitboard();
    printf("Test of bitboard: SUCCESS\n");
    test_move();
    printf("Test of move: SUCCESS\n");
    test_value();
    printf("Test of value: SUCCESS\n");
    printf("*** All test passed! ***\n");
    return 0;
}