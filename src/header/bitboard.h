#include "game.h"

// a 64 bit variable that store boolean information about a chessboard
typedef uint64_t Bitboard;

// puts 1 into the bit relative to the (x, y) coordinate
void set_bitboard_bit(Bitboard *bitboard, Coordinate x, Coordinate y);

// check for the specific (x, y) bit
int is_bitboard_bit(Bitboard *bitboard, Coordinate x, Coordinate y);

// a more efficient manner of retrieving bits if done in rapid succession.
// bitboard is then distorted and unusable for other purposes.
int get_bitboard_bit_and_shift(Bitboard *bitboard);

// prints a visual representation of the bitboard into the console
void print_bitboard(Bitboard *bitboard);

// calculate the possible moves of a given piece into the bitboard:
// 1 means a possible movement
void get_bitboard(Game *game, Bitboard *bitboard, Index index);