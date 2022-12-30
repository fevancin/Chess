#include "piece.h"

// collection of 32 pieces and their index location on the board.
// informations can be retrieved both using pieces[index] or
// board[x][y] in order to obtain O(1) searches.
typedef struct game {
    Index board[BOARD_DIM][BOARD_DIM];
    Piece pieces[PIECES_NUM];
} Game;

// the promoted status of the white king (index 0) is the turn
Color get_turn(Game *game);

// sets the promoted status of the white king
void set_turn(Game *game, Color color);

// alternate the game turn
void swap_turn(Game *game);

// checks if at least one king is not alive
int is_game_end(Game *game);

// true if there is a piece at the (x, y) coordinate
int is_piece(Game *game, Coordinate x, Coordinate y);

// empty the board, kill all the pieces and sets the turn to WHITE
void empty_game(Game *game);

// create a new piece and place it at the given coordinates
void place_piece(Game *game, Index index, Coordinate x, Coordinate y);

// kill the piece of the given index
void remove_piece(Game *game, Index index);

// move a piece to the given (x, y) coordinate,
// killing an eventual piece at the destination
void move_piece(Game *game, Index index, Coordinate x, Coordinate y);

// sets the game to the default initial state:
// r k b q k b k r
// p p p p p p p p
// . . . . . . . .
// . . . . . . . .
// . . . . . . . .
// . . . . . . . .
// P P P P P P P P
// R K B Q K B K R
void place_initial_configuration(Game *game);

// copy all the informations of game source to game destination
void copy_game(Game *destination, Game *source);

// output at the console a textual representation of the board
void print_game(Game *game);