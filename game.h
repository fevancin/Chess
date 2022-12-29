#include "piece.h"

typedef struct game {
    Index board[BOARD_DIM][BOARD_DIM];
    Piece pieces[PIECES_NUM];
} Game;

Color get_turn(Game *game);
void set_turn(Game *game, Color color);
void swap_turn(Game *game);

int is_game_end(Game *game);

int is_piece(Game *game, Coordinate x, Coordinate y);

void empty_game(Game *game);

void place_piece(Game *game, Index index, Coordinate x, Coordinate y);

void remove_piece(Game *game, Index i);

void move_piece(Game *game, Index index, Coordinate x, Coordinate y);

void place_initial_configuration(Game *game);

void copy_game(Game *destination, Game *source);

void print_game(Game *game);