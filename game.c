#include "game.h"

Color get_turn(Game *game) {
    return is_promoted(game->pieces[0]) ? BLACK : WHITE;
}
void set_turn(Game *game, Color color) {
    if (color == WHITE) depromote(&(game->pieces[0]));
    else promote(&(game->pieces[0]));
}
void swap_turn(Game *game) {
    if (is_promoted(game->pieces[0])) depromote(&(game->pieces[0]));
    else promote(&(game->pieces[0]));
}

int is_game_end(Game *game) {
    if (is_alive(game->pieces[0]) && is_alive(game->pieces[1])) return 0;
    return 1;
}

int is_piece(Game *game, Coordinate x, Coordinate y) {
    return game->board[x][y] != EMPTY;
}

void empty_game(Game *game) {
    memset(game->board, EMPTY, BOARD_DIM * BOARD_DIM);
    memset(game->pieces, (Piece)0, PIECES_NUM);
    set_turn(game, WHITE);
}

void place_piece(Game *game, Index index, Coordinate x, Coordinate y) {
    Piece *piece = &(game->pieces[index]);
    set_x(piece, x);
    set_y(piece, y);
    revive(piece);
    depromote(piece);
    game->board[x][y] = index;
}

void remove_piece(Game *game, Index i) {
    Piece p = game->pieces[i];
    game->board[get_x(p)][get_y(p)] = 0;
    kill(&(game->pieces[i]));
}

void move_piece(Game *game, Index index, Coordinate x, Coordinate y) {
    Index dest_index = game->board[x][y];
    if (dest_index != EMPTY) {
        kill(&(game->pieces[dest_index]));
    }
    Piece *piece = &(game->pieces[index]);
    game->board[get_x(*piece)][get_y(*piece)] = EMPTY;
    set_x(piece, x);
    set_y(piece, y);
    if ((x == BOARD_DIM - 1 || x == 0) && get_type(index) == PAWN) promote(piece);
    game->board[x][y] = index;
}

Position initial_configuration_map[32] = {
    {7, 4}, {0, 4},                                                 // kings
    {7, 3}, {0, 3},                                                 // queens
    {7, 0}, {0, 0}, {7, 7}, {0, 7},                                 // rooks
    {7, 1}, {0, 1}, {7, 6}, {0, 6},                                 // knights
    {7, 2}, {0, 2}, {7, 5}, {0, 5},                                 // bishops
    {6, 0}, {1, 0}, {6, 1}, {1, 1}, {6, 2}, {1, 2}, {6, 3}, {1, 3}, // pawns
    {6, 4}, {1, 4}, {6, 5}, {1, 5}, {6, 6}, {1, 6}, {6, 7}, {1, 7}
};

void place_initial_configuration(Game *game) {
    empty_game(game);
    Index index = 0;
    for (index = 0; index < PIECES_NUM; index++) {
        place_piece(game, index, initial_configuration_map[index].x, initial_configuration_map[index].y);
    }
}