#include "game.h"

typedef uint64_t Bitboard;

void set_bitboard_bit(Bitboard *bitboard, Coordinate x, Coordinate y);

int is_bitboard_bit(Bitboard *bitboard, Coordinate x, Coordinate y);

int get_bitboard_bit_and_shift(Bitboard *bitboard);

void get_bitboard(Game *game, Bitboard *bitboard, Index index);

void print_bitboard(Bitboard *bitboard);